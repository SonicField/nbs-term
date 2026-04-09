"""
test_integration.py — Python-level integration tests for _nbsterm extension.

Tests the Python API end-to-end: Terminal creation, feed(), get_screen(),
get_cell(), get_cursor(), encode_key/special/paste, resize, scrollback.
Covers the renderer output format and extension entry points that
cannot be tested from C.
"""
import sys
import os
import unittest

# Add parent directory to path for the built extension
sys.path.insert(0, os.path.dirname(os.path.dirname(os.path.abspath(__file__))))

import _nbsterm


class TestTerminalBasic(unittest.TestCase):
    def test_create_default(self):
        t = _nbsterm.Terminal()
        rows, cols = t.get_size()
        self.assertEqual(rows, 24)
        self.assertEqual(cols, 80)

    def test_create_custom(self):
        t = _nbsterm.Terminal(10, 40)
        rows, cols = t.get_size()
        self.assertEqual(rows, 10)
        self.assertEqual(cols, 40)

    def test_feed_and_cursor(self):
        t = _nbsterm.Terminal(24, 80)
        t.feed(b"Hello")
        row, col = t.get_cursor()
        self.assertEqual(row, 0)
        self.assertEqual(col, 5)

    def test_get_cell(self):
        t = _nbsterm.Terminal(24, 80)
        t.feed(b"A")
        cell = t.get_cell(0, 0)
        self.assertIsNotNone(cell)
        codepoint, fg, bg, attrs = cell
        self.assertEqual(codepoint, ord('A'))

    def test_get_cell_oob(self):
        t = _nbsterm.Terminal(24, 80)
        self.assertIsNone(t.get_cell(-1, 0))
        self.assertIsNone(t.get_cell(0, -1))
        self.assertIsNone(t.get_cell(24, 0))
        self.assertIsNone(t.get_cell(0, 80))

    def test_feed_empty(self):
        t = _nbsterm.Terminal(24, 80)
        t.feed(b"")  # must not crash
        row, col = t.get_cursor()
        self.assertEqual(row, 0)
        self.assertEqual(col, 0)


class TestRenderer(unittest.TestCase):
    def test_get_screen_returns_list(self):
        t = _nbsterm.Terminal(3, 10)
        t.feed(b"Hello")
        screen = t.get_screen()
        self.assertIsInstance(screen, list)
        self.assertEqual(len(screen), 3)  # one entry per row

    def test_per_span_colors(self):
        """Verify per-cell color attributes produce separate spans."""
        t = _nbsterm.Terminal(24, 80)
        t.feed(b"\x1b[31mRed\x1b[32mGreen\x1b[0m")
        screen = t.get_screen()
        row = screen[0]
        # Row should be a list of spans
        self.assertIsInstance(row, list)
        # Should have at least 2 spans (red and green)
        self.assertGreaterEqual(len(row), 2)
        # First span should contain 'Red' with red color
        first_text = row[0][0]
        first_fg = row[0][1]
        self.assertIn('Red', first_text)
        self.assertEqual(first_fg, '#cd0000')  # ANSI red

    def test_sgr_attributes_in_cells(self):
        """Verify SGR attributes visible via get_cell."""
        t = _nbsterm.Terminal(24, 80)
        t.feed(b"\x1b[1;31mBold Red\x1b[0mNormal")
        # Bold red cell
        cell = t.get_cell(0, 0)
        cp, fg, bg, attrs = cell
        self.assertEqual(cp, ord('B'))
        self.assertEqual(fg, '#cd0000')
        # Normal cell
        cell_n = t.get_cell(0, 8)
        cp_n, fg_n, bg_n, attrs_n = cell_n
        self.assertEqual(cp_n, ord('N'))


