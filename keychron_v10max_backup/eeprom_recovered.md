# Keychron V10 Max -- emulated-EEPROM (wear-leveling) recovery

Source: `dump_a.bin` file offsets 0x04000..0x04fff = flash 0x08004000..0x08004fff. Same 4 KiB slice is byte-identical in dump_a/dump_b/dump_c (SHA-256 of slice checked before decoding).

Decoder: `tools/eeprom_parse.py`; independent oracle: `tools/eeprom_oracle/` (the fork's real `quantum/wear_leveling/wear_leveling.c` + `lib/fnv/hash_64a.c` compiled for the host against a mock backing store that serves `~word` from the dump).

## Format (verified against fork source)

* `platforms/chibios/drivers/wear_leveling/wear_leveling_efl.c`: `backing_store_write()` programs `~value`, `backing_store_read()` returns `~(*loc)` -> every byte below is shown **after inversion** (erased 0xFF flash == logical 0x00).
* `quantum/wear_leveling/wear_leveling.c`: consolidated image `[0,2048)`, FNV-1a-64 of it at `[2048,2056)` (`fnv_64a_buf(cache, LOGICAL_SIZE, FNV1A_64_INIT)`), write log from 2056 in `BACKING_STORE_WRITE_SIZE`=4 units, terminated at the first zero word (`wear_leveling_playback_log`). `info.json` `eeprom.wear_leveling`: driver `embedded_flash`, `logical_size` 2048, `backing_size` 4096. STM32F4 write size = `1 << STM32_FLASH_PSIZE` = 4 (`wear_leveling_efl_config.h`).
* Multibyte entry (`wear_leveling_internal.h` `LOG_ENTRY_MULTIBYTE_*`): byte0 = type(2b, 00) | len(3b) << 3 | addr[18:16]; byte1 = addr[15:8]; byte2 = addr[7:0]; byte3 = value[0]; a second word carries value[1..4] iff len > 1. With a 4-byte backing store the OPTIMIZED_64 / WORD_01 encodings are compiled out, so only type-00 entries can exist.

## Raw inverted bytes

Consolidated image, first 64 bytes (backing offset, flash address):

```
0000 (flash 08004000): e6 fe 00 01 00 14 00 ff 00 00 00 00 00 00 00 00
0010 (flash 08004010): 00 00 00 00 00 00 00 00 41 00 ef 4f af ff 00 00
0020 (flash 08004020): 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
0030 (flash 08004030): 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
```

Hash + start of write log (backing 0x800..0x83f):

```
0800 (flash 08004800): 3a e8 13 08 b4 11 7f 6d 28 00 18 41 00 ef 3f af
0810 (flash 08004810): 18 00 1d ff 00 00 00 00 28 00 18 41 00 ef 2f af
0820 (flash 08004820): 18 00 1d ff 00 00 00 00 28 00 18 40 00 ef 1f af
0830 (flash 08004830): 18 00 1d ff 00 00 00 00 28 00 18 41 00 ef 2f af
```

For reference, the un-inverted flash bytes at file 0x4000: `19 01 ff fe ff eb ff 00 ff ff ff ff ff ff ff ff` (i.e. `19 01 ff fe ff eb ff 00 ...` = ~`e6 fe 00 01 00 14 00 ff`).

## Hash check

| | value |
|---|---|
| stored, little-endian u64 @ backing 0x800 (flash 0x08004800) | `0x6d7f11b40813e83a` |
| computed FNV-1a-64 over consolidated[0:2048] (init 0xcbf29ce484222325, prime 0x100000001b3) | `0x6d7f11b40813e83a` |
| computed FNV-1-64 (non-a, for discrimination) | `0xebbd17700e2e5e30` |
| **result** | **MATCH -- firmware accepts the consolidated image** |

## Write log

* 92 entries, all `LOG_ENTRY_TYPE_MULTIBYTE`; 184 of 510 log words used; terminator (first zero word) at backing `0x0ae8` = file `0x04ae8` = flash `0x08004ae8`; every byte after it is 0x00 logical / 0xFF flash (1304 bytes checked, 0 nonzero). Anomalies: none.
* Only two (addr,len) shapes occur: `(24,5)` and `(29,3)`, always in that order, 46 pairs. That is exactly what `eeconfig_flush_rgb_matrix()` (`EECONFIG_DEBOUNCE_HELPER(rgb_matrix, EECONFIG_RGB_MATRIX, ...)`, `quantum/rgb_matrix/rgb_matrix.c:103`) produces: `eeprom_update_block(&rgb_matrix_config, 24, 8)` -> `wear_leveling_write(24, ., 8)` -> `wear_leveling_write_raw` chops into `LOG_ENTRY_MULTIBYTE_MAX_BYTES`=5 + 3. No other EEPROM address was written since the last consolidation (no default_layer, keymap_config, debug, KB-data writes).
* **Write-path fingerprint.** The recovered keymap drives RGB with stock `RGB_VAI/RGB_VAD/RGB_TOG/RGB_HUI/...` keycodes (`keymap_recovered.md`), handled by `quantum/process_keycode/process_rgb.c` -> `rgb_matrix_increase_val()` etc. In the fork worktree HEAD those helpers write *partially* -- `eeprom_write_byte((uint8_t*)EECONFIG_RGB_MATRIX, mode)` (1 byte @24) and `eeprom_write_block(&rgb_matrix_config.hsv, 25, 3)` (`quantum/rgb_matrix/rgb_matrix.c:567,586,607,679`) -- which would have left `(24,1)` / `(25,3)` / `(28,1)` entries in this log. None exist: every entry is a full 8-byte flush. That matches the reference fork at 1011db8c8d (2024-07-01, `/Users/dexter/code/qmk-keychron-ref/quantum/rgb_matrix/rgb_matrix.c:540,557,577,601,644,740,776`), where every helper just calls `eeconfig_flag_rgb_matrix(write_to_eeprom)` and `rgb_task_sync()` later does `eeconfig_flush_rgb_matrix(false)` = `eeprom_update_block(&rgb_matrix_config, 24, 8)`. `git log -S` shows the partial-write code entered the fork in commit c9049679ac (2025-05-30), after this firmware's 2024-07-09 build date. So the EEPROM log independently confirms the firmware's `rgb_matrix.c` is the pre-2025 (reference-era) version, not worktree HEAD.
* Per entry (backing offset / flash addr / raw LE words / eeprom addr / len / bytes) -- see `eeprom_recovered.json` `log_entries`; the semantic replay is in the history table below.

### RGB-config history (state after each log entry; consolidated image = state 'C')

| # | backing | @ | len | bytes | en | mode | h | s | v | spd | flags | change |
|---|---|---|---|---|---|---|---|---|---|---|---|---|
| C | 0x0000 | 24 | 8 | 4100ef4fafff0000 | 1 | 16 | 0 | 239 | 79 | 175 | 0xff | consolidated image |
| 0 | 0x0808 | 24 | 5 | 4100ef3faf | 1 | 16 | 0 | 239 | 63 | 175 | 0xff | val 79->63 |
| 1 | 0x0810 | 29 | 3 | ff0000 | 1 | 16 | 0 | 239 | 63 | 175 | 0xff |  |
| 2 | 0x0818 | 24 | 5 | 4100ef2faf | 1 | 16 | 0 | 239 | 47 | 175 | 0xff | val 63->47 |
| 3 | 0x0820 | 29 | 3 | ff0000 | 1 | 16 | 0 | 239 | 47 | 175 | 0xff |  |
| 4 | 0x0828 | 24 | 5 | 4000ef1faf | 0 | 16 | 0 | 239 | 31 | 175 | 0xff | enable 1->0, val 47->31 |
| 5 | 0x0830 | 29 | 3 | ff0000 | 0 | 16 | 0 | 239 | 31 | 175 | 0xff |  |
| 6 | 0x0838 | 24 | 5 | 4100ef2faf | 1 | 16 | 0 | 239 | 47 | 175 | 0xff | enable 0->1, val 31->47 |
| 7 | 0x0840 | 29 | 3 | ff0000 | 1 | 16 | 0 | 239 | 47 | 175 | 0xff |  |
| 8 | 0x0848 | 24 | 5 | 4000ef1faf | 0 | 16 | 0 | 239 | 31 | 175 | 0xff | enable 1->0, val 47->31 |
| 9 | 0x0850 | 29 | 3 | ff0000 | 0 | 16 | 0 | 239 | 31 | 175 | 0xff |  |
| 10 | 0x0858 | 24 | 5 | 4100ef2faf | 1 | 16 | 0 | 239 | 47 | 175 | 0xff | enable 0->1, val 31->47 |
| 11 | 0x0860 | 29 | 3 | ff0000 | 1 | 16 | 0 | 239 | 47 | 175 | 0xff |  |
| 12 | 0x0868 | 24 | 5 | 4100ef3faf | 1 | 16 | 0 | 239 | 63 | 175 | 0xff | val 47->63 |
| 13 | 0x0870 | 29 | 3 | ff0000 | 1 | 16 | 0 | 239 | 63 | 175 | 0xff |  |
| 14 | 0x0878 | 24 | 5 | 4100ef4faf | 1 | 16 | 0 | 239 | 79 | 175 | 0xff | val 63->79 |
| 15 | 0x0880 | 29 | 3 | ff0000 | 1 | 16 | 0 | 239 | 79 | 175 | 0xff |  |
| 16 | 0x0888 | 24 | 5 | 4100ef5faf | 1 | 16 | 0 | 239 | 95 | 175 | 0xff | val 79->95 |
| 17 | 0x0890 | 29 | 3 | ff0000 | 1 | 16 | 0 | 239 | 95 | 175 | 0xff |  |
| 18 | 0x0898 | 24 | 5 | 4100ef6faf | 1 | 16 | 0 | 239 | 111 | 175 | 0xff | val 95->111 |
| 19 | 0x08a0 | 29 | 3 | ff0000 | 1 | 16 | 0 | 239 | 111 | 175 | 0xff |  |
| 20 | 0x08a8 | 24 | 5 | 4100ef7faf | 1 | 16 | 0 | 239 | 127 | 175 | 0xff | val 111->127 |
| 21 | 0x08b0 | 29 | 3 | ff0000 | 1 | 16 | 0 | 239 | 127 | 175 | 0xff |  |
| 22 | 0x08b8 | 24 | 5 | 4100ef8faf | 1 | 16 | 0 | 239 | 143 | 175 | 0xff | val 127->143 |
| 23 | 0x08c0 | 29 | 3 | ff0000 | 1 | 16 | 0 | 239 | 143 | 175 | 0xff |  |
| 24 | 0x08c8 | 24 | 5 | 4100ef9faf | 1 | 16 | 0 | 239 | 159 | 175 | 0xff | val 143->159 |
| 25 | 0x08d0 | 29 | 3 | ff0000 | 1 | 16 | 0 | 239 | 159 | 175 | 0xff |  |
| 26 | 0x08d8 | 24 | 5 | 4100efafaf | 1 | 16 | 0 | 239 | 175 | 175 | 0xff | val 159->175 |
| 27 | 0x08e0 | 29 | 3 | ff0000 | 1 | 16 | 0 | 239 | 175 | 175 | 0xff |  |
| 28 | 0x08e8 | 24 | 5 | 4100efbfaf | 1 | 16 | 0 | 239 | 191 | 175 | 0xff | val 175->191 |
| 29 | 0x08f0 | 29 | 3 | ff0000 | 1 | 16 | 0 | 239 | 191 | 175 | 0xff |  |
| 30 | 0x08f8 | 24 | 5 | 4100efcfaf | 1 | 16 | 0 | 239 | 207 | 175 | 0xff | val 191->207 |
| 31 | 0x0900 | 29 | 3 | ff0000 | 1 | 16 | 0 | 239 | 207 | 175 | 0xff |  |
| 32 | 0x0908 | 24 | 5 | 4100efdfaf | 1 | 16 | 0 | 239 | 223 | 175 | 0xff | val 207->223 |
| 33 | 0x0910 | 29 | 3 | ff0000 | 1 | 16 | 0 | 239 | 223 | 175 | 0xff |  |
| 34 | 0x0918 | 24 | 5 | 4100efefaf | 1 | 16 | 0 | 239 | 239 | 175 | 0xff | val 223->239 |
| 35 | 0x0920 | 29 | 3 | ff0000 | 1 | 16 | 0 | 239 | 239 | 175 | 0xff |  |
| 36 | 0x0928 | 24 | 5 | 4100efffaf | 1 | 16 | 0 | 239 | 255 | 175 | 0xff | val 239->255 |
| 37 | 0x0930 | 29 | 3 | ff0000 | 1 | 16 | 0 | 239 | 255 | 175 | 0xff |  |
| 38 | 0x0938 | 24 | 5 | 4100efffbf | 1 | 16 | 0 | 239 | 255 | 191 | 0xff | speed 175->191 |
| 39 | 0x0940 | 29 | 3 | ff0000 | 1 | 16 | 0 | 239 | 255 | 191 | 0xff |  |
| 40 | 0x0948 | 24 | 5 | 4100efefbf | 1 | 16 | 0 | 239 | 239 | 191 | 0xff | val 255->239 |
| 41 | 0x0950 | 29 | 3 | ff0000 | 1 | 16 | 0 | 239 | 239 | 191 | 0xff |  |
| 42 | 0x0958 | 24 | 5 | 4100efdfbf | 1 | 16 | 0 | 239 | 223 | 191 | 0xff | val 239->223 |
| 43 | 0x0960 | 29 | 3 | ff0000 | 1 | 16 | 0 | 239 | 223 | 191 | 0xff |  |
| 44 | 0x0968 | 24 | 5 | 4100efcfbf | 1 | 16 | 0 | 239 | 207 | 191 | 0xff | val 223->207 |
| 45 | 0x0970 | 29 | 3 | ff0000 | 1 | 16 | 0 | 239 | 207 | 191 | 0xff |  |
| 46 | 0x0978 | 24 | 5 | 4100efbfbf | 1 | 16 | 0 | 239 | 191 | 191 | 0xff | val 207->191 |
| 47 | 0x0980 | 29 | 3 | ff0000 | 1 | 16 | 0 | 239 | 191 | 191 | 0xff |  |
| 48 | 0x0988 | 24 | 5 | 4100efafbf | 1 | 16 | 0 | 239 | 175 | 191 | 0xff | val 191->175 |
| 49 | 0x0990 | 29 | 3 | ff0000 | 1 | 16 | 0 | 239 | 175 | 191 | 0xff |  |
| 50 | 0x0998 | 24 | 5 | 4100ef9fbf | 1 | 16 | 0 | 239 | 159 | 191 | 0xff | val 175->159 |
| 51 | 0x09a0 | 29 | 3 | ff0000 | 1 | 16 | 0 | 239 | 159 | 191 | 0xff |  |
| 52 | 0x09a8 | 24 | 5 | 4100ef8fbf | 1 | 16 | 0 | 239 | 143 | 191 | 0xff | val 159->143 |
| 53 | 0x09b0 | 29 | 3 | ff0000 | 1 | 16 | 0 | 239 | 143 | 191 | 0xff |  |
| 54 | 0x09b8 | 24 | 5 | 4100ef7fbf | 1 | 16 | 0 | 239 | 127 | 191 | 0xff | val 143->127 |
| 55 | 0x09c0 | 29 | 3 | ff0000 | 1 | 16 | 0 | 239 | 127 | 191 | 0xff |  |
| 56 | 0x09c8 | 24 | 5 | 4100ef8fbf | 1 | 16 | 0 | 239 | 143 | 191 | 0xff | val 127->143 |
| 57 | 0x09d0 | 29 | 3 | ff0000 | 1 | 16 | 0 | 239 | 143 | 191 | 0xff |  |
| 58 | 0x09d8 | 24 | 5 | 4100ef7fbf | 1 | 16 | 0 | 239 | 127 | 191 | 0xff | val 143->127 |
| 59 | 0x09e0 | 29 | 3 | ff0000 | 1 | 16 | 0 | 239 | 127 | 191 | 0xff |  |
| 60 | 0x09e8 | 24 | 5 | 4100ef8fbf | 1 | 16 | 0 | 239 | 143 | 191 | 0xff | val 127->143 |
| 61 | 0x09f0 | 29 | 3 | ff0000 | 1 | 16 | 0 | 239 | 143 | 191 | 0xff |  |
| 62 | 0x09f8 | 24 | 5 | 4100ef7fbf | 1 | 16 | 0 | 239 | 127 | 191 | 0xff | val 143->127 |
| 63 | 0x0a00 | 29 | 3 | ff0000 | 1 | 16 | 0 | 239 | 127 | 191 | 0xff |  |
| 64 | 0x0a08 | 24 | 5 | 4100ef6fbf | 1 | 16 | 0 | 239 | 111 | 191 | 0xff | val 127->111 |
| 65 | 0x0a10 | 29 | 3 | ff0000 | 1 | 16 | 0 | 239 | 111 | 191 | 0xff |  |
| 66 | 0x0a18 | 24 | 5 | 4100ef5fbf | 1 | 16 | 0 | 239 | 95 | 191 | 0xff | val 111->95 |
| 67 | 0x0a20 | 29 | 3 | ff0000 | 1 | 16 | 0 | 239 | 95 | 191 | 0xff |  |
| 68 | 0x0a28 | 24 | 5 | 4100ef6fbf | 1 | 16 | 0 | 239 | 111 | 191 | 0xff | val 95->111 |
| 69 | 0x0a30 | 29 | 3 | ff0000 | 1 | 16 | 0 | 239 | 111 | 191 | 0xff |  |
| 70 | 0x0a38 | 24 | 5 | 4100ef5fbf | 1 | 16 | 0 | 239 | 95 | 191 | 0xff | val 111->95 |
| 71 | 0x0a40 | 29 | 3 | ff0000 | 1 | 16 | 0 | 239 | 95 | 191 | 0xff |  |
| 72 | 0x0a48 | 24 | 5 | 4100ef4fbf | 1 | 16 | 0 | 239 | 79 | 191 | 0xff | val 95->79 |
| 73 | 0x0a50 | 29 | 3 | ff0000 | 1 | 16 | 0 | 239 | 79 | 191 | 0xff |  |
| 74 | 0x0a58 | 24 | 5 | 4100ef3fbf | 1 | 16 | 0 | 239 | 63 | 191 | 0xff | val 79->63 |
| 75 | 0x0a60 | 29 | 3 | ff0000 | 1 | 16 | 0 | 239 | 63 | 191 | 0xff |  |
| 76 | 0x0a68 | 24 | 5 | 4100ef2fbf | 1 | 16 | 0 | 239 | 47 | 191 | 0xff | val 63->47 |
| 77 | 0x0a70 | 29 | 3 | ff0000 | 1 | 16 | 0 | 239 | 47 | 191 | 0xff |  |
| 78 | 0x0a78 | 24 | 5 | 4000ef1fbf | 0 | 16 | 0 | 239 | 31 | 191 | 0xff | enable 1->0, val 47->31 |
| 79 | 0x0a80 | 29 | 3 | ff0000 | 0 | 16 | 0 | 239 | 31 | 191 | 0xff |  |
| 80 | 0x0a88 | 24 | 5 | 4100ef2fbf | 1 | 16 | 0 | 239 | 47 | 191 | 0xff | enable 0->1, val 31->47 |
| 81 | 0x0a90 | 29 | 3 | ff0000 | 1 | 16 | 0 | 239 | 47 | 191 | 0xff |  |
| 82 | 0x0a98 | 24 | 5 | 4100ef3fbf | 1 | 16 | 0 | 239 | 63 | 191 | 0xff | val 47->63 |
| 83 | 0x0aa0 | 29 | 3 | ff0000 | 1 | 16 | 0 | 239 | 63 | 191 | 0xff |  |
| 84 | 0x0aa8 | 24 | 5 | 4100ef4fbf | 1 | 16 | 0 | 239 | 79 | 191 | 0xff | val 63->79 |
| 85 | 0x0ab0 | 29 | 3 | ff0000 | 1 | 16 | 0 | 239 | 79 | 191 | 0xff |  |
| 86 | 0x0ab8 | 24 | 5 | 4100ef3fbf | 1 | 16 | 0 | 239 | 63 | 191 | 0xff | val 79->63 |
| 87 | 0x0ac0 | 29 | 3 | ff0000 | 1 | 16 | 0 | 239 | 63 | 191 | 0xff |  |
| 88 | 0x0ac8 | 24 | 5 | 4100ef2fbf | 1 | 16 | 0 | 239 | 47 | 191 | 0xff | val 63->47 |
| 89 | 0x0ad0 | 29 | 3 | ff0000 | 1 | 16 | 0 | 239 | 47 | 191 | 0xff |  |
| 90 | 0x0ad8 | 24 | 5 | 4108ef2fbf | 1 | 16 | 8 | 239 | 47 | 191 | 0xff | hue 0->8 |
| 91 | 0x0ae0 | 29 | 3 | ff0000 | 1 | 16 | 8 | 239 | 47 | 191 | 0xff |  |

## eeconfig decode (QMK 0.23 layout, `quantum/eeconfig.h` in the fork)

Two columns: the consolidated image (state at the last consolidation) and the state after log replay (= what `wear_leveling_init()` leaves in the cache = what the firmware reads at boot).

| field | addr | consolidated | after replay (live) | note |
|---|---|---|---|---|
| magic u16 | 0 | 0xFEE6 | 0xFEE6 | expect 0xFEE6 (`EECONFIG_MAGIC_NUMBER`) -> OK |
| debug u8 | 2 | 0 | 0 | |
| default_layer u8 (bitmask) | 3 | 0x01 | 0x01 | layer index 0 |
| keymap_config u16 | 4 | 0x1400 | 0x1400 | bits set: oneshot_enable, autocorrect_enable |
| backlight u8 | 6 | 0 | 0 | |
| audio u8 | 7 | 0xff | 0xff | 0xFF = eeconfig_init_quantum default ('on') |
| rgblight u32 | 8 | 0x00000000 | 0x00000000 | |
| unicode / steno / handedness | 12/13/14 | 0/0/0 | 0/0/0 | |
| keyboard u32 | 15 | 0x00000000 | 0x00000000 | KB-datablock version slot; see notes |
| user u32 | 19 | 0x00000000 | 0x00000000 | |
| unused u8 | 23 | 0 | 0 | |
| rgb_matrix u64 raw | 24..31 | 4100ef4fafff0000 | 4108ef2fbfff0000 | |
| rgb_matrix.enable (bits 1..0 of byte 24) | 24 | 1 | 1 | |
| rgb_matrix.mode (bits 7..2 of byte 24) | 24 | 16 | 16 | RGB_MATRIX_TYPING_HEATMAP (board-default enum, see caveat) |
| rgb_matrix.hsv.h / s / v | 25/26/27 | 0 / 239 / 79 | 8 / 239 / 47 | |
| rgb_matrix.speed | 28 | 175 | 191 | |
| rgb_matrix.flags | 29 | 0xff | 0xff | LED_FLAG_ALL (0xFF) |
| (union padding) | 30..31 | 0000 | 0000 | |
| haptic u32 | 32 | 0x00000000 | 0x00000000 | |
| rgblight_ext u8 | 36 | 0 | 0 | |
| Keychron KB data: language u8 | 37 | 0 | 0 | `eeconfig_kb.h` EECONFIG_BASE_LANGUAGE 37 |
| Keychron KB data: wireless backlit_disable_time u16 | 38 | 0 | 0 | 0 -> firmware substitutes CONNECTED_BACKLIGHT_DISABLE_TIMEOUT (600 s) |
| Keychron KB data: wireless connected_idle_time u16 | 40 | 0 | 0 | 0 -> firmware substitutes CONNECTED_IDLE_TIME (7200 s) |
| bytes 42..63 | | 00000000000000000000000000000000000000000000 | 00000000000000000000000000000000000000000000 | |
| bytes 64..2047 | | all zero | all zero | no VIA/dynamic-keymap blob present |

keymap_config bit map used (`quantum/keycode_config.h`, bit 0 first): 0=swap_control_capslock, 1=capslock_to_control, 2=swap_lalt_lgui, 3=swap_ralt_rgui, 4=no_gui, 5=swap_grave_esc, 6=swap_backslash_backspace, 7=nkro, 8=swap_lctl_lgui, 9=swap_rctl_rgui, 10=oneshot_enable, 11=swap_escape_capslock, 12=autocorrect_enable.

## RGB effect enum (assumed: board-default animation set)

enum built from quantum/rgb_matrix/animations/rgb_matrix_effects.inc (44 headers, 49 RGB_MATRIX_EFFECT names, 22 enabled -> RGB_MATRIX_EFFECT_MAX = 23); info.json animations=21 true, RGB_MATRIX_FRAMEBUFFER_EFFECTS=True, RGB_MATRIX_KEYPRESSES=True

| mode # | enum name | header (in `rgb_matrix_effects.inc` order) | compile condition |
|---|---|---|---|
| 0 | `RGB_MATRIX_NONE` | - | - |
| 1 | `RGB_MATRIX_SOLID_COLOR` | solid_color_anim.h | always |
| 2 | `RGB_MATRIX_BREATHING` | breathing_anim.h | ENABLE_RGB_MATRIX_BREATHING |
| 3 | `RGB_MATRIX_BAND_SPIRAL_VAL` | colorband_spiral_val_anim.h | ENABLE_RGB_MATRIX_BAND_SPIRAL_VAL |
| 4 | `RGB_MATRIX_CYCLE_ALL` | cycle_all_anim.h | ENABLE_RGB_MATRIX_CYCLE_ALL |
| 5 | `RGB_MATRIX_CYCLE_LEFT_RIGHT` | cycle_left_right_anim.h | ENABLE_RGB_MATRIX_CYCLE_LEFT_RIGHT |
| 6 | `RGB_MATRIX_CYCLE_UP_DOWN` | cycle_up_down_anim.h | ENABLE_RGB_MATRIX_CYCLE_UP_DOWN |
| 7 | `RGB_MATRIX_RAINBOW_MOVING_CHEVRON` | rainbow_moving_chevron_anim.h | ENABLE_RGB_MATRIX_RAINBOW_MOVING_CHEVRON |
| 8 | `RGB_MATRIX_CYCLE_OUT_IN` | cycle_out_in_anim.h | ENABLE_RGB_MATRIX_CYCLE_OUT_IN |
| 9 | `RGB_MATRIX_CYCLE_OUT_IN_DUAL` | cycle_out_in_dual_anim.h | ENABLE_RGB_MATRIX_CYCLE_OUT_IN_DUAL |
| 10 | `RGB_MATRIX_CYCLE_PINWHEEL` | cycle_pinwheel_anim.h | ENABLE_RGB_MATRIX_CYCLE_PINWHEEL |
| 11 | `RGB_MATRIX_CYCLE_SPIRAL` | cycle_spiral_anim.h | ENABLE_RGB_MATRIX_CYCLE_SPIRAL |
| 12 | `RGB_MATRIX_DUAL_BEACON` | dual_beacon_anim.h | ENABLE_RGB_MATRIX_DUAL_BEACON |
| 13 | `RGB_MATRIX_RAINBOW_BEACON` | rainbow_beacon_anim.h | ENABLE_RGB_MATRIX_RAINBOW_BEACON |
| 14 | `RGB_MATRIX_JELLYBEAN_RAINDROPS` | jellybean_raindrops_anim.h | ENABLE_RGB_MATRIX_JELLYBEAN_RAINDROPS |
| 15 | `RGB_MATRIX_PIXEL_RAIN` | pixel_rain_anim.h | ENABLE_RGB_MATRIX_PIXEL_RAIN |
| 16 | `RGB_MATRIX_TYPING_HEATMAP` **<-- stored mode** | typing_heatmap_anim.h | ENABLE_RGB_MATRIX_TYPING_HEATMAP && RGB_MATRIX_FRAMEBUFFER_EFFECTS |
| 17 | `RGB_MATRIX_DIGITAL_RAIN` | digital_rain_anim.h | ENABLE_RGB_MATRIX_DIGITAL_RAIN && RGB_MATRIX_FRAMEBUFFER_EFFECTS |
| 18 | `RGB_MATRIX_SOLID_REACTIVE_SIMPLE` | solid_reactive_simple_anim.h | ENABLE_RGB_MATRIX_SOLID_REACTIVE_SIMPLE && RGB_MATRIX_KEYREACTIVE_ENABLED |
| 19 | `RGB_MATRIX_SOLID_REACTIVE_MULTIWIDE` | solid_reactive_wide.h | ENABLE_RGB_MATRIX_SOLID_REACTIVE_MULTIWIDE && RGB_MATRIX_KEYREACTIVE_ENABLED |
| 20 | `RGB_MATRIX_SOLID_REACTIVE_MULTINEXUS` | solid_reactive_nexus.h | ENABLE_RGB_MATRIX_SOLID_REACTIVE_MULTINEXUS && RGB_MATRIX_KEYREACTIVE_ENABLED |
| 21 | `RGB_MATRIX_SPLASH` | splash_anim.h | ENABLE_RGB_MATRIX_SPLASH && RGB_MATRIX_KEYREACTIVE_ENABLED |
| 22 | `RGB_MATRIX_SOLID_SPLASH` | solid_splash_anim.h | ENABLE_RGB_MATRIX_SOLID_SPLASH && RGB_MATRIX_KEYREACTIVE_ENABLED |

**Caveat.** The mode number is only meaningful relative to the effect set compiled into the *custom* firmware: `enum rgb_matrix_effects` (`quantum/rgb_matrix/rgb_matrix.h:138`) numbers `RGB_MATRIX_NONE`=0, `SOLID_COLOR`=1, then only the `RGB_MATRIX_EFFECT()` entries that survive `#ifdef ENABLE_RGB_MATRIX_*` in `.inc` order. The table above uses the `rgb_matrix.animations` set from `keyboards/keychron/v10_max/info.json` in the fork worktree plus `RGB_MATRIX_KEYPRESSES` and `RGB_MATRIX_FRAMEBUFFER_EFFECTS` from `ansi_encoder/config.h`. If the custom build changed that set (e.g. added `rgb_matrix_kb.inc` custom effects or disabled animations in its keymap `config.h`), the name for mode 16 changes; the number 16 itself is what is stored.

## Sanity / observations

* magic == 0xFEE6: **True**.
* default_layer = 0x01 -> 1<<0 (layer 0). No write to address 3 appears in the log, so the DIP switch (stock `dip_switch_update_kb` calls `default_layer_set(1UL << (active ? 0 : 2))`, `keyboards/keychron/v10_max/v10_max.c:36`) did not change position during the whole log epoch (46 RGB flushes), and it was on the side that selects layer 0 (stock: 'Mac'). Whether the custom keymap keeps that DIP handler is for the code-analysis track.
* keymap_config = 0x1400: exactly the `eeconfig_init_quantum()` default `0x1400` (oneshot_enable | autocorrect_enable, `quantum/eeconfig.c`) -- never modified afterwards. In particular **nkro bit is 0** even though the keymap contains `NK_TOGG`; the Keychron fork is built with `-DAPDAPTIVE_NKRO_ENABLE` and `WIRELESS_NKRO_ENABLE` (`keychron_common.mk`, `v10_max/config.h`), so NKRO handling may not go through this bit; no swap-modifier/magic settings are active.
* rgb_matrix: enable=1, mode=16 (RGB_MATRIX_TYPING_HEATMAP under the board-default enum; RGB_MATRIX_EFFECT_MAX would be 23 so the value is in range: True), hue=8 sat=239 val=47 speed=191 flags=LED_FLAG_ALL (0xFF). Consolidated image had h=0 s=239 v=79 spd=175; the 46 logged flushes are the user stepping brightness (`val` in steps of 16 = `RGB_MATRIX_VAL_STEP`, `rgb_matrix.h:68`), speed (steps of 16 = `RGB_MATRIX_SPD_STEP`, `rgb_matrix.h:72`) and finally hue (0 -> 8 = `RGB_MATRIX_HUE_STEP`, `rgb_matrix.h:60`) with the Fn RGB keys. Mode never changed inside the log epoch.
* The three `enable 1->0` events (entries #4, #8, #78) each coincide with `val 47->31`, and the following `enable 0->1` events (#6, #10, #80) with `val 31->47`. That is not RGB_TOG but the fork's low-brightness auto-off: `ansi_encoder/config.h` defines `RGB_MATRIX_BRIGHTNESS_TURN_OFF_VAL 32`; `rgb_matrix_decrease_val_helper()` (`quantum/rgb_matrix/rgb_matrix.c:760-767`) subtracts 16 and then calls `rgb_matrix_toggle_eeprom_helper()` when `enable && hsv.v <= 32`; `rgb_matrix_increase_val_helper()` (`rgb_matrix.c:744-752`) on a disabled matrix calls the toggle helper, which (`rgb_matrix.c:565-575`) re-enables and steps `v` up until it is >= 32 (31 -> 47). So the user simply pressed RGB_VAD past the floor and RGB_VAI back up. Final val=47 is above the floor: backlight is on at boot.
* sat=239 (0xEF) is *not* the QMK default 255: `RGB_MATRIX_DEFAULT_SAT` is UINT8_MAX in `rgb_matrix.h`, and the consolidated image already has 0xEF, so either the custom firmware defines `RGB_MATRIX_DEFAULT_SAT 239`, or the user pressed RGB_SAD once (RGB_MATRIX_SAT_STEP default 16: 255-16 = 239) before the last consolidation. Cannot be distinguished from this sector alone.
* keyboard u32 @15 = 0x00000000 and language @37 = 0, wireless config @38..41 = 0. Consistent with the fork: Keychron's `eeconfig_init_kb_datablock()` (`keyboards/keychron/common/eeconfig_kb.c`) does not call `eeconfig_update_kb_datablock()`, so the KB-datablock version dword (would be `EECONFIG_KB_DATA_VERSION` = `EECONFIG_KB_DATA_SIZE` = 5 = 1 language + 4 wireless bytes) is never written and stays 0 after erase; language and wireless-idle settings were never set via the Launcher raw-HID path (`language_set`, `wireless_lpm_set`). `wireless_config_load()` maps the zeros to defaults 600 s / 7200 s.
* No dynamic-keymap / VIA data: bytes 64..2047 are all zero, matching the absence of VIA in the firmware.
* Log occupancy: 184/510 words; next write would go to backing 0x0ae8. No consolidation was imminent.
* Oracle: MATCH: C oracle (fork wear_leveling.c) cache == Python replay, all 2048 bytes

## Confidence

* **Verified** (byte evidence + fork source): format, inversion, hash match, log grammar, 92 entries, final rgb bytes, magic, default_layer, keymap_config, zero KB data, oracle equality, the (24,5)+(29,3) shape == 8-byte `eeconfig_flush_rgb_matrix` writes, the auto-off explanation of the enable flips.
* **Inference**: mode-number -> effect-name mapping (depends on the custom build's animation set); the DIP-switch and NKRO remarks; the sat=239 origin; 'firmware rgb_matrix.c is the reference-era version' (strong but indirect: it rests on the absence of partial-write entries in a 46-flush window).
* Line numbers cited as `rgb_matrix.c:NNN` without a path prefix refer to the fork worktree HEAD (`/Users/dexter/code/qmk-keychron`); the auto-off logic is the same in the reference commit (see the fingerprint bullet for the reference-specific lines).
