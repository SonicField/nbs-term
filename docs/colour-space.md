# XTerm 256-Colour Space: Structure and Conversion

## The palette

The xterm 256-colour palette is divided into three regions:

| Indices   | Name             | Count | Description                                      |
|-----------|------------------|------:|--------------------------------------------------|
| 0 -- 15   | ANSI colours     |    16 | Traditional 8 normal + 8 bright; terminal-configurable |
| 16 -- 231 | 6x6x6 colour cube |  216 | `index = 16 + 36r + 6g + b` where r,g,b in 0..5 |
| 232 -- 255| Greyscale ramp   |    24 | `grey = 8 + 10 * (index - 232)`, range 8..238    |

### The cube levels

The six intensity values on each axis of the colour cube are:

```
Index:  0    1    2    3    4    5
Value:  0   95  135  175  215  255
```

The first step (0 to 95) is a gap of 95; subsequent steps are 40 apart. This non-uniform spacing was chosen by Thomas Dickey for xterm and means darks are under-represented in the cube. The greyscale ramp partially compensates by providing fine-grained steps through the dark end.

### The greyscale ramp

24 shades from 8 to 238 in steps of 10. Pure black (0) and pure white (255) are omitted because they already exist as ANSI 0 / cube 16 and ANSI 15 / cube 231 respectively.

### ANSI colour defaults (indices 0 -- 15)

These are technically terminal-configurable. The values below are the canonical xterm defaults, derived from the X11 colour names in xterm's source (`charproc.c`):

| Index | Name           |   R |   G |   B | X11 source  |
|------:|----------------|----:|----:|----:|-------------|
|     0 | Black          |   0 |   0 |   0 | black       |
|     1 | Red            | 205 |   0 |   0 | red3        |
|     2 | Green          |   0 | 205 |   0 | green3      |
|     3 | Yellow         | 205 | 205 |   0 | yellow3     |
|     4 | Blue           |   0 |   0 | 238 | blue2       |
|     5 | Magenta        | 205 |   0 | 205 | magenta3    |
|     6 | Cyan           |   0 | 205 | 205 | cyan3       |
|     7 | White          | 229 | 229 | 229 | gray90      |
|     8 | Bright Black   | 127 | 127 | 127 | gray50      |
|     9 | Bright Red     | 255 |   0 |   0 | red         |
|    10 | Bright Green   |   0 | 255 |   0 |             |
|    11 | Bright Yellow  | 255 | 255 |   0 | yellow      |
|    12 | Bright Blue    |  92 |  92 | 255 | xterm special |
|    13 | Bright Magenta | 255 |   0 | 255 | magenta     |
|    14 | Bright Cyan    |   0 | 255 | 255 | cyan        |
|    15 | Bright White   | 255 | 255 | 255 | white       |

### Escape sequences

```
Foreground:  ESC[38;5;Nm
Background:  ESC[48;5;Nm
```

where N is the palette index 0..255.

---

## Why naive RGB distance fails

The obvious approach to finding the nearest palette colour for an arbitrary RGB value is Euclidean distance in RGB space:

```
d² = (r1-r2)² + (g1-g2)² + (b1-b2)²
```

This gives poor results because RGB is not perceptually uniform. Human vision has unequal sensitivity across channels -- a step of 40 in the blue axis looks very different from a step of 40 in green. Colours that are numerically close in RGB can look quite different, and vice versa.

## How macOS gets it right: CIELAB

Apple's ColorSync framework -- used by macOS Terminal -- performs colour matching in **CIELAB** (CIE 1976 L\*a\*b\*), a colour space specifically engineered so that equal Euclidean distances correspond to equal *perceived* colour differences. The conversion pipeline is:

```
sRGB byte  -->  linear light  -->  CIE XYZ  -->  CIELAB
  (0..255)       (0.0..1.0)       (tristimulus)   (perceptual)
```

### Step 1: sRGB to linear

