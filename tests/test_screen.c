/*
 * test_screen.c — Unit tests for screen buffer operations
 *
 * Tests allocation, cell operations, cursor movement, scrolling,
 * scroll regions, alternate screen, scrollback ring buffer, resize,
 * and SGR/pen operations.
 *
 * Uses phc test_framework.h for proper pass/fail/skip reporting.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#include "test_framework.h"

/* Include source .phc files directly — compiled as single translation unit */
#include "sgr.phc"
#include "screen.phc"

/* === Helpers === */

static Cell make_cell(uint32_t cp) {
    Pen pen = pen_default();
    return cell_from_pen(cp, &pen);
}

/* ================================================================
 * Section 1: Allocation and Deallocation
 * ================================================================ */

TEST(alloc_standard) {
    ScreenBuffer *scr = screen_alloc(24, 80);
    ASSERT_NOT_NULL(scr);
    ASSERT_EQ(scr->rows, 24);
    ASSERT_EQ(scr->cols, 80);
    ASSERT_EQ(scr->cursor.row, 0);
    ASSERT_EQ(scr->cursor.col, 0);
    ASSERT_EQ(scr->scroll_top, 0);
    ASSERT_EQ(scr->scroll_bottom, 23);
    screen_free(scr);
}

TEST(alloc_small) {
    ScreenBuffer *scr = screen_alloc(1, 1);
    ASSERT_NOT_NULL(scr);
    ASSERT_EQ(scr->rows, 1);
    ASSERT_EQ(scr->cols, 1);
    screen_free(scr);
}

TEST(alloc_large) {
    ScreenBuffer *scr = screen_alloc(200, 50);
    ASSERT_NOT_NULL(scr);
    ASSERT_EQ(scr->rows, 200);
    ASSERT_EQ(scr->cols, 50);
    screen_free(scr);
}

TEST(alloc_cells_empty) {
    ScreenBuffer *scr = screen_alloc(5, 5);
    ASSERT_NOT_NULL(scr);
    for (int r = 0; r < scr->rows; r++) {
        for (int c = 0; c < scr->cols; c++) {
            const Cell *cell = screen_cell_const(scr, r, c);
            ASSERT_EQ(cell->codepoint, 0);
            ASSERT_EQ(cell->fg.tag, Color_Default);
            ASSERT_EQ(cell->bg.tag, Color_Default);
            ASSERT_EQ(cell->attrs, 0);
        }
    }
    screen_free(scr);
}

TEST(free_null) {
    screen_free(NULL); /* must not crash */
}

/* ================================================================
 * Section 2: Cell Operations
 * ================================================================ */

TEST(cell_empty_defaults) {
    Cell c = cell_empty();
    ASSERT_EQ(c.codepoint, 0);
    ASSERT_EQ(c.fg.tag, Color_Default);
    ASSERT_EQ(c.bg.tag, Color_Default);
    ASSERT_EQ(c.attrs, 0);
    ASSERT_EQ(c.wide, 0);
    ASSERT_EQ(c.wide_cont, 0);
}

TEST(cell_from_pen_values) {
    Pen pen = pen_default();
    pen.fg = Color_mk_Indexed(1);
    pen.attrs = CellAttr_Bold;
    Cell c = cell_from_pen('A', &pen);
    ASSERT_EQ(c.codepoint, 'A');
    ASSERT_EQ(c.fg.tag, Color_Indexed);
    ASSERT_EQ(c.fg.Indexed.index, 1);
    ASSERT_EQ(c.attrs, CellAttr_Bold);
}

TEST(cell_write_read) {
    ScreenBuffer *scr = screen_alloc(24, 80);
    Cell c = make_cell('X');
    *screen_cell(scr, 5, 10) = c;
    ASSERT_EQ(screen_cell_const(scr, 5, 10)->codepoint, 'X');
    screen_free(scr);
}

