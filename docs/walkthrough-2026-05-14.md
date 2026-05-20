# Walkthrough — Autonomous Window 2026-05-14

This document covers everything shipped while you were away. Three changes
have user-visible effects; you can work through them linearly. A fourth
commit added an automation test only and is mentioned at the end for
completeness.

## Install

Run this once. It rebuilds from the latest source:

```
curl -fsSL https://raw.githubusercontent.com/SonicField/nbs-term/pure-phc-master/scripts/mac-setup-phc.sh | bash
```

Then launch:

```
~/nbs-term-phc/build/p3_pty
```

Launch from a Terminal window so you can see startup messages on the parent
shell. Several of the checks below ask you to look at output that prints
before the GUI window appears.

---

## Check 1 — Bold and italic should now work

**What changed.** Your saved font preference is Monaco. Monaco on your Mac
does not have separate bold or italic faces installed, so previously the
program asked the system for "Monaco bold" and silently got "Monaco
regular" back. The new behaviour is: at startup, the program checks all
four needed faces (normal, bold, italic, bold-italic). If any face is
missing, it falls back to a complete font for all four — so text on the
same line stays in one consistent style, not a mix.

You also get a one-time message at startup naming what it substituted in.

**Test.**

1. Look at the Terminal output between launch and the GUI appearing. You
   should see one line something like:

   ```
   [font] configured family 'Monaco' lacks bold/italic faces ... reconfigured all four named fonts to TkFixedFont (Menlo) for visual cohesion.
   ```

   Exact substitute family may differ — anything that names a fallback is
   fine.

2. Inside the running p3_pty, run:

   ```
   printf '\e[1mBOLD\e[0m normal \e[3mITAL\e[0m normal \e[1;3mBI\e[0m normal\n'
   ```

3. The labels BOLD, ITAL, and BI should each look visibly distinct from
   the surrounding "normal" labels.

**Pass signal.** Bold looks heavier; italic looks slanted; BI looks both.
Same as you see in any standard terminal supporting bold/italic
distinctly.

**Flag if.** All four labels still look identical, OR you see no fallback
message at startup despite Monaco being your saved family.

---

## Check 2 — Bold should also brighten the colour

**What changed.** This is standard terminal behaviour you mentioned: when
text is one of the eight basic ANSI colours AND it is bold, most
terminals show it in the bright variant of that colour (bright red
instead of regular red, etc.). p3_pty previously only changed the
weight, never the colour. Now it does both.

There is also a new preference checkbox to turn this off if you ever
want weight-only behaviour.

**Test.**

1. In the running p3_pty, run:

   ```
   printf '\e[31mnormal red\e[0m  \e[1;31mbold red\e[0m\n'
   ```

2. The "bold red" should look noticeably brighter than the "normal red"
   to its left.

3. Repeat for any other colour you want — replace `31` with `32`
   (green), `33` (yellow), `34` (blue), `35` (magenta), `36` (cyan).

4. Open preferences with Cmd+,. There is a new checkbox "Bright bold
   colors:". Untick it, save, relaunch p3_pty, repeat step 1. The
   bold red should now look the same shade as normal red (just heavier).
   Re-tick + save + relaunch to restore the brighter behaviour.

**Pass signal.** Default-on case: bold red is brighter than normal red.
Default-off case: bold red is same shade as normal red but heavier
weight.

**Flag if.** Bold red looks identical to normal red with the checkbox
ticked, OR the checkbox has no effect after save+relaunch.

---

## Check 3 — Configurable colour palette

**What changed.** The 16 standard ANSI colours are now user-settable in
preferences. There is a row of 16 colour swatches (the eight basic
colours on top, the eight bright variants on the bottom). Click any
swatch to open the colour picker and change just that colour. There is
also a new checkbox: "Default fg/bg from palette:" — off by default,
which preserves your existing foreground and background settings; turn
it on if you want the default text colour to come from palette slot 7
(white) and the default background from slot 0 (black) instead of your
explicit fg/bg preferences.

The default palette values match what you saw before (the standard xterm
colours), so untouched preferences mean no visual change.

**Test.**

1. Open preferences with Cmd+,. You should see 16 colour swatches
   somewhere in the dialog (added next to the existing font controls).

2. Click any swatch — say, slot 1 (the second swatch, which is the basic
   "red"). The standard Mac colour picker should open.

3. Pick a different shade — say, a bright orange. Click OK. The swatch
   should update to your chosen colour.

4. Click Save. Relaunch p3_pty.

5. Run `printf '\e[31mhello\e[0m\n'`. The text should appear in your
   chosen orange, not the original red.

6. Test the override toggle: open Cmd+, again, tick "Default fg/bg from
   palette:", save, relaunch. The default text colour and
   background should now come from your palette slots 7 and 0 instead of
   your separately-set fg/bg. Untick + save + relaunch to restore the
   previous behaviour.

**Pass signal.** Swatch click opens picker; chosen colour persists across
relaunch; ANSI red text uses the new colour.

**Flag if.** Swatches don't render in the dialog, OR clicking does
nothing, OR the chosen colour is lost after relaunch, OR the override
toggle has no effect.

---

## Known gaps to flag

These are deliberately deferred and not bugs to investigate, but worth
mentioning so you don't waste time on them:

- If you saved a different font than Monaco at some point and want to go
  back to it, the variant-fallback only fires on missing faces, not on
  the family choice itself. Your saved choice is preserved unless you
  explicitly change it in preferences.

- The fourth commit shipped this window (test_alt_mask) was an
  automation test only — build-server side, no GUI element. It exists so
  future changes to Option-key handling get caught automatically.

## Reporting results

Please flag pass/fail on each numbered check. If something fails, the
specific terminal text (or screenshot) plus what you expected helps
narrow the next fix. Once all three checks pass we resume building on
the deferred items (border fix path, golden-baseline test improvements,
tab support).
