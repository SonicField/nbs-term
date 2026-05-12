# nbs-term Feature Inventory

Authoritative catalogue of every user-facing feature and rendering / input mechanism in legacy nbs-term (`nbsterm.py` + `extension.phc` + supporting `.phc` modules + `config.py`), with per-feature mapping to current `p3_pty.exe` (pure-phc) state. Built per supervisor 2026-05-12 14:05:14 delegation under alexie 14:04:23 systematic-port directive.

**Authority binding** (alexie 2026-05-12 13:39:01 + 13:40:38, supervisor 13:40:59): the legacy implementation IS the spec. p3_pty ports replicate legacy behavior; do not redesign. Generalist's port commits should cite the legacy file:line(s) named below.

**Status legend:**
- `PRESENT` — feature is wired in p3_pty and matches legacy semantics
- `PARTIAL` — present but missing facets / edge cases / styles
- `MISSING` — entirely absent from p3_pty
- `BROKEN` — present but produces wrong output (alexie-observed or read-confirmed)

---

## A. Highest-priority brokenness (alexie 14:04:23 named)

| ID | Surface | Failure mode | Root cause (read-derived) | Fix shape |
|----|---------|--------------|---------------------------|-----------|
| A1 | Color rendering BROKEN | Per-cell fg colors collapse to row-uniform; SGR attrs (bold/italic/underline/dim/inverse) ignored | `p3_pty.phc:318-319` uses `screen_cell_const(scr, r, 0)->fg` — only column-0's fg for the whole row text item. No span-splitting on attr/color change. No `font_bold` / `font_italic` selection per attrs. | Port extension.phc:982-1153 span-splitting: walk cells grouping into spans of uniform (fg, bg, attrs); emit one text item per span at its measured x; apply font_tag = font_normal/bold/italic/bold_italic per attrs & 0x05; apply DIM/INVERSE per attrs & 0x02 / 0x20. |
| A2 | Layout PARTIALLY broken | (per alexie 13:35:31(3) + 14:04:23) Cursor too-far-left was eab5543; remainder TBD on Mac smoke. Cell-size uses font.measure now (e3d22a0+eab5543); origin/centering not implemented. | p3_pty does not implement `_compute_origin_for` (nbsterm.py:196-249) — text always at canvas (0, 0) with no centering padding. Window resize maps pixels to cells using g_cell_w/h with no asymmetric clamp (nbsterm.py:497-512 cols-self-correction missing); resize may oversize. | Port `_compute_origin_for` semantics: max-row text-width via per-span font.measure, take centered origin with PADDING margin. Add asymmetric bbox-calibration clamp on resize: only WIDEN g_cell_w, never shrink (per nbsterm.py:497-512 + alexie 2026-04-28 14:23:15 directive). |
| A3 | Config "not up" | Pressing Ctrl+, / Cmd+, opens nothing. File auto-create works (c2abdae verified). | (g) keybinding+dialog port deferred (supervisor 13:38:12 scoping). PreferencesDialog (nbsterm.py:887-1054) is Python+Tk Toplevel with per-field widgets — not yet ported to Tcl/Tk pure-phc. | Port PreferencesDialog as pure-Tcl `toplevel .prefs` with per-field entries + ColorPicker256, bound via `Ctrl+,` / `Cmd+,` per supervisor 13:38:12 mapping. |

---

## B. Rendering pipeline

