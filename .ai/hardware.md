# Hardware facts (Keychron V10 Max, ansi_encoder)

Sourced from the fork's board files and verified against the flash dump / product photo.

## MCU / flash / bootloader
- **STM32F401**, linked as **F401xC** (256 KB flash, 64 KB RAM). Runtime USB **VID 0x3434 / PID 0x09A0**, product string "Keychron V10 Max".
- Bootloader: **stm32-dfu** (ST ROM), DFU USB ID **0483:df11**, app at `0x08000000`.
- Flash map (fork `STM32F401xC.ld`): vectors in sector 0; **sector 1 (0x08004000, 16 KB) reserved for the emulated EEPROM**; code from 0x08008000.

## Matrix / layout
- Matrix **6 rows x 18 cols**, `DIODE_DIRECTION ROW2COL`.
- Layout macro **`LAYOUT_ansi_89`** (89 keys). Alice split; within every matrix row, matrix-column order == physical left-to-right order, and the Alice split falls between matrix cols 7 and 8. Unused matrix cells: [0,15][0,16][1,15][1,16][2,7][2,16][3,7][3,15][3,16][4,2][4,15][4,17][5,3][5,5][5,8][5,10][5,12][5,13][5,14].
- The left macro column keys are M1..M5 at matrix [1,0],[2,0],[3,0],[4,0],[5,0]; the knob is [0,0]. Split-B at [4,7] (outer/left) and [4,8] (inner/right). Two spacebars at [5,6] and [5,9].
- One rotary encoder (`NUM_ENCODERS` 1), pins B15/B14, `ENCODER_MAP_ENABLE` on.
- DIP switch (pin A8): Mac base = layer 0, Win base = layer 2 (stock `dip_switch_update_kb`).

## RGB
- **88 LEDs**, two **SNLED27351** drivers over **SPI** (`snled27351_spi`). `RGB_MATRIX_KEYPRESSES` + `RGB_MATRIX_FRAMEBUFFER_EFFECTS` enabled (typing heatmap works).
- `rgb_matrix_set_color(i, r, g, b)` writes **raw PWM** — NOT scaled by the brightness knob (`rgb_matrix_config.hsv.v`). Only HSV-based effects get scaled.
- Battery/indicator LED sets (from `keychron/v10_max/config.h`): `BAT_LEVEL_LED_LIST {17..26}` (number-row), caps-lock at LED index 48, BT host LEDs 17/18/19, 2.4G LED 20.

## Wireless (LKBT51)
- Bluetooth + 2.4 GHz via the **LKBT51** module (`LK_WIRELESS_ENABLE`). Reset pin C4.
- **The battery fuel gauge lives on the LKBT51, not the MCU** — there is no MCU battery ADC. The MCU learns the voltage by querying the module (`battery_measure()` = `lkbt51_read_state_reg(0x05,0x02)`), which replies with a battery event. This only happens on wireless transport (see gotchas.md).
- USB power sense pin B0; charging-status pin **C14** (`BAT_CHARGING_PIN`, active-low = charging), readable by the MCU on the cable. `KEEP_USB_CONNECTION_IN_WIRELESS_MODE` is defined (USB stays enumerated in wireless).

## EEPROM
- Emulated EEPROM via **wear-leveling on embedded flash**, sector 1 at 0x08004000, backing 4096 / logical 2048. Bytes stored **bit-inverted**. Holds eeconfig (default layer, keymap_config/NKRO, rgb_matrix mode/hsv/speed). No VIA dynamic keymap (this firmware is non-VIA).
- Flashing a full `.bin` zero-fills sector 1, so **flashing resets eeconfig to compiled defaults** (RGB settings revert). Expected; same as Keychron's stock images.
