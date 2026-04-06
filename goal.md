# nbs-term: Cross-Platform Terminal Emulator

A C-based terminal emulator embedded as a Tk widget, connected to remote systems via SSH (nbs-ssh). All terminal semantics in C. Python transports bytes.

**Language:** Phoenics (phc) — a superset of C11 with discriminated unions, exhaustive matching, pattern destructuring, and automatic cleanup. Non-negotiable.

## Architecture

```
User input → Tk → C extension encodes → SSH.write(bytes)
SSH.read(bytes) → C extension parses/renders → Tk canvas
Window resize → C extension recalculates → SSH.resize(cols, rows)
```

Three components, strict separation:

| Component | Language | Owns | Does NOT own |
|-----------|----------|------|-------------|
| Terminal emulator | C (phc) | VT parsing, screen buffer, cursor, scrollback, rendering, input encoding | SSH, UI events |
| SSH transport | Python (nbs-ssh) | Connection, PTY, byte stream, resize propagation | Terminal semantics |
| Orchestration | Python | Lifecycle, threading, wiring bytes between terminal and SSH | Anything else |

**Critical invariant:** All terminal semantics live in the C extension. Python must not interpret escape sequences.

## Where Phoenics Helps

The terminal emulator is built on discriminated unions and state machines — exactly what phc was designed for.

### VT Parser State Machine

The parser walks through bytes, transitioning between states. Each state processes data differently:

```c
phc_descr VTState {
    Ground {},
    Escape {},
    CSI { int params[16]; int param_count; int priv; },
    OSC { char buf[512]; int len; },
    DCS { char buf[512]; int len; }
};
```

Every byte-handling function uses `phc_match` — add a state, every handler must update:

```c
phc_match(VTState, parser->state) {
    case Ground: { handle_ground(parser, byte); } break;
    case Escape: { handle_escape(parser, byte); } break;
    case CSI(params, param_count, priv): {
        execute_csi(screen, params, param_count, priv);
    } break;
    case OSC(buf, len): { handle_osc(term, buf, len); } break;
    case DCS(buf, len): { handle_dcs(term, buf, len); } break;
}
```

### Color Representation

SGR attributes use three color models. Without phc, this is a tagged union with manual tag checks scattered across the renderer. With phc:

```c
phc_descr Color {
    Default {},
    Indexed { int index; },
    RGB { int r; int g; int b; }
};

// Renderer knows it handles every case:
phc_match(Color, cell.fg) {
    case Default: { use_default_fg(); } break;
    case Indexed(index): { set_palette_color(index); } break;
    case RGB(r, g, b): { set_rgb(r, g, b); } break;
}
```

### Input Events

User actions are one-of-several-shapes, each with different data:

```c
phc_descr InputEvent {
    Key { int codepoint; int modifiers; },
    Mouse { int button; int x; int y; int modifiers; },
    Paste { const char *data; int len; },
    Resize { int cols; int rows; }
};
```

### Resource Cleanup

The C extension manages screen buffers, scrollback, decode state. `phc_defer` ensures cleanup on every exit path:

```c
ScreenBuffer *buf = screen_buffer_alloc(cols, rows);
phc_defer { screen_buffer_free(buf); }

char *line = parse_osc_title(data, len);
phc_defer { free(line); }

// ... use buf and line ...
// Cleanup fires automatically at every return
```

## Build Pipeline

```
source.phc  →  cc -E (preprocess)  →  phc (transform)  →  cc -c (compile)
```

phc runs AFTER the C preprocessor. This means:
- `#include` is expanded — phc sees full header content (handled efficiently via island parsing)
- Macros are resolved — `Py_RETURN_NONE` expands to `return Py_None;` before phc sees it
- `phc_defer` correctly intercepts returns inside expanded macros (this is a feature — cleanup fires before Python API returns)
- `#ifdef` conditionals are resolved — conditional phc_descr variants work

Makefile pattern for Python C extensions:

```makefile
PHC := path/to/phc
PYTHON_CFLAGS := $(shell python3-config --cflags)
TK_CFLAGS := $(shell pkg-config --cflags tk)

# Preprocess with Python/Tk headers, transform with phc, compile
%.c: %.phc $(PHC)
	$(CC) $(PYTHON_CFLAGS) $(TK_CFLAGS) -E $< | $(PHC) > $@

# Multi-file rule (generates type manifest for cross-file matching)
%.c %.phc-types: %.phc $(PHC)
	$(CC) $(PYTHON_CFLAGS) $(TK_CFLAGS) -E $< | $(PHC) --emit-types=$*.phc-types > $@

# Cross-file matching (consumer includes manifest)
render.c: render.phc types.phc-types $(PHC)
	$(CC) $(PYTHON_CFLAGS) $(TK_CFLAGS) -E $< | $(PHC) --type-manifest=types.phc-types > $@
```