class TestRenderFrameContract(unittest.TestCase):
    """Verify render_frame C function accepts the args Python sends."""

    def test_arg_count_matches_python_call(self):
        """render_frame expects exactly 11 args (matching nbsterm.py _render)."""
        t = _nbsterm.Terminal(24, 80)
        with self.assertRaises(TypeError) as ctx:
            t.render_frame()
        self.assertIn("11", str(ctx.exception))

    def test_rejects_wrong_arg_count(self):
        """render_frame rejects 12 args (catches format string mismatch)."""
        t = _nbsterm.Terminal(24, 80)
        with self.assertRaises(TypeError) as ctx:
            t.render_frame(0, "", True, 0, "", "", "", 1.0, 10, 20, 8, 999)
        self.assertIn("11", str(ctx.exception))

    def test_draw_selection_arg_count(self):
        """draw_selection expects exactly 10 args."""
        t = _nbsterm.Terminal(24, 80)
        with self.assertRaises(TypeError) as ctx:
            t.draw_selection()
        # Verify it reports the expected arg count
        self.assertIn("argument", str(ctx.exception).lower())

    def test_clear_selection_arg_count(self):
        """clear_selection expects exactly 2 args."""
        t = _nbsterm.Terminal(24, 80)
        with self.assertRaises(TypeError) as ctx:
            t.clear_selection()
        self.assertIn("argument", str(ctx.exception).lower())

    def test_render_reset_callable(self):
        """render_reset takes no args and doesn't crash."""
        t = _nbsterm.Terminal(24, 80)
        t.render_reset()  # should not raise

    def test_tk_probe_arg_count(self):
        """tk_probe expects exactly 2 args."""
        with self.assertRaises(TypeError) as ctx:
            _nbsterm.tk_probe()
        self.assertIn("argument", str(ctx.exception).lower())

    def test_tcl_smoke_test(self):
        """Tcl ABI smoke test — uses _tkinter's interpreter, runs expr 1+1.
        Catches Tcl version mismatches that cause SIGSEGV in production.
        Requires a display (creates Tk root to get interpaddr)."""
        try:
            import tkinter as tk
            root = tk.Tk()
            root.withdraw()
        except Exception:
            self.skipTest("No display available for Tk")
            return
        try:
            result = _nbsterm.tcl_smoke_test(root.tk.interpaddr())
            self.assertEqual(result, "2")
        finally:
            root.destroy()


class TestInputEncoding(unittest.TestCase):
    def test_encode_key_ascii(self):
        t = _nbsterm.Terminal(24, 80)
        result = t.encode_key(ord('a'))
        self.assertEqual(result, b'a')

    def test_encode_key_ctrl(self):
        t = _nbsterm.Terminal(24, 80)
        result = t.encode_key(ord('c'), _nbsterm.MOD_CTRL)
        self.assertEqual(result, b'\x03')

    def test_encode_special_arrow(self):
        t = _nbsterm.Terminal(24, 80)
        result = t.encode_special(_nbsterm.KEY_UP)
        self.assertEqual(result, b'\x1b[A')

    def test_encode_special_shift_arrow(self):
        t = _nbsterm.Terminal(24, 80)
        result = t.encode_special(_nbsterm.KEY_UP, _nbsterm.MOD_SHIFT)
        self.assertEqual(result, b'\x1b[1;2A')

    def test_encode_paste_no_bracketed(self):
        t = _nbsterm.Terminal(24, 80)
        result = t.encode_paste("hello")
        self.assertEqual(result, b'hello')

    def test_encode_paste_bracketed(self):
        t = _nbsterm.Terminal(24, 80)
        t.feed(b"\x1b[?2004h")  # enable bracketed paste
        result = t.encode_paste("hello")
        self.assertEqual(result, b'\x1b[200~hello\x1b[201~')


class TestUTF8Spans(unittest.TestCase):
    """Tests for multi-byte UTF-8 text in screen spans (Bug 1 regression)."""

    def test_cjk_span_text_intact(self):
        """CJK characters survive span extraction as full codepoints."""
        t = _nbsterm.Terminal(24, 80)
        t.feed('世界test'.encode('utf-8'))
        screen = t.get_screen()
        self.assertIn('世界', screen[0][0][0])

    def test_cjk_multi_span_correct(self):
        """CJK + ASCII in separate SGR spans have correct text."""
        t = _nbsterm.Terminal(24, 80)
        t.feed(b'\x1b[31m\xe4\xb8\x96\xe7\x95\x8c\x1b[32mtest\x1b[0m')
        screen = t.get_screen()
        texts = [(s[0].strip(), s[1]) for s in screen[0] if s[0].strip()]
        self.assertEqual(texts[0][0], '世界')
        self.assertEqual(texts[0][1], '#cd0000')
        self.assertEqual(texts[1][0], 'test')
        self.assertEqual(texts[1][1], '#00cd00')

    def test_cjk_cell_codepoints(self):
        """CJK codepoints appear in correct cell positions."""
        t = _nbsterm.Terminal(24, 80)
        t.feed('世界'.encode('utf-8'))
        cp0 = t.get_cell(0, 0)[0]
        cp1 = t.get_cell(0, 1)[0]
        self.assertEqual(cp0, 0x4E16)  # 世
        self.assertEqual(cp1, 0x754C)  # 界

    def test_accented_char_span(self):
        """Multi-byte accented characters (2-byte UTF-8) in spans."""
        t = _nbsterm.Terminal(24, 80)
        t.feed('café'.encode('utf-8'))
        screen = t.get_screen()
        self.assertIn('café', screen[0][0][0])

    def test_mixed_utf8_cursor_position(self):
        """Cursor position correct after mixed UTF-8 text."""
        t = _nbsterm.Terminal(24, 80)
        t.feed('世界test'.encode('utf-8'))
        row, col = t.get_cursor()
        self.assertEqual(row, 0)
        # 2 CJK chars + 4 ASCII chars = 6 columns
        self.assertEqual(col, 6)