| Feature | User-visible | Legacy file:line | Mechanism | p3_pty status |
|---------|--------------|------------------|-----------|---------------|
| Per-row text item | Each row drawn as one Tk canvas text item | nbsterm.py:323-371 + extension.phc:838-1185 `Terminal_render_frame` | spans grouped by (fg,bg,attrs), one text item per span, per-cell bg via separate rectangles | **PARTIAL** — single text per row at p3_pty.phc:323-327 with no span-splitting (A1). |
| Font tag per attrs | Bold / italic / bold-italic glyph variants | extension.phc:988-991 | font_tag selection by `attrs & 0x05` over four named fonts (font_normal/bold/italic/bold_italic) | **MISSING** — only `TkFixedFont` used. Per-attr font tags absent. |
| DIM attribute | Dimmed foreground color | extension.phc:977-980 + render_dim:624 | scale fg color toward bg by ~50% via render_dim helper | **MISSING** — DIM attr not applied. |
| INVERSE attribute | fg/bg swap | extension.phc:981-985 | swap span_fg/span_bg pointers before paint | **MISSING** — INVERSE attr not applied. |
| Gamma correction | Per-platform gamma applied to fg+bg | extension.phc:971-976 + 607-622 `render_gamma` | gamma_val ≠ 1.0 → per-component pow(c/255, gamma) on fg+bg hex strings | **MISSING** — `g_config.gamma` loaded but unconsumed (pythia #69 dead-loaded; phase-1 staged). |
| Per-cell bg rectangles | Different bg per cell within a row | extension.phc:1043-1107 (no-selection path) + p3_pty.phc:304-315 | for each cell with non-default bg, create_rectangle at cell coords | **PRESENT** — p3_pty.phc:304-315 emits per-cell bg rects. Note: uses g_cell_w/h grid coords; once font.measure-anchored (post-eab5543) cursor approach extends to span-text x positions, bg-rect coords should follow span x too for consistency. |
| Double-buffered render | Atomic frame swap; no flicker | extension.phc:915-1185 (front/back tag swap) | two tag namespaces buf_0/buf_1, render to back then `state normal` swap | **MISSING** — p3_pty.phc:290 does `delete all` per frame (single-buffered). Visible flicker risk on heavy redraw. |
| Dirty-row tracking | Only re-render rows that changed | extension.phc:861-877 + screen.phc:318-348 | per-row dirty flag; render_frame skips clean rows + retags front items to back | **MISSING** — p3_pty render_screen unconditionally redraws every row. |
| Border bg fill | Canvas margin painted bg color (not aqua-tint) | nbsterm.py:474-478 (`bg_fill` rect) | create_rectangle covering whole canvas, tag_lower beneath text | **MISSING** — canvas widget bg attr only; no bg_fill rect. Mac aqua tint may show through. |
| Render scheduling | Throttle to refresh_hz | nbsterm.py:105 + render schedule | `after(refresh_ms)` driven loop | **PARTIAL** — p3_pty.phc:`schedule_render` uses Tcl idle callback (`Tcl_DoWhenIdle`); no Hz throttle. `g_config.refresh_hz` loaded, unconsumed. |

---

## C. Cursor

| Feature | User-visible | Legacy file:line | Mechanism | p3_pty status |
|---------|--------------|------------------|-----------|---------------|
| Cursor primitive | Block / Underline / Bar overlay on row text | extension.phc:1109-1152 + nbsterm.py:368-407 (commit 07e0158 "Cursor overlay no span split") | rect at (cx, y, cx+cw, y+ch) cur_color fill + re-render cell char in span_bg color (Block); 2px-bottom rect (Underline); 2px-left rect (Bar). cx via font.measure(prefix-of-row-text) | **PRESENT** (eab5543) — render_cursor at p3_pty.phc:195-285 ports the legacy three-style overlay using font.measure prefix. Awaits alexie smoke (Win + Mac) for cursor-on-glyph + inverted-overlay falsifiers. |
| Cursor blink | Block toggles visibility every ~530ms | nbsterm.py:518-525 `_toggle_blink` + 514-516 schedule | tk `after(530, ...)` re-renders cursor row with toggled `_cursor_visible` flag | **MISSING** — `g_config.cursor.blink` loaded, unconsumed. p3_pty cursor always visible. |
| Cursor visibility (DECTCEM) | `\e[?25h` / `\e[?25l` show/hide | screen.phc cursor_visible flag (TODO) + vt_parser.phc:240/256 marked TODO | screen mode flag + render_cursor gates on it | **MISSING** in screen.phc + p3_pty (TODO comments in vt_parser show known gap). |
| Cursor color override | User-set color via PreferencesDialog | nbsterm.py:1007-1019 + extension.phc:1128 cur_color = override or fg | `g_config.cursor.color` non-empty → use; else fg | **PRESENT** — p3_pty.phc render_cursor reads `g_config.cursor.color`, falls through to `g_config.fg`. |
| Reset blink on output | Cursor stays visible during active typing | nbsterm.py:441-443 | reset `_cursor_visible=True`+ next blink restarts | **MISSING** — no blink in p3_pty. |

---

## D. Input / keybindings

| Feature | User-visible | Legacy file:line | Mechanism | p3_pty status |
|---------|--------------|------------------|-----------|---------------|
| Plain keystroke → child | Type 'a' → child receives 'a' | extension.phc:248-326 `Terminal_encode_tk_event` + nbsterm.py:527-540 `handle_key` | encode_tk_event(keysym, state, char_code, is_mac) handles all Tk key events | **PARTIAL** — p3_pty.phc:536 `bind .c <Key> {pty_write %A}` uses Tk `%A` substitution. ASCII/Unicode chars work; everything else (special keys, Ctrl combos, Alt prefix) BROKEN. |
| Special keys (arrows / function / Home / End / PageUp / PageDown / Insert / Delete / Tab / Esc / Enter / BS) | Arrow → cursor move; F-keys → escape sequences; etc. | input.phc:121-194 `encode_special_key` + extension.phc:266-285 `special_map` | per-keysym → escape sequence emit, modifier-aware via CSI param | **MISSING** — p3_pty has no special-key path. Arrows / Fn keys / Home / End etc. produce nothing or literal chars. |
| Application cursor mode (DECCKM) | App in vim/less changes arrow encoding | screen.phc mode_app_cursor + input.phc encode dispatch | `term->active->mode_app_cursor` → `\eO_` vs `\e[_` for arrows | **MISSING** in p3_pty (no special key path at all). |
| Modifier combinations (Ctrl-C, Ctrl-D, Ctrl-Z, Ctrl-\, etc.) | Ctrl-C → SIGINT to child | input.phc:64-119 `encode_key_event` + extension.phc:317-322 | modifier bitmask + codepoint → control byte | **PARTIAL** — Tk `%A` produces some control bytes (Ctrl-C → 0x03 char) but not consistently across keysym/state combinations. Untested at scale. |
| Alt-prefix (Alt+letter → ESC + letter) | meta key in shells | input.phc:64-119 (Alt branch) | prefix `\e` to char | **MISSING** — `%A` doesn't produce ESC prefix. |
| Bracketed paste (DEC 2004) | `\e[200~` ... `\e[201~` wrap | input.phc:195-201 + screen.phc mode_bracketed_paste | wrap pasted text when mode set | **PRESENT** (79646c0) — p3_pty.phc PtyPaste at lines 403-432, gates on `g_term->active->mode_bracketed_paste`. Awaits alexie smoke (Win + Mac) for paste-into-shell falsifier. |
| Copy keybinding | Ctrl+Shift+C / Cmd+C | nbsterm.py:1196 + 1372-1378 `_on_copy` | get_selected_text → clipboard_clear + clipboard_append | **MISSING** — no copy binding; no get_selected_text in p3_pty. |
| Paste keybinding | Ctrl+Shift+V / Cmd+V | nbsterm.py:1197 + 1379-1392 `_on_paste` | clipboard_get → encode_paste → pty_write | **PRESENT** (79646c0) — Tcl-side bind at p3_pty.phc:538-544. Awaits alexie smoke (Win + Mac) for paste-into-shell falsifier. |
| Preferences keybinding | Ctrl+, / Cmd+, opens dialog | nbsterm.py:1173,1198 + 1393-1397 `_on_preferences` | open PreferencesDialog Toplevel | **MISSING** — no binding; no dialog (A3). |
| New tab | Ctrl+Shift+T / Cmd+T | nbsterm.py:1174,1199 + 1321-1326 `_on_new_tab` | `_add_tab(host, port, username)` | **MISSING** — single-PTY p3_pty has no tab concept (h surface). |
| Close tab | Ctrl+Shift+W / Cmd+W | nbsterm.py:1194,1200 + 1355-1359 `_on_close_tab` + Mac menu mechanism | bind + Tk menu (Mac dual-mechanism per nbsterm.py:1182-1195 comment) | **MISSING**. |
| Next/Prev tab | Ctrl+Tab / Ctrl+Shift+Tab | nbsterm.py:1203-1204 + 1360-1371 | `_select_tab((idx ± 1) % len)` | **MISSING**. |
| F11 fullscreen toggle | F11 toggles fullscreen | nbsterm.py:1207 + 1430-1434 `_toggle_fullscreen` | `attributes('-fullscreen', not current)` | **MISSING**. |
| Scrollback keys | Ctrl+Shift+Up / Down | nbsterm.py:187-188 + 395-410 | scroll_lines(±N) → render | **MISSING**. |

---

## E. Tabs / multi-session

| Feature | User-visible | Legacy file:line | Mechanism | p3_pty status |
|---------|--------------|------------------|-----------|---------------|
| TabSession | One PTY + one TerminalWidget per tab | nbsterm.py:1054-1115 | TabSession holds host/port/username + SSHTransport + TerminalWidget; connects on `start()` | **MISSING** — p3_pty has single global g_term/g_pty/g_parser. |
| TabStrip UI | Top bar showing tab names + close × | nbsterm.py:1147-1163 + 1285-1314 `_refresh_tab_strip` | tk.Frame + tk.Label per tab + × close glyph | **MISSING**. |
| Active-tab indicator | Visual cue for selected tab | nbsterm.py:1289-1298 (selected styling per d538b3f arc) | bg/fg differentiation on selected vs unselected Frame+Label | **MISSING**. |
| Tab close × | Click × → close that tab | nbsterm.py:1300-1310 (per 4197557 commit) | per-Frame button bound to `_close_tab(idx)` | **MISSING**. |

---

## F. Selection / copy / paste / mouse

| Feature | User-visible | Legacy file:line | Mechanism | p3_pty status |
|---------|--------------|------------------|-----------|---------------|
| Mouse-down start selection | Click + drag selects cells | nbsterm.py:339-354 + selection.phc:phc_pixel_to_cell + extension.phc:1240+ | pixel→cell via _pixel_to_cell_text_aware (binary search per font.measure) | **PRESENT** (e0665eb F1) — NbsSelDown/Drag/Up Tcl cmds + ButtonPress-1/B1-Motion/ButtonRelease-1 binds; uniform pixel_to_cell (text-aware refinement deferred per theologian 16:19:22 trap, see entry below). Awaits alexie smoke (Win + Mac) for drag-select highlight follows cursor. Algorithm regression discriminator: tests/test_pixel_to_cell at 836d03b (12 cases over origin × cell × grid). PASS narrows any 'wrong cells' report to render-side (A2 origin / A3a font / C cursor); FAIL narrows to F1 selection arithmetic. |
| Selection highlight | Visual inversion of selected cells | nbsterm.py:367-376 + extension.phc:1241-1294 `Terminal_draw_selection` + 1006-1107 split-rendering | selection rect items + span-split rendering (before/sel/after) | **PRESENT** (e0665eb F1) — flush_span split-render via emit_sub helper (pre/sel/post sub-spans, fg↔bg swap on selected, gamma-applied per H). Awaits alexie smoke for fg/bg swap visibility on highlight. |
| Selection extraction | Get text from selected cells | extension.phc:531-606 `Terminal_extract_selected_text` | walk selected cells, emit utf8 with linebreaks | **PRESENT** (f391992 F2) — NbsCopy walks selected cells via row_sel_range + view_row_cells (G composite-aware), 64KB buf, '\n' on row boundary, Tk clipboard via Tcl_EvalObjv. Cmd+C / Ctrl+Shift+C bind on root. Awaits alexie smoke for paste-elsewhere round-trip. Algorithm regression discriminator: tests/test_extract_utf8 at 6665d9a (13 cases over utf8_emit + row_sel_range + extract walk + newline-on-row-boundary + truncation). PASS narrows any 'copy wrong' report to selection-state upstream OR Tk clipboard downstream; FAIL narrows to F2 byte-extract algorithm. |
| Mouse wheel scroll | Wheel up/down → scrollback | nbsterm.py:377-384 `_on_mouse_wheel` (Win/Mac) + 385-394 (Linux Button-4/5) | scroll_lines(±delta) | **PRESENT** (e45fbca G) — NbsScrollLines Tcl cmd (no-op on alt-screen) + bind . MouseWheel/Button-4/Button-5/Ctrl+Shift+Up/Down (keyboard binds on .c per Bug B1 break-consume). Awaits alexie smoke for history scroll + auto-snap-to-bottom + alt-screen guard. |
| _pixel_to_cell_text_aware | Mouse hit-test through proportional row text | nbsterm.py:286-337 (uses _row_spans_for_visible + per-span font.measure binary search) | walks spans summing measured widths until x falls within | **PARTIAL** — p3_pty.phc:388-401 uses uniform pixel/g_cell_w divide; text-aware refinement deferred per theologian 16:19:22 trap (Mac CoreText subadditivity is its own axis). 836d03b test_pixel_to_cell anchors the uniform algorithm for regression; the text-aware refinement when it lands will need its own discriminator. |
| Wide-char selection | Selecting wide char selects whole 2-cell glyph | extension.phc + screen.phc:cell.wide / wide_cont (06bf221, f8ac340) | wide_cont skip in cell walk; sel range covers both cells | **PARTIAL** — p3_pty render_screen + flush_span skip wide_cont; selection col→char-index assumes 1 char per cell so wide-char selection precision deferred (first cut handles ASCII / Latin / shell typical content). |

---

## G. Scrollback

| Feature | User-visible | Legacy file:line | Mechanism | p3_pty status |
|---------|--------------|------------------|-----------|---------------|
| Scrollback buffer | Lines that scroll off-top retained for review | screen.phc Scrollback struct + extension.phc:354-440 | ring buffer of (cells + length) per line | **PRESENT** in screen.phc (compiled in via vt_parser.phc include) but no UI affordance in p3_pty. |
| Scroll into history | Ctrl+Shift+Up/Down or wheel-up scrolls back | nbsterm.py:185-188 + 377-410 + extension.phc:1202-1239 (`get_scroll_offset`/`set_scroll_offset`/`scroll_lines`) | `term->scroll_offset` increments; render_frame composes scrollback + screen rows | **MISSING** UI — engine present, no binding. |
| Auto-scroll-to-bottom on output | Output snaps view to live edge | nbsterm.py:407-411 + 441-443 | reset `scroll_offset = 0` on feed | **MISSING** — p3_pty has no scroll_offset awareness. |
| Composite scroll view | Mixed scrollback + live screen rows | extension.phc:881-912 (composite path) | for each visible row, pull from scrollback if past top, else from screen | **MISSING** — p3_pty render_screen reads only `term->active`. |

---

## H. Colors

| Feature | User-visible | Legacy file:line | Mechanism | p3_pty status |
|---------|--------------|------------------|-----------|---------------|
| 16-color palette (ANSI) | Standard ANSI colors | render.phc:28-34 (ansi_colors[]) + p3_pty.phc/color.phc Indexed path | hex strings indexed 0..15 | **PRESENT** in color.phc; consumed by p3_pty color_to_hex. |
| 256-color cube + grayscale | xterm 256 | render.phc:36-50 + color.phc Indexed branch | 6×6×6 cube formula + 24-step gray ramp | **PRESENT** (color.phc Indexed handler). |
| RGB24 truecolor | `\e[38;2;R;G;B m` | render.phc:52-54 + color.phc Rgb24 variant | direct hex emit | **PRESENT** (color.phc). |
| Default fg/bg | App-wide default colors | extension.phc color_to_tk Default branch + p3_pty color_to_hex defcol param | Default → fall through to caller-supplied default hex | **PRESENT**. |
| Per-cell fg in row | Row mixed colors render correctly | extension.phc render_screen span split (982-1107) | new span on color/attr change | **BROKEN** (A1) — p3_pty uses row-uniform fg from col 0. |
| Per-cell bg | Mixed bg per cell | extension.phc bg rects + p3_pty.phc:304-315 | per-cell rect when bg ≠ default | **PRESENT** in p3_pty (matches legacy mechanism). |
| Gamma | bg/fg gamma-corrected per platform | extension.phc:607-622 render_gamma + nbsterm.py:114 _bg_render | pow(c/255, gamma) | **MISSING** in p3_pty (g_config.gamma loaded, unconsumed). |

---

## I. Config

| Feature | User-visible | Legacy file:line | Mechanism | p3_pty status |
|---------|--------------|------------------|-----------|---------------|
| Honest-file load on start | Reads ~/.nbs/nbs-term.honest | config.py:195-301 `load_config` | parse honest format → TerminalConfig dataclass | **PRESENT** (13f9d4e) — nbs_config_load in src/config.phc. |
| Auto-create on first run | Missing file → write defaults | config.py:218 (legacy default-write) | mkdir parent + write template | **PRESENT** (c2abdae) — nbs__write_default. |
| PreferencesDialog | Modal Toplevel for editing config | nbsterm.py:887-1054 PreferencesDialog | per-field tk.Entry / Checkbutton / OptionMenu + ColorPicker256 | **MISSING** (A3) — no dialog ported to pure-phc. |
| ColorPicker256 | 256-color palette picker | nbsterm.py:786-885 ColorPicker256 (Toplevel) | 6×6×6 grid of color swatch buttons + custom hex entry | **MISSING** — no picker in pure-phc. |
| Live config apply | Save → all tabs update | nbsterm.py:1398-1429 `_apply_config` | iterate widget.font/_cursor_*/_bg/_fg setters | **MISSING** — p3_pty reads g_config once at startup, no re-apply path. |
| Persistent settings (font / cursor / colors / gamma / refresh) | Survives restart | config.py:302-359 `save_config` (legacy write) | honest-file write of all fields | **PARTIAL** — load + auto-create work; consumer-wiring of the loaded fields is staged (pythia #69: 6 of 11 fields dead-loaded — font.family/size, cursor.style/blink, gamma, refresh_hz). |
| Monospace warning | Font picker warns on non-monospace | nbsterm.py:990-1005 `_check_monospace` | font.measure 'M' vs 'i', warn if differ | **MISSING** (no dialog yet). |

---

## J. SSH transport

| Feature | User-visible | Legacy file:line | Mechanism | p3_pty status |
|---------|--------------|------------------|-----------|---------------|
| SSH connection | Connect to remote host | nbsterm.py:614-784 SSHTransport | asyncssh via background asyncio loop in dedicated thread | **MISSING** — p3_pty spawns local shell only via pty.phc; no SSH path. |
| Host-key prompt | First-connect verification dialog | nbsterm.py:564-613 TkInteractionHandler.on_host_key | tk.messagebox.askyesno on main thread via _ask_on_main_thread | **MISSING**. |
| Keyboard-interactive auth | Password / 2FA prompts | nbsterm.py:597-612 on_kbdint | tk.simpledialog.askstring per prompt | **MISSING**. |
| SSH disconnect handling | Tab shows status / can reconnect | nbsterm.py:1099-1108 _on_close / _handle_disconnect | TabSession.stop() + UI update | **MISSING**. |
| SSH resize forwarding | Window resize → remote PTY resize | nbsterm.py:761-772 SSHTransport.resize | channel.change_terminal_size | **MISSING** (local PTY resize works via pty.phc TIOCSWINSZ). |

---

## K. Layout / window / fonts

| Feature | User-visible | Legacy file:line | Mechanism | p3_pty status |
|---------|--------------|------------------|-----------|---------------|
| Centered text origin | Text grid centered with PADDING | nbsterm.py:196-249 `_compute_origin_for` (per-row span font.measure max) | walks row spans, picks max measured width, centers within canvas_w | **MISSING** (A2) — p3_pty draws at (0, 0). |
| Asymmetric bbox calibration | char_width self-corrects from actual paint, never shrinks | nbsterm.py:497-512 + commit 926cb0c | bbox of "buf_0" tag → effective_cw; clamp WIDEN-only | **MISSING** in p3_pty (e3d22a0+eab5543 derive g_cell_w from font.measure once at startup; no post-paint re-measure). |
| Slop-margin cap | Border padding ≤ 2 × char_width | nbsterm.py + commit d390acc Bug C v3 | cap origin within `canvas_w//8 + 2*char_width` | **MISSING**. |
| Window title | Set by OSC 0/2 from remote | extension.phc OSC handling — currently `# We store it but don't act on it in C` (per src/vt_parser.phc:445 comment) | OSC 0/1/2 parse → title field on screen | **PARTIAL** — title parsed but not applied to wm title in p3_pty. |
| Resize → grid | Window resize → cols/rows recompute → TIOCSWINSZ | nbsterm.py:541-562 `handle_resize` + p3_pty.phc:309-316 + pty.phc resize | pixel→cell with g_cell_w/h | **PRESENT** but with A2 caveats (no asymmetric clamp). |
| Per-attr named fonts | font_normal / font_bold / font_italic / font_bold_italic | nbsterm.py:131-140 `_font_cache` | tk.font.Font with weight/slant via _named_font helper | **MISSING** in p3_pty (only TkFixedFont). |
| Default font family | Platform-aware default | nbsterm.py:55-71 `default_font_family` | Menlo on Mac else "monospace"; explicit (not silent) | **MISSING** (TkFixedFont used uniformly). |

---

## L. Mouse / scroll

| Feature | User-visible | Legacy file:line | Mechanism | p3_pty status |
|---------|--------------|------------------|-----------|---------------|
| Mouse-down/drag/up selection | See section F | nbsterm.py:339-354 | bind ButtonPress-1 / B1-Motion / ButtonRelease-1 | **MISSING**. |
| Wheel scroll | See section F | nbsterm.py:377-394 | bind MouseWheel (Win/Mac) + Button-4/5 (Linux) | **MISSING**. |

---

## M. DEC private modes (CSI ? Pn h / l)

| Mode | Feature | Legacy implementation | p3_pty status |
|------|---------|----------------------|---------------|
| DECCKM (1) | App cursor mode | screen.phc:122 + vt_parser.phc:238/254 + input.phc app_cursor branch | **PRESENT** in screen+parser; CONSUMER missing in p3_pty input path. |
| DECAWM (7) | Auto-wrap | screen.phc + vt_parser.phc:239/255 | **PRESENT** end-to-end. |
| DECTCEM (25) | Cursor visible | vt_parser.phc:240/256 — TODO | **MISSING** (TODO marked in source). |
| Alt screen (47/1047/1049) | Switch alt screen | screen.phc terminal_switch_alt + vt_parser.phc:241-243/257-259 | **PRESENT** (engine); render_frame uses term->using_alt; p3_pty render reads term->active so picks up alt-screen automatically. |
| Bracketed paste (2004) | See section D | screen.phc + vt_parser.phc:247/263 | **PRESENT** end-to-end (79646c0). |

Other DEC modes (DECOM 6, DECNCSM 95, mouse-tracking 1000/1006, focus-event 1004, etc.): NOT implemented in vt_parser; legacy nbs-term also lacks most. Out of scope for v1 parity.

---

## N. OSC sequences (ESC ] Pn ; Ps ST/BEL)

| OSC | Feature | Legacy implementation | p3_pty status |
|-----|---------|----------------------|---------------|
| 0/1/2 | Window title / icon name | vt_parser.phc:439-456 — comment "we store it but don't act on it in C" | **PARTIAL** — parsed, stored, never propagated to wm title. p3_pty also no consumer. |
| 4 | Set palette color | NOT in vt_parser | **MISSING** (legacy lacks too). |
| 8 | Hyperlink | NOT in vt_parser | **MISSING** (legacy lacks too). |
| 52 | Set/get clipboard | NOT in vt_parser | **MISSING**. |
| 10/11 | Default fg/bg | NOT in vt_parser | **MISSING**. |

---

## O. Engine (vt_parser, screen, sgr) — already shared

These compile into p3_pty's TU and are largely complete:

| Module | Coverage | Notes |
|--------|----------|-------|
| vt_parser.phc | C0/C1, CSI, OSC, DCS state machine; SGR; cursor moves; ED/EL; IRM/ICH/DCH/IL/DL; DECSTBM; charset SO/SI G0/G1 | DECTCEM TODO (M section); some less-used CSIs may be stubs — full audit deferred. |
| screen.phc | Cell grid, cursor, scrollback ring, alt screen, scroll regions, dirty tracking, wide chars, autowrap | Cursor visibility (DECTCEM) gap. |
| sgr.phc | SGR attribute parsing → Color enum + attrs bitmask | Complete per legacy needs. |
| color.phc / color_utils.phc | Default / Indexed / Rgb24 + utility | color_utils currently EXTENSION_SO-only (Python.h coupling per pythia #69 + theologian D-1778586192). For pure-phc gamma consumer, must extract gamma-relevant helpers into a Python-free header. |

---

## P. Build / packaging

| Feature | Status |
|---------|--------|
| Pure-phc binary p3_pty | **PRESENT** — Mac + Linux + Win all build per recent CI work. |
| Tcl/Tk vendoring | **PRESENT**. |
| Build-time trim of pkgs/* | **IN FLIGHT** — generalist working on theologian 13:59:17 analysis (delete deps/tcl/pkgs/{itcl,sqlite,tdbc*,thread} pre-configure). |
| Tcl/Tk source tree size | 91MB (66 + 25); not on critical path per theologian 13:34:37 analysis. |

---

## Port-priority recommendation (theologian, alexie's prio gates each)

The order minimises blockers + matches alexie's stated brokenness severity:

1. **A1 color rendering** (extension.phc:982-1107 span-split port): largest experiential gap; unblocks "looks like a real terminal" judgment.
2. **D special keys** (input.phc:121 → Tcl bind + dispatch): unblocks vim/less/anything beyond plain typing.
3. **A2 layout — origin centering + bbox-calibration**: unblocks resize-without-overflow.
4. **C cursor blink + DECTCEM hide**: small, completes the cursor surface.
5. **A3 / I PreferencesDialog port** (g): user-facing config control.
6. **F selection + copy + mouse**: pairs with the existing paste binding.
7. **G scrollback UI binding**: engine present, only UI wiring missing.
8. **E tabs** (h): largest multi-PTY structural change; alexie-greenlit.
9. **J SSH** (later — local-shell-only is honest current scope).

Port commits per item should cite the legacy file:line range above + carry the named-falsifier rule (alexie surface name + behavioural predicate).

---

## Methodology notes

- "Status" is a snapshot read 2026-05-12 14:14Z; future ports update inline.
- Cited `nbsterm.py` line numbers reference current HEAD (13f9d4e); legacy file is read-only spec source.
- Cited `extension.phc` line numbers reference current HEAD (build presently broken on legacy EXTENSION_SO target per testkeeper 11:46:55, but file is the authoritative C-side legacy spec for reading).
- p3_pty status verified by `grep` on the module + cross-reference to `g_config.*` consumer chains.
- Open questions (alexie call): how strict is "identical experience" (verbatim layout? close-enough?); v1 vs v2 split for SSH and tab UI.
