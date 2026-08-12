# SZRKBD BCORNE (4x6 Corne with knobs)

A column-staggered split (5x7 matrix per hand, 60 keys total) with two rotary
encoders/knobs and per-key RGB, sold by SZRKBD as a "4x6 Corne with knobs".

* Keyboard Maintainer: [dexterds14](https://github.com/dexterds14)
* Hardware Supported: SZRKBD BCORNE, STM32F401 (256 KB), Plum UF2 bootloader

This configuration was reverse-engineered from the stock Vial firmware. See
`szrkbd_backup/HARDWARE_NOTES.md` in the repo root for the full extraction
(matrix pins, handedness, split transport, RGB) and the evidence behind each value.

## Hardware summary

| Item | Value |
|------|-------|
| MCU | STM32F401 (F401RC-class, 256 KB), **16 MHz HSE crystal** |
| Bootloader | Plum UF2 (tinyuf2-compatible), app @ `0x08010000` |
| Matrix | 5 rows x 7 cols per hand, `COL2ROW` |
| Left rows/cols | rows `C8 C7 B2 A6 A5`, cols `B13 B14 B15 C6 C9 A8 C12` |
| Right rows/cols | rows `A1 B7 C5 B0 B1`, cols `B8 C10 C8 C7 C6 B15 B14` |
| Handedness | `SPLIT_HAND_PIN C1`, low = left |
| Split link | full-duplex USART1, TX `A9` / RX `A10` |
| RGB | 58 per-key WS2812 (29/half) on `A7` via TIM3_CH2 + DMA; the two encoder-push keys have no LED |
| Encoders (TODO) | 1 knob per half (pins not yet extracted) |

Bring-up notes (2026-08-12): the original reverse-engineered config had two
fatal errors, both fixed in this tree and verified on hardware by electrical
probing:

* The crystal is 16 MHz, not the 8/25 MHz QMK's generic F401 boards assume.
  `board.h`/`mcuconf.h` mirror the stock firmware's exact PLL setup
  (PLLM=16, PLLN=192, PLLP=4, PLLQ=4 -> 48 MHz SYSCLK/USB). With the wrong
  PLL the firmware hangs before USB and the board appears dead.
* The left half's extracted row/col pin lists were scrambled (rows and cols
  mixed together). The right half's extraction was correct as-is.
  `szrkbd_backup/HARDWARE_NOTES.md` still shows the old wrong left-half lists.

## Building

    qmk compile -kb szrkbd/bcorne -km default

## Flashing

The Plum UF2 bootloader appears as a USB mass-storage drive named `STM32F4Plum`.

1. Enter the bootloader: with this firmware, FN+Esc (left half) or FN+Backspace
   (right half) — `QK_BOOT` reboots whichever half is on USB. Hardware fallback
   that always works: double-tap the reset button. (Note: the stock Vial
   firmware's Security -> Reboot to bootloader is a no-op on this board, and it
   ships with no `QK_BOOT` key.) The `STM32F4Plum` drive mounts.
2. Drag the built `.uf2` onto that drive, or run `keyboards/szrkbd/bcorne/flash.sh`
   which waits for the drive and copies automatically. Note that plain
   `qmk flash` can build but never deploys on this board: it detects UF2
   drives by the standard `INFO_UF2.TXT` file, and Plum names its info file
   `PLUM_UF2.TXT`, so the drive is never recognized ("Waiting for drive to
   deploy" forever). The board reboots into the new firmware after the copy.

The board is effectively unbrickable: the bootloader lives in a separate 64 KB
flash region and cannot be overwritten by an app-region flash.

## Not yet implemented

* **Encoders** - the two knobs are wired but their GPIO pins were not extracted yet.
* **RGB** - WS2812 data is on `A7` (TIM3_CH2 PWM); RGB Matrix needs the per-key LED
  layout before it can be enabled.
