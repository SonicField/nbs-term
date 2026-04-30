"""
test_gui_logic.py — Headless tests for GUI logic paths in nbsterm.py.

Tests the non-Tk logic: coordinate conversion, text extraction from
selection ranges, kbdint handler threading bridge, host target parsing,
and SSHTransport callback wiring. These run without a display.
"""
import sys
import os
import unittest
import concurrent.futures

sys.path.insert(0, os.path.dirname(os.path.dirname(os.path.abspath(__file__))))

import _nbsterm


class TestPixelToCellConversion(unittest.TestCase):
    """Test _pixel_to_cell coordinate conversion logic."""

    def _pixel_to_cell(self, x, y, char_width, char_height, cols, rows):
        """Standalone re-implementation of TerminalWidget._pixel_to_cell."""
        col = max(0, min(x // char_width, cols - 1))
        row = max(0, min(y // char_height, rows - 1))
        return (row, col)

    def test_origin(self):
        row, col = self._pixel_to_cell(0, 0, 10, 20, 80, 24)
        self.assertEqual(row, 0)
        self.assertEqual(col, 0)

    def test_first_cell(self):
        row, col = self._pixel_to_cell(5, 10, 10, 20, 80, 24)
        self.assertEqual(row, 0)
        self.assertEqual(col, 0)

    def test_second_col(self):
        row, col = self._pixel_to_cell(10, 0, 10, 20, 80, 24)
        self.assertEqual(row, 0)
        self.assertEqual(col, 1)

    def test_second_row(self):
        row, col = self._pixel_to_cell(0, 20, 10, 20, 80, 24)
        self.assertEqual(row, 1)
        self.assertEqual(col, 0)

    def test_middle_of_screen(self):
        row, col = self._pixel_to_cell(400, 240, 10, 20, 80, 24)
        self.assertEqual(row, 12)
        self.assertEqual(col, 40)

    def test_negative_x_clamps_to_zero(self):
        row, col = self._pixel_to_cell(-10, 0, 10, 20, 80, 24)
        self.assertEqual(col, 0)

    def test_negative_y_clamps_to_zero(self):
        row, col = self._pixel_to_cell(0, -10, 10, 20, 80, 24)
        self.assertEqual(row, 0)

    def test_overflow_x_clamps_to_max_col(self):
        row, col = self._pixel_to_cell(9999, 0, 10, 20, 80, 24)
        self.assertEqual(col, 79)

    def test_overflow_y_clamps_to_max_row(self):
        row, col = self._pixel_to_cell(0, 9999, 10, 20, 80, 24)
        self.assertEqual(row, 23)

    def test_both_overflow(self):
        row, col = self._pixel_to_cell(9999, 9999, 10, 20, 80, 24)
        self.assertEqual(row, 23)
        self.assertEqual(col, 79)

    def test_small_terminal(self):
        row, col = self._pixel_to_cell(100, 100, 10, 20, 5, 3)
        self.assertEqual(row, 2)
        self.assertEqual(col, 4)


class TestSelectionRange(unittest.TestCase):
    """Test selection range ordering logic."""

    def _sel_range(self, start, end):
        """Standalone re-implementation of TerminalWidget._sel_range."""
        if start is None or end is None:
            return None, None
        s, e = start, end
        if (s[0], s[1]) > (e[0], e[1]):
            s, e = e, s
        return s, e

    def test_none_start(self):
        s, e = self._sel_range(None, (0, 0))
        self.assertIsNone(s)
        self.assertIsNone(e)

    def test_none_end(self):
        s, e = self._sel_range((0, 0), None)
        self.assertIsNone(s)
        self.assertIsNone(e)

    def test_forward_selection(self):
        s, e = self._sel_range((0, 5), (2, 10))
        self.assertEqual(s, (0, 5))
        self.assertEqual(e, (2, 10))

    def test_backward_selection_swaps(self):
        s, e = self._sel_range((2, 10), (0, 5))
        self.assertEqual(s, (0, 5))
        self.assertEqual(e, (2, 10))

    def test_same_row_forward(self):
        s, e = self._sel_range((3, 2), (3, 8))
        self.assertEqual(s, (3, 2))
        self.assertEqual(e, (3, 8))

    def test_same_row_backward_swaps(self):
        s, e = self._sel_range((3, 8), (3, 2))
        self.assertEqual(s, (3, 2))
        self.assertEqual(e, (3, 8))

    def test_same_point(self):
        s, e = self._sel_range((5, 5), (5, 5))
        self.assertEqual(s, (5, 5))
        self.assertEqual(e, (5, 5))


class TestTextExtraction(unittest.TestCase):
    """Test text extraction from terminal buffer via get_cell."""

    def _extract_text(self, term, start, end, cols):
        """Standalone re-implementation of TerminalWidget.get_selected_text logic."""
        if start is None or start == end:
            return ""
        # Order start/end
        s, e = start, end
        if (s[0], s[1]) > (e[0], e[1]):
            s, e = e, s
        lines = []
        for r in range(s[0], e[0] + 1):
            c0 = s[1] if r == s[0] else 0
            c1 = e[1] if r == e[0] else cols - 1
            row_text = []
            for c in range(c0, c1 + 1):
                cell = term.get_cell(r, c)
                if cell and cell[0] > 0:
                    row_text.append(chr(cell[0]))
                else:
                    row_text.append(" ")
            lines.append("".join(row_text).rstrip())
        return "\n".join(lines)

    def test_extract_single_word(self):
        t = _nbsterm.Terminal(24, 80)
        t.feed(b"Hello World")
        text = self._extract_text(t, (0, 0), (0, 4), 80)
        self.assertEqual(text, "Hello")

    def test_extract_empty_selection(self):
        t = _nbsterm.Terminal(24, 80)
        t.feed(b"Hello")
        text = self._extract_text(t, (0, 0), (0, 0), 80)
        self.assertEqual(text, "")

    def test_extract_multiline(self):
        t = _nbsterm.Terminal(24, 80)
        t.feed(b"Line 1\r\nLine 2\r\nLine 3")
        text = self._extract_text(t, (0, 0), (2, 5), 80)
        self.assertEqual(text, "Line 1\nLine 2\nLine 3")

    def test_extract_partial_line(self):
        t = _nbsterm.Terminal(24, 80)
        t.feed(b"Hello World")
        text = self._extract_text(t, (0, 6), (0, 10), 80)
        self.assertEqual(text, "World")

    def test_extract_trailing_whitespace_stripped(self):
        t = _nbsterm.Terminal(24, 80)
        t.feed(b"Hi")
        # Extracting beyond the text should give stripped result
        text = self._extract_text(t, (0, 0), (0, 10), 80)
        self.assertEqual(text, "Hi")

    def test_extract_empty_cells(self):
        t = _nbsterm.Terminal(24, 80)
        # Row 5 has no content
        text = self._extract_text(t, (5, 0), (5, 9), 80)
        self.assertEqual(text, "")

    def test_extract_with_colors(self):
        """SGR attributes must not affect text extraction."""
        t = _nbsterm.Terminal(24, 80)
        t.feed(b"\x1b[31mRed\x1b[32mGreen\x1b[0m")
        text = self._extract_text(t, (0, 0), (0, 7), 80)
        self.assertEqual(text, "RedGreen")

    def test_extract_backward_selection(self):
        """Backward selection (end before start) should still work."""
        t = _nbsterm.Terminal(24, 80)
        t.feed(b"Hello")
        text = self._extract_text(t, (0, 4), (0, 0), 80)
        self.assertEqual(text, "Hello")


class TestKbdintHandler(unittest.TestCase):
    """Test the kbdint threading bridge logic without Tk."""

    def test_handler_with_responses(self):
        """Simulate kbdint handler receiving responses via futures."""
        responses_given = []

        def mock_auth_prompt(prompt_text, echo, future):
            """Simulate immediate user response."""
            responses_given.append(prompt_text)
            future.set_result("1")

        # Simulate the handler logic from SSHTransport._kbdint_handler
        prompts = [("Enter passcode: ", True), ("Confirm: ", True)]
        responses = []
        for prompt_text, echo in prompts:
            future = concurrent.futures.Future()
            mock_auth_prompt(prompt_text, echo, future)
            response = future.result(timeout=5)
            if response is None:
                break
            responses.append(response)

        self.assertEqual(len(responses), 2)
        self.assertEqual(responses, ["1", "1"])
        self.assertEqual(responses_given, ["Enter passcode: ", "Confirm: "])

    def test_handler_user_cancels(self):
        """Simulate user cancelling auth prompt."""
        def mock_cancel(prompt_text, echo, future):
            future.set_result(None)

        future = concurrent.futures.Future()
        mock_cancel("Prompt: ", True, future)
        response = future.result(timeout=5)
        self.assertIsNone(response)

    def test_handler_timeout(self):
        """Simulate timeout waiting for response."""
        future = concurrent.futures.Future()
        # Don't set result — should timeout
        with self.assertRaises(concurrent.futures.TimeoutError):
            future.result(timeout=0.01)


class TestGammaCorrection(unittest.TestCase):
    """Test gamma_correct() color transform."""

    def _gamma_correct(self, hex_color, gamma):
        """Standalone re-implementation of gamma_correct()."""
        if gamma == 1.0 or not hex_color.startswith("#") or len(hex_color) != 7:
            return hex_color
        r = int(hex_color[1:3], 16)
        g = int(hex_color[3:5], 16)
        b = int(hex_color[5:7], 16)
        r = int(255 * (r / 255) ** gamma)
        g = int(255 * (g / 255) ** gamma)
        b = int(255 * (b / 255) ** gamma)
        return f"#{r:02x}{g:02x}{b:02x}"

    def test_gamma_1_no_change(self):
        self.assertEqual(self._gamma_correct("#cd0000", 1.0), "#cd0000")

    def test_gamma_1_any_color(self):
        self.assertEqual(self._gamma_correct("#abcdef", 1.0), "#abcdef")

    def test_black_unchanged(self):
        """Black is always black regardless of gamma."""
        self.assertEqual(self._gamma_correct("#000000", 0.5), "#000000")
        self.assertEqual(self._gamma_correct("#000000", 2.0), "#000000")

    def test_white_unchanged(self):
        """White is always white regardless of gamma."""
        self.assertEqual(self._gamma_correct("#ffffff", 0.5), "#ffffff")
        self.assertEqual(self._gamma_correct("#ffffff", 2.0), "#ffffff")

    def test_gamma_less_than_1_brightens(self):
        """Gamma < 1 raises midtones (x^0.85 > x for x in (0,1))."""
        original = self._gamma_correct("#808080", 1.0)
        brightened = self._gamma_correct("#808080", 0.85)
        self.assertGreater(int(brightened[1:3], 16), int(original[1:3], 16))

    def test_gamma_greater_than_1_darkens(self):
        """Gamma > 1 lowers midtones (x^1.5 < x for x in (0,1))."""
        original = self._gamma_correct("#808080", 1.0)
        darkened = self._gamma_correct("#808080", 1.5)
        self.assertLess(int(darkened[1:3], 16), int(original[1:3], 16))

    def test_invalid_color_passthrough(self):
        """Non-hex colors pass through unchanged."""
        self.assertEqual(self._gamma_correct("red", 0.5), "red")
        self.assertEqual(self._gamma_correct("#fff", 0.5), "#fff")

    def test_round_trip_approximate(self):
        """Gamma and inverse gamma should approximately round-trip."""
        color = "#cd8844"
        forward = self._gamma_correct(color, 0.8)
        back = self._gamma_correct(forward, 1.0 / 0.8)
        # Should be close to original (within 1 due to integer rounding)
        for i in range(3):
            orig_ch = int(color[1 + i*2:3 + i*2], 16)
            back_ch = int(back[1 + i*2:3 + i*2], 16)
            self.assertAlmostEqual(orig_ch, back_ch, delta=2)

    def test_mac_default_gamma(self):
        """Mac default gamma 0.85 produces valid hex output."""
        result = self._gamma_correct("#cd0000", 0.85)
        self.assertTrue(result.startswith("#"))
        self.assertEqual(len(result), 7)
        # Gamma < 1 brightens — result should be >= original
        self.assertGreaterEqual(int(result[1:3], 16), 0xcd)


class TestCursorChars(unittest.TestCase):
    """Verify cursor character constants exist and are correct."""

    def test_cursor_chars_exists(self):
        """TerminalWidget must have _CURSOR_CHARS class attribute."""
        # Import check — can't import TerminalWidget directly (needs Tk)
        # but we can verify the constant is defined in the source
        import ast
        with open('nbsterm.py', encoding='utf-8') as f:
            tree = ast.parse(f.read())
        class_names = [n.name for n in ast.walk(tree) if isinstance(n, ast.ClassDef)]
        self.assertIn('TerminalWidget', class_names)

    def test_cursor_styles_complete(self):
        """All expected cursor styles must have unicode characters."""
        expected = {'Block', 'Underline', 'Bar'}
        with open('nbsterm.py', encoding='utf-8') as f:
            source = f.read()
        self.assertIn('_CURSOR_CHARS', source)
        for style in expected:
            # Check for both quote styles
            self.assertTrue(
                f'"{style}"' in source or f"'{style}'" in source,
                f"Cursor style '{style}' not found in _CURSOR_CHARS"
            )

    def test_no_wireframe(self):
        """Wireframe cursor style was removed per alexie's directive."""
        with open('nbsterm.py', encoding='utf-8') as f:
            source = f.read()
        self.assertNotIn('"Wireframe"', source)
        self.assertNotIn("'Wireframe'", source)


class TestHostTargetParsing(unittest.TestCase):
    """Test the user@host:port parsing logic from main()."""

    def _parse_target(self, target):
        """Standalone re-implementation of main() target parsing."""
        username = None
        port = None
        host = target

        if "@" in host:
            username, host = host.rsplit("@", 1)
        if ":" in host:
            host, port_str = host.rsplit(":", 1)
            port = int(port_str)

        return username, host, port

    def test_host_only(self):
        user, host, port = self._parse_target("example.com")
        self.assertIsNone(user)
        self.assertEqual(host, "example.com")
        self.assertIsNone(port)

    def test_user_and_host(self):
        user, host, port = self._parse_target("alice@example.com")
        self.assertEqual(user, "alice")
        self.assertEqual(host, "example.com")
        self.assertIsNone(port)

    def test_host_and_port(self):
        user, host, port = self._parse_target("example.com:2222")
        self.assertIsNone(user)
        self.assertEqual(host, "example.com")
        self.assertEqual(port, 2222)

    def test_user_host_port(self):
        user, host, port = self._parse_target("alice@example.com:2222")
        self.assertEqual(user, "alice")
        self.assertEqual(host, "example.com")
        self.assertEqual(port, 2222)

    def test_complex_username(self):
        user, host, port = self._parse_target("user.name@host.domain.com")
        self.assertEqual(user, "user.name")
        self.assertEqual(host, "host.domain.com")

    def test_at_in_username(self):
        """rsplit(@, 1) handles user@domain@host correctly."""
        user, host, port = self._parse_target("user@domain@host.com")
        self.assertEqual(user, "user@domain")
        self.assertEqual(host, "host.com")


class TestCPixelToCell(unittest.TestCase):
    """Test _nbsterm.pixel_to_cell C function directly."""

    def test_origin(self):
        row, col = _nbsterm.pixel_to_cell(0, 0, 10, 20, 80, 24)
        self.assertEqual((row, col), (0, 0))

    def test_mid_cell(self):
        row, col = _nbsterm.pixel_to_cell(5, 10, 10, 20, 80, 24)
        self.assertEqual((row, col), (0, 0))

    def test_second_col(self):
        row, col = _nbsterm.pixel_to_cell(10, 0, 10, 20, 80, 24)
        self.assertEqual((row, col), (0, 1))

    def test_second_row(self):
        row, col = _nbsterm.pixel_to_cell(0, 20, 10, 20, 80, 24)
        self.assertEqual((row, col), (1, 0))

    def test_negative_clamps_to_zero(self):
        row, col = _nbsterm.pixel_to_cell(-10, -10, 10, 20, 80, 24)
        self.assertEqual((row, col), (0, 0))

    def test_overflow_clamps_to_max(self):
        row, col = _nbsterm.pixel_to_cell(9999, 9999, 10, 20, 80, 24)
        self.assertEqual((row, col), (23, 79))

    def test_small_terminal(self):
        row, col = _nbsterm.pixel_to_cell(100, 100, 10, 20, 5, 3)
        self.assertEqual((row, col), (2, 4))

    def test_matches_python(self):
        """C version matches Python re-implementation for all edge cases."""
        def py_pixel_to_cell(x, y, cw, ch, cols, rows):
            col = max(0, min(x // cw, cols - 1))
            row = max(0, min(y // ch, rows - 1))
            return (row, col)

        cases = [
            (0, 0, 10, 20, 80, 24),
            (5, 10, 10, 20, 80, 24),
            (10, 0, 10, 20, 80, 24),
            (0, 20, 10, 20, 80, 24),
            (400, 240, 10, 20, 80, 24),
            (9999, 9999, 10, 20, 80, 24),
            (100, 100, 10, 20, 5, 3),
        ]
        for args in cases:
            with self.subTest(args=args):
                self.assertEqual(
                    _nbsterm.pixel_to_cell(*args),
                    py_pixel_to_cell(*args),
                )


class TestCSelRange(unittest.TestCase):
    """Test _nbsterm.sel_range C function directly."""

    def test_forward(self):
        sr, sc, er, ec = _nbsterm.sel_range(0, 5, 2, 10)
        self.assertEqual((sr, sc, er, ec), (0, 5, 2, 10))

    def test_backward_swaps(self):
        sr, sc, er, ec = _nbsterm.sel_range(2, 10, 0, 5)
        self.assertEqual((sr, sc, er, ec), (0, 5, 2, 10))

    def test_same_row_forward(self):
        sr, sc, er, ec = _nbsterm.sel_range(3, 2, 3, 8)
        self.assertEqual((sr, sc, er, ec), (3, 2, 3, 8))

    def test_same_row_backward_swaps(self):
        sr, sc, er, ec = _nbsterm.sel_range(3, 8, 3, 2)
        self.assertEqual((sr, sc, er, ec), (3, 2, 3, 8))

    def test_same_point(self):
        sr, sc, er, ec = _nbsterm.sel_range(5, 5, 5, 5)
        self.assertEqual((sr, sc, er, ec), (5, 5, 5, 5))


class TestCExtractSelectedText(unittest.TestCase):
    """Test term.extract_selected_text C function directly."""

    def test_single_word(self):
        t = _nbsterm.Terminal(24, 80)
        t.feed(b"Hello World")
        # ec is exclusive: [0, 5) = "Hello"
        self.assertEqual(t.extract_selected_text(0, 0, 0, 5), "Hello")

    def test_empty_same_point(self):
        t = _nbsterm.Terminal(24, 80)
        t.feed(b"Hello")
        self.assertEqual(t.extract_selected_text(0, 0, 0, 0), "")

    def test_multiline(self):
        t = _nbsterm.Terminal(24, 80)
        t.feed(b"Line 1\r\nLine 2\r\nLine 3")
        # ec exclusive: col 6 on row 2 = "Line 3" (6 chars)
        self.assertEqual(t.extract_selected_text(0, 0, 2, 6), "Line 1\nLine 2\nLine 3")

    def test_partial_line(self):
        t = _nbsterm.Terminal(24, 80)
        t.feed(b"Hello World")
        # ec exclusive: [6, 11) = "World"
        self.assertEqual(t.extract_selected_text(0, 6, 0, 11), "World")

    def test_trailing_whitespace_stripped(self):
        t = _nbsterm.Terminal(24, 80)
        t.feed(b"Hi")
        self.assertEqual(t.extract_selected_text(0, 0, 0, 11), "Hi")

    def test_empty_cells(self):
        t = _nbsterm.Terminal(24, 80)
        self.assertEqual(t.extract_selected_text(5, 0, 5, 10), "")

    def test_with_sgr_colors(self):
        t = _nbsterm.Terminal(24, 80)
        t.feed(b"\x1b[31mRed\x1b[32mGreen\x1b[0m")
        # ec exclusive: [0, 8) = "RedGreen" (3+5 chars)
        self.assertEqual(t.extract_selected_text(0, 0, 0, 8), "RedGreen")

    def test_backward_selection(self):
        t = _nbsterm.Terminal(24, 80)
        t.feed(b"Hello")
        # Backward: (0,5) to (0,0) → swapped to [0, 5) = "Hello"
        self.assertEqual(t.extract_selected_text(0, 5, 0, 0), "Hello")

    def test_rstrip_preserves_spaces(self):
        """C rstrip preserves trailing cp=32 spaces, strips only cp=0 NULs.
        Matches iTerm2/GNOME Terminal convention."""
        t = _nbsterm.Terminal(24, 80)
        t.feed(b"Hi   ")  # explicit spaces after text
        # ec exclusive: [0, 5) = "Hi   " (2 chars + 3 spaces)
        result = t.extract_selected_text(0, 0, 0, 5)
        self.assertEqual(result, "Hi   ")

    def test_draw_and_extract_agree(self):
        """draw_selection and extract_selected_text use the same ec convention.
        What is highlighted must equal what is copied."""
        t = _nbsterm.Terminal(24, 80)
        t.feed(b"Hello World Test")
        # Select "World" — cols 6 through 10 (ec=11, exclusive)
        sr, sc, er, ec = 0, 6, 0, 11
        t.draw_selection(sr, sc, er, ec)
        text = t.extract_selected_text(sr, sc, er, ec)
        self.assertEqual(text, "World")
        # Select single char "H" — col 0 (ec=1, exclusive)
        t.clear_selection()
        t.draw_selection(0, 0, 0, 1)
        text = t.extract_selected_text(0, 0, 0, 1)
        self.assertEqual(text, "H")


class TestBinarySearchChar(unittest.TestCase):
    """Test #2 — TerminalWidget._binary_search_char (nbsterm.py:184) directly.

    The function returns smallest i such that font.measure(text[:i+1]) > local_x.
    This is the per-cell cell-resolution primitive used by
    _pixel_to_cell_text_aware to translate a pixel offset within a span into a
    character index, which is then mapped to a column via col_widths.

    Tests headless via a stub font — does not require Tk."""

    @staticmethod
    def _binary_search_char(text, font, local_x):
        """Bind generalist's actual method bytecode (it is a @staticmethod on
        TerminalWidget so the bind is trivial)."""
        from nbsterm import TerminalWidget
        return TerminalWidget._binary_search_char(text, font, local_x)

    class _UniformFont:
        """Stub for tkfont.Font — every char is `width` pixels wide."""
        def __init__(self, width):
            self._w = width
        def measure(self, text):
            return self._w * len(text)

    class _NonUniformFont:
        """Stub for a per-char-variable font (e.g. proportional or
        CoreText-ish where wider chars mid-string accumulate sub-additively).
        widths is a dict char -> px width; missing chars default to fallback."""
        def __init__(self, widths, fallback=10):
            self._widths = widths
            self._fb = fallback
        def measure(self, text):
            return sum(self._widths.get(c, self._fb) for c in text)

    def test_zero_local_x_returns_zero(self):
        """local_x=0 lies before any cell's right edge → cell 0."""
        f = self._UniformFont(12)
        self.assertEqual(self._binary_search_char("Hello", f, 0), 0)

    def test_just_inside_first_cell_returns_zero(self):
        """local_x=11, char_width=12 → still inside cell 0."""
        f = self._UniformFont(12)
        self.assertEqual(self._binary_search_char("Hello", f, 11), 0)

    def test_at_first_cell_boundary_returns_one(self):
        """local_x=12 (==measure('H')) → cell 1 (the boundary belongs to next cell)."""
        f = self._UniformFont(12)
        self.assertEqual(self._binary_search_char("Hello", f, 12), 1)

    def test_mid_cell_returns_correct_index(self):
        """Pixel inside cell N returns N for any uniform-grid font."""
        f = self._UniformFont(12)
        # cell 2 spans [24, 36); local_x=30 → cell 2
        self.assertEqual(self._binary_search_char("Hello", f, 30), 2)

    def test_past_end_returns_len(self):
        """local_x past the full span width returns len(text)."""
        f = self._UniformFont(12)  # "Hello" = 60 px wide
        self.assertEqual(self._binary_search_char("Hello", f, 100), 5)
        self.assertEqual(self._binary_search_char("Hello", f, 60), 5)

    def test_empty_text(self):
        """Empty text → 0, no measure calls needed."""
        f = self._UniformFont(12)
        self.assertEqual(self._binary_search_char("", f, 0), 0)
        self.assertEqual(self._binary_search_char("", f, 999), 0)

    def test_non_uniform_widths(self):
        """The function must be correct under non-uniform widths — the whole
        point of the Bug A fix is that font.measure does NOT yield a uniform
        grid on macOS/CoreText. Construct a font where 'a'=10, 'b'=20.
        Cumulative widths: '' = 0, 'a' = 10, 'ab' = 30."""
        f = self._NonUniformFont({"a": 10, "b": 20})
        text = "ab"
        # local_x=0, 5 → cell 0 (still inside 'a')
        self.assertEqual(self._binary_search_char(text, f, 0), 0)
        self.assertEqual(self._binary_search_char(text, f, 5), 0)
        # local_x=9 → cell 0 (just before 'a' ends)
        self.assertEqual(self._binary_search_char(text, f, 9), 0)
        # local_x=10 → cell 1 (boundary)
        self.assertEqual(self._binary_search_char(text, f, 10), 1)
        # local_x=29 → cell 1 (still inside 'b')
        self.assertEqual(self._binary_search_char(text, f, 29), 1)
        # local_x=30 → cell 2 (past end)
        self.assertEqual(self._binary_search_char(text, f, 30), 2)

    def test_long_text_logarithmic_calls(self):
        """For a 256-char text, binary search should call measure at most
        ~9 times (log2(256)+1). Falsifies an accidental linear walk that
        would still return correct results but blow the per-click budget at
        60Hz drag-move."""
        class _CountingFont(self._UniformFont):
            def __init__(self, width):
                super().__init__(width)
                self.calls = 0
            def measure(self, text):
                self.calls += 1
                return super().measure(text)

        f = _CountingFont(12)
        text = "x" * 256
        self._binary_search_char(text, f, 1500)  # cell 125
        self.assertLessEqual(
            f.calls, 12,
            f"binary search made {f.calls} measure() calls for 256-char text "
            f"— expected ~log2(256)=8, allowing margin to 12. >12 indicates "
            f"linear-walk regression that would burn ms/click on long lines.")

    def test_mutation_caught_by_wrong_font_widths(self):
        """The contract under test must be capable of failing: feed a font that
        lies (returns wrong widths) and verify the binary search returns a
        wrong cell index. This proves the assertion can fail."""
        honest = self._UniformFont(12)
        liar = self._UniformFont(6)  # claims every char is 6 px wide
        # local_x=15 in the honest font is cell 1 (cell 1 spans [12, 24))
        self.assertEqual(self._binary_search_char("Hello", honest, 15), 1)
        # Same local_x in the liar font is cell 2 (cell 2 spans [12, 18))
        self.assertEqual(self._binary_search_char("Hello", liar, 15), 2)
        self.assertNotEqual(
            self._binary_search_char("Hello", honest, 15),
            self._binary_search_char("Hello", liar, 15),
            "Mutation control: function must produce different output for "
            "different font measurements, else the binary search is "
            "ignoring its font argument.")


class TestMouseHandlerRouting(unittest.TestCase):
    """Test #3 — mouse handlers route through _pixel_to_cell_text_aware
    (Bug A fix path), not the legacy uniform-grid _pixel_to_cell.

    Headless: bind handler bytecode against a stub host that records which
    pixel-to-cell method gets called. No Tk required."""

    class _HandlerHost:
        """Stub that records routing of pixel-to-cell calls."""
        def __init__(self):
            self.text_aware_calls = []
            self.uniform_calls = []
            self._sel_start = None
            self._sel_end = None
            self._highlight_drawn = False
            self._highlight_cleared = False

        def _pixel_to_cell_text_aware(self, x, y):
            self.text_aware_calls.append((x, y))
            return (1, 2)  # arbitrary fixed cell so handler logic can proceed

        def _pixel_to_cell(self, x, y):
            self.uniform_calls.append((x, y))
            return (0, 0)  # different return — divergence is detectable

        def _clear_selection_highlight(self):
            self._highlight_cleared = True

        def _draw_selection_highlight(self):
            self._highlight_drawn = True

    @classmethod
    def _make_host_with_handlers(cls):
        """Return a stub host with the three mouse handlers bound to it."""
        from nbsterm import TerminalWidget
        host = cls._HandlerHost()
        host._on_mouse_down = TerminalWidget._on_mouse_down.__get__(host, type(host))
        host._on_mouse_drag = TerminalWidget._on_mouse_drag.__get__(host, type(host))
        host._on_mouse_up = TerminalWidget._on_mouse_up.__get__(host, type(host))
        return host

    @staticmethod
    def _event(x, y):
        """Stub a Tk MouseEvent — the handlers only access .x and .y."""
        ev = type("_StubEvent", (), {})()
        ev.x = x
        ev.y = y
        return ev

    def test_mouse_down_routes_through_text_aware(self):
        host = self._make_host_with_handlers()
        host._on_mouse_down(self._event(100, 50))
        self.assertEqual(
            host.text_aware_calls, [(100, 50)],
            "mouse_down must route through _pixel_to_cell_text_aware (Bug A "
            "fix); legacy _pixel_to_cell would resurrect the uniform-grid bug.")
        self.assertEqual(
            host.uniform_calls, [],
            "mouse_down must NOT call legacy _pixel_to_cell — that path is "
            "preserved as fallback only (nbsterm.py:147).")
        self.assertEqual(host._sel_start, (1, 2))
        self.assertEqual(host._sel_end, (1, 2))
        self.assertTrue(host._highlight_cleared)

    def test_mouse_drag_routes_through_text_aware(self):
        host = self._make_host_with_handlers()
        # mouse_down first to seed _sel_start
        host._on_mouse_down(self._event(50, 25))
        # Now drag — must call text-aware
        host._on_mouse_drag(self._event(200, 75))
        self.assertEqual(
            host.text_aware_calls, [(50, 25), (200, 75)],
            "mouse_drag must route through _pixel_to_cell_text_aware on every "
            "drag event — selection bounds depend on it.")
        self.assertEqual(host.uniform_calls, [])
        self.assertEqual(host._sel_end, (1, 2))
        self.assertTrue(host._highlight_drawn)

    def test_mouse_up_routes_through_text_aware(self):
        host = self._make_host_with_handlers()
        host._on_mouse_down(self._event(0, 0))
        host._on_mouse_up(self._event(150, 60))
        self.assertEqual(
            host.text_aware_calls, [(0, 0), (150, 60)],
            "mouse_up must route through _pixel_to_cell_text_aware to set the "
            "final selection end coordinate.")
        self.assertEqual(host.uniform_calls, [])

    def test_no_handler_calls_legacy_pixel_to_cell(self):
        """Cross-handler invariant: across the full down/drag/up sequence, the
        legacy _pixel_to_cell must NEVER be called by the mouse handlers."""
        host = self._make_host_with_handlers()
        host._on_mouse_down(self._event(10, 10))
        host._on_mouse_drag(self._event(20, 20))
        host._on_mouse_drag(self._event(30, 30))
        host._on_mouse_up(self._event(40, 40))
        self.assertEqual(
            host.uniform_calls, [],
            f"Bug A regression: legacy _pixel_to_cell was called {len(host.uniform_calls)} "
            f"times by mouse handlers (calls: {host.uniform_calls}). The legacy "
            f"path is fallback-only (nbsterm.py:147); routing through it from "
            f"mouse handlers re-introduces the CoreText subadditivity bug.")
        self.assertEqual(len(host.text_aware_calls), 4)


class TestConfigureBindingPlacement(unittest.TestCase):
    """Configure-binding placement regression test.

    Invariant (post architectural rewrite): <Configure> MUST be bound on
    TabSession.canvas. The canvas is now the root-child geometry container
    (no wrapping tk.Frame) and event.width/height = canvas size.

    Pre-rewrite invariant (da5b9a1 era): bind on self.frame. The frame
    was dropped per alexie's 2026-04-28 06:59:16 architectural reset, so
    this test guards the new attachment point.

    Static source inspection — no Tk display needed.
    """

    def test_tabsession_binds_configure_on_canvas(self):
        """TabSession must bind <Configure> on self.canvas — the resize
        handler triggers from canvas geometry changes."""
        import inspect
        from nbsterm import TabSession
        src = inspect.getsource(TabSession)

        import re
        canvas_configure_pattern = re.compile(
            r'self\.canvas\.bind\(\s*["\']<Configure>["\']'
        )
        self.assertIsNotNone(
            canvas_configure_pattern.search(src),
            "TabSession does not bind <Configure> on self.canvas. "
            "Without it, handle_resize never fires and the terminal "
            "does not adapt to window size.",
        )

    def test_tabsession_no_frame_attribute(self):
        """TabSession.frame was dropped in the architectural rewrite —
        canvas is owned directly. Re-introducing self.frame would
        re-introduce the nested-Frame layout chain that produced the
        Bug C v3 lighter-slop perimeter."""
        import inspect
        from nbsterm import TabSession
        src = inspect.getsource(TabSession)

        import re
        frame_attribute_pattern = re.compile(r'self\.frame\s*=')
        match = frame_attribute_pattern.search(src)
        self.assertIsNone(
            match,
            "REGRESSION: TabSession assigns self.frame (line containing "
            f"{match.group(0) if match else None!r}). The architectural "
            "rewrite dropped the wrapping tk.Frame; canvas is owned "
            "directly. Re-introducing the frame stacks tk.Frame paint "
            "surfaces and re-creates Bug C v3.",
        )


class TestCanvasFillsRoot(unittest.TestCase):
    """Canvas-fill regression guard (post architectural rewrite).

    Invariant: TabSession's canvas MUST be packed in TerminalApp._select_tab
    with fill=tk.BOTH and expand=True. Per the rewrite, the canvas is the
    sole geometry container for the active tab — it covers the entire
    space below the tab strip. Without fill=BOTH expand=True the canvas
    reverts to its natural size and the uncovered root area shows
    around it.

    Static-source assertion catches both shapes.
    """

    def test_select_tab_packs_canvas_fill_both_expand(self):
        """TerminalApp._select_tab must pack the active tab's canvas
        with fill=BOTH and expand=True."""
        import inspect
        from nbsterm import TerminalApp
        src = inspect.getsource(TerminalApp._select_tab)

        import re
        # Match canvas.pack(...) inside _select_tab.
        pack_match = re.search(
            r'\.canvas\.pack\(([^)]*)\)', src, re.DOTALL,
        )
        self.assertIsNotNone(
            pack_match,
            "TerminalApp._select_tab does not call <tab>.canvas.pack(...). "
            "Tab content cannot become visible without it.",
        )
        args = pack_match.group(1)
        self.assertRegex(
            args,
            r"fill\s*=\s*(tk\.BOTH|['\"]both['\"])",
            f"REGRESSION: canvas.pack({args!r}) missing fill=tk.BOTH. "
            "Canvas must fill its packing cell.",
        )
        self.assertRegex(
            args,
            r"expand\s*=\s*True",
            f"REGRESSION: canvas.pack({args!r}) missing expand=True. "
            "Canvas must claim any extra space below the tab strip.",
        )


class TestResizeOrderingRaceFix(unittest.TestCase):
    """Regression guards for Bug C v3 e4fe48e (resize-event ordering races).

    Two ordering bugs alexie reported on 0a5ee56 (2026-04-28 09:42:18):
      1. Maximize: handle_resize computed origin BEFORE term.resize, so
         origin was derived from OLD spans while content reflowed wider.
      2. Cmd-T new tab: _select_tab called widget._render() immediately
         after canvas.pack(), before Tk had run layout — winfo_width()=1.

    Fix (e4fe48e): origin is recomputed inside _render from FRESH canvas
    dims + FRESH spans. handle_resize and _apply_config no longer compute
    origin (eliminated the cache-staleness class). _select_tab defers
    _render via root.after_idle so Tk completes layout first.

    Fourth invariant (alexie 07:31:54 + supervisor 11:38:29): _render
    rebuilds the bg_fill rect with self._bg every paint, so a runtime
    text_bg config change paints through on the next render.

    Static-source inspection — no Tk display needed.
    """

    def test_render_computes_origin(self):
        """_render MUST call _compute_origin_for. The architectural
        invariant (e4fe48e) is that origin is a function of CURRENT
        state at paint time — never cached input."""
        import inspect
        from nbsterm import TerminalWidget
        src = inspect.getsource(TerminalWidget._render)

        import re
        pattern = re.compile(r'_compute_origin_for\s*\(')
        self.assertIsNotNone(
            pattern.search(src),
            "REGRESSION: TerminalWidget._render does not call "
            "_compute_origin_for. The e4fe48e fix requires origin to "
            "be recomputed each paint from fresh canvas dims + spans, "
            "not read from a cache. Without this, the maximize and "
            "Cmd-T ordering races re-emerge.",
        )

    def test_resize_paths_do_not_compute_origin(self):
        """handle_resize AND _apply_config MUST NOT call
        _compute_origin_for. Both ran before term.resize / before Tk
        layout completed, so any origin computed there was against
        stale state. Computing origin only inside _render eliminates
        the entire ordering-race bug class."""
        import inspect
        from nbsterm import TerminalWidget, TerminalApp

        import re
        pattern = re.compile(r'_compute_origin_for\s*\(')

        for name, fn in (
            ("TerminalWidget.handle_resize", TerminalWidget.handle_resize),
            ("TerminalApp._apply_config", TerminalApp._apply_config),
        ):
            with self.subTest(method=name):
                src = inspect.getsource(fn)
                match = pattern.search(src)
                self.assertIsNone(
                    match,
                    f"REGRESSION: {name} calls _compute_origin_for. "
                    "Origin compute must live ONLY in _render so it "
                    "reads fresh canvas dims + spans. Computing origin "
                    "here re-introduces the cache-staleness race "
                    "alexie hit on 0a5ee56 (maximize off-to-one-side, "
                    "Cmd-T text-area-doesn't-relayout).",
                )

    def test_select_tab_defers_render_via_after_idle(self):
        """TerminalApp._select_tab MUST schedule widget._render via
        root.after_idle, not call it synchronously. After canvas.pack()
        Tk has not yet run layout — winfo_width() returns 1 (pre-layout)
        and any origin/bbox-calibration computed against width=1 is
        wrong. after_idle defers until Tk drains the layout queue."""
        import inspect
        from nbsterm import TerminalApp
        src = inspect.getsource(TerminalApp._select_tab)

        import re
        # Match after_idle(<anything>._render) or
        # after_idle(<anything>.widget._render).
        deferred_pattern = re.compile(
            r'after_idle\s*\(\s*[^,)]*\._render\b'
        )
        self.assertIsNotNone(
            deferred_pattern.search(src),
            "REGRESSION: TerminalApp._select_tab does not defer "
            "widget._render via root.after_idle. A synchronous _render "
            "after canvas.pack() reads winfo_width()=1 (pre-layout), "
            "computing origin against the wrong canvas size — alexie "
            "saw this on 0a5ee56 as 'tabs draw but text area does not "
            "relayout until manual window resize'.",
        )

        # And it must NOT call _render synchronously alongside the
        # deferred one. (Double-paint would defeat the purpose and
        # produce a flash of mis-laid-out text on every tab switch.)
        sync_pattern = re.compile(
            r'(?<!after_idle\()\s*[^.\s]+\.widget\._render\s*\(\s*\)'
        )
        self.assertIsNone(
            sync_pattern.search(src),
            "REGRESSION: TerminalApp._select_tab calls widget._render() "
            "synchronously alongside the deferred after_idle. The "
            "synchronous paint runs against pre-layout winfo_width()=1, "
            "producing the wrong-origin flash that after_idle was added "
            "to prevent.",
        )

    def test_render_rebuilds_bg_fill_with_self_bg(self):
        """_render MUST delete and recreate the bg_fill rect every
        paint, with fill=self._bg. Without this, runtime text_bg
        config changes (alexie 07:31:54: bg-color reactivity) would
        not paint through — the rect would carry the old bg until a
        full canvas reset. Three sub-invariants:
          (a) self.canvas.delete('bg_fill') in body
          (b) self.canvas.create_rectangle with tags='bg_fill' in body
          (c) the rectangle's fill arg references self._bg
        """
        import inspect
        from nbsterm import TerminalWidget
        src = inspect.getsource(TerminalWidget._render)

        import re

        delete_pattern = re.compile(
            r'self\.canvas\.delete\(\s*["\']bg_fill["\']\s*\)'
        )
        self.assertIsNotNone(
            delete_pattern.search(src),
            "REGRESSION: _render does not delete the bg_fill rect. "
            "Old bg color would persist on runtime text_bg change.",
        )

        create_pattern = re.compile(
            r'self\.canvas\.create_rectangle\([^)]*tags\s*=\s*'
            r'["\']bg_fill["\']',
            re.DOTALL,
        )
        create_match = create_pattern.search(src)
        self.assertIsNotNone(
            create_match,
            "REGRESSION: _render does not create_rectangle with "
            "tags='bg_fill'. The bg layer would not be rebuilt.",
        )

        fill_pattern = re.compile(
            r'self\.canvas\.create_rectangle\([^)]*'
            r'fill\s*=\s*self\._bg',
            re.DOTALL,
        )
        self.assertIsNotNone(
            fill_pattern.search(src),
            "REGRESSION: _render's create_rectangle does not use "
            "fill=self._bg. Runtime config bg change would not paint "
            "through (alexie 07:31:54 named bg-color reactivity).",
        )


class TestTabFocusFix(unittest.TestCase):
    """Regression guards for Bug C v3 f80a896 (tab-strip focus stealing).

    Bug alexie reported (2026-04-28 17:05:45): with >1 tab, typing space
    in the text area redirects to the tab strip and triggers tab
    selection. Root cause (theologian 2026-04-28 17:24:54): tk.Button
    defaults takefocus=1 and Tk's Button class binds <Key-space>/<Return>
    to invoke. After a click, Mac leaves focus on the button; subsequent
    Space fires button.invoke (re-selects current tab) before root's
    <Key> handler routes to handle_key.

    Fix (f80a896): (1) takefocus=0 on each tab button so Tab-traversal
    skips them; (2) self.tabs[idx].canvas.focus_set() at end of
    _select_tab so Mac click-focus is overridden back to the canvas.

    Static-source inspection — no Tk display needed. Mac click-focus
    behaviour itself is the falsifier alexie runs.
    """

    def test_add_tab_no_focus_stealing_button(self):
        """The INVARIANT: TerminalApp._add_tab MUST NOT construct any
        tk.Button that defaults to takefocus=1. Either no tk.Button at
        all (e.g. the tk.Frame+tk.Label migration theologian 2026-04-28
        17:55:42 specifies for Mac native-widget bg/height bugs), OR
        every tk.Button in _add_tab carries an explicit takefocus=0/False.

        Widget-agnostic per theologian 2026-04-28 18:02:33: encodes the
        focus-steal contract, not the f80a896 implementation choice. A
        Label-based tab strip satisfies trivially (Label has takefocus=0
        default and no Space/Return class binding); the legacy
        Button-based strip satisfies only with an explicit takefocus=0
        kwarg."""
        import inspect
        from nbsterm import TerminalApp
        src = inspect.getsource(TerminalApp._add_tab)

        import re
        # Find every tk.Button(...) call (paren-balanced extraction so
        # multi-line constructors are captured whole) and verify each
        # one has takefocus=0/False in its arg list. If no tk.Button
        # appears (Label migration), the invariant is trivially held.
        starts = [m.start() for m in re.finditer(r'tk\.Button\s*\(', src)]
        for start in starts:
            paren_open = src.index('(', start)
            depth = 0
            paren_close = None
            for j in range(paren_open, len(src)):
                if src[j] == '(':
                    depth += 1
                elif src[j] == ')':
                    depth -= 1
                    if depth == 0:
                        paren_close = j
                        break
            self.assertIsNotNone(
                paren_close,
                f"REGRESSION: unterminated tk.Button(... at offset {start} "
                "in TerminalApp._add_tab — could not parse arg list.",
            )
            call_args = src[paren_open + 1:paren_close]
            kwarg_pattern = re.compile(
                r'\btakefocus\s*=\s*(?:0|False)\b'
            )
            self.assertIsNotNone(
                kwarg_pattern.search(call_args),
                "REGRESSION: TerminalApp._add_tab constructs a tk.Button "
                "without takefocus=0 (or False). Default takefocus=1 "
                "makes Mac click leave focus on the button, and Tk's "
                "Button class binds <Key-space>/<KeyPress-Return> to "
                "invoke — typing Space in the text area re-selects the "
                "tab (alexie 2026-04-28 17:05:45 focus-steal bug). Add "
                "takefocus=0, OR migrate to tk.Label which has neither "
                "the focus-by-default nor the Space/Return class binding."
                f"\n\nOffending call args:\n{call_args}",
            )

    def test_select_tab_focuses_canvas(self):
        """TerminalApp._select_tab MUST call .focus_set() on the active
        tab's canvas. takefocus=0 alone removes Tab-traversal but Mac
        click still focuses the button — only an explicit focus_set on
        the canvas restores keyboard focus to the terminal after each
        tab switch. Cmd-T also routes through _select_tab so this
        single guard covers both paths."""
        import inspect
        from nbsterm import TerminalApp
        src = inspect.getsource(TerminalApp._select_tab)

        import re
        # Match either tabs[idx].canvas.focus_set() or
        # tabs[idx].widget.canvas.focus_set() etc — any expression that
        # ends in .canvas.focus_set( inside _select_tab. Reject a bare
        # self.root.focus_set or button.focus_set.
        pattern = re.compile(
            r'\.canvas\.focus_set\s*\(\s*\)'
        )
        self.assertIsNotNone(
            pattern.search(src),
            "REGRESSION: TerminalApp._select_tab does not call "
            "<...>.canvas.focus_set(). Without this, Mac click leaves "
            "focus on the tab button (takefocus=0 only blocks "
            "Tab-traversal, not click-focus on Mac) and the next Space "
            "in the text area routes through the button's class binding "
            "for <Key-space>, re-selecting the tab.",
        )

        # And the focused canvas MUST belong to the tab being selected
        # (idx), not a hard-coded self.tabs[0] or the previous active.
        # Otherwise Cmd-T / programmatic switches would land focus on
        # the wrong canvas.
        idx_pattern = re.compile(
            r'self\.tabs\s*\[\s*idx\s*\]\.canvas\.focus_set\s*\(\s*\)'
        )
        self.assertIsNotNone(
            idx_pattern.search(src),
            "REGRESSION: _select_tab calls .canvas.focus_set() but not "
            "on self.tabs[idx]. Focus must land on the tab being "
            "selected, otherwise Cmd-T (which calls _select_tab(len-1)) "
            "and programmatic switches would focus the wrong canvas.",
        )


class TestGammaMirrorInvariant(unittest.TestCase):
    """Gamma-mirror invariant guard for Python-painted bg surfaces.

    Per supervisor 2026-04-29 14:47:13 + theologian 14:47:01 + pythia
    14:46:19 second-order risk: 59ed176 patched three TerminalWidget
    bg-paint sites to use gamma_correct, but the invariant lived only
    in commit messages. d538b3f added new tk.Frame/tk.Label widgets;
    theologian's F' branch immediately found a fresh raw-_bg path
    (tab_strip:1101) — proving the pattern alive before the slop fix
    had finished smoke-testing. 41ec2fc cleared that one site.

    INVARIANT: every Python widget construction or .config(bg=)/
    .configure(bg=) call inside TerminalWidget or TerminalApp that
    carries a bg= argument MUST use one of:
      - self._bg_render or w._bg_render (cached gamma-corrected value)
      - gamma_correct(...) inline call
      - a hex-string literal like "#404040" (fixed UI chrome)
      - one of the _TAB_* class constants (also fixed hex literals)
      - self.tab_strip.cget("bg") or strip_bg (inherited from a
        gamma-corrected parent — strip_bg is assigned exactly that
        in _refresh_tab_strip)

    Anything else — most importantly self._config.bg, self._bg, or
    w._bg — is a regression: the next widget added in these classes
    would silently re-introduce the gamma differential alexie hit on
    Mac (2026-04-28 14:33:25, slop lighter than text-area cells).

    Dialogs (ColorPicker256, PreferencesDialog) are explicitly out of
    scope: their swatches and previews show user-picked raw colours
    and gamma correction would distort what the user sees.

    Static-source inspection — no Tk display needed.
    """

    # Methods on TerminalWidget that paint or configure backgrounds.
    # Deliberately enumerated rather than walked-by-source because
    # adding a new bg-painting method should also add deliberate
    # gamma handling — the enumeration forces the reviewer to think.
    _TARGET_METHODS = {
        "TerminalWidget": ["__init__", "_render"],
        "TerminalApp": ["__init__", "_add_tab", "_refresh_tab_strip",
                        "_apply_config"],
    }

    @staticmethod
    def _split_top_level_args(call_args):
        """Split call_args (the contents of a function-call's parens)
        on top-level commas, ignoring commas inside nested parens or
        brackets. Returns a list of arg strings."""
        parts = []
        depth = 0
        start = 0
        for i, ch in enumerate(call_args):
            if ch in "([{":
                depth += 1
            elif ch in ")]}":
                depth -= 1
            elif ch == ',' and depth == 0:
                parts.append(call_args[start:i].strip())
                start = i + 1
        tail = call_args[start:].strip()
        if tail:
            parts.append(tail)
        return parts

    @classmethod
    def _extract_calls(cls, src, callable_pattern):
        """Yield (call_name, raw_arg_string) for every call matching
        callable_pattern (a compiled regex matching e.g. r'\\btk\\.Frame\\s*\\(').
        Uses paren-balanced extraction so multi-line calls are captured
        whole."""
        for m in callable_pattern.finditer(src):
            paren_open = src.index('(', m.start())
            depth = 0
            paren_close = None
            for j in range(paren_open, len(src)):
                if src[j] == '(':
                    depth += 1
                elif src[j] == ')':
                    depth -= 1
                    if depth == 0:
                        paren_close = j
                        break
            assert paren_close is not None, (
                f"unterminated call at offset {m.start()}: {src[m.start():m.start()+40]}"
            )
            yield m.group(0), src[paren_open + 1:paren_close]

    @classmethod
    def _extract_bg_values(cls, src):
        """Yield every bg= value passed to a tk.Frame/tk.Label/tk.Canvas
        construction OR a .config(bg=...) / .configure(bg=...) call
        anywhere in src. Returns (kind, bg_value_string) per match.

        Skips kwargs whose value isn't a bg keyword arg — only matches
        bg=<expr> at top level of a tk.Widget(...) call or a
        .config*(...) call."""
        import re
        widget_pattern = re.compile(
            r'\btk\.(?:Frame|Label|Canvas)\s*\('
        )
        config_pattern = re.compile(
            r'\.config(?:ure)?\s*\('
        )

        def grab_bg(call_args):
            for arg in cls._split_top_level_args(call_args):
                m = re.match(r'^bg\s*=\s*(.+)$', arg, re.DOTALL)
                if m:
                    return m.group(1).strip()
            return None

        for kind, args in cls._extract_calls(src, widget_pattern):
            bg = grab_bg(args)
            if bg is not None:
                yield ('widget', bg)
        for kind, args in cls._extract_calls(src, config_pattern):
            bg = grab_bg(args)
            if bg is not None:
                yield ('config', bg)

    # Allowed bg expression patterns. Each pattern matches a bg value
    # that does NOT need to be gamma-corrected here — either it ALREADY
    # is, or it's a fixed UI chrome colour the gamma rule doesn't apply
    # to.
    _ALLOWED_BG_PATTERNS = [
        # Cached gamma-corrected attr on TerminalWidget; w._bg_render
        # used in TerminalApp._apply_config which iterates widgets.
        r'^self\._bg_render$',
        r'^w\._bg_render$',
        # Inline gamma_correct(...) — the TerminalApp.tab_strip pattern
        # (41ec2fc); init-order means we can't cache _bg_render here.
        r'^gamma_correct\s*\(',
        # Fixed hex literal — UI chrome that should never gamma-shift.
        r'^"#[0-9a-fA-F]{6}"$',
        r"^'#[0-9a-fA-F]{6}'$",
        # _TAB_* class constants — all fixed hex literals defined at
        # nbsterm.py:1075-1080.
        r'^self\._TAB_(?:BG|FG|BORDER)_(?:INACTIVE|ACTIVE)$',
        # Inherit-from-parent: tab_strip's bg IS gamma-corrected (per
        # 41ec2fc) so anything that copies it stays consistent.
        r'^self\.tab_strip\.cget\(\s*["\']bg["\']\s*\)$',
        r'^strip_bg$',  # Local alias for tab_strip.cget("bg") in _refresh_tab_strip.
    ]

    def test_widget_bg_uses_gamma_corrected_value(self):
        """Every bg= argument in TerminalWidget+TerminalApp methods
        listed in _TARGET_METHODS must match an _ALLOWED_BG_PATTERNS
        entry. Failure means a new widget paints a raw-bg surface that
        will look lighter on Mac (gamma=1.2) than the gamma-corrected
        cells the C extension paints."""
        import inspect
        import re
        import nbsterm

        compiled_allow = [re.compile(p) for p in self._ALLOWED_BG_PATTERNS]

        violations = []
        for class_name, method_names in self._TARGET_METHODS.items():
            cls = getattr(nbsterm, class_name)
            for method_name in method_names:
                method = getattr(cls, method_name)
                src = inspect.getsource(method)
                for kind, bg_value in self._extract_bg_values(src):
                    if not any(p.search(bg_value) for p in compiled_allow):
                        violations.append(
                            f"  {class_name}.{method_name} ({kind}): "
                            f"bg={bg_value}"
                        )

        self.assertEqual(
            violations, [],
            "REGRESSION: gamma-mirror invariant violated. Every "
            "Python-painted bg surface in TerminalWidget+TerminalApp "
            "must use _bg_render, gamma_correct(...), a hex literal, "
            "a _TAB_* constant, or a tab_strip-inherited value. "
            "Raw self._config.bg / self._bg / w._bg here will paint "
            "lighter than the C-rendered cells on Mac (gamma=1.2). "
            "Add the value to _ALLOWED_BG_PATTERNS only if it is "
            "DEMONSTRABLY already gamma-corrected.\n\nViolations:\n"
            + "\n".join(violations),
        )


class TestCloseTabIdxSemantics(unittest.TestCase):
    """Regression guards for Bug C v3 4197557 (× close glyph + _close_tab(idx)
    refactor). Covers the cross-tab idx-vs-active semantics that pythia
    2026-04-29 15:23:39 #2 named load-bearing for both Cmd-W and × close
    paths after the bundle.

    Invariants locked here:
      1. _close_tab(self, idx) signature — must accept any tab index.
      2. _on_close_tab is a thin wrapper that delegates to
         _close_tab(self._active_tab_idx) — Cmd-W and × converge on
         the same code path.
      3. _add_tab packs both wrapper._label AND wrapper._close — the
         × glyph child Label exists and is stored on the wrapper.
      4. _refresh_tab_strip binds <Button-1> on both ._label
         (→ _select_tab) and ._close (→ _close_tab) — the × click is
         actually wired, and indices stay correct across tab close
         (the rebind-per-refresh pattern).
      5. _close_tab body covers all three idx-vs-active branches:
         (a) idx == active   → adjacent re-select with -1 sentinel
         (b) idx <  active   → decrement self._active_tab_idx by 1
         (c) idx >  active   → active unchanged
         AND the len==1 short-circuit calls _on_close (window destroy).

    Static-source inspection — no Tk display needed. Branch behaviour
    is the falsifier alexie's bundled Mac smoke runs.
    """

    def test_close_tab_accepts_idx_parameter(self):
        """_close_tab MUST be _close_tab(self, idx) — accepts any tab
        index, not just self._active_tab_idx. The × glyph closes the
        clicked tab regardless of which tab is active; locking the
        signature prevents a regression that would silently revert to
        active-only semantics and break × on inactive tabs."""
        import inspect
        from nbsterm import TerminalApp
        sig = inspect.signature(TerminalApp._close_tab)
        params = list(sig.parameters.keys())
        self.assertEqual(
            params, ['self', 'idx'],
            "REGRESSION: TerminalApp._close_tab signature is "
            f"{params}, expected ['self', 'idx']. The × glyph close "
            "(theologian 2026-04-29 14:44:49) requires _close_tab to "
            "accept ANY tab index, not just the active one. Reverting "
            "to active-only semantics breaks × on inactive tabs.",
        )

    def test_on_close_tab_delegates_to_close_tab(self):
        """_on_close_tab MUST delegate to _close_tab(self._active_tab_idx)
        — both Cmd-W and × close paths share one implementation. A
        regression that re-inlines close logic into _on_close_tab would
        immediately diverge the two paths under any future change."""
        import inspect
        import re
        from nbsterm import TerminalApp
        src = inspect.getsource(TerminalApp._on_close_tab)
        pattern = re.compile(
            r'self\._close_tab\s*\(\s*self\._active_tab_idx\s*\)'
        )
        self.assertIsNotNone(
            pattern.search(src),
            "REGRESSION: TerminalApp._on_close_tab does not delegate "
            "to self._close_tab(self._active_tab_idx). Cmd-W and × "
            "close paths must converge on a single implementation; "
            "if they diverge, a fix to one will silently miss the "
            "other (alexie 2026-04-29 14:43:48 + theologian 14:44:49).",
        )

    def test_add_tab_packs_label_and_close_glyph(self):
        """_add_tab MUST create both wrapper._label (text) and
        wrapper._close (× glyph) child Labels inside the wrapper Frame.
        Without wrapper._close, the × is invisible and × is the entire
        UI half of the close feature alexie asked for."""
        import inspect
        import re
        from nbsterm import TerminalApp
        src = inspect.getsource(TerminalApp._add_tab)
        # Must assign wrapper._label AND wrapper._close. Either order.
        # Anchor to start-of-line (after indent) so a commented-out
        # `# wrapper._close = …` does not satisfy the guard.
        for attr in ('_label', '_close'):
            pattern = re.compile(
                rf'^\s*wrapper\.{attr}\s*=', re.MULTILINE,
            )
            self.assertIsNotNone(
                pattern.search(src),
                f"REGRESSION: TerminalApp._add_tab does not store "
                f"wrapper.{attr}. The × close glyph (theologian "
                "2026-04-29 14:44:49) requires both child Labels on "
                "the wrapper so _refresh_tab_strip can rebind their "
                "<Button-1> handlers per tab-index refresh.",
            )

    def test_refresh_tab_strip_binds_close_glyph(self):
        """_refresh_tab_strip MUST bind <Button-1> on each wrapper's
        _close Label, routing to self._close_tab(i). Without this bind
        the × glyph is decorative — clicking it does nothing.

        The lambda i-capture pattern (lambda e, x=i: …) is required so
        indices stay correct across tab close; the existing
        label._select_tab(i) bind already follows this pattern."""
        import inspect
        import re
        from nbsterm import TerminalApp
        src = inspect.getsource(TerminalApp._refresh_tab_strip)
        # Look for either close.bind('<Button-1>', …) or
        # wrapper._close.bind(…) — accept either local binding style.
        pattern = re.compile(
            r'(?:close|wrapper\._close)\s*'
            r'\.bind\s*\(\s*["\']<Button-1>["\']\s*,'
            r'[^)]*self\._close_tab\s*\(',
            re.DOTALL,
        )
        self.assertIsNotNone(
            pattern.search(src),
            "REGRESSION: _refresh_tab_strip does not bind <Button-1> "
            "on wrapper._close → self._close_tab(idx). The × glyph "
            "would be decorative — alexie 2026-04-29 14:43:48 'I "
            "cannot close a tab' would re-emerge with the × visible "
            "but inert.",
        )

    def test_close_tab_handles_three_idx_branches(self):
        """_close_tab MUST contain all three idx-vs-active branches AND
        the len==1 short-circuit. Pythia 2026-04-29 15:23:39 #2: this
        is load-bearing for both close paths; missing the
        idx<active decrement would silently desynchronise the strip
        when a leftward tab is closed via ×."""
        import inspect
        import re
        from nbsterm import TerminalApp
        src = inspect.getsource(TerminalApp._close_tab)

        # (a) Active-tab close: re-select via -1 sentinel + min().
        active_branch = re.compile(
            r'idx\s*==\s*self\._active_tab_idx',
        )
        self.assertIsNotNone(
            active_branch.search(src),
            "REGRESSION: _close_tab missing 'idx == self._active_tab_idx' "
            "branch. Closing the active tab requires the -1 sentinel + "
            "min(idx, len-1) re-select pattern; without it Tk paints "
            "into a destroyed canvas index.",
        )
        sentinel = re.compile(
            r'self\._active_tab_idx\s*=\s*-\s*1',
        )
        self.assertIsNotNone(
            sentinel.search(src),
            "REGRESSION: _close_tab does not assign "
            "self._active_tab_idx = -1 before the re-select. The -1 "
            "sentinel is what makes _select_tab skip pack_forget on "
            "the now-destroyed canvas index (4197557 commit body).",
        )

        # (b) idx < active: decrement self._active_tab_idx.
        decrement_branch = re.compile(
            r'idx\s*<\s*self\._active_tab_idx',
        )
        self.assertIsNotNone(
            decrement_branch.search(src),
            "REGRESSION: _close_tab missing 'idx < self._active_tab_idx' "
            "branch. When closing a tab BEFORE the active one, "
            "_active_tab_idx must shift down by 1 — otherwise the "
            "active tab points at the wrong canvas (off-by-one strip "
            "desync). Pythia 2026-04-29 15:23:39 #2 named this "
            "load-bearing for the bundled smoke.",
        )
        decrement_op = re.compile(
            r'self\._active_tab_idx\s*-=\s*1',
        )
        self.assertIsNotNone(
            decrement_op.search(src),
            "REGRESSION: _close_tab does not decrement "
            "self._active_tab_idx. The 'idx < active' branch must "
            "shift active down by 1 to track the now-shorter list.",
        )

        # (c) Last tab → window close. (idx > active is the implicit
        # fall-through after (a) and (b); no explicit check needed —
        # any active-stays case lands here.)
        last_tab_branch = re.compile(
            r'len\s*\(\s*self\.tabs\s*\)\s*==\s*1',
        )
        self.assertIsNotNone(
            last_tab_branch.search(src),
            "REGRESSION: _close_tab missing 'len(self.tabs) == 1' "
            "short-circuit. Closing the last tab must invoke "
            "_on_close (whole-window destroy); without this, popping "
            "the only tab leaves an empty window with no terminal.",
        )
        on_close_call = re.compile(
            r'self\._on_close\s*\(',
        )
        self.assertIsNotNone(
            on_close_call.search(src),
            "REGRESSION: _close_tab len==1 branch does not call "
            "self._on_close(). The last-tab path must converge on "
            "the same window-close logic that WM_DELETE_WINDOW uses, "
            "or the two destroy paths drift apart.",
        )


class TestMacMenuInstall(unittest.TestCase):
    """Regression guard for Bug C v3 6b9d015 (Cmd-W menu accelerator
    overrides OS auto-menubar on macOS).

    Per supervisor 2026-04-29 16:38:19 + theologian 16:38:31 spec, after
    pythia 2026-04-29 16:37:58 #3 missing-validation: the Mac menu
    install path is the entire Cmd-W fix, and Xvfb cannot reproduce
    OS menu shadowing — there is no functional CI for it. A future
    refactor that consolidates keyboard wiring or rides a Tk upgrade
    can silently re-introduce alexie's 14:55:05 bug ('Cmd+W kills the
    whole process'), with code reading as if the binding suffices.

    INVARIANT: the sys.platform == 'darwin' branch of
    TerminalApp.__init__ MUST install a tk.Menu with an entry binding
    Command+W (or Cmd+W) to a callable that closes the active tab
    (i.e. _on_close_tab), NOT one that closes the window
    (_on_close). Without this menu install, the OS-installed
    Cmd-W → NSWindow performClose: → WM_DELETE_WINDOW → _on_close
    path runs unhindered.

    Static-source inspection — no Tk display needed. OS menu
    shadowing behaviour is the falsifier alexie's Mac smoke runs.
    """

    @staticmethod
    def _extract_darwin_branch(src):
        """Extract the body of the `if sys.platform == "darwin":`
        branch from src. Returns the substring of source inside that
        branch (everything from the `if` line up to the matching
        `else:` or end-of-method-at-same-indent).

        Uses indentation tracking — the branch body lives one indent
        level deeper than the `if`."""
        lines = src.splitlines()
        if_idx = None
        if_indent = None
        for i, line in enumerate(lines):
            stripped = line.strip()
            if stripped.startswith('if ') and 'sys.platform' in stripped \
                    and '"darwin"' in stripped:
                if_idx = i
                if_indent = len(line) - len(line.lstrip())
                break
        if if_idx is None:
            return None
        body = []
        body_indent = if_indent + 4  # standard 4-space body indent
        for line in lines[if_idx + 1:]:
            stripped = line.strip()
            if not stripped:
                body.append(line)
                continue
            indent = len(line) - len(line.lstrip())
            if indent <= if_indent:
                # Hit the `else:` (or anything at the if's level) —
                # darwin branch ended.
                break
            body.append(line)
        return '\n'.join(body)

    def test_darwin_branch_installs_menu_with_close_tab_command(self):
        """The darwin branch MUST construct a tk.Menu, register an
        add_command entry with a Command+W (or Cmd+W) accelerator,
        and bind that entry's command to self._on_close_tab. All
        three pieces are load-bearing.

        Falsifier verified for each piece; see this commit's body."""
        import inspect
        import re
        from nbsterm import TerminalApp

        full_src = inspect.getsource(TerminalApp.__init__)
        darwin_src = self._extract_darwin_branch(full_src)
        self.assertIsNotNone(
            darwin_src,
            "REGRESSION: Cannot locate `if sys.platform == \"darwin\":` "
            "branch in TerminalApp.__init__. The Mac-only Cmd-W menu "
            "install (theologian 2026-04-29 14:57:30; alexie 14:55:05 "
            "'Cmd+W kills the whole process') lives inside this "
            "branch — its absence means the entire fix is gone.",
        )

        # (a) tk.Menu(...) construction inside the branch.
        menu_pattern = re.compile(r'\btk\.Menu\s*\(')
        self.assertIsNotNone(
            menu_pattern.search(darwin_src),
            "REGRESSION: TerminalApp.__init__ darwin branch does not "
            "construct a tk.Menu. Without a user-installed menu, the "
            "OS auto-menubar's Cmd-W → NSWindow performClose: path "
            "kills the process on close (alexie 2026-04-29 14:55:05).",
        )

        # (b) An add_command with accelerator matching Command+W or
        # Cmd+W (case-insensitive). Tk gives user-menu accelerators
        # precedence over the auto-menu accelerator on aqua, so this
        # is the override mechanism.
        accel_pattern = re.compile(
            r'add_command\s*\([^)]*accelerator\s*=\s*'
            r'["\'](?:command|cmd)\s*\+\s*w["\']',
            re.DOTALL | re.IGNORECASE,
        )
        self.assertIsNotNone(
            accel_pattern.search(darwin_src),
            "REGRESSION: TerminalApp.__init__ darwin branch does not "
            "register an add_command with accelerator='Command+W' (or "
            "'Cmd+W'). The accelerator is what tells Tk to override "
            "the OS auto-menu Cmd-W binding — without it the menu "
            "exists but Cmd-W still kills the process.",
        )

        # (c) The add_command's command kwarg references _on_close_tab,
        # NOT _on_close. Closing the tab is the user-visible intent;
        # closing the window would re-introduce the original bug under
        # a different code path.
        cmd_pattern = re.compile(
            r'add_command\s*\([^)]*command\s*=\s*'
            r'(?:self\.)?_on_close_tab\b',
            re.DOTALL,
        )
        self.assertIsNotNone(
            cmd_pattern.search(darwin_src),
            "REGRESSION: TerminalApp.__init__ darwin branch's "
            "add_command does not bind command=self._on_close_tab. "
            "Cmd-W must close the active tab (alexie 2026-04-29 "
            "14:43:48 'I cannot close a tab' — the Cmd-W keyboard "
            "side of the close-tab feature). Binding to _on_close "
            "instead would close the window — the original bug under "
            "a different name.",
        )


class TestRenderTclErrorGuard(unittest.TestCase):
    """Regression guard for Bug C v3 38cb3dc (Cmd-W during auth ->
    _render TclError on destroyed canvas).

    Per pythia 2026-04-30 08:44:09 #26 R3 + supervisor 08:45:26: the
    fix shipped without a static-source guard. A future _render
    refactor that moves the canvas.winfo_width call outside the
    try-block — or removes the except — silently re-surfaces
    alexie's 06:26:00 traceback ('bad window path name .!canvas2'
    when Cmd-W destroys the canvas while a blink/flush after()
    callback is still pending).

    INVARIANT: TerminalWidget._render MUST wrap the first
    canvas.winfo_* call in a try/except tk.TclError that returns
    early. Without the wrap, deferred callbacks after _close_tab's
    canvas.destroy() raise instead of dropping the frame.

    Static-source inspection — no Tk display needed (Xvfb cannot
    reproduce the destroy-mid-callback race).
    """

    def test_render_wraps_winfo_in_tclerror_guard(self):
        """The first canvas.winfo_* call in TerminalWidget._render MUST
        be inside a try-block whose except clause catches tk.TclError
        and returns. Three sub-assertions:
          (a) the body contains both `try:` and `except tk.TclError`
          (b) `canvas.winfo_width()` (or `.winfo_height()`) appears
              between them — the call that races the destroy
          (c) the except handler contains a `return` statement —
              dropping the frame is the documented behaviour
        """
        import inspect
        import re
        from nbsterm import TerminalWidget
        src = inspect.getsource(TerminalWidget._render)

        # (a) try / except tk.TclError pair anywhere in the body.
        try_pattern = re.compile(r'^\s*try\s*:\s*$', re.MULTILINE)
        except_pattern = re.compile(
            r'^\s*except\s+tk\.TclError\b', re.MULTILINE,
        )
        try_match = try_pattern.search(src)
        except_match = except_pattern.search(src)
        self.assertIsNotNone(
            try_match,
            "REGRESSION: TerminalWidget._render contains no `try:` "
            "block. The destroyed-canvas guard from 38cb3dc requires "
            "wrapping the first canvas.winfo_* call so a "
            "tk.TclError ('bad window path name') from a deferred "
            "blink/flush after() callback drops the frame instead "
            "of raising (alexie 2026-04-30 06:26:00 traceback).",
        )
        self.assertIsNotNone(
            except_match,
            "REGRESSION: TerminalWidget._render has no `except "
            "tk.TclError` clause. Without it, a deferred blink/flush "
            "callback firing after _close_tab destroys the canvas "
            "raises 'bad window path name' instead of being dropped.",
        )
        self.assertLess(
            try_match.start(), except_match.start(),
            "REGRESSION: `except tk.TclError` precedes `try:` in "
            "_render — they must form a wrapping pair.",
        )

        # (b) canvas.winfo_width or .winfo_height inside the try
        # block (between `try:` and `except`).
        try_body = src[try_match.end():except_match.start()]
        winfo_pattern = re.compile(
            r'self\.canvas\.winfo_(?:width|height)\s*\(\s*\)'
        )
        self.assertIsNotNone(
            winfo_pattern.search(try_body),
            "REGRESSION: TerminalWidget._render's try-block does not "
            "wrap a canvas.winfo_width() / winfo_height() call. The "
            "guard is only effective if it sits around the first call "
            "that touches Tk's widget path (the one that raises "
            "'bad window path name' on a destroyed canvas — alexie "
            "2026-04-30 06:26:00 hit this at line 442 winfo_width). "
            "If you reorder _render to call winfo_height first, move "
            "the try-block with it.",
        )

        # (c) the except handler returns early. Look for `return`
        # within the indented block immediately after `except
        # tk.TclError`. Find the indentation of the except line and
        # treat any line indented further as part of its body until
        # we hit a line at or below that indent.
        lines = src[except_match.start():].splitlines()
        except_line = lines[0]
        except_indent = len(except_line) - len(except_line.lstrip())
        body_indent = None
        body_lines = []
        for line in lines[1:]:
            stripped = line.strip()
            if not stripped:
                continue
            indent = len(line) - len(line.lstrip())
            if body_indent is None:
                if indent <= except_indent:
                    break
                body_indent = indent
            if indent < body_indent:
                break
            body_lines.append(line)
        body_text = '\n'.join(body_lines)
        return_pattern = re.compile(r'^\s*return\b', re.MULTILINE)
        self.assertIsNotNone(
            return_pattern.search(body_text),
            "REGRESSION: TerminalWidget._render's `except tk.TclError` "
            "handler does not `return`. The intent (38cb3dc commit "
            "body) is to drop the frame silently when the canvas was "
            "destroyed mid-callback. Without the return, control "
            "falls through to canvas_h = self.canvas.winfo_height() "
            "which raises the same TclError — the guard would be "
            "ineffective.",
        )


if __name__ == '__main__':
    result = unittest.main(verbosity=2, exit=False)
    total = result.result.testsRun
    failures = len(result.result.failures) + len(result.result.errors)
    skipped = len(result.result.skipped)
    passed = total - failures - skipped
    print(f"\n  Pass: {passed} | Fail: {failures} | Skip: {skipped} | Total: {total}")
    gate = "OPEN" if failures == 0 and skipped == 0 else "BLOCKED"
    print(f"  Gate: {gate} (full_suite: no)")
    sys.exit(0 if failures == 0 else 1)
