# tmux Integration: Automatic Tab Mapping + Scrollback

## Problem

The primary use case for nbs-term is connecting to a remote server and using tmux for session persistence and multiplexing. Currently, tmux runs inside a single nbs-term window — the user manages tmux windows via tmux keybindings (Ctrl-B c, Ctrl-B n, Ctrl-B p) and scrolls via tmux's copy mode (Ctrl-B [). This works but is clunky: tmux windows are invisible to the native UI, and scrolling requires modal interaction instead of a scrollbar.

**Terminal goal:** tmux windows automatically appear as native tabs in nbs-term. Creating a tmux window creates a tab. Closing a tmux window closes the tab. Each tab has native scrollbar-backed scrollback. The user gets a persistent, multiplexed terminal experience without learning tmux keybindings.

## Architecture: tmux Control Mode (`tmux -CC`)

tmux provides a **control mode** (`tmux -CC` or `tmux -CC attach`) that replaces the visual terminal UI with a structured text protocol. Instead of drawing to a terminal, tmux emits machine-readable events and accepts commands via stdin.

### Why Control Mode

| Alternative | Pros | Cons |
|---|---|---|
| **tmux -CC (control mode)** | No server helper needed. Real-time events. iTerm2 proves it works. | Protocol parsing complexity. |
| **Server-side helper + OSC sequences** | Simple parsing in nbs-term. | Requires helper installation on every server. State drift. |
| **Polling `tmux list-windows`** | Simplest implementation. | Latency. Extra SSH round-trips. No real-time. |

**Decision:** Control mode. It is the principled approach — tmux already has this protocol for exactly this purpose. No server-side installation required.

### Control Mode Protocol (Summary)

When running `tmux -CC attach -t <session>`, tmux emits:

| Event | Format | Meaning |
|---|---|---|
| Window created | `%window-add @<id>` | New window appeared |
| Window closed | `%window-close @<id>` | Window was destroyed |
| Window renamed | `%window-renamed @<id> <name>` | Window title changed |
| Output | `%output %<pane-id> <data>` | Terminal output from a pane |
| Layout changed | `%layout-change @<id> <layout>` | Window layout/size changed |
| Session changed | `%session-changed $<id> <name>` | Attached session changed |
| Begin/End/Error | `%begin`, `%end`, `%error` | Command response delimiters |

Commands are sent as plain text lines to tmux's stdin (e.g. `new-window`, `send-keys`, `capture-pane -p`).

### Falsifier

If `%output` events do NOT include pane/window identifiers sufficient to route output to the correct tab, control mode cannot support per-tab rendering. **Test:** Run `tmux -CC attach`, create two windows, type in each — verify output events carry distinguishing IDs.

## Component Architecture

```
┌─────────────────────────────────────────────────┐
│                  nbs-term (Tk)                   │
│  ┌──────────┬──────────┬──────────┐             │
│  │  Tab 0   │  Tab 1   │  Tab 2   │  Tab Bar    │
│  ├──────────┴──────────┴──────────┤             │
│  │        Active TerminalWidget    │             │
│  │   (Canvas + ScreenBuffer + C)   │  Scrollbar  │
│  └─────────────────────────────────┘             │
│                    │                              │
│            TmuxController                         │
│         (protocol parser + state)                 │
│                    │                              │
│              SSHTransport                         │
│          (nbs-ssh, single conn)                   │
└─────────────────────────────────────────────────┘
                     │ SSH
                     ▼
            ┌────────────────┐
            │  Remote host   │
            │  tmux -CC      │
            │  attach -t sess│
            └────────────────┘
```

### New Components

1. **TmuxController** — Parses control mode protocol. Maintains window→tab mapping. Routes `%output` to correct TerminalWidget. Sends commands (new-window, send-keys) to tmux stdin.

2. **TabBar** — Tk widget (ttk.Notebook or custom) displaying one tab per tmux window. Handles tab switching, close buttons, reordering.

3. **Per-tab TerminalWidget** — Each tab owns its own `_nbsterm.Terminal` C instance (ScreenBuffer, RenderState, selection state). Only the active tab renders to canvas.

4. **ScrollbackManager** — Per-tab scrollback buffer. Integrates with tmux's `capture-pane -p -S -<lines>` for history beyond what the C ScreenBuffer holds. Connected to a Tk Scrollbar widget.

### Modified Components

1. **TerminalApp** — Gains a TmuxController and TabBar. Connection mode: if target is a tmux session, use control mode; otherwise, use direct shell (existing behavior).

2. **SSHTransport** — Unchanged. The SSH channel carries control mode protocol instead of raw PTY data.

## Phase Plan

### Phase 1: Scrollback + Mouse Wheel (No tmux)

**Goal:** Add scrollback to the existing single-terminal mode.

**Scope:**
- Mouse wheel events scroll through the ScreenBuffer's scrollback region
- Thin Tk Scrollbar widget (auto-hiding or always-visible, configurable)
- Scroll position tracked in C (ScreenBuffer scroll offset)
- render_frame renders from scroll offset instead of always from cursor

**Success criteria:** User can scroll up through terminal history with mouse wheel/trackpad. Scrollbar reflects position. New output auto-scrolls to bottom.

