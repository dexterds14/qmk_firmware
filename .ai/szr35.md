# SZRKBD SZR35 ("SW36"): hardware facts, flashing, and the dexter keymap

Read this before building, flashing or changing `keyboards/szrkbd/szr35/`.
Established on 2026-11-25 from full dumps of both halves' stock flash
(`szrkbd_backup/szr35/`) and on-hardware testing. File refs may drift.

## 1. What the board is

- 36-key split (3x5 + 3 thumbs per half), STM32F401, 16 MHz crystal. Sold by
  Hardtochooseone / SZRKBD. Stock firmware is Vial: USB `3601:45d4`,
  manufacturer and product both "Hardtochooseone", Vial definition name "SW36".
- The stock USB IDs, the IDs inside the Vial definition (`45D4:1A32`) and the
  tree's IDs (`44DF:45D4`) all differ, and the Vial UID is the same one the
  bcorne's stock firmware uses. Identify the board by its matrix, not its IDs.
- Both halves run byte-identical stock firmware; the image holds both hands'
  pin tables and picks one from the handedness pin (`C7`, high = left).

## 2. Flash layout — do not violate

| Sector | Address | Contents |
|---|---|---|
| 0-1 | `0x08000000` | Plum UF2 bootloader (byte-identical to the bcorne's) |
| 2 | `0x08008000` | blank |
| 3 | `0x0800C000` | emulated EEPROM (`WEAR_LEVELING_EFL_FIRST_SECTOR 3` in `config.h`) |
| 4 | `0x08010000` | application, 64 KB |
| 5 | `0x08020000` | blank; may not exist (see §4) |

- The tree builds with `"bootloader": "tinyuf2"`, `ld/STM32F401xC.ld`
  (`_board_dfu_dbl_tap = 0x2000FC00`) and `UF2_FAMILY = 0xABCDF401`
  (keyboard-level `rules.mk`). Upstream's `stm32-dfu` setting links at
  `0x08000000` and **overwrites Plum** if flashed over ROM DFU.
- Option bytes: readout protection off, nothing write-protected. Nothing but
  the address in the command protects the bootloader.

## 3. Flashing and recovery

- Normal: `QK_BOOT` (RAISE2 `Q`/`P` in the dexter keymap), then
  `keyboards/szrkbd/szr35/flash.sh .build/szrkbd_szr35_<keymap>.uf2`. Flash
  **both** halves with the same build: the split handshake depends on the
  enabled sync features, so mismatched halves do not talk.
- `qmk flash` never finds the Plum drive (`PLUM_UF2.TXT`, not `INFO_UF2.TXT`).
- Reset pads: double-tap with the second tap inside ~100 ms. Plum decides from
  a RAM word at `0x2000FC00`; no GPIO is involved.
- On **stock** firmware every software route to the bootloader is dead (the
  jump is an empty stub; bootmagic wipes the keymap and returns). Hardware only.
- ROM DFU (`0483:df11`, via BOOT0) always works. Raw app image at
  `0x08010000`: `dfu-util -d 0483:df11 -a 0 -s 0x08010000:leave -D app.bin`.
- Back to stock: write the first 128 KB of `szrkbd_backup/szr35/stock_szr35_<side>.bin`
  at `0x08000000` over ROM DFU (the upper 128 KB of the dumps is blank).
- udev: `/etc/udev/rules.d/50-szr35.rules` on the user's machine grants hidraw
  and DFU access; `dfu-util` and `qmk` live in `~/.local/bin`.

## 4. App size budget

The linker script caps flash at 128 KB (the readme says F401RB), which leaves
the app exactly sector 4 = 64 KB. The dexter build is ~49 KB. Both stock dumps
read a full 256 KB without error, so the chip may really have 256 KB, but that
is **unproven**: before raising the cap, write and read back a test pattern in
sector 5 over ROM DFU.

## 5. Keyboard-level settings copied from stock (verified by disassembly)

All 40 direct matrix pins, `C7` handedness, USART1 half-duplex on `A9` at
19200 baud (`split.serial.speed` 5; the line is open-drain with no internal
pull-up), WS2812 on `A7` via TIM3_CH2 + DMA at **80 kHz** (`WS2812_PWM_FREQUENCY`),
brightness cap 50, no split watchdog. The LED order inside each row
(`rgb_matrix.layout`) differs from stock and is **not yet confirmed on
hardware**; full-board overlays do not care, position-based effects do.

## 6. The dexter keymap

A port of `keyboards/szrkbd/bcorne/keymaps/dexter/`; read `.ai/bcorne-rgb.md`
for the RGB behaviour (same animation list, so the same effect-mode table;
there are no knobs here, RGB brightness is on RAISE2 `U`/`I`). Differences:

- Two extra **locked** layers below the bcorne ones in the stack: `_NUM`
  (double-tap `L`, coral; digits on the top row, nav on the right outer columns) and
  `_FN` (`H` from `_NUM`; F-keys, volume/media, tab switching). They must stay
  below LOWER/RAISE so a one-shot from inside `_NUM` overrides it.
- `L` is a tap-dance key: the leader coupling in `AGENTS.md` applies
  (`td_base_keycode()`, `is_td_key()`).
- Leader sequence for sway lock is `C, I` (the bcorne's used its centre Ctrl key).
- Default look is `RAINDROPS` from hue 165 at speed 230; indicator pulses are
  rescaled to the brightness cap of 50.
- `keymap-diagram.html` is generated: edit `keymap.c`, then run
  `keymaps/dexter/gen-diagram.py` (it fails on any keycode it has no label for).
