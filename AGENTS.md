# AGENTS.md — keychron-v10-max branch notes

This branch lives in a **git worktree** (`~/code/qmk-keychron`) of `~/code/qmk` and is based on
Keychron's fork of QMK, branch `wireless_playground` (remote `keychron`, QMK 0.23.2 era, keycode
spec 0.0.3, `RGB_*` names). It exists to hold the recovered custom firmware of a **Keychron V10 Max
ANSI knob** (USB 0x3434:0x09A0, STM32F401xC, ROM DFU bootloader 0483:df11), whose original source
was lost. Everything custom is confined to:

```
keyboards/keychron/v10_max/ansi_encoder/keymaps/dexter/   # the recovered keymap (keymap.c, config.h, rules.mk, readme.md)
keychron_v10max_backup/                                    # flash dump, DFU metadata, analysis evidence, tools, reference builds
```

Do not modify `quantum/`, `platforms/`, `keyboards/keychron/common/` or the board directory
itself; the fork's board files are what the original firmware was built from.

## Provenance of the keymap (short version; details in keychron_v10max_backup/ANALYSIS.md)

- `keychron_v10max_backup/dump_a.bin` is the full 256 KB flash image read over DFU on 2026-09-10
  (sha256 in `sha256.txt`, two identical reads, readout protection level 0).
- The image was built 2024-07-09 from fork commit ~`1011db8c8d` (2024-07-01) with Ubuntu 24.04's
  `gcc-arm-none-eabi` 13.2.1, no LTO, no VIA.
- `keymaps[]` (6 layers) and `encoder_map[]` were extracted from the image and are byte-identical
  when recompiled (`keymap_recovered_table.c`). The custom C (tap dance, leader, RGB indicators,
  boot hook, `./` and `../` keys, one-shot helpers) was recovered by disassembly/decompilation and
  verified by adversarial review; see `RECONSTRUCTION_SPEC.md` for per-item confidence.
- Behavioral differences vs the original that are known and accepted are listed in
  `keymaps/dexter/readme.md`.

## Features added after recovery

The `dexter` keymap started as a byte-faithful reconstruction of the dumped firmware. Changes
made since (documented in `keymaps/dexter/readme.md`):
- **Gaming mode** — the **M1** key (`GM_TOGG`, matrix `[1,0]`, replacing that key's base-layer
  Backspace) toggles two new layers `_GAMING` (stock Windows base + Fn-thumb → `MO(_GAME_FN)`,
  right space → Enter, right B → Backspace) and `_GAME_FN` (stock Windows Fn). It flips a
  `gaming_mode` flag and `default_layer_set`s the base; RGB becomes a solid dark blue with the
  live typing heatmap recoloured to light blue via an overlay in
  `rgb_matrix_indicators_advanced_user` (no effect/EEPROM change; sleep still blanks the LEDs).
  Tune the blues via `GAME_OUTER_*`/`GAME_INNER_*` in `keymap.c`.
- Only `_QWERTY[1,0]` changed among the six recovered layers (verified: all other keymap bytes
  still equal the dump). This is a new feature, so the build is intentionally no longer
  byte-identical to `dump_a.bin`.
- No `QK_BOOTLOADER` key was added — the recovered one on `_RAISE2` Esc (right-Cmd, right-Cmd,
  Esc) already replaces the physical reset button.

Auto-sleep and idle-RGB-off/on in wireless mode were confirmed already-default (only on battery;
USB power blocks sleep); no config change was needed.

## Build / flash

Run `qmk` from inside this worktree (the CLI resolves the firmware tree from cwd first; do NOT run
`qmk setup` or `qmk config`, they rewrite `~/Library/Application Support/qmk/qmk.ini`).

```sh
cd ~/code/qmk-keychron
qmk compile -kb keychron/v10_max/ansi_encoder -km dexter -j 8
# optional: build with the original firmware's compiler family (xpack GCC 13.2.1) for byte comparison
QMK_PATH_PREFIX=~/.local/share/xpack-arm-none-eabi-gcc-13.2.1/xpack-arm-none-eabi-gcc-13.2.1-1.1/bin \
  qmk compile -kb keychron/v10_max/ansi_encoder -km dexter -j 8
```

Enter the bootloader with the **PCB reset button under the spacebar** (switch on Cable, unplug,
hold the button, plug in). Flash:

```sh
dfu-util -a 0 -d 0483:df11 -s 0x08000000:leave -D keychron_v10_max_ansi_encoder_dexter.bin
```

Roll back to the exact original firmware (code and EEPROM):

```sh
dfu-util -a 0 -d 0483:df11 -s 0x08000000 -D keychron_v10max_backup/dump_a.bin
```

The `.bin` zero-fills flash sector 1 (0x08004000, the emulated EEPROM), so flashing resets
eeconfig (RGB settings etc.) to compiled defaults. This is also what Keychron's own images do.

## Do NOT

- Hold **Esc or the knob** while plugging the board in: bootmagic erases the EEPROM sector on the
  spot (Esc since fork commit 2024-03-21; the knob position before that).
- Send raw HID **0xAA** (Bluetooth-module DFU) or **0xAB** (factory test) frames.
- Press **Fn+J+Z** for 3 s (factory reset: `eeconfig_init()` + BT pairing reset) or
  **Fn+Right+End** for 3 s (backlight test mode) while testing.
- Run `dfu-util` with `:unprotect` or `:mass-erase`.
- Run `git submodule sync` in this worktree: submodule URLs live in the shared `.git/config` of
  `~/code/qmk`. Submodules here were initialized with per-command URL overrides:
  `git -c submodule.lib/chibios.url=https://github.com/Keychron/ChibiOS.git
   -c submodule.lib/chibios-contrib.url=https://github.com/Keychron/ChibiOS-Contrib
   submodule update --init --reference ~/code/qmk/.git/modules/lib/<name> -- lib/<name>`
- Push to the `keychron` remote. Push this branch to `dexter-ds` only.
- Name any file `keymap.json` inside a keymap directory (the build prefers it over `keymap.c`).

## Environment notes

- QMK CLI 1.2.0 (uv tool venv, Python 3.14) works with this 0.23-era tree once the venv contains
  `appdirs` (`uv tool install --reinstall --with appdirs qmk==1.2.0`); the fork's CLI startup check
  otherwise exits or offers to pip-install.
- QMK toolchain gcc 15.2 builds this tree without `ALLOW_WARNINGS`; gcc 13.2.1 (xpack) too.
- Reference worktree `~/code/qmk-keychron-ref` is detached (at `1011db8c8d`, later `8e390f92a2`, the exact original source commit) and holds
  the reference builds used for function matching (`keychron_v10max_backup/refs/`).
- The live board never answered VIA/Keychron raw HID from macOS hidapi even though the firmware
  implements `kc_raw_hid_rx`; treat host-side raw HID on macOS as unverified.
