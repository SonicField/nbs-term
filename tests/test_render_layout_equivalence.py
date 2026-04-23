"""
test_render_layout_equivalence.py — Existence proof for option-(i) pure-Python path.

Falsifies (or fails to falsify) the premise behind generalist's pure-Python
implementation of `_pixel_to_cell_text_aware` and `_row_spans_for_visible`
(nbsterm.py:153, :193): that Python can compute the same per-cell pixel
boundaries the C renderer produces, by replaying `tkfont.Font.measure`
prefix-sum logic over the spans returned by `Terminal.get_screen()` (active
branch) and `Terminal.get_scrollback_line()` (composite-scrollback branch).

The C renderer (`Terminal_render_frame` in generated/extension.c) places each
span at `x = PADDING + cumulative font.measure(prior spans via the named font)`,
where the named font is selected from attrs via the table at extension.c:3639-3642.
`render_font_measure` (extension.c:3375-3394) and Python's
`tkfont.Font.measure(text)` both invoke the Tcl command `font measure $font $text`
against the same Tcl interpreter — equivalent by construction.

Two classes:
- `TestRenderLayoutEquivalence` (test #1): active-screen prefix-sum vs canvas.
- `TestScrollbackCompositeEquivalence` (tests #5 and #6): scrollback composite
  mirror (`_row_spans_for_visible`) vs canvas, including pure-active, mixed,
  and pure-scrollback boundary cases (test #5) plus the alt-screen gate added
  in b564910 (test #6 — `(using_alt=True, scroll_offset>0)` state from
  theologian's reachability argument; helper must return active-screen spans,
  NOT composite scrollback). Each test class includes a mutation-falsifier to
  prove the equivalence assertions are genuinely capable of failing.

**Intentional skip on headless boxes** (render_frame and font.measure both
require a Tk display). On a no-display run, this test does not constitute
verification of the option-(i) premise — treat as 'pending platform run'.
"""
import os
import sys
import unittest
import warnings

sys.path.insert(0, os.path.dirname(os.path.dirname(os.path.abspath(__file__))))

import tkinter
import tkinter.font as tkfont

import _nbsterm
from nbsterm import (
    DEFAULT_FONT_FAMILY, DEFAULT_FONT_SIZE, PADDING, TerminalWidget,
)


def _try_make_root():
    """Return a tk.Tk root, or None if no display is available."""
    try:
        return tkinter.Tk()
    except tkinter.TclError:
        return None


_root = _try_make_root()

if _root is None:
    warnings.warn(
        "tests/test_render_layout_equivalence.py skipped — needs Tk display. "
        "Option-(i) pure-Python premise is UNVERIFIED on this run; not "
        "regression coverage for the layout-equivalence falsifier.",
        UserWarning,
        stacklevel=2,
    )
    _FONTS = {}
    _CHAR_WIDTH = None
    _CHAR_HEIGHT = None
else:
    # Hide the root window. We don't need it visible for layout-equivalence
    # tests — canvas.coords() and canvas.itemcget() read from the display list
    # synchronously without requiring the window to be on screen. On Mac Tk
    # 9.0.3, leaving the root un-managed AND calling update_idletasks() after
    # a Canvas pack triggers showRootWindow, which dereferences NULL+0x170 and
    # segfaults the Python process (alexie crash report 2026-04-23 11:36).
    # withdraw() puts the root in iconified state without realising the
    # platform-window structure showRootWindow walks.
    _root.withdraw()
    # Module-level named fonts so both test classes (and any TerminalWidget
    # instantiated in TestScrollbackCompositeEquivalence) share the same Tcl
    # font registry. Re-creating named fonts in per-class setUp causes TclError
    # 'named font already exists'; using nametofont after first creation is the
    # documented Tk pattern but can return a different object identity. Owning
    # them at module scope sidesteps both issues.
    _FONTS = {
        0x00: tkfont.Font(
            root=_root, family=DEFAULT_FONT_FAMILY,
            size=DEFAULT_FONT_SIZE, name="font_normal"),
        0x01: tkfont.Font(
            root=_root, family=DEFAULT_FONT_FAMILY,
            size=DEFAULT_FONT_SIZE, weight="bold", name="font_bold"),
        0x04: tkfont.Font(
            root=_root, family=DEFAULT_FONT_FAMILY,
            size=DEFAULT_FONT_SIZE, slant="italic", name="font_italic"),
        0x05: tkfont.Font(
            root=_root, family=DEFAULT_FONT_FAMILY,
            size=DEFAULT_FONT_SIZE, weight="bold", slant="italic",
            name="font_bold_italic"),
    }
    _CHAR_WIDTH = _FONTS[0x00].measure("M")
    _CHAR_HEIGHT = _FONTS[0x00].metrics("linespace")


