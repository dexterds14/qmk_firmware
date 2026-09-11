# Dump triage: dump_a.bin

Generated 2026-09-11T01:26:44+00:00 by tools/dump_triage.py (stdlib heuristics; see script docstring).

| item | value |
|---|---|
| size | 262144 B (0x40000) |
| sha256 | `21c97cd5f838063db6218af8d918427f452299044275881a132948de93dd7e56` |
| flash base | 0x08000000 (file offset 0) |
| image end (last non-0xFF byte + 1) | 0x17F04 (flash 0x08017F04); 98052 B used, 164092 B erased tail |
| content end (last non-0xFF/0x00 + 1) | 0x17F04 |
| first non-fill byte after 0x200 | 0x4000 |
| last block classified as code ends at | 0x16700 (code/rodata boundary estimate, 256-B granularity) |
| .text end from disassembly (--code-end) | 0x16702 (flash 0x08016702): last `bx lr` at 0x16700, zero padding, .rodata from 0x16704 |

## Vector table (file 0x0)

| item | value | check |
|---|---|---|
| initial SP (word 0) | 0x20000400 | OK (SRAM 0x20000000..0x20010000, 8-aligned) |
| Reset (word 1) | 0x0800811D | OK (odd Thumb address inside image); file 0x811C, first bytes `70e700f000f8fee7` |
| entries (through last non-zero word) | 120 = 16 core + 104 IRQ, table 0x0..0x1DF | ChibiOS STM32F4xx cmparams.h: CORTEX_NUM_VECTORS 104 -> 120 entries = 0x1E0 B |
| plausible handler addresses | 119 of 119 (zero: 0, bad: 0) | |
| default (unhandled) handler | 0x0800811F used by 89 entries | |
| first non-zero byte after table | 0x4000 | zero fill expected up to 0x4000 (flash0 sector 0 = 16 KiB) |

Populated (non-default) vectors:

| idx | file off | name | handler |
|---|---|---|---|
| 1 | 0x004 | Reset | 0x0800811D |
| 11 | 0x02C | SVCall | 0x08013C15 |
| 18 | 0x048 | IRQ2_TAMP_STAMP | 0x08015EF5 |
| 19 | 0x04C | IRQ3_RTC_WKUP | 0x08015F5D |
| 22 | 0x058 | IRQ6_EXTI0 | 0x080148C5 |
| 23 | 0x05C | IRQ7_EXTI1 | 0x080148ED |
| 24 | 0x060 | IRQ8_EXTI2 | 0x08014915 |
| 25 | 0x064 | IRQ9_EXTI3 | 0x0801493D |
| 26 | 0x068 | IRQ10_EXTI4 | 0x08014965 |
| 27 | 0x06C | IRQ11_DMA1_Stream0 | 0x08014EB5 |
| 28 | 0x070 | IRQ12_DMA1_Stream1 | 0x08014EDD |
| 29 | 0x074 | IRQ13_DMA1_Stream2 | 0x08014F09 |
| 30 | 0x078 | IRQ14_DMA1_Stream3 | 0x08014F35 |
| 31 | 0x07C | IRQ15_DMA1_Stream4 | 0x08014F61 |
| 32 | 0x080 | IRQ16_DMA1_Stream5 | 0x08014F89 |
| 33 | 0x084 | IRQ17_DMA1_Stream6 | 0x08014FB5 |
| 39 | 0x09C | IRQ23_EXTI9_5 | 0x0801498D |
| 44 | 0x0B0 | IRQ28_TIM2 | 0x08014A61 |
| 56 | 0x0E0 | IRQ40_EXTI15_10 | 0x080149F1 |
| 57 | 0x0E4 | IRQ41_RTC_Alarm | 0x08015F95 |
| 63 | 0x0FC | IRQ47_DMA1_Stream7 | 0x08014FE1 |
| 72 | 0x120 | IRQ56_DMA2_Stream0 | 0x0801500D |
| 73 | 0x124 | IRQ57_DMA2_Stream1 | 0x08015035 |
| 74 | 0x128 | IRQ58_DMA2_Stream2 | 0x08015061 |
| 75 | 0x12C | IRQ59_DMA2_Stream3 | 0x0801508D |
| 76 | 0x130 | IRQ60_DMA2_Stream4 | 0x080150B9 |
| 83 | 0x14C | IRQ67_OTG_FS | 0x08015B5D |
| 84 | 0x150 | IRQ68_DMA2_Stream5 | 0x080150E1 |
| 85 | 0x154 | IRQ69_DMA2_Stream6 | 0x0801510D |
| 86 | 0x158 | IRQ70_DMA2_Stream7 | 0x08015139 |

## 256-byte block map

Legend: `V` vectors, `0` zero, `.` erased (0xFF), `C` Thumb code, `D` data, `A` ascii-dense, `P` pointer-dense, `s` sparse (>=50% zero bytes), `m` partly erased. One row = 64 blocks = 16 KiB.

