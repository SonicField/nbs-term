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
import platform
import asyncio
import logging
import threading
import concurrent.futures

# Windows DPI awareness — must be set before Tk initialises.
# Without this, Tk renders at 96 DPI and upscales, causing jagged text.
if platform.system() == "Windows":
    import ctypes
    try:
        ctypes.windll.shcore.SetProcessDpiAwareness(2)
    except (AttributeError, OSError):
        pass  # Pre-Win8.1 or missing shcore

import tkinter as tk
from tkinter import ttk
import tkinter.font as tkfont
import tkinter.simpledialog as simpledialog
import tkinter.colorchooser as colorchooser

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
PADDING = 8  # minimum canvas-internal border. Text origin centers in the canvas via _compute_origin_for, but never closer than PADDING to any edge.


SCROLLBACK_LINES = 10000


def _named_font(name, **kwargs):
    """Return the named font, reusing the existing one if already in Tk's
    global registry. Tk font names are global per interpreter, so a second
    TerminalWidget instance (e.g. opened via Cmd+T) cannot create the
    same name again — reuse instead. Bug D fix."""
    if name in tkfont.names():
        return tkfont.nametofont(name)
    return tkfont.Font(name=name, **kwargs)


# Color utilities — implemented in C (src/color_utils.phc)
dim_color = _nbsterm.dim_color
gamma_correct = _nbsterm.gamma_correct