TEST(cell_attributes_readback) {
    ScreenBuffer *scr = screen_alloc(24, 80);
    Cell c = cell_empty();
    c.codepoint = 'Z';
    c.fg = Color_mk_RGB(255, 0, 0);
    c.bg = Color_mk_Indexed(42);
    c.attrs = CellAttr_Bold | CellAttr_Underline;
    *screen_cell(scr, 0, 0) = c;

    const Cell *r = screen_cell_const(scr, 0, 0);
    ASSERT_EQ(r->codepoint, 'Z');
    ASSERT_EQ(r->fg.tag, Color_RGB);
    ASSERT_EQ(r->fg.RGB.r, 255);
    ASSERT_EQ(r->bg.tag, Color_Indexed);
    ASSERT_EQ(r->bg.Indexed.index, 42);
    ASSERT_EQ(r->attrs & CellAttr_Bold, CellAttr_Bold);
    ASSERT_EQ(r->attrs & CellAttr_Underline, CellAttr_Underline);
    screen_free(scr);
}

/* ================================================================
 * Section 3: Cursor Movement
 * ================================================================ */

TEST(cursor_clamp_negative) {
    ScreenBuffer *scr = screen_alloc(24, 80);
    scr->cursor.row = -5;
    scr->cursor.col = -5;
    screen_cursor_clamp(scr);
    ASSERT_EQ(scr->cursor.row, 0);
    ASSERT_EQ(scr->cursor.col, 0);
    screen_free(scr);
}

TEST(cursor_clamp_overflow) {
    ScreenBuffer *scr = screen_alloc(24, 80);
    scr->cursor.row = 100;
    scr->cursor.col = 200;
    screen_cursor_clamp(scr);
    ASSERT_EQ(scr->cursor.row, 23);
    ASSERT_EQ(scr->cursor.col, 79);
    screen_free(scr);
}

TEST(cursor_up) {
    ScreenBuffer *scr = screen_alloc(24, 80);
    scr->cursor.row = 10;
    screen_cursor_up(scr, 3);
    ASSERT_EQ(scr->cursor.row, 7);
    screen_free(scr);
}

TEST(cursor_up_clamp) {
    ScreenBuffer *scr = screen_alloc(24, 80);
    scr->cursor.row = 3;
    screen_cursor_up(scr, 10);
    ASSERT_EQ(scr->cursor.row, 0);
    screen_free(scr);
}

TEST(cursor_down) {
    ScreenBuffer *scr = screen_alloc(24, 80);
    screen_cursor_down(scr, 5);
    ASSERT_EQ(scr->cursor.row, 5);
    screen_free(scr);
}

TEST(cursor_down_clamp) {
    ScreenBuffer *scr = screen_alloc(24, 80);
    scr->cursor.row = 20;
    screen_cursor_down(scr, 10);
    ASSERT_EQ(scr->cursor.row, 23);
    screen_free(scr);
}

TEST(cursor_forward) {
    ScreenBuffer *scr = screen_alloc(24, 80);
    screen_cursor_forward(scr, 10);
    ASSERT_EQ(scr->cursor.col, 10);
    screen_free(scr);
}

TEST(cursor_forward_clamp) {
    ScreenBuffer *scr = screen_alloc(24, 80);
    scr->cursor.col = 75;
    screen_cursor_forward(scr, 10);
    ASSERT_EQ(scr->cursor.col, 79);
    screen_free(scr);
}

TEST(cursor_back) {
    ScreenBuffer *scr = screen_alloc(24, 80);
    scr->cursor.col = 10;
    screen_cursor_back(scr, 3);
    ASSERT_EQ(scr->cursor.col, 7);
    screen_free(scr);
}

TEST(cursor_back_clamp) {
    ScreenBuffer *scr = screen_alloc(24, 80);
    scr->cursor.col = 3;
    screen_cursor_back(scr, 10);
    ASSERT_EQ(scr->cursor.col, 0);
    screen_free(scr);
}

TEST(cursor_set_valid) {
    ScreenBuffer *scr = screen_alloc(24, 80);
    screen_cursor_set(scr, 10, 40);
    ASSERT_EQ(scr->cursor.row, 10);
    ASSERT_EQ(scr->cursor.col, 40);
    screen_free(scr);
}

TEST(cursor_set_clamped) {
    ScreenBuffer *scr = screen_alloc(24, 80);
    screen_cursor_set(scr, 999, 999);
    ASSERT_EQ(scr->cursor.row, 23);
    ASSERT_EQ(scr->cursor.col, 79);
    screen_free(scr);
}

