# SZRKBD "BCORNE" (4x6 Corne w/ knobs) — hardware spec

Reverse-engineered from the stock Vial firmware (`stock_bcorne.bin` — a full 256 KB
flash dump based at `0x08000000`: bootloader at file offset 0, app @ `0x08010000` =
file offset 0x10000. All flash addresses below are absolute).
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
#define MATRIX_ROW_PINS        { C8, C7, B2, A6, A5 }
#define MATRIX_COL_PINS        { B13, B14, B15, C6, C9, A8, C12 }

// RIGHT half (matrix rows 5-9)
#define MATRIX_ROW_PINS_RIGHT  { A1, B7, C5, B0, B1 }
#define MATRIX_COL_PINS_RIGHT  { B8, C10, C8, C7, C6, B15, B14 }

#define DIODE_DIRECTION COL2ROW
```

(2026-08-12 correction, verified electrically on hardware: the first extraction
grouped the left half's 12-pin array rows-first like the right half's, but the
binary stores the LEFT array cols-first (7 cols at 0x08021198, then 5 rows) while
the RIGHT array at 0x0802008C is rows-first. Lists above are the corrected ones.)

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
the Vial definition (xz stream @ 0x08030600 in the full-flash dump) — each visual key
is labeled "row,col", giving the full physical->matrix map for building the LAYOUT
macro. (An earlier revision of these notes claimed the knobs map to virtual matrix
positions (4,4)/(4,5)/(9,1)/(9,2); wrong — those are real thumb keys drawn rotated.
The knobs are true quadrature encoders, declared in the Vial def as encoder 0/1 via
the "N,D...e" key labels. See "Encoders" below.)

## Encoders — 1 quadrature knob per half, DIFFERENT pads per half
Standard QMK encoder driver. `.data` init image holds encoders_pad_a = { B9 },
encoders_pad_b = { B8 } (flash 0x0802133C -> RAM 0x20000E04/0x20000E08).
encoder_init @ 0x080190AC then checks isLeftHand (RAM 0x20000D98) and, for the
RIGHT half only, overwrites pad_b = B4 (literal 0x40020404) and pad_a = B6
(that literal + 2) at 0x080190C6..D0. So:

```
// LEFT knob             RIGHT knob
pad A = B9               pad A = B6
pad B = B8               pad B = B4
```

No pin conflicts: B8 is an encoder pad only on the left half and a matrix col
only on the right half. Encoder update fn (0x080190F0) accumulates LUT steps
(table @ 0x08020B00) and fires at >= +2 / <= -2 => **ENCODER_RESOLUTION = 2**
(QMK default 4 would drop every other detent).

## RGB LED layout — g_led_config equivalent @ 0x080211C8
70-byte matrix->LED-index table (rows stored interleaved L0,R0,L1,R1,...), then
58 (x,y) byte pairs (absolute 0-224/0-64 coords), then 58 flag bytes (all 0x04,
LED_FLAG_KEYLIGHT). LED chain: 0-28 = left half, 29-57 = right half; the two
encoder-push keys (QMK matrix (3,6) and (8,0)) have NO_LED. Matches
keyboards/szrkbd/bcorne/keyboard.json's rgb_matrix layout exactly.

## USB IDs (stock)
VID 0x6401 ("LG Studio"-ish vendor), PID 0x45D4, product "BCORNE".
Vial UID 0x4589d8fac72a3689. Bootloader VID 0x2398 PID 0x005D "PlumBootloader".
