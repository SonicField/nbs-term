# nbs-term Makefile
# Build pipeline: .phc -> cc -E (preprocess) -> phc (transform) -> cc (compile)
#
# Cross-file type sharing: files that define phc_descr types emit type manifests
# via --emit-types. Files that use phc_match on those types consume manifests
# via --type-manifest.

# phc preprocessor — built from deps/phc submodule or override with PHC_DIR
PHC_DIR ?= deps/phc
# nbs-ssh for SSH integration tests — override with NBS_SSH_DIR if needed
NBS_SSH_DIR ?= $(wildcard ../nbs-ssh)
NBS_SSH_PYTHONPATH := $(if $(NBS_SSH_DIR),$(NBS_SSH_DIR)/src:$(wildcard $(NBS_SSH_DIR)/venv/lib/python*/site-packages):,)
PHC_BIN := $(PHC_DIR)/build/phc
PHC := ASAN_OPTIONS=detect_leaks=0 $(PHC_BIN)
CC ?= gcc
PYTHON := python3

# Vendored Tcl/Tk 8.6.15 — built from deps/{tcl,tk}/ source via tcl-tk target.
# No system libtcl/libtk linkage (alexie 2026-05-05 D-1777978221, D-1777978497).
UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S),Darwin)
TCL_LIB_EXT := dylib
else
TCL_LIB_EXT := so
endif
TCL_BUILD_DIR := deps/tcl-build
TCL_VENDOR_LIB := $(TCL_BUILD_DIR)/lib/libtcl8.6.$(TCL_LIB_EXT)
TK_VENDOR_LIB := $(TCL_BUILD_DIR)/lib/libtk8.6.$(TCL_LIB_EXT)
TCL_VENDOR_PREFIX := $(abspath $(TCL_BUILD_DIR))

# Flags
PYTHON_CFLAGS := $(shell $(PYTHON)-config --cflags)
PYTHON_LDFLAGS := $(shell $(PYTHON)-config --ldflags --embed 2>/dev/null || $(PYTHON)-config --ldflags)
CFLAGS := -std=c11 -Wall -Wextra -Werror -Wno-unused-function -fPIC
LDFLAGS := -shared -L$(TCL_BUILD_DIR)/lib -ltcl8.6 -Wl,-rpath,$(TCL_VENDOR_PREFIX)/lib

# Sanitizer flags (for testing)
ASAN_FLAGS := -fsanitize=address -fno-omit-frame-pointer
UBSAN_FLAGS := -fsanitize=undefined

# Directories
SRCDIR := src
BUILDDIR := build
TESTDIR := tests

# Generated headers
GEN_HEADERS := $(BUILDDIR)/sgr.h $(BUILDDIR)/screen.h $(BUILDDIR)/vt_parser.h $(BUILDDIR)/input.h $(BUILDDIR)/render.h

# Type manifests (from files that define phc_descr types)
SGR_TYPES := $(BUILDDIR)/sgr.phc-types
VT_TYPES := $(BUILDDIR)/vt_parser.phc-types
INPUT_TYPES := $(BUILDDIR)/input.phc-types

# Output
EXTENSION_SO := _nbsterm$(shell $(PYTHON) -c "import sysconfig; print(sysconfig.get_config_var('EXT_SUFFIX'))")

.PHONY: all clean test test-asan test-ubsan regenerate verify-regenerate phc verify-no-python-link verify-no-eval-objex verify-no-system-tcl-link verify-phc-invariants tcl-tk test_pty_burst test_pixel_to_cell test_extract_utf8 test_render_gamma

all: $(EXTENSION_SO)

# --- Generated headers for tests (direct mode, no preprocessing) ---
# Direct mode: phc transforms phc_descr/phc_match but does NOT expand #include.
# This means the generated headers can be included alongside normal system headers.
$(BUILDDIR)/sgr.h $(SGR_TYPES): $(SRCDIR)/sgr.phc | $(BUILDDIR)
	$(PHC) --emit-types=$(SGR_TYPES) < $< > $(BUILDDIR)/sgr.h

