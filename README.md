# nbs-term

A standalone terminal emulator with a Phoenics-powered VT parser, rendered directly via Tcl/Tk and driven by a cross-platform PTY (forkpty on POSIX, ConPTY on Windows). Connects to remote systems via SSH using a child process.

All terminal semantics live in C. The runtime is a single binary — no Python at runtime, no system Tcl/Tk dependency (vendored 8.6.15 under `deps/`).

[![Pure-phc Build & Test](https://github.com/SonicField/nbs-term/actions/workflows/build-test.yml/badge.svg?branch=pure-phc-master)](https://github.com/SonicField/nbs-term/actions/workflows/build-test.yml)

## Install

The setup scripts build everything from source (vendored Tcl/Tk, the phc compiler, `p3_pty`). Only a host C toolchain and Git are required up front; the scripts handle the rest.

**Mac:**

```bash
curl -fsSL https://raw.githubusercontent.com/SonicField/nbs-term/pure-phc-master/scripts/mac-setup-phc.sh | bash
```

Self-clones into `$HOME/nbs-term-phc`, triggers Xcode CLT install if absent, builds vendored Tcl/Tk + the phc compiler + `build/p3_pty`. Launch with `$HOME/nbs-term-phc/build/p3_pty`.

**Linux:**

```bash
git clone --branch pure-phc-master --single-branch https://github.com/SonicField/nbs-term.git
cd nbs-term
git submodule update --init deps/phc
make tcl-tk    # vendored Tcl/Tk 8.6.15 (one-time, ~3 min)
make p3_pty    # production binary
./build/p3_pty
```

**Windows:**

```powershell
iwr -useb 'https://raw.githubusercontent.com/SonicField/nbs-term/pure-phc-master/scripts/windows-setup-phc.ps1' | iex
```

Self-clones into `%USERPROFILE%\nbs-term-phc`, installs Visual Studio Build Tools if absent (admin required), builds vendored Tcl/Tk + the phc compiler + `build\p3_pty.exe`, and copies the Tcl/Tk runtime DLLs next to the binary so it's launchable from any shell. Launch with `%USERPROFILE%\nbs-term-phc\build\p3_pty.exe`.

## Usage

Local shell:

```bash
./build/p3_pty
```

Live SSH:

```bash
./build/p3_pty --ssh ssh user@host
```

## What it does

- VT100/xterm-256color terminal emulation (cursor, scrolling, SGR attributes, alt screen)
- UTF-8 with error recovery (U+FFFD for invalid sequences)
- DEC line-drawing charset (tmux pane borders)
- 256-color and bold/italic/underline/inverse rendering
- Bracketed paste mode
- Modifier key encoding (Shift/Ctrl/Alt + arrows, F-keys)
- Scrollback buffer (10,000 lines, ring buffer)
- Per-span attribute rendering for correct syntax highlighting
- Tabbed sessions
- Mouse selection + clipboard integration
- Configurable palette + fonts via `~/.nbs/nbs-term.honest` (POSIX) / `%LOCALAPPDATA%\nbs\nbs-term.honest` (Win)

## Architecture

```
User input -> Tk binds -> input.phc encodes -> pty_write (PTY master)
PTY master -> pty_read -> vt_parser.phc -> screen.phc state -> Tk canvas render
```

Single thread, Tcl/Tk event loop. PTY reads land via a Tcl file handler. No Python in the runtime; the entire stack (input encoding, VT parsing, screen state, rendering, PTY I/O) is compiled C linked against vendored Tcl/Tk.

## Keyboard Shortcuts

| Shortcut | Action |
|----------|--------|
| Cmd+, (Mac) / Ctrl+, (Linux/Windows) | Open preferences |
| Cmd+C / Ctrl+Shift+C | Copy selection |
| Cmd+V / Ctrl+Shift+V | Paste |
| Cmd+T / Ctrl+T | New tab |
| Cmd+W / Ctrl+W | Close tab |
| Cmd+1..9 / Ctrl+1..9 | Switch to tab N |
| F11 | Toggle fullscreen |

## Tcl Linkage

`p3_pty` links the vendored Tcl/Tk 8.6.15 build under `deps/tcl-build/lib` (libtcl8.6, libtk8.6). No system Tcl/Tk dependency — every platform uses the same in-tree build, pinned at the source level under `deps/tcl/` and `deps/tk/`. The static guard `make verify-phc-invariants` enforces this on every build (no system `/usr/lib`, `/opt/`, or `/System/` Tcl in the binary's link map).

## Development

Requires [phc](https://github.com/SonicField/phoenics) (Phoenics preprocessor) for modifying `.phc` source files. Included as a git submodule under `deps/phc`.

```bash
git clone --recurse-submodules --branch pure-phc-master https://github.com/SonicField/nbs-term.git
cd nbs-term

make tcl-tk                  # one-time vendored Tcl/Tk build
make p3_pty                  # production binary
make verify-phc-invariants   # static guards (no Python / no Tcl_EvalObjEx / vendored-only)

# Per-source unit tests (libc-only + Tk-linked + golden harness):
make test_pty_burst test_pixel_to_cell test_extract_utf8 test_render_gamma \
     test_input_keys test_compute_layout test_pty_resize test_blink_step \
     test_register_named_fonts test_bold_recolour test_palette_lookup \
     test_tabs_logic test_alt_mask test_tab_dispatch test_render_state
```

## Tests

Canonical gate (CI on Linux + macOS + Windows via `.github/workflows/build-test.yml`):

- 14 per-`.phc` test entries (234 cases): `test_alt_mask`, `test_blink_step`, `test_bold_recolour`, `test_compute_layout`, `test_extract_utf8`, `test_input_keys`, `test_palette_lookup`, `test_pixel_to_cell`, `test_pty_burst`, `test_pty_resize`, `test_register_named_fonts`, `test_render_gamma`, `test_tab_dispatch`, `test_tabs_logic`
- `make verify-phc-invariants` (3 invariants: no Python linkage / no `Tcl_EvalObjEx` / vendored Tcl/Tk only)
- Per-platform `test_render_state` golden harness (per-surface `.tcl` driver scripts under `tests/scripts/`, goldens under `tests/goldens/`)

## License

MIT
