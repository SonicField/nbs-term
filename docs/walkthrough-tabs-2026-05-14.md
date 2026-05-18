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

**What changed.** F11 toggles the window between normal size and
fullscreen on every platform. On Mac, a File menu now appears in the
menu bar with a "Close Tab" item showing ⌘W. The menu install is what
makes Cmd+W close just the current tab on Mac instead of killing the
whole program — a longstanding trap from the legacy version: without
the explicit menu, the OS picks up Cmd+W as "close window" which exits
everything.

**Test.**

1. Press F11 — the window should fill the screen.
2. Press F11 again — the window returns to normal size.
3. On Mac, open p3_pty and press Cmd+T to create a second tab.
4. Press Cmd+W on the second tab. **This is the load-bearing test for
   the menu install fix.** Three possible outcomes:
   - **Pass:** only the second tab closes; the first stays open and
     the program keeps running.
   - **Fail (legacy trap):** the entire program exits — the OS picked
     up Cmd+W as "close window" and killed everything.
   - **Fail (no effect):** the program keeps running but neither tab
     closes — Cmd+W reached neither the menu nor the Tk bind. This is
     a different failure mode (accelerator-vs-bind ordering) and
     worth flagging separately.
5. With one tab left, press Cmd+W again on that last surviving tab.
   The window should close cleanly (process exits because there are no
   tabs left, not because the OS hijacked Cmd+W).
6. Look at the menu bar at the top of the screen: "File" menu visible,
   with "Close Tab ⌘W" inside.
7. With at least two tabs open, click File > Close Tab in the menu bar
   (don't use the keyboard shortcut). The active tab should close. If
   step 4 passed but this step doesn't close a tab, the keyboard
   shortcut works but the menu's command isn't wired — also worth
   flagging separately.

**Pass signal.** F11 toggles fullscreen on every platform. On Mac: File
menu visible with Close Tab item; Cmd+W closes just the active tab (not
the whole program); closing the last tab exits cleanly.

**Flag if.** F11 does nothing OR the window doesn't visibly resize. On
Mac: no File menu in the menu bar. Cmd+W kills the entire process
despite the menu install — this would mean the menu+bind pairing isn't
taking, which is the trap the legacy version had to fix specifically.

---

## Section 4 — Shell-exit in one tab no longer kills the app

**What changed.** Typing `exit` (or Ctrl+D) in a tab's shell used to kill
the whole program even when other tabs were still open — the PTY EOF
signal short-circuited straight to the app's main-loop exit, bypassing
the multi-tab close logic. Now PTY EOF goes through the same close-tab
path as Cmd+W and the × glyph: the tab that received the EOF closes,
focus moves to the next active tab, and the app only exits when the
last tab is gone.

**Test.**

1. Open p3_pty. Press Cmd+T so two tabs exist (tab strip visible at
   top, tab 2 is the active one).
2. In the active tab (tab 2), type `exit` and press Enter.
   - **Pass:** tab 2 closes, tab 1 becomes active, tab strip auto-hides
     (only one tab left), the program is still running.
   - **Fail:** the entire program exits — the EOF still kills the app
     instead of routing through close-tab.
3. With one tab left, type `exit` again in that tab. The program should
   exit cleanly (no zombie shell, no spinning).
4. Discriminator from Section 3: this section is the `exit`/EOF path,
   not the Cmd+W path. If Cmd+W kills the app but `exit` only closes
   the tab, that's the Mac menu-install trap (Section 3); if both kill
   the app, both paths regressed; if `exit` kills the app but Cmd+W
   only closes the tab, this section's fix didn't take.

**Pass signal.** `exit` in a multi-tab session closes just that tab and
the next tab activates; `exit` on the last tab closes the program.

**Flag if.** `exit` on any non-last tab kills the whole program.
Closing the EOF'd tab leaves a zombie tab strip entry. Focus doesn't
move to the next tab after the EOF'd tab closes.

---

## Reporting results

Please flag pass/fail per section. If something fails, the specific
behaviour you saw plus what you expected helps narrow the next fix.
Sections are independent; a failure in any one section does not
invalidate the others.
