# tests/scripts/f_mouse.tcl — F mouse selection split-render
# verification
#
# Bucket B per-surface test for F1 (commit e0665eb — port of legacy
# extension.phc:1240+ Terminal_draw_selection split-rendering, plus
# the flush_span emit_sub helper at p3_pty.phc:716-719). Discriminator:
# if alexie reports 'selection highlight wrong / missing' AND this
# passes, bug is in NbsSelDown/Drag/Up button-event arithmetic OR
# the Tk binding chain — pixel→cell mapping (covered by the F1
# test_pixel_to_cell unit test); if this fails, regression is inside
# flush_span split-render (selection range applied as 3 sub-spans
# with fg↔bg swap on the selected segment).
#
# Approach: feed a single 5-character ASCII span ('hello'), set
# selection to columns 2..4 inclusive (selecting 'll' — sr=0 sc=2
# er=0 ec=4 with end-exclusive convention per row_sel_range at
# src/p3_pty.phc:406-415); render. The harness dump should show
# THREE text items for row 0: 'he' (default fg/bg), 'll' (swapped
# fg=bg, bg=fg per inverse-render branch), 'o' (default).
# Regressed renderer would emit one row-uniform text item with no
# split; or split with wrong colors.

nbs_test_feed_bytes "hello"
nbs_test_set_sel 0 2 0 4
nbs_test_render
nbs_test_complete