```
0x00000  VV00000000000000000000000000000000000000000000000000000000000000
0x04000  m.......mmm.....................................................
0x08000  CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC
0x0C000  CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC
0x10000  CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC
0x14000  CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCDDDDDDssDPDDssDAPDDsssssm
0x18000  ................................................................
0x1C000  ................................................................
0x20000  ................................................................
0x24000  ................................................................
0x28000  ................................................................
0x2C000  ................................................................
0x30000  ................................................................
0x34000  ................................................................
0x38000  ................................................................
0x3C000  ................................................................
```
Block counts: ascii=1, code=231, data=12, erased=700, mixed=5, ptr=2, sparse=9, vectors=2, zero=62

## Regions

Fill regions are byte-exact; content regions are 256-B granular.

| file start | file end | flash | len | class | annotation |
|---|---|---|---|---|---|
| 0x00000 | 0x001E0 | 0x08000000 |    480 | vectors |  |
| 0x001E0 | 0x04000 | 0x080001E0 |  15904 | zero |  |
| 0x04000 | 0x0401E | 0x08004000 |     30 | mixed | eeprom_wear_leveling_backing (0x4000..0x5000) |
| 0x0401E | 0x04800 | 0x0800401E |   2018 | erased | eeprom_wear_leveling_backing (0x4000..0x5000) |
| 0x04800 | 0x04AE4 | 0x08004800 |    740 | mixed | eeprom_wear_leveling_backing (0x4000..0x5000) |
| 0x04AE4 | 0x08000 | 0x08004AE4 |  13596 | erased | eeprom_wear_leveling_backing (0x4000..0x5000) |
| 0x08000 | 0x16700 | 0x08008000 |  59136 | code |  |
| 0x16700 | 0x16D00 | 0x08016700 |   1536 | data | encoder_map[6][1][2] u16 (literal @0xD2C4, keycode_at_encodermap_location_raw 0x0800D2A8) (0x169A0..0x169B8); keymaps[] 6x6x18 u16 (literal @0xD2A0, keycode_at_keymap_location_raw 0x0800D27C) (0x169B8..0x16EC8) |
| 0x16D00 | 0x16F00 | 0x08016D00 |    512 | sparse | keymaps[] 6x6x18 u16 (literal @0xD2A0, keycode_at_keymap_location_raw 0x0800D27C) (0x169B8..0x16EC8); KEYCODE2CONSUMER usage table u16[27] for KC_MUTE..KC_LPAD (literal @0xD5FC, range check @0x0800D5CE) (0x16EC8..0x16EFE) |
| 0x16F00 | 0x17000 | 0x08016F00 |    256 | data |  |
| 0x17000 | 0x17100 | 0x08017000 |    256 | ptr |  |
| 0x17100 | 0x17300 | 0x08017100 |    512 | data |  |
| 0x17300 | 0x17500 | 0x08017300 |    512 | sparse |  |
| 0x17500 | 0x17600 | 0x08017500 |    256 | data |  |
| 0x17600 | 0x17700 | 0x08017600 |    256 | ascii |  |
| 0x17700 | 0x17800 | 0x08017700 |    256 | ptr |  |
| 0x17800 | 0x17A00 | 0x08017800 |    512 | data |  |
| 0x17A00 | 0x17F00 | 0x08017A00 |   1280 | sparse |  |
| 0x17F00 | 0x17F04 | 0x08017F00 |      4 | mixed |  |
| 0x17F04 | 0x40000 | 0x08017F04 | 164092 | erased |  |

## Landmarks (string search)

| landmark | file off | flash | text |
|---|---|---|---|
| product_ascii | 0x1679B | 0x0801679B | `Keychron V10 Max` |
| build_date | 0x167AC | 0x080167AC | `2024-07-09-13:57:36` |
| newlib_path | 0x17674 | 0x08017674 | `../../../../../../newlib/libc/stdlib/rand.c` |
| wear_leveling_assert | 0x167C0 | 0x080167C0 | `Invalid sector count intended to be used with wear_leveling` |
| product_utf16 | 0x17102 | 0x08017102 | `Keychron V10 Max` |

## Annotations supplied on the command line

- 0x4000..0x5000 (flash 0x08004000): eeprom_wear_leveling_backing
- 0x169A0..0x169B8 (flash 0x080169A0): encoder_map[6][1][2] u16 (literal @0xD2C4, keycode_at_encodermap_location_raw 0x0800D2A8)
- 0x169B8..0x16EC8 (flash 0x080169B8): keymaps[] 6x6x18 u16 (literal @0xD2A0, keycode_at_keymap_location_raw 0x0800D27C)
- 0x16EC8..0x16EFE (flash 0x08016EC8): KEYCODE2CONSUMER usage table u16[27] for KC_MUTE..KC_LPAD (literal @0xD5FC, range check @0x0800D5CE)

