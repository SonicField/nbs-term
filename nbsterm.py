#!/usr/bin/env python3
"""
nbs-term: Terminal emulator application.

Wires the _nbsterm C extension to Tk (display) and nbs-ssh (transport).

Architecture:
  Main thread (Tk): mainloop, term.feed(), canvas rendering, user input, auth dialogs
  Background thread (asyncio): SSH connection, byte I/O

Invariant: C extension only called from main thread.
"""
import sys
import os
import asyncio
import logging
import threading
import concurrent.futures
import tkinter as tk
import tkinter.font as tkfont
import tkinter.simpledialog as simpledialog

import _nbsterm
from nbs_ssh import (
    SSHConnection,
    SSHInteractionHandler,
    SSHConfig,
    create_keyboard_interactive_auth,
)
from nbs_ssh.auth import AuthConfig, AuthMethod, get_agent_cert_key_pair
from config import load_config, save_config, TerminalConfig, FontConfig, CursorConfig

log = logging.getLogger("nbs-term")

# --- Configuration ---

DEFAULT_ROWS = 24
DEFAULT_COLS = 80
DEFAULT_FONT_FAMILY = "Menlo" if sys.platform == "darwin" else "monospace"
DEFAULT_FONT_SIZE = 14
DEFAULT_FG = "#d0d0d0"
DEFAULT_BG = "#1a1a1a"
SCROLLBACK_LINES = 10000