The sRGB transfer function (IEC 61966-2-1) is a piecewise curve, not a simple power law:

```
if S <= 0.04045 then
    linear = S / 12.92
else
    linear = ((S + 0.055) / 1.055) ^ 2.4
```

where `S = byte_value / 255`.

### Step 2: linear RGB to CIE XYZ

A 3x3 matrix transform under the D65 illuminant (the sRGB standard white point):

```
X = 0.4124564 * R_lin + 0.3575761 * G_lin + 0.1804375 * B_lin
Y = 0.2126729 * R_lin + 0.7151522 * G_lin + 0.0721750 * B_lin
Z = 0.0193339 * R_lin + 0.2591036 * G_lin + 0.6699764 * B_lin
```

### Step 3: XYZ to CIELAB

Normalise by the D65 white point (Xn=0.95047, Yn=1.0, Zn=1.08883), then apply the LAB transfer function -- a cube root with a linear toe to keep the slope finite at the origin:

```
f(t) = t^(1/3)                           if t > (6/29)³
f(t) = t / (3 * (6/29)²) + 4/29          otherwise

L* = 116 * f(Y/Yn) - 16
a* = 500 * (f(X/Xn) - f(Y/Yn))
b* = 200 * (f(Y/Yn) - f(Z/Zn))
```

### Step 4: CIE76 colour difference

With both colours in CIELAB, the perceptual distance is just Euclidean:

```
ΔE² = ΔL² + Δa² + Δb²
```

We skip the square root since we only need to compare magnitudes.

### Matching strategy

Search all 256 palette entries and return the one with the smallest ΔE². No heuristic shortcuts (e.g. "snap each channel to the nearest cube level") -- those can miss edge-case matches across region boundaries, particularly where a greyscale ramp entry beats the nearest cube colour, or an ANSI colour happens to be closer than either.

The 256 palette CIELAB values are precomputed once at initialisation so each lookup is just one `ToLAB` call plus 256 distance comparisons.

---

## Pascal implementation

### Unit: XTermColor.pas