/* ================================================================
 * Section 4: Character Insertion and Wrapping
 * ================================================================ */

TEST(put_char_basic) {
    ScreenBuffer *scr = screen_alloc(24, 80);
    screen_put_char(scr, NULL, 'A');
    ASSERT_EQ(screen_cell_const(scr, 0, 0)->codepoint, 'A');
    ASSERT_EQ(scr->cursor.col, 1);
    screen_free(scr);
}

TEST(put_char_wrap_pending) {
    ScreenBuffer *scr = screen_alloc(24, 5);
    for (int i = 0; i < 5; i++)
        screen_put_char(scr, NULL, 'A' + i);
    ASSERT_EQ(scr->cursor.wrap_pending, 1);
    ASSERT_EQ(scr->cursor.col, 4);
    screen_free(scr);
}

TEST(put_char_wrap_triggers) {
    ScreenBuffer *scr = screen_alloc(24, 5);
    for (int i = 0; i < 6; i++)
        screen_put_char(scr, NULL, 'A' + i);
    ASSERT_EQ(scr->cursor.row, 1);
    ASSERT_EQ(screen_cell_const(scr, 1, 0)->codepoint, 'F');
    screen_free(scr);
}

TEST(put_char_scroll_on_wrap) {
    ScreenBuffer *scr = screen_alloc(2, 3);
    /* Fill row 0 and row 1, then one more to trigger scroll */
    for (int i = 0; i < 7; i++)
        screen_put_char(scr, NULL, 'A' + i);
    /* Screen should have scrolled */
    ASSERT_EQ(scr->cursor.row, 1);
    screen_free(scr);
}

/* ================================================================
 * Section 5: Scrolling
 * ================================================================ */

TEST(scroll_up_basic) {
    ScreenBuffer *scr = screen_alloc(3, 5);
    for (int r = 0; r < 3; r++)
        screen_cell(scr, r, 0)->codepoint = 'A' + r;
    screen_scroll_up(scr, NULL, 1);
    ASSERT_EQ(screen_cell_const(scr, 0, 0)->codepoint, 'B');
    ASSERT_EQ(screen_cell_const(scr, 1, 0)->codepoint, 'C');
    ASSERT_EQ(screen_cell_const(scr, 2, 0)->codepoint, 0);
    screen_free(scr);
}

TEST(scroll_up_with_scrollback) {
    ScreenBuffer *scr = screen_alloc(3, 5);
    Scrollback *sb = scrollback_alloc(100, 5);
    for (int r = 0; r < 3; r++)
        screen_cell(scr, r, 0)->codepoint = 'A' + r;
    screen_scroll_up(scr, sb, 1);
    const Cell *sb_line = scrollback_get(sb, 0);
    ASSERT_NOT_NULL(sb_line);
    ASSERT_EQ(sb_line[0].codepoint, 'A');
    scrollback_free(sb);
    screen_free(scr);
}

TEST(scroll_down_basic) {
    ScreenBuffer *scr = screen_alloc(3, 5);
    for (int r = 0; r < 3; r++)
        screen_cell(scr, r, 0)->codepoint = 'A' + r;
    screen_scroll_down(scr, 1);
    ASSERT_EQ(screen_cell_const(scr, 0, 0)->codepoint, 0);
    ASSERT_EQ(screen_cell_const(scr, 1, 0)->codepoint, 'A');
    ASSERT_EQ(screen_cell_const(scr, 2, 0)->codepoint, 'B');
    screen_free(scr);
}

TEST(scroll_within_region) {
    ScreenBuffer *scr = screen_alloc(5, 5);
    for (int r = 0; r < 5; r++)
        screen_cell(scr, r, 0)->codepoint = 'A' + r;
    scr->scroll_top = 1;
    scr->scroll_bottom = 3;
    screen_scroll_up(scr, NULL, 1);
    ASSERT_EQ(screen_cell_const(scr, 0, 0)->codepoint, 'A');
    ASSERT_EQ(screen_cell_const(scr, 1, 0)->codepoint, 'C');
    ASSERT_EQ(screen_cell_const(scr, 2, 0)->codepoint, 'D');
    ASSERT_EQ(screen_cell_const(scr, 3, 0)->codepoint, 0);
    ASSERT_EQ(screen_cell_const(scr, 4, 0)->codepoint, 'E');
    screen_free(scr);
}

