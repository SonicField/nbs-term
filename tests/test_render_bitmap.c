/*
 * test_render_bitmap.c — Unit tests for pixel-buffer rendering
 *
 * TDD tests for the PhotoImage renderer: glyph compositing,
 * screen-to-pixel rendering, and PPM output.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#include "test_framework.h"

#include "sgr.phc"
#include "screen.phc"
#include "render_bitmap.phc"

/* === Helpers === */

/* Create a simple test atlas: 8x16 glyphs, 256 entries.
 * Glyph for 'A' (65) has a filled rectangle pattern.
 * All other glyphs are empty (alpha=0). */
static GlyphAtlas *make_test_atlas(void) {
    GlyphAtlas *atlas = atlas_alloc(8, 16, 256);
    if (!atlas) return NULL;

    /* Fill glyph 'A' with full alpha (solid foreground) */
    uint8_t *glyph_a = atlas->data + 65 * 8 * 16;
    for (int i = 0; i < 8 * 16; i++) {
        glyph_a[i] = 255;
    }

    /* Fill glyph ' ' (32) with zero alpha (transparent = background only) */
    /* Already zero from calloc */

    return atlas;
}

/* ================================================================
 * Section 1: Atlas operations
 * ================================================================ */

TEST(atlas_alloc_free) {
    GlyphAtlas *atlas = atlas_alloc(8, 16, 256);
    ASSERT_NOT_NULL(atlas);
    ASSERT_EQ(atlas->glyph_w, 8);
    ASSERT_EQ(atlas->glyph_h, 16);
    ASSERT_EQ(atlas->num_glyphs, 256);
    ASSERT_NOT_NULL(atlas->data);
    atlas_free(atlas);
}

TEST(atlas_glyph_valid) {
    GlyphAtlas *atlas = make_test_atlas();
    ASSERT_NOT_NULL(atlas);
    const uint8_t *glyph = atlas_glyph(atlas, 65); /* 'A' */
    ASSERT_NOT_NULL(glyph);
    /* 'A' glyph should be all 255 */
    ASSERT_EQ(glyph[0], 255);
    ASSERT_EQ(glyph[8 * 16 - 1], 255);
    atlas_free(atlas);
}

TEST(atlas_glyph_oob) {
    GlyphAtlas *atlas = make_test_atlas();
    ASSERT_NOT_NULL(atlas);
    ASSERT_NULL(atlas_glyph(atlas, -1));
    ASSERT_NULL(atlas_glyph(atlas, 256));
    ASSERT_NULL(atlas_glyph(atlas, 1000));
    atlas_free(atlas);
}

/* ================================================================
 * Section 2: Frame buffer operations
 * ================================================================ */

TEST(framebuf_alloc_free) {
    FrameBuffer *fb = framebuf_alloc(640, 384);
    ASSERT_NOT_NULL(fb);
    ASSERT_EQ(fb->width, 640);
    ASSERT_EQ(fb->height, 384);
    ASSERT_NOT_NULL(fb->pixels);
    framebuf_free(fb);
}

TEST(framebuf_clear_color) {
    FrameBuffer *fb = framebuf_alloc(4, 4);
    ASSERT_NOT_NULL(fb);
    framebuf_clear(fb, 0xAA, 0xBB, 0xCC);
    /* Check first and last pixel */
    ASSERT_EQ(fb->pixels[0], 0xAA);
    ASSERT_EQ(fb->pixels[1], 0xBB);
    ASSERT_EQ(fb->pixels[2], 0xCC);
    int last = (4 * 4 - 1) * 3;
    ASSERT_EQ(fb->pixels[last], 0xAA);
    ASSERT_EQ(fb->pixels[last + 1], 0xBB);
    ASSERT_EQ(fb->pixels[last + 2], 0xCC);
    framebuf_free(fb);
}

TEST(parse_hex_color_valid) {
    uint8_t r, g, b;
    parse_hex_color("#ff8800", &r, &g, &b);
    ASSERT_EQ(r, 0xFF);
    ASSERT_EQ(g, 0x88);
    ASSERT_EQ(b, 0x00);
}

