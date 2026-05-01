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

**xfail on darwin (added 2026-04-23):** Bug A's root cause IS the grid-contract
violation on Menlo/CoreText (font.measure('M' * 10) == 115 != 120, ratio 0.9583).
The fix (TerminalWidget._pixel_to_cell_text_aware in nbsterm.py:184) does NOT
restore the contract — it sidesteps the contract by routing mouse hit-testing
through font.measure prefix-sums instead of uniform-grid division. The legacy
_pixel_to_cell is preserved as fallback only (nbsterm.py:142-148). So this test
is EXPECTED to fail on darwin post-fix; the failure documents the still-violated
invariant rather than gating CI. xfail uses strict=True so an unexpected pass on
darwin (e.g. Apple fixes CoreText subadditivity, or font default changes) gets
reported as XPASS — surfaces the platform-state change that would warrant
re-evaluation.

Per testkeeper standards, a structured xfail-as-skip needs the same visibility
treatment as the headless-skip warning: emit a UserWarning at module load on
darwin so the xfail status doesn't silently disappear into the pytest summary.
"""
import os
import sys
import unittest
import warnings

import pytest

sys.path.insert(0, os.path.dirname(os.path.dirname(os.path.abspath(__file__))))

import tkinter
import tkinter.font as tkfont

from nbsterm import DEFAULT_FONT_SIZE, default_font_family


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

if sys.platform == "darwin":
    warnings.warn(
        "tests/test_grid_contract.py is xfail-on-darwin — Bug A's root cause "
        "(CoreText subadditivity on Menlo) is a documented invariant violation "
        "fixed via _pixel_to_cell_text_aware, not via restoring the contract. "
        "Unexpected pass (XPASS) on darwin would indicate platform-state "
        "change worth re-evaluating; unexpected XPASS is reported as failure.",
        UserWarning,
        stacklevel=2,
    )


# Per-method xfail marker — pytest.mark.xfail at the class level does NOT
# propagate to test methods on a unittest.TestCase subclass (alexie crash run
# 2026-04-23 11:36 showed FFFF.FF on darwin: marker silently ignored, plain
# failures reported instead of XFAIL). Apply per method.
_xfail_on_darwin = pytest.mark.xfail(
    sys.platform == "darwin",
    strict=True,
    reason="Bug A: CoreText subadditivity on Menlo violates the grid contract. "
           "Compensated by TerminalWidget._pixel_to_cell_text_aware (text-aware "
           "click-to-cell helper) which walks per-char font.measure widths "
           "instead of dividing by char_width. Legacy _pixel_to_cell is "
           "preserved as fallback only. Compensation is regression-protected "
           "by tests/test_render_layout_equivalence.py::TestBugAFixDisagrees "
           "(stub-FakeFont DISAGREE assertion, Linux-runnable). Test failure "
           "on darwin documents the still-violated invariant; unexpected pass "
           "= Apple fixed CoreText, or font default changed — re-evaluate.",
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
        cls.font_family = default_font_family()
        cls.font = tkfont.Font(
            root=_root, family=cls.font_family, size=DEFAULT_FONT_SIZE
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
            f"{self.font_family!r}: font.measure({char!r}*{n})={repeated} "
            f"!= {n}*font.measure({char!r})={n * single}. "
            f"Click->cell mapping divides event.x by font.measure('M')={single} "
            f"but text renders at the per-text advance, so visual click and "
            f"computed column will diverge. See D-1776409935.",
        )

    @_xfail_on_darwin
    def test_M_x5(self):
        self._assert_grid("M", 5)

    @_xfail_on_darwin
    def test_M_x10(self):
        self._assert_grid("M", 10)

    @_xfail_on_darwin
    def test_M_x50(self):
        self._assert_grid("M", 50)

    @_xfail_on_darwin
    def test_i_x10(self):
        self._assert_grid("i", 10)

    @_xfail_on_darwin
    def test_W_x10(self):
        self._assert_grid("W", 10)

    @_xfail_on_darwin
    def test_space_x10(self):
        self._assert_grid(" ", 10)

    # NOTE: test_all_glyphs_share_M_width does NOT carry the darwin xfail mark.
    # Mac-CoreText subadditivity affects MULTI-character measure (the c×N
    # tests above); single-character widths agree on Menlo (verified in
    # alexie's run 11:36 — this test was the lone PASS in FFFF.FF). The
    # bug A path doesn't break this invariant, so this test should continue
    # to pass on darwin too. If it ever fails on darwin, the font defaulting
    # changed (e.g. Menlo replaced by a proportional font), not Bug A.
    def test_all_glyphs_share_M_width(self):
        """In a true monospace font, every glyph occupies the same cell width.

        If `i` and `W` differ from `M`, the font is not monospace -- click->cell
        will land on the right cell for `M`-widths but be off for narrower or
        wider glyphs.
        """
        m = self.font.measure("M")
        widths = {c: self.font.measure(c) for c in ("i", "W", " ", "0", "x", ".")}
        mismatches = {c: w for c, w in widths.items() if w != m}
        self.assertEqual(
            mismatches,
            {},
            f"Glyphs differ from 'M' width ({m}) on font "
            f"{self.font_family!r}: {mismatches}. Single-glyph monospace "
            f"assumption is false; click->cell mapping is unreliable.",
        )


if __name__ == "__main__":
    unittest.main()