TEST(scroll_up_zero) {
    ScreenBuffer *scr = screen_alloc(3, 5);
    screen_cell(scr, 0, 0)->codepoint = 'A';
    screen_scroll_up(scr, NULL, 0);
    ASSERT_EQ(screen_cell_const(scr, 0, 0)->codepoint, 'A');
    screen_free(scr);
}

/* ================================================================
 * Section 6: Erase Operations
 * ================================================================ */

TEST(erase_display_all) {
    ScreenBuffer *scr = screen_alloc(3, 5);
    for (int r = 0; r < 3; r++)
        for (int c = 0; c < 5; c++)
            screen_cell(scr, r, c)->codepoint = 'X';
    screen_erase_display(scr, 2);
    for (int r = 0; r < 3; r++)
        for (int c = 0; c < 5; c++)
            ASSERT_EQ(screen_cell_const(scr, r, c)->codepoint, 0);
    screen_free(scr);
}

TEST(erase_line_to_end) {
    ScreenBuffer *scr = screen_alloc(1, 10);
    for (int c = 0; c < 10; c++)
        screen_cell(scr, 0, c)->codepoint = 'A' + c;
    scr->cursor.col = 5;
    screen_erase_line(scr, 0);
    for (int c = 0; c < 5; c++)
        ASSERT_EQ(screen_cell_const(scr, 0, c)->codepoint, (uint32_t)('A' + c));
    for (int c = 5; c < 10; c++)
        ASSERT_EQ(screen_cell_const(scr, 0, c)->codepoint, 0);
    screen_free(scr);
}

TEST(erase_line_to_start) {
    ScreenBuffer *scr = screen_alloc(1, 10);
    for (int c = 0; c < 10; c++)
        screen_cell(scr, 0, c)->codepoint = 'A' + c;
    scr->cursor.col = 5;
    screen_erase_line(scr, 1);
    for (int c = 0; c <= 5; c++)
        ASSERT_EQ(screen_cell_const(scr, 0, c)->codepoint, 0);
    for (int c = 6; c < 10; c++)
        ASSERT_EQ(screen_cell_const(scr, 0, c)->codepoint, (uint32_t)('A' + c));
    screen_free(scr);
}

TEST(erase_line_entire) {
    ScreenBuffer *scr = screen_alloc(1, 10);
    for (int c = 0; c < 10; c++)
        screen_cell(scr, 0, c)->codepoint = 'A' + c;
    screen_erase_line(scr, 2);
    for (int c = 0; c < 10; c++)
        ASSERT_EQ(screen_cell_const(scr, 0, c)->codepoint, 0);
    screen_free(scr);
}

/* ================================================================
 * Section 7: Insert/Delete Characters and Lines
 * ================================================================ */

TEST(insert_chars) {
    ScreenBuffer *scr = screen_alloc(1, 10);
    for (int i = 0; i < 5; i++)
        screen_cell(scr, 0, i)->codepoint = 'A' + i;
    scr->cursor.col = 2;
    screen_insert_chars(scr, 2);
    ASSERT_EQ(screen_cell_const(scr, 0, 0)->codepoint, 'A');
    ASSERT_EQ(screen_cell_const(scr, 0, 1)->codepoint, 'B');
    ASSERT_EQ(screen_cell_const(scr, 0, 2)->codepoint, 0);
    ASSERT_EQ(screen_cell_const(scr, 0, 3)->codepoint, 0);
    ASSERT_EQ(screen_cell_const(scr, 0, 4)->codepoint, 'C');
    screen_free(scr);
}

TEST(delete_chars) {
    ScreenBuffer *scr = screen_alloc(1, 10);
    for (int i = 0; i < 5; i++)
        screen_cell(scr, 0, i)->codepoint = 'A' + i;
    scr->cursor.col = 1;
    screen_delete_chars(scr, 2);
    ASSERT_EQ(screen_cell_const(scr, 0, 0)->codepoint, 'A');
    ASSERT_EQ(screen_cell_const(scr, 0, 1)->codepoint, 'D');
    ASSERT_EQ(screen_cell_const(scr, 0, 2)->codepoint, 'E');
    screen_free(scr);
}