TEST(parse_hex_color_black) {
    uint8_t r, g, b;
    parse_hex_color("#000000", &r, &g, &b);
    ASSERT_EQ(r, 0);
    ASSERT_EQ(g, 0);
    ASSERT_EQ(b, 0);
}

TEST(parse_hex_color_white) {
    uint8_t r, g, b;
    parse_hex_color("#ffffff", &r, &g, &b);
    ASSERT_EQ(r, 255);
    ASSERT_EQ(g, 255);
    ASSERT_EQ(b, 255);
}

/* ================================================================
 * Section 3: Color resolution (phc_match)
 * ================================================================ */

TEST(color_to_rgb_default) {
    RGB def = {255, 128, 0};
    RGB result = color_to_rgb(Color_mk_Default(), def);
    ASSERT_EQ(result.r, 255);
    ASSERT_EQ(result.g, 128);
    ASSERT_EQ(result.b, 0);
}

TEST(color_to_rgb_indexed) {
    RGB def = {0, 0, 0};
    /* Index 1 = red (#cd0000) */
    RGB result = color_to_rgb(Color_mk_Indexed(1), def);
    ASSERT_EQ(result.r, 0xcd);
    ASSERT_EQ(result.g, 0x00);
    ASSERT_EQ(result.b, 0x00);
}

TEST(color_to_rgb_direct) {
    RGB def = {0, 0, 0};
    RGB result = color_to_rgb(Color_mk_RGB(0x12, 0x34, 0x56), def);
    ASSERT_EQ(result.r, 0x12);
    ASSERT_EQ(result.g, 0x34);
    ASSERT_EQ(result.b, 0x56);
}

/* ================================================================
 * Section 4: Glyph compositing
 * ================================================================ */

TEST(composite_glyph_solid_fg) {
    /* Composite a fully opaque glyph — result should be fg color */
    GlyphAtlas *atlas = make_test_atlas();
    FrameBuffer *fb = framebuf_alloc(8, 16);
    ASSERT_NOT_NULL(atlas);
    ASSERT_NOT_NULL(fb);

    framebuf_clear(fb, 0, 0, 0);
    composite_glyph(fb, atlas, 65 /* 'A' */, 0, 0,
                    255, 128, 0,    /* fg: orange */
                    0, 0, 0);       /* bg: black */

    /* Fully opaque glyph -> pixel should be fg color */
    ASSERT_EQ(fb->pixels[0], 255);
    ASSERT_EQ(fb->pixels[1], 128);
    ASSERT_EQ(fb->pixels[2], 0);

    framebuf_free(fb);
    atlas_free(atlas);
}

TEST(composite_glyph_transparent_bg) {
    /* Composite a fully transparent glyph — result should be bg color */
    GlyphAtlas *atlas = make_test_atlas();
    FrameBuffer *fb = framebuf_alloc(8, 16);
    ASSERT_NOT_NULL(atlas);
    ASSERT_NOT_NULL(fb);

    framebuf_clear(fb, 0, 0, 0);
    composite_glyph(fb, atlas, 32 /* ' ' */, 0, 0,
                    255, 255, 255,  /* fg: white */
                    0, 128, 0);     /* bg: green */

    /* Fully transparent glyph -> pixel should be bg color */
    ASSERT_EQ(fb->pixels[0], 0);
    ASSERT_EQ(fb->pixels[1], 128);
    ASSERT_EQ(fb->pixels[2], 0);

    framebuf_free(fb);
    atlas_free(atlas);
}

TEST(composite_glyph_oob_codepoint) {
    /* Out-of-range codepoint should fill with bg color, not crash */
    GlyphAtlas *atlas = make_test_atlas();
    FrameBuffer *fb = framebuf_alloc(8, 16);
    ASSERT_NOT_NULL(atlas);
    ASSERT_NOT_NULL(fb);

    framebuf_clear(fb, 0, 0, 0);
    composite_glyph(fb, atlas, 999, 0, 0,
                    255, 255, 255,
                    64, 64, 64);

    /* No glyph -> bg color */
    ASSERT_EQ(fb->pixels[0], 64);
    ASSERT_EQ(fb->pixels[1], 64);
    ASSERT_EQ(fb->pixels[2], 64);

    framebuf_free(fb);
    atlas_free(atlas);
}

