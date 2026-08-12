#!/bin/sh
# Deploy the built UF2 to the Plum bootloader drive (macOS + Linux).
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

# Mounted-volume roots: /Volumes (macOS), /media/<user> and
# /run/media/<user> (Linux udisks/desktop automount), /media (bare).
find_plum_vol() {
    for vol in /Volumes/* /media/*/* /run/media/*/* /media/*; do
        if [ -f "$vol/PLUM_UF2.TXT" ]; then
            echo "$vol"
            return 0
        fi
    done
    return 1
}

# Linux without an automounter: the STM32F4Plum drive enumerates but never
# gets mounted. If we can see it by label, mount it via udisksctl (no root
# needed on a normal desktop session).
try_mount_unmounted() {
    command -v udisksctl >/dev/null 2>&1 || return 1
    command -v lsblk >/dev/null 2>&1 || return 1
    dev=$(lsblk -prno NAME,LABEL,MOUNTPOINT 2>/dev/null \
          | awk '$2 == "STM32F4Plum" && $3 == "" {print $1; exit}')
    [ -n "$dev" ] || return 1
    udisksctl mount -b "$dev" >/dev/null 2>&1
}

# Copy the UF2 onto the drive. A plain cp goes through the page cache and
# Linux flushes data and FAT metadata in no guaranteed order, so the Plum
# bootloader can see its "transfer complete" cue (final block / directory
# entry) while data blocks are still buffered on the host -- it then resets
# mid-transfer, the half-written app fails validation, and the board drops
# back into the bootloader (the "flashing takes two tries" symptom). GNU
# dd with O_DIRECT+O_SYNC writes every block to the device in order before
# returning; fall back to cp+sync where that isn't available (macOS).
deploy_uf2() {
    # $1 = volume
    if dd --version 2>/dev/null | grep -q GNU; then
        dd if="$UF2" of="$1/$(basename "$UF2")" bs=4096 \
           oflag=direct,sync conv=fsync status=none && sync
    else
        cp "$UF2" "$1/" && sync
    fi
}

echo "Waiting for a volume with PLUM_UF2.TXT ..."
while :; do
    if vol=$(find_plum_vol); then
        if deploy_uf2 "$vol"; then
            echo "Flashed $(basename "$UF2") -> $vol"
            exit 0
        fi
        echo "Copy to $vol failed" >&2
        exit 1
    fi
    try_mount_unmounted
    sleep 1
done
