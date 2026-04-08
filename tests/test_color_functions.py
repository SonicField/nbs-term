"""
test_color_functions.py — TDD baseline for Phase 1 Phoenics port.

These tests capture the exact behavior of dim_color(), gamma_correct(),
and xterm_256_color() as reference implementations. When these functions
are ported to phc, the SAME tests verify the phc output matches.
"""
import sys
import os
import unittest

sys.path.insert(0, os.path.dirname(os.path.dirname(os.path.abspath(__file__))))


# --- Reference implementations (copied from nbsterm.py) ---
# These are the PYTHON versions. When phc versions exist,
# tests will compare phc output against these.

def dim_color(hex_color):
    if not hex_color.startswith("#") or len(hex_color) != 7:
        return hex_color
    r = int(hex_color[1:3], 16) // 2
    g = int(hex_color[3:5], 16) // 2
    b = int(hex_color[5:7], 16) // 2
    return f"#{r:02x}{g:02x}{b:02x}"


def gamma_correct(hex_color, gamma):
    if gamma == 1.0 or not hex_color.startswith("#") or len(hex_color) != 7:
        return hex_color
    r = int(hex_color[1:3], 16)
    g = int(hex_color[3:5], 16)
    b = int(hex_color[5:7], 16)
    r = int(255 * (r / 255) ** gamma)
    g = int(255 * (g / 255) ** gamma)
    b = int(255 * (b / 255) ** gamma)
    return f"#{r:02x}{g:02x}{b:02x}"


