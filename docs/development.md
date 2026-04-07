# Development

## Prerequisites

The C extension compiles from a pre-generated file. End users need only:
- Python 3.12+
- A C11 compiler (gcc, clang, or MSVC)
- Tkinter (see platform notes below)

Developers modifying `.phc` sources also need [phc](https://github.com/SonicField/phoenics) (included as a git submodule).

### Platform Setup

**Mac (Homebrew):**
```bash
brew install python-tk@3.14    # Tk GUI framework
```

**Linux (Debian/Ubuntu):**
```bash
sudo apt install python3-tk    # Tk GUI framework
```

**Windows:**
Python.org installer includes Tk. Install [Visual Studio Build Tools](https://visualstudio.microsoft.com/visual-cpp-build-tools/) for the C compiler.

## Install

```bash
git clone https://github.com/SonicField/nbs-term.git
cd nbs-term
pip install -e .
```

`pip install` automatically fetches nbs-ssh from GitHub.

## Developer Install

```bash
git clone --recurse-submodules https://github.com/SonicField/nbs-term.git
cd nbs-term
make          # builds phc from submodule, then the C extension
make test     # runs the full test suite
pip install -e .
```

## Build Pipeline

### The Two Paths

Phoenics source files (`.phc`) compile to C through two pipelines:

**Development path** (`make test`):
```
src/*.phc  →  cc -E (preprocess)  →  phc (transform)  →  cc (compile)  →  test binary
```

**Distribution path** (`make regenerate`):
```
src/*.phc  →  cat (concatenate)  →  grep -v #include  →  phc  →  generated/extension.c
```

The distribution path strips `#include` directives and prepends standard headers, producing a portable C file that compiles on any platform with Python headers and a C11 compiler.

### Source Files

| File | Lines | Responsibility |
|------|------:|---------------|
| sgr.phc | ~100 | SGR attribute parsing |
| screen.phc | ~400 | Screen buffer, cursor, scroll |
| vt_parser.phc | ~600 | VT escape sequence state machine |
| input.phc | ~200 | Key encoding for terminal input |
| render.phc | ~150 | Screen state extraction for Python |
| extension.phc | ~200 | CPython module glue |
| color.phc | ~165 | CIELAB colour conversion (sRGB ↔ perceptual) |

### Makefile Targets

| Target | What it does |
|--------|-------------|
| `make` | Build phc (if needed) + C extension |
| `make test` | Run all test suites |
| `make test-asan` | Run with AddressSanitizer |
| `make test-ubsan` | Run with UndefinedBehaviourSanitizer |
| `make regenerate` | Update `generated/extension.c` from `.phc` sources |
| `make verify-regenerate` | Check `generated/extension.c` is current (CI uses this) |
| `make phc` | Build phc from submodule |
| `make clean` | Remove build artefacts |

## Test Suite

268 tests. Run with `make test`.

```
test_parser:        117 tests — VT state machine, CSI, SGR, UTF-8
test_screen:         57 tests — cursor, scroll, erase, resize, scrollback
test_integration:    23 tests — Python ↔ C extension
test_orchestration:   9 tests — SSH data flow, threading
test_gui_logic:      35 tests — selection, kbdint bridge, coordinates
test_config:         18 tests — config loading, defaults, overrides
test_ssh_integration: 3 tests — SSH transport (skipped without nbs-ssh)
```

C tests compile through the phc pipeline and use the test framework from the phc submodule.

### Sanitisers

Every C change should pass ASan and UBSan:

```bash
make test-asan     # heap errors, use-after-free, buffer overflow
make test-ubsan    # undefined behaviour, signed overflow
```

## CI

GitHub Actions runs on every push to master:
1. Build C extension via `pip install -e .`
2. Run Python integration tests
3. Build phc from submodule
4. Verify `generated/extension.c` is current

CI is Linux-only. macOS CI is a known gap — see `feature-requests/`.

## Adding a New .phc File

1. Write the file in `src/`
2. Add `#include "yourfile.phc"` to `src/extension.phc`
3. Add the file to the `regenerate` target's `cat` command in `Makefile`
4. Add it to the `verify-regenerate` target's `cat` command
5. Run `make regenerate` to update `generated/extension.c`
6. Run `make test` to verify

## Project Structure

```
nbs-term/
├── nbsterm.py              Python orchestration (Tk + SSH + C extension)
├── config.py               Configuration system (Honest format)
├── setup.py                C extension build config
├── pyproject.toml           Package metadata + dependencies
├── generated/extension.c   Pre-generated C (committed, portable)
├── src/                    Phoenics source files
│   ├── sgr.phc
│   ├── screen.phc
│   ├── vt_parser.phc
│   ├── input.phc
│   ├── render.phc
│   ├── extension.phc
│   └── color.phc
├── tests/                  Test suite
├── docs/                   Documentation
├── deps/phc/               phc submodule (for developers)
└── feature-requests/       Planned improvements
```
