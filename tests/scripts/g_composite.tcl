# tests/scripts/g_composite.tcl — G scrollback composite render
#
# Bucket B per-surface test for G (commit e45fbca — scrollback UI:
# composite render of scrollback ring + active screen via
# view_row_cells at p3_pty.phc:323-349 when term->scroll_offset > 0
# && !term->using_alt). Discriminator: if alexie reports 'scrollback
# missing / wrong content' AND this passes, bug is in scroll-trigger
# bindings (MouseWheel / Ctrl+Shift+Up) OR scrollback ring upstream
# (screen.phc Scrollback insert path); if this fails, regression is
# inside view_row_cells composite path OR nbs_set_scroll_offset
# bounds-clamp.
#
# Approach: feed 30 rows of distinct content (ROW00..ROW29) to fill
# the 24-row screen + push 6 rows into scrollback. Then nbs_scroll_lines
# 6 — top 6 visible rows should pull from scrollback ring (ROW00..ROW05);
# bottom 18 visible rows should pull from live screen (ROW06..ROW23).
# Regressed renderer would show only live rows (ROW06..ROW29) without
# scrollback compositing.

# Feed 30 numbered rows, each terminated by CR+LF.
for {set i 0} {$i < 30} {incr i} {
    nbs_test_feed_bytes [format "ROW%02d\r\n" $i]
}

# Scroll back 6 lines into history. After 30 rows of 'ROWxx\r\n' on
# a 24-row screen: each \n at the bottom row triggers screen.phc scroll
# which pushes top row to scrollback. Empirically scrollback ends up
# with 7 rows (ROW00..ROW06; the final \n on ROW29 also scrolls);
# active screen shows ROW07..ROW29 + blank. With scroll_offset=6 the
# visible composite is scrollback rows [count-6..count-1] = ROW01..
# ROW06 (top 6 of view) + active rows ROW07..ROW24 (bottom 18 of view)
# = 24 rows total ROW01..ROW24. Regressed renderer (no composite path)
# would show only ROW06..ROW29 (live screen), 5 rows different at top.
nbs_scroll_lines 6

nbs_test_render
nbs_test_complete