$(BUILDDIR)/screen.h: $(SRCDIR)/screen.phc $(BUILDDIR)/sgr.h | $(BUILDDIR)
	$(PHC) < $< > $@

$(BUILDDIR)/vt_parser.h $(VT_TYPES): $(SRCDIR)/vt_parser.phc $(BUILDDIR)/sgr.h $(BUILDDIR)/screen.h | $(BUILDDIR)
	$(PHC) --emit-types=$(VT_TYPES) < $< > $(BUILDDIR)/vt_parser.h

$(BUILDDIR)/input.h $(INPUT_TYPES): $(SRCDIR)/input.phc $(BUILDDIR)/sgr.h $(BUILDDIR)/screen.h | $(BUILDDIR)
	$(PHC) --emit-types=$(INPUT_TYPES) < $< > $(BUILDDIR)/input.h

$(BUILDDIR)/render.h: $(SRCDIR)/render.phc $(BUILDDIR)/sgr.h $(BUILDDIR)/screen.h $(SGR_TYPES) | $(BUILDDIR)
	$(PHC) --type-manifest=$(SGR_TYPES) < $< > $@

# --- Step 6: extension.phc (single translation unit) ---
# extension.phc #includes all .phc sources directly.
# Preprocessed as one unit so phc sees all phc_descr types.
$(BUILDDIR)/extension.c: $(SRCDIR)/extension.phc $(SRCDIR)/sgr.phc $(SRCDIR)/screen.phc $(SRCDIR)/vt_parser.phc $(SRCDIR)/input.phc $(SRCDIR)/render.phc $(TCL_VENDOR_LIB) | $(BUILDDIR)
	$(CC) $(CFLAGS) $(PYTHON_CFLAGS) -I$(TCL_BUILD_DIR)/include -I$(SRCDIR) -x c -E $< | $(PHC) > $@

$(BUILDDIR)/extension.o: $(BUILDDIR)/extension.c
	$(CC) $(CFLAGS) $(PYTHON_CFLAGS) -I$(TCL_BUILD_DIR)/include -c $< -o $@

# --- Shared library ---
$(EXTENSION_SO): $(BUILDDIR)/extension.o $(TK_VENDOR_LIB)
	$(CC) $(LDFLAGS) $< -o $@

# --- P1 calibration: standalone phc binary, no Python ---
# Tcl/Tk C-API hello-world. Builds a native executable directly from .phc;
# zero Python linkage. Bar: see src/p1_hello.phc header.
#
# Tcl/Tk linkage: vendored deps/tcl-build (built via tcl-tk target). Override
# TCLTK_CFLAGS / TCLTK_LIBS only for diagnostic builds — production builds
# must link against the vendored prefix per pure-phc doctrine.
TCLTK_CFLAGS ?= -I$(TCL_BUILD_DIR)/include
TCLTK_LIBS ?= -L$(TCL_BUILD_DIR)/lib -ltk8.6 -ltcl8.6 -Wl,-rpath,$(TCL_VENDOR_PREFIX)/lib
P1_CFLAGS := -std=c11 -Wall -Wextra -Werror -Wno-unused-function

# --- Vendored Tcl/Tk build (deps/tcl-build) ---
# In-tree configure+make+install. Source under deps/{tcl,tk}/ stays pristine
# vs upstream tarball (8.6.15); configure-generated artifacts are gitignored.
# JOBS: parallelism for the inner Tcl/Tk make. Defaults to nproc on
# Linux, sysctl on Mac, 4 elsewhere. Override with `make JOBS=N tcl-tk`.
# Tcl 8.6 + Tk 8.6 Makefiles are autoconf-generated and parallel-safe
# (theologian 13:59:17). Mac script already uses `make -j`; Win nmake
# is serial (alexie-greenlit-only per supervisor 14:10:53).
JOBS ?= $(shell nproc 2>/dev/null || sysctl -n hw.ncpu 2>/dev/null || echo 4)