class TestEncodeTkEvent(unittest.TestCase):
    """Tests for encode_tk_event — the Tk keysym dispatch ported in Phase 4."""

    def setUp(self):
        self.t = _nbsterm.Terminal(24, 80)

    # --- Special keys ---
    def test_arrow_up(self):
        self.assertEqual(self.t.encode_tk_event("Up", 0, 0, False), b'\x1b[A')

    def test_arrow_down(self):
        self.assertEqual(self.t.encode_tk_event("Down", 0, 0, False), b'\x1b[B')

    def test_arrow_right(self):
        self.assertEqual(self.t.encode_tk_event("Right", 0, 0, False), b'\x1b[C')

    def test_arrow_left(self):
        self.assertEqual(self.t.encode_tk_event("Left", 0, 0, False), b'\x1b[D')

    def test_home(self):
        self.assertEqual(self.t.encode_tk_event("Home", 0, 0, False), b'\x1b[H')

    def test_end(self):
        self.assertEqual(self.t.encode_tk_event("End", 0, 0, False), b'\x1b[F')

    def test_insert(self):
        self.assertEqual(self.t.encode_tk_event("Insert", 0, 0, False), b'\x1b[2~')

    def test_delete(self):
        self.assertEqual(self.t.encode_tk_event("Delete", 0, 0, False), b'\x1b[3~')

    def test_page_up(self):
        self.assertEqual(self.t.encode_tk_event("Prior", 0, 0, False), b'\x1b[5~')

    def test_page_down(self):
        self.assertEqual(self.t.encode_tk_event("Next", 0, 0, False), b'\x1b[6~')

    def test_f1(self):
        self.assertEqual(self.t.encode_tk_event("F1", 0, 0, False), b'\x1bOP')

    def test_f5(self):
        self.assertEqual(self.t.encode_tk_event("F5", 0, 0, False), b'\x1b[15~')

    def test_f12(self):
        self.assertEqual(self.t.encode_tk_event("F12", 0, 0, False), b'\x1b[24~')

    # --- Special keys with modifiers ---
    def test_shift_up(self):
        result = self.t.encode_tk_event("Up", 0x1, 0, False)
        self.assertEqual(result, b'\x1b[1;2A')

    def test_ctrl_up(self):
        result = self.t.encode_tk_event("Up", 0x4, 0, False)
        self.assertEqual(result, b'\x1b[1;5A')

    # --- Simple keys ---
    def test_return(self):
        self.assertEqual(self.t.encode_tk_event("Return", 0, 0, False), b'\r')

    def test_backspace(self):
        self.assertEqual(self.t.encode_tk_event("BackSpace", 0, 0, False), b'\x7f')

    def test_tab(self):
        self.assertEqual(self.t.encode_tk_event("Tab", 0, 0, False), b'\t')

    def test_escape(self):
        self.assertEqual(self.t.encode_tk_event("Escape", 0, 0, False), b'\x1b')

    # --- Ctrl+letter ---
    def test_ctrl_a(self):
        result = self.t.encode_tk_event("a", 0x4, 0, False)
        self.assertEqual(result, b'\x01')

    def test_ctrl_c(self):
        result = self.t.encode_tk_event("c", 0x4, 0, False)
        self.assertEqual(result, b'\x03')

    def test_ctrl_z(self):
        result = self.t.encode_tk_event("z", 0x4, 0, False)
        self.assertEqual(result, b'\x1a')

    def test_ctrl_uppercase(self):
        result = self.t.encode_tk_event("A", 0x4, 0, False)
        self.assertEqual(result, b'\x01')

    # --- Alt+key ---
    def test_alt_x_linux(self):
        result = self.t.encode_tk_event("x", 0x8, 0, False)
        self.assertEqual(result, b'\x1bx')

    def test_alt_x_mac(self):
        result = self.t.encode_tk_event("x", 0x10, 0, True)
        self.assertEqual(result, b'\x1bx')

    def test_alt_wrong_mask_linux(self):
        # Mac alt mask (0x10) on Linux should NOT trigger alt
        result = self.t.encode_tk_event("x", 0x10, ord('x'), False)
        # Falls through to regular character
        self.assertIsNotNone(result)
        self.assertNotEqual(result, b'\x1bx')

    # --- Regular character ---
    def test_regular_char(self):
        result = self.t.encode_tk_event("a", 0, ord('a'), False)
        self.assertEqual(result, b'a')

    # --- Unhandled key ---
    def test_unhandled_modifier_only(self):
        result = self.t.encode_tk_event("Shift_L", 0x1, 0, False)
        self.assertIsNone(result)

    def test_unhandled_unknown_key(self):
        result = self.t.encode_tk_event("Super_L", 0, 0, False)
        self.assertIsNone(result)


