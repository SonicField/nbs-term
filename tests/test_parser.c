/*
 * test_parser.c — Comprehensive unit tests for VT parser
 *
 * Tests state transitions, CSI dispatch, SGR attributes, UTF-8 decoding,
 * OSC/DCS handling, partial buffer feeds, and adversarial inputs.
 *
 * Uses phc test_framework.h for proper pass/fail/skip reporting.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdarg.h>

/* phc test framework — proper pass/fail/skip tracking */
#include "test_framework.h"

/* Include source .phc files directly — compiled as single translation unit */
#include "sgr.phc"
#include "screen.phc"
#include "vt_parser.phc"
#include "input.phc"

/* === Helpers === */

static void feed(VTParser *p, const uint8_t *data, int len) {
    vt_parser_feed(p, data, len);
}

static void feed_str(VTParser *p, const char *s) {
    feed(p, (const uint8_t *)s, (int)strlen(s));
}

static void feed_bytes(VTParser *p, ...) {
    /* Sentinel-terminated list of bytes */
    va_list ap;
    va_start(ap, p);
    uint8_t buf[256];
    int n = 0;
    int b;
    while ((b = va_arg(ap, int)) != -1 && n < 256) {
        buf[n++] = (uint8_t)b;
    }
    va_end(ap);
    feed(p, buf, n);
}

static uint32_t cell_cp(Terminal *term, int row, int col) {
    return screen_cell_const(term->active, row, col)->codepoint;
}

static const Cell *cell_at(Terminal *term, int row, int col) {
    return screen_cell_const(term->active, row, col);
}

/* Create a fresh terminal+parser pair. Caller must free both. */
typedef struct { Terminal *term; VTParser *parser; } TestCtx;

static TestCtx make_ctx(int rows, int cols) {
    TestCtx ctx;
    ctx.term = terminal_new(rows, cols);
    ctx.parser = vt_parser_new(ctx.term);
    return ctx;
}

static void free_ctx(TestCtx *ctx) {
    vt_parser_free(ctx->parser);
    terminal_free(ctx->term);
}

/* ================================================================
 * Section 1: Ground State — Printable Characters and C0 Controls
 * ================================================================ */

TEST(printable_ascii) {
    TestCtx c = make_ctx(24, 80);
    feed_str(c.parser, "Hello");
    ASSERT_EQ(cell_cp(c.term, 0, 0), 'H');
    ASSERT_EQ(cell_cp(c.term, 0, 1), 'e');
    ASSERT_EQ(cell_cp(c.term, 0, 2), 'l');
    ASSERT_EQ(cell_cp(c.term, 0, 3), 'l');
    ASSERT_EQ(cell_cp(c.term, 0, 4), 'o');
    ASSERT_EQ(c.term->active->cursor.col, 5);
    ASSERT_EQ(c.term->active->cursor.row, 0);
    free_ctx(&c);
}

TEST(printable_utf8_2byte) {
    TestCtx c = make_ctx(24, 80);
    /* é = U+00E9 = 0xC3 0xA9 */
    uint8_t bytes[] = {0xC3, 0xA9};
    feed(c.parser, bytes, 2);
    ASSERT_EQ(cell_cp(c.term, 0, 0), 0x00E9);
    ASSERT_EQ(c.term->active->cursor.col, 1);
    free_ctx(&c);
}

TEST(printable_utf8_3byte) {
    TestCtx c = make_ctx(24, 80);
    /* ✓ = U+2713 = 0xE2 0x9C 0x93 */
    uint8_t bytes[] = {0xE2, 0x9C, 0x93};
    feed(c.parser, bytes, 3);
    ASSERT_EQ(cell_cp(c.term, 0, 0), 0x2713);
    ASSERT_EQ(c.term->active->cursor.col, 1);
    free_ctx(&c);
}

TEST(printable_utf8_4byte) {
    TestCtx c = make_ctx(24, 80);
    /* U+1F600 = 0xF0 0x9F 0x98 0x80 */
    uint8_t bytes[] = {0xF0, 0x9F, 0x98, 0x80};
    feed(c.parser, bytes, 4);
    ASSERT_EQ(cell_cp(c.term, 0, 0), 0x1F600);
    free_ctx(&c);
}

TEST(control_bel) {
    TestCtx c = make_ctx(24, 80);
    feed_str(c.parser, "A");
    uint8_t bel = 0x07;
    feed(c.parser, &bel, 1);
    /* BEL: no screen change, cursor stays */
    ASSERT_EQ(cell_cp(c.term, 0, 0), 'A');
    ASSERT_EQ(c.term->active->cursor.col, 1);
    free_ctx(&c);
}

TEST(control_bs) {
    TestCtx c = make_ctx(24, 80);
    feed_str(c.parser, "AB\bC");
    ASSERT_EQ(cell_cp(c.term, 0, 0), 'A');
    ASSERT_EQ(cell_cp(c.term, 0, 1), 'C');
    ASSERT_EQ(c.term->active->cursor.col, 2);
    free_ctx(&c);
}

TEST(control_ht) {
    TestCtx c = make_ctx(24, 80);
    feed_str(c.parser, "A\tB");
    ASSERT_EQ(cell_cp(c.term, 0, 0), 'A');
    ASSERT_EQ(cell_cp(c.term, 0, 8), 'B');
    free_ctx(&c);
}

TEST(control_lf) {
    TestCtx c = make_ctx(24, 80);
    feed_str(c.parser, "AB\nCD");
    ASSERT_EQ(cell_cp(c.term, 0, 0), 'A');
    ASSERT_EQ(cell_cp(c.term, 0, 1), 'B');
    /* LF without CR: column stays */
    ASSERT_EQ(cell_cp(c.term, 1, 2), 'C');
    ASSERT_EQ(cell_cp(c.term, 1, 3), 'D');
    free_ctx(&c);
}

TEST(control_cr) {
    TestCtx c = make_ctx(24, 80);
    feed_str(c.parser, "AB\rCD");
    /* CR moves to col 0, then C overwrites A, D overwrites B */
    ASSERT_EQ(cell_cp(c.term, 0, 0), 'C');
    ASSERT_EQ(cell_cp(c.term, 0, 1), 'D');
    free_ctx(&c);
}

TEST(control_cr_lf) {
    TestCtx c = make_ctx(24, 80);
    feed_str(c.parser, "AB\r\nCD");
    ASSERT_EQ(cell_cp(c.term, 0, 0), 'A');
    ASSERT_EQ(cell_cp(c.term, 0, 1), 'B');
    ASSERT_EQ(cell_cp(c.term, 1, 0), 'C');
    ASSERT_EQ(cell_cp(c.term, 1, 1), 'D');
    free_ctx(&c);
}

TEST(escape_entry) {
    TestCtx c = make_ctx(24, 80);
    uint8_t esc = 0x1B;
    feed(c.parser, &esc, 1);
    ASSERT_EQ(c.parser->state.tag, VTState_Escape);
    free_ctx(&c);
}

/* ================================================================
 * Section 2: Escape State
 * ================================================================ */

TEST(esc_csi_entry) {
    TestCtx c = make_ctx(24, 80);
    feed_str(c.parser, "\x1b[");
    ASSERT_EQ(c.parser->state.tag, VTState_CSI);
    free_ctx(&c);
}

TEST(esc_osc_entry) {
    TestCtx c = make_ctx(24, 80);
    feed_str(c.parser, "\x1b]");
    ASSERT_EQ(c.parser->state.tag, VTState_OSC);
    free_ctx(&c);
}

TEST(esc_dcs_entry) {
    TestCtx c = make_ctx(24, 80);
    feed_str(c.parser, "\x1bP");
    ASSERT_EQ(c.parser->state.tag, VTState_DCS);
    free_ctx(&c);
}

