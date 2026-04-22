#!/usr/bin/env python3
"""Diagnostic for the Mac mouse-offset bug (D-1776408292).

Mirrors TerminalWidget's font and PADDING setup, draws a labeled column
ruler on a canvas, and prints per-click diagnostics so we can compute
the (event.x - PADDING) / char_width vs intended-column ratio directly.

Usage:
    python scripts/diag-mouse-offset.py

Click on each labeled column tick (col 0, col 10, col 20, ...) and copy
the printed lines into chat.

If computed_col == clicked_label, no offset (PASS).
If computed_col is a constant integer offset from clicked_label, suspect
PADDING (case 1).
If computed_col / clicked_label is a constant ratio (e.g. ~2.0 on Retina),
suspect char_width unit mismatch (case 2 — Retina/HiDPI).
If the ratio drifts non-linearly with column, suspect font-measurement
mismatch with rendered glyph width (case 3).
If `font.measure('M' * 10)` is not exactly 10 * `font.measure('M')`,
suspect grid-vs-CoreText mismatch (case 4 — render uses real text
metrics, click uses uniform M-grid; D-1776409935).
"""
import sys
import tkinter as tk
import tkinter.font as tkfont

# Match nbsterm.py defaults exactly.
DEFAULT_FONT_FAMILY = "Menlo" if sys.platform == "darwin" else "monospace"
DEFAULT_FONT_SIZE = 14
PADDING = 8
ROWS = 10
COLS = 80
TICK_EVERY = 10


def main():
    root = tk.Tk()
    root.title("nbs-term mouse offset diagnostic")

    font = tkfont.Font(family=DEFAULT_FONT_FAMILY, size=DEFAULT_FONT_SIZE)
    char_width = font.measure("M")
    char_height = font.metrics("linespace")

    width = COLS * char_width + 2 * PADDING
    height = ROWS * char_height + 2 * PADDING
    canvas = tk.Canvas(root, width=width, height=height, bg="#1a1a1a",
                       highlightthickness=0, borderwidth=0)
    canvas.pack()

    # Header diagnostics — print before any clicks.
    print("=== nbs-term mouse offset diagnostic ===")
    print(f"sys.platform:               {sys.platform}")
    print(f"DEFAULT_FONT_FAMILY:        {DEFAULT_FONT_FAMILY}")
    print(f"DEFAULT_FONT_SIZE:          {DEFAULT_FONT_SIZE}")
    print(f"PADDING:                    {PADDING}")
    print(f"tk scaling:                 {root.tk.call('tk', 'scaling')}")
    print(f"font.measure('M'):          {char_width}")
    m10 = font.measure("M" * 10)
    print(f"font.measure('M' * 10):     {m10}   "
          f"(10 * char_width = {10 * char_width}, "
          f"ratio = {m10 / (10 * char_width):.4f})")
    print(f"font.metrics('linespace'):  {char_height}")
    print(f"canvas.winfo_fpixels('1i'): {canvas.winfo_fpixels('1i')}")
    print(f"canvas declared size:       {width} x {height}  ({COLS} cols x {ROWS} rows)")
    print()
    print("Click on each labeled column tick. One line per click.")
    print("Format: event.x  event.y  computed_col  computed_row  intended_label")
    print()

    # Draw labeled ruler ticks every TICK_EVERY columns.
    label_font = tkfont.Font(family=DEFAULT_FONT_FAMILY, size=DEFAULT_FONT_SIZE)
    for col in range(0, COLS + 1, TICK_EVERY):
        x = PADDING + col * char_width
        canvas.create_line(x, PADDING, x, height - PADDING,
                           fill="#404040")
        canvas.create_text(x + 2, PADDING + 4, anchor="nw",
                           text=f"col {col}", fill="#d0d0d0", font=label_font)

    # Horizontal row lines for reference.
    for row in range(0, ROWS + 1):
        y = PADDING + row * char_height
        canvas.create_line(PADDING, y, width - PADDING, y, fill="#202020")

    def on_click(event):
        x_local = event.x - PADDING
        computed_col = x_local // char_width if char_width else -1
        computed_row = (event.y - PADDING) // char_height if char_height else -1
        # Nearest labeled tick (in cols, using the *drawn* char_width, so
        # this matches what the user sees on screen).
        nearest_label = round(x_local / (TICK_EVERY * char_width)) * TICK_EVERY
        nearest_label = max(0, min(COLS, nearest_label))
        print(f"[click] event.x={event.x:4d}  event.y={event.y:4d}  "
              f"computed_col={computed_col:4d}  computed_row={computed_row:3d}  "
              f"intended={nearest_label}")

    canvas.bind("<ButtonPress-1>", on_click)

    root.mainloop()


if __name__ == "__main__":
    main()
