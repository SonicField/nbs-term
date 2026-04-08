"""Build configuration for the _nbsterm C extension."""
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

# Platform-specific Tcl linkage (required for render pipeline)
if platform.system() == "Darwin":
    # macOS: use Tcl framework. Try Homebrew first, then system framework.
    try:
        tcl_prefix = subprocess.check_output(
            ["brew", "--prefix", "tcl-tk"], text=True
        ).strip()
        include_dirs.append(f"{tcl_prefix}/include")
        extra_link_args.extend([f"-L{tcl_prefix}/lib", "-ltcl8.6"])
    except (subprocess.CalledProcessError, FileNotFoundError):
        # Fall back to system Tcl framework
        extra_link_args.extend(["-framework", "Tcl"])
else:
    # Linux: link against system Tcl
    libraries.append("tcl8.6")

extension = Extension(
    "_nbsterm",
    sources=["generated/extension.c"],
    extra_compile_args=extra_compile_args,
    include_dirs=include_dirs,
    libraries=libraries,
    extra_link_args=extra_link_args,
)

setup(ext_modules=[extension])
