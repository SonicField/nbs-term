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

## Section 5 — Initial tab resizes when the tab strip appears

**What changed.** When you press Cmd+T to create a second tab, the tab
strip appears at the top and the canvas area below it shrinks by the
strip's height. Previously the original tab's shell didn't notice this
shrink until the next geometry event, so the first tab painted a stale
frame at the pre-strip dimensions (and the shell could think it had
more rows than it did until a resize fired). Now the geometry flush
happens synchronously when the strip is packed, so the `<Configure>`
event reaches the canvas (and the shell sees the new rows/cols via
TIOCSWINSZ) before the first post-create paint.

**Test.**

1. Open p3_pty (single tab). Type `stty size` and note the row/col count
   it prints — call this `rows0 cols0`.
2. Press Cmd+T. The tab strip appears at the top.
3. In the new tab, type `stty size` again. The row count should now be
   `rows0 - 1` (one less, because the strip ate a row). The col count
   should still be `cols0`.
4. Switch back to tab 1 (Cmd+1). Type `stty size`. It should also
   report `rows0 - 1` (the resize reached the first tab's shell, not
   just the new one).
5. Run a tall command in tab 1 (e.g. `seq 1 100`) — the bottom row of
   output should sit flush with the bottom of the canvas, not be
   clipped behind where the strip used to be.

**Pass signal.** Both tabs see `rows0 - 1` after the strip appears; no
clipped output at the canvas bottom in tab 1.

**Flag if.** `stty size` in either tab still reports the pre-strip row
count after Cmd+T — means the canvas `<Configure>` didn't reach
`pty_resize`, which would be an architectural problem, not the
ordering problem this fix targets. If the dims update only after you
focus or resize the window, the geometry flush isn't happening
synchronously.

---

## Section 6 — Background tabs detect their own shell exit

**What changed.** Each tab now has its own PTY file handler that
ingests data and detects shell-exit independently. Before this, only
the active tab's PTY was actively watched — a shell exiting in a
background tab was either silently ignored or caused the wrong tab
to close. Now if you've left a shell running in a background tab and
that shell exits, the background tab itself closes (tab strip entry
disappears), the active tab is undisturbed, and the app stays alive.

**Test.**

1. Open p3_pty. Press Cmd+T so two tabs exist.
2. In tab 2 (the active one), type `sleep 5 && exit` and press Enter.
3. Press Cmd+1 to switch back to tab 1 immediately. Tab 1 is now
   active; tab 2's shell is still running its 5-second sleep in the
   background.
4. In tab 1, type `echo tab1-still-here`. The prompt accepts input
   and echoes the string — proves tab 1 is alive and the active
   handler still works.
5. Wait until at least 5 seconds have passed since step 2 (tab 2's
   shell should now have exited).
   - **Pass:** tab 2's entry vanishes from the tab strip, tab strip
     auto-hides (only tab 1 left), tab 1 stays active, the program
     keeps running, and any further keystrokes in tab 1 still work.
   - **Fail (silent):** tab 2's strip entry stays even though its
     shell is dead. Switching to tab 2 then shows a dead prompt that
     only closes after you Cmd+W it — means background EOF was not
     detected.
   - **Fail (wrong tab):** tab 1 closes instead of tab 2 — means
     background EOF dispatched through the active tab's path (the
     theologian-B failure mode this fix targets).
   - **Fail (kills app):** the entire program exits when tab 2's
     shell ends — means the EOF route fell back to unconditional
     `child_done`.

**Pass signal.** Background tab vanishes on its own when its shell
exits; tab 1 unaffected; app keeps running.

**Flag if.** Any of the three fail modes above. Also flag if typing
in tab 1 during step 4 has any lag or stutter (would suggest the
background handler is doing too much work on the active path).

---

## Section 7 — Copy over a soft-wrapped line stays on one line

**What changed.** When a line you typed is longer than the terminal
width, it visually wraps onto the next row. Copying across that
wrap used to insert a literal `\n` between the two rows — so pasting
the result into another program saw two lines instead of one long
one. Now each row carries a wrap flag set by the terminal whenever
autowrap moves the cursor down, and the copy path skips the
newline when that flag is on. Real line breaks (you pressed Enter or
the program emitted `\n`) still get a real `\n` in the copied text.

**Test.**

1. Open p3_pty. Note the column count (e.g. type `tput cols`, get
   `cols0`).
2. Type a single line longer than `cols0` — pick something easy to
   recognise, e.g. `echo "AAAA...A"` with enough A's to overflow the
   row (rough rule: `cols0 + 20` A's). Press Enter so the command
   runs; `echo` will print the long line and wrap visually on the
   terminal.
3. Select the entire wrapped echo output (drag from the first `A` to
   the last `A`) and Cmd+C (Mac) / Ctrl+Shift+C (Linux/Win).
4. Paste into another text editor or the URL bar of a browser.
   - **Pass:** the pasted text is one continuous line of A's. No
     line break in the middle.
   - **Fail:** the paste shows two (or more) lines split at the row
     boundary where the terminal wrapped.
5. Hard-break case: run `printf 'one\ntwo\n'`. Select across both
   `one` and `two` and copy.
   - **Pass:** the paste is `one` newline `two` — the real `\n`
     from the printf is preserved.
   - **Fail:** the paste loses the newline between `one` and `two`.
     (This would mean the wrap flag is being set on hard breaks too.)
6. Mixed case: type `seq 1 50 | tr '\n' ' '; echo done` so you get a
   long whitespace-separated line that wraps several times, followed
   by `done`. Select from `1` through `done` and copy.
   - **Pass:** the paste is one continuous `1 2 3 ... 50 done` line
     with no embedded `\n`.

**Pass signal.** Soft-wrapped rows copy as one line; hard line breaks
still copy as `\n`.

**Flag if.** Either direction breaks — soft wraps inserting `\n`, or
hard `\n` being suppressed. Also flag if the behaviour is
intermittent (works once, fails the next time) — would suggest the
wrap flag is being cleared or not propagated correctly through
scroll-up into scrollback.

---

## Reporting results

Please flag pass/fail per section. If something fails, the specific
behaviour you saw plus what you expected helps narrow the next fix.
Sections are independent; a failure in any one section does not
invalidate the others.
