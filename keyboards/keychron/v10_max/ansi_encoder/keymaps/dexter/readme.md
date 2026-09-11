# Keychron V10 Max ANSI knob — `dexter` keymap

Recovered from a flash dump of the original custom firmware (built 2024-07-09 from Keychron's
`wireless_playground` fork at commit 8e390f92a2 with Ubuntu's arm-none-eabi GCC 13.2.1). The full
evidence trail lives in `keychron_v10max_backup/` at the repository root:

- `ANALYSIS.md` — acquisition, image layout, toolchain/base identification, every custom function
  with address, size, behavior and evidence, config constants, features, raw-HID conclusion.
- `RECONSTRUCTION_SPEC.md` — this keymap line by line with a confidence tag and evidence pointer,
  the unavoidable differences, and the hardware test checklist.
- `tools/final_compile_compare.py` — regression test: rebuild with GCC 13.2.1 and compare every
  user function (masked for addresses), both tables, the tap-dance table and the static layout
  against `dump_a.bin`. At the time of writing: all 17 user-TU functions identical, tables
  byte-identical, 41 config-bearing core functions identical.

## Layers

| # | name      | content                                                                 | indicator |
|---|-----------|-------------------------------------------------------------------------|-----------|
| 0 | `_QWERTY` | base; `OSL(_LEADR)` on the grave position, `OSM(MOD_LSFT)` at caps, `OSM(MOD_RSFT)` at `;`, Tab at LShift, Caps Lock at left Option, `OSM(MOD_LGUI)` at left Cmd, `TD(LAYR_DOWN)` on Fn, `OSL(_RAISE)` on right Cmd | heatmap (animation) |
| 1 | `_LOWER`  | Ctrl chords on letters, Alt+arrows, arrows on J K L ;, `DOT_SLS` (`./`) on `,`, `DIR_UP` (`../`) on `.`, `TO(0)` on right Cmd | green |
| 2 | `_RAISE`  | symbols and F-keys, `TO(0)` / `TO(_RAISE2)` on the bottom row            | blue |
| 3 | `_RAISE2` | Keychron Fn layer: RGB keys, BT hosts 1-3, 2.4 GHz, battery level, `QK_BOOT` on Esc | orange |
| 4 | `_MOUSE`  | mouse keys (kinetic), `TD(LAYR_DOWN)`, `TO(0)`                           | teal |
| 5 | `_LEADR`  | `QK_LEADER` on grave, Ctrl+Shift chords, Alt+arrows, `DOT_SLS`, `TO(0)` / `TO(_LEADR)` | red |

Encoder: volume on layers 0 and 2, RGB brightness on 1 and 5, nothing on 3 and 4.

## Behaviors

- **Fn key (`TD(LAYR_DOWN)`):** tap = one-shot `_LOWER`; tap twice with nothing in between = lock
  `_LOWER`; tap while `_LOWER` is locked = back to a one-shot; tap while on `_MOUSE` = one-shot
  `_LOWER` then return to `_MOUSE`; hold (175 ms) = lock `_MOUSE`; double tap = lock `_LOWER`.
- **Leader** (`OSL(_LEADR)`, then grave, 525 ms per key): `F` -> GUI+P, GUI+K, GUI+' (the two `F`
  bindings in the original both fire; reproduced as found); `A Q` -> Ctrl+A, Z, Q, Enter; `Y` ->
  Ctrl+X, Y, Enter; `LCtrl I` -> Ctrl+Alt+I; `J` -> GUI+P; `Del` -> GUI+Up+Left. All LEDs flash
  magenta while a sequence is being entered.
- **One-shot mods:** `ONESHOT_TAP_TOGGLE 2` (double tap locks). A pending Shift paints the board
  white, a pending GUI yellow; Caps Lock toggled from this keyboard paints it white.
- **Boot:** always starts on layer 0 (the Mac/Win DIP switch only matters when toggled at runtime)
  and (re)selects the typing-heatmap RGB effect.

## Known differences from the original firmware

- Compiler: the stock QMK toolchain (gcc 15.2) changes code bytes but not behavior; the xpack
  GCC 13.2.1 build reproduces the original code generation. Library code (newlib) always differs.
- Fork revision: this branch builds on `wireless_playground` HEAD, so Keychron's later wireless
  and RGB fixes are included. An exact-era build from commit 8e390f92a2 is kept in
  `keychron_v10max_backup/refs/exact8e390f92_dexter_gcc13.bin`.
- Flashing erases the emulated EEPROM sector, so RGB brightness/hue/speed return to compiled
  defaults (the original's runtime values are recorded in `eeprom_recovered.md`).
- Quirks kept on purpose: the double `F` leader binding; the inert `check_unlock_osm` helper;
  `NK_TOGG` keys that do nothing because `MAGIC_ENABLE = no`.

## Build and flash

```sh
cd ~/code/qmk-keychron
qmk compile -kb keychron/v10_max/ansi_encoder -km dexter -j 8
# bootloader: switch on Cable, unplug, hold the PCB reset button under the spacebar, plug in
dfu-util -a 0 -d 0483:df11 -s 0x08000000:leave -D keychron_v10_max_ansi_encoder_dexter.bin
```

Never hold Esc or the knob while plugging in (bootmagic erases the EEPROM). Rollback to the exact
original image: `dfu-util -a 0 -d 0483:df11 -s 0x08000000 -D keychron_v10max_backup/dump_a.bin`.
