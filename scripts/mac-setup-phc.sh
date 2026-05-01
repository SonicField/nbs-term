#!/bin/bash
# nbs-term Mac pure-phc Setup Script
#
# Builds the standalone phc binary build/p3_pty (no Python at runtime;
# links Tcl/Tk + libc). Pure-phc-master branch.
#
# Run: bash scripts/mac-setup-phc.sh
#  or: curl -fsSL https://raw.githubusercontent.com/SonicField/nbs-term/pure-phc-master/scripts/mac-setup-phc.sh | bash
#
# Per supervisor 2026-05-01 14:42:10 — companion to scripts/mac-setup.sh
# (which builds the legacy Python C extension; this script's output is a
# separate executable, both can coexist).

set -e

REPO_URL="https://github.com/SonicField/nbs-term.git"
REPO_DIR="$HOME/nbs-term-phc"
BRANCH="pure-phc-master"

echo "=== nbs-term Mac pure-phc Setup ==="

# ---- Step 1: Homebrew ----
if ! command -v brew &>/dev/null; then
    echo "ERROR: Homebrew not installed."
    echo "Install from https://brew.sh:"
    echo '  /bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"'
    exit 1
fi
echo "Homebrew found."

# ---- Step 2: Tcl/Tk + clang ----
echo "Installing Tcl/Tk via Homebrew..."
brew install tcl-tk pkg-config || {
    echo "ERROR: brew install tcl-tk failed."
    exit 1
}
TCL_PREFIX="$(brew --prefix tcl-tk)"
echo "Tcl/Tk: $TCL_PREFIX"

# Homebrew's tcl-tk is keg-only; pkg-config + linker need its lib paths
# explicitly. Export so the Makefile pkg-config call resolves correctly.
export PKG_CONFIG_PATH="$TCL_PREFIX/lib/pkgconfig${PKG_CONFIG_PATH:+:$PKG_CONFIG_PATH}"
export LDFLAGS="-L$TCL_PREFIX/lib${LDFLAGS:+ $LDFLAGS}"
export CPPFLAGS="-I$TCL_PREFIX/include${CPPFLAGS:+ $CPPFLAGS}"

if ! pkg-config --exists tk; then
    echo "ERROR: pkg-config cannot find tk after brew install. Check Homebrew."
    exit 1
fi

# ---- Step 3: clone or refresh the pure-phc-master branch ----
if [ -d "$REPO_DIR/.git" ]; then
    echo "Repo at $REPO_DIR exists — fetching pure-phc-master..."
    cd "$REPO_DIR"
    git fetch origin "$BRANCH"
    git checkout "$BRANCH"
    git reset --hard "origin/$BRANCH"
else
    echo "Cloning $BRANCH branch into $REPO_DIR..."
    git clone --branch "$BRANCH" --single-branch "$REPO_URL" "$REPO_DIR"
    cd "$REPO_DIR"
fi
echo "HEAD: $(git rev-parse --short HEAD) ($(git log -1 --format=%s))"

# ---- Step 4: build phc compiler from deps/phc ----
echo "Building phc compiler..."
make -C deps/phc CC=cc -j 2>&1 | tail -3
if [ ! -x deps/phc/build/phc ]; then
    echo "ERROR: phc build failed."
    exit 1
fi
echo "phc: $(deps/phc/build/phc 2>&1 || true | head -1)"

# ---- Step 5: build the pure-phc terminal binary ----
echo "Building build/p3_pty..."
make p3_pty 2>&1 | tail -5
if [ ! -x build/p3_pty ]; then
    echo "ERROR: build/p3_pty not produced."
    exit 1
fi

# ---- Static guards (mirror Linux verify-no-python-link) ----
echo "Verifying zero Python linkage..."
if otool -L build/p3_pty 2>/dev/null | grep -i python; then
    echo "FAIL: build/p3_pty links Python. B-shape requires zero Python at runtime."
    exit 1
fi
echo "PASS: build/p3_pty has zero Python linkage."

make verify-no-eval-objex 2>&1 | tail -2

# ---- Step 6: self-test ----
echo "Running self-test (build/p3_pty -test)..."
if build/p3_pty -test; then
    echo "SELF-TEST OK: PTY echo -> render round-trip on Mac."
else
    rc=$?
    echo "SELF-TEST FAILED (exit $rc)."
    echo "Likely causes:"
    echo "  * Not running inside an Aqua session (need a window server)."
    echo "  * Tk runtime DLLs not picked up — check otool -L build/p3_pty."
    echo "  * /bin/sh not available (unusual)."
    exit $rc
fi

echo ""
echo "=== Build Complete ==="
echo "Run interactively:"
echo "  $REPO_DIR/build/p3_pty                          # local /bin/sh"
echo "  $REPO_DIR/build/p3_pty --ssh ssh user@host       # live SSH"
echo ""
echo "Smoke checklist (theologian 14:13:* + supervisor 13:04:49):"
echo "  1. Type a few commands, see output, exit cleanly (golden path)."
echo "  2. cat a large file or run vim — exercises ring backpressure."
echo "  3. Close window mid-output — exercises cleanup race."
