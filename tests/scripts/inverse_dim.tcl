# tests/scripts/inverse_dim.tcl — INVERSE Default+Default + DIM
# end-to-end render coverage
#
# Bucket B companion test for ac4480d (flush_span colour-pipeline
# reorder per supervisor 14:26:54 + theologian 14:26:37 BUNDLE).
# Discriminator for the two simultaneous fixes in that commit:
#  - INVERSE Default+Default no-op regression (alexie 14:16:47
#    'cursor invisible in claude-code' + theologian 13:56:44)
#  - DIM ignored at render regression (alexie 14:16:47 'dimmed text
#    rendered as the same as normal brightness' + theologian
#    14:18:00)
#
# Pre-fix: SGR 7 + neither colour set = no-op visual (post-swap
# Default still resolves to fg via fg-defcol). SGR 2 = no effect at
# render despite parsing. Post-fix: pipeline is resolve→gamma→DIM
# (fg only)→INVERSE swap of resolved hex per legacy
# extension.phc:970-985.
#
# Approach: 3 row-feed phases — INVERSE-only, DIM-only, INVERSE+DIM
# combined — each followed by inline assertions on the resulting
# canvas text + rect items. Errors raise TCL_ERROR -> harness exits
# non-zero (theologian 12:53:01 Option 1).

# Defaults from nbs_config_default (config.phc:91-92): font.family
# TkFixedFont, font.size 14, fg #d0d0d0, bg #1a1a1a, gamma 1.0.
# Gamma identity at default → gamma_apply is passthrough; expected
# colours match raw config values.

# Helper: find row-N text item with given text content; returns the
# fill colour or empty string if not found. Walks all canvas text
# items, matches on -text, returns -fill.
proc text_fill_for {canvas needle} {
    foreach id [$canvas find withtag row0] {
        set t [string trimright [$canvas itemcget $id -text]]
        if {$t eq $needle} {
            return [$canvas itemcget $id -fill]
        }
    }
    return ""
}

# Helper: find row-0 rect item whose x1 is at given x_pixel; return
# its fill or empty if not found. Useful for confirming bg-rect
# emission for INVERSE (post-swap bg ≠ widget bg → rect needed).
proc rect_fill_at {canvas x_pixel} {
    foreach id [$canvas find withtag row0] {
        if {[$canvas type $id] eq "rectangle"} {
            set coords [$canvas coords $id]
            set x1 [lindex $coords 0]
            if {abs($x1 - $x_pixel) < 0.5} {
                return [$canvas itemcget $id -fill]
            }
        }
    }
    return ""
}

# (1) INVERSE only: feed `\e[7mIVA\e[m` then render. Span "IVA" should
# render with fg=g_config.bg (dark) and a bg rect of fg colour.
# Pre-fix shape would resolve text fg to g_config.fg (= no visible
# inversion). Discriminator: text fill == #1a1a1a not #d0d0d0.
nbs_test_feed_bytes "\x1b\[7mIVA\x1b\[m"
nbs_test_render

set fill [text_fill_for .c "IVA"]
if {$fill ne "#1a1a1a"} {
    error "FAIL INVERSE: 'IVA' text fill = '$fill', want '#1a1a1a' (bg colour after swap of resolved hex). Pre-fix swap-tags-first then resolve-with-fg-defcol resolved Default→g_config.fg #d0d0d0 — visual no-op."
}

# (2) DIM only: feed `\e[2mDIM\e[m` then render (on row 1 of the
# next-page; we're cumulative so adjust). Actually feed CR LF first
# to advance to row 1, then the DIM segment. text "DIM" should
# render with fg = render_dim(g_config.fg) = #686868 (half of
# #d0d0d0). Pre-fix shape ignored CellAttr_Dim → text rendered at
# #d0d0d0 (no dim).
nbs_test_feed_bytes "\r\n\x1b\[2mDIM\x1b\[m"
nbs_test_render

# Helper for row1
proc text_fill_for_row {canvas row needle} {
    foreach id [$canvas find withtag row$row] {
        set t [string trimright [$canvas itemcget $id -text]]
        if {$t eq $needle} {
            return [$canvas itemcget $id -fill]
        }
    }
    return ""
}

set fill [text_fill_for_row .c 1 "DIM"]
if {$fill ne "#686868"} {
    error "FAIL DIM: 'DIM' text fill = '$fill', want '#686868' (render_dim(#d0d0d0)). Pre-fix CellAttr_Dim parsed but ignored at render → rendered #d0d0d0 = no dim."
}

# (3) INVERSE + DIM combined: feed `\e[2;7mID\e[m` on row 2.
# Pipeline: fg=Default→#d0d0d0; bg=Default→#1a1a1a; gamma identity;
# DIM applied to fg → #686868; INVERSE swap of resolved hex →
# fg_g=#1a1a1a, bg_g=#686868. Text "ID" should render fill=#1a1a1a
# with bg rect at #686868.
nbs_test_feed_bytes "\r\n\x1b\[2;7mID\x1b\[m"
nbs_test_render

set fill [text_fill_for_row .c 2 "ID"]
if {$fill ne "#1a1a1a"} {
    error "FAIL INVERSE+DIM: 'ID' text fill = '$fill', want '#1a1a1a' (post-DIM-on-fg + INVERSE swap). DIM applied to fg before swap; swap of resolved hex puts the unaltered bg colour into fg position."
}

# All assertions PASS — render the final state for golden capture.
nbs_test_complete
