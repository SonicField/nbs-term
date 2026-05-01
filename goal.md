# nbs-term: Cross-Platform Terminal Emulator

A standalone Phoenics (phc) terminal emulator. All terminal semantics, display, and orchestration in phc. SSH (and any other transport) is an external program, invoked via `--ssh <argv>`, with bytes pumped through a PTY proxy.

**Language:** Phoenics (phc) — a superset of C11 with discriminated unions, exhaustive matching, pattern destructuring, and automatic cleanup. Non-negotiable.

**No Python at runtime.** No Python C extension. nbs-term is a phc-built native executable that links Tcl/Tk + libc directly.

## Architecture

```
User input  → Tk (C-API) → phc encodes → write(pty_master, bytes)
read(pty_master, bytes)  → phc parses/renders → Tk canvas (C-API)
Window resize → phc recomputes → ioctl(pty_master, TIOCSWINSZ, ...)
```

Two components, strict separation:

| Component | Owns | Does NOT own |
|-----------|------|-------------|
| nbs-term (phc binary) | VT parsing, screen buffer, cursor, scrollback, rendering, input encoding, Tk display, tab/settings UI, PTY master, --ssh subprocess lifecycle | Network, authentication, key management |
| External --ssh program (e.g. `ssh user@host`) | Connection, authentication (kbdint, certs, ProxyJump), wire protocol, byte stream | Terminal semantics, UI |

**Critical invariant:** All terminal semantics live in phc. The --ssh program is opaque — nbs-term treats its stdout/stdin as raw bytes, surfaces its stdin prompts (e.g. password, kbdint) as ordinary terminal input, and never interprets or re-encodes them.

**--ssh interface:** PTY proxy. nbs-term opens a PTY (forkpty on unix, ConPTY on Windows), execs the --ssh argv into the child, and treats the master fd as the byte stream. Window resize propagates via TIOCSWINSZ on the master. This is the standard xterm/alacritty/kitty pattern.

**Authentication:** Delegated entirely to the external --ssh program. kbdint (Duo 2FA) prompts appear in the terminal as ordinary tty I/O. No in-process auth dialog.

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

SGR attributes use three color models. With phc:

```c
phc_descr Color {
    Default {},
    Indexed { int index; },
    RGB { int r; int g; int b; }
};

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

`phc_defer` ensures cleanup on every exit path:

```c
ScreenBuffer *buf = screen_buffer_alloc(cols, rows);
phc_defer { screen_buffer_free(buf); }

char *line = parse_osc_title(data, len);
phc_defer { free(line); }
```

## Build Pipeline

```
source.phc  →  cc -E (preprocess)  →  phc (transform)  →  cc -c (compile)  →  ld → nbs-term executable
```

phc runs AFTER the C preprocessor. `#include` is expanded, macros are resolved, conditional `#ifdef` works.

The build links against:
- `libtcl` + `libtk` (Tcl/Tk C library, version 8.6+)
- `libc` (forkpty, ioctl, signal, etc.)
- No Python.

Cross-platform PTY:
- Unix: `forkpty(3)` from `<util.h>` (Linux) or `<libutil.h>` (BSD/macOS)
- Windows: ConPTY APIs (`CreatePseudoConsole`, `ResizePseudoConsole`) — Win10 1809+

## Terminal Emulation Scope

**Target:** `TERM=xterm-256color`. Enough to run tmux, vim, htop, less correctly.

### Tier 1 — Mandatory

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

### Tier 2

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

## UI Surfaces

**Multi-tab:** kept. Reimplemented in phc via Tcl/Tk C-API, driving the standard `ttk::notebook` widget. Tab create/close/switch keybindings preserved.

**Settings UI:** kept. Font / cursor / color dialogs reimplemented in phc as Tk toplevels driven through the Tcl/Tk C-API. Persistence via a config file written/read by phc (`config.phc`); no Python config layer.

## Validation

The emulator is sufficient when these work correctly:

- **Shell:** bash, zsh
- **Pager:** less
- **Editor:** vim (including inside tmux)
- **Monitor:** htop
- **Multiplexer:** tmux — pane create/switch, resize, copy mode, mouse

Tested via recorded session replay and deterministic I/O verification, not visual inspection.

### Testing Strategy

1. **Unit tests** (phc, run with `make test`): VT parser state transitions, screen buffer operations, SGR attribute handling. Use phc_descr types directly.
2. **Session replay** (recorded byte streams): Capture real terminal sessions (`script -t` or `ttyrec`). Feed recorded output bytes through the parser, compare screen buffer state against known-good snapshots.
3. **Application integration** (manual + CI): Launch real apps (vim, tmux, htop) via `--ssh ssh user@host` (or `--ssh /bin/sh` for local), verify correct rendering. Automate where possible via `expect`-style scripting.
4. **ASan/UBSan gate**: All phc code compiled and tested with AddressSanitizer and UndefinedBehaviorSanitizer. Zero leaks, zero memory errors.

Test driver: subprocess invocation of the nbs-term binary (replaces the prior Python C-extension introspection model).

### Error Handling

Use phc_descr for error propagation:

```c
phc_descr ParseResult {
    Ok { int bytes_consumed; },
    Err { const char *message; int position; }
};
```

### Threading

- Tcl event loop owns the main thread
- PTY master fd is registered via `Tcl_CreateFileHandler`; bytes arrive in the Tcl event loop
- All Tk rendering happens on the main thread — no concurrent canvas access
- No background threads; no asyncio

## File Structure

```
nbs-term/
├── src/
│   ├── vt_parser.phc      # VT state machine (phc_descr VTState)
│   ├── screen.phc          # Screen buffer, cursor, scrollback
│   ├── sgr.phc             # SGR attributes, Color type
│   ├── input.phc           # Input event encoding (phc_descr InputEvent)
│   ├── render.phc          # Tk canvas rendering
│   ├── tk_render.phc       # Tcl/Tk C-API binding for canvas draw
│   ├── pty.phc             # forkpty / ConPTY abstraction; --ssh subprocess lifecycle
│   ├── tabs.phc            # ttk::notebook driver
│   ├── settings.phc        # Tk dialogs (font / cursor / color)
│   ├── config.phc          # config-file parse/serialize
│   ├── app.phc             # Application bootstrap, Tcl event loop
│   └── main.phc            # main(), argv parse, --ssh dispatch
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
- Built-in SSH client (use `--ssh <argv>`)
- Built-in authentication (the --ssh program handles its own)

## Security

- Authentication and connection security delegated to the --ssh program
- Terminal must not execute local commands (the --ssh argv is the only spawn point; user-controlled at launch, not at runtime)
- Clipboard via bracketed paste (prevents injection)

## Dependencies

- C11 compiler (clang or gcc)
- phc (Phoenics preprocessor)
- Tcl/Tk 8.6+ (libtcl + libtk)
- POSIX libc (forkpty) on unix; Windows 10 1809+ for ConPTY

No Python. No nbs-ssh. No asyncssh.
