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
brew install python@3.14 tcl-tk 2>/dev/null || brew upgrade python@3.14 tcl-tk 2>/dev/null || true

# Verify
PYTHON=$(brew --prefix python@3.14)/bin/python3.14
if [ ! -f "$PYTHON" ]; then
    PYTHON=python3
fi

$PYTHON -c "import tkinter; print(f'Tcl/Tk version: {tkinter.TclVersion}')" || {
    echo "ERROR: tkinter not available. Check Python installation."
    exit 1
}

# Verify Tcl headers exist
TCL_INC=/opt/homebrew/opt/tcl-tk/include
if [ ! -f "$TCL_INC/tcl.h" ]; then
    echo "ERROR: Tcl headers not found at $TCL_INC"
    echo "Run: brew install tcl-tk"
    exit 1
fi
echo "Tcl headers found at $TCL_INC"

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

# Step 5: Clean and install
echo "Installing nbs-term..."
rm -rf build/ _nbsterm*.so
pip install -e .

# Step 6: Run tests
echo "Running tests..."
pip install pytest 2>/dev/null
pytest

echo ""
echo "=== Setup Complete ==="
echo "To use nbs-term:"
echo "  source $VENV_DIR/bin/activate"
echo "  nbs-term user@host"