$(TCL_VENDOR_LIB):
	@echo "Building vendored Tcl 8.6.15 -> $(TCL_BUILD_DIR) (jobs=$(JOBS)) ..."
	cd deps/tcl/unix && ./configure --prefix=$(TCL_VENDOR_PREFIX) --enable-shared --enable-threads
	$(MAKE) -j$(JOBS) -C deps/tcl/unix
	$(MAKE) -C deps/tcl/unix install

$(TK_VENDOR_LIB): $(TCL_VENDOR_LIB)
	@echo "Building vendored Tk 8.6.15 -> $(TCL_BUILD_DIR) (jobs=$(JOBS)) ..."
	cd deps/tk/unix && ./configure --prefix=$(TCL_VENDOR_PREFIX) --enable-shared --enable-threads $(if $(filter Darwin,$(UNAME_S)),--enable-aqua,) --with-tcl=$(abspath deps/tcl/unix)
	$(MAKE) -j$(JOBS) -C deps/tk/unix
	$(MAKE) -C deps/tk/unix install

tcl-tk: $(TK_VENDOR_LIB)

$(BUILDDIR)/p1_hello.c: $(SRCDIR)/p1_hello.phc $(TCL_VENDOR_LIB) | $(BUILDDIR)
	$(CC) $(P1_CFLAGS) $(TCLTK_CFLAGS) -I$(SRCDIR) -x c -E $< | $(PHC) > $@

$(BUILDDIR)/p1_hello: $(BUILDDIR)/p1_hello.c $(TK_VENDOR_LIB)
	$(CC) $(P1_CFLAGS) $(TCLTK_CFLAGS) $< $(TCLTK_LIBS) -o $@

p1_hello: $(BUILDDIR)/p1_hello

$(BUILDDIR)/p1_5_notebook.c: $(SRCDIR)/p1_5_notebook.phc $(TCL_VENDOR_LIB) | $(BUILDDIR)
	$(CC) $(P1_CFLAGS) $(TCLTK_CFLAGS) -I$(SRCDIR) -x c -E $< | $(PHC) > $@

$(BUILDDIR)/p1_5_notebook: $(BUILDDIR)/p1_5_notebook.c $(TK_VENDOR_LIB)
	$(CC) $(P1_CFLAGS) $(TCLTK_CFLAGS) $< $(TCLTK_LIBS) -o $@

p1_5_notebook: $(BUILDDIR)/p1_5_notebook

# P2: standalone phc TerminalWidget renderer (includes vt_parser+screen+sgr)
$(BUILDDIR)/p2_render.c: $(SRCDIR)/p2_render.phc $(SRCDIR)/vt_parser.phc $(SRCDIR)/screen.phc $(SRCDIR)/sgr.phc $(TCL_VENDOR_LIB) | $(BUILDDIR)
	$(CC) $(P1_CFLAGS) $(TCLTK_CFLAGS) -I$(SRCDIR) -x c -E $< | $(PHC) > $@

$(BUILDDIR)/p2_render: $(BUILDDIR)/p2_render.c $(TK_VENDOR_LIB)
	$(CC) $(P1_CFLAGS) $(TCLTK_CFLAGS) $< $(TCLTK_LIBS) -o $@

p2_render: $(BUILDDIR)/p2_render

# P3+P4: PTY-driven live terminal. Cross-platform via pty.phc (forkpty on
# POSIX, ConPTY on Win32). -lutil for forkpty (Linux); macOS pulls forkpty
# from libSystem, the -lutil is a harmless no-op there.
$(BUILDDIR)/p3_pty.c: $(SRCDIR)/p3_pty.phc $(SRCDIR)/pty.phc $(SRCDIR)/vt_parser.phc $(SRCDIR)/screen.phc $(SRCDIR)/sgr.phc $(TCL_VENDOR_LIB) | $(BUILDDIR)
	$(CC) $(P1_CFLAGS) $(TCLTK_CFLAGS) -I$(SRCDIR) -x c -E $< | $(PHC) > $@

