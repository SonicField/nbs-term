"""Build configuration for the _nbsterm C extension.

Uses Tcl stubs on all platforms (like CPython's _tkinter). TclFreeObj
is internal to Tcl 9 and only accessible through the stubs table.
On Mac, Homebrew's Tcl headers are detected via brew --prefix tcl-tk.
"""
import glob
import os
import platform
import re
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


def _find_tcl():
    """Find Tcl headers and stubs library for the current platform.

    Returns (include_dir, stub_lib_path) or (None, None).
    """
    if platform.system() == "Darwin":
        # macOS: Homebrew Tcl headers + libtclstub + link against libtcl.
        # Same approach as CPython's _tkinter. No custom stubs code.
        # TCL_PREFIX env var set by mac-setup.sh (survives pip build isolation).
        try:
            prefix = os.environ.get("TCL_PREFIX") or subprocess.check_output(
                ["brew", "--prefix", "tcl-tk"],
                stderr=subprocess.DEVNULL
            ).decode().strip()
            lib_dir = os.path.join(prefix, "lib")
            # Homebrew tcl-tk puts headers in include/tcl-tk/, not include/
            for subdir in ["include/tcl-tk", "include"]:
                inc = os.path.join(prefix, subdir)
                if os.path.isfile(os.path.join(inc, "tcl.h")):
                    break
            else:
                return None, None
            # Find libtclstub*.a (provides tclStubsPtr + Tcl_InitStubs)
            stubs = glob.glob(os.path.join(lib_dir, "libtclstub*.a"))
            stub = stubs[0] if stubs else None
            # Link against libtcl so Tcl_PkgRequireEx resolves
            for f in sorted(os.listdir(lib_dir), reverse=True):
                m = re.match(r"libtcl(\d+\.\d+)\.dylib$", f)
                if m:
                    extra_link_args.extend([f"-L{lib_dir}", f"-ltcl{m.group(1)}"])
                    break
            return inc, stub
        except (subprocess.CalledProcessError, FileNotFoundError):
            pass
        return None, None

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
        setup_dir = os.path.dirname(os.path.abspath(__file__))
        tcl_win = os.path.join(setup_dir, "deps", "tcl-win")
        inc = os.path.join(tcl_win, "include")
        if os.path.isfile(os.path.join(inc, "tcl.h")):
            return inc, None
        return None, None

    return None, None


# Find Tcl
tcl_inc, tcl_stub = _find_tcl()

print(f"Tcl stubs: inc={tcl_inc}, stub={tcl_stub}")
if tcl_inc:
    include_dirs.append(tcl_inc)

if tcl_stub:
    extra_objects.append(tcl_stub)

sources = ["generated/extension.c"]
if platform.system() == "Windows":
    # Windows: compile our GetProcAddress-based stubs bootstrap.
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
