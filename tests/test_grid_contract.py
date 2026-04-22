"""
test_grid_contract.py — Falsifies the uniform-grid assumption nbs-term relies on.

The mouse selection click->cell mapping (`_pixel_to_cell` in nbsterm.py:142,
`phc_pixel_to_cell` in src/selection.phc:16) divides `event.x` by
`char_width = font.measure('M')`. This only lands on the visually correct cell
if the configured font satisfies the **grid contract**:

    font.measure(c * N) == N * font.measure(c)   for any glyph c, any N >= 1

If the grid contract holds, every cell is exactly `font.measure('M')` pixels wide
and the integer-division mapping is correct. If the grid contract fails (e.g.
CoreText on macOS reporting per-text advance with kerning/ligature adjustments),
the renderer's per-text positioning (`render_font_measure` in
generated/extension.c:3375) and the click->cell mapping disagree -- the user
clicks visually on column N but `_pixel_to_cell` returns column N' != N.

This test fails iff the grid contract fails. A failure here is the structural
falsifier for D-1776409935 ("Bug A and Bug B share root cause: char_width grid
vs CoreText mismatch") on the platform/font where it runs.

**Intentional skip on headless boxes** (font.measure requires a Tk root).
This is a platform-contract assertion, not a unit test -- the right runner is
a display-equipped platform (macOS desktop, Windows desktop, Linux X11/Wayland
desktop). Headless CI cannot exercise CoreText behaviour; running this under
Xvfb would yield false confidence. Treat skips here as 'pending platform
verification', not 'pass'. Bug A regression insurance for D-1776408309.
"""
import os
import sys
import unittest
import warnings

sys.path.insert(0, os.path.dirname(os.path.dirname(os.path.abspath(__file__))))

import tkinter
import tkinter.font as tkfont

from nbsterm import DEFAULT_FONT_FAMILY, DEFAULT_FONT_SIZE


def _try_make_root():
    """Return a tk.Tk root, or None if no display is available."""
    try:
        return tkinter.Tk()
    except tkinter.TclError:
        return None


_root = _try_make_root()

if _root is None:
    warnings.warn(
        "tests/test_grid_contract.py skipped — needs Tk display. "
        "Grid contract is UNVERIFIED on this run; not regression coverage.",
        UserWarning,
        stacklevel=2,
    )


@unittest.skipIf(_root is None, "no display available (font.measure needs Tk)")
class TestGridContract(unittest.TestCase):
    """Falsify the uniform-grid assumption that mouse selection depends on.

    Runs against the configured default font for the current platform. A failure
    means the click->cell mapping in nbsterm.py:144 is operating on a grid that
    does not match the rendered text -- the mechanism behind Bug A
    (D-1776408309).
    """

    @classmethod
    def setUpClass(cls):
        cls.font = tkfont.Font(
            root=_root, family=DEFAULT_FONT_FAMILY, size=DEFAULT_FONT_SIZE
        )

    @classmethod
    def tearDownClass(cls):
        if _root is not None:
            _root.destroy()

    def _assert_grid(self, char, n):
        single = self.font.measure(char)
        repeated = self.font.measure(char * n)
        self.assertEqual(
            repeated,
            n * single,
            f"Grid contract violated for {char!r} x {n} on font "
            f"{DEFAULT_FONT_FAMILY!r}: font.measure({char!r}*{n})={repeated} "
            f"!= {n}*font.measure({char!r})={n * single}. "
            f"Click->cell mapping divides event.x by font.measure('M')={single} "
            f"but text renders at the per-text advance, so visual click and "
            f"computed column will diverge. See D-1776409935.",
        )

    def test_M_x5(self):
        self._assert_grid("M", 5)

    def test_M_x10(self):
        self._assert_grid("M", 10)

    def test_M_x50(self):
        self._assert_grid("M", 50)

    def test_i_x10(self):
        self._assert_grid("i", 10)

    def test_W_x10(self):
        self._assert_grid("W", 10)

    def test_space_x10(self):
        self._assert_grid(" ", 10)

    def test_all_glyphs_share_M_width(self):
        """In a true monospace font, every glyph occupies the same cell width.

        If `i` and `W` differ from `M`, the font is not monospace -- click->cell
        will land on the right cell for `M`-widths but be off for narrower or
        wider glyphs.
        """
        m = self.font.measure("M")
        for c in ("i", "W", " ", "0", "x", "."):
            with self.subTest(char=c):
                self.assertEqual(
                    self.font.measure(c),
                    m,
                    f"Glyph {c!r} width != 'M' width on font "
                    f"{DEFAULT_FONT_FAMILY!r}. Single-glyph monospace "
                    f"assumption is false; click->cell mapping is unreliable.",
                )


if __name__ == "__main__":
    unittest.main()