$(BUILDDIR)/p3_pty: $(BUILDDIR)/p3_pty.c $(TK_VENDOR_LIB)
	$(CC) $(P1_CFLAGS) $(TCLTK_CFLAGS) $< $(TCLTK_LIBS) -lutil -lm -o $@

p3_pty: $(BUILDDIR)/p3_pty

# --- Test targets ---
# Tests include .phc source files directly, so they go through the phc pipeline.
# Uses test_framework.h from phc tests directory.
TEST_INCLUDES := -I$(SRCDIR) -I$(PHC_DIR)/tests

$(BUILDDIR)/test_parser: $(TESTDIR)/test_parser.c $(SRCDIR)/sgr.phc $(SRCDIR)/screen.phc $(SRCDIR)/vt_parser.phc $(SRCDIR)/input.phc | $(BUILDDIR)
	$(CC) $(CFLAGS) $(TEST_INCLUDES) -x c -E $(TESTDIR)/test_parser.c | $(PHC) | $(CC) $(CFLAGS) $(TEST_INCLUDES) -x c - -o $@

$(BUILDDIR)/test_screen: $(TESTDIR)/test_screen.c $(SRCDIR)/sgr.phc $(SRCDIR)/screen.phc | $(BUILDDIR)
	$(CC) $(CFLAGS) $(TEST_INCLUDES) -x c -E $(TESTDIR)/test_screen.c | $(PHC) | $(CC) $(CFLAGS) $(TEST_INCLUDES) -x c - -o $@

# test_pty_burst — programmatic byte-accounting for pty.phc (testkeeper
# deferred spec D-1777640886). Validates POSIX read-pump-under-load and
# Win32 ring backpressure (c8d5378 fix #4) without Tk/render in the loop.
# Producer is direct-exec self-spawn (--emit mode) — no shell wrapper, so
# test isolates the PTY layer from interpreter cold-start (post-(iii)
# canonicalisation, 1f2e33a confirmed powershell-startup as Win bottleneck).
# Same build shape as p3_pty (Tcl link, vendored Tcl/Tk, -lutil for forkpty).
$(BUILDDIR)/test_pty_burst.c: $(TESTDIR)/test_pty_burst.phc $(SRCDIR)/pty.phc $(TCL_VENDOR_LIB) | $(BUILDDIR)
	$(CC) $(P1_CFLAGS) $(TCLTK_CFLAGS) -I$(SRCDIR) -x c -E $< | $(PHC) > $@

$(BUILDDIR)/test_pty_burst: $(BUILDDIR)/test_pty_burst.c $(TK_VENDOR_LIB)
	$(CC) $(P1_CFLAGS) $(TCLTK_CFLAGS) $< $(TCLTK_LIBS) -lutil -o $@

test_pty_burst: $(BUILDDIR)/test_pty_burst

# test_pixel_to_cell — selection-arithmetic regression anchor for F1
# (testkeeper shim per pythia #76 + supervisor 17:48:58). Pure-spec:
# copies pixel_to_cell algorithm from p3_pty.phc:388 and tests
# (px,py,origin,cell,grid) sweeps. Headless; no Tcl/Tk/PTY link.
# Discharges 'wrong cells' attribution to render-side when this PASSes.
$(BUILDDIR)/test_pixel_to_cell.c: $(TESTDIR)/test_pixel_to_cell.phc | $(BUILDDIR)
	$(CC) $(P1_CFLAGS) -I$(SRCDIR) -x c -E $< | $(PHC) > $@

$(BUILDDIR)/test_pixel_to_cell: $(BUILDDIR)/test_pixel_to_cell.c
	$(CC) $(P1_CFLAGS) $< -o $@

