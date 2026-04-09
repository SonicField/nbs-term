# Bold Font Width on Windows

## Problem

On Windows, bold font variants often have wider advance widths than their regular counterparts. A bold 'W' may be 1-2 pixels wider than a regular 'W'. In a monospace terminal, every character must occupy exactly the same cell width (`char_width`). When bold text overflows its cell boundary, adjacent characters shift or overlap, breaking grid alignment.

Reported by alexie on Windows (2026-04-09) during dogfooding.

## Current Behaviour

The renderer uses `font measure` (via Tcl_EvalObjv) to compute span widths. Bold spans use the `font_bold` named font. If `font measure font_bold "W"` returns a wider value than `font measure font_normal "W"`, the span occupies more pixels than expected, pushing subsequent spans rightward.

The cursor overlay uses `char_width` (from the normal font) for positioning, creating a mismatch between rendered text and cursor position on bold rows.

## Fix Approaches

### 1. Cell clipping (recommended)

Force each character to render within its `char_width` cell regardless of the font's actual advance width. Tk canvas text items can be clipped by overlaying a rectangle or using canvas item coordinates to constrain rendering.

**Pros:** Simple, preserves grid alignment, works for all font variants.
**Cons:** Very wide bold glyphs may be visually truncated.

### 2. Font measure adjustment

Use `font measure font_normal` for ALL span width calculations, regardless of the actual font variant. Bold/italic text renders at the normal font's advance width.

**Pros:** Grid stays aligned. Bold text that fits within normal width looks fine.
**Cons:** Same as clipping — wide bold glyphs truncated.

### 3. Per-character rendering

Instead of rendering spans as single text items, render each character individually at fixed `char_width` intervals. This guarantees grid alignment but increases the number of canvas items.

**Pros:** Perfect grid alignment, handles all font variants.
**Cons:** Performance — up to 80x more canvas items per row (one per character instead of one per span).

## Requirements

- Must maintain pixel-perfect grid alignment on all platforms
- Must not regress rendering performance (currently ~270 Tk calls per typical frame)
- Needs testing on Windows with alexie's specific font (Consolas, Cascadia Code, etc.)

## Status

Design needed. Requires Windows testing before implementation.