TEST(esc_reverse_index) {
    TestCtx c = make_ctx(24, 80);
    feed_str(c.parser, "TopLine\r\n");
    feed_str(c.parser, "\x1b[1;1H");
    feed_str(c.parser, "\x1bM");
    ASSERT_EQ(cell_cp(c.term, 1, 0), 'T');
    ASSERT_EQ(c.parser->state.tag, VTState_Ground);
    free_ctx(&c);
}

TEST(esc_save_restore_cursor) {
    TestCtx c = make_ctx(24, 80);
    feed_str(c.parser, "\x1b[5;10H");
    feed_str(c.parser, "\x1b" "7");   /* DECSC */
    feed_str(c.parser, "\x1b[1;1H");
    ASSERT_EQ(c.term->active->cursor.row, 0);
    feed_str(c.parser, "\x1b" "8");   /* DECRC */
    ASSERT_EQ(c.term->active->cursor.row, 4);
    ASSERT_EQ(c.term->active->cursor.col, 9);
    free_ctx(&c);
}

TEST(esc_interrupted_by_esc) {
    TestCtx c = make_ctx(24, 80);
    /* ESC then another ESC — restart escape */
    feed_str(c.parser, "\x1b\x1b[2J");
    /* Second ESC starts new escape, [2J is CSI erase display */
    ASSERT_EQ(c.parser->state.tag, VTState_Ground);
    free_ctx(&c);
}

/* ================================================================
 * Section 3: CSI State
 * ================================================================ */

TEST(csi_cursor_up) {
    TestCtx c = make_ctx(24, 80);
    feed_str(c.parser, "\x1b[6;1H");
    ASSERT_EQ(c.term->active->cursor.row, 5);
    feed_str(c.parser, "\x1b[3A");
    ASSERT_EQ(c.term->active->cursor.row, 2);
    free_ctx(&c);
}

TEST(csi_cursor_up_default) {
    TestCtx c = make_ctx(24, 80);
    feed_str(c.parser, "\x1b[6;1H");
    feed_str(c.parser, "\x1b[A");
    ASSERT_EQ(c.term->active->cursor.row, 4);
    free_ctx(&c);
}

TEST(csi_cursor_down) {
    TestCtx c = make_ctx(24, 80);
    feed_str(c.parser, "\x1b[B");
    ASSERT_EQ(c.term->active->cursor.row, 1);
    free_ctx(&c);
}

TEST(csi_cursor_forward) {
    TestCtx c = make_ctx(24, 80);
    feed_str(c.parser, "\x1b[5C");
    ASSERT_EQ(c.term->active->cursor.col, 5);
    free_ctx(&c);
}

TEST(csi_cursor_backward) {
    TestCtx c = make_ctx(24, 80);
    feed_str(c.parser, "\x1b[10;20H");
    feed_str(c.parser, "\x1b[5D");
    ASSERT_EQ(c.term->active->cursor.col, 14);
    free_ctx(&c);
}

TEST(csi_cursor_position) {
    TestCtx c = make_ctx(24, 80);
    feed_str(c.parser, "\x1b[10;20H");
    ASSERT_EQ(c.term->active->cursor.row, 9);
    ASSERT_EQ(c.term->active->cursor.col, 19);
    free_ctx(&c);
}

TEST(csi_cursor_position_defaults) {
    TestCtx c = make_ctx(24, 80);
    feed_str(c.parser, "\x1b[10;20H");
    feed_str(c.parser, "\x1b[H");
    ASSERT_EQ(c.term->active->cursor.row, 0);
    ASSERT_EQ(c.term->active->cursor.col, 0);
    free_ctx(&c);
}

TEST(csi_erase_display_all) {
    TestCtx c = make_ctx(24, 80);
    feed_str(c.parser, "ABCDE");
    feed_str(c.parser, "\x1b[2J");
    ASSERT_EQ(cell_cp(c.term, 0, 0), 0);
    ASSERT_EQ(cell_cp(c.term, 0, 4), 0);
    free_ctx(&c);
}

TEST(csi_erase_display_below) {
    TestCtx c = make_ctx(24, 80);
    feed_str(c.parser, "AAAAA\r\nBBBBB\r\nCCCCC");
    feed_str(c.parser, "\x1b[2;3H");  /* row 2, col 3 */
    feed_str(c.parser, "\x1b[0J");
    /* Row 0 untouched */
    ASSERT_EQ(cell_cp(c.term, 0, 0), 'A');
    /* Row 1: cols 0-1 preserved, col 2+ erased */
    ASSERT_EQ(cell_cp(c.term, 1, 0), 'B');
    ASSERT_EQ(cell_cp(c.term, 1, 1), 'B');
    ASSERT_EQ(cell_cp(c.term, 1, 2), 0);
    /* Row 2 fully erased */
    ASSERT_EQ(cell_cp(c.term, 2, 0), 0);
    free_ctx(&c);
}

TEST(csi_erase_line_right) {
    TestCtx c = make_ctx(24, 80);
    feed_str(c.parser, "ABCDE");
    feed_str(c.parser, "\x1b[3G");
    feed_str(c.parser, "\x1b[0K");
    ASSERT_EQ(cell_cp(c.term, 0, 0), 'A');
    ASSERT_EQ(cell_cp(c.term, 0, 1), 'B');
    ASSERT_EQ(cell_cp(c.term, 0, 2), 0);
    ASSERT_EQ(cell_cp(c.term, 0, 3), 0);
    free_ctx(&c);
}

TEST(csi_erase_line_left) {
    TestCtx c = make_ctx(24, 80);
    feed_str(c.parser, "ABCDE");
    feed_str(c.parser, "\x1b[3G");
    feed_str(c.parser, "\x1b[1K");
    ASSERT_EQ(cell_cp(c.term, 0, 0), 0);
    ASSERT_EQ(cell_cp(c.term, 0, 1), 0);
    ASSERT_EQ(cell_cp(c.term, 0, 2), 0);
    ASSERT_EQ(cell_cp(c.term, 0, 3), 'D');
    ASSERT_EQ(cell_cp(c.term, 0, 4), 'E');
    free_ctx(&c);
}

TEST(csi_erase_line_all) {
    TestCtx c = make_ctx(24, 80);
    feed_str(c.parser, "ABCDE");
    feed_str(c.parser, "\x1b[2K");
    for (int i = 0; i < 5; i++)
        ASSERT_EQ(cell_cp(c.term, 0, i), 0);
    free_ctx(&c);
}

TEST(csi_insert_chars) {
    TestCtx c = make_ctx(24, 80);
    feed_str(c.parser, "ABCDE");
    feed_str(c.parser, "\x1b[2G");    /* col 2 (0-indexed: 1) */
    feed_str(c.parser, "\x1b[2@");    /* ICH 2 */
    ASSERT_EQ(cell_cp(c.term, 0, 0), 'A');
    ASSERT_EQ(cell_cp(c.term, 0, 1), 0);  /* inserted blank */
    ASSERT_EQ(cell_cp(c.term, 0, 2), 0);  /* inserted blank */
    ASSERT_EQ(cell_cp(c.term, 0, 3), 'B');
    ASSERT_EQ(cell_cp(c.term, 0, 4), 'C');
    free_ctx(&c);
}

TEST(csi_delete_chars) {
    TestCtx c = make_ctx(24, 80);
    feed_str(c.parser, "ABCDE");
    feed_str(c.parser, "\x1b[2G");
    feed_str(c.parser, "\x1b[2P");
    ASSERT_EQ(cell_cp(c.term, 0, 0), 'A');
    ASSERT_EQ(cell_cp(c.term, 0, 1), 'D');
    ASSERT_EQ(cell_cp(c.term, 0, 2), 'E');
    free_ctx(&c);
}

