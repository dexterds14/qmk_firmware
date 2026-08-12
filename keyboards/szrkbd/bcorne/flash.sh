#!/bin/sh
# Deploy the built UF2 to the Plum bootloader drive (macOS).
#
# `qmk flash` never detects this board: QMK's uf2 deployer identifies
# bootloader volumes by the standard INFO_UF2.TXT file, but the Plum
# bootloader names its info file PLUM_UF2.TXT, so the drive is never
# recognized and the deployer waits forever. This script does the same
# marker-file scan as uf2conv.py, just with Plum's filename, so it finds
# the drive whatever the volume happens to be called.
#
# Usage: build first (qmk compile -kb szrkbd/bcorne -km <keymap>), then
# run this and put the board into the bootloader (FN+Esc / FN+Backspace,
# bootmagic, or double-tap reset).

UF2="${1:-$(cd "$(dirname "$0")/../../.." && pwd)/.build/szrkbd_bcorne_default.uf2}"

if [ ! -f "$UF2" ]; then
    echo "UF2 not found: $UF2" >&2
    exit 1
fi

echo "Waiting for a volume with PLUM_UF2.TXT ..."
while :; do
    for vol in /Volumes/*; do
        if [ -f "$vol/PLUM_UF2.TXT" ]; then
            cp "$UF2" "$vol/" && echo "Flashed $(basename "$UF2") -> $vol" && exit 0
            echo "Copy to $vol failed" >&2
            exit 1
        fi
    done
    sleep 1
done