/* ================================================================
 * Section 8: Scrollback Ring Buffer
 * ================================================================ */

TEST(scrollback_basic) {
    Scrollback *sb = scrollback_alloc(10, 5);
    ASSERT_NOT_NULL(sb);
    ASSERT_EQ(sb->count, 0);
    Cell line[5];
    for (int i = 0; i < 5; i++) line[i] = make_cell('A' + i);
    scrollback_push_n(sb, line, sb->cols);
    ASSERT_EQ(sb->count, 1);
    const Cell *got = scrollback_get(sb, 0);
    ASSERT_NOT_NULL(got);
    ASSERT_EQ(got[0].codepoint, 'A');
    ASSERT_EQ(got[4].codepoint, 'E');
    scrollback_free(sb);
}

TEST(scrollback_ring_wrap) {
    Scrollback *sb = scrollback_alloc(3, 2);
    for (int i = 0; i < 5; i++) {
        Cell line[2];
        line[0] = make_cell('A' + i);
        line[1] = make_cell('a' + i);
        scrollback_push_n(sb, line, sb->cols);
    }
    ASSERT_EQ(sb->count, 3);
    ASSERT_EQ(scrollback_get(sb, 0)[0].codepoint, 'C');
    ASSERT_EQ(scrollback_get(sb, 1)[0].codepoint, 'D');
    ASSERT_EQ(scrollback_get(sb, 2)[0].codepoint, 'E');
    scrollback_free(sb);
}

TEST(scrollback_get_oob) {
    Scrollback *sb = scrollback_alloc(10, 5);
    ASSERT_NULL(scrollback_get(sb, 0));
    ASSERT_NULL(scrollback_get(sb, -1));
    ASSERT_NULL(scrollback_get(sb, 100));
    scrollback_free(sb);
}

TEST(scrollback_free_null) {
    scrollback_free(NULL);
}

/* ================================================================
 * Section 9: Terminal (Main + Alt + Scrollback)
 * ================================================================ */

TEST(terminal_new_free) {
    Terminal *term = terminal_new(24, 80);
    ASSERT_NOT_NULL(term);
    ASSERT_NOT_NULL(term->main_screen);
    ASSERT_NOT_NULL(term->alt_screen);
    ASSERT_NOT_NULL(term->scrollback);
    ASSERT_EQ(term->using_alt, 0);
    ASSERT(term->active == term->main_screen);
    terminal_free(term);
}

TEST(terminal_switch_alt) {
    Terminal *term = terminal_new(24, 80);
    screen_cell(term->main_screen, 0, 0)->codepoint = 'M';
    terminal_switch_alt(term, 1);
    ASSERT_EQ(term->using_alt, 1);
    ASSERT(term->active == term->alt_screen);
    ASSERT_EQ(screen_cell_const(term->active, 0, 0)->codepoint, 0);
    terminal_switch_alt(term, 0);
    ASSERT_EQ(term->using_alt, 0);
    ASSERT_EQ(screen_cell_const(term->active, 0, 0)->codepoint, 'M');
    terminal_free(term);
}

TEST(terminal_free_null) {
    terminal_free(NULL);
}

/* ================================================================
 * Section 10: Resize
 * ================================================================ */

TEST(resize_grow) {
    ScreenBuffer *scr = screen_alloc(10, 10);
    screen_cell(scr, 0, 0)->codepoint = 'A';
    screen_resize(scr, 20, 20);
    ASSERT_EQ(scr->rows, 20);
    ASSERT_EQ(scr->cols, 20);
    ASSERT_EQ(screen_cell_const(scr, 0, 0)->codepoint, 'A');
    screen_free(scr);
}