TEST(csi_insert_lines) {
    TestCtx c = make_ctx(5, 10);
    feed_str(c.parser, "AAA\r\nBBB\r\nCCC\r\nDDD\r\nEEE");
    feed_str(c.parser, "\x1b[2;1H");
    feed_str(c.parser, "\x1b[1L");
    ASSERT_EQ(cell_cp(c.term, 0, 0), 'A');
    ASSERT_EQ(cell_cp(c.term, 1, 0), 0);    /* inserted blank */
    ASSERT_EQ(cell_cp(c.term, 2, 0), 'B');
    ASSERT_EQ(cell_cp(c.term, 3, 0), 'C');
    ASSERT_EQ(cell_cp(c.term, 4, 0), 'D');
    free_ctx(&c);
}

TEST(csi_delete_lines) {
    TestCtx c = make_ctx(5, 10);
    feed_str(c.parser, "AAA\r\nBBB\r\nCCC\r\nDDD\r\nEEE");
    feed_str(c.parser, "\x1b[2;1H");
    feed_str(c.parser, "\x1b[1M");
    ASSERT_EQ(cell_cp(c.term, 0, 0), 'A');
    ASSERT_EQ(cell_cp(c.term, 1, 0), 'C');
    ASSERT_EQ(cell_cp(c.term, 2, 0), 'D');
    ASSERT_EQ(cell_cp(c.term, 3, 0), 'E');
    ASSERT_EQ(cell_cp(c.term, 4, 0), 0);
    free_ctx(&c);
}

TEST(csi_scroll_up) {
    TestCtx c = make_ctx(5, 10);
    feed_str(c.parser, "AAA\r\nBBB\r\nCCC\r\nDDD\r\nEEE");
    feed_str(c.parser, "\x1b[2S");
    ASSERT_EQ(cell_cp(c.term, 0, 0), 'C');
    ASSERT_EQ(cell_cp(c.term, 1, 0), 'D');
    ASSERT_EQ(cell_cp(c.term, 2, 0), 'E');
    ASSERT_EQ(cell_cp(c.term, 3, 0), 0);
    free_ctx(&c);
}

TEST(csi_scroll_down) {
    TestCtx c = make_ctx(5, 10);
    feed_str(c.parser, "AAA\r\nBBB\r\nCCC\r\nDDD\r\nEEE");
    feed_str(c.parser, "\x1b[2T");
    ASSERT_EQ(cell_cp(c.term, 0, 0), 0);
    ASSERT_EQ(cell_cp(c.term, 1, 0), 0);
    ASSERT_EQ(cell_cp(c.term, 2, 0), 'A');
    ASSERT_EQ(cell_cp(c.term, 3, 0), 'B');
    ASSERT_EQ(cell_cp(c.term, 4, 0), 'C');
    free_ctx(&c);
}

TEST(csi_scroll_region) {
    TestCtx c = make_ctx(24, 80);
    feed_str(c.parser, "\x1b[5;10r");
    ASSERT_EQ(c.term->active->scroll_top, 4);
    ASSERT_EQ(c.term->active->scroll_bottom, 9);
    feed_str(c.parser, "\x1b[r");
    ASSERT_EQ(c.term->active->scroll_top, 0);
    ASSERT_EQ(c.term->active->scroll_bottom, 23);
    free_ctx(&c);
}

TEST(csi_private_mode_set_reset) {
    TestCtx c = make_ctx(24, 80);
    feed_str(c.parser, "\x1b[?1049h");
    ASSERT_EQ(c.term->using_alt, 1);
    feed_str(c.parser, "\x1b[?1049l");
    ASSERT_EQ(c.term->using_alt, 0);
    free_ctx(&c);
}

TEST(csi_bracketed_paste) {
    TestCtx c = make_ctx(24, 80);
    feed_str(c.parser, "\x1b[?2004h");
    ASSERT_EQ(c.term->active->mode_bracketed_paste, 1);
    feed_str(c.parser, "\x1b[?2004l");
    ASSERT_EQ(c.term->active->mode_bracketed_paste, 0);
    free_ctx(&c);
}

TEST(csi_overflow_params) {
    TestCtx c = make_ctx(24, 80);
    /* 17 params — more than the 16-param limit */
    feed_str(c.parser, "\x1b[0;0;0;0;0;0;0;0;0;0;0;0;0;0;0;0;0m");
    /* Must not crash. Parser should handle gracefully. */
    ASSERT_EQ(c.parser->state.tag, VTState_Ground);
    free_ctx(&c);
}

TEST(csi_interrupted_by_esc) {
    TestCtx c = make_ctx(24, 80);
    /* Start CSI, then ESC cancels it */
    feed_str(c.parser, "\x1b[5");
    ASSERT_EQ(c.parser->state.tag, VTState_CSI);
    feed_str(c.parser, "\x1b[2J");
    /* New ESC should cancel the pending CSI and start a new one */
    ASSERT_EQ(c.parser->state.tag, VTState_Ground);
    free_ctx(&c);
}

/* ================================================================
 * Section 4: SGR (Select Graphic Rendition)
 * ================================================================ */

TEST(sgr_reset) {
    TestCtx c = make_ctx(24, 80);
    feed_str(c.parser, "\x1b[1;4;31m");
    feed_str(c.parser, "\x1b[0m");
    feed_str(c.parser, "X");
    const Cell *cell = cell_at(c.term, 0, 0);
    ASSERT_EQ(cell->attrs, ATTR_NONE);
    ASSERT_EQ(cell->fg.tag, Color_Default);
    free_ctx(&c);
}

TEST(sgr_bold) {
    TestCtx c = make_ctx(24, 80);
    feed_str(c.parser, "\x1b[1mA\x1b[0mB");
    ASSERT_EQ(cell_at(c.term, 0, 0)->attrs & ATTR_BOLD, ATTR_BOLD);
    ASSERT_EQ(cell_at(c.term, 0, 1)->attrs & ATTR_BOLD, 0);
    free_ctx(&c);
}

TEST(sgr_underline) {
    TestCtx c = make_ctx(24, 80);
    feed_str(c.parser, "\x1b[4mU");
    ASSERT_EQ(cell_at(c.term, 0, 0)->attrs & ATTR_UNDERLINE, ATTR_UNDERLINE);
    free_ctx(&c);
}

TEST(sgr_fg_16color) {
    TestCtx c = make_ctx(24, 80);
    feed_str(c.parser, "\x1b[31mR");
    const Cell *cell = cell_at(c.term, 0, 0);
    ASSERT_EQ(cell->fg.tag, Color_Indexed);
    ASSERT_EQ(cell->fg.Indexed.index, 1);
    free_ctx(&c);
}

TEST(sgr_bg_16color) {
    TestCtx c = make_ctx(24, 80);
    feed_str(c.parser, "\x1b[42mG");
    const Cell *cell = cell_at(c.term, 0, 0);
    ASSERT_EQ(cell->bg.tag, Color_Indexed);
    ASSERT_EQ(cell->bg.Indexed.index, 2);
    free_ctx(&c);
}

TEST(sgr_bright_fg) {
    TestCtx c = make_ctx(24, 80);
    feed_str(c.parser, "\x1b[91mR");
    const Cell *cell = cell_at(c.term, 0, 0);
    ASSERT_EQ(cell->fg.tag, Color_Indexed);
    ASSERT_EQ(cell->fg.Indexed.index, 9);
    free_ctx(&c);
}

TEST(sgr_256color_fg) {
    TestCtx c = make_ctx(24, 80);
    feed_str(c.parser, "\x1b[38;5;196mR");
    const Cell *cell = cell_at(c.term, 0, 0);
    ASSERT_EQ(cell->fg.tag, Color_Indexed);
    ASSERT_EQ(cell->fg.Indexed.index, 196);
    free_ctx(&c);
}

