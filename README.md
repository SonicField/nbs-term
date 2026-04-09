# nbs-term

A terminal emulator with a Phoenics-powered VT parser, embedded as a Tk widget and connected to remote systems via SSH ([nbs-ssh](https://github.com/SonicField/nbs-ssh)).

All terminal semantics live in C. Python transports bytes.

## Install

Requires Python 3.12+, a C compiler, Tk, and Tcl development headers (for the GUI and render pipeline).

**Mac (Homebrew):**

```bash
brew install python-tk@3.14 tcl-tk   # match your Python version
git clone https://github.com/SonicField/nbs-term.git
cd nbs-term
make install                 # clean build + pip install (recommended)
```

**Linux (Debian/Ubuntu):**

```bash
sudo apt install python3-tk tcl-dev
git clone https://github.com/SonicField/nbs-term.git
cd nbs-term
make install
```

**Windows (automated):**

```powershell
Invoke-WebRequest -Uri 'https://raw.githubusercontent.com/SonicField/nbs-term/master/scripts/windows-setup.ps1' -OutFile windows-setup.ps1
.\windows-setup.ps1
```

The script installs Python 3.12 (per-user, with Tk), Visual Studio Build Tools, creates a venv, clones the repo, builds, and runs tests. Run as Administrator if Build Tools need installing.

No C preprocessor needed — the C extension builds from pre-generated C.

**Rebuilding after updates:**

Always use `make install` after `git pull` — it removes stale build artifacts before rebuilding. Plain `pip install -e .` may pick up old `.so` files from a previous build.

## Usage

```bash
nbs-term user@host
nbs-term user@host:2222
```

Or via Python:

```bash
python -m nbsterm user@host
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

## Architecture

```
User input -> Tk -> C extension encodes -> SSH.write(bytes)
SSH.read(bytes) -> C extension parses/renders -> Tk canvas
```

Two threads:
- **Main thread (Tk):** event loop, terminal feed, canvas rendering
- **Background thread (asyncio):** nbs-ssh connection, byte I/O

The C extension is only called from the main thread. Raw bytes cross the thread boundary.

## Keyboard Shortcuts

| Shortcut | Action |
|----------|--------|
| Cmd+, (Mac) / Ctrl+, (Linux/Windows) | Open preferences |
| Cmd+C / Ctrl+Shift+C | Copy selection |
| Cmd+V / Ctrl+Shift+V | Paste |

## Tcl Linkage (Cross-Platform)

The C extension calls Tcl/Tk functions to render terminal content on the canvas. Each platform resolves these calls differently:

- **Linux:** Links `libtclstub.a` (from `tcl-dev`). `Tcl_InitStubs()` populates a function-pointer table from the Tcl interpreter that `_tkinter` loaded.
- **macOS:** Same stubs mechanism. `libtclstub.a` from Homebrew `tcl-tk`. Avoids `-undefined dynamic_lookup` version mismatches.
- **Windows:** Tcl headers embedded in `deps/tcl-win/include/`. Custom stubs bootstrap via `GetProcAddress`. No external Tcl dev files needed.

Key invariant: the extension never links a Tcl shared library directly. It resolves Tcl functions at runtime through the interpreter that `_tkinter` loaded, guaranteeing version consistency.

## Development

Requires [phc](https://github.com/SonicField/phoenics) (Phoenics preprocessor) for modifying `.phc` source files. It's included as a git submodule.

```bash
git clone --recurse-submodules https://github.com/SonicField/nbs-term.git
cd nbs-term

# Edit .phc sources, then:
make              # build extension + run tests (requires phc)
make regenerate   # update generated/extension.c from .phc sources
make test         # run all test suites (210 tests)
make test-asan    # run with AddressSanitizer
make test-ubsan   # run with UndefinedBehaviorSanitizer

pip install -e .  # reinstall after changes
```

The generated C file (`generated/extension.c`) is committed so end users don't need phc.

## Tests

- 117 VT parser tests (state transitions, CSI, SGR, UTF-8, partial feeds, adversarial inputs)
- 57 screen buffer tests (cursor, scroll, erase, resize, scrollback, alt screen)
- 23 Python integration tests (including UTF-8/CJK span verification)
- 9 orchestration tests (SSH data flow, threading model)
- 4 SSH integration tests (requires nbs-ssh, skipped if not installed)

```bash
make test    # run all
```

## License

MIT