**Effort:** ~1 session. Self-contained, no tmux dependency.

### Phase 2: Tab UI (No tmux)

**Goal:** Add tab bar to nbs-term, supporting multiple independent terminal sessions.

**Scope:**
- TabBar widget (ttk.Notebook or custom drawn)
- Each tab creates a new TerminalWidget + SSHTransport
- Tab switching shows/hides terminal widgets
- Keyboard shortcuts: Ctrl-T (new tab), Ctrl-W (close tab), Ctrl-Tab (next tab)
- Only active tab's TerminalWidget renders (performance)

**Success criteria:** User can open multiple SSH sessions in tabs. Each tab is independent. Switching is instant.

**Effort:** ~1-2 sessions.

### Phase 3: tmux Control Mode Parser

**Goal:** Parse tmux's control mode protocol.

**Scope:**
- TmuxController class: line-oriented protocol parser
- Handle `%window-add`, `%window-close`, `%window-renamed`
- Handle `%output %<pane-id> <data>` — route to correct TerminalWidget
- Handle `%begin`/`%end`/`%error` for command responses
- Send commands: `new-window`, `kill-window`, `send-keys -t <pane> <keys>`

**Success criteria:** Connect to tmux -CC, see structured events parsed correctly. Can send a command and receive a response.

**Falsifier:** If %output events lack pane/window routing information, this phase blocks. Test first with manual `tmux -CC` session.

**Effort:** ~2 sessions.

### Phase 4: tmux ↔ Tab Integration

**Goal:** Wire TmuxController to TabBar. tmux windows become tabs automatically.

**Scope:**
- On connect: enumerate existing tmux windows → create tabs
- `%window-add` → create new tab + TerminalWidget
- `%window-close` → close tab
- `%window-renamed` → update tab title
- `%output` → feed to correct tab's TerminalWidget
- Tab input → `send-keys -t <pane>` command to tmux
- Tab close button → `kill-window -t <window>`
- Ctrl-B c in any tab → tmux creates window → new tab appears

**Success criteria:** End-to-end: connect to tmux session, existing windows appear as tabs, new tmux windows create tabs, closing tabs closes tmux windows.

**Effort:** ~1-2 sessions (depends on Phase 3 stability).

### Phase 5: tmux-Backed Scrollback

**Goal:** Per-tab scrollback using tmux's history buffer instead of (or in addition to) the local ScreenBuffer.

**Scope:**
- Scrollbar scroll-up triggers `capture-pane -p -S -<offset> -E -<offset+rows>` on the active pane
- Captured history rendered into the tab's TerminalWidget
- Seamless transition between local buffer (recent) and tmux history (older)
- Scroll position communicated to tmux so Ctrl-B [ is unnecessary

**Success criteria:** User scrolls up past local buffer → tmux history loads seamlessly. No Ctrl-B [ needed.

**Effort:** ~1-2 sessions.

### Phase 6: Polish + Edge Cases

**Goal:** Production-quality tmux integration.

**Scope:**
- Session selection UI (if multiple tmux sessions exist)
- Reconnection handling (SSH drops → reconnect → re-attach)
- Window resize → notify tmux (`refresh-client -C <cols>,<rows>`)
- Pane splits (tmux panes within a window) — defer or render as sub-panels
- Status line integration (tmux status bar info in nbs-term UI)
- Fallback: if no tmux on server, use direct shell (existing behavior)

**Success criteria:** Robust enough for daily use. Handles disconnection, resize, and missing tmux gracefully.

**Effort:** ~2-3 sessions.

## Invariants

| Invariant | Enforcement |
|---|---|
| Tab lifecycle mirrors tmux window lifecycle | TmuxController creates/destroys tabs only on %window-add/%window-close |
| Each tab owns exactly one TerminalWidget | TabBar enforces 1:1 mapping |
| Only the active tab renders to canvas | Tab switch hides/shows widgets |
| C extension called only from main thread | Existing invariant — maintained |
| Scrollback buffer is per-tab | Each TerminalWidget has its own ScreenBuffer |
| No server-side installation required | Control mode is built into tmux |

## Risks

| Risk | Impact | Mitigation |
|---|---|---|
| tmux -CC protocol underdocumented | Parser bugs, missed events | Study iTerm2 source as reference implementation |
| Older tmux versions lack control mode features | Incompatibility | Require tmux ≥ 3.2 (control mode stable) |
| Per-tab TerminalWidget memory usage | High memory for many tabs | Lazy initialization — only create C terminal for active tabs, background tabs store raw output |
| SSH disconnection during control mode | Orphaned tabs, lost state | Reconnect + re-attach, reconcile tabs with tmux state |
| Pane splits within windows | Complex sub-tab rendering | Phase 6 — initially show only the active pane per window |

## Dependencies

- **nbs-ssh:** Unchanged — carries control mode protocol over existing SSH channel
- **_nbsterm C extension:** Unchanged — each tab creates a new Terminal instance
- **Tk:** ttk.Notebook for tabs, Scrollbar widget for scrollback
- **tmux ≥ 3.2:** Required on the remote server for control mode
