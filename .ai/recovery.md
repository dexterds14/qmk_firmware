# How this firmware was recovered (provenance & verification)

The original custom firmware's source was lost. It was reverse-engineered from a full flash
dump and rebuilt as source. Full evidence is in `keychron_v10max_backup/`.

## Provenance of the original image
- Built **2024-07-09** from Keychron fork commit **`8e390f92a2`** (`wireless_playground`, QMK 0.23.2 era) with **Ubuntu arm-none-eabi-gcc 13.2.1** / newlib 4.4.0. No LTO. **No VIA** (raw HID present but only answers the Keychron factory command).
- The keymap architecture mirrors the user's sibling `dactyl_manuform` keymap (older "09bf" generation): identifier names come from there; only values/behaviour are provable from the binary.

## The dump
- `keychron_v10max_backup/dump_a.bin` (and `dump_c.bin`) — two identical full 256 KB DFU reads (`sha256` in `sha256.txt`). `dump_b.bin` — a segment-limited read. `optbytes.bin` — option bytes (RDP level 0 = readable). Acquired with `dfu-util -a 0 -d 0483:df11 -s 0x08000000:0x40000 -U`.
- Layout: vectors 0x0–0x1DF, zero to 0x3FFF, EEPROM backing at 0x4000, code+rodata 0x8000–0x17F04.

## What was recovered and how
- **keymaps[]** at flash 0x080169B8 (6 layers × 6×18 u16) and **encoder_map[]** at 0x080169A0 — located by structural scan (19 unused matrix cells must be zero) + cross-check with the disassembled `keycode_at_keymap_location_raw`; decoded with keycode spec 0.0.3. See `keymap_recovered.{json,md,_table.c}`.
- **EEPROM** — parsed from the inverted wear-leveling sector (`eeprom_recovered.md`); a C oracle built from the fork's real `wear_leveling.c` agreed with the Python decode byte-for-byte.
- **Custom C** (tap dance, leader, one-shot indicators, `process_record_user`, RGB indicator, `./`/`../` keycodes) — decompiled (Ghidra headless, capstone) and adversarially verified. Function map in `functions_final.csv` / `hooks.csv`; per-function reports in `custom_code/`; decompiled C in `decompiled/`.
- Toolchain/base identified by strings + masked function matching against reference builds (`refs/`).

## Verification (how to re-confirm the recovery is faithful)
Rebuild the `dexter` keymap at the original commit with the matching compiler and compare against the dump:
```sh
# reference worktree is already at commit 8e390f92a2:
cd ~/code/qmk-keychron-ref
QMK_PATH_PREFIX=~/.local/share/xpack-arm-none-eabi-gcc-13.2.1/xpack-arm-none-eabi-gcc-13.2.1-1.1/bin \
  qmk compile -kb keychron/v10_max/ansi_encoder -km dexter -j 8
# then compare every user-TU function, both tables, tap-dance table, and config-bearing core funcs:
cd ~/code/qmk-keychron/keychron_v10max_backup
uv run --with pyelftools --with capstone python3 tools/final_compile_compare.py \
  ~/code/qmk-keychron-ref/.build/keychron_v10_max_ansi_encoder_dexter.elf
```
Historically this reported **ALL IDENTICAL** for the recovered portions (an exact-era build at
`8e390f92a2` with gcc 13.2.1). Note: the keymap now also contains the **added** features
(gaming mode, battery readout) which are NOT in the dump, so a whole-image match is no longer
expected — the byte-fidelity claim applies to the recovered base only. `tools/` holds the
scripts (dump triage, keymap decode/scan, function matchers, EEPROM parser + C oracle, Ghidra scripts).

## Simpler ongoing check when editing recovered layer tables
After changing a layer table, extract `keymaps`/`encoder_map` from the freshly built ELF (`nm -S`
+ read the bytes from the `.bin`) and compare the untouched layers to `dump_a.bin`
(0x080169B8 / 0x080169A0). Only the cells you intended to change should differ. This is how each
reformat/edit this project was proven not to reorder or drop keycodes.
