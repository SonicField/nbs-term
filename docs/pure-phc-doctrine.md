# Pure-phc Doctrine

The pure-phc branch (`pure-phc-master`) builds standalone native terminal binaries directly from Phoenics (`.phc`) source. The B-shape doctrine asserts a small set of build invariants that distinguish a pure-phc binary from the legacy Python C-extension build.

The invariants are enforced by static gates in the `Makefile` (target: `verify-phc-invariants`) and the platform setup scripts (`scripts/{windows,mac}-setup-phc.{ps1,sh}`).

## Invariants

### 1. No Python linkage at runtime

Pure-phc binaries (`build/p1_hello`, `build/p1_5_notebook`, `build/p2_render`, `build/p3_pty`) must not link against `libpython*` or import any Python DLL. Python is permitted as a *build-time* tool (e.g. for code-generation via `phc`) but not at runtime.

Gate: `verify-no-python-link` (`ldd` on Linux, `otool -L` on Mac, `dumpbin /dependents` on Windows; reject any match against `python`).

### 2. No `Tcl_EvalObjEx` in production source

Production `.phc` files must use `Tcl_EvalObjv` with `Tcl_NewStringObj`-constructed argv arrays, not `Tcl_EvalObjEx` with printf-formatted strings. The latter risks Tcl-script injection on attacker-controlled content.

Gate: `verify-no-eval-objex` (greps `src/*.phc`; allowlist for P1/P1.5 calibration scaffolds).

### 3. No system Tcl/Tk linkage

Tcl/Tk is a **first-class source-code dependency of this repository**, vendored under `deps/tcl/` and `deps/tk/` at version 8.6.15 (BSD-licensed; pristine upstream tarballs verifiable against the SHA256s recorded in commit `e05c00c`).

Pure-phc binaries must link against the vendored build under `deps/tcl-build/` produced by the `tcl-tk` Makefile target (or by the `windows-setup-phc.ps1` / `mac-setup-phc.sh` setup scripts). They must not link against system `/usr/lib/libtcl*`, `/usr/lib/libtk*`, Homebrew `/opt/homebrew/.../libtcl*`, or Magicsplat `C:\Tcl\...` installs.

Gate: `verify-no-system-tcl-link` (`ldd` on Linux, `otool -L` on Mac; rejects matches against `/(usr|opt|System)/.*libt(cl|k)`; requires `$(TCL_VENDOR_PREFIX)/lib/libtcl8.6` in the import list).

Bumping the vendored Tcl/Tk version requires explicit re-vendoring: replace `deps/tcl/` and `deps/tk/` with the extracted contents of the new upstream tarballs, update the SHA256 references, and re-run the build pipeline on all three platforms (Win/Mac/Linux).

## Why source vendoring (not system or installer-fetched Tcl/Tk)

Per `alexie 2026-05-05` (decisions D-1777978221 + D-1777978497):

> A 100% source code solution which assumes nothing about installed software or tooling. It works.

The class of bug eliminated is *Tcl/Tk-version-mismatch*. With the vendored build, the version is pinned, the source is in the repo, and there is no "which Tcl is on this system" debugging surface across Win/Mac/Linux. The single source of truth is `deps/{tcl,tk}/`.

The host C compiler (MSVC on Windows, Xcode CLT on Mac, gcc/clang on Linux) is the architectural floor. Bootstrap is delegated to the platform setup scripts (`windows-setup-phc.ps1` auto-installs MSVC Build Tools; `mac-setup-phc.sh` triggers `xcode-select --install` if absent). Everything above the C compiler floor — including all of Tcl/Tk — is built from vendored source.

## Roll-up

```
make verify-phc-invariants
```

runs all three gates in sequence. CI and gatekeeper review treat any gate failure as a hard block.