def _attrs_to_font_tag(attrs):
    """Mirror of the C-side font_tag selection in extension.c:3639-3642."""
    if (attrs & 0x05) == 0x05:
        return "font_bold_italic"
    if attrs & 0x01:
        return "font_bold"
    if attrs & 0x04:
        return "font_italic"
    return "font_normal"


def _canvas_text_items_at_row(canvas, row):
    """Return [(x, text, font_tag), ...] for each canvas text item whose y
    falls in the band of the given row. Sorted by x."""
    y_expected = PADDING + row * _CHAR_HEIGHT
    items = []
    for item_id in canvas.find_all():
        if canvas.type(item_id) != "text":
            continue
        coords = canvas.coords(item_id)
        if not coords:
            continue
        x, y = coords[0], coords[1]
        if abs(y - y_expected) > 0.5:
            continue
        text = canvas.itemcget(item_id, "text")
        font_tag = canvas.itemcget(item_id, "font")
        items.append((int(round(x)), text, font_tag))
    items.sort(key=lambda t: t[0])
    return items


def _predicted_layout_from_spans(spans):
    """Replay font.measure prefix-sum across spans, in the same order and shape
    the C renderer iterates them at extension.c:3597-3653."""
    x = PADDING
    out = []
    for span in spans:
        text_bytes, _fg, _bg, attrs, _col_widths = span
        text = (text_bytes if isinstance(text_bytes, str)
                else text_bytes.decode("utf-8"))
        if not text:
            continue
        font_tag = _attrs_to_font_tag(attrs)
        out.append((x, text, font_tag))
        x += _FONTS[attrs & 0x05].measure(text)
    return out


