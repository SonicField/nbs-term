#!/usr/bin/env python3
"""Font width diagnostic — run on Mac to identify CJK width mismatches.

Usage: python3 scripts/diag-widths.py [font_family] [font_size]
Default: monospace, 14
"""
import sys
import tkinter as tk
import tkinter.font

def main():
    family = sys.argv[1] if len(sys.argv) > 1 else "monospace"
    size = int(sys.argv[2]) if len(sys.argv) > 2 else 14

    root = tk.Tk()
    root.withdraw()
    f = tkinter.font.Font(family=family, size=size)

    # Basic char_width (what nbs-term uses)
    char_width_M = f.measure("M")
    char_width_avg10 = f.measure("M" * 10) / 10
    char_width_avg80 = f.measure("M" * 80) / 80

    print(f"Font: {family} {size}")
    print(f"")
    print(f"=== ASCII char_width ===")
    print(f"  font.measure('M')         = {char_width_M}")
    print(f"  font.measure('M'*10)/10   = {char_width_avg10:.2f}")
    print(f"  font.measure('M'*80)/80   = {char_width_avg80:.2f}")
    print(f"")

    # CJK measurements
    cjk_chars = [
        ("你", "CJK Unified"),
        ("好", "CJK Unified"),
        ("世", "CJK Unified"),
        ("界", "CJK Unified"),
        ("カ", "Katakana"),
        ("한", "Hangul"),
        ("Ａ", "Fullwidth A"),
    ]

    print(f"=== Wide char widths (expected: 2 * char_width = {2 * char_width_M}) ===")
    for ch, name in cjk_chars:
        w = f.measure(ch)
        ratio = w / char_width_M
        print(f"  '{ch}' ({name}): {w}px = {ratio:.3f}x char_width")

    # Multi-char CJK strings
    print(f"")
    print(f"=== Multi-char CJK strings ===")
    for s, expected_cols in [("你好", 4), ("你好世界", 8), ("カタカナ", 8), ("한글", 4)]:
        w = f.measure(s)
        expected_px = expected_cols * char_width_M
        print(f"  '{s}': {w}px (expected {expected_px}px = {expected_cols} cols × {char_width_M})")

    # Mixed strings
    print(f"")
    print(f"=== Mixed width strings ===")
    for s, expected_cols in [("A你B", 4), ("AB你好CD", 8), ("ABCD", 4)]:
        w = f.measure(s)
        expected_px = expected_cols * char_width_M
        print(f"  '{s}': {w}px (expected {expected_px}px = {expected_cols} cols)")

    # Emoji
    print(f"")
    print(f"=== Emoji widths ===")
    for ch, name in [("🎉", "Party"), ("🔥", "Fire"), ("🚀", "Rocket")]:
        w = f.measure(ch)
        ratio = w / char_width_M
        print(f"  '{ch}' ({name}): {w}px = {ratio:.3f}x char_width")

    root.destroy()

if __name__ == "__main__":
    main()
