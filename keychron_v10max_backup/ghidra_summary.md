# Ghidra auto-analysis summary (dump_a.bin @ 0x08000000)

## Coverage
```
Ghidra coverage of code region 0x08008000..0x08017F04 (65284 bytes)
functions total=903 (thunks=32) with entry in code region=903
bytes inside function bodies : 53592 (82.09%)
bytes as instructions        : 53592 (82.09%)  [20904 instructions]
bytes as defined data        : 6958 (10.66%)  [1471 data items]
bytes undefined              : 4734 (7.25%)
instruction bytes outside any function: 0
```

Total functions: 903

## 20 largest functions

| entry | size | name | callers | callees | strings |
|---|---|---|---|---|---|
| 0x0800D698 | 1010 | FUN_0800d698 | 1 | 40 |  |
| 0x08008DE4 | 762 | FUN_08008de4 | 1 | 8 |  |
| 0x08015B5C | 706 | Vector14C_IRQ67_OTG_FS | 0 | 9 |  |
| 0x08014478 | 700 | FUN_08014478 | 0 | 11 |  |
| 0x08008188 | 666 | FUN_08008188 | 1 | 2 |  |
| 0x0800DF94 | 644 | FUN_0800df94 | 1 | 12 |  |
| 0x0800B008 | 616 | FUN_0800b008 | 0 | 9 |  |
| 0x08008ABC | 598 | FUN_08008abc | 3 | 5 | 08017708:#-0+  / 08017714:efgEFG |
| 0x08009D4C | 570 | FUN_08009d4c | 1 | 2 | 08017730:0123456789abcdef / 0801771C:0123456789ABCDEF |
| 0x08010A4C | 456 | FUN_08010a4c | 2 | 27 |  |
| 0x0800E8B0 | 432 | FUN_0800e8b0 | 1 | 2 |  |
| 0x0800BDCC | 418 | FUN_0800bdcc | 1 | 24 |  |
| 0x0800A570 | 396 | FUN_0800a570 | 1 | 20 |  |
| 0x0800CB90 | 392 | factory_test_rx | 1 | 6 | 080167AC:2024-07-09-13:57:36 |
| 0x08011DF0 | 374 | FUN_08011df0 | 1 | 8 |  |
| 0x0800CDFE | 354 | FUN_0800cdfe | 1 | 5 |  |
| 0x0800FEF0 | 342 | FUN_0800fef0 | 1 | 5 |  |
| 0x080116D0 | 342 | FUN_080116d0 | 1 | 3 |  |
| 0x0800883C | 306 | memcpy | 40 | 0 |  |
| 0x0800B6AC | 292 | FUN_0800b6ac | 2 | 8 |  |

## Functions referencing keymaps[] (0x080169B8)

- 0x0800D27C keycode_at_keymap_location_raw

Literal-pool words pointing into keymaps[]:
- word 0x0800D2A0 = 0x080169B8 (+0) inside -; readers: 0x0800D294@keycode_at_keymap_location_raw

## Functions whose decompiled body contains keycode-like constants

| file | distinct keycode consts | switches | cases | refs keymaps | constants |
|---|---|---|---|---|---|
| 08011530_process_rgb_matrix.c | 21 | 6 | 21 |  | 0x7820 0x7821 0x7822 0x7823 0x7824 0x7825 0x7826 0x7827 0x7828 0x7829 0x782A 0x782B 0x782C 0x782D 0x782E 0x782F 0x7830 0 |
| 0800c720_process_record_keychron_common.c | 11 | 2 | 11 |  | 0x7E00 0x7E01 0x7E02 0x7E03 0x7E04 0x7E05 0x7E06 0x7E07 0x7E08 0x7E09 0x7E0A |
| 0800d104_process_record_user.c | 7 | 0 | 0 |  | 0x52A2 0x52A8 0x52B2 0x52B8 0x5700 0x7E40 0x7E41 |
| 0800e8b0_FUN_0800e8b0.c | 6 | 0 | 0 |  | 0x5200 0x521F 0x5240 0x5260 0x5280 0x52A0 |
| 0800a788_process_record_wireless.c | 3 | 0 | 0 |  | 0x7E0B 0x7E0E 0x7E0F |
| 0800c4b4_FUN_0800c4b4.c | 3 | 0 | 0 |  | 0x7E0B 0x7E0E 0x7E0F |
| 0800c928_process_record_factory_test.c | 2 | 0 | 0 |  | 0x5221 0x5223 |
| 0800d396_reset_keyboard.c | 1 | 0 | 0 |  | 0x7C00 |
| 0800d3b6_process_record_quantum.c | 1 | 0 | 0 |  | 0x7C00 |
| 080118f4_process_leader.c | 1 | 0 | 0 |  | 0x7C58 |
| 08012040_process_tap_dance.c | 1 | 0 | 0 |  | 0x5700 |
| 0800d27c_keycode_at_keymap_location_raw.c | 0 | 0 | 0 | yes |  |
| 0800d2a4_keycode_at_keymap_location.c | 0 | 0 | 0 | yes |  |
