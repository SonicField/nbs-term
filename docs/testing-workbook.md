# nbs-term Manual Testing Workbook

Step-by-step test procedures for manual validation. Work through each
section in order. Record PASS/FAIL next to each test.

---

## Prerequisites

```bash
git pull
pip install -e .     # or: python setup.py build_ext --inplace
```

Verify automated tests pass first:
```bash
python -m pytest tests/ -v --tb=short
```
Expected: 223 passed, 0 skipped.

---

## 1. Basic Terminal

### 1.1 Connect to a host
**Action:** `nbs-term user@host`
**Expected:** Terminal window opens, SSH connects, shell prompt appears.
**Result:** ___

### 1.2 Type and echo
**Action:** Type `echo hello` and press Enter.
**Expected:** Command echoes correctly, output "hello" appears on next line.
**Result:** ___

### 1.3 Colors
**Action:** Run `ls --color` in a directory with files.
**Expected:** Files, directories, symlinks show distinct colors.
**Result:** ___

### 1.4 Full-screen app
**Action:** Run `vim` or `htop`.
**Expected:** Full-screen UI renders correctly, responds to input.
Press `q` or `Ctrl-C` to exit.
**Result:** ___

---

## 2. Mouse Selection

### 2.1 Select text
**Action:** Click and drag to select some text (e.g. a word on screen).
**Expected:** Selected text highlights with fg/bg color swap.
No overlay artifacts, no misalignment.
**Result:** ___

### 2.2 Copy selected text
**Action:** Select a word, then press Ctrl-C (or Cmd-C on Mac).
Open a text editor and paste.
**Expected:** Pasted text matches exactly what was highlighted.
No extra characters before or after the selection.
**Result:** ___

### 2.3 Single character selection
**Action:** Click and drag to select exactly one character.
Copy and paste.
**Expected:** Exactly one character is copied.
**Result:** ___

### 2.4 Multi-line selection
**Action:** Select text spanning 3+ lines. Copy and paste.
**Expected:** All selected lines copied with correct line breaks.
Trailing whitespace stripped from each line.
**Result:** ___

### 2.5 Clear selection
**Action:** After making a selection, click anywhere without dragging.
**Expected:** Selection highlight disappears.
**Result:** ___

---

## 3. Cursor

### 3.1 Cursor style
**Action:** Open Preferences, change cursor style (block/bar/underline).
Click Save.
**Expected:** Cursor changes to the selected style immediately.
**Result:** ___

### 3.2 Cursor blink
**Action:** Wait 2 seconds without typing. Observe cursor.
**Expected:** Cursor blinks on/off.
**Result:** ___

### 3.3 Blink suppression during typing
**Action:** Type continuously for a few seconds. Watch the cursor.
**Expected:** Cursor stays solid (visible) while typing.
Resumes blinking after ~0.5 seconds of inactivity.
**Result:** ___

### 3.4 Cursor color persistence
**Action:** Open Preferences, change cursor color to green (or any color).
Click Save. Close nbs-term completely. Reopen `nbs-term user@host`.
**Expected:** Cursor color is the color you set (not the default).
**Result:** ___

---

## 4. Scrollback

### 4.1 Mouse wheel scroll
**Action:** Generate output: `seq 1 200`. Then scroll up with mouse
wheel (or two-finger trackpad swipe).
**Expected:** Terminal scrolls up through output history.
Lines previously off-screen become visible.
**Result:** ___

### 4.2 Keyboard scroll
**Action:** With scrollback history available, press Ctrl-Shift-Up.
**Expected:** Terminal scrolls up one line.
**Result:** ___

### 4.3 Auto-scroll on input
**Action:** Scroll up into history, then type any character.
**Expected:** Terminal jumps back to live output (bottom of buffer).
Your typed character appears at the prompt.
**Result:** ___

### 4.4 Auto-scroll on new output
**Action:** Scroll up into history, then wait for new output
(e.g. a running `ping` or `tail -f`).
**Expected:** Terminal stays scrolled up (does NOT jump to bottom
on new output -- only on user input).
**Result:** ___

---

## 5. Tabs (Phase 2)

### 5.1 New tab
**Action:** Press Ctrl-Shift-T (or Cmd-T on Mac).
**Expected:** A new tab appears, connecting to the same host.
New SSH session, independent shell prompt.
**Result:** ___

### 5.2 Switch tabs
**Action:** With 2+ tabs open, press Ctrl-Tab.
**Expected:** Switches to the next tab. The terminal content
in each tab is independent.
**Result:** ___

### 5.3 Switch tabs backward
**Action:** Press Ctrl-Shift-Tab.
**Expected:** Switches to the previous tab.
**Result:** ___

### 5.4 Close tab
**Action:** Press Ctrl-Shift-W (or Cmd-W on Mac).
**Expected:** Current tab closes. Adjacent tab becomes active.
**Result:** ___

### 5.5 Close last tab
**Action:** With only one tab open, press Ctrl-Shift-W.
**Expected:** Window closes entirely (application exits).
**Result:** ___

### 5.6 Tab independence
**Action:** In tab 1, run `echo TAB1`. Switch to tab 2,
run `echo TAB2`. Switch back to tab 1.
**Expected:** Tab 1 still shows TAB1 output, not TAB2.
Each tab has its own terminal state.
**Result:** ___

### 5.7 Tab labels
**Action:** Open multiple tabs.
**Expected:** Each tab label shows the hostname.
**Result:** ___

---

## 6. Configuration

### 6.1 Font change
**Action:** Open Preferences, change font family and size. Save.
**Expected:** Terminal text renders in the new font immediately.
**Result:** ___

### 6.2 Config persistence
**Action:** Change font, cursor style, or colors in Preferences.
Save. Close and reopen nbs-term.
**Expected:** All settings persist across restart.
**Result:** ___

---

## 7. Visual Test Card

### 7.1 Character rendering
**Action:** In nbs-term, run: `cat tests/visual-test-card.txt`
(or use `nbs-md-viewer tests/visual-test-card.md` if available).
**Expected:** ASCII text renders aligned. CJK characters render
(width depends on font -- see note below). Emoji render.
Box drawing characters form connected lines.
**Result:** ___

**Note:** CJK characters may appear narrower than 2 columns with
the default monospace font. This is a font limitation, not a bug.
Use a CJK-capable font (e.g. Noto Sans Mono CJK) for proper
double-width rendering.

---

## Summary

| Section | Tests | Pass | Fail |
|---------|-------|------|------|
| 1. Basic Terminal | 4 | | |
| 2. Mouse Selection | 5 | | |
| 3. Cursor | 4 | | |
| 4. Scrollback | 4 | | |
| 5. Tabs | 7 | | |
| 6. Configuration | 2 | | |
| 7. Visual Test Card | 1 | | |
| **Total** | **27** | | |
