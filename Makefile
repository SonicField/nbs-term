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

# Flags
PYTHON_CFLAGS := $(shell $(PYTHON)-config --cflags)
PYTHON_LDFLAGS := $(shell $(PYTHON)-config --ldflags --embed 2>/dev/null || $(PYTHON)-config --ldflags)
CFLAGS := -std=c11 -Wall -Wextra -Werror -Wno-unused-function -fPIC
LDFLAGS := -shared -ltcl8.6

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

.PHONY: all clean test test-asan test-ubsan regenerate verify-regenerate phc

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
$(BUILDDIR)/extension.c: $(SRCDIR)/extension.phc $(SRCDIR)/sgr.phc $(SRCDIR)/screen.phc $(SRCDIR)/vt_parser.phc $(SRCDIR)/input.phc $(SRCDIR)/render.phc | $(BUILDDIR)
	$(CC) $(CFLAGS) $(PYTHON_CFLAGS) -I$(SRCDIR) -x c -E $< | $(PHC) > $@

$(BUILDDIR)/extension.o: $(BUILDDIR)/extension.c
	$(CC) $(CFLAGS) $(PYTHON_CFLAGS) -c $< -o $@

# --- Shared library ---
$(EXTENSION_SO): $(BUILDDIR)/extension.o
	$(CC) $(LDFLAGS) $< -o $@

# --- Test targets ---
# Tests include .phc source files directly, so they go through the phc pipeline.
# Uses test_framework.h from phc tests directory.
TEST_INCLUDES := -I$(SRCDIR) -I$(PHC_DIR)/tests

$(BUILDDIR)/test_parser: $(TESTDIR)/test_parser.c $(SRCDIR)/sgr.phc $(SRCDIR)/screen.phc $(SRCDIR)/vt_parser.phc $(SRCDIR)/input.phc | $(BUILDDIR)
	$(CC) $(CFLAGS) $(TEST_INCLUDES) -x c -E $(TESTDIR)/test_parser.c | $(PHC) | $(CC) $(CFLAGS) $(TEST_INCLUDES) -x c - -o $@

$(BUILDDIR)/test_screen: $(TESTDIR)/test_screen.c $(SRCDIR)/sgr.phc $(SRCDIR)/screen.phc | $(BUILDDIR)
	$(CC) $(CFLAGS) $(TEST_INCLUDES) -x c -E $(TESTDIR)/test_screen.c | $(PHC) | $(CC) $(CFLAGS) $(TEST_INCLUDES) -x c - -o $@

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
		echo '#include <tcl.h>'; \
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

# Build phc from submodule (if not already built)
phc: $(PHC_BIN)
$(PHC_BIN):
	@if [ ! -f $(PHC_DIR)/Makefile ]; then \
		echo "Error: phc submodule not initialised. Run: git submodule update --init"; \
		exit 1; \
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
		echo '#include <tcl.h>'; \
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

# Install: clean stale artifacts and install via pip
install: clean
	rm -f _nbsterm*.so
	pip install -e .
