#!/usr/bin/env python3
"""Check whether the grid-snap wide char code is compiled into _nbsterm."""
import _nbsterm

t = _nbsterm.Terminal(24, 80)
t.feed('你好'.encode('utf-8'))
screen = t.get_screen()

if not screen or not screen[0]:
    print("ERROR: no screen output")
    raise SystemExit(1)

span = screen[0][0]
print(f"Span tuple length: {len(span)}")

if len(span) > 4:
    col_widths = list(span[4])
    print(f"col_widths (first 5): {col_widths[:5]}")
    if col_widths[:2] == [2, 2]:
        print("GRID-SNAP CODE: PRESENT (wide chars detected as width=2)")
    else:
        print("GRID-SNAP CODE: PRESENT but wide chars NOT detected (width=1)")
else:
    print("GRID-SNAP CODE: NOT PRESENT (stale binary, rebuild needed)")
