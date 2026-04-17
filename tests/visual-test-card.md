# Visual Test Card — nbs-term Character Rendering

Ruler lines use `|` at each column boundary. If characters are correctly sized,
pipes should stay vertically aligned across test and ruler lines.

## 1. CJK Wide Characters (2 columns each)

### Chinese
```
你好世界
|·|·|·|·|
```
Each `|` marks a column boundary. Wide chars span 2 columns (pipe-dot-pipe).

```
中文测试
|·|·|·|·|
```

**你好世界** — bold
*中文测试* — italic
***你好世界*** — bold italic

### Japanese
```
カタカナ
|·|·|·|·|
```

```
ひらがな
|·|·|·|·|
```

```
漢字混合テスト
|·|·|·|·|·|·|
```

**カタカナ** — bold
*ひらがな* — italic

### Korean
```
한글테스트
|·|·|·|·|·|
```

```
안녕하세요
|·|·|·|·|·|
```

## 2. Mixed Width Alignment (critical test)

Wide and narrow chars on same line — rulers must stay aligned:
```
AAAA你好BBBB
||||·||·|||||
```
A=1col each, 你=2col, 好=2col, B=1col each → 4+2+2+4=12 cols

```
AAAAAAAABBBB
|||||||||||||
```
12 single-width chars for comparison — same total width as above

```
AカBタC
||·||·||
```
Alternating single/double — 1+2+1+2+1=7 cols

## 3. Emoji (2 columns each)

```
🎉🚀🌍🔥💻
|·|·|·|·|·|
```

### Emoji sequences
👨‍💻 👩‍🔬 🏳️‍🌈 — ZWJ sequences
1️⃣ 2️⃣ 3️⃣ — keycap sequences
🇺🇸 🇯🇵 🇬🇧 — flag sequences

## 4. Symbols and Box Drawing

```
┌─────────┐
│  box     │
│  drawing │
└─────────┘
```

### Math symbols
```
∀x∈ℝ:x²≥0
||||||||||
```

← → ↑ ↓ ↔ ⇐ ⇒ ⇑ ⇓ ⇔
● ○ ■ □ ▲ △ ▼ ▽ ◆ ◇
♠ ♥ ♦ ♣ ★ ☆ ☐ ☑ ☒

## 5. RTL Text (Right-to-Left)

### Hebrew
```
שלום עולם
|||||||||
```
**שלום עולם** — bold
*שלום עולם* — italic

### Arabic
مرحبا بالعالم
**مرحبا بالعالم** — bold
*مرحبا بالعالم* — italic

### Mixed LTR/RTL
Hello שלום Hello

## 6. Accented and Combining Characters

```
Résumé café
|||||||||||
```
ñ ü ö ä ß æ ø å — European characters
**Résumé café** — bold

### Combining marks
a̐ ë̊ ö̃ — combining diacritics (should be 1 col each)
ạ ệ ộ — combining below

## 7. Fullwidth Latin and Halfwidth Katakana

```
ＡＢＣＤ
|·|·|·|·|
```
Fullwidth Latin — should be 2 cols each (same as CJK)

```
ｱｲｳｴｵ
||||||
```
Halfwidth Katakana — should be 1 col each

## 8. Bold and Italic Variants

**你好世界** vs 你好世界 — bold CJK vs normal (same width?)
*你好世界* vs 你好世界 — italic CJK vs normal
**ABCDEF** vs ABCDEF — bold ASCII vs normal
*ABCDEF* vs ABCDEF — italic ASCII vs normal
**🎉🚀** vs 🎉🚀 — bold emoji vs normal

## 9. Currency Symbols

$ € £ ¥ ₹ ₩ ₪ ₿ ¢ — all should be 1 column
```
$€£¥₹₩₪₿¢
||||||||||
```