/* ================================================================
 * Section 5: Screen rendering
 * ================================================================ */

TEST(render_empty_screen) {
    /* Empty terminal should produce solid background color */
    GlyphAtlas *atlas = make_test_atlas();
    ScreenBuffer *scr = screen_alloc(2, 4);
    FrameBuffer *fb = framebuf_alloc(4 * 8, 2 * 16);
    ASSERT_NOT_NULL(atlas);
    ASSERT_NOT_NULL(scr);
    ASSERT_NOT_NULL(fb);

    render_screen_to_framebuf(fb, scr, atlas, "#ffffff", "#000000");

    /* All pixels should be background (black) since all cells are empty (space) */
    /* Space glyph is transparent -> bg color fills */
    ASSERT_EQ(fb->pixels[0], 0);
    ASSERT_EQ(fb->pixels[1], 0);
    ASSERT_EQ(fb->pixels[2], 0);

    framebuf_free(fb);
    screen_free(scr);
    atlas_free(atlas);
}

TEST(render_single_char) {
    /* Place 'A' at (0,0), verify it renders with fg color */
    GlyphAtlas *atlas = make_test_atlas();
    ScreenBuffer *scr = screen_alloc(2, 4);
    FrameBuffer *fb = framebuf_alloc(4 * 8, 2 * 16);
    ASSERT_NOT_NULL(atlas);
    ASSERT_NOT_NULL(scr);
    ASSERT_NOT_NULL(fb);

    /* Place 'A' at row 0, col 0 */
    Scrollback *sb = NULL;
    screen_put_char(scr, sb, 'A');

    render_screen_to_framebuf(fb, scr, atlas, "#ffffff", "#000000");

    /* First pixel should be white (fg) because 'A' glyph is fully opaque */
    ASSERT_EQ(fb->pixels[0], 255);
    ASSERT_EQ(fb->pixels[1], 255);
    ASSERT_EQ(fb->pixels[2], 255);

    /* A pixel in the second cell (col 1) should be bg (black) - empty cell */
    int col1_px = 8 * 3; /* x=8 (col 1), y=0, pixel index */
    ASSERT_EQ(fb->pixels[col1_px], 0);
    ASSERT_EQ(fb->pixels[col1_px + 1], 0);
    ASSERT_EQ(fb->pixels[col1_px + 2], 0);

    framebuf_free(fb);
    screen_free(scr);
    atlas_free(atlas);
}

TEST(render_colored_char) {
    /* Place 'A' with red fg on blue bg */
    GlyphAtlas *atlas = make_test_atlas();
    ScreenBuffer *scr = screen_alloc(1, 2);
    FrameBuffer *fb = framebuf_alloc(2 * 8, 1 * 16);
    ASSERT_NOT_NULL(atlas);
    ASSERT_NOT_NULL(scr);
    ASSERT_NOT_NULL(fb);

    /* Set pen to red fg, blue bg */
    scr->cursor.pen.fg = Color_mk_RGB(255, 0, 0);
    scr->cursor.pen.bg = Color_mk_RGB(0, 0, 255);
    screen_put_char(scr, NULL, 'A');

    render_screen_to_framebuf(fb, scr, atlas, "#ffffff", "#000000");

    /* 'A' glyph is fully opaque -> pixel should be red (fg) */
    ASSERT_EQ(fb->pixels[0], 255);
    ASSERT_EQ(fb->pixels[1], 0);
    ASSERT_EQ(fb->pixels[2], 0);

    framebuf_free(fb);
    screen_free(scr);
    atlas_free(atlas);
}

