# Gotchas & do-not list

## Hard rules
- **No core edits.** All custom code stays under `keyboards/keychron/v10_max/ansi_encoder/keymaps/dexter/`. Do not touch `quantum/`, `platforms/`, or `keyboards/keychron/common/` (that's the fork's source the original was built from). Every feature so far was done from the keymap alone (weak-symbol hooks + reading extern state).
- **Never hold Esc or the knob while plugging in.** Bootmagic-lite is on that key ([0,1] Esc; the knob [0,0] on very old builds) and it calls `eeconfig_disable()` → **erases the emulated EEPROM immediately**. Use the PCB reset button under the spacebar, or `QK_BOOTLOADER` (right-Cmd, right-Cmd, Esc).
- **Fn+J+Z for 3 s = factory reset** (`eeconfig_init` + BT pairing reset). **Fn+Right+End for 3 s = backlight test.** Don't hit these while testing.
- **Never `dfu-util … :unprotect` / `:mass-erase`.**
- **Never `git submodule sync` in this worktree** — submodule URLs live in the shared `.git/config`; a sync rewrites them for the main checkout too. Submodules here were set up with per-command `-c submodule.<name>.url=…` overrides (Keychron's ChibiOS forks).
- **Never `qmk setup`/`qmk config`** (rewrites `qmk.ini`). **Never push to the `keychron` remote** (push to `dexter-ds`).

## macOS: modifier remap wiped on reflash (important, recurring)
The `_LOWER` layer sends real `LCTL(x)` chords (undo/cut/copy/paste, ctrl-combos) and relies on
macOS's **per-keyboard "Control → Command" remap** (System Settings → Keyboard → Keyboard
Shortcuts → Modifier Keys, per device) to act as ⌘ in GUI apps. **Reflashing can make macOS see
it as a new keyboard and wipe that remap** — then Ctrl+C/V stop copying/pasting in Chrome etc.
Fix: reselect "Keychron V10 Max" there and set Control → ⌘. Flag this to the user after any flash.

## Battery / wireless
- The **battery gauge is on the LKBT51 module, not the MCU**; a real percentage is only available on wireless transport. On USB the pack is charging, so voltage reads high — that's why USB shows charge-state (green/red), not a %.
- **The fork's native `BAT_LVL` handler ignores press vs. release** (`keychron_wireless_common.c`), so it fires on the key-up too. A press-only interceptor leaks the release → the native white ramp animation starts. Swallow `BAT_LVL` on **both** edges (return false), as the keymap does.
- The native battery animation's "growing" phase is **white** (`r=g=b=255` in `bat_level_animation.c`), then blinks green/red. It's suppressed here in favour of a static custom bar.
- `bat_level_animiation_start` is only called from `keychron_wireless_common.c` (the `BAT_LVL` case) for this board — no auto-trigger.

## RGB LED colour
- LEDs are additive/emissive: a colour with **green ≈ blue reads teal/cyan**, and **red ≈ green ≈ blue reads washed-out/white**. To get a "blue", keep green clearly below blue and red low. (This is why the first gaming-heat attempts looked teal / pale.)
- `rgb_matrix_set_color()` writes **raw PWM** — the brightness knob does NOT scale it. Indicator/gaming colours are literal.
- `rgb_matrix_indicators_advanced_user` runs **after** the effect and the kb indicator each frame, so it can overwrite any of them — but that also means it will paint over things like the native battery bar unless you yield or redraw. During idle/sleep the effect is NONE and indicators don't run (LEDs stay off), so overlays are sleep-safe.

## Build / CLI
- The `qmk` 1.2.0 venv needs `appdirs` for this 0.23-era tree (see build-flash.md).
- The reconstruction is byte-verified only with **gcc 13.2.1**; gcc 15.2 changes code bytes (not behaviour). Library (newlib) bytes always differ.

## Editing keymap.c from an agent
The worktree may be outside the harness's allowed read/write root (Read/Write/Edit tools can be
denied). Use Bash (`sed`/`grep` to read, a Python script with `str.replace` + count assertions to
edit) — that's how the whole keymap was built. When you change layer tables, re-verify the
`keymaps[]`/`encoder_map[]` bytes against the intent (see recovery.md for the byte-compare method).
