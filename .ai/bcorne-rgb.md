# bcorne (dexter keymap): adjusting and debugging RGB at runtime

Read this before helping adjust the RGB effect/colour on `keyboards/szrkbd/bcorne/keymaps/dexter/`
by hand (RM_* keys / knobs), or before diagnosing "the colour won't change" / "I can't reach
effect X". Everything below was established on hardware on 2026-09-17 after a long, painful
session. Do not re-derive it; do not repeat the mistakes in the "Traps" section.

File:line refs are to the state on 2026-09-17 and may drift.

## 1. Where runtime RGB state lives

- All runtime RGB state (mode, hue, sat, val, speed) is `rgb_matrix_config`, persisted to
  **EEPROM** by every RM_* key. The compiled defaults in `keymaps/dexter/config.h` only apply
  on a fresh EEPROM: `RGB_MATRIX_SOLID_COLOR`, hue 94, sat 255, val 50 (a dim green).
- `EE_CLR` is bound on the **leader layer** (`keymap.c` `_LEADR` row 1, outer key). Hitting it
  wipes EEPROM and drops the board to that dim solid green. This is the usual cause of
  "my colour suddenly reset".
- The user's preferred look ("sparkling orange" / rust) is **`PIXEL_FRACTAL_OK` at hue
  roughly 16–32**, set at runtime and therefore lost on every EEPROM wipe. As of 2026-09-17 it
  is NOT the compiled default (see §7).
- Split: `keyboard.json` enables `split.transport.sync.rgb_matrix`, and core memcpys the whole
  `rgb_matrix_config` master→slave (`quantum/split_common/transactions.c`). Both halves always
  share one config; a colour difference between halves is not a config-sync issue.

## 2. The control surface (RAISE2 layer, `_RAISE2` = layer 3)

Same LAYOUT slot = same physical key, so read positions off the base layer:

| Base key (right half, bottom row) | On RAISE2 | Effect |
|---|---|---|
| `N`   | `RM_TOGG` | RGB on/off |
| `M`   | `RM_NEXT` | **next effect, exactly one step per tap** |
| `,`   | `RM_HUEU` | hue ±8 (see §5) |
| `.`   | `RM_SATU` | sat ±16 |
| `/`   | `RM_SPDD` | speed −16 |
| `;`   | `RM_SPDU` | speed +16 |

Knobs on RAISE2 (`encoder_map`): **left** = `RM_PREV` (CCW) / `RM_NEXT` (CW); **right** =
`RM_VALD` (CCW) / `RM_VALU` (CW). Left-knob push is `RM_TOGG` on RAISE2.

There is **no `RM_HUED` and no `RM_SATD` bound**: hue and sat can only be stepped one way
(they wrap). Core inverts every RM_* key when Shift is in `get_mods()` at release
(`quantum/process_keycode/process_rgb_matrix.c`, the `shifted` checks).

RM_* keys fire on key **release** (`process_rgb_matrix.c`: `if (!record->event.pressed)`),
not press. A keycode that seems "consumed but inert" is not proof it fired.

Reaching RAISE2:
- **Triple-tap `K`** → RAISE2 as a **one-shot**: it drops back to base after the next
  key or knob event. Ideal for "one adjustment, then look" (step-and-preview).
- **Double-tap `K`** → one-shot RAISE, then press **`TO(_RAISE2)`** (on the `H` key of the
  RAISE layer) → **sticky** RAISE2 until `TO(_QWERTY)`. Use for many taps in a row.

**The RAISE2 indicator paints the whole board solid TEAL** (`rgb_matrix_indicators_advanced_user`,
`HSV_TEAL`, clamped to `RGB_MATRIX_MAXIMUM_BRIGHTNESS` 150 so it reads as a pale teal).
Consequence: **nothing about the effect or colour is visible while on RAISE2.** All
adjustments are made blind, then verified after `TO(_QWERTY)`. Any "it went teal" report
made while on RAISE2 is the overlay, not the effect. A teal that *sparkles/twinkles* is NOT
the overlay (the overlay is uniform and still).

## 3. Effect mode order (deterministic)

Mode numbers = include order of `quantum/rgb_matrix/animations/rgb_matrix_effects.inc`,
keeping only effects enabled in `keyboard.json` `rgb_matrix.animations` (confirmed against
the compiled `ENABLE_RGB_MATRIX_*` set in `.build/obj_szrkbd_bcorne_dexter/src/info_config.h`),
with `SOLID_COLOR` always present at 1 and custom effects appended last.
`RGB_MATRIX_EFFECT_MAX` = 31.

```
 1 SOLID_COLOR              hue ✓ still            16 CYCLE_OUT_IN         rainbow (ignores hue)
 2 ALPHAS_MODS              hue ✓ still, 2-tone    17 CYCLE_OUT_IN_DUAL    rainbow
 3 GRADIENT_UP_DOWN         hue ✓                  18 CYCLE_PINWHEEL       rainbow
 4 GRADIENT_LEFT_RIGHT      hue ✓                  19 CYCLE_SPIRAL         rainbow
 5 BREATHING                hue ✓                  20 DUAL_BEACON          rainbow
 6 BAND_SAT                 hue ✓                  21 RAINBOW_BEACON       rainbow
 7 BAND_VAL                 hue ✓                  22 RAINBOW_PINWHEELS    rainbow
 8 BAND_PINWHEEL_SAT        hue ✓                  23 RAINDROPS            hue ± random
 9 BAND_PINWHEEL_VAL        hue ✓                  24 JELLYBEAN_RAINDROPS  random colours
10 BAND_SPIRAL_SAT          hue ✓                  25 HUE_BREATHING        hue ✓ (drifts)
11 BAND_SPIRAL_VAL          hue ✓                  26 HUE_PENDULUM         hue ✓ (drifts)
12 CYCLE_ALL                IGNORES hue, uniform   27 HUE_WAVE             hue ✓ (drifts)
13 CYCLE_LEFT_RIGHT         rainbow                28 PIXEL_RAIN           IGNORES hue, random, pale
14 CYCLE_UP_DOWN            rainbow                29 PIXEL_FLOW           IGNORES hue, random, pale
15 RAINBOW_MOVING_CHEVRON   rainbow                30 PIXEL_FRACTAL_OK     hue ✓  (custom; the target)
```

