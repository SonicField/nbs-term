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
libraries = []
extra_link_args = []


def _find_tcl_lib(lib_dir):
    """Find the Tcl library name in a directory (handles 8.6, 9.0, etc)."""
    for pattern in ["libtcl[0-9].[0-9]*", "libtcl[0-9][0-9]*"]:
        matches = glob.glob(os.path.join(lib_dir, pattern + ".*"))
        if matches:
            # Extract library name: libtcl9.0.dylib -> tcl9.0
            basename = os.path.basename(matches[0])
            # Strip lib prefix and extension
            name = basename.split(".dylib")[0].split(".so")[0].split(".a")[0]
            if name.startswith("lib"):
                name = name[3:]
            return name
    return None


# Platform-specific Tcl linkage (required for render pipeline)
if platform.system() == "Darwin":
    # macOS: use framework linkage (works with both system Tcl and Homebrew).
    # Add Homebrew include path if available for headers.
    try:
        tcl_prefix = subprocess.check_output(
            ["brew", "--prefix", "tcl-tk"], text=True
        ).strip()
        include_dirs.append(f"{tcl_prefix}/include")
    except (subprocess.CalledProcessError, FileNotFoundError):
        pass
    extra_link_args.extend(["-framework", "Tcl"])
else:
    # Linux: auto-detect Tcl library version, fall back to tcl8.6
    tcl_lib = _find_tcl_lib("/usr/lib") or _find_tcl_lib("/usr/lib/x86_64-linux-gnu") or "tcl8.6"
    libraries.append(tcl_lib)

extension = Extension(
    "_nbsterm",
    sources=["generated/extension.c"],
    extra_compile_args=extra_compile_args,
    include_dirs=include_dirs,
    libraries=libraries,
    extra_link_args=extra_link_args,
)

setup(ext_modules=[extension])
