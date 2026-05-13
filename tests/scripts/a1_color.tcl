# tests/scripts/a1_color.tcl — A1 color renderer per-span verification
#
# Bucket B per-surface test for A1 (commit 439c7cc + c776668 — port of
# legacy extension.phc:982-1107 span-split renderer). Discriminator:
# if alexie reports 'colours wrong / row-uniform' AND this passes, bug
# is in g_config palette load OR cell color storage upstream of
# render_screen; if this fails, regression is inside flush_span /
# cells_same_span / per-span fg/bg/font emission.
#
# Approach: feed three SGR sequences in one row (red ASCII, default,
# green ASCII), render synchronously, harness dumps the canvas. A
# correctly-ported renderer emits SEPARATE text items per span, each
# with its own -fill colour matching the SGR code. A regressed renderer
# would emit one row-uniform item with column-0's fg.
#
# Falsifier: golden compare exits non-zero if the dump differs from
# tests/goldens/a1_color.{linux,mac,win}.golden.txt.

# \x1b[31m = ANSI red fg; \x1b[32m = ANSI green fg; \x1b[m = SGR reset.
# Three spans on row 0: "RED" (fg=ANSI 1), " plain " (fg=default),
# "GREEN" (fg=ANSI 2). ASCII only — Unicode + wide-char are separate
# discriminators (would belong in a future a1_unicode.tcl).
nbs_test_feed_bytes "\x1b\[31mRED\x1b\[m plain \x1b\[32mGREEN\x1b\[m"
nbs_test_render
nbs_test_complete