def xterm_256_color(index):
    if index < 16:
        ansi = [
            "#000000", "#cd0000", "#00cd00", "#cdcd00",
            "#0000ee", "#cd00cd", "#00cdcd", "#e5e5e5",
            "#7f7f7f", "#ff0000", "#00ff00", "#ffff00",
            "#5c5cff", "#ff00ff", "#00ffff", "#ffffff",
        ]
        return ansi[index]
    elif index < 232:
        ci = index - 16
        r = ci // 36
        g = (ci // 6) % 6
        b = ci % 6
        r = r * 40 + 55 if r else 0
        g = g * 40 + 55 if g else 0
        b = b * 40 + 55 if b else 0
        return f"#{r:02x}{g:02x}{b:02x}"
    else:
        v = (index - 232) * 10 + 8
        return f"#{v:02x}{v:02x}{v:02x}"


# --- Tests ---

class TestDimColor(unittest.TestCase):
    """Reference tests for dim_color — halves RGB brightness."""

    def test_white_to_half(self):
        self.assertEqual(dim_color("#ffffff"), "#7f7f7f")

    def test_black_stays_black(self):
        self.assertEqual(dim_color("#000000"), "#000000")

    def test_red(self):
        self.assertEqual(dim_color("#cd0000"), "#660000")

    def test_green(self):
        self.assertEqual(dim_color("#00cd00"), "#006600")

    def test_arbitrary(self):
        self.assertEqual(dim_color("#8844cc"), "#442266")

    def test_invalid_passthrough(self):
        self.assertEqual(dim_color("red"), "red")
        self.assertEqual(dim_color("#fff"), "#fff")

    def test_all_ansi_16(self):
        """Dim all 16 ANSI colors — no crashes, all valid hex."""
        for i in range(16):
            c = xterm_256_color(i)
            d = dim_color(c)
            self.assertTrue(d.startswith("#"))
            self.assertEqual(len(d), 7)


class TestGammaCorrect(unittest.TestCase):
    """Reference tests for gamma_correct."""

    def test_gamma_1_identity(self):
        self.assertEqual(gamma_correct("#abcdef", 1.0), "#abcdef")

    def test_black_any_gamma(self):
        self.assertEqual(gamma_correct("#000000", 0.5), "#000000")
        self.assertEqual(gamma_correct("#000000", 2.0), "#000000")

    def test_white_any_gamma(self):
        self.assertEqual(gamma_correct("#ffffff", 0.5), "#ffffff")
        self.assertEqual(gamma_correct("#ffffff", 2.0), "#ffffff")

    def test_darken(self):
        result = gamma_correct("#808080", 1.5)
        self.assertLess(int(result[1:3], 16), 0x80)

    def test_brighten(self):
        result = gamma_correct("#808080", 0.5)
        self.assertGreater(int(result[1:3], 16), 0x80)

    def test_invalid_passthrough(self):
        self.assertEqual(gamma_correct("red", 1.5), "red")

    def test_all_256_colors(self):
        """Gamma correct all 256 palette colors — no crashes."""
        for i in range(256):
            c = xterm_256_color(i)
            r = gamma_correct(c, 1.2)
            self.assertTrue(r.startswith("#"))
            self.assertEqual(len(r), 7)


class TestXterm256Color(unittest.TestCase):
    """Reference tests for xterm_256_color palette."""

    def test_ansi_black(self):
        self.assertEqual(xterm_256_color(0), "#000000")

    def test_ansi_red(self):
        self.assertEqual(xterm_256_color(1), "#cd0000")

    def test_ansi_white(self):
        self.assertEqual(xterm_256_color(15), "#ffffff")

    def test_cube_origin(self):
        """Color 16 = cube (0,0,0) = black."""
        self.assertEqual(xterm_256_color(16), "#000000")

    def test_cube_red(self):
        """Color 196 = cube (5,0,0) = bright red."""
        self.assertEqual(xterm_256_color(196), "#ff0000")

    def test_cube_mid(self):
        """Color 110 = cube (2,3,4) — verify against formula."""
        c = xterm_256_color(110)
        # 110-16=94, r=94//36=2→135, g=(94//6)%6=3→175, b=94%6=4→215
        self.assertEqual(c, "#87afd7")

    def test_grayscale_start(self):
        """Color 232 = darkest gray."""
        self.assertEqual(xterm_256_color(232), "#080808")

    def test_grayscale_end(self):
        """Color 255 = lightest gray."""
        self.assertEqual(xterm_256_color(255), "#eeeeee")

    def test_grayscale_ramp(self):
        """Grayscale ramp is monotonically increasing."""
        prev = 0
        for i in range(232, 256):
            c = xterm_256_color(i)
            v = int(c[1:3], 16)
            self.assertGreaterEqual(v, prev)
            prev = v

    def test_all_256_valid_hex(self):
        """All 256 colors produce valid 7-char hex strings."""
        for i in range(256):
            c = xterm_256_color(i)
            self.assertTrue(c.startswith("#"), f"Color {i}: {c}")
            self.assertEqual(len(c), 7, f"Color {i}: {c}")

    def test_cube_formula(self):
        """Verify the 6x6x6 cube uses standard xterm ramp: 0,95,135,175,215,255."""
        ramp = [0, 95, 135, 175, 215, 255]
        for ri in range(6):
            for gi in range(6):
                for bi in range(6):
                    idx = 16 + ri * 36 + gi * 6 + bi
                    c = xterm_256_color(idx)
                    r = int(c[1:3], 16)
                    g = int(c[3:5], 16)
                    b = int(c[5:7], 16)
                    self.assertEqual(r, ramp[ri], f"Color {idx} R: {r} != {ramp[ri]}")
                    self.assertEqual(g, ramp[gi], f"Color {idx} G: {g} != {ramp[gi]}")
                    self.assertEqual(b, ramp[bi], f"Color {idx} B: {b} != {ramp[bi]}")


if __name__ == '__main__':
    result = unittest.main(verbosity=2, exit=False)
    total = result.result.testsRun
    failures = len(result.result.failures) + len(result.result.errors)
    skipped = len(result.result.skipped)
    passed = total - failures - skipped
    print(f"\n  Pass: {passed} | Fail: {failures} | Skip: {skipped} | Total: {total}")
    gate = "OPEN" if failures == 0 and skipped == 0 else "BLOCKED"
    print(f"  Gate: {gate} (full_suite: no)")
    sys.exit(0 if failures == 0 else 1)