```pascal
unit XTermColor;
{ Bidirectional conversion between 24-bit sRGB and the xterm 256-colour
  palette.  RGB->xterm matching uses CIE76 DeltaE in CIELAB colour space for
  perceptually accurate nearest-colour selection -- the same principle
  Apple's ColorSync framework applies in macOS Terminal.

  The palette comprises three regions:
    0..15   -- ANSI colours (terminal-configurable; xterm defaults here)
   16..231  -- 6x6x6 colour cube: index = 16 + 36*r + 6*g + b
  232..255  -- 24-step greyscale ramp: grey = 8 + 10*(index - 232)        }

{$mode objfpc}{$H+}

interface

type
  TRGB = record
    R, G, B: Byte;
  end;

{ Map xterm colour index (0..255) to its canonical sRGB triplet. }
function XTermToRGB(Index: Byte): TRGB;

{ Find the perceptually nearest xterm colour for an arbitrary 24-bit
  sRGB value.  Searches all 256 entries including the 16 ANSI colours. }
function RGBToXTerm(R, G, B: Byte): Byte;

implementation

uses
  Math;

{ -------------------------------------------------------------------
  Palette data
  ------------------------------------------------------------------- }

const
  { The six intensity levels that define the 6x6x6 cube (indices 16..231).
    Note the non-uniform first step: 0 -> 95 is a gap of 95, subsequent
    steps are 40 apart.  This is the xterm/Thomas Dickey original spec. }
  CubeLevel: array[0..5] of Byte = (0, 95, 135, 175, 215, 255);

  { Canonical xterm defaults for the 16 ANSI colours.
    These match the X11 colour names xterm uses internally:
      0-7 : black, red3, green3, yellow3, blue2, magenta3, cyan3, gray90
      8-15: gray50, red, (bright green), yellow, (bright blue),
            magenta, cyan, white
    Terminals may override these -- substitute your own values if needed. }
  AnsiPalette: array[0..15] of TRGB = (
    (R:  0; G:  0; B:  0),      {  0 -- Black                           }
    (R:205; G:  0; B:  0),      {  1 -- Red            (X11 red3)       }
    (R:  0; G:205; B:  0),      {  2 -- Green          (X11 green3)     }
    (R:205; G:205; B:  0),      {  3 -- Yellow         (X11 yellow3)    }
    (R:  0; G:  0; B:238),      {  4 -- Blue           (X11 blue2)      }
    (R:205; G:  0; B:205),      {  5 -- Magenta        (X11 magenta3)   }
    (R:  0; G:205; B:205),      {  6 -- Cyan           (X11 cyan3)      }
    (R:229; G:229; B:229),      {  7 -- White          (X11 gray90)     }
    (R:127; G:127; B:127),      {  8 -- Bright Black   (X11 gray50)     }
    (R:255; G:  0; B:  0),      {  9 -- Bright Red                      }
    (R:  0; G:255; B:  0),      { 10 -- Bright Green                    }
    (R:255; G:255; B:  0),      { 11 -- Bright Yellow                   }
    (R: 92; G: 92; B:255),      { 12 -- Bright Blue    (xterm special)  }
    (R:255; G:  0; B:255),      { 13 -- Bright Magenta                  }
    (R:  0; G:255; B:255),      { 14 -- Bright Cyan                     }
    (R:255; G:255; B:255)       { 15 -- Bright White                    }
  );

{ -------------------------------------------------------------------
  CIELAB colour science
  ------------------------------------------------------------------- }

type
  TLAB = record
    L, A, B: Double;
  end;

var
  { Precomputed CIELAB coordinates for every palette entry.
    Built once at unit initialisation -- makes RGBToXTerm a fast
    linear scan of 256 distance comparisons. }
  PaletteLAB: array[0..255] of TLAB;

{ Linearise one sRGB channel: undo the ~2.2 transfer curve.
  Follows IEC 61966-2-1 exactly (the piecewise sRGB EOTF). }
function SRGBToLinear(V: Byte): Double; inline;
var
  S: Double;
begin
  S := V * (1.0 / 255.0);
  if S <= 0.04045 then
    Result := S / 12.92
  else
    Result := Power((S + 0.055) / 1.055, 2.4);
end;

{ CIELAB f(t) -- cube-root with linear toe for very small tristimulus
  ratios, ensuring continuity and finite slope at the origin. }
function LabF(T: Double): Double; inline;
const
  Delta3 = 216.0 / 24389.0;        { (6/29)^3 = 0.008856 }
  Scale  = 24389.0 / 3132.0;       { 1 / (3 * delta^2)   }
  Offset = 4.0 / 29.0;             { 16/116               }
begin
  if T > Delta3 then
    Result := Power(T, 1.0 / 3.0)
  else
    Result := Scale * T + Offset;
end;

{ Convert one sRGB colour to CIELAB under the D65 illuminant.
  Pipeline: sRGB byte -> linear -> CIE XYZ -> CIELAB. }
function ToLAB(R, G, B: Byte): TLAB;
var
  LR, LG, LB: Double;
  X, Y, Z, FX, FY, FZ: Double;
const
  { Reciprocals of the D65 reference white (Xn, Yn, Zn).
    Yn = 1.0 so its reciprocal is elided from the code. }
  InvXn = 1.0 / 0.95047;
  InvZn = 1.0 / 1.08883;
begin
  { Step 1 -- linearise sRGB }
  LR := SRGBToLinear(R);
  LG := SRGBToLinear(G);
  LB := SRGBToLinear(B);

  { Step 2 -- linear sRGB -> CIE XYZ  (IEC 61966-2-1 matrix, D65) }
  X := 0.4124564 * LR + 0.3575761 * LG + 0.1804375 * LB;
  Y := 0.2126729 * LR + 0.7151522 * LG + 0.0721750 * LB;
  Z := 0.0193339 * LR + 0.2591036 * LG + 0.6699764 * LB;

  { Step 3 -- CIE XYZ -> CIELAB }
  FX := LabF(X * InvXn);
  FY := LabF(Y);             { Y / Yn where Yn = 1.0 }
  FZ := LabF(Z * InvZn);

  Result.L := 116.0 * FY - 16.0;
  Result.A := 500.0 * (FX - FY);
  Result.B := 200.0 * (FY - FZ);
end;

{ Squared CIE76 DeltaE -- Euclidean distance in CIELAB.
  We omit the square root since only relative magnitude matters. }
function DeltaESq(const C1, C2: TLAB): Double; inline;
begin
  Result := Sqr(C1.L - C2.L) + Sqr(C1.A - C2.A) + Sqr(C1.B - C2.B);
end;

{ -------------------------------------------------------------------
  Public API
  ------------------------------------------------------------------- }

function XTermToRGB(Index: Byte): TRGB;
var
  CI, Grey: Integer;
begin
  if Index < 16 then
    { Region 1: ANSI colours -- direct table lookup }
    Result := AnsiPalette[Index]
  else if Index < 232 then
  begin
    { Region 2: 6x6x6 colour cube.
      Decode the three cube coordinates from the linear index. }
    CI := Index - 16;
    Result.R := CubeLevel[CI div 36];
    Result.G := CubeLevel[(CI div 6) mod 6];
    Result.B := CubeLevel[CI mod 6];
  end
  else
  begin
    { Region 3: 24-step greyscale ramp (8, 18, 28, ... 238).
      Excludes pure black (0) and pure white (255) since those
      already exist as ANSI 0/cube 16 and ANSI 15/cube 231. }
    Grey := 8 + 10 * (Index - 232);
    Result.R := Grey;
    Result.G := Grey;
    Result.B := Grey;
  end;
end;

function RGBToXTerm(R, G, B: Byte): Byte;
var
  Target: TLAB;
  I: Integer;
  D, Best: Double;
begin
  Target := ToLAB(R, G, B);

  { Seed with palette entry 0 }
  Best := DeltaESq(Target, PaletteLAB[0]);
  Result := 0;

  { Linear scan -- 255 CIELAB distance comparisons against the
    precomputed table.  No heuristic shortcuts that could miss
    edge-case matches across region boundaries. }
  for I := 1 to 255 do
  begin
    D := DeltaESq(Target, PaletteLAB[I]);
    if D < Best then
    begin
      Best := D;
      Result := I;
    end;
  end;
end;

{ -------------------------------------------------------------------
  Unit initialisation -- precompute the CIELAB palette once at startup.
  Cost: 256 x sRGB->LAB (a few hundred us on modern hardware).
  ------------------------------------------------------------------- }

procedure BuildPaletteLAB;
var
  I: Integer;
  C: TRGB;
begin
  for I := 0 to 255 do
  begin
    C := XTermToRGB(I);
    PaletteLAB[I] := ToLAB(C.R, C.G, C.B);
  end;
end;

initialization
  BuildPaletteLAB;

end.
```

