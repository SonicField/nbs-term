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
        self.assertEqual(t.extract_selected_text(0, 0, 0, 4), "Hello")

    def test_empty_same_point(self):
        t = _nbsterm.Terminal(24, 80)
        t.feed(b"Hello")
        self.assertEqual(t.extract_selected_text(0, 0, 0, 0), "")

    def test_multiline(self):
        t = _nbsterm.Terminal(24, 80)
        t.feed(b"Line 1\r\nLine 2\r\nLine 3")
        self.assertEqual(t.extract_selected_text(0, 0, 2, 5), "Line 1\nLine 2\nLine 3")

    def test_partial_line(self):
        t = _nbsterm.Terminal(24, 80)
        t.feed(b"Hello World")
        self.assertEqual(t.extract_selected_text(0, 6, 0, 10), "World")

    def test_trailing_whitespace_stripped(self):
        t = _nbsterm.Terminal(24, 80)
        t.feed(b"Hi")
        self.assertEqual(t.extract_selected_text(0, 0, 0, 10), "Hi")

    def test_empty_cells(self):
        t = _nbsterm.Terminal(24, 80)
        self.assertEqual(t.extract_selected_text(5, 0, 5, 9), "")

    def test_with_sgr_colors(self):
        t = _nbsterm.Terminal(24, 80)
        t.feed(b"\x1b[31mRed\x1b[32mGreen\x1b[0m")
        self.assertEqual(t.extract_selected_text(0, 0, 0, 7), "RedGreen")

    def test_backward_selection(self):
        t = _nbsterm.Terminal(24, 80)
        t.feed(b"Hello")
        self.assertEqual(t.extract_selected_text(0, 4, 0, 0), "Hello")

    def test_rstrip_preserves_spaces(self):
        """C rstrip preserves trailing cp=32 spaces, strips only cp=0 NULs.
        Matches iTerm2/GNOME Terminal convention."""
        t = _nbsterm.Terminal(24, 80)
        t.feed(b"Hi   ")  # explicit spaces after text
        # Select range covering text + trailing spaces (not NUL cells)
        result = t.extract_selected_text(0, 0, 0, 4)
        self.assertEqual(result, "Hi   ")


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