class TerminalWidget:
    """Tk canvas-based terminal display."""

    # Unicode cursor characters — rendered inline with text for perfect alignment
    _CURSOR_CHARS = {
        "Block": "\u2588",      # █ Full block
        "Underline": "\u2581",  # ▁ Lower one eighth block
        "Bar": "\u258f",        # ▏ Left one eighth block
    }

    def __init__(self, parent, rows=DEFAULT_ROWS, cols=DEFAULT_COLS,
                 font_family=DEFAULT_FONT_FAMILY, font_size=DEFAULT_FONT_SIZE,
                 cursor_style="Block", cursor_blink=True, cursor_color=None,
                 gamma=1.0, fg=DEFAULT_FG, bg=DEFAULT_BG, refresh_hz=60):
        self.parent = parent
        self._refresh_ms = max(1, 1000 // refresh_hz)
        self.rows = rows
        self._gamma = gamma
        self._fg = fg
        self._bg = bg
        # Mirror C render_gamma (extension.phc:607) on Python-painted bg
        # surfaces so canvas widget bg + bg_fill rect match per-cell bg
        # pixels. Without this, gamma!=1.0 makes the slop look lighter
        # than the text-area cells (Mac default gamma=1.2).
        self._bg_render = gamma_correct(self._bg, self._gamma)
        self.cols = cols
        self._cursor_style = cursor_style
        self._cursor_blink = cursor_blink
        self._cursor_color = cursor_color  # None = use fg
        self._cursor_visible = True
        self._blink_id = None

        # Font setup — use requested font (no silent fallback). Named fonts
        # so C render_frame() can reference them via Tcl. Reuse existing
        # named fonts on second+ TerminalWidget (Cmd+T) — Tk font names are
        # global per interpreter so we cannot create the same name twice.
        self.font = _named_font(
            "font_normal", family=font_family, size=font_size)
        self._font_cache = {
            0: self.font,
            0x01: _named_font(
                "font_bold", family=font_family, size=font_size, weight="bold"),
            0x04: _named_font(
                "font_italic", family=font_family, size=font_size, slant="italic"),
            0x05: _named_font(
                "font_bold_italic", family=font_family, size=font_size,
                weight="bold", slant="italic"),
        }
        # char_width: cold-start primitive uses an averaged sample across
        # representative chars (M wide, i narrow, space, digit, etc) so the
        # initial value is reasonable on platforms whose 'monospace' alias
        # is not actually fixed-width (Windows). After first paint, _render
        # self-corrects char_width from the actual rendered bbox.
        self.char_width = max(1, self.font.measure("MiW 0x.") // 7)
        self.char_height = self.font.metrics("linespace")

        # Canvas — single widget, owned by TerminalWidget, packed by caller
        # (TerminalApp swaps tabs via canvas.pack/pack_forget on root). Text
        # is drawn at (origin_x, origin_y) computed per resize so the text
        # grid stays centered inside the canvas with at least PADDING on
        # every side. Border region (canvas pixels outside the text grid)
        # is painted by a canvas-item rectangle in _render so it shows
        # clean bg even when the canvas WIDGET bg attr aqua-tints.
        width = self.cols * self.char_width + 2 * PADDING
        height = self.rows * self.char_height + 2 * PADDING
        self.canvas = tk.Canvas(
            parent, width=width, height=height,
            bg=self._bg_render, highlightthickness=0, borderwidth=0,
        )
        # Initial origin = PADDING; recomputed in handle_resize once the
        # canvas has its real geometry.
        self._origin_x = PADDING
        self._origin_y = PADDING

        # Terminal engine
        self.term = _nbsterm.Terminal(rows, cols)

        # Backpressure: buffer incoming data, render on next idle cycle
        self._pending_data = bytearray()
        self._render_scheduled = False

        # Selection state
        self._sel_start = None  # (row, col) of selection start
        self._sel_end = None    # (row, col) of selection end

        # Mouse bindings for selection
        self.canvas.bind("<ButtonPress-1>", self._on_mouse_down)
        self.canvas.bind("<B1-Motion>", self._on_mouse_drag)
        self.canvas.bind("<ButtonRelease-1>", self._on_mouse_up)

        # Scrollback bindings
        self.canvas.bind("<MouseWheel>", self._on_mouse_wheel)  # Windows/macOS
        self.canvas.bind("<Button-4>", self._on_scroll_up)      # Linux scroll up
        self.canvas.bind("<Button-5>", self._on_scroll_down)    # Linux scroll down
        parent.bind("<Control-Shift-Up>", self._on_key_scroll_up)
        parent.bind("<Control-Shift-Down>", self._on_key_scroll_down)

        # Callbacks
        self._write_callback = None  # called with bytes to send to SSH

    def set_write_callback(self, cb):
        self._write_callback = cb

    def _compute_origin_for(self, cols, rows, canvas_w, canvas_h):
        """Centered text origin via the same per-span font.measure machinery
        the mouse-selection fix uses (_pixel_to_cell_text_aware). Walks
        _row_spans_for_visible(r) for each row, sums font.measure(span_text)
        with the per-span font (bold/italic/etc keyed on attrs & 0x05);
        takes the max row width as text_w. Pixel-accurate on Mac CoreText
        because Tcl 'font measure' (used by both render_frame and
        Python tkfont.Font.measure) is the same call on the same text.

        Vertical: rows * char_height — line metric is uniform, no
        subadditivity in the y direction.

        Cold start (no spans yet, all rows return None or empty): origin
        = (PADDING, PADDING) so the first paint lands at a defined spot."""
        text_w = 0
        for r in range(rows):
            spans = self._row_spans_for_visible(r)
            if not spans:
                continue
            row_w = 0
            for span in spans:
                text_bytes, _fg, _bg, attrs, _col_widths = span
                text = (text_bytes if isinstance(text_bytes, str)
                        else text_bytes.decode("utf-8", "replace"))
                if not text:
                    continue
                font = self._font_cache.get(attrs & 0x05, self.font)
                row_w += font.measure(text)
            if row_w > text_w:
                text_w = row_w
        if text_w == 0:
            return (PADDING, PADDING)
        text_h = rows * self.char_height
        return ((canvas_w - text_w) // 2, (canvas_h - text_h) // 2)

    def _row_spans_for_visible(self, row):
        """Return spans for visible viewport row, mirroring C composite-scrollback
        logic at extension.c:3530-3559 (`scroll_off > 0 && !using_alt`).
        None if unavailable.
        """
        scroll_off = self.term.get_scroll_offset()
        if scroll_off > 0 and not self.term.using_alt():
            sb_count = self.term.get_scrollback_count()
            sb_line_idx = sb_count - scroll_off + row
            if 0 <= sb_line_idx < sb_count:
                spans = self.term.get_scrollback_line(sb_line_idx)
                return spans if spans else None
            screen_row = sb_line_idx - sb_count
            screen = self.term.get_screen()
            if 0 <= screen_row < len(screen):
                return screen[screen_row]
            return None
        screen = self.term.get_screen()
        if 0 <= row < len(screen):
            return screen[row]
        return None

    @staticmethod
    def _binary_search_char(text, font, local_x):
        """Smallest i such that font.measure(text[:i+1]) > local_x.
        Returns len(text) when local_x lies past the span's right edge."""
        lo, hi = 0, len(text)
        while lo < hi:
            mid = (lo + hi) // 2
            if local_x < font.measure(text[:mid + 1]):
                hi = mid
            else:
                lo = mid + 1
        return lo

    def _pixel_to_cell_text_aware(self, x, y):
        """Map (x, y) to (row, col) using actual font metrics for the row's
        rendered text. Equivalent-by-construction to the C renderer's per-span
        layout (verified by tests/test_render_layout_equivalence.py).

        Bug A fix: replaces the uniform-grid assumption that breaks on macOS,
        where CoreText subadditivity makes font.measure(c*N) != N*font.measure(c).
        Walks get_screen() spans (or scrollback composite when scrolled back),
        accumulates font.measure(prefix), and binary-searches for the cell x
        falls in. Cold-start fallback (no spans available) uses uniform-grid
        math via _nbsterm.pixel_to_cell with self.char_width — which is
        bbox-calibrated post-first-paint, so the fallback is reasonably
        accurate even on non-monospace fonts.
        """
        row = (y - self._origin_y) // self.char_height
        if row < 0:
            row = 0
        elif row >= self.rows:
            row = self.rows - 1

        spans = self._row_spans_for_visible(row)
        if not spans:
            return _nbsterm.pixel_to_cell(
                x - self._origin_x, y - self._origin_y,
                self.char_width, self.char_height, self.cols, self.rows)

        cur_x = self._origin_x
        cur_col = 0
        for text_bytes, _fg, _bg, attrs, col_widths in spans:
            text = (text_bytes if isinstance(text_bytes, str)
                    else text_bytes.decode("utf-8", "replace"))
            if not text:
                continue
            font = self._font_cache.get(attrs & 0x05, self.font)
            span_width = font.measure(text)
            if x < cur_x + span_width:
                local_x = x - cur_x
                char_i = self._binary_search_char(text, font, local_x)
                if char_i >= len(text):
                    col_in_span = sum(col_widths)
                else:
                    col_in_span = sum(col_widths[:char_i])
                col = cur_col + col_in_span
                if col < 0:
                    col = 0
                if col >= self.cols:
                    col = self.cols - 1
                return (row, col)
            cur_x += span_width
            cur_col += sum(col_widths)

        return (row, self.cols - 1)

    def _on_mouse_down(self, event):
        """Start selection."""
        self._sel_start = self._pixel_to_cell_text_aware(event.x, event.y)
        self._sel_end = self._sel_start
        self._clear_selection_highlight()

    def _on_mouse_drag(self, event):
        """Extend selection."""
        self._sel_end = self._pixel_to_cell_text_aware(event.x, event.y)
        self._draw_selection_highlight()

    def _on_mouse_up(self, event):
        """Finish selection."""
        self._sel_end = self._pixel_to_cell_text_aware(event.x, event.y)
        self._draw_selection_highlight()

    def _sel_range(self):
        """Return (start, end) as (row, col) tuples in order."""
        s, e = self._sel_start, self._sel_end
        if s is None or e is None:
            return None, None
        sr, sc, er, ec = _nbsterm.sel_range(s[0], s[1], e[0], e[1])
        return (sr, sc), (er, ec)

    def _clear_selection_highlight(self):
        self.term.clear_selection()
        self._render()

    def _draw_selection_highlight(self):
        start, end = self._sel_range()
        if start is None or start == end:
            self._clear_selection_highlight()
            return
        self.term.draw_selection(start[0], start[1], end[0], end[1])
        self._render()

    # --- Scrollback ---

    def _on_mouse_wheel(self, event):
        """Handle mouse wheel (Windows/macOS: event.delta)."""
        if event.delta > 0:
            self.term.scroll_lines(3)  # scroll up into history
        elif event.delta < 0:
            self.term.scroll_lines(-3)  # scroll down toward live
        self._render()

    def _on_scroll_up(self, event):
        """Handle Linux scroll up (Button-4)."""
        self.term.scroll_lines(3)
        self._render()

    def _on_scroll_down(self, event):
        """Handle Linux scroll down (Button-5)."""
        self.term.scroll_lines(-3)
        self._render()

    def _on_key_scroll_up(self, event):
        """Ctrl+Shift+Up: scroll up one line."""
        self.term.scroll_lines(1)
        self._render()
        return "break"

    def _on_key_scroll_down(self, event):
        """Ctrl+Shift+Down: scroll down one line."""
        self.term.scroll_lines(-1)
        self._render()
        return "break"

    def _auto_scroll_to_bottom(self):
        """Reset scroll offset to live output."""
        if self.term.get_scroll_offset() > 0:
            self.term.set_scroll_offset(0)

    def get_selected_text(self):
        """Return the text in the current selection."""
        start, end = self._sel_range()
        if start is None or start == end:
            return ""
        return self.term.extract_selected_text(start[0], start[1], end[0], end[1])

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
        Data is coalesced at the configured refresh rate to reduce flicker
        from SSH data chunking."""
        self._pending_data.extend(data)
        if not self._render_scheduled:
            self._render_scheduled = True
            self.parent.after(self._refresh_ms, self._flush_and_render)

    def _flush_and_render(self):
        """Process all buffered data and render once per frame."""
        self._render_scheduled = False
        if self._pending_data:
            self._cursor_visible = True
            # Reset blink timer so cursor stays visible during active output
            if self._blink_id is not None:
                self.parent.after_cancel(self._blink_id)
                self._blink_id = None
            self._auto_scroll_to_bottom()
            self.term.feed(bytes(self._pending_data))
            self._pending_data.clear()
            self._render()

    def _render(self):
        """Delegate rendering to C via Tcl. C manages double-buffering internally.
        Origin (text top-left) is recomputed here from CURRENT canvas dims +
        CURRENT spans, so it always reflects the live state — no cache to go
        stale across resize/tab-switch ordering races. self._origin_{x,y}
        gets updated as a side effect so mouse handlers
        (_pixel_to_cell_text_aware) see the same coordinates the renderer
        used for the most recent paint.
        bg_fill rect underneath covers canvas widget bg with text bg color."""
        canvas_w = self.canvas.winfo_width()
        canvas_h = self.canvas.winfo_height()
        self._origin_x, self._origin_y = self._compute_origin_for(
            self.cols, self.rows, canvas_w, canvas_h)
        self.canvas.delete("bg_fill")
        self.canvas.create_rectangle(
            0, 0, canvas_w, canvas_h,
            fill=self._bg_render, outline="", tags="bg_fill")
        self.canvas.tag_lower("bg_fill")
        # Cursor style: 0=Block, 1=Underline, 2=Bar
        style_map = {"Block": 0, "Underline": 1, "Bar": 2}
        cursor_style_int = style_map.get(self._cursor_style, 0)

        self.term.render_frame(
            self.parent.tk.interpaddr(),
            str(self.canvas),
            self._cursor_visible,
            cursor_style_int,
            self._cursor_color or "",
            self._fg,
            self._bg,
            self._gamma,
            self.char_width,
            self.char_height,
            self._origin_x,
            self._origin_y,
        )
        # bbox-calibration: derive effective per-cell width from what was
        # actually painted. Asymmetric clamp — only WIDEN char_width, never
        # shrink. Sparse content (mostly spaces) gives bbox/cols ≈ space
        # width, which on non-monospace fonts (Windows 'monospace' alias)
        # is much smaller than 'M' width. Letting char_width shrink to
        # space width inflates cols, oversizes the SSH session, and
        # overflows the canvas (alexie 2026-04-28 14:23:15: line wrap
        # broken). Asymmetry preserves self-correction for under-estimated
        # initial samples while preventing the cols-runaway.
        bb0 = self.canvas.bbox("buf_0")
        bb1 = self.canvas.bbox("buf_1")
        bb = bb0 if bb0 and (not bb1 or (bb0[2] - bb0[0]) >= (bb1[2] - bb1[0])) else bb1
        if bb is not None and self.cols > 0:
            effective_cw = (bb[2] - bb[0]) / self.cols
            if effective_cw > self.char_width + 0.5:
                self.char_width = max(1, int(round(effective_cw)))

        # Restart blink timer
        if self._cursor_blink and self._blink_id is None:
            self._blink_id = self.parent.after(530, self._toggle_blink)

    def _toggle_blink(self):
        """Toggle cursor visibility and trigger a re-render of the cursor row."""
        self._cursor_visible = not self._cursor_visible
        self._blink_id = None
        # Force cursor row dirty so _render() redraws it
        crow, _ = self.term.get_cursor()
        if crow < self.rows:
            self._render()

    def handle_key(self, event):
        """Handle a Tk key event — dispatch to C for encoding."""
        if not self._write_callback:
            return

        char_code = ord(event.char[0]) if event.char and len(event.char) > 0 else 0
        is_mac = sys.platform == "darwin"
        data = self.term.encode_tk_event(
            event.keysym, event.state, char_code, is_mac)

        if data:
            self._auto_scroll_to_bottom()
            self._write_callback(data)

    def handle_resize(self, event):
        """Handle window resize. event comes from the canvas's Configure
        (event.width/height = canvas size). Recomputes cols/rows; origin is
        recomputed inside _render from fresh canvas dims + fresh spans, so
        no ordering race here."""
        new_cols = max(1, (event.width - 2 * PADDING) // self.char_width)
        new_rows = max(1, (event.height - 2 * PADDING) // self.char_height)
        if new_cols != self.cols or new_rows != self.rows:
            self.cols = new_cols
            self.rows = new_rows
            self.term.resize(new_rows, new_cols)
            self.canvas.delete("buf_0")
            self.canvas.delete("buf_1")
            self.term.render_reset()
            self._render()
            return (new_rows, new_cols)
        self.canvas.delete("buf_0")
        self.canvas.delete("buf_1")
        self.term.render_reset()
        self._render()
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
                encoding=None,  # binary mode — we handle raw bytes
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
                        self._on_data(data if isinstance(data, bytes) else data.encode("utf-8", errors="replace"))
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
            self._process.stdin.write(data if isinstance(data, bytes) else data.encode("utf-8"))
            # Ensure data is flushed to the transport immediately
            await self._process.stdin.drain()

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


xterm_256_color = _nbsterm.xterm_256_color


class ColorPicker256(tk.Toplevel):
    """256-color palette picker. Click a swatch to select."""

    def __init__(self, parent, title="Pick a Color", initial=None, callback=None):
        super().__init__(parent)
        self.title(title)
        self.transient(parent)
        self.grab_set()
        self._callback = callback
        self._selected = initial or "#ffffff"
        self.resizable(False, False)

        SWATCH = 18  # px per color swatch
        PAD = 2

        main = tk.Frame(self, bg="#2a2a2a", padx=10, pady=10)
        main.pack(fill=tk.BOTH, expand=True)

        # Preview bar
        preview_frame = tk.Frame(main, bg="#2a2a2a")
        preview_frame.pack(fill=tk.X, pady=(0, 8))
        tk.Label(preview_frame, text="Selected:", fg="#cccccc", bg="#2a2a2a",
                font=("", 10)).pack(side=tk.LEFT)
        self._preview = tk.Label(preview_frame, text="  ", bg=self._selected,
                                 width=8, relief=tk.SUNKEN)
        self._preview.pack(side=tk.LEFT, padx=5)
        self._hex_label = tk.Label(preview_frame, text=self._selected,
                                   fg="#cccccc", bg="#2a2a2a", font=("", 10))
        self._hex_label.pack(side=tk.LEFT)

        # 16 standard colors (2 rows of 8)
        tk.Label(main, text="Standard", fg="#888888", bg="#2a2a2a",
                font=("", 9)).pack(anchor=tk.W)
        std_frame = tk.Frame(main, bg="#2a2a2a")
        std_frame.pack(pady=(0, 6))
        for i in range(16):
            color = xterm_256_color(i)
            row, col = divmod(i, 8)
            swatch = tk.Frame(std_frame, width=SWATCH, height=SWATCH,
                             bg=color, highlightthickness=1,
                             highlightbackground="#555555")
            swatch.grid(row=row, column=col, padx=PAD, pady=PAD)
            swatch.bind("<Button-1>", lambda e, c=color: self._pick(c))

        # 216 color cube (6 blocks of 6x6)
        tk.Label(main, text="Color Cube", fg="#888888", bg="#2a2a2a",
                font=("", 9)).pack(anchor=tk.W)
        cube_frame = tk.Frame(main, bg="#2a2a2a")
        cube_frame.pack(pady=(0, 6))
        for i in range(216):
            color = xterm_256_color(16 + i)
            # Layout: 6 blocks horizontally, each 6x6
            block = i // 36
            within = i % 36
            row = within // 6
            col = block * 6 + within % 6
            swatch = tk.Frame(cube_frame, width=SWATCH, height=SWATCH,
                             bg=color, highlightthickness=0)
            swatch.grid(row=row, column=col, padx=0, pady=0)
            swatch.bind("<Button-1>", lambda e, c=color: self._pick(c))

        # 24 grayscale ramp
        tk.Label(main, text="Grayscale", fg="#888888", bg="#2a2a2a",
                font=("", 9)).pack(anchor=tk.W)
        gray_frame = tk.Frame(main, bg="#2a2a2a")
        gray_frame.pack(pady=(0, 6))
        for i in range(24):
            color = xterm_256_color(232 + i)
            swatch = tk.Frame(gray_frame, width=SWATCH, height=SWATCH,
                             bg=color, highlightthickness=0)
            swatch.grid(row=0, column=i, padx=0, pady=0)
            swatch.bind("<Button-1>", lambda e, c=color: self._pick(c))

        # Custom color + OK / Cancel
        btn_frame = tk.Frame(main, bg="#2a2a2a")
        btn_frame.pack(pady=(8, 0))
        tk.Button(btn_frame, text="Custom...", command=self._custom_color,
                  width=8).pack(side=tk.LEFT, padx=5)
        tk.Button(btn_frame, text="OK", command=self._ok, width=8).pack(
            side=tk.LEFT, padx=5)
        tk.Button(btn_frame, text="Cancel", command=self.destroy, width=8).pack(
            side=tk.LEFT, padx=5)

    def _custom_color(self):
        """Open Tk's built-in color chooser for full 24-bit sRGB selection."""
        result = colorchooser.askcolor(
            initialcolor=self._selected, title="Custom Color", parent=self)
        if result and result[1]:
            self._pick(result[1])

    def _pick(self, color):
        self._selected = color
        self._preview.configure(bg=color)
        self._hex_label.configure(text=color)

    def _ok(self):
        if self._callback:
            self._callback(self._selected)
        self.destroy()


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
        # Show all system fonts sorted — Combobox provides scrollable dropdown
        all_fonts = sorted(set(tkfont.families()))
        from tkinter import ttk
        family_combo = ttk.Combobox(self, textvariable=self._font_family,
                                     values=all_fonts, width=30, state="readonly")
        family_combo.grid(row=1, column=1, sticky="w", padx=10, pady=2)

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
                               "Block", "Underline", "Bar")
        styles.grid(row=4, column=1, sticky="w", padx=10, pady=2)

        self._cursor_blink = tk.BooleanVar(value=config.cursor.blink)
        tk.Checkbutton(self, text="Blink", variable=self._cursor_blink).grid(
            row=5, column=1, sticky="w", padx=10, pady=2)

        tk.Label(self, text="Color:").grid(row=6, column=0, sticky="e", padx=10)
        self._cursor_color = config.cursor.color or ""
        cc_frame = tk.Frame(self)
        cc_frame.grid(row=6, column=1, sticky="w", padx=10, pady=2)
        self._cc_swatch = tk.Label(cc_frame, text="  ",
                                   bg=config.cursor.color if config.cursor.color else config.fg,
                                   width=4, relief=tk.SUNKEN)
        self._cc_swatch.pack(side=tk.LEFT)
        tk.Button(cc_frame, text="Pick...",
                  command=self._pick_cursor_color).pack(side=tk.LEFT, padx=5)
        tk.Button(cc_frame, text="Default",
                  command=self._reset_cursor_color).pack(side=tk.LEFT)

        # Color section
        tk.Label(self, text="Color", font=("", 12, "bold")).grid(
            row=7, column=0, columnspan=2, sticky="w", padx=10, pady=(10, 5))

        tk.Label(self, text="Foreground:").grid(row=8, column=0, sticky="e", padx=10)
        self._fg_color = config.fg
        fg_frame = tk.Frame(self)
        fg_frame.grid(row=8, column=1, sticky="w", padx=10, pady=2)
        self._fg_swatch = tk.Label(fg_frame, text="  ", bg=config.fg,
                                   width=4, relief=tk.SUNKEN)
        self._fg_swatch.pack(side=tk.LEFT)
        tk.Button(fg_frame, text="Pick...",
                  command=lambda: self._open_picker("fg")).pack(side=tk.LEFT, padx=5)

        tk.Label(self, text="Background:").grid(row=9, column=0, sticky="e", padx=10)
        self._bg_color = config.bg
        bg_frame = tk.Frame(self)
        bg_frame.grid(row=9, column=1, sticky="w", padx=10, pady=2)
        self._bg_swatch = tk.Label(bg_frame, text="  ", bg=config.bg,
                                   width=4, relief=tk.SUNKEN)
        self._bg_swatch.pack(side=tk.LEFT)
        tk.Button(bg_frame, text="Pick...",
                  command=lambda: self._open_picker("bg")).pack(side=tk.LEFT, padx=5)

        tk.Label(self, text="Gamma:").grid(row=10, column=0, sticky="e", padx=10)
        self._gamma = tk.DoubleVar(value=config.gamma)
        tk.Scale(self, from_=0.5, to=2.0, resolution=0.05,
                 orient=tk.HORIZONTAL, variable=self._gamma, length=150).grid(
            row=10, column=1, padx=10, pady=2)

        # Performance section
        tk.Label(self, text="Performance", font=("", 12, "bold")).grid(
            row=11, column=0, columnspan=2, sticky="w", padx=10, pady=(10, 5))

        tk.Label(self, text="Refresh (Hz):").grid(row=12, column=0, sticky="e", padx=10)
        self._refresh_hz = tk.IntVar(value=config.refresh_hz)
        tk.Scale(self, from_=10, to=120, resolution=5,
                 orient=tk.HORIZONTAL, variable=self._refresh_hz, length=150).grid(
            row=12, column=1, padx=10, pady=2)

        # Buttons
        btn_frame = tk.Frame(self)
        btn_frame.grid(row=13, column=0, columnspan=2, pady=10)
        tk.Button(btn_frame, text="Save", command=self._save).pack(side=tk.LEFT, padx=5)
        tk.Button(btn_frame, text="Cancel", command=self.destroy).pack(side=tk.LEFT, padx=5)

    def _check_monospace(self):
        """Check if selected font is monospace and warn if not."""
        family = self._font_family.get()
        size = self._font_size.get()
        test_font = tkfont.Font(family=family, size=size)
        test_chars = "MWil@_"
        widths = {test_font.measure(c * 10) for c in test_chars}
        if len(widths) > 1:
            from tkinter import messagebox
            messagebox.showwarning(
                "Variable Width Font",
                f"'{family}' is not a monospace font.\n"
                "Text may not align correctly in the terminal.\n\n"
                "You can continue, but monospace fonts like "
                "Menlo, Monaco, or Courier are recommended.",
                parent=self)

    def _pick_cursor_color(self):
        """Open color picker for cursor color."""
        ColorPicker256(self, title="Cursor Color",
                       initial=self._cursor_color or self._config.fg,
                       callback=self._set_cursor_color)

    def _set_cursor_color(self, color):
        self._cursor_color = color
        self._cc_swatch.configure(bg=color)

    def _reset_cursor_color(self):
        self._cursor_color = ""
        self._cc_swatch.configure(bg=self._config.fg)

    def _open_picker(self, which):
        """Open the 256-color picker for fg or bg."""
        initial = self._fg_color if which == "fg" else self._bg_color
        title = "Foreground Color" if which == "fg" else "Background Color"

        def on_pick(color):
            if which == "fg":
                self._fg_color = color
                self._fg_swatch.configure(bg=color)
            else:
                self._bg_color = color
                self._bg_swatch.configure(bg=color)

        ColorPicker256(self, title=title, initial=initial, callback=on_pick)

    def _save(self):
        # Warn if font is not monospace
        self._check_monospace()
        self._config.font.family = self._font_family.get()
        self._config.font.size = self._font_size.get()
        self._config.cursor.style = self._cursor_style.get()
        self._config.cursor.blink = self._cursor_blink.get()
        self._config.cursor.color = self._cursor_color
        self._config.fg = self._fg_color
        self._config.bg = self._bg_color
        self._config.gamma = self._gamma.get()
        self._config.refresh_hz = self._refresh_hz.get()
        save_config(self._config)
        if self._on_save:
            self._on_save(self._config)
        self.destroy()


class TabSession:
    """One tab: a TerminalWidget + SSHTransport pair. Owns a tk.Canvas
    directly (no wrapper frame). Caller (TerminalApp._select_tab) swaps
    visibility via canvas.pack/pack_forget on the root."""

    def __init__(self, parent, host, port, username, config, app):
        self.app = app
        self.host = host
        self.label = host.split("@")[-1].split(".")[0] if host else "local"

        if config:
            self.widget = TerminalWidget(
                parent,
                rows=config.rows, cols=config.cols,
                font_family=config.font.family, font_size=config.font.size,
                cursor_style=config.cursor.style, cursor_blink=config.cursor.blink,
                cursor_color=config.cursor.color or None,
                gamma=config.gamma, fg=config.fg, bg=config.bg,
                refresh_hz=config.refresh_hz,
            )
        else:
            self.widget = TerminalWidget(parent)
        self.canvas = self.widget.canvas

        self.ssh = SSHTransport(host, port, username)
        self.widget.set_write_callback(self.ssh.write)
        self.ssh.set_data_callback(self._on_data)
        self.ssh.set_close_callback(self._on_close)
        self.ssh.set_interaction_handler(TkInteractionHandler(app.root))
        self.ssh.set_error_callback(self._on_error)

        # <Configure> on the canvas itself: event.width/height = canvas size.
        # Cross-platform (Linux/Mac/Windows pack semantics deliver Configure
        # events on geometry change uniformly).
        self.canvas.bind("<Configure>", self._on_configure)

    def start(self):
        self.ssh.start(self.widget.rows, self.widget.cols)

    def stop(self):
        self.ssh.stop()

    def _on_data(self, data):
        self.app.root.after(0, self.widget.feed, data)

    def _on_close(self):
        self.app.root.after(0, self._handle_disconnect)

    def _handle_disconnect(self):
        self.widget.feed(b"\r\n[Connection closed]\r\n")

    def _on_error(self, error_msg):
        self.app.root.after(0, self.widget.feed,
                            f"\r\n[SSH error: {error_msg}]\r\n".encode())

    def _on_configure(self, event):
        result = self.widget.handle_resize(event)
        if result:
            rows, cols = result
            self.ssh.resize(rows, cols)


class TerminalApp:
    """Main application with tabbed terminal sessions."""

    # Tab strip visual styling. _TAB_BORDER_ACTIVE is a Frame wrapper
    # accent so the selected tab is distinguished by border + bg, not
    # just text color (alexie 2026-04-28 17:05:45: white-on-light-grey
    # unreadable on Mac). Inactive wrapper takes the strip's own bg,
    # making the border invisible.
    _TAB_BG_INACTIVE = "#2a2a2a"
    _TAB_BG_ACTIVE = "#404040"
    _TAB_FG_INACTIVE = "#888888"
    _TAB_FG_ACTIVE = "#ffffff"
    _TAB_BORDER_ACTIVE = "#888888"

    def __init__(self, host, port=None, username=None, config=None):
        self.root = tk.Tk()
        self.root.title(f"nbs-term — {host}")
        self._config = config or TerminalConfig()
        self._host = host
        self._port = port
        self._username = username
        self.tabs = []  # list of TabSession
        self._tab_buttons = []  # parallel to self.tabs
        self._active_tab_idx = -1

        # Tab strip — single tk.Frame for tab buttons, packed at TOP when
        # 2+ tabs exist (a45403a auto-hide on single tab). Active TabSession's
        # canvas is packed directly in root after the strip (TerminalApp swaps
        # canvases on tab change). No nested Frames, no manual centering math
        # — alexie 2026-04-28 06:59:16 architectural reset, theologian spec
        # 07:00:17.
        self.tab_strip = tk.Frame(self.root,
                                  bg=gamma_correct(self._config.bg, self._config.gamma),
                                  highlightthickness=0, borderwidth=0)

        # Create first tab
        self._add_tab(host, port, username)

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

        # Bind keyboard to active tab
        self.root.bind("<Key>", self._on_key)

        # Copy/Paste and Preferences shortcuts
        if sys.platform == "darwin":
            self.root.bind("<Command-c>", self._on_copy)
            self.root.bind("<Command-v>", self._on_paste)
            self.root.bind("<Command-comma>", self._on_preferences)
            self.root.bind("<Command-t>", self._on_new_tab)
            self.root.bind("<Command-w>", self._on_close_tab)
        else:
            self.root.bind("<Control-Shift-C>", self._on_copy)
            self.root.bind("<Control-Shift-V>", self._on_paste)
            self.root.bind("<Control-comma>", self._on_preferences)
            self.root.bind("<Control-Shift-T>", self._on_new_tab)
            self.root.bind("<Control-Shift-W>", self._on_close_tab)

        # Tab switching
        self.root.bind("<Control-Tab>", self._on_next_tab)
        self.root.bind("<Control-Shift-Tab>", self._on_prev_tab)

        # F11 fullscreen toggle (all platforms)
        self.root.bind("<F11>", self._toggle_fullscreen)

        # Handle window close
        self.root.protocol("WM_DELETE_WINDOW", self._on_close)

    @property
    def _active_tab(self):
        """Get the currently active TabSession."""
        if 0 <= self._active_tab_idx < len(self.tabs):
            return self.tabs[self._active_tab_idx]
        return None

    @property
    def widget(self):
        """Active tab's widget (backward compatibility)."""
        tab = self._active_tab
        return tab.widget if tab else None

    def _add_tab(self, host, port=None, username=None):
        """Create a new tab with an SSH session. The TabSession's canvas is
        a child of root; visibility managed via pack/pack_forget in
        _select_tab."""
        tab = TabSession(self.root, host, port, username,
                         self._config, self)
        self.tabs.append(tab)
        # Tab is a tk.Frame wrapper around a tk.Label (NOT tk.Button).
        # On macOS aqua tk.Button paints native NSButton chrome — bg/
        # padding ignored, native min-height too tall, native bg shows
        # through (alexie 2026-04-28 17:05:45). tk.Label respects bg/fg
        # and has no class binding for <Key-space>/<Return>, so the
        # focus-stealing class also disappears (theologian 17:55:42).
        # Wrapper bg = active border accent when selected, strip bg
        # (invisible) otherwise. <Button-1> click bound in
        # _refresh_tab_strip so indices stay correct across tab close.
        wrapper = tk.Frame(self.tab_strip, bg=self.tab_strip.cget("bg"))
        label = tk.Label(
            wrapper, text=tab.label,
            bg=self._TAB_BG_INACTIVE, fg=self._TAB_FG_INACTIVE,
            padx=12, pady=1,
        )
        label.pack(padx=2, pady=2)
        wrapper._label = label
        self._tab_buttons.append(wrapper)
        self._select_tab(len(self.tabs) - 1)
        return tab

    def _select_tab(self, idx):
        """Make tab `idx` the visible/active tab."""
        if not (0 <= idx < len(self.tabs)):
            return
        if 0 <= self._active_tab_idx < len(self.tabs):
            self.tabs[self._active_tab_idx].canvas.pack_forget()
        self._active_tab_idx = idx
        self.tabs[idx].canvas.pack(side=tk.TOP, fill=tk.BOTH, expand=True)
        # Mac click leaves focus on the clicked tab button; Tk's Button
        # class binds <Key-space>/<Return> to invoke. Without this,
        # typing space in the text area re-fires the focused button's
        # command (visible flicker / re-pack) before reaching root's
        # <Key> handler. takefocus=0 alone removes Tab-traversal but not
        # Mac click-focus — explicit focus_set restores canvas focus.
        self.tabs[idx].canvas.focus_set()
        self._refresh_tab_strip()
        self.root.title(f"nbs-term — {self.tabs[idx].host}")
        # Defer render so Tk completes layout first; otherwise canvas
        # winfo_width() returns 1 (pre-layout) and origin computes wrong.
        self.root.after_idle(self.tabs[idx].widget._render)

    def _refresh_tab_strip(self):
        """Repack tab buttons + auto-hide the strip on single tab. Rebinds
        button commands to current indices (indices shift on close)."""
        active_canvas = self.tabs[self._active_tab_idx].canvas \
            if 0 <= self._active_tab_idx < len(self.tabs) else None
        if len(self.tabs) <= 1:
            self.tab_strip.pack_forget()
        else:
            kwargs = {"side": tk.TOP, "fill": tk.X}
            if active_canvas is not None:
                kwargs["before"] = active_canvas
            self.tab_strip.pack(**kwargs)
        for wrapper in self._tab_buttons:
            wrapper.pack_forget()
        strip_bg = self.tab_strip.cget("bg")
        for i, wrapper in enumerate(self._tab_buttons):
            label = wrapper._label
            label.bind("<Button-1>", lambda e, x=i: self._select_tab(x))
            if i == self._active_tab_idx:
                wrapper.config(bg=self._TAB_BORDER_ACTIVE)
                label.config(bg=self._TAB_BG_ACTIVE, fg=self._TAB_FG_ACTIVE)
            else:
                wrapper.config(bg=strip_bg)
                label.config(bg=self._TAB_BG_INACTIVE, fg=self._TAB_FG_INACTIVE)
            wrapper.pack(side=tk.LEFT)

    def _on_key(self, event):
        """Route keyboard to active tab."""
        tab = self._active_tab
        if tab:
            tab.widget.handle_key(event)

    def _on_new_tab(self, event=None):
        """Open a new tab (same host for now)."""
        tab = self._add_tab(self._host, self._port, self._username)
        tab.start()
        return "break"

    def _on_close_tab(self, event=None):
        """Close the current tab."""
        if not (0 <= self._active_tab_idx < len(self.tabs)):
            return "break"
        if len(self.tabs) > 1:
            idx = self._active_tab_idx
            tab = self.tabs.pop(idx)
            tab.stop()
            tab.canvas.destroy()
            btn = self._tab_buttons.pop(idx)
            btn.destroy()
            new_idx = min(idx, len(self.tabs) - 1)
            # Force _select_tab to repack (skip the pack_forget on the old idx
            # which no longer exists).
            self._active_tab_idx = -1
            self._select_tab(new_idx)
        elif len(self.tabs) == 1:
            # Last tab — close window
            self._on_close()
        return "break"

    def _on_next_tab(self, event=None):
        """Switch to next tab."""
        if len(self.tabs) > 1:
            self._select_tab((self._active_tab_idx + 1) % len(self.tabs))
        return "break"

    def _on_prev_tab(self, event=None):
        """Switch to previous tab."""
        if len(self.tabs) > 1:
            self._select_tab((self._active_tab_idx - 1) % len(self.tabs))
        return "break"

    def _on_copy(self, event=None):
        """Copy selected text to clipboard."""
        tab = self._active_tab
        if tab:
            tab.widget.copy_selection()
        return "break"

    def _on_paste(self, event=None):
        """Paste clipboard text into the terminal."""
        tab = self._active_tab
        if not tab:
            return "break"
        try:
            text = self.root.clipboard_get()
        except tk.TclError:
            return "break"
        if text and tab.ssh._running:
            data = tab.widget.term.encode_paste(text.encode("utf-8"))
            tab.ssh.write(data)
        return "break"

    def _on_preferences(self, event=None):
        """Open the preferences dialog."""
        PreferencesDialog(self.root, self._config, on_save=self._apply_config)
        return "break"

    def _apply_config(self, config):
        """Apply config changes live to all tabs."""
        for tab in self.tabs:
            w = tab.widget
            w.font.configure(family=config.font.family, size=config.font.size)
            for key, f in w._font_cache.items():
                f.configure(family=config.font.family, size=config.font.size)
            w.char_width = w.font.measure("M")
            w.char_height = w.font.metrics("linespace")
            w._fg = config.fg
            w._bg = config.bg
            w._gamma = config.gamma
            w._bg_render = gamma_correct(w._bg, w._gamma)
            w.canvas.configure(bg=w._bg_render)
            w._refresh_ms = max(1, 1000 // config.refresh_hz)
            w._cursor_style = config.cursor.style
            w._cursor_blink = config.cursor.blink
            w._cursor_color = config.cursor.color or None
            canvas_w = w.canvas.winfo_width()
            canvas_h = w.canvas.winfo_height()
            new_cols = max(1, (canvas_w - 2 * PADDING) // w.char_width)
            new_rows = max(1, (canvas_h - 2 * PADDING) // w.char_height)
            if new_cols != w.cols or new_rows != w.rows:
                w.cols = new_cols
                w.rows = new_rows
                w.term.resize(new_rows, new_cols)
                w.canvas.delete("buf_0")
                w.canvas.delete("buf_1")
                w.term.render_reset()
                tab.ssh.resize(new_rows, new_cols)
            w._render()

    def _toggle_fullscreen(self, event=None):
        """Toggle fullscreen mode (F11)."""
        current = self.root.attributes("-fullscreen")
        self.root.attributes("-fullscreen", not current)

    def _on_close(self):
        """Handle window close — stop all tabs."""
        for tab in self.tabs:
            tab.stop()
        self.root.destroy()

    def run(self):
        """Start the application."""
        for tab in self.tabs:
            tab.start()
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
    parser.add_argument("--refresh-hz", type=int, dest="refresh_hz",
                        help="refresh rate in Hz (25-120, overrides config)")
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