TEST(resize_shrink) {
    ScreenBuffer *scr = screen_alloc(20, 20);
    screen_cell(scr, 0, 0)->codepoint = 'A';
    scr->cursor.row = 15;
    scr->cursor.col = 15;
    screen_resize(scr, 10, 10);
    ASSERT_EQ(scr->rows, 10);
    ASSERT_EQ(scr->cols, 10);
    ASSERT_EQ(screen_cell_const(scr, 0, 0)->codepoint, 'A');
    ASSERT_EQ(scr->cursor.row, 9);
    ASSERT_EQ(scr->cursor.col, 9);
    screen_free(scr);
}

TEST(resize_resets_scroll_region) {
    ScreenBuffer *scr = screen_alloc(24, 80);
    scr->scroll_top = 5;
    scr->scroll_bottom = 20;
    screen_resize(scr, 30, 100);
    ASSERT_EQ(scr->scroll_top, 0);
    ASSERT_EQ(scr->scroll_bottom, 29);
    screen_free(scr);
}

TEST(resize_shrink_then_scroll) {
    /* Pythia bug: after resize shrinks cols, scrollback_push reads
     * sb->cols cells from a screen row that only has scr->cols cells.
     * Heap buffer overread when sb->cols > scr->cols.
     * Use extreme shrink: 80 cols → 5 cols with 2 rows.
     * Screen buffer = 2*5 = 10 cells. Scrollback reads 80 cells from row 0.
     * Row 0 starts at offset 0, reading 80 cells from a 10-cell buffer = overread. */
    Terminal *term = terminal_new(2, 80);
    for (int c = 0; c < 80; c++) {
        screen_cell(term->main_screen, 0, c)->codepoint = 'A';
        screen_cell(term->main_screen, 1, c)->codepoint = 'B';
    }
    /* Shrink drastically: screen is now 5 cols, scrollback still expects 80 */
    terminal_resize(term, 2, 5);
    /* Scroll — pushes a 5-col row into an 80-col scrollback.
     * scrollback_push copies 80 cells from a buffer that only has 10 total.
     * Under ASan: heap-buffer-overflow. */
    screen_scroll_up(term->main_screen, term->scrollback, 1);
    /* If we get here without ASan crash, the bug may be fixed or masked. */
    terminal_free(term);
}

/* ================================================================
 * Section 11: SGR / Pen Operations
 * ================================================================ */

TEST(pen_defaults) {
    Pen p = pen_default();
    ASSERT_EQ(p.fg.tag, Color_Default);
    ASSERT_EQ(p.bg.tag, Color_Default);
    ASSERT_EQ(p.attrs, 0);
}

TEST(pen_bold_on_off) {
    Pen p = pen_default();
    pen_apply_sgr(&p, 1);
    ASSERT_EQ(p.attrs & CellAttr_Bold, CellAttr_Bold);
    pen_apply_sgr(&p, 22);
    ASSERT_EQ(p.attrs & CellAttr_Bold, 0);
}

TEST(pen_fg_color) {
    Pen p = pen_default();
    pen_apply_sgr(&p, 31);
    ASSERT_EQ(p.fg.tag, Color_Indexed);
    ASSERT_EQ(p.fg.Indexed.index, 1);
}

TEST(pen_bg_color) {
    Pen p = pen_default();
    pen_apply_sgr(&p, 42);
    ASSERT_EQ(p.bg.tag, Color_Indexed);
    ASSERT_EQ(p.bg.Indexed.index, 2);
}

TEST(pen_reset) {
    Pen p = pen_default();
    pen_apply_sgr(&p, 1);
    pen_apply_sgr(&p, 31);
    pen_apply_sgr(&p, 0);
    ASSERT_EQ(p.attrs, 0);
    ASSERT_EQ(p.fg.tag, Color_Default);
}

TEST(pen_256_fg) {
    Pen p = pen_default();
    int params[] = {38, 5, 196};
    pen_apply_sgr_extended(&p, params, 3, 0);
    ASSERT_EQ(p.fg.tag, Color_Indexed);
    ASSERT_EQ(p.fg.Indexed.index, 196);
}

TEST(pen_256_bg) {
    Pen p = pen_default();
    int params[] = {48, 5, 42};
    pen_apply_sgr_extended(&p, params, 3, 1);
    ASSERT_EQ(p.bg.tag, Color_Indexed);
    ASSERT_EQ(p.bg.Indexed.index, 42);
}

