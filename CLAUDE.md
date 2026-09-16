# CLAUDE.md — Keychron V10 Max custom firmware

You are working in a git worktree dedicated to the **Keychron V10 Max** (`keychron/v10_max/ansi_encoder`)
custom firmware, branch **`keychron-v10-max`** (based on Keychron's `wireless_playground` fork).
All custom work lives under `keyboards/keychron/v10_max/ansi_encoder/keymaps/dexter/` and
`keychron_v10max_backup/`. **Do not modify QMK core** (`quantum/`, `platforms/`, `keyboards/keychron/common/`).

## Start here
- **[.ai/](.ai/README.md)** — curated reference for agents. Read the doc that matches your task:
  overview, hardware, build-flash, keymap, gotchas, recovery.
- **[keyboards/keychron/v10_max/ansi_encoder/keymaps/dexter/readme.md](keyboards/keychron/v10_max/ansi_encoder/keymaps/dexter/readme.md)** — the keymap, user-facing (layers, behaviors, build/flash).
- **[AGENTS.md](AGENTS.md)** — branch conventions and the do-not list.
- **keychron_v10max_backup/ANALYSIS.md** and **RECONSTRUCTION_SPEC.md** — reverse-engineering evidence.

## The essentials (see .ai/ for detail)
- Build: `cd ~/code/qmk-keychron && qmk compile -kb keychron/v10_max/ansi_encoder -km dexter -j 8`.
- Flash: enter DFU with the **PCB reset button under the spacebar** (or right-Cmd, right-Cmd, Esc) — **never hold Esc/knob while plugging in** (erases EEPROM) — then
  `dfu-util -a 0 -d 0483:df11 -s 0x08000000:leave -D keychron_v10_max_ansi_encoder_dexter.bin`.
- Roll back to the original image: `dfu-util -a 0 -d 0483:df11 -s 0x08000000 -D keychron_v10max_backup/dump_a.bin`.
- Push to `dexter-ds` only, never to `keychron`.
- Before big multi-part work, read **.ai/gotchas.md** — several non-obvious traps (EEPROM wipes,
  macOS Control→Command remap wiped on reflash, RGB-LED colour behaviour, native BAT_LVL firing on
  release, editing files from a restricted worktree).