TEST(render_dim_attribute) {
    /* DIM (SGR 2) should halve foreground brightness */
    GlyphAtlas *atlas = make_test_atlas();
    ScreenBuffer *scr = screen_alloc(1, 2);
    FrameBuffer *fb = framebuf_alloc(2 * 8, 1 * 16);
    ASSERT_NOT_NULL(atlas);
    ASSERT_NOT_NULL(scr);
    ASSERT_NOT_NULL(fb);

    /* Set pen with DIM attribute and white fg */
    scr->cursor.pen.fg = Color_mk_RGB(200, 200, 200);
    scr->cursor.pen.attrs = CellAttr_Dim;
    screen_put_char(scr, NULL, 'A');

    render_screen_to_framebuf(fb, scr, atlas, "#ffffff", "#000000");

    /* DIM halves fg: 200/2 = 100 */
    ASSERT_EQ(fb->pixels[0], 100);
    ASSERT_EQ(fb->pixels[1], 100);
    ASSERT_EQ(fb->pixels[2], 100);

    framebuf_free(fb);
    screen_free(scr);
    atlas_free(atlas);
}

TEST(render_inverse_attribute) {
    /* INVERSE swaps fg and bg */
    GlyphAtlas *atlas = make_test_atlas();
    ScreenBuffer *scr = screen_alloc(1, 1);
    FrameBuffer *fb = framebuf_alloc(1 * 8, 1 * 16);
    ASSERT_NOT_NULL(atlas);
    ASSERT_NOT_NULL(scr);
    ASSERT_NOT_NULL(fb);

    scr->cursor.pen.fg = Color_mk_RGB(255, 0, 0);
    scr->cursor.pen.bg = Color_mk_RGB(0, 0, 255);
    scr->cursor.pen.attrs = CellAttr_Inverse;
    screen_put_char(scr, NULL, 'A');

    render_screen_to_framebuf(fb, scr, atlas, "#ffffff", "#000000");

    /* Inverse: fg becomes blue (was bg), fully opaque glyph */
    ASSERT_EQ(fb->pixels[0], 0);
    ASSERT_EQ(fb->pixels[1], 0);
    ASSERT_EQ(fb->pixels[2], 255);

    framebuf_free(fb);
    screen_free(scr);
    atlas_free(atlas);
}

TEST(render_with_padding) {
    /* Padding should offset glyph positions */
    GlyphAtlas *atlas = make_test_atlas();
    ScreenBuffer *scr = screen_alloc(1, 1);
    /* Frame buffer with 4px padding: (1*8 + 2*4) x (1*16 + 2*4) = 16 x 24 */
    FrameBuffer *fb = framebuf_alloc(16, 24);
    ASSERT_NOT_NULL(atlas);
    ASSERT_NOT_NULL(scr);
    ASSERT_NOT_NULL(fb);

    scr->cursor.pen.fg = Color_mk_RGB(255, 255, 255);
    screen_put_char(scr, NULL, 'A');

    uint8_t dfg_r = 255, dfg_g = 255, dfg_b = 255;
    uint8_t dbg_r = 0, dbg_g = 0, dbg_b = 0;
    render_screen_to_framebuf_rgb(fb, scr, atlas,
                                  (RGB){dfg_r, dfg_g, dfg_b},
                                  (RGB){dbg_r, dbg_g, dbg_b}, 4);

    /* Pixel (0,0) is in padding — should be bg (black) */
    ASSERT_EQ(fb->pixels[0], 0);
    ASSERT_EQ(fb->pixels[1], 0);
    ASSERT_EQ(fb->pixels[2], 0);

    /* Pixel (4,4) is start of glyph — 'A' is fully opaque, should be fg (white) */
    int idx = (4 * 16 + 4) * 3;
    ASSERT_EQ(fb->pixels[idx], 255);
    ASSERT_EQ(fb->pixels[idx + 1], 255);
    ASSERT_EQ(fb->pixels[idx + 2], 255);

    framebuf_free(fb);
    screen_free(scr);
    atlas_free(atlas);
}