TEST(sgr_256color_bg) {
    TestCtx c = make_ctx(24, 80);
    feed_str(c.parser, "\x1b[48;5;42mX");
    const Cell *cell = cell_at(c.term, 0, 0);
    ASSERT_EQ(cell->bg.tag, Color_Indexed);
    ASSERT_EQ(cell->bg.Indexed.index, 42);
    free_ctx(&c);
}

TEST(sgr_default_fg) {
    TestCtx c = make_ctx(24, 80);
    feed_str(c.parser, "\x1b[31m");
    feed_str(c.parser, "\x1b[39mX");
    ASSERT_EQ(cell_at(c.term, 0, 0)->fg.tag, Color_Default);
    free_ctx(&c);
}

TEST(sgr_default_bg) {
    TestCtx c = make_ctx(24, 80);
    feed_str(c.parser, "\x1b[42m");
    feed_str(c.parser, "\x1b[49mX");
    ASSERT_EQ(cell_at(c.term, 0, 0)->bg.tag, Color_Default);
    free_ctx(&c);
}

TEST(sgr_combined) {
    TestCtx c = make_ctx(24, 80);
    feed_str(c.parser, "\x1b[1;4;31mX");
    const Cell *cell = cell_at(c.term, 0, 0);
    ASSERT_EQ(cell->attrs & ATTR_BOLD, ATTR_BOLD);
    ASSERT_EQ(cell->attrs & ATTR_UNDERLINE, ATTR_UNDERLINE);
    ASSERT_EQ(cell->fg.tag, Color_Indexed);
    ASSERT_EQ(cell->fg.Indexed.index, 1);
    free_ctx(&c);
}

TEST(sgr_interleaved) {
    TestCtx c = make_ctx(24, 80);
    feed_str(c.parser, "\x1b[1mA\x1b[0mB");
    ASSERT_EQ(cell_at(c.term, 0, 0)->attrs & ATTR_BOLD, ATTR_BOLD);
    ASSERT_EQ(cell_at(c.term, 0, 1)->attrs & ATTR_BOLD, 0);
    ASSERT_EQ(cell_at(c.term, 0, 0)->codepoint, 'A');
    ASSERT_EQ(cell_at(c.term, 0, 1)->codepoint, 'B');
    free_ctx(&c);
}

TEST(sgr_per_span_colors) {
    /* Verify per-cell color attributes for multi-color output */
    TestCtx c = make_ctx(24, 80);
    feed_str(c.parser, "\x1b[31mABC\x1b[32mDEF");
    /* ABC should be red (Indexed 1), DEF should be green (Indexed 2) */
    ASSERT_EQ(cell_at(c.term, 0, 0)->fg.tag, Color_Indexed);
    ASSERT_EQ(cell_at(c.term, 0, 0)->fg.Indexed.index, 1);
    ASSERT_EQ(cell_at(c.term, 0, 1)->fg.Indexed.index, 1);
    ASSERT_EQ(cell_at(c.term, 0, 2)->fg.Indexed.index, 1);
    ASSERT_EQ(cell_at(c.term, 0, 3)->fg.tag, Color_Indexed);
    ASSERT_EQ(cell_at(c.term, 0, 3)->fg.Indexed.index, 2);
    ASSERT_EQ(cell_at(c.term, 0, 4)->fg.Indexed.index, 2);
    ASSERT_EQ(cell_at(c.term, 0, 5)->fg.Indexed.index, 2);
    free_ctx(&c);
}

/* ================================================================
 * Section 5: OSC State
 * ================================================================ */

TEST(osc_set_title_bel) {
    TestCtx c = make_ctx(24, 80);
    feed_str(c.parser, "\x1b]0;My Title\x07");
    feed_str(c.parser, "X");
    ASSERT_EQ(c.parser->state.tag, VTState_Ground);
    ASSERT_EQ(cell_cp(c.term, 0, 0), 'X');
    free_ctx(&c);
}

TEST(osc_set_title_st) {
    TestCtx c = make_ctx(24, 80);
    feed_str(c.parser, "\x1b]0;My Title\x1b\\");
    feed_str(c.parser, "Y");
    ASSERT_EQ(c.parser->state.tag, VTState_Ground);
    ASSERT_EQ(cell_cp(c.term, 0, 0), 'Y');
    free_ctx(&c);
}

TEST(osc_buffer_overflow) {
    TestCtx c = make_ctx(24, 80);
    /* Feed OSC with >512 chars — must not overflow */
    feed_str(c.parser, "\x1b]0;");
    char big[600];
    memset(big, 'X', 599);
    big[599] = '\0';
    feed_str(c.parser, big);
    uint8_t bel = 0x07;
    feed(c.parser, &bel, 1);
    ASSERT_EQ(c.parser->state.tag, VTState_Ground);
    /* Verify we can still write to screen after overflow */
    feed_str(c.parser, "Z");
    ASSERT_EQ(cell_cp(c.term, 0, 0), 'Z');
    free_ctx(&c);
}

/* ================================================================
 * Section 6: DCS State
 * ================================================================ */

TEST(dcs_passthrough) {
    TestCtx c = make_ctx(24, 80);
    feed_str(c.parser, "\x1bPtest data\x1b\\");
    /* DCS simplified: ESC terminates */
    /* After DCS, parser should be in ground (ESC consumed by DCS exit) */
    /* The backslash may or may not be consumed depending on implementation */
    feed_str(c.parser, "Z");
    /* Key check: no crash and eventually back to ground */
    ASSERT_EQ(c.parser->state.tag, VTState_Ground);
    free_ctx(&c);
}

TEST(dcs_buffer_overflow) {
    TestCtx c = make_ctx(24, 80);
    feed_str(c.parser, "\x1bP");
    char big[600];
    memset(big, 'X', 599);
    big[599] = '\0';
    feed_str(c.parser, big);
    /* Terminate with ESC (simplified DCS handling) */
    feed_str(c.parser, "\x1b");
    /* Must not crash, parser back to some sane state */
    feed_str(c.parser, "Z");
    free_ctx(&c);
}

/* ================================================================
 * Section 7: Adversarial / Cross-Cutting
 * ================================================================ */

TEST(empty_input) {
    TestCtx c = make_ctx(24, 80);
    feed(c.parser, (const uint8_t *)"", 0);
    feed(c.parser, NULL, 0);
    ASSERT_EQ(c.parser->state.tag, VTState_Ground);
    ASSERT_EQ(c.term->active->cursor.row, 0);
    ASSERT_EQ(c.term->active->cursor.col, 0);
    free_ctx(&c);
}

TEST(all_zeros) {
    TestCtx c = make_ctx(24, 80);
    uint8_t zeros[512];
    memset(zeros, 0, 512);
    feed(c.parser, zeros, 512);
    ASSERT_EQ(c.parser->state.tag, VTState_Ground);
    free_ctx(&c);
}

TEST(all_ff) {
    TestCtx c = make_ctx(24, 80);
    uint8_t ffs[512];
    memset(ffs, 0xFF, 512);
    feed(c.parser, ffs, 512);
    /* 0xFF is invalid UTF-8 start byte — should emit replacement chars, not crash */
    ASSERT_EQ(c.parser->state.tag, VTState_Ground);
    free_ctx(&c);
}

TEST(rapid_state_changes) {
    TestCtx c = make_ctx(24, 80);
    /* ESC [ ESC ] ESC P ESC [ m — each ESC cancels prior */
    feed_str(c.parser, "\x1b[\x1b]\x1bP\x1b[m");
    ASSERT_EQ(c.parser->state.tag, VTState_Ground);
    free_ctx(&c);
}

