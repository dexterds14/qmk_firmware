# SZRKBD "BCORNE" (4x6 Corne w/ knobs) — hardware spec

Reverse-engineered from the stock Vial firmware (`stock_bcorne.bin`, app @ `0x08010000`).
All facts below were extracted from the binary via capstone disassembly, not guessed.

## MCU / flash
- **STM32F401** (256 KB flash, F401RC-class — app uses up to ~0x24000).
- ChibiOS-based QMK/Vial build.
- Bootloader: **Plum UF2** mass-storage bootloader @ `0x08000000` (64 KB). App @ `0x08010000`.
  Flashing = drag a `.uf2` onto the `STM32F4Plum` drive. Unbrickable (bootloader separate).
- Enter bootloader: Vial → Security → Reboot to bootloader, or `QK_BOOT`. Exit: power-cycle.

## Matrix — 5 rows x 7 cols per hand, DIODE_DIRECTION = COL2ROW
Rows driven low (output, BSRR), cols read via IDR with pullup. Asymmetric split.

```
// LEFT half  (matrix rows 0-4)
#define MATRIX_ROW_PINS        { B13, B14, B15, C6, C9 }
#define MATRIX_COL_PINS        { A8, C12, C8, C7, B2, A6, A5 }

// RIGHT half (matrix rows 5-9)
#define MATRIX_ROW_PINS_RIGHT  { A1, B7, C5, B0, B1 }
#define MATRIX_COL_PINS_RIGHT  { B8, C10, C8, C7, C6, B15, B14 }

#define DIODE_DIRECTION COL2ROW
```

## Handedness detection — SPLIT_HAND_PIN = C1
Fn @ 0x8014bd0: configures **C1** as input, delays, reads GPIOC IDR bit1.
Result = !C1 → stored as handedness flag; flag==0 ⇒ right half (matrix rows 5-9).
=> **C1 LOW = LEFT, C1 HIGH = RIGHT**.

```
#define SPLIT_HAND_PIN C1
#define SPLIT_HAND_PIN_LOW_IS_LEFT   // low = left (inverse of QMK default)
```

## Split transport — full-duplex hardware USART1
RCC APB2ENR bit4 (USART1EN) enabled. Pin AF config @ 0x801c4c2:
- **A9**  = USART1_TX (AF7)
- **A10** = USART1_RX (AF7)
Both pins AF7 ⇒ full-duplex (TX+RX crossed in the C-to-C interconnect cable).

```
#define SERIAL_DRIVER usart
#define SERIAL_USART_FULL_DUPLEX
#define SERIAL_USART_TX_PIN A9
#define SERIAL_USART_RX_PIN A10
// master detection appears USB-based -> likely also: #define SPLIT_USB_DETECT
```

## RGB (bonus) — WS2812 on A7 via TIM3_CH2 (PWM+DMA)
Fn @ 0x80191bc: A7 set to AF2 (TIM3_CH2), followed by DMA stream setup. "lighting":"vialrgb".

```
#define WS2812_DI_PIN A7
#define WS2812_PWM_DRIVER PWMD3
#define WS2812_PWM_CHANNEL 2
// (WS2812_PWM_COMPLEMENTARY_OUTPUT / TIM3_AF as needed)
```

## Logical layout (from extracted Vial definition)
matrix 10 rows x 7 cols. Left = rows 0-4, right = rows 5-9. Per-key positions are in
`vial_def.json` (scratchpad) — each visual key is labeled "row,col", giving the full
physical->matrix map for building the LAYOUT macro. Encoders/knobs mapped to virtual
matrix positions (4,4)/(4,5)/(9,1)/(9,2) etc.

## USB IDs (stock)
VID 0x6401 ("LG Studio"-ish vendor), PID 0x45D4, product "BCORNE".
Vial UID 0x4589d8fac72a3689. Bootloader VID 0x2398 PID 0x005D "PlumBootloader".
