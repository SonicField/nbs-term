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
    gamma  : Real;
    fg     : String;
    bg     : String;
    rows   : Integer;
    cols   : Integer;
  end;

var config : TerminalConfig = (
  font   : (family : 'Menlo'; size : 14);
  cursor : (style : Block; blink : True);
  gamma  : 0.85;
  fg     : '#d0d0d0';
  bg     : '#000000';
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
    gamma: float = 0.85 if sys.platform == "darwin" else 1.0
    fg: str = "#d0d0d0"
    bg: str = "#000000"
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


def _parse_honest_values(text):
    """Extract key-value pairs from an Honest config var block.

    Parses the 'var config : ... = (...)' section and returns a flat
    dict of dot-separated keys to string values.
    E.g. {'font.family': 'Menlo', 'font.size': '14', 'rows': '24'}
    """
    import re
    result = {}

    # Find the var assignment block: var ... = ( ... );
    # Use paren counting to handle nested records
    match = re.search(r'var\s+\w+\s*:\s*\w+\s*=\s*\(', text)
    if not match:
        return result
    start = match.end()
    depth = 1
    pos = start
    while pos < len(text) and depth > 0:
        if text[pos] == '(':
            depth += 1
        elif text[pos] == ')':
            depth -= 1
        pos += 1
    outer_block = text[start:pos - 1]

    def parse_record(block, prefix=""):
        """Recursively parse nested record values."""
        # Match field : value pairs, handling nested ( ... ) blocks
        pos = 0
        while pos < len(block):
            # Skip whitespace
            while pos < len(block) and block[pos] in ' \t\r\n':
                pos += 1
            if pos >= len(block):
                break

            # Match field name
            field_match = re.match(r'(\w+)\s*:\s*', block[pos:])
            if not field_match:
                pos += 1
                continue

            field_name = field_match.group(1)
            pos += field_match.end()
            key = f"{prefix}{field_name}" if not prefix else f"{prefix}.{field_name}"

            # Check if value is a nested record
            if pos < len(block) and block[pos] == '(':
                # Find matching closing paren
                depth = 1
                start = pos + 1
                pos += 1
                while pos < len(block) and depth > 0:
                    if block[pos] == '(':
                        depth += 1
                    elif block[pos] == ')':
                        depth -= 1
                    pos += 1
                parse_record(block[start:pos - 1], key)
            else:
                # Simple value — read until ; or end
                val_match = re.match(r"'([^']*)'|([\w.]+)", block[pos:])
                if val_match:
                    value = val_match.group(1) if val_match.group(1) is not None else val_match.group(2)
                    result[key] = value
                    pos += val_match.end()

            # Skip separator
            while pos < len(block) and block[pos] in ' \t\r\n;':
                pos += 1

    parse_record(outer_block)
    return result


def _honest_get(file_path, var, *fields):
    """Read a value from an Honest config file.

    Uses a built-in parser (no external tools needed).
    Falls back to honest-get CLI if available.
    """
    try:
        with open(file_path, "r") as f:
            text = f.read()
        values = _parse_honest_values(text)
        key = ".".join(fields) if fields else var
        return values.get(key)
    except (OSError, KeyError):
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

        val = _honest_get(config_path, "config", "gamma")
        if val:
            try:
                config.gamma = float(val)
            except ValueError:
                pass

        val = _honest_get(config_path, "config", "fg")
        if val:
            config.fg = val.strip("'\"")

        val = _honest_get(config_path, "config", "bg")
        if val:
            config.bg = val.strip("'\"")

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


def save_config(config):
    """Save config to the Honest config file."""
    config_path = get_config_path()
    config_dir = get_config_dir()

    if not os.path.exists(config_dir):
        try:
            os.makedirs(config_dir, exist_ok=True)
        except OSError:
            log.warning("Cannot create config dir: %s", config_dir)
            return False

    blink_str = "True" if config.cursor.blink else "False"
    content = f"""\
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
    gamma  : Real;
    fg     : String;
    bg     : String;
    rows   : Integer;
    cols   : Integer;
  end;

var config : TerminalConfig = (
  font   : (family : '{config.font.family}'; size : {config.font.size});
  cursor : (style : {config.cursor.style}; blink : {blink_str});
  gamma  : {config.gamma:.2f};
  fg     : '{config.fg}';
  bg     : '{config.bg}';
  rows   : {config.rows};
  cols   : {config.cols};
);
"""
    try:
        with open(config_path, "w") as f:
            f.write(content)
        log.info("Saved config to %s", config_path)
        return True
    except OSError:
        log.warning("Cannot save config: %s", config_path)
        return False