### Demo program: XTermColorDemo.pas

```pascal
program XTermColorDemo;
{ Quick smoke-test for the XTermColor unit.
  Compile:  fpc XTermColorDemo.pas
  Run:      ./XTermColorDemo                }

{$mode objfpc}{$H+}

uses
  XTermColor;

{ Print a colour swatch using the actual xterm escape sequence,
  followed by the index and RGB values. }
procedure ShowEntry(Index: Byte);
var
  C: TRGB;
begin
  C := XTermToRGB(Index);
  { Set background to this xterm colour, print a block, then reset }
  Write(#27'[48;5;', Index, 'm    '#27'[0m');
  WriteLn('  index ', Index:3,
          '  ->  R=', C.R:3, ' G=', C.G:3, ' B=', C.B:3);
end;

{ Round-trip test: RGB -> xterm -> RGB, report any that don't survive. }
procedure RoundTripTest;
var
  I: Integer;
  C, C2: TRGB;
  Idx: Byte;
  Mismatches: Integer;
begin
  WriteLn;
  WriteLn('-- Round-trip test: XTermToRGB -> RGBToXTerm --');
  Mismatches := 0;
  for I := 0 to 255 do
  begin
    C := XTermToRGB(I);
    Idx := RGBToXTerm(C.R, C.G, C.B);
    { The returned index may differ from I if two palette entries
      share the same RGB (e.g. ANSI 0 and cube 16 are both black).
      What matters is that the RGB values match. }
    C2 := XTermToRGB(Idx);
    if (C.R <> C2.R) or (C.G <> C2.G) or (C.B <> C2.B) then
    begin
      WriteLn('  MISMATCH: index ', I:3,
              ' (', C.R:3, ',', C.G:3, ',', C.B:3, ')',
              ' -> ', Idx:3,
              ' (', C2.R:3, ',', C2.G:3, ',', C2.B:3, ')');
      Inc(Mismatches);
    end;
  end;
  if Mismatches = 0 then
    WriteLn('  All 256 palette colours round-trip correctly.')
  else
    WriteLn('  ', Mismatches, ' mismatches found.');
end;

{ Test some known RGB values and show what they map to. }
procedure ProbeTest;

  procedure Probe(R, G, B: Byte);
  var
    Idx: Byte;
    C: TRGB;
  begin
    Idx := RGBToXTerm(R, G, B);
    C := XTermToRGB(Idx);
    Write('  RGB(', R:3, ',', G:3, ',', B:3, ')');
    Write('  ->  index ', Idx:3);
    Write('  RGB(', C.R:3, ',', C.G:3, ',', C.B:3, ')');
    { Show a visual swatch }
    Write('  '#27'[48;2;', R, ';', G, ';', B, 'm in '#27'[0m');
    WriteLn(#27'[48;5;', Idx, 'm out'#27'[0m');
  end;

begin
  WriteLn;
  WriteLn('-- Probe: arbitrary RGB -> nearest xterm colour --');
  Probe(255, 128,   0);   { orange          }
  Probe(128,  64,  32);   { brown           }
  Probe( 70, 130, 180);   { steel blue      }
  Probe(255, 192, 203);   { pink            }
  Probe( 50,  50,  50);   { dark grey       }
  Probe(100, 100, 100);   { mid grey        }
  Probe(200, 200, 200);   { light grey      }
  Probe(  1,   1,   1);   { near-black      }
  Probe(254, 254, 254);   { near-white      }
  Probe(127,   0, 255);   { purple          }
  Probe(  0, 100,   0);   { dark green      }
  Probe(255, 215,   0);   { gold            }
end;

begin
  WriteLn('=== XTermColor Demo ===');

  WriteLn;
  WriteLn('-- ANSI colours (0..15) --');
  for var I: Integer := 0 to 15 do
    ShowEntry(I);

  WriteLn;
  WriteLn('-- Cube samples (16..231, every 24th) --');
  for var I: Integer := 0 to 8 do
    ShowEntry(16 + I * 24);

  WriteLn;
  WriteLn('-- Greyscale ramp (232..255) --');
  for var I: Integer := 232 to 255 do
    ShowEntry(I);

  RoundTripTest;
  ProbeTest;
end.
```

---

## Performance notes

- **`XTermToRGB`**: O(1) -- direct computation or table lookup.
- **`RGBToXTerm`**: O(256) -- one `ToLAB` conversion for the input, then 256 precomputed distance comparisons. No allocations, no branches beyond the loop.
- **Initialisation**: O(256) -- `BuildPaletteLAB` runs once at unit load. A few hundred microseconds on modern hardware.

For hot-path use (e.g. converting every pixel of a truecolour image to 256-colour), the `SRGBToLinear` call could be replaced with a 256-entry lookup table. The 256-way palette scan is already branch-free enough to be fast.
