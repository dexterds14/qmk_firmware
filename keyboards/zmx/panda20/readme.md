# ZMX Panda20

21-key wireless numpad (USB `36b0:3006`, "RDMCTMZT Panda 20").

**This is NOT a buildable QMK board.** The Panda20 runs a closed vendor QMK
fork (with 2.4G/BLE wireless support that upstream QMK lacks) and must never
be reflashed — the keymap is customized *in place* over the VIA raw-HID
protocol instead. There is intentionally no `keyboard.json` here, so the QMK
build system ignores this directory.

See [`.ai/panda20.md`](../../../.ai/panda20.md) at the repo root for the full
story (udev setup, protocol details, layer map, gotchas).

## Files

| File | Purpose |
|------|---------|
| `via_keymap.py` | keymap programmer speaking VIA protocol v12 over `/dev/hidrawX` |
| `keymap.txt` | the editable keymap (QMK keycode tokens, one grid per layer) |
| `via_definition.json` | VIA v3 sideload definition (for usevia.app, if ever needed) |
| `backups/` | factory keymap snapshot — apply it to restore stock behavior |

## Usage

```sh
python3 via_keymap.py dump    # board -> keymap.txt
# edit keymap.txt
python3 via_keymap.py diff    # preview changes (writes nothing)
python3 via_keymap.py apply   # write diffs to board EEPROM + verify readback
```

Changes are instant and persist in the board's EEPROM. Close any usevia.app
browser tab first — it holds the same hidraw node.