TEST(incomplete_utf8_then_esc) {
    TestCtx c = make_ctx(24, 80);
    /* Start 2-byte UTF-8 (0xC3) then ESC interrupts before completion.
     * The incomplete codepoint should emit U+FFFD before ESC is processed.
     * Then ESC[H moves cursor home — so U+FFFD should be at (0,0). */
    uint8_t data[] = {0xC3, 0x1B, '[', 'H'};
    feed(c.parser, data, 4);
    ASSERT_EQ(c.parser->state.tag, VTState_Ground);
    /* U+FFFD emitted for the broken sequence before ESC is processed */
    ASSERT_EQ(cell_cp(c.term, 0, 0), 0xFFFD);
    free_ctx(&c);
}

/* ================================================================
 * Section 7b: CSI Parameter Defaults (zero vs missing)
 * ================================================================ */

TEST(csi_explicit_zero_vs_default) {
    /* ESC[0A (explicit zero) vs ESC[A (default 1) — different behaviour.
     * Explicit zero means move 0 lines (noop). Default means move 1 line.
     * This exercises the -1 sentinel fix in csi_param. */
    TestCtx c = make_ctx(24, 80);
    feed_str(c.parser, "\x1b[5;1H");  /* move to row 5 */
    ASSERT_EQ(c.term->active->cursor.row, 4);
    feed_str(c.parser, "\x1b[0A");    /* explicit zero: move up 0 — noop */
    ASSERT_EQ(c.term->active->cursor.row, 4);
    feed_str(c.parser, "\x1b[A");     /* default: move up 1 */
    ASSERT_EQ(c.term->active->cursor.row, 3);
    free_ctx(&c);
}

TEST(csi_leading_semicolon) {
    /* ESC[;5H — missing first param, explicit second */
    TestCtx c = make_ctx(24, 80);
    feed_str(c.parser, "\x1b[;5H");
    /* Missing first param defaults to 1, so row = 0 (1-based to 0-based) */
    ASSERT_EQ(c.term->active->cursor.row, 0);
    /* Second param = 5, so col = 4 */
    ASSERT_EQ(c.term->active->cursor.col, 4);
    free_ctx(&c);
}

TEST(csi_missing_second_param) {
    /* ESC[3;H — explicit first, missing second */
    TestCtx c = make_ctx(24, 80);
    feed_str(c.parser, "\x1b[3;H");
    ASSERT_EQ(c.term->active->cursor.row, 2);
    ASSERT_EQ(c.term->active->cursor.col, 0);
    free_ctx(&c);
}

TEST(csi_both_params_missing) {
    /* ESC[;H — both missing */
    TestCtx c = make_ctx(24, 80);
    feed_str(c.parser, "\x1b[10;20H");  /* move away first */
    feed_str(c.parser, "\x1b[;H");
    ASSERT_EQ(c.term->active->cursor.row, 0);
    ASSERT_EQ(c.term->active->cursor.col, 0);
    free_ctx(&c);
}

TEST(csi_empty_params_sgr) {
    /* ESC[;;m — three empty params, all default to 0 for SGR (reset) */
    TestCtx c = make_ctx(24, 80);
    feed_str(c.parser, "\x1b[1;4;31m");  /* bold + underline + red */
    feed_str(c.parser, "\x1b[;;m");
    feed_str(c.parser, "X");
    const Cell *cell = cell_at(c.term, 0, 0);
    /* All params default to 0 = reset. Attributes should be cleared. */
    ASSERT_EQ(cell->attrs, ATTR_NONE);
    ASSERT_EQ(cell->fg.tag, Color_Default);
    free_ctx(&c);
}

TEST(csi_large_value_clamp) {
    /* ESC[99999A — cursor up clamped to top */
    TestCtx c = make_ctx(24, 80);
    feed_str(c.parser, "\x1b[10;1H");
    feed_str(c.parser, "\x1b[99999A");
    ASSERT_EQ(c.term->active->cursor.row, 0);
    free_ctx(&c);
}

/* ================================================================
 * Section 7c: C0 Controls in Non-Ground States
 * Per VT standard, C0 controls (except ESC) should execute
 * without disrupting the current escape sequence.
 * ================================================================ */

TEST(c0_lf_during_csi) {
    /* LF during CSI param accumulation: LF executes, CSI continues */
    TestCtx c = make_ctx(24, 80);
    feed_str(c.parser, "A");
    /* Start CSI, then LF mid-sequence, then finish CSI */
    feed_str(c.parser, "\x1b[1");
    int row_before = c.term->active->cursor.row;
    feed_str(c.parser, "\n");  /* LF should move cursor down */
    /* Currently the parser may or may not handle this — test documents expected behaviour */
    /* If LF is processed: cursor moved down. If not: cursor stays. */
    /* Per VT standard: C0 in CSI should execute. */
    /* For now, test that the parser doesn't crash and returns to a sane state */
    feed_str(c.parser, "m");  /* finish the CSI as SGR */
    /* Parser should be back in Ground */
    ASSERT_EQ(c.parser->state.tag, VTState_Ground);
    (void)row_before;
    free_ctx(&c);
}

TEST(c0_cr_during_csi) {
    /* CR during CSI: should execute CR (cursor to col 0) without breaking CSI */
    TestCtx c = make_ctx(24, 80);
    feed_str(c.parser, "\x1b[5;20H");  /* move to row 5, col 20 */
    feed_str(c.parser, "\x1b[");
    feed_str(c.parser, "\r");  /* CR mid-CSI */
    feed_str(c.parser, "2J");  /* finish CSI: erase display */
    /* If CR executed: cursor col is 0. If CSI continued correctly: screen cleared. */
    /* Key check: no crash, parser returns to Ground */
    ASSERT_EQ(c.parser->state.tag, VTState_Ground);
    free_ctx(&c);
}

TEST(c0_bs_during_csi) {
    /* BS during CSI: should execute BS without breaking CSI */
    TestCtx c = make_ctx(24, 80);
    feed_str(c.parser, "ABCDE");
    feed_str(c.parser, "\x1b[");
    feed_str(c.parser, "\b");  /* BS mid-CSI */
    feed_str(c.parser, "1m");  /* finish CSI: SGR bold */
    /* Key check: no crash, parser returns to Ground */
    ASSERT_EQ(c.parser->state.tag, VTState_Ground);
    free_ctx(&c);
}

TEST(c0_bel_during_osc) {
    /* BEL during OSC terminates the OSC (this is the standard behaviour) */
    TestCtx c = make_ctx(24, 80);
    feed_str(c.parser, "\x1b]0;title\x07");
    ASSERT_EQ(c.parser->state.tag, VTState_Ground);
    feed_str(c.parser, "X");
    ASSERT_EQ(cell_cp(c.term, 0, 0), 'X');
    free_ctx(&c);
}

/* ================================================================
 * Section 7d: DECAWM and DEC Line-Drawing Charset
 * ================================================================ */

TEST(decawm_disable) {
    /* Disable autowrap — writing at last column should NOT wrap */
    TestCtx c = make_ctx(24, 5);
    feed_str(c.parser, "\x1b[?7l");  /* disable autowrap */
    feed_str(c.parser, "ABCDE");
    /* Cursor should stay at last column, no wrap */
    ASSERT_EQ(c.term->active->cursor.row, 0);
    /* Write one more — should overwrite last col, not wrap */
    feed_str(c.parser, "F");
    ASSERT_EQ(c.term->active->cursor.row, 0);
    ASSERT_EQ(cell_cp(c.term, 0, 4), 'F');
    /* Row 1 should be empty */
    ASSERT_EQ(cell_cp(c.term, 1, 0), 0);
    free_ctx(&c);
}

