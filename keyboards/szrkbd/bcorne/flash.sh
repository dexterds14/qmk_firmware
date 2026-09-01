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
# Flash reliability (diagnosed from dmesg, 2026-08): while the Plum
# bootloader erases/programs the STM32F401's large flash sectors it stops
# servicing USB for seconds at a time. Linux USB/SCSI error recovery then
# RESETS the device mid-transfer. Outcomes observed on hardware:
#   1. Bootloader survives the reset and finishes: app enumerates. OK.
#   2. Transfer state dies; board reboots back into the bootloader as a
#      NEW USB session (devnum changes).
#   3. Transfer state dies; bootloader stays wedged in the SAME session,
#      still enumerated, going nowhere.
# So this script judges a write by what happens afterwards: app device
# appears = success; new bootloader session = rewrite; same session still
# there after the settle window = remount and rewrite into it (the
# software approximation of unplug/replug).
#
# Identity rules learned the hard way:
# - Detect the bootloader by USB VID:PID (239a:005d) in sysfs, never by
#   volume label or /media scan: stale mounts of departed devices keep
#   PLUM_UF2.TXT readable from the page cache, and label probing can lag
#   re-enumeration.
# - The bootloader session id is USB bus:devnum -- devnum increments on
#   every re-enumeration but survives kernel-initiated USB resets, which
#   is exactly the distinction needed.
# - A dd error is not conclusive: on success the board reboots out from
#   under the final write; on failure writes die midway. Only what
#   re-enumerates afterwards is trustworthy.

UF2="${1:-$(cd "$(dirname "$0")/../../.." && pwd)/.build/szrkbd_bcorne_default.uf2}"

if [ ! -f "$UF2" ]; then
    echo "UF2 not found: $UF2" >&2
    exit 1
fi

# One write. bs=512 = one UF2 block per synchronous command, so a stall
# holds minimal data in flight. (GNU dd on Linux; plain cp on macOS.)
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

# --- Linux helpers ------------------------------------------------------

# First attached Plum bootloader (tinyuf2 VID:PID 239a:005d), printed as
# "bus:devnum /sys/bus/usb/devices/<dev>".
first_plum_session() {
    for d in /sys/bus/usb/devices/*; do
        [ -f "$d/idVendor" ] || continue
        [ "$(cat "$d/idVendor" 2>/dev/null)" = "239a" ] || continue
        [ "$(cat "$d/idProduct" 2>/dev/null)" = "005d" ] || continue
        echo "$(cat "$d/busnum" 2>/dev/null):$(cat "$d/devnum" 2>/dev/null) $d"
        return 0
    done
    return 1
}

# Block device name (e.g. sdc) beneath a USB device's sysfs path; fails
# until the kernel has finished SCSI probing.
blk_of_usb() {
    for b in "$1"/*/host*/target*/*/block/*; do
        [ -e "$b" ] || continue
        basename "$b"
        return 0
    done
    return 1
}

# Mountpoint of a block device, mounting it via udisksctl if needed.
vol_of_blk() {
    mp=$(findmnt -rno TARGET "/dev/$1" 2>/dev/null | head -1)
    if [ -z "$mp" ]; then
        command -v udisksctl >/dev/null 2>&1 || return 1
        udisksctl mount -b "/dev/$1" >/dev/null 2>&1
        mp=$(findmnt -rno TARGET "/dev/$1" 2>/dev/null | head -1)
    fi
    [ -n "$mp" ] && [ -f "$mp/PLUM_UF2.TXT" ] || return 1
    echo "$mp"
}

# Drop a possibly-wedged mount so the next vol_of_blk gets a fresh one.
refresh_mount() {
    command -v udisksctl >/dev/null 2>&1 || return 0
    udisksctl unmount -b "/dev/$1" >/dev/null 2>&1 \
        || udisksctl unmount --force -b "/dev/$1" >/dev/null 2>&1 \
        || :
}

# Best effort: more kernel patience before its error recovery resets the
# stalled board mid-flash. Needs root.
bump_scsi_timeout() {
    if [ -w "/sys/block/$1/device/timeout" ]; then
        echo 120 > "/sys/block/$1/device/timeout" 2>/dev/null \
            && echo "(raised SCSI timeout for $1 to 120s)"
    fi
}

# Count enumerated app-firmware devices (VID:PID 45d4:1b32). The half
# being flashed is in the bootloader, so a COUNT INCREASE after the write
# means it booted the new app -- immune to the other half being plugged in.
count_app_devices() {
    c=0
    for f in /sys/bus/usb/devices/*/idVendor; do
        [ -e "$f" ] || continue
        [ "$(cat "$f" 2>/dev/null)" = "45d4" ] || continue
        [ "$(cat "${f%idVendor}idProduct" 2>/dev/null)" = "1b32" ] && c=$((c + 1))
    done
    echo "$c"
}

# --- Linux main loop ----------------------------------------------------

MAX_ATTEMPTS=5
# Observed on hardware: a flash that actually sticks boots the app in well
# under 15s, so there is no point waiting longer to judge the outcome.
SETTLE_CLEAN=15   # write reported success: wait this long for the app to boot
SETTLE_ERROR=15   # write errored: same window to see if it booted anyway

echo "Waiting for the Plum bootloader (USB 239a:005d) ..."
attempt=1
while :; do
    sess=$(first_plum_session) || { sleep 1; continue; }
    session_id=${sess%% *}
    usb_path=${sess#* }
    blk=$(blk_of_usb "$usb_path") || { sleep 1; continue; }
    vol=$(vol_of_blk "$blk") || { sleep 1; continue; }

    bump_scsi_timeout "$blk"
    apps_before=$(count_app_devices)

    echo "Attempt $attempt/$MAX_ATTEMPTS: writing $(basename "$UF2") -> $vol (session $session_id)"
    w0=$(date +%s)
    if write_uf2 "$vol" 2>/dev/null; then
        settle=$SETTLE_CLEAN
        echo "Write completed in $(($(date +%s) - w0))s; waiting up to ${settle}s for the board to reboot"
    else
        settle=$SETTLE_ERROR
        echo "Write errored after $(($(date +%s) - w0))s; watching what the board does (up to ${settle}s)"
    fi

    t=0
    outcome=timeout
    while [ "$t" -lt "$settle" ]; do
        if [ "$(count_app_devices)" -gt "$apps_before" ]; then
            outcome=ok
            break
        fi
        cur=$(first_plum_session) || cur=""
        cur_id=${cur%% *}
        if [ -n "$cur_id" ] && [ "$cur_id" != "$session_id" ]; then
            outcome=newsession
            break
        fi
        sleep 1
        t=$((t + 1))
        [ $((t % 15)) -eq 0 ] && echo "  ... still waiting (${t}s/${settle}s, bootloader session unchanged)"
    done

    case $outcome in
        ok)
            echo "Flashed OK: app firmware enumerated (attempt $attempt)"
            exit 0
            ;;
        newsession)
            echo "Bootloader re-attached (session $cur_id): flash did not stick, retrying"
            ;;
        timeout)
            if first_plum_session >/dev/null 2>&1; then
                echo "Bootloader still attached (same session) but no app appeared: remounting and rewriting"
                refresh_mount "$blk"
            else
                echo "Board vanished without re-enumerating; replug USB and re-run" >&2
                exit 1
            fi
            ;;
    esac

    attempt=$((attempt + 1))
    if [ "$attempt" -gt "$MAX_ATTEMPTS" ]; then
        echo "Giving up after $MAX_ATTEMPTS attempts; replug USB and re-run" >&2
        exit 1
    fi
done
