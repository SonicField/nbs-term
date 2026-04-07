"""Configuration for nbs-term.

Loads settings from ~/.nbs/nbs-term.honest (Mac/Linux) or
%LOCALAPPDATA%/nbs/nbs-term.honest (Windows). Falls back to
sensible defaults when no config file exists.

Uses the Honest format (Pascal-like structured data).
Parsed via the honest-get CLI tool.
"""
import os
import sys
import subprocess
import logging
from dataclasses import dataclass

log = logging.getLogger("nbs-term")

# Default config file content (written when none exists)
DEFAULT_CONFIG = """\
type
  CursorStyle = (Block, Wireframe, Underline, Bar);

  FontConfig = record
    family : String;
    size   : Integer;
  end;

  CursorConfig = record
    style : CursorStyle;
    blink : Boolean;
  end;

  TerminalConfig = record
    font   : FontConfig;
    cursor : CursorConfig;
    rows   : Integer;
    cols   : Integer;
  end;

var config : TerminalConfig = (
  font   : (family : 'Menlo'; size : 14);
  cursor : (style : Block; blink : True);
  rows   : 24;
  cols   : 80;
);
"""


@dataclass
class FontConfig:
    family: str = "Menlo" if sys.platform == "darwin" else "monospace"
    size: int = 14


@dataclass
class CursorConfig:
    style: str = "Block"  # Block, Wireframe, Underline, Bar
    blink: bool = True


@dataclass
class TerminalConfig:
    font: FontConfig = None
    cursor: CursorConfig = None
    rows: int = 24
    cols: int = 80

    def __post_init__(self):
        if self.font is None:
            self.font = FontConfig()
        if self.cursor is None:
            self.cursor = CursorConfig()


def get_config_dir():
    """Return the config directory path for the current platform."""
    if sys.platform == "win32":
        base = os.environ.get("LOCALAPPDATA", os.path.expanduser("~"))
        return os.path.join(base, "nbs")
    return os.path.expanduser("~/.nbs")


def get_config_path():
    """Return the full path to the config file."""
    return os.path.join(get_config_dir(), "nbs-term.honest")


def _honest_get(file_path, var, *fields):
    """Read a value from an Honest file using honest-get.

    Nested fields are joined with dots: _honest_get(f, 'config', 'font', 'size')
    runs: honest-get f config font.size
    """
    try:
        cmd = ["honest-get", file_path, var]
        if fields:
            cmd.append(".".join(fields))
        result = subprocess.run(
            cmd, capture_output=True, text=True, timeout=5,
        )
        if result.returncode == 0:
            return result.stdout.strip()
    except (subprocess.TimeoutExpired, FileNotFoundError):
        pass
    return None


def load_config(cli_args=None):
    """Load config from file, with CLI overrides.

    Args:
        cli_args: argparse.Namespace with optional overrides
                  (font_size, cursor_style, cursor_blink, rows, cols)

    Returns:
        TerminalConfig with merged settings.
    """
    config = TerminalConfig()
    config_path = get_config_path()

    # Create default config if none exists
    if not os.path.exists(config_path):
        config_dir = get_config_dir()
        if not os.path.exists(config_dir):
            try:
                os.makedirs(config_dir, exist_ok=True)
            except OSError:
                log.debug("Cannot create config dir: %s", config_dir)
        try:
            with open(config_path, "w") as f:
                f.write(DEFAULT_CONFIG)
            log.info("Created default config: %s", config_path)
        except OSError:
            log.debug("Cannot write default config: %s", config_path)

    # Read from config file
    if os.path.exists(config_path):
        log.debug("Loading config from %s", config_path)

        val = _honest_get(config_path, "config", "font", "family")
        if val:
            config.font.family = val.strip("'\"")

        val = _honest_get(config_path, "config", "font", "size")
        if val:
            try:
                config.font.size = int(val)
            except ValueError:
                pass

        val = _honest_get(config_path, "config", "cursor", "style")
        if val:
            config.cursor.style = val

        val = _honest_get(config_path, "config", "cursor", "blink")
        if val:
            config.cursor.blink = val.lower() in ("true", "yes", "1")

        val = _honest_get(config_path, "config", "rows")
        if val:
            try:
                config.rows = int(val)
            except ValueError:
                pass

        val = _honest_get(config_path, "config", "cols")
        if val:
            try:
                config.cols = int(val)
            except ValueError:
                pass

    # CLI overrides take precedence
    if cli_args:
        if getattr(cli_args, "font_size", None) is not None:
            config.font.size = cli_args.font_size
        if getattr(cli_args, "font_family", None) is not None:
            config.font.family = cli_args.font_family
        if getattr(cli_args, "rows", None) is not None:
            config.rows = cli_args.rows
        if getattr(cli_args, "cols", None) is not None:
            config.cols = cli_args.cols

    return config