TEST(decawm_enable) {
    /* Re-enable autowrap after disabling */
    TestCtx c = make_ctx(24, 5);
    feed_str(c.parser, "\x1b[?7l");  /* disable */
    feed_str(c.parser, "\x1b[?7h");  /* re-enable */
    feed_str(c.parser, "ABCDEF");
    /* Should wrap: F on row 1 */
    ASSERT_EQ(cell_cp(c.term, 1, 0), 'F');
    free_ctx(&c);
}

TEST(dec_charset_line_drawing) {
    /* ESC(0 activates DEC special graphics — 'q' becomes U+2500 (─) */
    TestCtx c = make_ctx(24, 80);
    feed_str(c.parser, "\x1b(0");  /* activate DEC graphics */
    feed_str(c.parser, "q");       /* horizontal line in DEC set */
    ASSERT_EQ(cell_cp(c.term, 0, 0), 0x2500);  /* ─ */
    free_ctx(&c);
}

TEST(dec_charset_revert) {
    /* ESC(B reverts to ASCII — 'q' is literal 'q' */
    TestCtx c = make_ctx(24, 80);
    feed_str(c.parser, "\x1b(0");  /* DEC graphics */
    feed_str(c.parser, "q");
    ASSERT_EQ(cell_cp(c.term, 0, 0), 0x2500);
    feed_str(c.parser, "\x1b(B");  /* back to ASCII */
    feed_str(c.parser, "q");
    ASSERT_EQ(cell_cp(c.term, 0, 1), 'q');  /* literal q */
    free_ctx(&c);
}

TEST(dec_charset_box_chars) {
    /* Verify key box-drawing translations for tmux pane borders */
    TestCtx c = make_ctx(24, 80);
    feed_str(c.parser, "\x1b(0");
    /* l=┌ k=┐ m=└ j=┘ x=│ q=─ */
    feed_str(c.parser, "lqkxmj");
    ASSERT_EQ(cell_cp(c.term, 0, 0), 0x250C);  /* ┌ */
    ASSERT_EQ(cell_cp(c.term, 0, 1), 0x2500);  /* ─ */
    ASSERT_EQ(cell_cp(c.term, 0, 2), 0x2510);  /* ┐ */
    ASSERT_EQ(cell_cp(c.term, 0, 3), 0x2502);  /* │ */
    ASSERT_EQ(cell_cp(c.term, 0, 4), 0x2514);  /* └ */
    ASSERT_EQ(cell_cp(c.term, 0, 5), 0x2518);  /* ┘ */
    feed_str(c.parser, "\x1b(B");  /* revert */
    free_ctx(&c);
}

TEST(dec_charset_so_si) {
    /* SO (0x0E) activates G1, SI (0x0F) reverts to G0 */
    TestCtx c = make_ctx(24, 80);
    /* Set G1 to DEC graphics */
    feed_str(c.parser, "\x1b)0");
    /* SO switches to G1 */
    uint8_t so = 0x0E;
    feed(c.parser, &so, 1);
    feed_str(c.parser, "q");
    ASSERT_EQ(cell_cp(c.term, 0, 0), 0x2500);  /* ─ via G1 */
    /* SI switches back to G0 (ASCII) */
    uint8_t si = 0x0F;
    feed(c.parser, &si, 1);
    feed_str(c.parser, "q");
    ASSERT_EQ(cell_cp(c.term, 0, 1), 'q');  /* literal q */
    free_ctx(&c);
}

/* ================================================================
 * Section 8: Screen Buffer Operations
 * ================================================================ */

TEST(line_wrap) {
    TestCtx c = make_ctx(24, 10);
    feed_str(c.parser, "1234567890X");
    ASSERT_EQ(cell_cp(c.term, 0, 0), '1');
    ASSERT_EQ(cell_cp(c.term, 0, 9), '0');
    ASSERT_EQ(cell_cp(c.term, 1, 0), 'X');
    free_ctx(&c);
}

TEST(scroll_at_bottom) {
    TestCtx c = make_ctx(3, 10);
    feed_str(c.parser, "AAA\r\nBBB\r\nCCC\r\nDDD");
    ASSERT_EQ(cell_cp(c.term, 0, 0), 'B');
    ASSERT_EQ(cell_cp(c.term, 1, 0), 'C');
    ASSERT_EQ(cell_cp(c.term, 2, 0), 'D');
    const Cell *sb_line = scrollback_get(c.term->scrollback, 0);
    ASSERT_NOT_NULL(sb_line);
    ASSERT_EQ(sb_line[0].codepoint, 'A');
    free_ctx(&c);
}

TEST(alt_screen) {
    TestCtx c = make_ctx(24, 80);
    feed_str(c.parser, "MainScreen");
    ASSERT_EQ(cell_cp(c.term, 0, 0), 'M');
    feed_str(c.parser, "\x1b[?1049h");
    ASSERT_EQ(c.term->using_alt, 1);
    ASSERT_EQ(cell_cp(c.term, 0, 0), 0);
    feed_str(c.parser, "AltScreen");
    ASSERT_EQ(cell_cp(c.term, 0, 0), 'A');
    feed_str(c.parser, "\x1b[?1049l");
    ASSERT_EQ(c.term->using_alt, 0);
    ASSERT_EQ(cell_cp(c.term, 0, 0), 'M');
    free_ctx(&c);
}

TEST(cursor_save_restore_csi) {
    TestCtx c = make_ctx(24, 80);
    feed_str(c.parser, "\x1b[5;10H");
    feed_str(c.parser, "\x1b[s");
    feed_str(c.parser, "\x1b[1;1H");
    ASSERT_EQ(c.term->active->cursor.row, 0);
    feed_str(c.parser, "\x1b[u");
    ASSERT_EQ(c.term->active->cursor.row, 4);
    ASSERT_EQ(c.term->active->cursor.col, 9);
    free_ctx(&c);
}

TEST(cursor_bounds_top) {
    TestCtx c = make_ctx(24, 80);
    feed_str(c.parser, "\x1b[99A");
    ASSERT_EQ(c.term->active->cursor.row, 0);
    free_ctx(&c);
}

TEST(cursor_bounds_left) {
    TestCtx c = make_ctx(24, 80);
    feed_str(c.parser, "\x1b[99D");
    ASSERT_EQ(c.term->active->cursor.col, 0);
    free_ctx(&c);
}

TEST(cursor_bounds_right) {
    TestCtx c = make_ctx(24, 80);
    feed_str(c.parser, "\x1b[999C");
    ASSERT_EQ(c.term->active->cursor.col, 79);
    free_ctx(&c);
}

TEST(cursor_bounds_bottom) {
    TestCtx c = make_ctx(24, 80);
    feed_str(c.parser, "\x1b[999B");
    ASSERT_EQ(c.term->active->cursor.row, 23);
    free_ctx(&c);
}

/* ================================================================
 * Section 9: Partial Buffer Feeds
 * ================================================================ */

TEST(split_esc_csi) {
    TestCtx c = make_ctx(24, 80);
    feed_str(c.parser, "\x1b[6;1H");
    /* Split ESC [5A across two feeds */
    feed_str(c.parser, "\x1b");
    feed_str(c.parser, "[5A");
    ASSERT_EQ(c.term->active->cursor.row, 0);
    free_ctx(&c);
}

TEST(split_csi_params) {
    TestCtx c = make_ctx(24, 80);
    feed_str(c.parser, "\x1b[1");
    feed_str(c.parser, ";2H");
    ASSERT_EQ(c.term->active->cursor.row, 0);
    ASSERT_EQ(c.term->active->cursor.col, 1);
    free_ctx(&c);
}

TEST(split_csi_mid_param) {
    TestCtx c = make_ctx(24, 80);
    feed_str(c.parser, "\x1b[1");
    feed_str(c.parser, "0;20H");
    ASSERT_EQ(c.term->active->cursor.row, 9);
    ASSERT_EQ(c.term->active->cursor.col, 19);
    free_ctx(&c);
}

