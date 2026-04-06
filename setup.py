"""Build configuration for the _nbsterm C extension."""
from setuptools import setup, Extension
import subprocess
import os

def get_python_flags():
    """Get Python include flags."""
    cflags = subprocess.check_output(
        ["python3-config", "--cflags"], text=True
    ).strip().split()
    return cflags

# The extension is built from the pre-generated build/extension.c
# which was produced by the phc pipeline from the .phc source files.
# Users do not need phc installed.
extension = Extension(
    "_nbsterm",
    sources=["generated/extension.c"],
    extra_compile_args=[
        "-std=c11", "-Wall", "-Wextra",
        "-Wno-unused-function",
        "-Wno-missing-field-initializers",
    ],
)

setup(ext_modules=[extension])