test_pixel_to_cell: $(BUILDDIR)/test_pixel_to_cell

# test_extract_utf8 — F2 byte-extract regression anchor (testkeeper
# shim per pythia #77 + supervisor 18:26:48). Pure-spec: copies
# utf8_emit + row_sel_range + NbsCopy walk from p3_pty.phc into
# parameterised locals; tests utf8 1-4 byte + row_sel sentinels +
# multi-row newline + wide_cont skip + truncation. Headless.
$(BUILDDIR)/test_extract_utf8.c: $(TESTDIR)/test_extract_utf8.phc | $(BUILDDIR)
	$(CC) $(P1_CFLAGS) -I$(SRCDIR) -x c -E $< | $(PHC) > $@

$(BUILDDIR)/test_extract_utf8: $(BUILDDIR)/test_extract_utf8.c
	$(CC) $(P1_CFLAGS) $< -o $@

test_extract_utf8: $(BUILDDIR)/test_extract_utf8

# test_render_gamma — H gamma + dim regression anchor (generalist shim
# per supervisor 2026-05-13 09:47:45 + alexie 09:46:53 automated-suite
# directive). Direct-include of src/render_color.phc (pure-C header,
# extracted per theologian 14:43:30 specifically for cross-TU sharing).
# Headless; libm only for pow().
$(BUILDDIR)/test_render_gamma.c: $(TESTDIR)/test_render_gamma.phc $(SRCDIR)/render_color.phc | $(BUILDDIR)
	$(CC) $(P1_CFLAGS) -I$(SRCDIR) -x c -E $< | $(PHC) > $@

$(BUILDDIR)/test_render_gamma: $(BUILDDIR)/test_render_gamma.c
	$(CC) $(P1_CFLAGS) $< -lm -o $@

test_render_gamma: $(BUILDDIR)/test_render_gamma

test: $(BUILDDIR)/test_parser $(BUILDDIR)/test_screen $(EXTENSION_SO)
	@exit_code=0; \
	./$(BUILDDIR)/test_parser || exit_code=1; \
	echo ""; \
	./$(BUILDDIR)/test_screen || exit_code=1; \
	echo ""; \
	$(PYTHON) $(TESTDIR)/test_integration.py || exit_code=1; \
	echo ""; \
	$(PYTHON) $(TESTDIR)/test_gui_logic.py || exit_code=1; \
	echo ""; \
	$(PYTHON) $(TESTDIR)/test_config.py || exit_code=1; \
	echo ""; \
	$(PYTHON) $(TESTDIR)/test_color_functions.py || exit_code=1; \
	echo ""; \
	PYTHONPATH=$(NBS_SSH_PYTHONPATH)$$PYTHONPATH $(PYTHON) $(TESTDIR)/test_ssh_integration.py || exit_code=1; \
	echo ""; \
	$(PYTHON) $(TESTDIR)/test_orchestration.py || exit_code=1; \
	echo ""; \
	if [ $$exit_code -eq 0 ]; then echo "Gate: OPEN"; else echo "Gate: BLOCKED"; fi; \
	exit $$exit_code

# --- pure-phc invariant guards (testkeeper, per pythia #36) ---
# Static-source assertions enforcing the B-shape doctrine on pure-phc-master.
# Per testkeeper 2026-05-01 12:26:44 ack of pythia D-1777639528 + D-1777639551.

# (1) No Python linkage on any phc binary. ldd must show zero python entries.
PHC_BINARIES := $(BUILDDIR)/p1_hello $(BUILDDIR)/p1_5_notebook $(BUILDDIR)/p2_render $(BUILDDIR)/p3_pty

