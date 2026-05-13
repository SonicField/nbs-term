# tests/scripts/f_copy.tcl — F copy clipboard utf8 round-trip
#
# Bucket B per-surface test for F2 (commit f391992 — NbsCopy walks
# selected cells via row_sel_range + view_row_cells, emits utf8 to a
# 64KB buffer, sets Tk clipboard via Tcl_EvalObjv). Discriminator:
# if alexie reports 'copy gives wrong text' AND this passes, bug is
# in selection-state upstream (NbsSelDown/Drag/Up arithmetic — covered
# by F1 test_pixel_to_cell unit test) OR Tk clipboard downstream
# (system clipboard daemon); if this fails, regression is inside
# NbsCopy walk OR utf8_emit + row_sel_range (covered by F2
# test_extract_utf8 unit test).
#
# Approach: feed 'hello world' (single row), set selection to columns
# 6..11 inclusive (selecting 'world' end-exclusive per row_sel_range
# at p3_pty.phc:406-415), call nbs_copy directly (skip Cmd+C/Ctrl+
# Shift+C bind firing — Tk infrastructure, not our logic). Then assert
# nbs_test_get_clipboard returns 'world' exactly. Errors raise
# TCL_ERROR -> harness exits non-zero.

nbs_test_feed_bytes "hello world"
nbs_test_set_sel 0 6 0 11
nbs_copy

set actual [nbs_test_get_clipboard]
set want "world"
if {$actual ne $want} {
    error "FAIL: clipboard = '$actual', want '$want' (NbsCopy walk + utf8_emit + row_sel_range chain)"
}

# Multi-row case: feed two rows + select across.
# 'foo\r\nbar' would need CR+LF feed; simpler with explicit \r\n.
nbs_test_feed_bytes "\r\nbar"
# Selection: row 0 cols 0..3 + row 1 cols 0..3 (inclusive) => 'hello' + '\n' + 'bar'
# end-exclusive: er=1 ec=3 captures 'bar' on row 1.
# Expected per NbsCopy: row 0 chars [0..80) (row continues to cols)
# concat '\n' + row 1 chars [0..3) = full row 0 + '\n' + 'bar'.
# Row 0 has 'hello world' followed by trailing spaces to col 80.
# Strip trailing spaces in actual? NbsCopy emits trailing spaces;
# verify pattern: starts with 'hello world', has many spaces, then \n + 'bar'.
nbs_test_set_sel 0 0 1 3
nbs_copy

set actual2 [nbs_test_get_clipboard]
if {[string range $actual2 0 10] ne "hello world"} {
    error "FAIL: multi-row clipboard does not start with 'hello world' (got: '$actual2')"
}
# Expect '\nbar' at the tail (after row-0 trailing spaces).
if {[string range $actual2 end-3 end] ne "\nbar"} {
    error "FAIL: multi-row clipboard tail != '\\nbar' (got: '[string range $actual2 end-3 end]')"
}

nbs_test_render
nbs_test_complete
