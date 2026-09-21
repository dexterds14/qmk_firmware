# .ai — AI-facing documentation index

One file per topic. Read the doc whose topic matches your task.

| Doc | Read when… |
|-----|-----------|
| [`panda20.md`](panda20.md) | working with the ZMX Panda20 numpad (`keyboards/zmx/panda20/`) — it is programmed over VIA raw HID, **never** built/flashed from this tree |
| [`/AGENTS.md`](../AGENTS.md) | working on the dactyl_manuform 5x6 keymap (`keyboards/handwired/dactyl_manuform/5x6/`) — hardware quirks, the LTO/split-serial constraint, tap-dance/leader coupling, flash budget |
| [`visualizer.md`](visualizer.md) | working on / viewing the keymap visualizer (`keyboards/handwired/dactyl_manuform/5x6/visualizer/`) — opens from `file://`; regenerate `keymap-data.js` after any keymap/keyboard.json/config.h change |

Everything else in this repo is upstream QMK (fork of qmk/qmk_firmware; custom
work lives on the `dexter-ds` branch).
