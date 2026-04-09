#!/bin/bash
# nbs-term Mac Setup Script
# Installs all dependencies, creates venv, builds, tests.
# Run: bash scripts/mac-setup.sh

set -e

echo "=== nbs-term Mac Setup ==="

# Step 1: Check for Homebrew
if ! command -v brew &>/dev/null; then
    echo "ERROR: Homebrew not installed."
    echo "Install from: https://brew.sh"
    echo '  /bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"'
    exit 1
fi
echo "Homebrew found."

# Step 2: Install Python with Tk + Tcl dev headers
echo "Installing Python and Tcl/Tk..."
brew install python@3.14 tcl-tk || {
    echo "ERROR: brew install failed. Check Homebrew and try again."
    exit 1
}

# Verify Python
PYTHON=$(brew --prefix python@3.14)/bin/python3.14
if [ ! -f "$PYTHON" ]; then
    echo "ERROR: Python 3.14 not found at $(brew --prefix python@3.14)/bin/python3.14"
    exit 1
fi

$PYTHON -c "import tkinter; print(f'Tcl/Tk version: {tkinter.TclVersion}')" || {
    echo "ERROR: tkinter not available. Check Python installation."
    exit 1
}

# Find and embed Tcl headers into the repo for deterministic builds
TCL_PREFIX=$(brew --prefix tcl-tk)
TCL_HEADER=$(find "$TCL_PREFIX" -name tcl.h -print -quit 2>/dev/null)
if [ -z "$TCL_HEADER" ]; then
    echo "ERROR: tcl.h not found under $TCL_PREFIX"
    exit 1
fi
TCL_INC_DIR=$(dirname "$TCL_HEADER")
echo "Tcl headers found at $TCL_INC_DIR"

# Step 3: Create venv
VENV_DIR="$HOME/nbsterm-venv"
if [ -d "$VENV_DIR" ]; then
    echo "Venv exists at $VENV_DIR — reusing."
else
    echo "Creating venv at $VENV_DIR..."
    $PYTHON -m venv "$VENV_DIR"
fi
source "$VENV_DIR/bin/activate"

# Step 4: Clone or pull repo
REPO_DIR="$HOME/nbs-term"
if [ -d "$REPO_DIR/.git" ]; then
    echo "Repo exists — pulling latest..."
    cd "$REPO_DIR"
    git pull
else
    echo "Cloning nbs-term..."
    git clone https://github.com/SonicField/nbs-term.git "$REPO_DIR"
    cd "$REPO_DIR"
fi

# Step 5: Embed Tcl headers from Homebrew into repo
echo "Embedding Tcl headers from $TCL_INC_DIR..."
mkdir -p deps/tcl-mac/include
cp "$TCL_INC_DIR"/*.h deps/tcl-mac/include/
echo "Embedded $(ls deps/tcl-mac/include/*.h | wc -l) headers."

# Step 6: Clean and install
echo "Installing nbs-term..."
rm -rf build/ _nbsterm*.so
pip install -e .

# Step 6: Run tests
echo "Running tests..."
pip install pytest
pytest

echo ""
echo "=== Setup Complete ==="
echo "To use nbs-term:"
echo "  source $VENV_DIR/bin/activate"
echo "  nbs-term user@host"
