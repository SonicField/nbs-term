# tests/scripts/a3a_prefs.tcl — A3a PreferencesDialog construction +
# var-binding verification
#
# Bucket B per-surface test for A3a (commit 2e57d0d — PreferencesDialog
# Toplevel + per-field widgets + Ctrl+, / Cmd+, bind). Discriminator:
# if alexie reports 'Prefs dialog does not open' OR 'Prefs fields show
# wrong values' AND this passes, bug is in the keybinding chain
# (Ctrl+, / Cmd+, → nbs_open_prefs) — Tk infrastructure layer; if this
# fails, regression is inside NbsOpenPrefs widget construction or
# g_config → ::prefs_* var population.
#
# Approach (theologian 2026-05-13 12:53:01 Option 1): call
# nbs_open_prefs directly (skip bind firing — Tk infrastructure, not
# our logic); assert Toplevel + per-field widget existence + var binding
# inline; raise Tcl error on mismatch (harness exits non-zero per
# Tcl_EvalFile error path at test_render_state.phc:515).

# (1) Trigger dialog construction.
nbs_open_prefs

# (2) Toplevel must exist.
if {![winfo exists .prefs]} {
    error "FAIL: .prefs Toplevel not created by nbs_open_prefs"
}

# (3) Per-field widgets must exist (one per g_config field).
foreach {widget label} {
    .prefs.ef "font-family combobox"
    .prefs.es "font-size spinbox"
    .prefs.ecs "cursor-style combobox"
    .prefs.ecb "cursor-blink checkbutton"
    .prefs.fcc.e "cursor-color entry"
    .prefs.fcc.b "cursor-color picker button"
    .prefs.eg "gamma scale"
    .prefs.ffg.e "fg entry"
    .prefs.ffg.b "fg picker button"
    .prefs.fbg.e "bg entry"
    .prefs.fbg.b "bg picker button"
    .prefs.er "rows spinbox"
    .prefs.ec "cols spinbox"
    .prefs.eh "refresh-hz scale"
    .prefs.btn.s "Save button"
    .prefs.btn.c "Cancel button"
} {
    if {![winfo exists $widget]} {
        error "FAIL: $label ($widget) not created by nbs_open_prefs"
    }
}

# (4) Per-field widgets must be bound to the correct global var so the
# Save path (nbs_save_prefs) reads back correct user input.
foreach {widget expected_var} {
    .prefs.ef ::prefs_font_family
    .prefs.es ::prefs_font_size
    .prefs.ecs ::prefs_cursor_style
    .prefs.fcc.e ::prefs_cursor_color
    .prefs.ffg.e ::prefs_fg
    .prefs.fbg.e ::prefs_bg
    .prefs.er ::prefs_rows
    .prefs.ec ::prefs_cols
} {
    set actual [$widget cget -textvariable]
    if {$actual ne $expected_var} {
        error "FAIL: $widget cget -textvariable = '$actual', want '$expected_var'"
    }
}

# (5) Defaults loaded from g_config (cold-start path: nbs_config_default
# at config.phc:83-92 — TkFixedFont / size 14 / Block / blink 1 / etc).
# nbs_test_layout_done has fired by the time the harness runs the
# script (per test_render_state.phc:510 vwait), so g_config is
# populated and ::prefs_* vars are pre-set by NbsOpenPrefs from g_config.
if {$::prefs_font_family ne "TkFixedFont"} {
    error "FAIL: ::prefs_font_family = '$::prefs_font_family', want 'TkFixedFont' (config.phc:91 default)"
}
if {$::prefs_font_size != 14} {
    error "FAIL: ::prefs_font_size = $::prefs_font_size, want 14 (config.phc:92 default)"
}
if {$::prefs_cursor_style ne "Block"} {
    error "FAIL: ::prefs_cursor_style = '$::prefs_cursor_style', want 'Block' (config.phc default)"
}

# (6) A3a font-picker pulldown (commit 7d61308): font-family widget
# class is ttk::combobox (was Entry pre-7d61308); -values list contains
# at least TkFixedFont (the seed entry — even if no system monospace
# detected, TkFixedFont is always selectable).
set fam_class [winfo class .prefs.ef]
if {$fam_class ne "TCombobox"} {
    error "FAIL: .prefs.ef class = '$fam_class', want 'TCombobox' per 7d61308 font-picker pulldown"
}
set fam_values [.prefs.ef cget -values]
if {[lsearch -exact $fam_values "TkFixedFont"] < 0} {
    error "FAIL: .prefs.ef -values does not contain TkFixedFont seed entry (got: $fam_values)"
}

# All assertions passed. Render + complete so harness produces a
# golden-comparable dump (canvas is mostly empty since Prefs is on
# a separate Toplevel, but a stable golden over the .c surface still
# anchors the cold-start render-after-prefs-open path).
nbs_test_render
nbs_test_complete