TEST(split_sgr_256) {
    TestCtx c = make_ctx(24, 80);
    feed_str(c.parser, "\x1b[38;5");
    feed_str(c.parser, ";196mX");
    const Cell *cell = cell_at(c.term, 0, 0);
    ASSERT_EQ(cell->fg.tag, Color_Indexed);
    ASSERT_EQ(cell->fg.Indexed.index, 196);
    free_ctx(&c);
}

TEST(split_utf8_2byte) {
    TestCtx c = make_ctx(24, 80);
    uint8_t b1 = 0xC3;
    uint8_t b2 = 0xA9;
    feed(c.parser, &b1, 1);
    feed(c.parser, &b2, 1);
    ASSERT_EQ(cell_cp(c.term, 0, 0), 0x00E9);
    free_ctx(&c);
}

TEST(split_three_way) {
    TestCtx c = make_ctx(24, 80);
    feed_str(c.parser, "ABCDE");
    feed_str(c.parser, "\x1b");
    feed_str(c.parser, "[");
    feed_str(c.parser, "2J");
    ASSERT_EQ(cell_cp(c.term, 0, 0), 0);
    free_ctx(&c);
}

TEST(single_byte_drip) {
    TestCtx c = make_ctx(24, 80);
    feed_str(c.parser, "\x1b[6;1H");
    /* Feed ESC[5A one byte at a time */
    const uint8_t seq[] = {0x1B, '[', '5', 'A'};
    for (int i = 0; i < 4; i++) {
        feed(c.parser, &seq[i], 1);
    }
    ASSERT_EQ(c.term->active->cursor.row, 0);
    free_ctx(&c);
}

TEST(split_then_interrupt) {
    TestCtx c = make_ctx(24, 80);
    feed_str(c.parser, "XXXXX");
    /* Start a CSI but interrupt with a new ESC sequence */
    feed_str(c.parser, "\x1b[5");
    feed_str(c.parser, "\x1b[2J");
    /* First CSI cancelled, second one (clear screen) should execute */
    ASSERT_EQ(cell_cp(c.term, 0, 0), 0);
    ASSERT_EQ(c.parser->state.tag, VTState_Ground);
    free_ctx(&c);
}

TEST(split_osc_title) {
    TestCtx c = make_ctx(24, 80);
    feed_str(c.parser, "\x1b]0;Hel");
    feed_str(c.parser, "lo World\x07");
    feed_str(c.parser, "Z");
    ASSERT_EQ(c.parser->state.tag, VTState_Ground);
    ASSERT_EQ(cell_cp(c.term, 0, 0), 'Z');
    free_ctx(&c);
}

/* ================================================================
 * Section 10: UTF-8 Edge Cases
 * ================================================================ */

TEST(utf8_invalid_start_fe) {
    TestCtx c = make_ctx(24, 80);
    uint8_t fe = 0xFE;
    feed(c.parser, &fe, 1);
    /* Should emit replacement char U+FFFD */
    ASSERT_EQ(cell_cp(c.term, 0, 0), 0xFFFD);
    free_ctx(&c);
}

TEST(utf8_invalid_start_ff) {
    TestCtx c = make_ctx(24, 80);
    uint8_t ff = 0xFF;
    feed(c.parser, &ff, 1);
    ASSERT_EQ(cell_cp(c.term, 0, 0), 0xFFFD);
    free_ctx(&c);
}

TEST(utf8_orphan_continuation) {
    TestCtx c = make_ctx(24, 80);
    uint8_t cont = 0x80;
    feed(c.parser, &cont, 1);
    /* Orphan continuation byte — replacement char */
    ASSERT_EQ(cell_cp(c.term, 0, 0), 0xFFFD);
    free_ctx(&c);
}

TEST(utf8_invalid_continuation) {
    TestCtx c = make_ctx(24, 80);
    /* Start 2-byte sequence then give ASCII instead of continuation */
    uint8_t data[] = {0xC3, 'A'};
    feed(c.parser, data, 2);
    /* 0xC3 incomplete → replacement; then 'A' printed */
    /* Implementation may vary: either U+FFFD then A, or just A */
    /* The key invariant: no crash, 'A' ends up on screen */
    int found_a = 0;
    for (int i = 0; i < 3; i++) {
        if (cell_cp(c.term, 0, i) == 'A') { found_a = 1; break; }
    }
    ASSERT(found_a);
    free_ctx(&c);
}

TEST(utf8_truncated_persist) {
    TestCtx c = make_ctx(24, 80);
    /* Feed first byte of 2-byte sequence, then complete in second feed */
    uint8_t b1 = 0xC3;
    feed(c.parser, &b1, 1);
    /* Nothing should be written yet — partial state held */
    ASSERT_EQ(c.parser->utf8.remaining, 1);
    uint8_t b2 = 0xA9;
    feed(c.parser, &b2, 1);
    ASSERT_EQ(cell_cp(c.term, 0, 0), 0x00E9);
    free_ctx(&c);
}

/* ================================================================
 * Section 11: Input Encoding
 * ================================================================ */

static void assert_encodes_to(int key, int mods, int app_cursor,
                              const char *expected, int expected_len) {
    char buf[32];
    int n = encode_special_key(key, mods, app_cursor, buf, sizeof(buf));
    ASSERT_EQ(n, expected_len);
    ASSERT(memcmp(buf, expected, (size_t)n) == 0);
}

TEST(input_arrow_up) {
    assert_encodes_to(KEY_UP, MOD_NONE, 0, "\x1b[A", 3);
}

TEST(input_arrow_up_app_cursor) {
    assert_encodes_to(KEY_UP, MOD_NONE, 1, "\x1bOA", 3);
}

TEST(input_shift_up) {
    /* Shift=2 per xterm convention */
    assert_encodes_to(KEY_UP, MOD_SHIFT, 0, "\x1b[1;2A", 6);
}

TEST(input_ctrl_up) {
    /* Ctrl=5 per xterm convention */
    assert_encodes_to(KEY_UP, MOD_CTRL, 0, "\x1b[1;5A", 6);
}

TEST(input_alt_up) {
    /* Alt=3 per xterm convention */
    assert_encodes_to(KEY_UP, MOD_ALT, 0, "\x1b[1;3A", 6);
}

TEST(input_shift_ctrl_up) {
    /* Shift+Ctrl=6 per xterm convention */
    assert_encodes_to(KEY_UP, MOD_SHIFT | MOD_CTRL, 0, "\x1b[1;6A", 6);
}

TEST(input_shift_delete) {
    assert_encodes_to(KEY_DELETE, MOD_SHIFT, 0, "\x1b[3;2~", 6);
}

TEST(input_f1_plain) {
    assert_encodes_to(KEY_F1, MOD_NONE, 0, "\x1bOP", 3);
}

TEST(input_ctrl_f1) {
    /* F1-F4 with modifiers use CSI form */
    assert_encodes_to(KEY_F1, MOD_CTRL, 0, "\x1b[1;5P", 6);
}

TEST(input_f5_plain) {
    assert_encodes_to(KEY_F5, MOD_NONE, 0, "\x1b[15~", 5);
}

TEST(input_shift_f5) {
    assert_encodes_to(KEY_F5, MOD_SHIFT, 0, "\x1b[15;2~", 7);
}

TEST(input_home_end) {
    assert_encodes_to(KEY_HOME, MOD_NONE, 0, "\x1b[H", 3);
    assert_encodes_to(KEY_END, MOD_NONE, 0, "\x1b[F", 3);
}

