# nbs-term Makefile
# Build pipeline: .phc -> cc -E (preprocess) -> phc (transform) -> cc (compile)
#
# Cross-file type sharing: files that define phc_descr types emit type manifests
# via --emit-types. Files that use phc_match on those types consume manifests
# via --type-manifest.

# phc is built with ASan; suppress leak detection for large files
PHC := ASAN_OPTIONS=detect_leaks=0 $(HOME)/local/phc/build/phc
CC ?= gcc
PYTHON := python3

# Flags
PYTHON_CFLAGS := $(shell $(PYTHON)-config --cflags)
PYTHON_LDFLAGS := $(shell $(PYTHON)-config --ldflags --embed 2>/dev/null || $(PYTHON)-config --ldflags)
CFLAGS := -std=c11 -Wall -Wextra -Werror -Wno-unused-function -fPIC
LDFLAGS := -shared

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

.PHONY: all clean test test-asan test-ubsan regenerate

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
TEST_INCLUDES := -I$(SRCDIR) -I$(HOME)/local/phc/tests

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
	$(PYTHON) $(TESTDIR)/test_ssh_integration.py || exit_code=1; \
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
regenerate: $(BUILDDIR)/extension.c
	cp $(BUILDDIR)/extension.c generated/extension.c

clean:
	rm -rf $(BUILDDIR) $(EXTENSION_SO)
