# Build, flash, and toolchains

Run everything from **inside this worktree** (`~/code/qmk-keychron`): the `qmk` CLI resolves
the firmware tree from the current directory first.

## Build
```sh
cd ~/code/qmk-keychron
qmk compile -kb keychron/v10_max/ansi_encoder -km dexter -j 8
```
Output: `keychron_v10_max_ansi_encoder_dexter.bin` in the worktree root (and `.build/…​.elf`).

- **CLI:** the installed `qmk` 1.2.0 (uv tool, Python 3.14) works against this 0.23-era tree,
  but its venv must contain `appdirs` or the startup check exits / offers to pip-install:
  `uv tool install --reinstall --with appdirs qmk==1.2.0` (already done on this machine).
- **Never run `qmk setup` or `qmk config`** — they rewrite `~/Library/Application Support/qmk/qmk.ini`.
- Default toolchain is the QMK-distributed **arm-none-eabi-gcc 15.2** at
  `~/Library/Application Support/qmk/bin` (auto-added to PATH by the CLI). Builds clean, no `-Werror` trouble.

## Alternate toolchain (matches the original firmware)
The original firmware was built with **arm-none-eabi-gcc 13.2.1** (Ubuntu apt). An xpack 13.2.1
is installed for byte-comparison; select it with `QMK_PATH_PREFIX`:
```sh
QMK_PATH_PREFIX=~/.local/share/xpack-arm-none-eabi-gcc-13.2.1/xpack-arm-none-eabi-gcc-13.2.1-1.1/bin \
  qmk compile -kb keychron/v10_max/ansi_encoder -km dexter -j 8
```
Only needed for the recovery verification (see recovery.md); everyday builds use gcc 15.2.

## Enter the bootloader (DFU)
- Switch the mode toggle to **Cable**, unplug USB, **hold the PCB reset button under the spacebar**, plug in, release.
- Or from running firmware: **right-Cmd, right-Cmd, Esc** (that's `OSL(_RAISE)` then `TO(_RAISE2)` then the `QK_BOOTLOADER` on `_RAISE2` Esc). Same effect as the reset button, no EEPROM wipe.
- **NEVER hold Esc or the knob while plugging in** — that's bootmagic and it **erases the EEPROM** on the spot.

## Flash
```sh
dfu-util -a 0 -d 0483:df11 -s 0x08000000:leave -D keychron_v10_max_ansi_encoder_dexter.bin
```
Or `qmk flash -kb keychron/v10_max/ansi_encoder -km dexter` (same dfu-util args).

## Watch-and-flash pattern (used all session)
Because entering DFU is a manual step, arm a background poller that flashes when the board appears:
```sh
for i in $(seq 1 1750); do
  if dfu-util -l 2>/dev/null | grep -q '0483:df11'; then
    dfu-util -a 0 -d 0483:df11 -s 0x08000000:leave -D keychron_v10_max_ansi_encoder_dexter.bin
    break
  fi
  sleep 2
done
```
Run it with `run_in_background`, then ask the user to enter DFU.

## Verify the flash / read firmware version over raw HID
```sh
"$(head -1 ~/.local/bin/qmk | sed 's/^#!//')" - <<'PY'   # the qmk venv python has hid
import hid
ds=[d for d in hid.enumerate(0x3434,0x09A0) if d['usage_page']==0xFF60 and d['usage']==0x61]
dev=hid.Device(path=ds[0]['path']); dev.write(b'\x00'+bytes([0xA1])+bytes(31))
print(bytes(dev.read(64,timeout=1500))[1:].split(b'\x00')[0].decode())  # "vX.Y.Z <build date>"
PY
```
Keychron raw HID (USB only, and only after this firmware's own commands are compiled in):
`0xA0` protocol, `0xA1` firmware version + build date, `0xA2` features, `0xA3` default layer.

## Roll back to the exact original firmware
```sh
dfu-util -a 0 -d 0483:df11 -s 0x08000000 -D keychron_v10max_backup/dump_a.bin
```
(`dump_a.bin` includes sector 1, so this also restores the original eeconfig.)

## Never
`dfu-util … :unprotect` or `:mass-erase` (mass-erases flash). Readout protection is off (RDP 0);
keep it that way.