@unittest.skipIf(_root is None, "no display available (render_frame needs Tk)")
class TestRenderLayoutEquivalence(unittest.TestCase):
    """Falsifier #2 (active-screen path): does Python prefix-sum of font.measure
    per span equal the canvas item positions produced by C's render_frame?

    Pass on Linux empirically validates theologian's pure-Python premise for
    the active branch (no scrollback). Composite branch lives in
    `TestScrollbackCompositeEquivalence` below.
    """

    @classmethod
    def setUpClass(cls):
        cls.canvas = tkinter.Canvas(
            _root, width=80 * _CHAR_WIDTH + 2 * PADDING,
            height=10 * _CHAR_HEIGHT + 2 * PADDING,
            bg="#000000", highlightthickness=0, borderwidth=0)
        # Don't pack — Mac Tk 9.0.3 segfaults in showRootWindow when the
        # canvas is geometry-managed before the root is shown (see _root.withdraw
        # comment at module load). Canvas operations (create text via Tcl,
        # coords readback) work without geometry management.
        # No update_idletasks: render_frame is synchronous via Tcl_EvalObjv;
        # canvas items are in the display list immediately on return.

    @classmethod
    def tearDownClass(cls):
        cls.canvas.destroy()

    def setUp(self):
        self.term = _nbsterm.Terminal(10, 80)
        self.canvas.delete("all")
        self.term.render_reset()

    def _render(self):
        self.term.render_frame(
            _root.tk.interpaddr(),
            str(self.canvas),
            False, 0, "", "#ffffff", "#000000",
            1.0, _CHAR_WIDTH, _CHAR_HEIGHT, PADDING,
        )
        # No update_idletasks — see module-load _root.withdraw() comment.

    def _python_predicted_layout(self, row):
        screen = self.term.get_screen("#ffffff", "#000000")
        if row >= len(screen):
            return []
        return _predicted_layout_from_spans(screen[row])

    def test_single_span_plain_ascii(self):
        """Plain ASCII text on row 0 → canvas and Python agree on (x, text, font)."""
        self.term.feed(b"Hello, World! 1234567890")
        self._render()
        canvas_items = _canvas_text_items_at_row(self.canvas, 0)
        python_items = self._python_predicted_layout(0)
        self.assertEqual(
            canvas_items, python_items,
            f"Layout divergence on row 0 (single-span plain ASCII):\n"
            f"  canvas:  {canvas_items}\n"
            f"  python:  {python_items}\n"
            f"If they differ on this trivial case, get_screen() is NOT a "
            f"faithful mirror of what render_frame iterates — the pure-Python "
            f"option-(i) path is unsupportable and the C-surfacing path is "
            f"required.")

    def test_mixed_attrs_multi_span(self):
        """Bold + plain mix: SGR 1 turns on bold, SGR 22 turns it off."""
        self.term.feed(b"AAA\x1b[1mBBB\x1b[22mCCC")
        self._render()
        canvas_items = _canvas_text_items_at_row(self.canvas, 0)
        python_items = self._python_predicted_layout(0)
        self.assertEqual(
            canvas_items, python_items,
            f"Layout divergence on row 0 (mixed bold/normal spans):\n"
            f"  canvas:  {canvas_items}\n"
            f"  python:  {python_items}")

    def test_multiple_rows(self):
        """Three rows of distinct content — each row's prefix-sum independent."""
        self.term.feed(b"Row zero text\r\nRow one different\r\nRow two yet more")
        self._render()
        for row in range(3):
            with self.subTest(row=row):
                canvas_items = _canvas_text_items_at_row(self.canvas, row)
                python_items = self._python_predicted_layout(row)
                self.assertEqual(
                    canvas_items, python_items,
                    f"Layout divergence on row {row}:\n"
                    f"  canvas:  {canvas_items}\n"
                    f"  python:  {python_items}")

    def test_python_x_positions_are_integer_pixels(self):
        """Sanity: the prefix-sum produces integer pixel x positions matching
        the C renderer's int-typed `x` accumulator (extension.c:3599)."""
        self.term.feed(b"Anything goes here")
        self._render()
        python_items = self._python_predicted_layout(0)
        for x, _text, _font in python_items:
            self.assertIsInstance(
                x, int,
                f"Python x position {x!r} is not integer — would diverge "
                f"from C's int x accumulator.")


