"""Build configuration for the _nbsterm C extension."""
from setuptools import setup, Extension

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
