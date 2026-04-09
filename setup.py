"""Build configuration for the _nbsterm C extension.

Uses Tcl stubs for cross-platform Tcl linkage: a small static library
(libtclstub.a) is linked at build time, and all Tcl functions resolve
at runtime through the interpreter's own function table via Tcl_InitStubs.
This avoids version mismatches — we always use the same Tcl that Python's
_tkinter loaded.
"""
import glob
import os
import platform
import subprocess
from setuptools import setup, Extension

if platform.system() == "Windows":
    extra_compile_args = ["/std:c11", "/W3", "/DPY_SSIZE_T_CLEAN"]
else:
    extra_compile_args = [
        "-std=c11", "-Wall", "-Wextra",
        "-Wno-unused-function",
        "-Wno-missing-field-initializers",
        "-DPY_SSIZE_T_CLEAN",
    ]
include_dirs = []
extra_link_args = []
extra_objects = []


def _find_tcl_stubs():
    """Find Tcl stubs library (libtclstub.a) and headers.

    No _tkinter import — works in pip's build isolation sandbox.
    Returns (include_dir, stub_lib_path) or (None, None).
    """
    if platform.system() == "Darwin":
        # macOS: Homebrew tcl-tk
        try:
            tcl_prefix = subprocess.check_output(
                ["brew", "--prefix", "tcl-tk"], text=True
            ).strip()
            inc = os.path.join(tcl_prefix, "include")
            lib_dir = os.path.join(tcl_prefix, "lib")
            # Match any tclstub naming: libtclstub8.6.a, libtclstub.a, etc.
            stubs = glob.glob(os.path.join(lib_dir, "libtcl*stub*.a"))
            if not stubs:
                stubs = glob.glob(os.path.join(lib_dir, "*tclstub*.a"))
            if stubs and os.path.isdir(inc):
                return inc, stubs[0]
        except (subprocess.CalledProcessError, FileNotFoundError):
            pass

    elif platform.system() == "Linux":
        # System Tcl dev packages — search common paths
        for inc_path in ["/usr/include/tcl8.6", "/usr/include/tcl9.0",
                         "/usr/include/tcl", "/usr/include"]:
            if os.path.isfile(os.path.join(inc_path, "tcl.h")):
                for lib_path in ["/usr/lib/x86_64-linux-gnu", "/usr/lib64",
                                 "/usr/lib"]:
                    stubs = glob.glob(os.path.join(lib_path, "libtcl*stub*.a"))
                    if stubs:
                        return inc_path, stubs[0]
                return inc_path, None

    elif platform.system() == "Windows":
        # Windows: use embedded Tcl headers and stubs source from deps/tcl-win/.
        # No external Tcl SDK needed — headers are bundled, stubs bootstrap is
        # compiled as an additional source file (see extension sources below).
        setup_dir = os.path.dirname(os.path.abspath(__file__))
        tcl_win = os.path.join(setup_dir, "deps", "tcl-win")
        inc = os.path.join(tcl_win, "include")
        if os.path.isfile(os.path.join(inc, "tcl.h")):
            return inc, None  # No separate stubs lib — compiled inline
        return None, None

    return None, None


# Find Tcl stubs library
tcl_inc, tcl_stub = _find_tcl_stubs()

print(f"Tcl stubs: inc={tcl_inc}, stub={tcl_stub}")
if tcl_inc:
    include_dirs.append(tcl_inc)

if tcl_stub:
    # Static stubs library — not affected by -undefined dynamic_lookup.
    extra_objects.append(tcl_stub)
else:
    print("WARNING: No Tcl stubs library found — Tcl calls may fail at runtime")

sources = ["generated/extension.c"]
if platform.system() == "Windows":
    # Compile our stubs bootstrap alongside the extension — provides
    # Tcl_InitStubs via GetProcAddress, no Tcl import library needed.
    sources.append(os.path.join("deps", "tcl-win", "tclStubLib.c"))

extension = Extension(
    "_nbsterm",
    sources=sources,
    extra_compile_args=extra_compile_args,
    include_dirs=include_dirs,
    extra_link_args=extra_link_args,
    extra_objects=extra_objects,
)

setup(ext_modules=[extension])
