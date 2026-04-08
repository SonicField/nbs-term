# Architecture

nbs-term is a terminal emulator. It parses VT escape sequences in C, renders to a Tk canvas in Python, and transports bytes over SSH via nbs-ssh.

## The Three Layers

```
SSH bytes  ──►  C extension (parse + state)  ──►  Tk canvas (render)
                      ▲                               │
                      │                               ▼
                keyboard input  ◄──────────────  Tk event loop
```

**C extension (`_nbsterm`):** The terminal engine. Parses VT100/xterm-256color escape sequences, maintains a screen buffer (characters, attributes, cursor position), handles scrollback. Written in Phoenics (.phc files), compiled to a single C translation unit. This is where correctness lives.

**Python orchestration (`nbsterm.py`):** Wires the C extension to Tk (display) and nbs-ssh (transport). Two threads:

| Thread | Runs | Does |
|--------|------|------|
| Main (Tk) | `root.mainloop()` | Canvas rendering, keyboard input, auth dialogs |
| Background (asyncio) | `asyncio.new_event_loop()` | SSH connection, byte I/O |

**Invariant:** The C extension is only called from the main thread. Raw bytes cross the thread boundary via `root.after()`.

**nbs-ssh:** Handles SSH connection, authentication (agent keys, certificates, keyboard-interactive/Duo), host key verification, and SSH config (`~/.ssh/config` — ProxyJump, ProxyCommand, IdentityFile, IdentityAgent). nbs-term passes an `SSHInteractionHandler` for auth dialogs.

## The C Extension

Eight Phoenics source files, compiled as one translation unit:

| File | Responsibility |
|------|---------------|
| `sgr.phc` | SGR attribute parsing — `phc_flags CellAttr`, `phc_descr Color` |
| `screen.phc` | Screen buffer, cursor, scroll regions, alternate screen, dirty tracking |
| `vt_parser.phc` | VT state machine — CSI, OSC, DCS, escape sequences |
| `input.phc` | Key encoding — `phc_flags Modifier`, `phc_enum SpecialKey` |
| `render.phc` | Extracts screen state for Python (spans with attributes) |
| `color.phc` | CIELAB colour conversion (sRGB to perceptual space) |
| `color_utils.phc` | Ported Python colour functions: dim_color, gamma_correct, xterm_256_color |
| `extension.phc` | CPython module definition, method table, type exports |

The parser is a byte-at-a-time state machine. It handles partial sequences across `feed()` calls — a multi-byte escape sequence split across two SSH reads is reassembled correctly.

### Build Pipeline

Two paths produce C from Phoenics:

| Path | Command | Used by | Output |
|------|---------|---------|--------|
| Development | `cc -E \| phc` | `make test` | `build/extension.c` (preprocessed) |
| Distribution | `cat \| grep -v #include \| phc` | `make regenerate` | `generated/extension.c` (portable) |

The generated file is committed so end users need only a C compiler, not phc. `make verify-regenerate` checks freshness in CI.

## Authentication Flow

nbs-term uses nbs-ssh's `SSHConnection` with a `TkInteractionHandler`:

```
SSHConnection reads ~/.ssh/config
  → discovers ProxyCommand, IdentityFile, IdentityAgent
  → builds auth chain: cert agent → keys → kbdint → password
  → cert publickey partial success → server offers Duo (kbdint)
  → TkInteractionHandler.on_kbdint() → Tk dialog → user responds
  → auth complete → PTY session starts
```

The certificate-backed agent key (from `IdentityFile` + `IdentityAgent` in SSH config) provides the first authentication factor. Keyboard-interactive (Duo 2FA) provides the second. This matches the nbs-ssh CLI's auth flow.

**Known limitation:** nbs-term currently builds the cert auth chain manually in `_ssh_session()`, bypassing `SSHConnection._build_auth_configs()`. This is documented tech debt — see `feature-requests/ssh-interaction-handler-integration.md`.

