"""Build configuration for the _nbsterm C extension."""
import glob
import os
import platform
import subprocess
from setuptools import setup, Extension

# The extension is built from the pre-generated build/extension.c
# which was produced by the phc pipeline from the .phc source files.
# Users do not need phc installed.

extra_compile_args = [
    "-std=c11", "-Wall", "-Wextra",
    "-Wno-unused-function",
    "-Wno-missing-field-initializers",
]
include_dirs = []
extra_link_args = []
extra_objects = []  # for static libraries (libtclstub.a)


def _find_tcl_stubs():
    """Find Tcl stubs library and headers for the current platform.

    Tcl stubs lets us link a small static library (libtclstub.a) at build
    time and resolve all Tcl functions at runtime through the interpreter's
    own function table. This avoids version mismatches between the Tcl we
    link and the Tcl that _tkinter loaded.

    Returns (include_dir, stub_lib_path) or (None, None).
    """
    # macOS: Homebrew tcl-tk
    if platform.system() == "Darwin":
        try:
            tcl_prefix = subprocess.check_output(
                ["brew", "--prefix", "tcl-tk"], text=True
            ).strip()
            inc = os.path.join(tcl_prefix, "include")
            lib_dir = os.path.join(tcl_prefix, "lib")
            # Find libtclstub*.a
            stubs = glob.glob(os.path.join(lib_dir, "libtclstub*.a"))
            if stubs and os.path.isdir(inc):
                return inc, stubs[0]
        except (subprocess.CalledProcessError, FileNotFoundError):
            pass

    # Linux: system Tcl dev packages
    elif platform.system() == "Linux":
        # Common locations for Tcl headers and stubs
        for inc_path in ["/usr/include/tcl8.6", "/usr/include/tcl",
                         "/usr/include"]:
            if os.path.isfile(os.path.join(inc_path, "tcl.h")):
                # Find stubs library
                for lib_path in ["/usr/lib/x86_64-linux-gnu", "/usr/lib64",
                                 "/usr/lib"]:
                    stubs = glob.glob(os.path.join(lib_path, "libtclstub*.a"))
                    if stubs:
                        return inc_path, stubs[0]
                # Fallback: try -ltclstub8.6
                return inc_path, None
        # If no stubs found, try linking Tcl directly (fallback)
        return None, None

    # Windows: bundled with Python
    elif platform.system() == "Windows":
        try:
            import _tkinter
            import sys
            ver = _tkinter.TCL_VERSION.replace(".", "")
            dll_dir = os.path.join(sys.prefix, "DLLs")
            inc = os.path.join(sys.prefix, "include")
            stub = os.path.join(sys.prefix, "libs", f"tclstub{ver}.lib")
            if os.path.isfile(stub):
                return inc, stub
        except (ImportError, AttributeError):
            pass

    return None, None


# Find Tcl stubs library
tcl_inc, tcl_stub = _find_tcl_stubs()

if tcl_inc:
    include_dirs.append(tcl_inc)

if tcl_stub:
    # Link stubs library statically — not affected by -undefined dynamic_lookup.
    # All Tcl functions resolve at runtime through Tcl_InitStubs.
    extra_objects.append(tcl_stub)
    # On Linux, also link the real Tcl library (needed for Tcl_CreateInterp
    # which bootstraps the stubs table). On Mac, _tkinter already loaded it.
    if platform.system() == "Linux":
        extra_link_args.append("-ltcl8.6")
elif platform.system() == "Linux":
    # Linux fallback: link Tcl dynamically if no stubs library found.
    extra_link_args.append("-ltcl8.6")

extension = Extension(
    "_nbsterm",
    sources=["generated/extension.c"],
    extra_compile_args=extra_compile_args,
    include_dirs=include_dirs,
    extra_link_args=extra_link_args,
    extra_objects=extra_objects,
)

setup(ext_modules=[extension])