**Pitfall:** Python.h must be included first in every .phc file (Python requirement). phc passes it through unchanged.

## Terminal Emulation Scope

**Target:** `TERM=xterm-256color`. Enough to run tmux, vim, htop, less correctly.

### Tier 1 — Mandatory (Phase 1)

- UTF-8 encoding
- Cursor movement (CSI)
- Screen clearing and erasure
- Line wrapping, scrolling regions
- Insert/delete character and line
- SGR attributes (bold, underline, 16-color, 256-color)
- Normal + alternate screen buffer
- Standard key sequences (arrows, Home/End, F1-F12, PgUp/PgDn)
- Meta via ESC prefix
- Bracketed paste mode
- Window resize handling
- Scrollback buffer

### Tier 2 — Phase 2

- Mouse reporting (modes 1000, 1002)
- Focus in/out reporting
- Truecolor (RGB) support
- OSC title setting

### Tier 3 — Optional

- OSC 52 clipboard
- OSC 8 hyperlinks
- Synchronized updates
- Cursor styling

### Out of Scope

Sixel graphics, pixel-addressable rendering, full DEC terminal set, GPU acceleration.

## Validation

The emulator is sufficient when these work correctly:

- **Shell:** bash, zsh
- **Pager:** less
- **Editor:** vim (including inside tmux)
- **Monitor:** htop
- **Multiplexer:** tmux — pane create/switch, resize, copy mode, mouse

Tested via recorded session replay and deterministic I/O verification, not visual inspection.

### Testing Strategy

1. **Unit tests** (C, run with `make test`): VT parser state transitions, screen buffer operations, SGR attribute handling. Use phc_descr types directly — construct a VTState, feed bytes, assert resulting state.
2. **Session replay** (recorded byte streams): Capture real terminal sessions (`script -t` or `ttyrec`). Feed recorded output bytes through the parser, compare screen buffer state against known-good snapshots.
3. **Application integration** (manual + CI): Launch real apps (vim, tmux, htop) over SSH, verify correct rendering. Automate where possible via `expect`-style scripting.
4. **ASan/UBSan gate**: All C code compiled and tested with AddressSanitizer and UndefinedBehaviorSanitizer. Zero leaks, zero memory errors.

### Error Handling

Use phc_descr for error propagation within the C extension:

```c
phc_descr ParseResult {
    Ok { int bytes_consumed; },
    Err { const char *message; int position; }
};
```

Python-facing functions return standard Python error conventions (NULL + PyErr_SetString). phc_defer ensures reference counts are correct on every exit path — this is where phc_defer earns its keep in Python C extensions.

### Threading

- Tk owns the main thread
- SSH data arrives on a background thread
- `term.feed(bytes)` must marshal to the Tk thread via `Tk_ThreadQueueEvent` or Python's `root.after(0, ...)`
- The C extension releases the GIL during parsing (`Py_BEGIN_ALLOW_THREADS` / `Py_END_ALLOW_THREADS`) to avoid blocking Python
- All Tk rendering happens on the main thread — no concurrent canvas access

## File Structure

```
nbs-term/
├── src/
│   ├── vt_parser.phc      # VT state machine (phc_descr VTState)
│   ├── screen.phc          # Screen buffer, cursor, scrollback
│   ├── sgr.phc             # SGR attributes, Color type
│   ├── input.phc           # Input event encoding (phc_descr InputEvent)
│   ├── render.phc          # Tk canvas rendering
│   └── extension.phc       # Python C extension entry points
├── tests/
│   ├── test_parser.c       # VT parser unit tests
│   ├── test_screen.c       # Screen buffer tests
│   └── sessions/           # Recorded terminal sessions for replay
├── Makefile
└── goal.md
```

## Non-Goals

- Full emulation of historical terminal types
- Pixel-perfect compatibility with all terminal emulators
- GPU-accelerated rendering
- General-purpose GUI framework
- Arbitrary shell embedding beyond SSH/local PTY

## Security

- SSH handled entirely by nbs-ssh
- Terminal must not execute local commands
- Clipboard via bracketed paste (prevents injection)

## Dependencies

- Python runtime + Tk
- C11 compiler (clang or gcc)
- phc (Phoenics preprocessor)
- nbs-ssh (Python SSH transport module)
