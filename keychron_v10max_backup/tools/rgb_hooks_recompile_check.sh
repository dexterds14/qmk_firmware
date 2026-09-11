#!/bin/sh
# Recompile the reconstructed RGB/one-shot hooks (standalone stub harness, same logic as
# custom_code/rgb_hooks.c) with QMK's ARM flags and print the disassembly, for side-by-side
# comparison with the dump:
#   dump keyboard_post_init_user             0x0800CF60..0x0800CF73
#   dump rgb_matrix_indicators_advanced_user 0x0800CF74..0x0800D00F
#   dump handle_oneshots body                0x0800D010..0x0800D07F
#   dump oneshot(_locked)_mods_changed_user  0x0800D088 / 0x0800D08C (b.w thunks)
# Compare with:
#   arm-none-eabi-objdump -D -b binary -m arm -M force-thumb --adjust-vma=0x08000000 \
#       --start-address=0x0800cf60 --stop-address=0x0800d090 keychron_v10max_backup/dump_a.bin
# Note: the original was built with gcc 13.2.1; the local toolchain is 15.2, so expect identical
# control flow (verified for all four functions) but possibly different basic-block placement.
set -e
HERE=$(cd "$(dirname "$0")" && pwd)
BIN="/Users/dexter/Library/Application Support/qmk/bin"
OUT=${1:-/tmp/rgb_hooks_recon.o}
"$BIN/arm-none-eabi-gcc" -c -Os -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 \
    -ffunction-sections -fdata-sections -fno-common -Wall -o "$OUT" "$HERE/rgb_hooks_recompile_check.c"
"$BIN/arm-none-eabi-objdump" -d "$OUT"