## Rendering

The Python renderer uses a double-buffered canvas with configurable refresh rate:

1. `feed(data)` buffers SSH data and schedules a render after `_refresh_ms` (configurable via `refresh_hz`)
2. `_flush_and_render()` feeds all buffered data to the C extension, then calls `_render()`
3. `_render()` uses dirty-row tracking (`get_dirty_rows()`) — only changed rows are redrawn
4. Double-buffer tag system (`buf_0`/`buf_1`): new items drawn hidden, then swapped visible atomically
5. Cursor rendered as a Unicode character (Block: U+2588, Underline: U+2581, Bar: U+258F) using the same font as terminal text — automatic pixel-perfect alignment

### Colour Pipeline

```
C extension palette (sRGB)  →  gamma correction (Python)  →  Tk canvas
```

Gamma correction compensates for macOS colour management. Tk on macOS passes hex colours to Cocoa, which applies the display profile (Display P3 on modern Macs). The gamma slider in preferences lets the user compensate visually. Default: 1.2 on Mac (darkens midtones), 1.0 elsewhere.

SGR attributes affecting colour:

| SGR | Attribute | Effect |
|-----|-----------|--------|
| 1 | Bold | Bold font variant |
| 2 | Dim/Faint | Foreground at 50% brightness |
| 3 | Italic | Italic font variant |
| 7 | Inverse | Swap foreground and background |
| 38;5;N | 256-colour fg | xterm palette index |
| 48;5;N | 256-colour bg | xterm palette index |

## Configuration

`~/.nbs/nbs-term.honest` (Honest format). Created with defaults on first run.

Settings: font family, font size, cursor style (Block/Wireframe/Underline/Bar), cursor blink, foreground colour, background colour, gamma correction, refresh rate (Hz).

Access preferences via Cmd+, (Mac) or Ctrl+, (Linux). Changes apply immediately — no restart needed. Foreground and background colours are selectable via a 256-colour picker (16 ANSI + 216 colour cube + 24 grayscale). Non-monospace fonts are automatically rejected with a fallback to Menlo (Mac) or monospace (Linux).

## Key Bindings

| Binding | Action |
|---------|--------|
| Cmd+C / Ctrl+Shift+C | Copy selection to clipboard |
| Cmd+V / Ctrl+Shift+V | Paste from clipboard (bracketed paste) |
| Cmd+, / Ctrl+, | Open preferences |
| Ctrl+letter | Send control character (Ctrl-C = 0x03) |
| Alt/Option+letter | Send ESC + letter (Meta key) |
| Mouse drag | Select text |

## Threading Model

```
Main thread (Tk)              Background thread (asyncio)
─────────────────             ──────────────────────────
root.mainloop()               loop.run_until_complete()
  ├─ Key events                 ├─ SSH connection
  ├─ Canvas rendering           ├─ Data read loop
  ├─ Auth dialogs               └─ PTY resize
  └─ feed() → C extension
       │
       └─ root.after(0, feed, data)  ◄── crosses thread boundary
```

`concurrent.futures.Future` bridges the threads for auth dialogs: the asyncio thread creates a Future, `root.after()` schedules the dialog on the main thread, the dialog result resolves the Future.

## Test Suite

268 tests across 7 files:

| File | Tests | What it covers |
|------|------:|---------------|
| test_parser | 117 | VT state machine, CSI, SGR, UTF-8, partial feeds |
| test_screen | 57 | Cursor, scroll, erase, resize, scrollback, alt screen |
| test_integration | 23 | Python ↔ C extension interface |
| test_orchestration | 9 | SSH data flow, threading model |
| test_gui_logic | 44 | Selection coordinates, text extraction, kbdint bridge, gamma |
| test_config | 18 | Config loading, defaults, CLI overrides, platform paths |
| test_ssh_integration | 3 | SSH transport (skipped without nbs-ssh) |