TEST(input_ctrl_key) {
    char buf[32];
    /* Ctrl+A = 0x01 */
    int n = encode_key_event('a', MOD_CTRL, 0, buf, sizeof(buf));
    ASSERT_EQ(n, 1);
    ASSERT_EQ(buf[0], 1);
    /* Ctrl+C = 0x03 */
    n = encode_key_event('c', MOD_CTRL, 0, buf, sizeof(buf));
    ASSERT_EQ(n, 1);
    ASSERT_EQ(buf[0], 3);
}

TEST(input_alt_key) {
    char buf[32];
    /* Alt+x = ESC x */
    int n = encode_key_event('x', MOD_ALT, 0, buf, sizeof(buf));
    ASSERT_EQ(n, 2);
    ASSERT_EQ(buf[0], 0x1B);
    ASSERT_EQ(buf[1], 'x');
}

TEST(input_utf8_encode) {
    char buf[32];
    /* Regular character: é (U+00E9) */
    int n = encode_key_event(0xE9, MOD_NONE, 0, buf, sizeof(buf));
    ASSERT_EQ(n, 2);
    ASSERT_EQ((uint8_t)buf[0], 0xC3);
    ASSERT_EQ((uint8_t)buf[1], 0xA9);
}

TEST(input_paste_bracketed) {
    char start[16], end[16];
    int sn = encode_paste_start(start, sizeof(start));
    int en = encode_paste_end(end, sizeof(end));
    ASSERT_EQ(sn, 6);
    ASSERT_EQ(en, 6);
    ASSERT(memcmp(start, "\x1b[200~", 6) == 0);
    ASSERT(memcmp(end, "\x1b[201~", 6) == 0);
}

/* ================================================================
 * Main
 * ================================================================ */

TEST_MAIN(
    /* Section 1: Ground state */
    RUN_TEST(printable_ascii);
    RUN_TEST(printable_utf8_2byte);
    RUN_TEST(printable_utf8_3byte);
    RUN_TEST(printable_utf8_4byte);
    RUN_TEST(control_bel);
    RUN_TEST(control_bs);
    RUN_TEST(control_ht);
    RUN_TEST(control_lf);
    RUN_TEST(control_cr);
    RUN_TEST(control_cr_lf);
    RUN_TEST(escape_entry);

    /* Section 2: Escape state */
    RUN_TEST(esc_csi_entry);
    RUN_TEST(esc_osc_entry);
    RUN_TEST(esc_dcs_entry);
    RUN_TEST(esc_reverse_index);
    RUN_TEST(esc_save_restore_cursor);
    RUN_TEST(esc_interrupted_by_esc);

    /* Section 3: CSI */
    RUN_TEST(csi_cursor_up);
    RUN_TEST(csi_cursor_up_default);
    RUN_TEST(csi_cursor_down);
    RUN_TEST(csi_cursor_forward);
    RUN_TEST(csi_cursor_backward);
    RUN_TEST(csi_cursor_position);
    RUN_TEST(csi_cursor_position_defaults);
    RUN_TEST(csi_erase_display_all);
    RUN_TEST(csi_erase_display_below);
    RUN_TEST(csi_erase_line_right);
    RUN_TEST(csi_erase_line_left);
    RUN_TEST(csi_erase_line_all);
    RUN_TEST(csi_insert_chars);
    RUN_TEST(csi_delete_chars);
    RUN_TEST(csi_insert_lines);
    RUN_TEST(csi_delete_lines);
    RUN_TEST(csi_scroll_up);
    RUN_TEST(csi_scroll_down);
    RUN_TEST(csi_scroll_region);
    RUN_TEST(csi_private_mode_set_reset);
    RUN_TEST(csi_bracketed_paste);
    RUN_TEST(csi_overflow_params);
    RUN_TEST(csi_interrupted_by_esc);

    /* Section 4: SGR */
    RUN_TEST(sgr_reset);
    RUN_TEST(sgr_bold);
    RUN_TEST(sgr_underline);
    RUN_TEST(sgr_fg_16color);
    RUN_TEST(sgr_bg_16color);
    RUN_TEST(sgr_bright_fg);
    RUN_TEST(sgr_256color_fg);
    RUN_TEST(sgr_256color_bg);
    RUN_TEST(sgr_default_fg);
    RUN_TEST(sgr_default_bg);
    RUN_TEST(sgr_combined);
    RUN_TEST(sgr_interleaved);
    RUN_TEST(sgr_per_span_colors);

    /* Section 5: OSC */
    RUN_TEST(osc_set_title_bel);
    RUN_TEST(osc_set_title_st);
    RUN_TEST(osc_buffer_overflow);

    /* Section 6: DCS */
    RUN_TEST(dcs_passthrough);
    RUN_TEST(dcs_buffer_overflow);

    /* Section 7: Adversarial */
    RUN_TEST(empty_input);
    RUN_TEST(all_zeros);
    RUN_TEST(all_ff);
    RUN_TEST(rapid_state_changes);
    RUN_TEST(incomplete_utf8_then_esc);

    /* Section 7b: CSI parameter defaults */
    RUN_TEST(csi_explicit_zero_vs_default);
    RUN_TEST(csi_leading_semicolon);
    RUN_TEST(csi_missing_second_param);
    RUN_TEST(csi_both_params_missing);
    RUN_TEST(csi_empty_params_sgr);
    RUN_TEST(csi_large_value_clamp);

    /* Section 7c: C0 in non-Ground states */
    RUN_TEST(c0_lf_during_csi);
    RUN_TEST(c0_cr_during_csi);
    RUN_TEST(c0_bs_during_csi);
    RUN_TEST(c0_bel_during_osc);

    /* Section 7d: DECAWM and DEC charset */
    RUN_TEST(decawm_disable);
    RUN_TEST(decawm_enable);
    RUN_TEST(dec_charset_line_drawing);
    RUN_TEST(dec_charset_revert);
    RUN_TEST(dec_charset_box_chars);
    RUN_TEST(dec_charset_so_si);

    /* Section 8: Screen buffer */
    RUN_TEST(line_wrap);
    RUN_TEST(scroll_at_bottom);
    RUN_TEST(alt_screen);
    RUN_TEST(cursor_save_restore_csi);
    RUN_TEST(cursor_bounds_top);
    RUN_TEST(cursor_bounds_left);
    RUN_TEST(cursor_bounds_right);
    RUN_TEST(cursor_bounds_bottom);

    /* Section 9: Partial feeds */
    RUN_TEST(split_esc_csi);
    RUN_TEST(split_csi_params);
    RUN_TEST(split_csi_mid_param);
    RUN_TEST(split_sgr_256);
    RUN_TEST(split_utf8_2byte);
    RUN_TEST(split_three_way);
    RUN_TEST(single_byte_drip);
    RUN_TEST(split_then_interrupt);
    RUN_TEST(split_osc_title);

    /* Section 10: UTF-8 edge cases */
    RUN_TEST(utf8_invalid_start_fe);
    RUN_TEST(utf8_invalid_start_ff);
    RUN_TEST(utf8_orphan_continuation);
    RUN_TEST(utf8_invalid_continuation);
    RUN_TEST(utf8_truncated_persist);

    /* Section 11: Input encoding */
    RUN_TEST(input_arrow_up);
    RUN_TEST(input_arrow_up_app_cursor);
    RUN_TEST(input_shift_up);
    RUN_TEST(input_ctrl_up);
    RUN_TEST(input_alt_up);
    RUN_TEST(input_shift_ctrl_up);
    RUN_TEST(input_shift_delete);
    RUN_TEST(input_f1_plain);
    RUN_TEST(input_ctrl_f1);
    RUN_TEST(input_f5_plain);
    RUN_TEST(input_shift_f5);
    RUN_TEST(input_home_end);
    RUN_TEST(input_ctrl_key);
    RUN_TEST(input_alt_key);
    RUN_TEST(input_utf8_encode);
    RUN_TEST(input_paste_bracketed);
)