TEST(render_unicode_fallback) {
    /* Codepoint > atlas size should render as space (fallback) */
    GlyphAtlas *atlas = make_test_atlas();
    ScreenBuffer *scr = screen_alloc(1, 1);
    FrameBuffer *fb = framebuf_alloc(8, 16);
    ASSERT_NOT_NULL(atlas);
    ASSERT_NOT_NULL(scr);
    ASSERT_NOT_NULL(fb);

    /* Place a codepoint beyond atlas range */
    screen_put_char(scr, NULL, 0x1F600); /* emoji — way beyond 256 */

    render_screen_to_framebuf(fb, scr, atlas, "#ffffff", "#000000");

    /* Should fall back to space glyph (transparent) → bg color (black) */
    ASSERT_EQ(fb->pixels[0], 0);
    ASSERT_EQ(fb->pixels[1], 0);
    ASSERT_EQ(fb->pixels[2], 0);

    framebuf_free(fb);
    screen_free(scr);
    atlas_free(atlas);
}

/* ================================================================
 * Section 6: PPM output
 * ================================================================ */

TEST(ppm_valid_header) {
    FrameBuffer *fb = framebuf_alloc(4, 2);
    ASSERT_NOT_NULL(fb);
    framebuf_clear(fb, 128, 64, 32);

    size_t len = 0;
    uint8_t *ppm = framebuf_to_ppm(fb, &len);
    ASSERT_NOT_NULL(ppm);
    ASSERT(len > 0);

    /* Check PPM header starts with "P6\n" */
    ASSERT_EQ(ppm[0], 'P');
    ASSERT_EQ(ppm[1], '6');
    ASSERT_EQ(ppm[2], '\n');

    /* Parse header to verify dimensions */
    int w = 0, h = 0, maxval = 0;
    ASSERT_EQ(sscanf((char *)ppm, "P6\n%d %d\n%d\n", &w, &h, &maxval), 3);
    ASSERT_EQ(w, 4);
    ASSERT_EQ(h, 2);
    ASSERT_EQ(maxval, 255);

    free(ppm);
    framebuf_free(fb);
}

TEST(ppm_pixel_data) {
    FrameBuffer *fb = framebuf_alloc(1, 1);
    ASSERT_NOT_NULL(fb);
    framebuf_clear(fb, 0xAA, 0xBB, 0xCC);

    size_t len = 0;
    uint8_t *ppm = framebuf_to_ppm(fb, &len);
    ASSERT_NOT_NULL(ppm);

    /* Find end of header (after "255\n") */
    char *header_end = strstr((char *)ppm, "255\n");
    ASSERT_NOT_NULL(header_end);
    uint8_t *pixels = (uint8_t *)header_end + 4;

    /* Single pixel should match our color */
    ASSERT_EQ(pixels[0], 0xAA);
    ASSERT_EQ(pixels[1], 0xBB);
    ASSERT_EQ(pixels[2], 0xCC);

    free(ppm);
    framebuf_free(fb);
}

/* ================================================================
 * Test runner
 * ================================================================ */

TEST_MAIN(
    /* Atlas */
    RUN_TEST(atlas_alloc_free);
    RUN_TEST(atlas_glyph_valid);
    RUN_TEST(atlas_glyph_oob);

    /* Frame buffer */
    RUN_TEST(framebuf_alloc_free);
    RUN_TEST(framebuf_clear_color);
    RUN_TEST(parse_hex_color_valid);
    RUN_TEST(parse_hex_color_black);
    RUN_TEST(parse_hex_color_white);

    /* Color resolution */
    RUN_TEST(color_to_rgb_default);
    RUN_TEST(color_to_rgb_indexed);
    RUN_TEST(color_to_rgb_direct);

    /* Glyph compositing */
    RUN_TEST(composite_glyph_solid_fg);
    RUN_TEST(composite_glyph_transparent_bg);
    RUN_TEST(composite_glyph_oob_codepoint);

    /* Screen rendering */
    RUN_TEST(render_empty_screen);
    RUN_TEST(render_single_char);
    RUN_TEST(render_colored_char);

    /* Attributes + padding + Unicode */
    RUN_TEST(render_dim_attribute);
    RUN_TEST(render_inverse_attribute);
    RUN_TEST(render_with_padding);
    RUN_TEST(render_unicode_fallback);

    /* PPM output */
    RUN_TEST(ppm_valid_header);
    RUN_TEST(ppm_pixel_data);
)