verify-no-python-link: $(PHC_BINARIES)
	@fail=0; \
	for b in $(PHC_BINARIES); do \
	  if [ -x "$$b" ]; then \
	    if ldd "$$b" 2>/dev/null | grep -qi python; then \
	      echo "FAIL: $$b links Python (B-shape requires zero Python linkage at runtime)"; \
	      ldd "$$b" | grep -i python; \
	      fail=1; \
	    fi; \
	  else \
	    echo "SKIP: $$b not built"; \
	  fi; \
	done; \
	if [ $$fail -eq 0 ]; then echo "PASS: phc binaries have zero Python linkage"; else exit 1; fi

# (2) No Tcl_EvalObjEx in production .phc. Use Tcl_EvalObjv + Tcl_NewStringObj
# per theologian 2026-05-01 12:09:51 + refinement 12:27:27 (ban EvalObjEx
# entirely, not the printf+EvalObjEx pair). Allowlist: P1/P1.5 calibration
# scaffolds (won't ship per theologian 12:11:13 throwaway disposition).
EVAL_OBJEX_ALLOWLIST := p1_hello\.phc|p1_5_notebook\.phc

verify-no-eval-objex:
	@hits=$$(grep -l 'Tcl_EvalObjEx' $(SRCDIR)/*.phc 2>/dev/null | grep -vE '$(EVAL_OBJEX_ALLOWLIST)' || true); \
	if [ -n "$$hits" ]; then \
	  echo "FAIL: Tcl_EvalObjEx found in production .phc (allowlist: P1/P1.5 scaffolds only)"; \
	  echo "$$hits" | while read f; do grep -nH 'Tcl_EvalObjEx' "$$f"; done; \
	  echo "Use Tcl_EvalObjv + Tcl_NewStringObj-constructed argv instead."; \
	  exit 1; \
	fi; \
	echo "PASS: no Tcl_EvalObjEx in production .phc"

# (3) No system libtcl/libtk linkage on phc binaries. Tcl/Tk must come from
# the vendored build under deps/tcl-build/lib (alexie 2026-05-05
# D-1777978221, D-1777978497; pure-source-code-dep doctrine). Mirrors
# verify-no-python-link scope (phc binaries only; EXTENSION_SO legacy
# build also links vendored via LDFLAGS, but is not asserted here).
verify-no-system-tcl-link: $(PHC_BINARIES)
	@fail=0; \
	if [ "$(UNAME_S)" = "Darwin" ]; then \
	  inspect="otool -L"; \
	else \
	  inspect="ldd"; \
	fi; \
	for b in $(PHC_BINARIES); do \
	  if [ -e "$$b" ]; then \
	    if $$inspect "$$b" 2>/dev/null | grep -E '/(usr|opt|System)/.*libt(cl|k)' >/dev/null; then \
	      echo "FAIL: $$b links system Tcl/Tk (must use vendored deps/tcl-build)"; \
	      $$inspect "$$b" | grep -E 'libt(cl|k)'; \
	      fail=1; \
	    fi; \
	    if ! $$inspect "$$b" 2>/dev/null | grep -F "$(TCL_VENDOR_PREFIX)/lib/libtcl8.6" >/dev/null; then \
	      echo "FAIL: $$b does not link vendored libtcl8.6 from $(TCL_VENDOR_PREFIX)/lib"; \
	      $$inspect "$$b" | grep -E 'libt(cl|k)'; \
	      fail=1; \
	    fi; \
	  else \
	    echo "SKIP: $$b not built"; \
	  fi; \
	done; \
	if [ $$fail -eq 0 ]; then echo "PASS: phc binaries link vendored Tcl/Tk only"; else exit 1; fi

# Roll-up: run all invariant guards.
verify-phc-invariants: verify-no-python-link verify-no-eval-objex verify-no-system-tcl-link

test-asan: CC := clang
test-asan: CFLAGS += $(ASAN_FLAGS)
test-asan: clean test

test-ubsan: CC := clang
test-ubsan: CFLAGS += $(UBSAN_FLAGS)
test-ubsan: clean test

$(BUILDDIR):
	mkdir -p $(BUILDDIR)

# Regenerate the committed generated/extension.c from .phc sources (requires phc)
# Produces portable C: system #includes at top, phc-transformed source below.
# No embedded system headers — compiles on any platform with Python + C11.
regenerate:
	@echo "Regenerating generated/extension.c from src/*.phc..."
	@{ \
		echo '/* Generated by phc from src .phc files -- do not edit */'; \
		echo ''; \
		echo '#include <Python.h>'; \
		echo '#include <stdlib.h>'; \
		echo '#include <string.h>'; \
		echo '#include <stdint.h>'; \
		echo '#include <stdio.h>'; \
		echo '#include <assert.h>'; \
		echo '#define USE_TCL_STUBS'; \
		echo '#include <tcl.h>'; \
		echo '#if !defined(__APPLE__)'; \
		echo '#undef Tcl_InitStubs'; \
		echo '#endif'; \
		echo ''; \
		echo '/* phc_assert macros — trust-level assertions */'; \
		echo '#define phc_require(expr, msg) do { if (!(expr)) { \'; \
		echo '    fprintf(stderr, "REQUIRE FAILED %s:%d: %s\\n", __FILE__, __LINE__, msg); \'; \
		echo '    abort(); }} while(0)'; \
		echo '#ifndef PHC_STRIP_CHECK'; \
		echo '#define phc_check(expr, msg) do { if (!(expr)) { \'; \
		echo '    fprintf(stderr, "CHECK FAILED %s:%d: %s\\n", __FILE__, __LINE__, msg); \'; \
		echo '    abort(); }} while(0)'; \
		echo '#else'; \
		echo '#define phc_check(expr, msg) ((void)0)'; \
		echo '#endif'; \
		echo '#ifndef PHC_STRIP_INVARIANT'; \
		echo '#define phc_invariant(expr, msg) do { if (!(expr)) { \'; \
		echo '    fprintf(stderr, "INVARIANT FAILED %s:%d: %s\\n", __FILE__, __LINE__, msg); \'; \
		echo '    abort(); }} while(0)'; \
		echo '#else'; \
		echo '#define phc_invariant(expr, msg) ((void)0)'; \
		echo '#endif'; \
		echo ''; \
		cat $(SRCDIR)/sgr.phc $(SRCDIR)/screen.phc $(SRCDIR)/vt_parser.phc \
			$(SRCDIR)/input.phc $(SRCDIR)/render.phc \
			$(SRCDIR)/color_utils.phc $(SRCDIR)/config_structs.phc \
			$(SRCDIR)/tk_render.phc $(SRCDIR)/selection.phc $(SRCDIR)/extension.phc | \
		grep -v '^\s*#include' | \
		grep -v '^\s*#ifndef NBSTERM_' | \
		grep -v '^\s*#define NBSTERM_' | \
		grep -v '^\s*#endif.*/\*.*NBSTERM_' | \
		$(PHC); \
	} > generated/extension.c
	@echo "Done ($(shell wc -l < generated/extension.c) lines)"

