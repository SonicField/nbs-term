# tests/scripts/c_dectcem.tcl — C cursor visibility (DECTCEM)
#
# Bucket B per-surface test for C cursor DECTCEM (commit a348556 —
# screen->mode_cursor_visible field + vt_parser.phc:240/256 toggle on
# CSI ?25l/?25h + render_cursor early-return at p3_pty.phc:552 when
# !mode_cursor_visible). The 9th zero-guard surface from testkeeper
# 09:41:25 coverage map; medic 13:43:35 + supervisor 13:44:26 caught
# this gap in the original Bucket B sequence (testkeeper 09:52:11
# omitted C in start order — A1 → A3a → F-mouse → F-copy → G).
#
# Discriminator: if alexie reports 'cursor stays visible when app
# hides it' (e.g. claude-code, vim insert-mode TUI sometimes hide the
# system cursor) AND this passes, bug is in CSI parser dispatch or
# render-after-mode-change schedule (Tk timing); if this fails,
# regression is inside vt_parser DECTCEM toggle OR render_cursor
# visibility gate.
#
# Approach: 3-phase script — (1) cold start: cursor visible per DEC
# default; (2) CSI ?25l: hide; (3) CSI ?25h: show again. Inline Tcl
# assertion: count cursor-fill rect items in the canvas after each
# render; expect 1 before hide + after show, 0 between. Errors raise
# TCL_ERROR -> harness exits non-zero. Per theologian 12:53:01
# Option 1 in-line assertion shape.
#
# Blink (530ms timer-driven g_blink_visible) deferred — requires
# production refactor to extract blink state machine into pure-C
# function per supervisor 13:44:26 split (DECTCEM-now, blink-later).

# Helper: count canvas items tagged "cursor". Block-style cursor
# emits 2 items per render (rect fill + inverted-text overlay per
# render_cursor at p3_pty.phc:610-660); Underline + Bar styles emit
# 1 (rect only). Discriminator is presence vs absence — when DECTCEM
# hides, count drops to 0 regardless of style.
proc cursor_item_count {canvas} {
    return [llength [$canvas find withtag cursor]]
}

# (1) Cold start: feed nothing, render. Cursor at row 0 col 0, visible
# by default (mode_cursor_visible = 1 per screen.phc:150). Block style
# default → 2 items (rect + inverted text); any non-zero proves visible.
nbs_test_render
set n0 [cursor_item_count .c]
if {$n0 < 1} {
    error "FAIL phase-1 cold-start: cursor count = $n0, want >=1 (DEC default mode_cursor_visible=1)"
}
set visible_count $n0

# (2) Feed CSI ?25l (hide cursor) then render. render_cursor early-
# return at p3_pty.phc:552 should produce zero cursor canvas items.
nbs_test_feed_bytes "\x1b\[?25l"
nbs_test_render
set n1 [cursor_item_count .c]
if {$n1 != 0} {
    error "FAIL phase-2 hide: cursor count = $n1 after CSI ?25l, want 0 (DECTCEM hide)"
}

# (3) Feed CSI ?25h (show cursor) then render. Cursor should reappear
# at the same item count as phase 1 (style unchanged).
nbs_test_feed_bytes "\x1b\[?25h"
nbs_test_render
set n2 [cursor_item_count .c]
if {$n2 != $visible_count} {
    error "FAIL phase-3 show: cursor count = $n2 after CSI ?25h, want $visible_count (matching phase-1 visible count)"
}

nbs_test_complete
