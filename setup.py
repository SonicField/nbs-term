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

extra_compile_args = [
    "-std=c11", "-Wall", "-Wextra",
    "-Wno-unused-function",
    "-Wno-missing-field-initializers",
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
            stubs = glob.glob(os.path.join(lib_dir, "libtclstub*.a"))
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
                    stubs = glob.glob(os.path.join(lib_path, "libtclstub*.a"))
                    if stubs:
                        return inc_path, stubs[0]
                return inc_path, None

    elif platform.system() == "Windows":
        # Windows: Tcl bundled with Python. Find stubs via sys.prefix.
        import sys
        for ver in ["90", "86", "85"]:
            stub = os.path.join(sys.prefix, "libs", f"tclstub{ver}.lib")
            inc = os.path.join(sys.prefix, "include")
            if os.path.isfile(stub) and os.path.isdir(inc):
                return inc, stub

    return None, None


# Find Tcl stubs library
tcl_inc, tcl_stub = _find_tcl_stubs()

if tcl_inc:
    include_dirs.append(tcl_inc)

if tcl_stub:
    # Static stubs library — not affected by -undefined dynamic_lookup.
    extra_objects.append(tcl_stub)

extension = Extension(
    "_nbsterm",
    sources=["generated/extension.c"],
    extra_compile_args=extra_compile_args,
    include_dirs=include_dirs,
    extra_link_args=extra_link_args,
    extra_objects=extra_objects,
)

setup(ext_modules=[extension])
