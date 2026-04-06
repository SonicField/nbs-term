#!/usr/bin/env python3
"""
nbs-term: Terminal emulator application.

Wires the _nbsterm C extension to Tk (display) and nbs-ssh (transport).

Architecture:
  Main thread (Tk): mainloop, term.feed(), canvas rendering, user input
  Background thread (asyncio): nbs-ssh connection, byte I/O

Invariant: C extension only called from main thread.
"""
import sys
import os
import asyncio
import threading
import tkinter as tk
import tkinter.font as tkfont

# Add nbs-ssh and its dependencies to path
sys.path.insert(0, os.path.expanduser("~/local/nbs-ssh/src"))
sys.path.insert(0, os.path.expanduser("~/local/nbs-ssh/venv/lib/python3.15/site-packages"))

import _nbsterm
from nbs_ssh import SSHConnection, HostKeyPolicy

# --- Configuration ---

DEFAULT_ROWS = 24
DEFAULT_COLS = 80
DEFAULT_FONT_FAMILY = "monospace"
DEFAULT_FONT_SIZE = 14
DEFAULT_FG = "#d0d0d0"
DEFAULT_BG = "#1a1a1a"
SCROLLBACK_LINES = 10000


class TerminalWidget:
    """Tk canvas-based terminal display."""

    def __init__(self, parent, rows=DEFAULT_ROWS, cols=DEFAULT_COLS):
        self.parent = parent
        self.rows = rows
        self.cols = cols

        # Font setup — cache all 4 style variants
        self.font = tkfont.Font(family=DEFAULT_FONT_FAMILY, size=DEFAULT_FONT_SIZE)
        self._font_cache = {
            0: self.font,
            0x01: tkfont.Font(family=DEFAULT_FONT_FAMILY, size=DEFAULT_FONT_SIZE, weight="bold"),
            0x04: tkfont.Font(family=DEFAULT_FONT_FAMILY, size=DEFAULT_FONT_SIZE, slant="italic"),
            0x05: tkfont.Font(family=DEFAULT_FONT_FAMILY, size=DEFAULT_FONT_SIZE, weight="bold", slant="italic"),
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

        # Callbacks
        self._write_callback = None  # called with bytes to send to SSH

    def set_write_callback(self, cb):
        self._write_callback = cb

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
            self.term.feed(bytes(self._pending_data))
            self._pending_data.clear()
            self._render()

    def _render(self):
        """Redraw the screen from terminal state."""
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

                # Draw background rectangle if not default
                if bg != DEFAULT_BG:
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

        # Draw cursor
        if self._cursor_item:
            self.canvas.delete(self._cursor_item)
        crow, ccol = self.term.get_cursor()
        cx = ccol * self.char_width
        cy = crow * self.char_height
        self._cursor_item = self.canvas.create_rectangle(
            cx, cy, cx + self.char_width, cy + self.char_height,
            outline=DEFAULT_FG, width=1,
        )

    def handle_key(self, event):
        """Handle a Tk key event."""
        if not self._write_callback:
            return

        # Map Tk keysym to _nbsterm key constants
        modifiers = 0
        if event.state & 0x1:
            modifiers |= _nbsterm.MOD_SHIFT
        if event.state & 0x8:
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
        elif event.char and len(event.char) > 0 and ord(event.char[0]) >= 1:
            # Regular character (including Ctrl+letter which produces chars 1-26)
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
        self._on_data = None  # callback for received data (called from asyncio thread)
        self._on_close = None
        self._running = False

    def set_data_callback(self, cb):
        self._on_data = cb

    def set_close_callback(self, cb):
        self._on_close = cb

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
            print(f"SSH error: {e}", file=sys.stderr)
        finally:
            self._running = False
            if self._on_close:
                self._on_close()

    async def _ssh_session(self, rows, cols):
        """Connect and run the SSH shell session."""
        conn = SSHConnection(
            self.host,
            port=self.port,
            username=self.username,
            host_key_policy=HostKeyPolicy.ACCEPT_NEW,
        )
        async with conn:
            self._conn = conn
            # NOTE: Accesses nbs-ssh internal asyncssh connection (_conn) because
            # SSHConnection has no public API for raw PTY process creation.
            # shell() handles the full interactive session (stdin/stdout forwarding)
            # which we don't want — we need raw byte access for our own terminal.
            # If nbs-ssh adds a public create_process API, switch to it.
            process = await conn._conn.create_process(
                None,  # shell
                term_type="xterm-256color",
                term_size=(cols, rows),
            )
            self._process = process

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


class TerminalApp:
    """Main application tying together Tk, Terminal, and SSH."""

    def __init__(self, host, port=None, username=None):
        self.root = tk.Tk()
        self.root.title(f"nbs-term — {host}")

        # Terminal widget
        self.widget = TerminalWidget(self.root)

        # SSH transport
        self.ssh = SSHTransport(host, port, username)

        # Wire callbacks
        self.widget.set_write_callback(self.ssh.write)
        self.ssh.set_data_callback(self._on_ssh_data)
        self.ssh.set_close_callback(self._on_ssh_close)

        # Bind keyboard
        self.root.bind("<Key>", self.widget.handle_key)

        # Bind resize
        self.widget.canvas.bind("<Configure>", self._on_configure)

        # Handle window close
        self.root.protocol("WM_DELETE_WINDOW", self._on_close)

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
    if len(sys.argv) < 2:
        print(f"Usage: {sys.argv[0]} [user@]host[:port]", file=sys.stderr)
        sys.exit(1)

    target = sys.argv[1]

    # Parse user@host:port
    username = None
    port = None
    host = target

    if "@" in host:
        username, host = host.rsplit("@", 1)
    if ":" in host:
        host, port_str = host.rsplit(":", 1)
        port = int(port_str)

    app = TerminalApp(host, port, username)
    app.run()


if __name__ == "__main__":
    main()
