# Project overview

## What this is
Recovery and extension of the lost custom QMK firmware for a **Keychron V10 Max ANSI (knob)**
Alice-layout keyboard. The original firmware's source was lost; it was recovered from a DFU
flash dump, rebuilt as source, then extended (gaming mode, battery readout). All verified on
the physical board.

Keyboard target: `keychron/v10_max/ansi_encoder`, keymap `dexter`.

## Worktrees (this is a git worktree setup)
- `~/code/qmk-keychron` — **this** worktree, branch **`keychron-v10-max`**. All active work.
- `~/code/qmk` — the main repo, branch `szrkbd-bcorne-port` (a different keyboard, `szrkbd/bcorne`). Shares the object store.
- `~/code/qmk-keychron-ref` — detached at fork commit **`8e390f92a2`** (the exact commit the
  original firmware was built from). Used only for byte-for-byte verification of the recovery.

## Branch / remotes
- Branch `keychron-v10-max` is based on Keychron's fork branch `wireless_playground`
  (QMK 0.23.2 era; `RGB_*` keycode names; keycode spec 0.0.3).
- Remote **`dexter-ds`** (`git@github.com:dexterds14/qmk_firmware.git`) — the user's fork. **Push here.**
- Remote **`keychron`** (`https://github.com/Keychron/qmk_firmware.git`) — upstream fork. **Never push here.**
- Push with: `git push dexter-ds keychron-v10-max`.

## Status (what's done)
- **Recovered keymap** (`keymaps/dexter/`): 6 layers reconstructed from the dump, byte-identical to the original tables. See recovery.md.
- **Layer tables** reformatted to mirror the physical Alice layout (whitespace only).
- **Gaming mode** (layers `_GAMING`/`_GAME_FN`, toggled by M1): stock Windows base + solid-blue RGB with a blue typing heatmap.
- **Battery readout** on `BAT_LVL`: wireless % bar / USB charge-state bar.
- Confirmed: builds with gcc 15.2 and xpack gcc 13.2.1; flashed and tested on hardware.

## The build/flash loop used here
Because DFU requires the user to physically put the board in the bootloader, the pattern all
session was: edit → `qmk compile` → arm a background watcher that polls `dfu-util -l` and
flashes when the board appears → ask the user to enter DFU → verify re-enumeration. See build-flash.md.
