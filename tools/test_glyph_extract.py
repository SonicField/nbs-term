#!/usr/bin/env python3
"""Proof-of-concept: extract anti-aliased glyph pixels from Tk.

Run on a machine with a display (e.g. Mac):
    python3 tools/test_glyph_extract.py

This proves the seam between Tk font rendering and the C atlas works.
It renders 'A' using the system font, extracts per-pixel alpha values,
and prints the glyph as ASCII art.
"""
import tkinter as tk
import tkinter.font as tkfont


def extract_glyph(root, char, font):
    """Render a character and extract its alpha values via PhotoImage.get()."""
    gw = font.measure("M")
    gh = font.metrics("linespace")

    # Create a canvas, draw white text on black background
    canvas = tk.Canvas(root, width=gw, height=gh, bg="#000000",
                       highlightthickness=0, borderwidth=0)
    canvas.pack()
    canvas.create_text(0, 0, text=char, fill="#ffffff", font=font, anchor=tk.NW)
    canvas.update()

    # Snapshot the canvas to a PhotoImage
    # Tk 8.6+ supports this on some platforms
    photo = tk.PhotoImage(width=gw, height=gh)

    # Method: render canvas content to postscript, convert... too complex.
    # Instead: use the canvas widget's ability to be captured via
    # Tk's internal 'image create photo' with -format window
    try:
        # Try Tk's built-in window capture (8.6+)
        photo.tk.call(photo, 'copy', canvas._w)
    except tk.TclError:
        # Fallback: manually read via postscript (not ideal)
        # Try another approach: use a Label widget
        canvas.destroy()
        return extract_glyph_via_label(root, char, font, gw, gh)

    # Extract pixel data
    alpha_data = []
    for y in range(gh):
        row = []
        for x in range(gw):
            r, g, b = photo.get(x, y)
            # Use red channel as alpha (white text on black = luminance)
            row.append(r)
        alpha_data.append(row)

    canvas.destroy()
    return gw, gh, alpha_data


def extract_glyph_via_label(root, char, font, gw, gh):
    """Fallback: extract glyph by rendering to a Label and capturing."""
    # Create a frame to hold the label
    frame = tk.Frame(root, width=gw, height=gh)
    frame.pack()

    label = tk.Label(frame, text=char, font=font, fg="#ffffff", bg="#000000",
                     borderwidth=0, padx=0, pady=0)
    label.pack()
    root.update()

    # Take screenshot of the label using Tk's built-in photo capture
    photo = tk.PhotoImage(width=gw, height=gh)
    try:
        # Use Tk's image capture API
        x = label.winfo_rootx()
        y = label.winfo_rooty()
        photo.tk.call(photo, 'copy', '.',
                      '-from', x, y, x + gw, y + gh)
    except tk.TclError:
        # Last resort: try pixel-by-pixel from the screen
        print(f"WARNING: Could not capture label pixels. "
              f"Label at ({x}, {y}), size {gw}x{gh}")
        frame.destroy()
        return gw, gh, [[0] * gw for _ in range(gh)]

    alpha_data = []
    for py in range(gh):
        row = []
        for px in range(gw):
            try:
                r, g, b = photo.get(px, py)
                row.append(r)
            except Exception:
                row.append(0)
        alpha_data.append(row)

    frame.destroy()
    return gw, gh, alpha_data


def print_glyph(gw, gh, alpha_data):
    """Print glyph as ASCII art."""
    chars = " .:-=+*#%@"
    for row in alpha_data:
        line = ""
        for val in row:
            idx = min(val * len(chars) // 256, len(chars) - 1)
            line += chars[idx]
        print(line)


def main():
    root = tk.Tk()
    root.withdraw()

    font = tkfont.Font(family="Courier", size=14)
    gw = font.measure("M")
    gh = font.metrics("linespace")
    print(f"Font: Courier 14, glyph size: {gw}x{gh}")

    for char in "AHg@":
        print(f"\n--- '{char}' ---")
        gw, gh, alpha = extract_glyph(root, char, font)

        # Check if we got non-trivial alpha values
        flat = [v for row in alpha for v in row]
        nonzero = sum(1 for v in flat if v > 0)
        has_aa = any(0 < v < 255 for v in flat)
        print(f"Size: {gw}x{gh}, non-zero: {nonzero}/{len(flat)}, "
              f"anti-aliased: {has_aa}")
        print_glyph(gw, gh, alpha)

        if nonzero > 0:
            # Build atlas bytes for this one character
            atlas_bytes = bytes(v for row in alpha for v in row)
            print(f"Atlas bytes: {len(atlas_bytes)} (first 16: {list(atlas_bytes[:16])})")

    print("\n--- RESULT ---")
    print("If you see character shapes above with anti-aliased values,")
    print("the Tk → atlas extraction path works. The C compositor already")
    print("supports 8bpp alpha blending.")

    root.destroy()


if __name__ == "__main__":
    main()
