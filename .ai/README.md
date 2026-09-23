# .ai — AI-facing documentation index

One file per topic. Read the doc whose topic matches your task.

| Doc | Read when… |
|-----|-----------|
| [`panda20.md`](panda20.md) | working with the ZMX Panda20 numpad (`keyboards/zmx/panda20/`) — it is programmed over VIA raw HID, **never** built/flashed from this tree |
| [`/AGENTS.md`](../AGENTS.md) | working on the dactyl_manuform 5x6 keymap (`keyboards/handwired/dactyl_manuform/5x6/`) — hardware quirks, the LTO/split-serial constraint, tap-dance/leader coupling, flash budget |
| [`bcorne-rgb.md`](bcorne-rgb.md) | adjusting or debugging RGB **at runtime** on the szrkbd bcorne dexter keymap (`keyboards/szrkbd/bcorne/keymaps/dexter/`) — deterministic effect-mode table, which effects ignore hue, the RAISE2 teal overlay, the double-stepping left knob (use the `M` key), EEPROM defaults, and the diagnostic traps to avoid |

Everything else in this repo is upstream QMK (fork of qmk/qmk_firmware; custom
work lives on the `dexter-ds` branch).
