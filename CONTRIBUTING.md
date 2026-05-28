# Contributing to nbs-term

Thank you for your interest in nbs-term (standalone terminal emulator with Phoenics-powered VT parser)!

## How to Contribute

### Reporting Bugs

If you find a bug, please open an issue with:
- A clear, descriptive title
- Steps to reproduce the behavior
- Expected vs actual behavior
- Terminal size and remote shell details

### Pull Requests

Pull requests are welcome, especially for:
- Bug fixes
- VT sequence coverage improvements
- Test coverage
- Documentation improvements

Before submitting a large PR, consider opening an issue first to discuss the approach.

**PR Guidelines:**
- Canonical gate must pass: 14 per-`.phc` test entries + `make verify-phc-invariants`
- Add tests for new functionality
- Follow existing code style

## Development Setup

```bash
# Clone the repository with the phc submodule
git clone --recurse-submodules --branch pure-phc-master https://github.com/SonicField/nbs-term.git
cd nbs-term

# One-time vendored Tcl/Tk build
make tcl-tk

# Production binary
make p3_pty

# Canonical gate
make verify-phc-invariants
```

## Architecture

- `src/*.phc` — Phoenics (C11 superset) source files for the terminal engine
- `tests/*.phc` — Per-source unit tests (libc-only + Tk-linked + golden harness)
- `deps/phc/` — phc compiler submodule
- `deps/tcl/`, `deps/tk/` — vendored Tcl/Tk 8.6.15 source (built to `deps/tcl-build/`)
- `scripts/{mac,windows}-setup-phc.{sh,ps1}` — one-line install scripts

## License

By contributing, you agree that your contributions will be licensed under the MIT license.