Builtin `pixel_fractal` is disabled in `keyboard.json` (it never paints the middle column on
this 7-col matrix); `PIXEL_FRACTAL_OK` in `keymaps/dexter/rgb_matrix_user.inc` is the fixed
copy. Step wrap: `RM_NEXT` from 30 → 1; `RM_PREV` from 1 → 30 (`rgb_matrix_step_reverse_helper`).

## 4. The left knob double-steps (skips the fractal)

Observed on hardware: **one detent of the left knob sends two (sometimes three) RM_PREV/RM_NEXT
events.** Compiled `ENCODER_RESOLUTION` is 2 (`keyboard.json`), consistent with a 4-pulse-per-detent
encoder; the stock-firmware note in `szrkbd_backup/HARDWARE_NOTES.md` inferred 2.

Consequence: from `SOLID_COLOR` (1), one CCW detent lands on **28/29** (pale random twinkle), not 30;
from 29, one CW detent lands on 1. **The knob skips mode 30 every time.** This is why the user
could never reach the fractal by knob and repeatedly landed on hue-ignoring effects.

**Rule: step effects with the `M` key (`RM_NEXT`), never the knob.** From the pale random
twinkle (28/29), one or two `M` taps reaches 30. From `SOLID_COLOR`, 29 `M` taps reaches 30
(or one CCW detent to land on 29, then `M` once).

Fix candidate (NOT applied, NOT tested): `ENCODER_RESOLUTION` 4 in `keyboard.json`.

## 5. Hue stepping

- `RGB_MATRIX_HUE_STEP` = 8 (core default, no override), 32 taps = one full lap.
  `RGB_MATRIX_SAT_STEP`/`VAL_STEP`/`SPD_STEP` = 16. Max brightness clamp 150.
- Only `RM_HUEU` is bound, so hue is a one-way wheel. **Never count taps from an assumed
  starting hue** — identify the *current* colour first, then count. Reference:
  the hue-map artifact https://claude.ai/artifact/AQJDBZ2XMsHrpiiVvfScYp (32 swatches in tap order,
  direction toggle, tap counter).
- Direction: the one clean measurement (teal ≈128 → orange ≈32 in 12 taps) fits hue
  **decreasing** per tap. Earlier "evidence" for that was confounded by being on hue-ignoring
  effects, and a stuck Shift was ruled out (no capitals typed). Treat direction as
  **unresolved; measure it on the board** rather than asserting either way.
- QMK targets: `HSV_ORANGE` hue 21 (nearest tap 24), rust ≈ 8–16, green 85, teal 128, purple 191.
- "Sat does nothing" when sat is already 255: `RM_SATU` clamps. Not a bug.

## 6. How to identify what effect you are on (by eye)

Only trust these tests, never "it looks solid":

- **`SOLID_COLOR`**: uniform, still, **and comma recolours it**. A frozen `CYCLE_ALL` (mode 12,
  speed near 0: `hsv.h = time`, time barely advances) is uniform, still, and looks identical
  — but ignores comma. Crank speed up (`;`) first so cyclers visibly move before hunting for solid.
- **`PIXEL_FRACTAL_OK`**: one colour (the config hue), pixels lighting in **mirrored pairs
  marching outward from the centre of each half**. Comma recolours it.
- **`PIXEL_RAIN` / `PIXEL_FLOW`**: random twinkle, ~50% lit, **per-pixel random hue with sat
  127–255** → reads as a pale/whitish spray with a cast. Ignores comma. Comma will still move
  `SOLID_COLOR`'s colour because config is shared — that is how to prove you're on one of these.
- The **brightness knob (right) works on every effect**; hue-ignoring effects still pass
  `config.v` through. "Brightness works but hue doesn't" = you are on 12, 13–22, 24, 28 or 29.

## 7. Recommended permanent fixes (proposed, not applied)

1. Make the preferred look the compiled default in `keymaps/dexter/config.h`:
   `RGB_MATRIX_DEFAULT_MODE RGB_MATRIX_CUSTOM_PIXEL_FRACTAL_OK`, `DEFAULT_HUE` ≈ 21–32,
   `DEFAULT_SAT 255`, `DEFAULT_VAL` and `DEFAULT_SPD` to taste; needs a flash plus one
   EEPROM clear (EE_CLR is on the leader layer) to take effect.
2. Bind `RM_HUED` and `RM_SATD` on RAISE2 so hue/sat are two-way.
3. `ENCODER_RESOLUTION` 4 so one detent = one effect step (verify on hardware).

## 8. Traps that cost a whole session (do not repeat)

- Asserting "you're on the wrong layer" or "that's the overlay" without a discriminating test.
  A sparkling teal is not the overlay.
- Giving blind hue tap counts from an assumed start hue. Match colour to a swatch first.
- Telling the user "one knob click = the fractal". The knob double-steps; use `M`.
- Treating "static solid colour" as `SOLID_COLOR`. Only comma-recolours proves it.
- Treating "no character typed" as proof an RM_* key fired. A dead slot is also silent.
- Reasoning one data point at a time when the code makes the answer deterministic (mode table,
  step sizes, wrap logic). Compute the table first.