# Build phc from submodule (if not already built). Auto-init the submodule
# so a fresh clone + make works without a manual `git submodule update --init`
# step (per supervisor 2026-05-05 11:55:33; matches windows-setup-phc.ps1 +
# mac-setup-phc.sh auto-init pattern).
#
# Recovery: if $(PHC_DIR) exists but is non-empty without the submodule's
# Makefile inside (e.g. a prior failed run touched $(PHC_DIR)/build), git
# submodule update refuses to clone into a non-empty path. Deinit+rm+init
# is the canonical recovery (per supervisor 2026-05-05 12:15:05; mirrors
# 9dfcf83 Win/Mac fix).
phc: $(PHC_BIN)
$(PHC_BIN):
	@if [ ! -f $(PHC_DIR)/Makefile ]; then \
		if [ -d $(PHC_DIR) ] && [ -n "$$(ls -A $(PHC_DIR) 2>/dev/null)" ]; then \
			echo "Cleaning stale $(PHC_DIR) before submodule init..."; \
			git submodule deinit -f $(PHC_DIR) 2>/dev/null || true; \
			rm -rf $(PHC_DIR); \
		fi; \
		echo "Initializing phc submodule ($(PHC_DIR))..."; \
		git submodule update --init $(PHC_DIR) || { echo "ERROR: git submodule init failed for $(PHC_DIR)"; exit 1; }; \
	fi
	$(MAKE) -C $(PHC_DIR)