class TerminalWidget:
    """Tk canvas-based terminal display."""

    def __init__(self, parent, rows=DEFAULT_ROWS, cols=DEFAULT_COLS,
                 font_family=DEFAULT_FONT_FAMILY, font_size=DEFAULT_FONT_SIZE,
                 cursor_style="Block", cursor_blink=True):
        self.parent = parent
        self.rows = rows
        self.cols = cols
        self._cursor_style = cursor_style
        self._cursor_blink = cursor_blink
        self._cursor_visible = True
        self._blink_id = None

        # Font setup — cache all 4 style variants
        self.font = tkfont.Font(family=font_family, size=font_size)
        self._font_cache = {
            0: self.font,
            0x01: tkfont.Font(family=font_family, size=font_size, weight="bold"),
            0x04: tkfont.Font(family=font_family, size=font_size, slant="italic"),
            0x05: tkfont.Font(family=font_family, size=font_size, weight="bold", slant="italic"),
        }
        self.char_width = self.font.measure("M")
        self.char_height = self.font.metrics("linespace")

        # Canvas
        width = self.cols * self.char_width
        height = self.rows * self.char_height
        self.canvas = tk.Canvas(
            parent, width=width, height=height,
            bg=DEFAULT_BG, highlightthickness=0,
        )
        self.canvas.pack(fill=tk.BOTH, expand=True)

        # Terminal engine
        self.term = _nbsterm.Terminal(rows, cols)

        # Render state: list of canvas item IDs per row
        self._row_items = [[] for _ in range(rows)]

        # Cursor
        self._cursor_item = None

        # Backpressure: buffer incoming data, render on next idle cycle
        self._pending_data = bytearray()
        self._render_scheduled = False

        # Selection state
        self._sel_start = None  # (row, col) of selection start
        self._sel_end = None    # (row, col) of selection end
        self._sel_items = []    # canvas item IDs for selection highlight

        # Mouse bindings for selection
        self.canvas.bind("<ButtonPress-1>", self._on_mouse_down)
        self.canvas.bind("<B1-Motion>", self._on_mouse_drag)
        self.canvas.bind("<ButtonRelease-1>", self._on_mouse_up)

        # Callbacks
        self._write_callback = None  # called with bytes to send to SSH

    def set_write_callback(self, cb):
        self._write_callback = cb

    def _pixel_to_cell(self, x, y):
        """Convert pixel coordinates to (row, col)."""
        col = max(0, min(x // self.char_width, self.cols - 1))
        row = max(0, min(y // self.char_height, self.rows - 1))
        return (row, col)

    def _on_mouse_down(self, event):
        """Start selection."""
        self._sel_start = self._pixel_to_cell(event.x, event.y)
        self._sel_end = self._sel_start
        self._clear_selection_highlight()

    def _on_mouse_drag(self, event):
        """Extend selection."""
        self._sel_end = self._pixel_to_cell(event.x, event.y)
        self._draw_selection_highlight()

    def _on_mouse_up(self, event):
        """Finish selection."""
        self._sel_end = self._pixel_to_cell(event.x, event.y)
        self._draw_selection_highlight()

    def _sel_range(self):
        """Return (start, end) as (row, col) tuples in order."""
        s, e = self._sel_start, self._sel_end
        if s is None or e is None:
            return None, None
        if (s[0], s[1]) > (e[0], e[1]):
            s, e = e, s
        return s, e

    def _clear_selection_highlight(self):
        for item_id in self._sel_items:
            self.canvas.delete(item_id)
        self._sel_items = []

    def _draw_selection_highlight(self):
        self._clear_selection_highlight()
        start, end = self._sel_range()
        if start is None or start == end:
            return
        # Draw selection as inverted cells: white bg, black text
        for r in range(start[0], end[0] + 1):
            c0 = start[1] if r == start[0] else 0
            c1 = end[1] if r == end[0] else self.cols - 1
            x0 = c0 * self.char_width
            y0 = r * self.char_height
            x1 = (c1 + 1) * self.char_width
            y1 = y0 + self.char_height
            # Background
            bg_item = self.canvas.create_rectangle(
                x0, y0, x1, y1,
                fill=DEFAULT_FG, outline="",
            )
            self._sel_items.append(bg_item)
            # Redraw text in inverted colors
            for c in range(c0, c1 + 1):
                cell = self.term.get_cell(r, c)
                if cell and cell[0] > 0:
                    tx = c * self.char_width
                    text_item = self.canvas.create_text(
                        tx, y0, text=chr(cell[0]), fill=DEFAULT_BG,
                        font=self.font, anchor=tk.NW,
                    )
                    self._sel_items.append(text_item)

    def get_selected_text(self):
        """Return the text in the current selection."""
        start, end = self._sel_range()
        if start is None or start == end:
            return ""
        lines = []
        for r in range(start[0], end[0] + 1):
            c0 = start[1] if r == start[0] else 0
            c1 = end[1] if r == end[0] else self.cols - 1
            row_text = []
            for c in range(c0, c1 + 1):
                cell = self.term.get_cell(r, c)
                if cell and cell[0] > 0:
                    row_text.append(chr(cell[0]))
                else:
                    row_text.append(" ")
            lines.append("".join(row_text).rstrip())
        return "\n".join(lines)

    def copy_selection(self):
        """Copy selected text to system clipboard."""
        text = self.get_selected_text()
        if text:
            self.parent.clipboard_clear()
            self.parent.clipboard_append(text)
            return True
        return False

    def feed(self, data):
        """Buffer SSH data for rendering. Must be called from main thread.
        Multiple feed() calls between render cycles are coalesced into a
        single feed+render — this provides backpressure under burst output."""
        self._pending_data.extend(data)
        if not self._render_scheduled:
            self._render_scheduled = True
            self.parent.after_idle(self._flush_and_render)

    def _flush_and_render(self):
        """Process all buffered data and render once."""
        self._render_scheduled = False
        if self._pending_data:
            # Reset cursor blink on new data — cursor always visible after input
            self._cursor_visible = True
            self.term.feed(bytes(self._pending_data))
            self._pending_data.clear()
            self._render()

    def _render(self):
        """Redraw the screen from terminal state.
        Cursor is hidden during redraw to prevent visual flicker."""
        # Hide cursor during redraw
        if self._cursor_item:
            self.canvas.delete(self._cursor_item)
            self._cursor_item = None

        screen = self.term.get_screen(DEFAULT_FG, DEFAULT_BG)

        for r in range(min(len(screen), self.rows)):
            # Clear old items for this row
            for item_id in self._row_items[r]:
                self.canvas.delete(item_id)
            self._row_items[r] = []

            spans = screen[r]
            x = 0
            y = r * self.char_height

            for span in spans:
                text, fg, bg, attrs = span

                # Handle inverse video before drawing anything
                if attrs & 0x20:  # ATTR_INVERSE
                    fg, bg = bg, fg

                # Draw background rectangle for every span to cover old content
                text_width = self.char_width * len(text)
                rect_id = self.canvas.create_rectangle(
                    x, y, x + text_width, y + self.char_height,
                    fill=bg, outline="",
                )
                self._row_items[r].append(rect_id)

                # Determine font style from cache
                display_font = self._font_cache.get(attrs & 0x05, self.font)

                text_id = self.canvas.create_text(
                    x, y, text=text, fill=fg, font=display_font,
                    anchor=tk.NW,
                )
                self._row_items[r].append(text_id)
                x += self.char_width * len(text)

        # Defer cursor drawing to after Tk processes all pending canvas ops.
        # This prevents the cursor from flickering during the redraw cycle.
        self.parent.after_idle(self._show_cursor_after_render)

    def _show_cursor_after_render(self):
        """Draw cursor after Tk has processed all canvas operations."""
        if self._cursor_visible:
            self._draw_cursor()
        if self._cursor_blink and self._blink_id is None:
            self._blink_id = self.parent.after(530, self._toggle_blink)

    def _toggle_blink(self):
        """Toggle cursor visibility for blinking (redraws cursor only)."""
        self._cursor_visible = not self._cursor_visible
        if self._cursor_item:
            self.canvas.delete(self._cursor_item)
            self._cursor_item = None
        if self._cursor_visible:
            self._draw_cursor()
        if self._cursor_blink:
            self._blink_id = self.parent.after(530, self._toggle_blink)

    def _draw_cursor(self):
        """Draw the cursor at the current position."""
        crow, ccol = self.term.get_cursor()
        cx = ccol * self.char_width
        cy = crow * self.char_height
        style = self._cursor_style
        if style == "Block":
            self._cursor_item = self.canvas.create_rectangle(
                cx, cy, cx + self.char_width, cy + self.char_height,
                fill=DEFAULT_FG, outline="",
            )
        elif style == "Underline":
            uy = cy + self.char_height - 2
            self._cursor_item = self.canvas.create_rectangle(
                cx, uy, cx + self.char_width, cy + self.char_height,
                fill=DEFAULT_FG, outline="",
            )
        elif style == "Bar":
            self._cursor_item = self.canvas.create_rectangle(
                cx, cy, cx + 2, cy + self.char_height,
                fill=DEFAULT_FG, outline="",
            )
        else:  # Wireframe
            self._cursor_item = self.canvas.create_rectangle(
                cx, cy, cx + self.char_width, cy + self.char_height,
                outline=DEFAULT_FG, width=1,
            )

    def handle_key(self, event):
        """Handle a Tk key event."""
        if not self._write_callback:
            return

        # Map Tk keysym to _nbsterm key constants
        # Mac: Ctrl=0x4, Command=0x8, Alt/Option=0x10
        # Linux: Ctrl=0x4, Alt=0x8
        modifiers = 0
        if event.state & 0x1:
            modifiers |= _nbsterm.MOD_SHIFT
        if sys.platform == "darwin":
            alt_mask = 0x10  # Option key on Mac
        else:
            alt_mask = 0x8
        if event.state & alt_mask:
            modifiers |= _nbsterm.MOD_ALT
        if event.state & 0x4:
            modifiers |= _nbsterm.MOD_CTRL

        # Special keys
        special_map = {
            "Up": _nbsterm.KEY_UP,
            "Down": _nbsterm.KEY_DOWN,
            "Right": _nbsterm.KEY_RIGHT,
            "Left": _nbsterm.KEY_LEFT,
            "Home": _nbsterm.KEY_HOME,
            "End": _nbsterm.KEY_END,
            "Insert": _nbsterm.KEY_INSERT,
            "Delete": _nbsterm.KEY_DELETE,
            "Prior": _nbsterm.KEY_PAGEUP,
            "Next": _nbsterm.KEY_PAGEDOWN,
            "F1": _nbsterm.KEY_F1, "F2": _nbsterm.KEY_F2,
            "F3": _nbsterm.KEY_F3, "F4": _nbsterm.KEY_F4,
            "F5": _nbsterm.KEY_F5, "F6": _nbsterm.KEY_F6,
            "F7": _nbsterm.KEY_F7, "F8": _nbsterm.KEY_F8,
            "F9": _nbsterm.KEY_F9, "F10": _nbsterm.KEY_F10,
            "F11": _nbsterm.KEY_F11, "F12": _nbsterm.KEY_F12,
        }

        keysym = event.keysym
        if keysym in special_map:
            data = self.term.encode_special(special_map[keysym], modifiers)
        elif keysym == "Return":
            data = b"\r"
        elif keysym == "BackSpace":
            data = b"\x7f"
        elif keysym == "Tab":
            data = b"\t"
        elif keysym == "Escape":
            data = b"\x1b"
        elif (event.state & 0x4) and len(keysym) == 1 and keysym.isalpha():
            # Ctrl+letter: send control character directly (Ctrl-A=1, Ctrl-C=3, etc.)
            data = bytes([ord(keysym.upper()) - 0x40])
        elif (event.state & alt_mask) and len(keysym) == 1:
            # Alt/Meta+key: send ESC prefix + character
            data = b"\x1b" + keysym.encode("utf-8")
        elif event.char and len(event.char) > 0 and ord(event.char[0]) >= 1:
            # Regular character
            data = self.term.encode_key(ord(event.char[0]), modifiers)
        else:
            return  # Unhandled key (Shift, Control alone, etc.)

        if data:
            self._write_callback(data)

    def handle_resize(self, event):
        """Handle window resize."""
        new_cols = max(1, event.width // self.char_width)
        new_rows = max(1, event.height // self.char_height)
        if new_cols != self.cols or new_rows != self.rows:
            self.cols = new_cols
            self.rows = new_rows
            self.term.resize(new_rows, new_cols)
            self._row_items = [[] for _ in range(new_rows)]
            self._render()
            return (new_rows, new_cols)
        return None


class TkInteractionHandler(SSHInteractionHandler):
    """Bridge SSH interactive events to Tk dialogs.

    Each callback runs on the asyncio thread and uses
    concurrent.futures.Future to marshal to the Tk main thread.
    """

    def __init__(self, root):
        self._root = root

    def _ask_on_main_thread(self, fn, *args, **kwargs):
        """Run fn(*args, **kwargs) on the Tk main thread and return the result."""
        future = concurrent.futures.Future()
        self._root.after(0, self._run_and_set, future, fn, args, kwargs)
        try:
            return future.result(timeout=120)
        except (concurrent.futures.TimeoutError, concurrent.futures.CancelledError):
            return None

    @staticmethod
    def _run_and_set(future, fn, args, kwargs=None):
        future.set_result(fn(*args, **(kwargs or {})))

    def on_host_key(self, host, port, key_info):
        from tkinter import messagebox
        result = self._ask_on_main_thread(
            messagebox.askyesno,
            "Unknown Host Key",
            f"The authenticity of host '{host}' ({port}) can't be established.\n"
            f"{key_info}\n\nAccept and connect anyway?",
        )
        return bool(result)

    def on_kbdint(self, name, instructions, prompts):
        log.debug("kbdint challenge: name=%r, prompts=%d", name, len(prompts))
        responses = []
        for prompt_text, echo in prompts:
            log.debug("kbdint prompt: %r (echo=%s)", prompt_text, echo)
            show = None if echo else "*"
            response = self._ask_on_main_thread(
                simpledialog.askstring,
                "SSH Authentication", prompt_text, show=show,
            )
            if response is None:
                log.debug("User cancelled auth prompt")
                return []
            responses.append(response)
        return responses


class SSHTransport:
    """Manages SSH connection in a background asyncio thread."""

    def __init__(self, host, port=None, username=None):
        self.host = host
        self.port = port
        self.username = username
        self._loop = None
        self._thread = None
        self._process = None
        self._conn = None
        self._on_data = None
        self._on_close = None
        self._on_error = None
        self._interaction_handler = None
        self._running = False

    def set_data_callback(self, cb):
        self._on_data = cb

    def set_close_callback(self, cb):
        self._on_close = cb

    def set_interaction_handler(self, handler):
        self._interaction_handler = handler

    def set_error_callback(self, cb):
        self._on_error = cb

    def start(self, rows, cols):
        """Start the SSH connection in a background thread."""
        self._running = True
        self._thread = threading.Thread(
            target=self._run_asyncio, args=(rows, cols), daemon=True,
        )
        self._thread.start()

    def _run_asyncio(self, rows, cols):
        """Run the asyncio event loop in a background thread."""
        self._loop = asyncio.new_event_loop()
        asyncio.set_event_loop(self._loop)
        try:
            self._loop.run_until_complete(self._ssh_session(rows, cols))
        except Exception as e:
            log.error("SSH session failed: %s", e, exc_info=True)
            if self._on_error:
                self._on_error(str(e))
            else:
                print(f"SSH error: {e}", file=sys.stderr)
        finally:
            log.debug("SSH session ended")
            self._running = False
            if self._on_close:
                self._on_close()

    async def _ssh_session(self, rows, cols):
        """Connect and run the SSH shell session using nbs-ssh."""
        log.info("Connecting to %s:%s as %s",
                 self.host, self.port or 22, self.username or "(default)")

        # Build auth chain matching the CLI's cert + kbdint flow.
        # The server requires publickey (cert) first, then offers kbdint
        # (Duo) as second factor. We must include cert-backed agent keys
        # from SSH config before kbdint.
        auth = []

        # Load certificate identity files from SSH config
        # (matches CLI __main__.py lines 958-988)
        ssh_config = SSHConfig()
        host_config = ssh_config.lookup(self.host)
        cert_files = [
            p for p in (host_config.identity_file or [])
            if str(p).endswith("-cert.pub") and p.exists()
        ]
        for cert_path in cert_files:
            try:
                key_pair = await get_agent_cert_key_pair(
                    cert_path,
                    agent_path=host_config.identity_agent,
                )
                if key_pair is not None:
                    cert_auth = AuthConfig(method=AuthMethod.SSH_AGENT)
                    cert_auth._agent_key_pair = key_pair
                    auth.append(cert_auth)
                    log.info("Certificate identity: %s (agent-backed)", cert_path)
            except Exception as e:
                log.warning("Failed to load certificate %s: %s", cert_path, e)

        # Add kbdint for second factor (Duo 2FA via Tk dialog)
        auth.append(create_keyboard_interactive_auth(
            response_callback=self._interaction_handler.on_kbdint,
        ))

        conn_kwargs = {
            "host": self.host,
            "interaction_handler": self._interaction_handler,
            "auth": auth,
        }
        if self.port:
            conn_kwargs["port"] = self.port
        if self.username:
            conn_kwargs["username"] = self.username
        conn = SSHConnection(**conn_kwargs)

        async with conn:
            self._conn = conn
            log.debug("Creating PTY process (term=%s, size=%dx%d)",
                      "xterm-256color", cols, rows)
            process = await conn._conn.create_process(
                None,  # shell
                term_type="xterm-256color",
                term_size=(cols, rows),
            )
            self._process = process
            log.info("PTY session started")

            # Read loop
            try:
                while self._running:
                    data = await process.stdout.read(4096)
                    if not data:
                        break
                    if self._on_data:
                        self._on_data(data.encode() if isinstance(data, str) else data)
            except asyncio.CancelledError:
                pass
            except Exception as e:
                if self._on_error:
                    self._on_error(str(e))
                else:
                    print(f"SSH read error: {e}", file=sys.stderr)

    def write(self, data):
        """Send data to the SSH process. Thread-safe."""
        if self._process and self._loop and self._running:
            asyncio.run_coroutine_threadsafe(
                self._async_write(data), self._loop
            )

    async def _async_write(self, data):
        """Write data to SSH stdin from the asyncio thread."""
        if self._process:
            self._process.stdin.write(data.decode("utf-8", errors="replace")
                                     if isinstance(data, bytes) else data)

    def resize(self, rows, cols):
        """Resize the PTY. Thread-safe."""
        if self._process and self._loop and self._running:
            asyncio.run_coroutine_threadsafe(
                self._async_resize(rows, cols), self._loop
            )

    async def _async_resize(self, rows, cols):
        """Resize PTY from the asyncio thread."""
        if self._process:
            self._process.change_terminal_size(cols, rows)

    def stop(self):
        """Stop the SSH connection."""
        self._running = False
        if self._process:
            try:
                self._process.stdin.write_eof()
            except Exception:
                pass


class PreferencesDialog(tk.Toplevel):
    """Tk preferences dialog for nbs-term settings."""

    def __init__(self, parent, config, on_save=None):
        super().__init__(parent)
        self.title("Preferences")
        self.resizable(False, False)
        self.transient(parent)
        self.grab_set()
        self._config = config
        self._on_save = on_save

        # Font section
        tk.Label(self, text="Font", font=("", 12, "bold")).grid(
            row=0, column=0, columnspan=2, sticky="w", padx=10, pady=(10, 5))

        tk.Label(self, text="Family:").grid(row=1, column=0, sticky="e", padx=10)
        self._font_family = tk.StringVar(value=config.font.family)
        fonts = ["Menlo", "Monaco", "Courier New", "Consolas",
                 "DejaVu Sans Mono", "Liberation Mono", "monospace"]
        family_menu = tk.OptionMenu(self, self._font_family, *fonts)
        family_menu.grid(row=1, column=1, sticky="w", padx=10, pady=2)

        tk.Label(self, text="Size:").grid(row=2, column=0, sticky="e", padx=10)
        self._font_size = tk.IntVar(value=config.font.size)
        tk.Spinbox(self, from_=6, to=72, textvariable=self._font_size, width=5).grid(
            row=2, column=1, sticky="w", padx=10, pady=2)

        # Cursor section
        tk.Label(self, text="Cursor", font=("", 12, "bold")).grid(
            row=3, column=0, columnspan=2, sticky="w", padx=10, pady=(10, 5))

        tk.Label(self, text="Style:").grid(row=4, column=0, sticky="e", padx=10)
        self._cursor_style = tk.StringVar(value=config.cursor.style)
        styles = tk.OptionMenu(self, self._cursor_style,
                               "Block", "Wireframe", "Underline", "Bar")
        styles.grid(row=4, column=1, sticky="w", padx=10, pady=2)

        self._cursor_blink = tk.BooleanVar(value=config.cursor.blink)
        tk.Checkbutton(self, text="Blink", variable=self._cursor_blink).grid(
            row=5, column=1, sticky="w", padx=10, pady=2)

        # Buttons
        btn_frame = tk.Frame(self)
        btn_frame.grid(row=6, column=0, columnspan=2, pady=10)
        tk.Button(btn_frame, text="Save", command=self._save).pack(side=tk.LEFT, padx=5)
        tk.Button(btn_frame, text="Cancel", command=self.destroy).pack(side=tk.LEFT, padx=5)

    def _save(self):
        self._config.font.family = self._font_family.get()
        self._config.font.size = self._font_size.get()
        self._config.cursor.style = self._cursor_style.get()
        self._config.cursor.blink = self._cursor_blink.get()
        save_config(self._config)
        if self._on_save:
            self._on_save(self._config)
        self.destroy()


class TerminalApp:
    """Main application tying together Tk, Terminal, and SSH."""

    def __init__(self, host, port=None, username=None, config=None):
        self.root = tk.Tk()
        self.root.title(f"nbs-term — {host}")
        self._config = config or TerminalConfig()

        # No visible menu bar — preferences accessed via Cmd+, (Mac) or Ctrl+, (Linux)

        # Terminal widget with config
        if config:
            self.widget = TerminalWidget(
                self.root,
                rows=config.rows, cols=config.cols,
                font_family=config.font.family, font_size=config.font.size,
                cursor_style=config.cursor.style, cursor_blink=config.cursor.blink,
            )
        else:
            self.widget = TerminalWidget(self.root)

        # Constrain window to screen and center
        self.root.update_idletasks()
        win_w = self.root.winfo_reqwidth()
        win_h = self.root.winfo_reqheight()
        scr_w = self.root.winfo_screenwidth()
        scr_h = self.root.winfo_screenheight()
        win_w = min(win_w, scr_w - 40)
        win_h = min(win_h, scr_h - 80)
        x = (scr_w - win_w) // 2
        y = (scr_h - win_h) // 2
        self.root.geometry(f"{win_w}x{win_h}+{x}+{y}")

        # SSH transport
        self.ssh = SSHTransport(host, port, username)

        # Wire callbacks
        self.widget.set_write_callback(self.ssh.write)
        self.ssh.set_data_callback(self._on_ssh_data)
        self.ssh.set_close_callback(self._on_ssh_close)
        self.ssh.set_interaction_handler(TkInteractionHandler(self.root))
        self.ssh.set_error_callback(self._on_ssh_error)

        # Bind keyboard
        self.root.bind("<Key>", self.widget.handle_key)

        # Copy/Paste and Preferences shortcuts
        if sys.platform == "darwin":
            self.root.bind("<Command-c>", self._on_copy)
            self.root.bind("<Command-v>", self._on_paste)
            self.root.bind("<Command-comma>", self._on_preferences)
        else:
            self.root.bind("<Control-Shift-C>", self._on_copy)
            self.root.bind("<Control-Shift-V>", self._on_paste)
            self.root.bind("<Control-comma>", self._on_preferences)

        # Bind resize
        self.widget.canvas.bind("<Configure>", self._on_configure)

        # Handle window close
        self.root.protocol("WM_DELETE_WINDOW", self._on_close)

    def _on_copy(self, event=None):
        """Copy selected text to clipboard."""
        self.widget.copy_selection()
        return "break"

    def _on_paste(self, event=None):
        """Paste clipboard text into the terminal."""
        try:
            text = self.root.clipboard_get()
        except tk.TclError:
            return "break"  # clipboard empty
        if text and self.ssh._running:
            data = self.widget.term.encode_paste(text.encode("utf-8"))
            self.ssh.write(data)
        return "break"

    def _on_preferences(self, event=None):
        """Open the preferences dialog."""
        PreferencesDialog(self.root, self._config)
        return "break"

    def _on_ssh_error(self, error_msg):
        """Show SSH errors in the terminal window."""
        self.root.after(0, self.widget.feed,
                        f"\r\n[SSH error: {error_msg}]\r\n".encode())

    def _on_ssh_data(self, data):
        """Called from asyncio thread when SSH data arrives."""
        # Marshal to main thread via root.after
        self.root.after(0, self.widget.feed, data)

    def _on_ssh_close(self):
        """Called when SSH connection closes."""
        self.root.after(0, self._handle_disconnect)

    def _handle_disconnect(self):
        """Handle SSH disconnect on main thread."""
        self.widget.feed(b"\r\n[Connection closed]\r\n")

    def _on_configure(self, event):
        """Handle canvas resize."""
        result = self.widget.handle_resize(event)
        if result:
            rows, cols = result
            self.ssh.resize(rows, cols)

    def _on_close(self):
        """Handle window close."""
        self.ssh.stop()
        self.root.destroy()

    def run(self):
        """Start the application."""
        self.ssh.start(self.widget.rows, self.widget.cols)
        self.root.mainloop()


def main():
    import argparse
    parser = argparse.ArgumentParser(
        prog="nbs-term",
        description="Terminal emulator over SSH",
    )
    parser.add_argument("target", help="[user@]host[:port]")
    parser.add_argument("-v", "--verbose", action="store_true",
                        help="enable verbose logging")
    parser.add_argument("--font-size", type=int, dest="font_size",
                        help="font size (overrides config)")
    parser.add_argument("--font-family", dest="font_family",
                        help="font family (overrides config)")
    parser.add_argument("--rows", type=int,
                        help="initial terminal rows (overrides config)")
    parser.add_argument("--cols", type=int,
                        help="initial terminal columns (overrides config)")
    args = parser.parse_args()

    if args.verbose:
        logging.basicConfig(
            level=logging.DEBUG,
            format="%(asctime)s %(name)s %(levelname)s %(message)s",
            stream=sys.stderr,
        )
        logging.getLogger("asyncssh").setLevel(logging.DEBUG)
    else:
        logging.basicConfig(level=logging.WARNING, stream=sys.stderr)

    # Parse user@host:port
    username = None
    port = None
    host = args.target

    if "@" in host:
        username, host = host.rsplit("@", 1)
    if ":" in host:
        host, port_str = host.rsplit(":", 1)
        port = int(port_str)

    config = load_config(args)
    app = TerminalApp(host, port, username, config=config)
    app.run()


if __name__ == "__main__":
    main()
