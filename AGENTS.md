# AGENTS.md — dexter-ds branch notes

This is a fork of `qmk_firmware`. All custom work lives on the `dexter-ds`
branch and is confined to **one keyboard**:

```
keyboards/handwired/dactyl_manuform/5x6/
├── keyboard.json                 # hardware config (modified vs master)
└── keymaps/default/
    ├── keymap.c                  # all keymap logic (~1100 lines added)
    ├── config.h                  # feature/timing config
    ├── rules.mk                  # feature flags, LTO
    └── glcdfont_custom.c         # trimmed OLED font (space..'Z') to save ~1KB flash
```

Everything else in the repo is upstream QMK. Do not modify `quantum/` or other
core code — all customization happens in the keymap directory.

## Hardware (keyboard.json changes vs master)

Handwired split dactyl manuform 5x6, ATmega32u4 (AVR, caterina bootloader),
**left half is master** (`MASTER_LEFT` in config.h).

- `matrix_pins`: rows/cols **swapped** relative to upstream (this build's wiring).
- Split serial on **D2** (upstream: D0), soft serial.
- WS2812 RGB on **F4**, bitbang driver, **24 LEDs total** (12 per half).
- Bottom two right-thumb key positions swapped in the layout to match the build.
- `command`, `extrakey`, locking resync disabled at board level
  (extrakey re-enabled in the keymap's rules.mk).

## THE critical constraint: LTO vs split serial

**Read the comment blocks in `rules.mk` and `config.h` before touching
anything related to RGB, split sync, or LTO.** Summary:

- `LTO_ENABLE = yes` + soft serial speed 5 works, BUT the master→slave
  payloads for **mods / LED state / rgblight sync corrupt** (value-dependent
  byte desync). Key events and **layer-state sync are reliable**.
- Sidestep architecture (the only thing that works on hardware):
  - `RGBLED_SPLIT` intentionally NOT defined → no rgblight split sync.
  - Each half renders the full LED buffer locally; the slave derives layer
    colors from `layer_state` (`apply_rgb_layer_state()` + a poller in
    `housekeeping_task_user()` in keymap.c).
- **Do NOT re-attempt** (both failed on hardware, 2026-07, see git history):
  - CRC-verified RGB sync via user RPC — locks up the slave (AVR ISR runs RPC
    callbacks before payload receive).
  - `READ_WRITE_*_ADJUST` serial timing recalibration — no working window.
- Full-revert fallback if the link breaks: LTO off + serial speed 0.

## Keymap architecture (keymap.c)

### Layers
| # | Layer | Purpose |
|---|-------|---------|
| 0 | `_QWERTY` | base |
| 1 | `_LOWER` | ctrl-combos / nav; can be "locked" (moved-to) |
| 2 | `_RAISE` | symbols / F-keys |
| 3 | `_RAISE2` | media / arrows / `QK_BOOT` |
| 4 | `_MOUSE` | mouse keys (kinetic mode) |
| 5 | `_LEADR` | one-shot layer holding `QK_LEAD` + shortcut chords |
| 6–8 | `_CAPSIND` / `_ALTLKIND` / `_LOWLKIND` | **phantom indicator layers** |

`LAYER_STATE_16BIT` is set to fit the 9 layers.

**Phantom layers** are fully transparent, never used for key lookup. Their
bits in `layer_state` are the master→slave signal for caps lock, alt
mod-lock, and lower layer-lock indicators (OLED/RGB on the slave), because
layer-state sync is the only channel that survives LTO uncorrupted.
`layer_state_set_user()` re-asserts them from master-local flags after any
`layer_clear()`/`layer_move()`.

### Tap dances
Letters S, D, F, G, H, J, K, V, Q are `TD(...)` keys (one-shot mods, caps
toggle, layer moves, etc.), with a fast-typing detector
(`FAST_TYPING_THRESHOLD`) that passes taps through during quick typing.
Triple-tap D toggles an **alt mod-lock**; double-tap F/K do layer moves.
`ONESHOT_TAP_TOGGLE 2` — double-tapping an `OSL` key **locks** that layer.

### Leader key
- `QK_LEAD` lives on the `_LEADR` layer (reached via `OSL(_LEADR)` thumb keys).
  Sequences are defined in `leader_end_user()` with plain keycodes (`KC_H`...).
- QMK's leader core records **raw TD keycodes** (only MT/LT are unwrapped), so
  a `process_record_user()` intercept translates TD keys to their base letter
  via `td_base_keycode()` while a sequence is recording, feeds
  `leader_sequence_add()`, and consumes the event (also suppressing the dance).
- **Coupling: if you add/change/remove a tap-dance key, update the
  `td_base_keycode()` switch** or leader sequences on that key silently break.
- Sequences must be typed on `_QWERTY` (after the OSL one-shot is consumed);
  a locked `_LEADR` layer resolves sequence keys to the wrong keycodes.

### RGB / OLED indicators
- RGB layer colors come from `my_rgb_layers[]`; **beware: the `enum rgb_layer`
  indices do not match the color comments** in the array (e.g. `RGB_LEADER=1`
  is actually magenta, not pink). Trust the array order, not the comments.
- OLED: 128x32, rotated 270°, custom trimmed font (`OLED_FONT_END 90`, so
  **only chars up to 'Z' render** — no lowercase). Indicators for caps/shift/
  sway-mod/leader plus per-layer banners; phantom-layer bits are masked out of
  `get_highest_layer()` or they'd hit the `ERR!` case.

## Build / flash

```sh
qmk compile -kb handwired/dactyl_manuform/5x6 -km default
qmk flash   -kb handwired/dactyl_manuform/5x6 -km default   # caterina/avrdude
```

`QK_BOOT` is on the `_RAISE2` layer for entering the bootloader; `EE_CLR` is
on `_LEADR`.

**Flash budget is tight**: ~85% used (≈4KB free) as of 2026-07. Check the
size line after every build; the trimmed OLED font and disabled features
(console, magic, space cadet, NKRO, audio…) exist to stay under the limit.
LTO is load-bearing for size — see the constraint section above before
considering turning it off.