TEST(pen_rgb) {
    Pen p = pen_default();
    int params[] = {38, 2, 255, 128, 0};
    pen_apply_sgr_extended(&p, params, 5, 0);
    ASSERT_EQ(p.fg.tag, Color_RGB);
    ASSERT_EQ(p.fg.RGB.r, 255);
    ASSERT_EQ(p.fg.RGB.g, 128);
    ASSERT_EQ(p.fg.RGB.b, 0);
}

TEST(color_equal_same) {
    ASSERT(color_equal(Color_mk_Default(), Color_mk_Default()));
    ASSERT(color_equal(Color_mk_Indexed(42), Color_mk_Indexed(42)));
    ASSERT(color_equal(Color_mk_RGB(1, 2, 3), Color_mk_RGB(1, 2, 3)));
}

TEST(color_equal_different) {
    ASSERT_FALSE(color_equal(Color_mk_Default(), Color_mk_Indexed(0)));
    ASSERT_FALSE(color_equal(Color_mk_Indexed(1), Color_mk_Indexed(2)));
    ASSERT_FALSE(color_equal(Color_mk_Indexed(0), Color_mk_RGB(0, 0, 0)));
}

/* ================================================================
 * Main
 * ================================================================ */

TEST_MAIN(
    /* Allocation */
    RUN_TEST(alloc_standard);
    RUN_TEST(alloc_small);
    RUN_TEST(alloc_large);
    RUN_TEST(alloc_cells_empty);
    RUN_TEST(free_null);

    /* Cell operations */
    RUN_TEST(cell_empty_defaults);
    RUN_TEST(cell_from_pen_values);
    RUN_TEST(cell_write_read);
    RUN_TEST(cell_attributes_readback);

    /* Cursor movement */
    RUN_TEST(cursor_clamp_negative);
    RUN_TEST(cursor_clamp_overflow);
    RUN_TEST(cursor_up);
    RUN_TEST(cursor_up_clamp);
    RUN_TEST(cursor_down);
    RUN_TEST(cursor_down_clamp);
    RUN_TEST(cursor_forward);
    RUN_TEST(cursor_forward_clamp);
    RUN_TEST(cursor_back);
    RUN_TEST(cursor_back_clamp);
    RUN_TEST(cursor_set_valid);
    RUN_TEST(cursor_set_clamped);

    /* Character insertion */
    RUN_TEST(put_char_basic);
    RUN_TEST(put_char_wrap_pending);
    RUN_TEST(put_char_wrap_triggers);
    RUN_TEST(put_char_scroll_on_wrap);

    /* Scrolling */
    RUN_TEST(scroll_up_basic);
    RUN_TEST(scroll_up_with_scrollback);
    RUN_TEST(scroll_down_basic);
    RUN_TEST(scroll_within_region);
    RUN_TEST(scroll_up_zero);

    /* Erase */
    RUN_TEST(erase_display_all);
    RUN_TEST(erase_line_to_end);
    RUN_TEST(erase_line_to_start);
    RUN_TEST(erase_line_entire);

    /* Insert/Delete */
    RUN_TEST(insert_chars);
    RUN_TEST(delete_chars);

    /* Scrollback */
    RUN_TEST(scrollback_basic);
    RUN_TEST(scrollback_ring_wrap);
    RUN_TEST(scrollback_get_oob);
    RUN_TEST(scrollback_free_null);

    /* Terminal */
    RUN_TEST(terminal_new_free);
    RUN_TEST(terminal_switch_alt);
    RUN_TEST(terminal_free_null);

    /* Resize */
    RUN_TEST(resize_grow);
    RUN_TEST(resize_shrink);
    RUN_TEST(resize_resets_scroll_region);
    RUN_TEST(resize_shrink_then_scroll);

    /* SGR / Pen */
    RUN_TEST(pen_defaults);
    RUN_TEST(pen_bold_on_off);
    RUN_TEST(pen_fg_color);
    RUN_TEST(pen_bg_color);
    RUN_TEST(pen_reset);
    RUN_TEST(pen_256_fg);
    RUN_TEST(pen_256_bg);
    RUN_TEST(pen_rgb);
    RUN_TEST(color_equal_same);
    RUN_TEST(color_equal_different);
)
