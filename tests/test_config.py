"""
test_config.py — Tests for the config system.

Tests config defaults, Honest file loading, CLI overrides,
and platform-aware path selection.
"""
import sys
import os
import unittest
import tempfile
import shutil
from unittest.mock import patch
from argparse import Namespace

sys.path.insert(0, os.path.dirname(os.path.dirname(os.path.abspath(__file__))))

from config import (
    TerminalConfig, FontConfig, CursorConfig,
    get_config_dir, get_config_path, load_config,
    DEFAULT_CONFIG,
)


class TestDefaultConfig(unittest.TestCase):
    """Verify default TerminalConfig values."""

    def test_default_rows(self):
        c = TerminalConfig()
        self.assertEqual(c.rows, 24)

    def test_default_cols(self):
        c = TerminalConfig()
        self.assertEqual(c.cols, 80)

    def test_default_font_size(self):
        c = TerminalConfig()
        self.assertEqual(c.font.size, 14)

    def test_default_font_family_not_empty(self):
        c = TerminalConfig()
        self.assertTrue(len(c.font.family) > 0)

    def test_default_cursor_style(self):
        c = TerminalConfig()
        self.assertEqual(c.cursor.style, "Block")

    def test_default_cursor_blink(self):
        c = TerminalConfig()
        self.assertTrue(c.cursor.blink)

    def test_font_config_independent(self):
        c1 = TerminalConfig()
        c2 = TerminalConfig()
        c1.font.size = 20
        self.assertEqual(c2.font.size, 14)

    def test_cursor_config_independent(self):
        c1 = TerminalConfig()
        c2 = TerminalConfig()
        c1.cursor.blink = False
        self.assertTrue(c2.cursor.blink)


class TestConfigPath(unittest.TestCase):
    """Verify platform-aware config paths."""

    @patch("config.sys")
    def test_mac_linux_path(self, mock_sys):
        mock_sys.platform = "linux"
        path = get_config_dir()
        self.assertTrue(path.endswith("/.nbs"))

    @patch("config.sys")
    @patch.dict(os.environ, {"LOCALAPPDATA": "/fake/appdata"})
    def test_windows_path(self, mock_sys):
        mock_sys.platform = "win32"
        path = get_config_dir()
        self.assertEqual(path, os.path.join("/fake/appdata", "nbs"))

    def test_config_file_name(self):
        path = get_config_path()
        self.assertTrue(path.endswith("nbs-term.honest"))


class TestLoadConfigDefaults(unittest.TestCase):
    """Verify load_config returns defaults when no config file exists."""

    def setUp(self):
        self._tmpdir = tempfile.mkdtemp()

    def tearDown(self):
        shutil.rmtree(self._tmpdir)

    @patch("config.get_config_path")
    def test_no_config_file_returns_defaults(self, mock_path):
        mock_path.return_value = os.path.join(self._tmpdir, "nonexistent.honest")
        # Patch get_config_dir to use tmpdir (so it doesn't write to real ~/.nbs)
        with patch("config.get_config_dir", return_value=self._tmpdir):
            c = load_config()
        self.assertEqual(c.rows, 24)
        self.assertEqual(c.cols, 80)
        self.assertEqual(c.font.size, 14)
        self.assertEqual(c.cursor.style, "Block")


