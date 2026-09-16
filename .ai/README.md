# .ai — reference for future agents

This folder is curated operational knowledge for anyone (human or AI) working on the
**Keychron V10 Max** custom firmware in this worktree. Read `../CLAUDE.md` first, then the
doc here that matches your task.

| Doc | Read it when you need to… |
|---|---|
| [overview.md](overview.md) | understand what this project is, the branches/worktrees/remotes, and current status |
| [hardware.md](hardware.md) | know the board's MCU, matrix, RGB, wireless, EEPROM, bootloader facts |
| [build-flash.md](build-flash.md) | build the firmware, enter DFU, flash, roll back, or pick a toolchain |
| [keymap.md](keymap.md) | change the keymap: layers, custom keycodes, gaming mode, battery readout, RGB |
| [gotchas.md](gotchas.md) | avoid the traps (EEPROM wipes, macOS remap, RGB-LED color, no-core-edits, etc.) |
| [recovery.md](recovery.md) | understand how this firmware was recovered from a flash dump and how to re-verify it |

Other in-repo references (authoritative detail):
- `../keyboards/keychron/v10_max/ansi_encoder/keymaps/dexter/readme.md` — the keymap, user-facing.
- `../AGENTS.md` — branch conventions and the do-not list (also summarized in gotchas.md).
- `../keychron_v10max_backup/ANALYSIS.md` and `RECONSTRUCTION_SPEC.md` — the reverse-engineering evidence, per-line.

Everything custom lives under `keyboards/keychron/v10_max/ansi_encoder/keymaps/dexter/` and
`keychron_v10max_backup/`. Do not modify QMK core (`quantum/`, `platforms/`,
`keyboards/keychron/common/`).
