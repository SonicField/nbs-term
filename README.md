# nbs-term

A terminal emulator with a Phoenics-powered VT parser, embedded as a Tk widget and connected to remote systems via SSH ([nbs-ssh](https://github.com/SonicField/nbs-ssh)).

All terminal semantics live in C. Python transports bytes.

## Install

Requires Python 3.12+, a C compiler, and Tk (for the GUI).

**Mac (Homebrew):**

```bash
brew install python-tk@3.14   # match your Python version
git clone https://github.com/SonicField/nbs-term.git
cd nbs-term
pip install -e .              # builds C extension + installs nbs-ssh from GitHub
```

**Linux (Debian/Ubuntu):**

```bash
sudo apt install python3-tk
git clone https://github.com/SonicField/nbs-term.git
cd nbs-term
pip install -e .
```

**Windows:**

Install [Python 3.12+](https://www.python.org/downloads/) from python.org (includes Tk by default).
Install [Build Tools for Visual Studio](https://visualstudio.microsoft.com/visual-cpp-build-tools/) (C compiler).

```powershell
git clone https://github.com/SonicField/nbs-term.git
cd nbs-term
pip install -e .
```

No C preprocessor needed — the C extension builds from pre-generated C.

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

## Development

Requires [phc](https://github.com/SonicField/phoenics) (Phoenics preprocessor) for modifying `.phc` source files. It's included as a git submodule.

```bash
git clone --recurse-submodules https://github.com/SonicField/nbs-term.git
cd nbs-term

# Edit .phc sources, then:
make              # build extension + run tests (requires phc)
make regenerate   # update generated/extension.c from .phc sources
make test         # run all test suites (209 tests)
make test-asan    # run with AddressSanitizer
make test-ubsan   # run with UndefinedBehaviorSanitizer

pip install -e .  # reinstall after changes
```

The generated C file (`generated/extension.c`) is committed so end users don't need phc.

## Tests

- 117 VT parser tests (state transitions, CSI, SGR, UTF-8, partial feeds, adversarial inputs)
- 57 screen buffer tests (cursor, scroll, erase, resize, scrollback, alt screen)
- 23 Python integration tests
- 9 orchestration tests (SSH data flow, threading model)
- 3 SSH integration tests (requires nbs-ssh)

```bash
make test    # run all
```

## License

MIT
