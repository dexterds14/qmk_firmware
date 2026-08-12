#!/bin/sh
# Deploy the built UF2 to the Plum bootloader drive (macOS + Linux).
#
# `qmk flash` never detects this board: QMK's uf2 deployer identifies
# bootloader volumes by the standard INFO_UF2.TXT file, but the Plum
# bootloader names its info file PLUM_UF2.TXT, so the drive is never
# recognized and the deployer waits forever.
#
# Usage: build first (qmk compile -kb szrkbd/bcorne -km <keymap>), then
# run this and put the board into the bootloader (FN+Esc / FN+Backspace,
# bootmagic, or double-tap reset). Run under sudo to also get the SCSI
# timeout bump (optional).
#
# Flash reliability (diagnosed from dmesg, 2026-08-12): while the Plum
# bootloader erases/programs the STM32F401's large flash sectors it stops
# servicing USB for seconds at a time. Linux USB/SCSI error recovery then
# RESETS the device mid-transfer ("reset full-speed USB device" in dmesg).
# Whether the bootloader's transfer state survives that reset is luck: if
# yes, flashing completes ("device firmware changed" + app enumerates);
# if not, the half-written app fails validation and the board drops back
# into the bootloader. So this script judges the outcome by what
# RE-ENUMERATES after the write and auto-retries on failure.
#
# Identity subtleties learned the hard way:
# - After the board reboots away, the old mountpoint lingers STALE with
#   PLUM_UF2.TXT still readable from the page cache; never trust a
#   directory scan of /media. Resolve the mountpoint from the live block
#   device (lsblk by label -> findmnt) instead.
# - Right after the write the bootloader is STILL attached (flashing for
#   tens of seconds); "a Plum drive exists" is not a failure signal. A
#   NEW attachment is: track the USB bus:devnum, which increments on
#   every re-enumeration.

UF2="${1:-$(cd "$(dirname "$0")/../../.." && pwd)/.build/szrkbd_bcorne_default.uf2}"

if [ ! -f "$UF2" ]; then
    echo "UF2 not found: $UF2" >&2
    exit 1
fi

# --- Linux helpers (sysfs/lsblk/findmnt) -------------------------------

# Block device (e.g. "sdc") of an attached Plum bootloader drive.
find_plum_blk() {
    lsblk -rno NAME,LABEL 2>/dev/null \
        | awk '$2 == "STM32F4Plum" {print $1; exit}'
}

