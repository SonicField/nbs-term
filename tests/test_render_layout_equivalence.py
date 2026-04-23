"""
test_render_layout_equivalence.py — Existence proof for option-(i) pure-Python path.

Falsifies (or fails to falsify) the premise behind theologian's pure-Python
implementation of `_pixel_to_cell_text_aware`: that Python can compute the same
per-cell pixel boundaries the C renderer produces, by replaying
`tkfont.Font.measure` prefix-sum logic over the spans returned by
`Terminal.get_screen()`.

The C renderer (`Terminal_render_frame` in generated/extension.c) places each
span at `x = PADDING + cumulative font.measure(prior spans via the named font)`,
where the named font is selected from attrs via the table at extension.c:3639-3642.
`render_font_measure` (extension.c:3375-3394) and Python's
`tkfont.Font.measure(text)` both invoke the Tcl command `font measure $font $text`
against the same Tcl interpreter — equivalent by construction.

This test verifies the equivalence end-to-end against the live canvas items the
C renderer produced. If it passes on Linux, theologian's structural claim
survives the empirical falsifier and the pure-Python option-(i) helper is safe
to implement. If it fails, get_screen()'s span representation does NOT faithfully
mirror what render_frame iterates over, and the C-side cell-boundary surface
would have to be added instead.

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
from nbsterm import DEFAULT_FONT_FAMILY, DEFAULT_FONT_SIZE, PADDING


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


def _attrs_to_font_tag(attrs):
    """Mirror of the C-side font_tag selection in extension.c:3639-3642."""
    if (attrs & 0x05) == 0x05:
        return "font_bold_italic"
    if attrs & 0x01:
        return "font_bold"
    if attrs & 0x04:
        return "font_italic"
    return "font_normal"


@unittest.skipIf(_root is None, "no display available (render_frame needs Tk)")
class TestRenderLayoutEquivalence(unittest.TestCase):
    """Falsifier #2: does Python prefix-sum of font.measure per span equal the
    canvas item positions produced by C's render_frame?

    Pass on Linux empirically validates theologian's pure-Python premise.
    Fail on Linux means the C-surfacing path is required.
    """

    @classmethod
    def setUpClass(cls):
        # Named fonts must exist before render_frame runs — same names
        # the C renderer looks up by tag at extension.c:3639-3642.
        cls.fonts = {
            "font_normal": tkfont.Font(
                root=_root, family=DEFAULT_FONT_FAMILY,
                size=DEFAULT_FONT_SIZE, name="font_normal"),
            "font_bold": tkfont.Font(
                root=_root, family=DEFAULT_FONT_FAMILY,
                size=DEFAULT_FONT_SIZE, weight="bold", name="font_bold"),
            "font_italic": tkfont.Font(
                root=_root, family=DEFAULT_FONT_FAMILY,
                size=DEFAULT_FONT_SIZE, slant="italic", name="font_italic"),
            "font_bold_italic": tkfont.Font(
                root=_root, family=DEFAULT_FONT_FAMILY,
                size=DEFAULT_FONT_SIZE, weight="bold", slant="italic",
                name="font_bold_italic"),
        }
        cls.char_width = cls.fonts["font_normal"].measure("M")
        cls.char_height = cls.fonts["font_normal"].metrics("linespace")
        cls.canvas = tkinter.Canvas(
            _root, width=80 * cls.char_width + 2 * PADDING,
            height=10 * cls.char_height + 2 * PADDING,
            bg="#000000", highlightthickness=0, borderwidth=0)
        cls.canvas.pack()
        _root.update_idletasks()

    @classmethod
    def tearDownClass(cls):
        if _root is not None:
            _root.destroy()

    def setUp(self):
        # Fresh terminal each test
        self.term = _nbsterm.Terminal(10, 80)
        # Wipe canvas + render state
        self.canvas.delete("all")
        self.term.render_reset()

    def _render(self):
        self.term.render_frame(
            _root.tk.interpaddr(),
            str(self.canvas),
            False,         # cursor_visible
            0,             # cursor_style (Block)
            "",            # cursor_color
            "#ffffff",     # default fg
            "#000000",     # default bg
            1.0,           # gamma
            self.char_width,
            self.char_height,
            PADDING,
        )
        _root.update_idletasks()

    def _canvas_text_items_at_row(self, row):
        """Return [(x, text, font_tag), ...] for each canvas text item whose y
        falls in the band of the given row. Sorted by x."""
        y_expected = PADDING + row * self.char_height
        items = []
        for item_id in self.canvas.find_all():
            if self.canvas.type(item_id) != "text":
                continue
            coords = self.canvas.coords(item_id)
            if not coords:
                continue
            x, y = coords[0], coords[1]
            # Tk reports floats for canvas coords; row band is exact-integer y.
            if abs(y - y_expected) > 0.5:
                continue
            text = self.canvas.itemcget(item_id, "text")
            font_tag = self.canvas.itemcget(item_id, "font")
            items.append((int(round(x)), text, font_tag))
        items.sort(key=lambda t: t[0])
        return items

    def _python_predicted_layout(self, row):
        """Replay font.measure prefix-sum from get_screen() spans for one row.
        Mirrors the C renderer's per-span x accumulation at extension.c:3597-3653.
        """
        screen = self.term.get_screen("#ffffff", "#000000")
        if row >= len(screen):
            return []
        spans = screen[row]
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
            x += self.fonts[font_tag].measure(text)
        return out

    def test_single_span_plain_ascii(self):
        """Plain ASCII text on row 0 → canvas and Python agree on (x, text, font)."""
        self.term.feed(b"Hello, World! 1234567890")
        self._render()
        canvas_items = self._canvas_text_items_at_row(0)
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
        """Bold + plain mix: SGR 1 turns on bold, SGR 22 turns it off.

        Each attr change creates a new span; canvas should produce one text item
        per span, all aligned at the prefix-sum boundaries Python predicts.
        """
        # ESC[1m bold, ESC[22m normal-intensity
        self.term.feed(b"AAA\x1b[1mBBB\x1b[22mCCC")
        self._render()
        canvas_items = self._canvas_text_items_at_row(0)
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
                canvas_items = self._canvas_text_items_at_row(row)
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


if __name__ == "__main__":
    unittest.main()