class TestLoadConfigFromFile(unittest.TestCase):
    """Verify load_config reads Honest config files."""

    def setUp(self):
        self._tmpdir = tempfile.mkdtemp()
        self._config_path = os.path.join(self._tmpdir, "nbs-term.honest")

    def tearDown(self):
        shutil.rmtree(self._tmpdir)

    @patch("config.get_config_dir")
    @patch("config.get_config_path")
    def test_load_default_config_file(self, mock_path, mock_dir):
        """Write the default config, load it, verify values match defaults."""
        mock_path.return_value = self._config_path
        mock_dir.return_value = self._tmpdir
        with open(self._config_path, "w") as f:
            f.write(DEFAULT_CONFIG)
        c = load_config()
        self.assertEqual(c.font.size, 14)
        self.assertEqual(c.cursor.style, "Block")
        self.assertTrue(c.cursor.blink)
        self.assertEqual(c.rows, 24)
        self.assertEqual(c.cols, 80)

    @patch("config.get_config_dir")
    @patch("config.get_config_path")
    def test_load_custom_font_size(self, mock_path, mock_dir):
        """Config with different font size."""
        mock_path.return_value = self._config_path
        mock_dir.return_value = self._tmpdir
        custom = DEFAULT_CONFIG.replace("size : 14", "size : 20")
        with open(self._config_path, "w") as f:
            f.write(custom)
        c = load_config()
        self.assertEqual(c.font.size, 20)

    @patch("config.get_config_dir")
    @patch("config.get_config_path")
    def test_load_custom_cursor_style(self, mock_path, mock_dir):
        """Config with wireframe cursor."""
        mock_path.return_value = self._config_path
        mock_dir.return_value = self._tmpdir
        custom = DEFAULT_CONFIG.replace("style : Block", "style : Wireframe")
        with open(self._config_path, "w") as f:
            f.write(custom)
        c = load_config()
        self.assertEqual(c.cursor.style, "Wireframe")


class TestConfigPersistence(unittest.TestCase):
    """Verify config round-trip: save then load preserves values."""

    def setUp(self):
        self._tmpdir = tempfile.mkdtemp()
        self._config_path = os.path.join(self._tmpdir, "nbs-term.honest")

    def tearDown(self):
        shutil.rmtree(self._tmpdir)

    @patch("config.get_config_dir")
    @patch("config.get_config_path")
    def test_cursor_color_survives_restart(self, mock_path, mock_dir):
        """Cursor color set, saved, and loaded back must persist."""
        mock_path.return_value = self._config_path
        mock_dir.return_value = self._tmpdir
        from config import save_config
        c = TerminalConfig()
        c.cursor.color = "#ff8800"
        save_config(c)
        c2 = load_config()
        self.assertEqual(c2.cursor.color, "#ff8800")

    @patch("config.get_config_dir")
    @patch("config.get_config_path")
    def test_empty_cursor_color_round_trip(self, mock_path, mock_dir):
        """Empty cursor color (default) survives save/load."""
        mock_path.return_value = self._config_path
        mock_dir.return_value = self._tmpdir
        from config import save_config
        c = TerminalConfig()
        c.cursor.color = ""
        save_config(c)
        c2 = load_config()
        self.assertEqual(c2.cursor.color, "")


class TestCLIOverrides(unittest.TestCase):
    """Verify CLI arguments override config file values."""

    def setUp(self):
        self._tmpdir = tempfile.mkdtemp()
        self._config_path = os.path.join(self._tmpdir, "nbs-term.honest")

    def tearDown(self):
        shutil.rmtree(self._tmpdir)

    @patch("config.get_config_dir")
    @patch("config.get_config_path")
    def test_cli_font_size_overrides(self, mock_path, mock_dir):
        mock_path.return_value = self._config_path
        mock_dir.return_value = self._tmpdir
        with open(self._config_path, "w") as f:
            f.write(DEFAULT_CONFIG)
        args = Namespace(font_size=20, font_family=None, rows=None, cols=None)
        c = load_config(cli_args=args)
        self.assertEqual(c.font.size, 20)

    @patch("config.get_config_dir")
    @patch("config.get_config_path")
    def test_cli_rows_cols_override(self, mock_path, mock_dir):
        mock_path.return_value = self._config_path
        mock_dir.return_value = self._tmpdir
        with open(self._config_path, "w") as f:
            f.write(DEFAULT_CONFIG)
        args = Namespace(font_size=None, font_family=None, rows=40, cols=120)
        c = load_config(cli_args=args)
        self.assertEqual(c.rows, 40)
        self.assertEqual(c.cols, 120)

    def test_cli_override_no_config_file(self):
        """CLI overrides work even without a config file."""
        with patch("config.get_config_path", return_value="/nonexistent/path.honest"):
            with patch("config.get_config_dir", return_value="/nonexistent"):
                args = Namespace(font_size=18, font_family="Courier", rows=None, cols=None)
                c = load_config(cli_args=args)
        self.assertEqual(c.font.size, 18)
        self.assertEqual(c.font.family, "Courier")


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
