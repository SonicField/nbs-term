# Configuration

nbs-term stores settings in `~/.nbs/nbs-term.honest` on Mac and Linux, `%LOCALAPPDATA%\nbs\nbs-term.honest` on Windows. The file is created with sensible defaults on first run.

## Format

The config file uses Honest format — a self-describing interchange format with Pascal-like syntax. Every field carries its type definition, so the file explains itself.

```pascal
type
  CursorStyle = (Block, Wireframe, Underline, Bar);

  FontConfig = record
    family : String;
    size   : Integer;
  end;

  CursorConfig = record
    style : CursorStyle;
    blink : Boolean;
  end;

  TerminalConfig = record
    font       : FontConfig;
    cursor     : CursorConfig;
    fg         : String;
    bg         : String;
    gamma      : Real;
    refresh_hz : Integer;
  end;

var config : TerminalConfig = (
  font       : (family : 'Menlo'; size : 14);
  cursor     : (style : Block; blink : True);
  fg         : '#d0d0d0';
  bg         : '#000000';
  gamma      : 1.0;
  refresh_hz : 60;
);
```

## Settings

| Setting | Type | Default | What it does |
|---------|------|---------|-------------|
| font.family | String | Menlo (Mac), monospace (Linux) | Terminal font face |
| font.size | Integer | 14 | Font size in points |
| cursor.style | CursorStyle | Block | Cursor shape: Block, Wireframe, Underline, or Bar |
| cursor.blink | Boolean | True | Whether the cursor blinks (530ms cycle) |
| fg | String | #d0d0d0 | Default text colour (hex RGB) |
| bg | String | #000000 | Terminal background colour (hex RGB) |
| gamma | Real | 1.2 (Mac), 1.0 (Linux) | Colour gamma correction — higher values darken midtones |
| refresh_hz | Integer | 60 | Render refresh rate in Hz (10-120). Lower values reduce flicker but increase input latency |

## Preferences Dialog

Open with Cmd+, (Mac) or Ctrl+, (Linux/Windows). Changes apply immediately to the running terminal — no restart needed.

The dialog provides:
- Font family dropdown (validated monospace fonts only)
- Font size spinner
- Cursor style dropdown
- Cursor blink checkbox
- Gamma slider (0.5 to 2.0)
- Refresh rate slider (10-120 Hz)
- Foreground colour button with 256-colour picker
- Background colour button with 256-colour picker

Save writes back to `~/.nbs/nbs-term.honest`.

## CLI Overrides

Command-line arguments override config file values for a single session:

```bash
nbs-term --font-size=20 --font-family=Consolas user@host
nbs-term --refresh-hz=25 user@host   # lower refresh rate to reduce flicker
nbs-term -v user@host                # verbose SSH logging to stderr
```

## Gamma Correction

macOS applies colour management (ColorSync/Display P3) to Tk canvas colours, which can make standard xterm palette colours appear too bright. The gamma setting compensates:

- gamma = 1.0 — no correction (standard on Linux)
- gamma > 1.0 — darkens midtones (use on Mac if colours look washed out)
- gamma < 1.0 — brightens midtones

Adjust in preferences until colours look right for your display. The default of 1.2 on Mac is a starting point — your display profile may need a different value.

## Colour Rendering

Three things affect how colours appear:

1. **The xterm-256 palette** — stored in the C extension with standard sRGB values. Correct per spec.
2. **SGR DIM (attribute 2)** — reduces foreground brightness to 50%. Used by TUI applications for ghost text, hints, and secondary information.
3. **Gamma correction** — the final transform before colours reach Tk. Applied in Python, configurable per above.

See `docs/colour-space.md` for the colour science behind palette matching and sRGB conversion.
