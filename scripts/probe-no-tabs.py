#!/usr/bin/env python3
"""Bug C v3 widget-nesting probe.

Discriminator for: where in the widget tree does the lighter-slop perimeter
get painted on macOS aqua?

Per supervisor 2026-04-27 18:18:28 + pythia #71/#72. The post-6164ef5 chain
nests TerminalWidget four-deep (tab_area → tab_strip / tab_content →
TabSession.frame → TerminalWidget). This probe varies the nesting depth so
alexie can compare runs and isolate which depth introduces the slop.

Usage on Mac:
  source ~/nbsterm-venv/bin/activate
  python3 scripts/probe-no-tabs.py [--frames=N]

  N=0 (default): TerminalWidget directly in tk.Tk() — no tk.Frame at all.
  N=1: TerminalWidget in one tk.Frame in tk.Tk().
  N=2: TerminalWidget in tk.Frame in tk.Frame in tk.Tk().

Run all three and compare the perimeter slop across windows. Outcomes:
  - Slop on ALL three (incl. N=0): tk.Canvas widget bg paints aqua-tinted
    even with no tk.Frame in the chain — refutes the
    "tk.Frame is the painter" anchor; next iteration must target canvas-side.
  - Slop only on N>=1, clean on N=0: tk.Frame wrapper introduces it; the
    issue is the Frame, not depth or tab logic.
  - Slop only on N=2, clean on N=0 and N=1: nesting depth matters; aqua
    composites/tints across nested Frames.
  - Clean on all three: post-6164ef5 chain has something specific in tab_area
    / tab_strip / tab_content / TabSession.frame; the standalone widget
    architecture is fine.

This probe never starts SSH; it just feeds example text so the grid is
visible.
"""
import argparse
import sys
import tkinter as tk

# Allow running from repo root without install
sys.path.insert(0, ".")

from nbsterm import TerminalWidget, TerminalConfig


def build_parent(root, frames):
    """Return the parent widget for the TerminalWidget after wrapping the
    requested number of tk.Frame containers. Each Frame uses fill=BOTH,
    expand=True so canvas geometry mirrors what the real app does."""
    parent = root
    for _ in range(frames):
        wrapper = tk.Frame(parent)
        wrapper.pack(fill=tk.BOTH, expand=True)
        parent = wrapper
    return parent


def main():
    ap = argparse.ArgumentParser(description=__doc__,
                                 formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("--frames", type=int, default=0,
                    help="number of tk.Frame wrappers between tk.Tk() and "
                         "the TerminalWidget (default: 0)")
    args = ap.parse_args()

    if args.frames < 0:
        ap.error("--frames must be >= 0")

    config = TerminalConfig()
    root = tk.Tk()
    root.title(f"Bug C v3 probe (frames={args.frames})")
    root.geometry("800x500")
    root.configure(bg=config.bg)

    parent = build_parent(root, args.frames)
    if parent is not root:
        parent.configure(bg=config.bg)
    widget = TerminalWidget(
        parent,
        rows=config.rows, cols=config.cols,
        font_family=config.font.family, font_size=config.font.size,
        cursor_style=config.cursor.style, cursor_blink=config.cursor.blink,
        cursor_color=config.cursor.color or None,
        gamma=config.gamma, fg=config.fg, bg=config.bg,
        refresh_hz=config.refresh_hz,
    )

    if args.frames == 0:
        depth_line = "frames=0: TerminalWidget DIRECTLY in tk.Tk(). No tk.Frame."
    else:
        depth_line = (f"frames={args.frames}: TerminalWidget wrapped in "
                      f"{args.frames} tk.Frame layer(s).")
    sample_text = (
        f"\x1b[2J\x1b[H"
        f"=== Bug C v3 probe (frames={args.frames}) ===\r\n"
        f"\r\n"
        f"{depth_line}\r\n"
        f"\r\n"
        f"Look at the perimeter around this text:\r\n"
        f"  Lighter band visible? -> note 'slop at frames=N'.\r\n"
        f"  Clean dark, no band?  -> note 'no slop at frames=N'.\r\n"
        f"\r\n"
        f"Close window when done. Run again with a different --frames= value.\r\n"
    )
    widget.feed(sample_text.encode("utf-8"))

    root.mainloop()


if __name__ == "__main__":
    main()