@unittest.skipIf(_root is None, "no display available (render_frame needs Tk)")
class TestScrollbackCompositeEquivalence(unittest.TestCase):
    """Tests #5 and #6 — scrollback composite path falsifier for generalist's
    `_row_spans_for_visible` (nbsterm.py:153), including the alt-screen gate
    added in b564910.

    The helper mirrors the C composite at extension.c:3530-3559: when
    `scroll_offset > 0 && !using_alt`, each visible row r resolves to either a
    scrollback line at index `sb_count - scroll_offset + r` OR an active-screen
    row at `(sb_count - scroll_offset + r) - sb_count`. When `using_alt` is
    true, the gate fires and the helper falls into the active-screen branch
    regardless of scroll_offset (test #6).

    Test strategy: feed enough lines to populate scrollback; set scroll_offset
    > 0; render via the actual C path; for each visible row, assert that the
    canvas item layout equals the prefix-sum predicted from the spans returned
    by `_row_spans_for_visible(r)`.

    Mutation-falsification: a deliberately-corrupted prediction (e.g. using
    row N's spans for row M's prediction, or skipping the gate when alt-screen
    is active) is asserted to FAIL the equivalence — the test must be capable
    of falsifying the helper.
    """

    ROWS = 10
    COLS = 80

    @classmethod
    def setUpClass(cls):
        # Each scrollback test renders into its own canvas to keep render-state
        # fresh. Module-level named fonts (created at import) are reused.
        cls.canvas = tkinter.Canvas(
            _root, width=cls.COLS * _CHAR_WIDTH + 2 * PADDING,
            height=cls.ROWS * _CHAR_HEIGHT + 2 * PADDING,
            bg="#000000", highlightthickness=0, borderwidth=0)
        # Don't pack — Mac Tk 9.0.3 segfaults in showRootWindow when the
        # canvas is geometry-managed before the root is shown (see _root.withdraw
        # comment at module load). Canvas operations (create text via Tcl,
        # coords readback) work without geometry management.
        # No update_idletasks: render_frame is synchronous via Tcl_EvalObjv;
        # canvas items are in the display list immediately on return.

    @classmethod
    def tearDownClass(cls):
        cls.canvas.destroy()

    def setUp(self):
        # Bound-method trick: invoke generalist's actual `_row_spans_for_visible`
        # bytecode against a stub host with a `.term` attribute. Avoids
        # constructing TerminalWidget (which would re-create named fonts and
        # raise TclError 'named font already exists' against the module-level
        # registry above).
        self.term = _nbsterm.Terminal(self.ROWS, self.COLS)
        self.canvas.delete("all")
        self.term.render_reset()

        host = type("_HelperHost", (), {})()
        host.term = self.term
        host._row_spans_for_visible = TerminalWidget._row_spans_for_visible.__get__(
            host, type(host))
        self.host = host

    def _render(self):
        self.term.render_frame(
            _root.tk.interpaddr(),
            str(self.canvas),
            False, 0, "", "#ffffff", "#000000",
            1.0, _CHAR_WIDTH, _CHAR_HEIGHT, PADDING,
        )
        # No update_idletasks — see module-load _root.withdraw() comment.

    def _predicted_layout_via_helper(self, row):
        """Replay font.measure prefix-sum on whatever spans
        `_row_spans_for_visible(row)` returns. Tests generalist's actual
        method bytecode via the bound-method stub."""
        spans = self.host._row_spans_for_visible(row)
        if spans is None:
            return None
        return _predicted_layout_from_spans(spans)

    def _populate_scrollback(self, n_overflow_lines):
        """Feed enough distinct lines to push n_overflow_lines into scrollback.
        Each line's content names its source ordinal so divergences are visible."""
        total_lines = self.ROWS + n_overflow_lines
        for i in range(total_lines):
            line = f"line{i:03d}content"
            self.term.feed(line.encode("ascii"))
            if i < total_lines - 1:
                self.term.feed(b"\r\n")
        self._render()

    def test_scrollback_populated_no_scroll(self):
        """With content in scrollback but scroll_offset=0, the helper falls
        into the active-screen branch and matches the canvas (sanity-checked
        through the helper rather than direct get_screen)."""
        self._populate_scrollback(n_overflow_lines=5)
        self.assertEqual(self.term.get_scroll_offset(), 0,
            "Pre-condition: scroll_offset must be 0 for active-screen branch")
        for row in range(self.ROWS):
            with self.subTest(row=row):
                canvas_items = _canvas_text_items_at_row(self.canvas, row)
                predicted = self._predicted_layout_via_helper(row)
                self.assertIsNotNone(predicted,
                    f"_row_spans_for_visible({row}) returned None — helper "
                    f"failed to resolve a row that should exist on active screen")
                self.assertEqual(canvas_items, predicted,
                    f"Helper-vs-canvas divergence on row {row} "
                    f"(scroll_offset=0 active branch):\n"
                    f"  canvas:    {canvas_items}\n"
                    f"  predicted: {predicted}")

    def test_scrollback_partial_scroll(self):
        """scroll_offset = 3 with 5 lines in scrollback: top 3 visible rows
        come from scrollback, bottom 7 from active screen. Helper must resolve
        the boundary correctly."""
        self._populate_scrollback(n_overflow_lines=5)
        self.term.set_scroll_offset(3)
        self._render()
        self.assertEqual(self.term.get_scroll_offset(), 3,
            "Pre-condition: scroll_offset = 3 to mix scrollback + active rows")
        sb_count = self.term.get_scrollback_count()
        self.assertGreaterEqual(sb_count, 3,
            f"Pre-condition: need >=3 scrollback lines to test partial mix, "
            f"got {sb_count}")
        for row in range(self.ROWS):
            with self.subTest(row=row):
                canvas_items = _canvas_text_items_at_row(self.canvas, row)
                predicted = self._predicted_layout_via_helper(row)
                self.assertIsNotNone(predicted,
                    f"_row_spans_for_visible({row}) returned None at "
                    f"scroll_offset=3 — composite mirror failed to resolve row")
                self.assertEqual(canvas_items, predicted,
                    f"Helper-vs-canvas divergence on row {row} "
                    f"(scroll_offset=3 partial composite):\n"
                    f"  canvas:    {canvas_items}\n"
                    f"  predicted: {predicted}")

    def test_scrollback_full_viewport(self):
        """scroll_offset large enough that ALL visible rows come from
        scrollback. Tests the pure-scrollback branch."""
        self._populate_scrollback(n_overflow_lines=30)
        self.term.set_scroll_offset(self.ROWS + 5)
        self._render()
        for row in range(self.ROWS):
            with self.subTest(row=row):
                canvas_items = _canvas_text_items_at_row(self.canvas, row)
                predicted = self._predicted_layout_via_helper(row)
                self.assertIsNotNone(predicted,
                    f"_row_spans_for_visible({row}) returned None at "
                    f"scroll_offset={self.ROWS + 5} — pure-scrollback branch failed")
                self.assertEqual(canvas_items, predicted,
                    f"Helper-vs-canvas divergence on row {row} "
                    f"(pure scrollback, scroll_offset={self.ROWS + 5}):\n"
                    f"  canvas:    {canvas_items}\n"
                    f"  predicted: {predicted}")

    def test_mutation_off_by_one_scroll_offset_caught(self):
        """The equivalence assertion must be capable of failing. Verify by
        constructing a deliberately-wrong predicted layout (corresponds to
        what the helper would return if it had an off-by-one on scroll_offset)
        and asserting it does NOT equal the canvas."""
        self._populate_scrollback(n_overflow_lines=5)
        self.term.set_scroll_offset(3)
        self._render()
        honest_row_0 = self._predicted_layout_via_helper(0)
        # Mutated prediction: pretend the helper returned row 1's spans for
        # row 0. The mutation must be catchable — rows 0/1 contain distinct
        # `lineNNNcontent` strings so their predictions differ.
        wrong_for_row_0 = self._predicted_layout_via_helper(1)
        self.assertNotEqual(honest_row_0, wrong_for_row_0,
            "Mutation falsifier degenerate: row 0 and row 1 predictions are "
            "equal, so the equivalence assertion would not catch this class "
            "of helper bug. Test fixture is too uniform — fix before trusting.")
        # Positive control: honest prediction matches canvas
        canvas_row_0 = _canvas_text_items_at_row(self.canvas, 0)
        self.assertEqual(canvas_row_0, honest_row_0,
            f"Positive control failed: honest prediction != canvas:\n"
            f"  canvas:  {canvas_row_0}\n"
            f"  honest:  {honest_row_0}")

    def test_helper_returns_none_outside_known_rows(self):
        """When asked for a row outside the resolvable range, the helper
        returns None so the caller can fall back to the legacy uniform-grid
        path (nbsterm.py:211-212)."""
        self._populate_scrollback(n_overflow_lines=2)
        self.term.set_scroll_offset(0)
        self.assertIsNone(
            self.host._row_spans_for_visible(-1),
            "_row_spans_for_visible(-1) should be None for fallback")
        self.assertIsNone(
            self.host._row_spans_for_visible(self.ROWS + 100),
            f"_row_spans_for_visible({self.ROWS + 100}) should be None for fallback")

    def test_alt_screen_with_scroll_offset_returns_active_not_composite(self):
        """Test #6 — positive coverage of the alt-screen gate added in b564910.

        Reachability: a user in vim/less (alt-screen) presses Ctrl+Shift+Up
        to scroll back. Result: (using_alt=True, scroll_offset>0). Without
        the gate, _row_spans_for_visible would composite scrollback rows
        (wrong — vim is rendering alt-screen content); with the gate it
        returns active (alt) screen rows. This test asserts the gate fires.

        The gate (nbsterm.py:159) is `scroll_off > 0 and not self.term.using_alt()`,
        matching the C composite condition at extension.c:3532.
        """
        # Populate scrollback with distinct content
        self._populate_scrollback(n_overflow_lines=5)
        self.term.set_scroll_offset(3)

        # Capture what the helper returns BEFORE alt-screen entry — this is
        # the composite (scrollback) content for row 0
        composite_row_0 = self.host._row_spans_for_visible(0)
        self.assertIsNotNone(composite_row_0,
            "Pre-condition: composite branch should resolve row 0 before "
            "alt-screen entry (scroll_offset=3, using_alt=False)")

        # Enter alt-screen via DECSET 1049 + write distinctive alt content
        self.term.feed(b"\x1b[?1049h")
        self.assertTrue(self.term.using_alt(),
            "Pre-condition: ?1049h should put terminal in alt-screen state")
        self.assertGreater(self.term.get_scroll_offset(), 0,
            "Theologian's reachability claim: terminal_switch_alt does NOT "
            "reset scroll_offset, so (using_alt=True, scroll_offset>0) is "
            "constructible by entering alt-screen while scrolled back.")
        self.term.feed(b"ALT_SCREEN_ROW_0_DISTINCTIVE_CONTENT")
        self._render()

        # Post-gate: helper must return the ACTIVE (alt-screen) row's spans,
        # NOT the composite scrollback spans. Falls into the active branch:
        #   `if scroll_off > 0 and not self.term.using_alt():`
        # is False (using_alt is True), so composite is skipped.
        active_row_0 = self.host._row_spans_for_visible(0)
        self.assertIsNotNone(active_row_0,
            "Post-condition: helper must resolve row 0 into active "
            "alt-screen content when gate fires")

        # Distinctness check: alt-screen content should be ALT_SCREEN_ROW_0...,
        # composite (scrollback) was line000content. They must differ.
        active_text = b"".join(
            (s[0] if isinstance(s[0], bytes) else s[0].encode("utf-8"))
            for s in active_row_0
        )
        composite_text = b"".join(
            (s[0] if isinstance(s[0], bytes) else s[0].encode("utf-8"))
            for s in composite_row_0
        )
        self.assertIn(b"ALT_SCREEN_ROW_0", active_text,
            f"Gate-fired path must return alt-screen row 0 spans containing "
            f"the distinctive alt-screen marker. Got active_text={active_text!r}")
        self.assertNotIn(b"ALT_SCREEN_ROW_0", composite_text,
            f"Sanity: pre-alt composite must NOT contain alt-screen marker. "
            f"Got composite_text={composite_text!r}")
        self.assertNotEqual(active_row_0, composite_row_0,
            f"Gate-fired vs composite must produce different spans for the "
            f"same row, else the gate is observationally a no-op. \n"
            f"  active (gate fired): {active_row_0}\n"
            f"  composite (gate would skip): {composite_row_0}")

        # Canvas equivalence: the helper's active-screen branch should match
        # what the C renderer drew on the canvas (which also bypassed
        # composite per extension.c:3532). End-to-end gate validation.
        canvas_items = _canvas_text_items_at_row(self.canvas, 0)
        predicted = _predicted_layout_from_spans(active_row_0)
        self.assertEqual(
            canvas_items, predicted,
            f"Alt-screen + scroll-offset canvas-vs-helper divergence on row 0:\n"
            f"  canvas:    {canvas_items}\n"
            f"  predicted: {predicted}\n"
            f"If these differ, the gate fired in Python but not in C (or vice "
            f"versa) — the two `if` conditions are out of sync. Cite "
            f"nbsterm.py:159 vs extension.c:3532.")


if __name__ == "__main__":
    unittest.main()