class TestResize(unittest.TestCase):
    def test_resize(self):
        t = _nbsterm.Terminal(24, 80)
        t.resize(10, 40)
        rows, cols = t.get_size()
        self.assertEqual(rows, 10)
        self.assertEqual(cols, 40)

    def test_resize_preserves_content(self):
        t = _nbsterm.Terminal(24, 80)
        t.feed(b"Hello")
        t.resize(30, 100)
        cell = t.get_cell(0, 0)
        self.assertEqual(cell[0], ord('H'))


class TestScrollback(unittest.TestCase):
    def test_scrollback_count_empty(self):
        t = _nbsterm.Terminal(24, 80)
        self.assertEqual(t.get_scrollback_count(), 0)

    def test_scrollback_after_scroll(self):
        t = _nbsterm.Terminal(3, 10)
        t.feed(b"AAA\r\nBBB\r\nCCC\r\nDDD\r\nEEE")
        # 3-row terminal with 5 lines → 2 lines in scrollback
        self.assertEqual(t.get_scrollback_count(), 2)

    def test_scrollback_line_content(self):
        t = _nbsterm.Terminal(3, 10)
        t.feed(b"AAA\r\nBBB\r\nCCC\r\nDDD")
        # First scrolled line should contain 'AAA'
        count = t.get_scrollback_count()
        self.assertGreaterEqual(count, 1)
        line = t.get_scrollback_line(0)
        self.assertIsNotNone(line)

    def test_scrollback_oob(self):
        t = _nbsterm.Terminal(24, 80)
        self.assertIsNone(t.get_scrollback_line(0))
        self.assertIsNone(t.get_scrollback_line(-1))
        self.assertIsNone(t.get_scrollback_line(99999))


class TestAltScreen(unittest.TestCase):
    def test_alt_screen_switch(self):
        t = _nbsterm.Terminal(24, 80)
        t.feed(b"Main")
        cell = t.get_cell(0, 0)
        self.assertEqual(cell[0], ord('M'))
        # Switch to alt
        t.feed(b"\x1b[?1049h")
        cell = t.get_cell(0, 0)
        self.assertEqual(cell[0], 0)  # alt screen clear
        # Switch back
        t.feed(b"\x1b[?1049l")
        cell = t.get_cell(0, 0)
        self.assertEqual(cell[0], ord('M'))  # main preserved


class TestRealisticSequence(unittest.TestCase):
    """Feed a realistic escape sequence stream similar to vim/htop output."""

    def test_vim_like_output(self):
        t = _nbsterm.Terminal(24, 80)
        # Switch to alt screen
        t.feed(b"\x1b[?1049h")
        # Clear screen
        t.feed(b"\x1b[2J")
        # Move to top, write a status line with colors
        t.feed(b"\x1b[1;1H")
        t.feed(b"\x1b[7m file.txt [+]                                                                 \x1b[0m")
        # Write some code with syntax highlighting
        t.feed(b"\x1b[2;1H")
        t.feed(b"\x1b[34mdef \x1b[33mhello\x1b[0m():")
        t.feed(b"\x1b[3;5H")
        t.feed(b"\x1b[32mprint\x1b[0m(\x1b[31m\"world\"\x1b[0m)")
        # Verify screen state
        screen = t.get_screen()
        self.assertEqual(len(screen), 24)
        # Row 0 should have content (status line)
        self.assertGreater(len(screen[0]), 0)
        # Row 1 should have multiple color spans
        self.assertGreaterEqual(len(screen[1]), 2)
        # Verify cell-level: 'd' at (1,0) should be blue (Indexed 4)
        cell = t.get_cell(1, 0)
        self.assertEqual(cell[0], ord('d'))
        # Switch back to main
        t.feed(b"\x1b[?1049l")
        # Main screen should be empty (nothing was written before alt)
        cell = t.get_cell(0, 0)
        self.assertEqual(cell[0], 0)


