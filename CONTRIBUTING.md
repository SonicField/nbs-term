# Contributing to nbs-term

Thank you for your interest in nbs-term (terminal emulator with Phoenics-powered VT parser)!

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
- All tests must pass (`make test`)
- ASan/UBSan clean (`make test-asan` / `make test-ubsan`)
- Add tests for new functionality
- Follow existing code style

## Development Setup

```bash
# Clone the repository
git clone https://github.com/SonicField/nbs-term.git
cd nbs-term

# Build and test (requires phc for .phc source changes)
make
make test

# Install in development mode (also fetches nbs-ssh from GitHub)
pip install -e .
```

## Architecture

- `src/*.phc` — Phoenics (C11 superset) source files for the terminal engine
- `generated/extension.c` — Pre-generated C from the phc pipeline (committed for users without phc)
- `nbsterm.py` — Python orchestration layer (Tk + SSH wiring)
- `tests/` — Test suites (C unit tests + Python integration tests)

## License

By contributing, you agree that your contributions will be licensed under the MIT license.
