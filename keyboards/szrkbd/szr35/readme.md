# SZR35 

![szr35](https://i.ibb.co/vvQPBTF9/szr35.jpg)

*The **SZR35** is a minimalist 36-key split keyboard. It follows the popular 3x5+3 layout and is aimed at users who value ergonomic typing, portability, and open-source firmware flexibility. It ships with Vial-compatible firmware and is built around an STM32 microcontroller.*

* Keyboard Maintainer: [diegorodriguezv](https://github.com/diegorodriguezv)
* Hardware:
  * **Microcontroller:** STM32F401RBT6 (Cortex-M4, 256KB Flash, 64KB RAM)
  * **Backlighting:** Addressable RGB (WS2812 or similar)
  * **Connection:** USB-C on both halves, TRS jack for interconnect
* Hardware Availability:
  * [HardToChooseOne](https://hardtochooseone.com) on [Amazon](https://www.amazon.com/gp/product/B0DD69RGHK).
  * Alternatively sold from other websites under the SZRKBD brand.

Make example for this keyboard (after setting up your build environment):

    make szrkbd/szr35:default

If you want you can use the keymap that came with the keyboard from factory:

    make szrkbd/szr35:factory

## Flashing

The board ships with the vendor's **Plum UF2 bootloader** in the first 64 KB of
flash (the same one as `szrkbd/bcorne`); the firmware is linked at `0x08010000`
and built as a `.uf2` with family id `0xABCDF401`. Both halves take the same
firmware and must run the same build.

    qmk compile -kb szrkbd/szr35 -km default
    keyboards/szrkbd/szr35/flash.sh .build/szrkbd_szr35_default.uf2

`flash.sh` waits for the bootloader drive (`STM32F4Plum`) and copies the file.
Plain `qmk flash` / `make ...:flash` never finds the drive, because Plum names
its info file `PLUM_UF2.TXT` instead of `INFO_UF2.TXT`.

## Bootloader

* **Keycode**: `QK_BOOT` reboots the half that is on USB into the Plum drive.
* **Bootmagic**: hold the top-left key (left half) or top-right key (right
  half) while plugging in.
* **Reset pads**: double-tap reset; the second tap must land within roughly
  100 ms of the first. The drive leaves by itself after about a minute.
* **Stock firmware**: none of the software routes work on it (its bootloader
  jump is an empty stub, and bootmagic only wipes the keymap). Use the reset
  pads, or the STM32 ROM DFU (`0483:df11`) via BOOT0.

Do **not** write a firmware image at `0x08000000` over ROM DFU: that overwrites
the Plum bootloader. To flash over ROM DFU, write the raw app image at
`0x08010000` (`arm-none-eabi-objcopy -O binary <elf> app.bin`, then
`dfu-util -d 0483:df11 -a 0 -s 0x08010000:leave -D app.bin`).
