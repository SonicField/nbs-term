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

*Pending — added after the tab strip and shortcuts ship.*

---

## Section 3 — Fullscreen + Mac menu bar

*Pending — added after the fullscreen toggle and menu install ship.*

---

## Reporting results

Please flag pass/fail per section. If something fails, the specific
behaviour you saw plus what you expected helps narrow the next fix.
Sections are independent; a failure in Section 2 does not invalidate
your Section 1 result.