# USB bus:devnum of a block device -- unique per attachment session.
usb_id_of_blk() {
    p=$(readlink -f "/sys/block/$1/device" 2>/dev/null) || return 1
    while [ -n "$p" ] && [ "$p" != "/" ]; do
        if [ -f "$p/devnum" ] && [ -f "$p/busnum" ]; then
            echo "$(cat "$p/busnum"):$(cat "$p/devnum")"
            return 0
        fi
        p=${p%/*}
    done
    return 1
}

# Best effort: give the kernel more patience with the stalled drive before
# its error recovery resets the board mid-flash. Needs root.
bump_scsi_timeout() {
    if [ -w "/sys/block/$1/device/timeout" ]; then
        echo 120 > "/sys/block/$1/device/timeout" 2>/dev/null \
            && echo "(raised SCSI timeout for $1 to 120s)"
    fi
}

# Count enumerated app-firmware devices (VID:PID 45d4:1b32). The half
# being flashed is in the bootloader (different VID), so a COUNT INCREASE
# after the write means it booted the new app -- immune to the other half
# or another keyboard being plugged in.
count_app_devices() {
    c=0
    for f in /sys/bus/usb/devices/*/idVendor; do
        [ -e "$f" ] || continue
        [ "$(cat "$f" 2>/dev/null)" = "45d4" ] || continue
        [ "$(cat "${f%idVendor}idProduct" 2>/dev/null)" = "1b32" ] && c=$((c + 1))
    done
    echo "$c"
}

# Mountpoint of the LIVE Plum drive (never a stale leftover mount).
# Mounts it via udisksctl if the drive is attached but unmounted.
find_live_plum_vol() {
    blk=$(find_plum_blk)
    [ -n "$blk" ] || return 1
    mp=$(findmnt -rno TARGET "/dev/$blk" 2>/dev/null | head -1)
    if [ -z "$mp" ]; then
        command -v udisksctl >/dev/null 2>&1 || return 1
        udisksctl mount -b "/dev/$blk" >/dev/null 2>&1
        mp=$(findmnt -rno TARGET "/dev/$blk" 2>/dev/null | head -1)
    fi
    [ -n "$mp" ] && [ -f "$mp/PLUM_UF2.TXT" ] || return 1
    echo "$mp"
}

# One write attempt. bs=512 = one UF2 block per synchronous command, so a
# mid-write stall holds minimal data in flight. The write itself erroring
# is NOT conclusive either way (the board reboots out from under the last
# command on success too) -- the caller judges by what re-enumerates.
write_uf2() {
    if dd --version 2>/dev/null | grep -q GNU; then
        dd if="$UF2" of="$1/$(basename "$UF2")" bs=512 \
           oflag=direct,sync conv=fsync status=none
    else
        cp "$UF2" "$1/"
    fi
    sync
}

# --- macOS: no sysfs to watch outcomes with; legacy single attempt -----

if [ ! -d /sys/bus/usb/devices ]; then
    echo "Waiting for a volume with PLUM_UF2.TXT ..."
    while :; do
        for vol in /Volumes/*; do
            if [ -f "$vol/PLUM_UF2.TXT" ]; then
                if write_uf2 "$vol"; then
                    echo "Flashed $(basename "$UF2") -> $vol"
                    exit 0
                fi
                echo "Copy to $vol failed" >&2
                exit 1
            fi
        done
        sleep 1
    done
fi

# --- Linux: write, watch what re-enumerates, retry on failure ----------

MAX_ATTEMPTS=4
SETTLE_SECS=90

echo "Waiting for the STM32F4Plum bootloader drive ..."
attempt=1
while :; do
    if vol=$(find_live_plum_vol); then
        blk=$(find_plum_blk)
        session_id=$(usb_id_of_blk "$blk" 2>/dev/null || :)
        bump_scsi_timeout "$blk"
        apps_before=$(count_app_devices)

        echo "Attempt $attempt/$MAX_ATTEMPTS: writing $(basename "$UF2") -> $vol"
        write_uf2 "$vol" 2>/dev/null \
            || echo "(write reported an error; checking what the board did)"

        # Success = a new app device appears. Failure = a NEW bootloader
        # attachment (different bus:devnum). The ORIGINAL session hanging
        # around just means it is still flashing -- stalls of ~50s before
        # the app boots have been observed on successful flashes.
        t=0
        outcome=timeout
        while [ "$t" -lt "$SETTLE_SECS" ]; do
            if [ "$(count_app_devices)" -gt "$apps_before" ]; then
                outcome=ok
                break
            fi
            blk=$(find_plum_blk)
            if [ -n "$blk" ]; then
                id=$(usb_id_of_blk "$blk" 2>/dev/null || :)
                if [ -n "$id" ] && [ "$id" != "$session_id" ]; then
                    outcome=retry
                    break
                fi
            fi
            sleep 1
            t=$((t + 1))
        done

        case $outcome in
            ok)
                echo "Flashed OK: app firmware enumerated (attempt $attempt)"
                exit 0
                ;;
            retry)
                echo "Bootloader re-attached: flash did not stick, retrying"
                attempt=$((attempt + 1))
                if [ "$attempt" -gt "$MAX_ATTEMPTS" ]; then
                    echo "Giving up after $MAX_ATTEMPTS attempts" >&2
                    exit 1
                fi
                continue
                ;;
            timeout)
                echo "No app or new bootloader within ${SETTLE_SECS}s; unplug/replug and retry" >&2
                exit 1
                ;;
        esac
    fi
    sleep 1
done
