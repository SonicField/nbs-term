#!/bin/bash
# nbs-term Mac pure-phc Setup Script
#
# Builds the standalone phc binary build/p3_pty (no Python at runtime;
# links Tcl/Tk + libc). Pure-phc-master branch.
#
# Self-contained: only assumes Xcode Command Line Tools (host C compiler)
# and Git. Tcl/Tk is built from vendored source under deps/tcl/ + deps/tk/
# (8.6.15, BSD-licensed; pinned in repo per alexie 2026-05-05 D-1777978221,
# D-1777978497). No Homebrew dependency; no system Tcl/Tk dependency.
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

# ---- Step 1: ensure Xcode Command Line Tools (host C compiler floor) ----
if ! xcode-select -p &>/dev/null; then
    echo "Xcode Command Line Tools not installed."
    echo "Triggering installer (a GUI dialog will appear)..."
    xcode-select --install || true
    echo "Re-run this script after the installer finishes."
    exit 1
fi
if ! command -v cc &>/dev/null; then
    echo "ERROR: cc not on PATH after xcode-select. Re-install CLT."
    exit 1
fi
echo "Xcode CLT found: $(xcode-select -p)"

# ---- Step 2: clone or refresh the pure-phc-master branch ----
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

# ---- Step 3: build vendored Tcl/Tk from deps/{tcl,tk}/ ----
TCL_SRC_DIR="$REPO_DIR/deps/tcl"
TK_SRC_DIR="$REPO_DIR/deps/tk"
TCL_BUILD_DIR="$REPO_DIR/deps/tcl-build"

if [ ! -d "$TCL_SRC_DIR/unix" ] || [ ! -x "$TCL_SRC_DIR/unix/configure" ]; then
    echo "ERROR: vendored Tcl source missing or unconfigured at $TCL_SRC_DIR/unix"
    exit 1
fi
if [ ! -d "$TK_SRC_DIR/unix" ] || [ ! -x "$TK_SRC_DIR/unix/configure" ]; then
    echo "ERROR: vendored Tk source missing or unconfigured at $TK_SRC_DIR/unix"
    exit 1
fi

if [ ! -f "$TCL_BUILD_DIR/lib/libtcl8.6.dylib" ]; then
    echo "Building vendored Tcl 8.6.15 -> $TCL_BUILD_DIR ..."
    (
        cd "$TCL_SRC_DIR/unix"
        ./configure --prefix="$TCL_BUILD_DIR" --enable-shared --enable-threads
        make -j
        make install
    )
    echo "Built Tcl 8.6.15."
else
    echo "Vendored Tcl 8.6.15 already built (delete deps/tcl-build to force rebuild)."
fi

if [ ! -f "$TCL_BUILD_DIR/lib/libtk8.6.dylib" ]; then
    echo "Building vendored Tk 8.6.15 -> $TCL_BUILD_DIR ..."
    (
        cd "$TK_SRC_DIR/unix"
        # --enable-aqua: build native Cocoa Tk on Mac, not X11 (which would need
        # X11/Xlib.h and friends — not part of macOS).
        ./configure --prefix="$TCL_BUILD_DIR" --enable-shared --enable-threads \
            --enable-aqua \
            --with-tcl="$TCL_SRC_DIR/unix"
        make -j
        make install
    )
    echo "Built Tk 8.6.15 (Aqua)."
else
    echo "Vendored Tk 8.6.15 already built."
fi

# ---- Step 4: build phc compiler from deps/phc ----
# phc is a git submodule. `git clone --single-branch` does NOT init submodules,
# so deps/phc is empty until explicit init. Recovery: if a prior failed run
# left deps/phc non-empty (e.g. created deps/phc/build/ before bombing), git
# submodule update refuses to clone into it. Deinit + rm + init is the
# canonical recovery (per supervisor 2026-05-05 12:15:05).
if [ ! -d "deps/phc/src" ]; then
    if [ -d "deps/phc" ] && [ -n "$(ls -A deps/phc 2>/dev/null)" ]; then
        echo "Cleaning stale deps/phc before submodule init..."
        git submodule deinit -f deps/phc 2>/dev/null || true
        rm -rf deps/phc
    fi
    echo "Initializing phc submodule (deps/phc)..."
    git submodule update --init deps/phc
    if [ ! -d "deps/phc/src" ]; then
        echo "ERROR: git submodule init failed for deps/phc."
        exit 1
    fi
fi
echo "Building phc compiler..."
make -C deps/phc CC=cc -j 2>&1 | tail -3
if [ ! -x deps/phc/build/phc ]; then
    echo "ERROR: phc build failed."
    exit 1
fi
echo "phc: $(deps/phc/build/phc 2>&1 || true | head -1)"

# ---- Step 5: build the pure-phc terminal binary against vendored Tcl/Tk ----
# Override Makefile's pkg-config-based TCLTK_CFLAGS/TCLTK_LIBS so it uses the
# vendored install instead of any system tcl/tk. Mac dylib needs -rpath so
# the binary finds libtcl8.6.dylib / libtk8.6.dylib at runtime.
echo "Building build/p3_pty..."
make p3_pty \
    TCLTK_CFLAGS="-I$TCL_BUILD_DIR/include" \
    TCLTK_LIBS="-L$TCL_BUILD_DIR/lib -ltk8.6 -ltcl8.6 -Wl,-rpath,$TCL_BUILD_DIR/lib" \
    2>&1 | tail -5
if [ ! -x build/p3_pty ]; then
    echo "ERROR: build/p3_pty not produced."
    exit 1
fi

# ---- Static guards (mirror Linux verify-no-python-link + new tcl-vendored guard) ----
echo "Verifying zero Python linkage..."
if otool -L build/p3_pty 2>/dev/null | grep -i python; then
    echo "FAIL: build/p3_pty links Python. B-shape requires zero Python at runtime."
    exit 1
fi
echo "PASS: build/p3_pty has zero Python linkage."

echo "Verifying vendored (not system) Tcl/Tk linkage..."
if otool -L build/p3_pty 2>/dev/null | grep -E '/(usr|opt|System)/.*libt(cl|k)' >/dev/null; then
    echo "FAIL: build/p3_pty links system Tcl/Tk (must use vendored deps/tcl-build)."
    otool -L build/p3_pty | grep -E 'libt(cl|k)'
    exit 1
fi
if ! otool -L build/p3_pty 2>/dev/null | grep -F "$TCL_BUILD_DIR/lib/libtcl8.6" >/dev/null; then
    echo "FAIL: build/p3_pty does not link vendored libtcl8.6."
    otool -L build/p3_pty | grep -E 'libt(cl|k)'
    exit 1
fi
echo "PASS: build/p3_pty links vendored Tcl/Tk only."

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
    echo "  * Vendored Tk dylib not picked up — check otool -L build/p3_pty."
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