# Verify generated/extension.c matches current .phc sources
verify-regenerate: $(PHC_BIN)
	@echo "Verifying generated/extension.c is up to date..."
	@{ \
		echo '/* Generated by phc from src .phc files -- do not edit */'; \
		echo ''; \
		echo '#include <Python.h>'; \
		echo '#include <stdlib.h>'; \
		echo '#include <string.h>'; \
		echo '#include <stdint.h>'; \
		echo '#include <stdio.h>'; \
		echo '#include <assert.h>'; \
		echo '#define USE_TCL_STUBS'; \
		echo '#include <tcl.h>'; \
		echo '#if !defined(__APPLE__)'; \
		echo '#undef Tcl_InitStubs'; \
		echo '#endif'; \
		echo ''; \
		echo '/* phc_assert macros — trust-level assertions */'; \
		echo '#define phc_require(expr, msg) do { if (!(expr)) { \'; \
		echo '    fprintf(stderr, "REQUIRE FAILED %s:%d: %s\\n", __FILE__, __LINE__, msg); \'; \
		echo '    abort(); }} while(0)'; \
		echo '#ifndef PHC_STRIP_CHECK'; \
		echo '#define phc_check(expr, msg) do { if (!(expr)) { \'; \
		echo '    fprintf(stderr, "CHECK FAILED %s:%d: %s\\n", __FILE__, __LINE__, msg); \'; \
		echo '    abort(); }} while(0)'; \
		echo '#else'; \
		echo '#define phc_check(expr, msg) ((void)0)'; \
		echo '#endif'; \
		echo '#ifndef PHC_STRIP_INVARIANT'; \
		echo '#define phc_invariant(expr, msg) do { if (!(expr)) { \'; \
		echo '    fprintf(stderr, "INVARIANT FAILED %s:%d: %s\\n", __FILE__, __LINE__, msg); \'; \
		echo '    abort(); }} while(0)'; \
		echo '#else'; \
		echo '#define phc_invariant(expr, msg) ((void)0)'; \
		echo '#endif'; \
		echo ''; \
		cat $(SRCDIR)/sgr.phc $(SRCDIR)/screen.phc $(SRCDIR)/vt_parser.phc \
			$(SRCDIR)/input.phc $(SRCDIR)/render.phc \
			$(SRCDIR)/color_utils.phc $(SRCDIR)/config_structs.phc \
			$(SRCDIR)/tk_render.phc $(SRCDIR)/selection.phc $(SRCDIR)/extension.phc | \
		grep -v '^\s*#include' | \
		grep -v '^\s*#ifndef NBSTERM_' | \
		grep -v '^\s*#define NBSTERM_' | \
		grep -v '^\s*#endif.*/\*.*NBSTERM_' | \
		$(PHC); \
	} > $(BUILDDIR)/extension_verify.c
	@diff -q generated/extension.c $(BUILDDIR)/extension_verify.c > /dev/null 2>&1 \
		&& echo "OK — generated/extension.c is up to date" \
		|| (echo "STALE — generated/extension.c differs from .phc sources. Run: make regenerate"; exit 1)

clean:
	rm -rf $(BUILDDIR) $(EXTENSION_SO)

# Install: clean stale artifacts, purge pip cache, and install via pip
install: clean
	rm -f _nbsterm*.so
	rm -rf build/
	pip cache remove nbs_term 2>/dev/null || true
	pip install -e .
