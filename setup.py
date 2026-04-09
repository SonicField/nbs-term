"""Build configuration for the _nbsterm C extension."""
import os
import platform
import re
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
library_dirs = []
libraries = []
extra_link_args = []


def _find_tcl_from_tkinter():
    """Find Tcl library path and name from Python's own _tkinter module.

    This is the most reliable method: we link the exact same Tcl that
    Python's _tkinter uses, avoiding version mismatches.

    Returns (lib_dir, lib_name) or (None, None).
    """
    try:
        import _tkinter
        tkinter_path = _tkinter.__file__
    except (ImportError, AttributeError):
        return None, None

    # On macOS, use otool -L to find linked Tcl library
    if platform.system() == "Darwin":
        try:
            output = subprocess.check_output(
                ["otool", "-L", tkinter_path], text=True
            )
            for line in output.splitlines():
                # Match lines like: /opt/homebrew/.../libtcl9.0.dylib
                m = re.search(r"(/\S+/lib(tcl[\d.]+)\.dylib)", line)
                if m:
                    full_path = m.group(1)
                    lib_name = m.group(2)
                    lib_dir = os.path.dirname(full_path)
                    return lib_dir, lib_name
        except (subprocess.CalledProcessError, FileNotFoundError):
            pass
    else:
        # On Linux, use ldd
        try:
            output = subprocess.check_output(
                ["ldd", tkinter_path], text=True
            )
            for line in output.splitlines():
                m = re.search(r"lib(tcl[\d.]+)\.so", line)
                if m:
                    lib_name = m.group(1)
                    # Extract path
                    path_m = re.search(r"=> (/\S+)", line)
                    if path_m:
                        lib_dir = os.path.dirname(path_m.group(1))
                        return lib_dir, lib_name
        except (subprocess.CalledProcessError, FileNotFoundError):
            pass

    return None, None


# Find Tcl from Python's _tkinter — the authoritative source.
tcl_lib_dir, tcl_lib_name = _find_tcl_from_tkinter()

if tcl_lib_dir and tcl_lib_name:
    # Use the exact Tcl library that _tkinter links.
    library_dirs.append(tcl_lib_dir)
    libraries.append(tcl_lib_name)
    # Add include dir (typically ../include relative to lib)
    tcl_include = os.path.join(os.path.dirname(tcl_lib_dir), "include")
    if os.path.isdir(tcl_include):
        include_dirs.append(tcl_include)
    # On macOS, add rpath for runtime resolution
    if platform.system() == "Darwin":
        extra_link_args.append(f"-Wl,-rpath,{tcl_lib_dir}")
elif platform.system() == "Darwin":
    # Fallback: system Tcl framework (may version-mismatch with _tkinter)
    extra_link_args.extend(["-framework", "Tcl"])
else:
    # Fallback: system Tcl on Linux
    libraries.append("tcl8.6")

extension = Extension(
    "_nbsterm",
    sources=["generated/extension.c"],
    extra_compile_args=extra_compile_args,
    include_dirs=include_dirs,
    library_dirs=library_dirs,
    libraries=libraries,
    extra_link_args=extra_link_args,
)

setup(ext_modules=[extension])
