# Walkthrough — Tabs Support 2026-05-14

This document covers the tabs support work — three commits split into
sections you can smoke independently. Sections are added as each commit
ships; come back after each new section appears for the next thing to
test.

## Install

Run this once. It rebuilds from the latest source:

```
curl -fsSL https://raw.githubusercontent.com/SonicField/nbs-term/pure-phc-master/scripts/mac-setup-phc.sh | bash
```

Then launch:

```
~/nbs-term-phc/build/p3_pty
```

---

## Section 1 — Tab support foundation (no UI yet)

**What changed.** Internal refactor. The program now keeps per-tab state
ready for multiple tabs, but no new buttons or shortcuts yet — those
land in the next section. Single-tab usage is unchanged.

**Test.** Open p3_pty the usual way. Type a command. Close the window.
Everything should work exactly as before.

**Pass signal.** Single-tab usage feels identical to the previous
version.

**Flag if.** Anything works differently than before — text doesn't
appear, window closes unexpectedly, keys do the wrong thing, startup
fails. Anything except "identical to before" is a Section 1 regression.

---

## Section 2 — New tab + close tab + switch tabs

**What changed.** You can now have multiple shells in one window. Cmd+T
opens a new tab; Cmd+W closes the current tab; Cmd+1 through Cmd+9 jump
directly to that tab number; Ctrl+Tab and Ctrl+Shift+Tab cycle
forward/backward through tabs. A tab strip appears at the top of the
window when you have two or more tabs (it auto-hides for single-tab
sessions). Click a tab's name to switch; click the small "x" next to
the name to close that tab.

**Test.**

1. Open p3_pty. Press Cmd+T — second tab appears, tab strip becomes
   visible at the top, prompt shows in the active canvas.
2. Type something different in each tab to confirm they're separate
   shells.
3. Cmd+1 returns to first tab; Cmd+2 returns to second.
4. Click "x" on the first tab — second tab becomes active, tab strip
   hides (only one tab left).
5. Cmd+W on the last tab closes the window cleanly (process exits, no
   zombie shell).

**Pass signal.** Multiple shells coexist; switching preserves each
tab's contents; closing the last tab closes the window cleanly.

**Flag if.** Cmd+T does nothing OR doesn't spawn a new shell. Cmd+W
kills the entire process instead of closing just the active tab (this
is the trap Section 3 addresses with the menu install fix). Tab strip
doesn't appear when you have two or more tabs OR doesn't hide when
you're back to one. Click on tab label doesn't switch. Switching loses
the contents of the previous tab.

**Note on close behaviour.** When you close an active tab, focus moves
to the immediate next tab (with wrap to the first if you closed the
rightmost). If you've used Mac Terminal or iTerm before, this matches
that convention.

---

## Section 3 — Fullscreen + Mac menu bar

*Pending — added after the fullscreen toggle and menu install ship.*

---

## Reporting results

Please flag pass/fail per section. If something fails, the specific
behaviour you saw plus what you expected helps narrow the next fix.
Sections are independent; a failure in Section 2 does not invalidate
your Section 1 result.