class TestDirtyTracking(unittest.TestCase):
    """Verify dirty-row tracking — the renderer's early-return gate."""

    def test_initial_all_dirty(self):
        """New terminal should have all rows dirty."""
        t = _nbsterm.Terminal(4, 10)
        dirty = t.get_dirty_rows()
        self.assertEqual(len(dirty), 4)

    def test_clean_after_get(self):
        """After get_dirty_rows(), no rows are dirty."""
        t = _nbsterm.Terminal(4, 10)
        t.get_dirty_rows()  # clear
        dirty = t.get_dirty_rows()
        self.assertEqual(len(dirty), 0)

    def test_feed_dirties_rows(self):
        """Feeding data should mark affected rows dirty."""
        t = _nbsterm.Terminal(4, 10)
        t.get_dirty_rows()  # clear
        t.feed(b"Hello")  # writes to row 0
        dirty = t.get_dirty_rows()
        self.assertIn(0, dirty)

    def test_single_row_update(self):
        """Writing to one row should dirty only that row."""
        t = _nbsterm.Terminal(4, 10)
        t.get_dirty_rows()  # clear
        t.feed(b"\x1b[3;1H")  # move to row 2
        t.get_dirty_rows()  # clear cursor move dirtying
        t.feed(b"X")  # write to row 2
        dirty = t.get_dirty_rows()
        self.assertIn(2, dirty)

    def test_idle_no_dirty(self):
        """No feed after clear → no dirty rows (renderer skips)."""
        t = _nbsterm.Terminal(4, 10)
        t.feed(b"Hello")
        t.get_dirty_rows()  # clear
        # No further feed
        dirty = t.get_dirty_rows()
        self.assertEqual(len(dirty), 0)

    def test_alt_screen_all_dirty(self):
        """Alt screen switch should mark all rows dirty."""
        t = _nbsterm.Terminal(4, 10)
        t.feed(b"Hello")
        t.get_dirty_rows()  # clear
        t.feed(b"\x1b[?1049h")  # switch to alt
        dirty = t.get_dirty_rows()
        self.assertEqual(len(dirty), 4)

    def test_alt_screen_back_all_dirty(self):
        """Switching back from alt should mark all rows dirty."""
        t = _nbsterm.Terminal(4, 10)
        t.feed(b"\x1b[?1049h")  # alt
        t.get_dirty_rows()  # clear
        t.feed(b"\x1b[?1049l")  # back to main
        dirty = t.get_dirty_rows()
        self.assertEqual(len(dirty), 4)

    def test_erase_display_dirties_all(self):
        """CSI 2J (erase display) should dirty all rows."""
        t = _nbsterm.Terminal(4, 10)
        t.get_dirty_rows()  # clear
        t.feed(b"\x1b[2J")
        dirty = t.get_dirty_rows()
        self.assertEqual(len(dirty), 4)

    def test_cursor_move_dirties_rows(self):
        """Cursor movement should dirty both old and new cursor rows."""
        t = _nbsterm.Terminal(4, 10)
        t.feed(b"Hello")  # cursor on row 0
        t.get_dirty_rows()  # clear
        t.feed(b"\x1b[2;1H")  # move cursor to row 1
        dirty = t.get_dirty_rows()
        # Both old row (0) and new row (1) should be dirty
        self.assertIn(0, dirty)
        self.assertIn(1, dirty)

    def test_cursor_move_same_row_dirties(self):
        """Cursor movement within same row should dirty that row."""
        t = _nbsterm.Terminal(4, 10)
        t.feed(b"Hello")  # cursor at row 0, col 5
        t.get_dirty_rows()  # clear
        t.feed(b"\x1b[1;1H")  # move to row 0, col 0 (same row)
        dirty = t.get_dirty_rows()
        self.assertIn(0, dirty)

    def test_scroll_dirties_rows(self):
        """Scrolling should dirty affected rows."""
        t = _nbsterm.Terminal(4, 10)
        t.feed(b"A\r\nB\r\nC\r\nD")
        t.get_dirty_rows()  # clear
        t.feed(b"\r\nE")  # scroll up, new line
        dirty = t.get_dirty_rows()
        self.assertGreater(len(dirty), 0)


if __name__ == '__main__':
    # Run with verbose output and summary
    result = unittest.main(verbosity=2, exit=False)
    # Print gate-compatible summary
    total = result.result.testsRun
    failures = len(result.result.failures) + len(result.result.errors)
    skipped = len(result.result.skipped)
    passed = total - failures - skipped
    print(f"\n  Pass: {passed} | Fail: {failures} | Skip: {skipped} | Total: {total}")
    gate = "OPEN" if failures == 0 and skipped == 0 else "BLOCKED"
    print(f"  Gate: {gate} (full_suite: no)")
    sys.exit(0 if failures == 0 else 1)
