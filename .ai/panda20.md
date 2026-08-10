# ZMX Panda20 numpad — programmed via VIA raw HID, never reflashed

The Panda20 (21-key wireless numpad, USB `36b0:3006`, name "RDMCTMZT Panda 20")
runs a **closed vendor QMK fork**: wireless (2.4G + 3 BLE channels) exists only
in the vendor firmware, so flashing anything from this tree would destroy it.
All customization is done by writing the dynamic keymap in the board's EEPROM
over the VIA raw-HID protocol — same channel the VIA web app uses.

## Tooling — `keyboards/zmx/panda20/`

- `via_keymap.py` — dependency-free programmer (`dump` / `diff` / `apply` / `show`).
  `apply` writes only changed keys and verifies each by readback.
- `keymap.txt` — the keymap as text: QMK keycode tokens (`KC_P7`, `MO(1)`,
  `LT(2,KC_ESC)`, `LCTL(KC_C)`, `M0`–`M15`), one 6x5 grid per layer; unknown
  keycodes round-trip as hex `0x____`.
- `backups/factory-keymap-2026-08-10.txt` — stock layout; `apply` it to restore.
- `via_definition.json` — VIA v3 sideload definition for usevia.app (Settings →
  Show Design tab → Design → load), only needed for the GUI route.

## Hardware / protocol facts

- VIA protocol **v12** (modern QMK ≥0.22 keycode values), **4 layers**,
  **6x5 matrix** (30 slots, 21 keys — rest are `KC_NO`), 16 macro slots.
- The raw-HID node is found by scanning `/sys/class/hidraw` for VID/PID plus
  usage page `0xFF60` (the board exposes 3 hidraw nodes; only one is VIA).
- Writes: 32-byte reports prefixed with `0x00` (unnumbered report) on the
  hidraw fd. Command `0x05` = set keycode (layer,row,col,hi,lo).

## Layer map (factory)

- Layer 0: numpad base. `MO(1)` sits at matrix `[0,1]`.
- Layer 1: vendor Fn layer — RGB controls + wireless mode keys. `MD_BLE1/2/3`
  (= `QK_KB_1..3`, 0x7E01–03) on the 1/2/3 keys, `MD_24G` (0x7E00) on 4,
  plus **undocumented vendor keycodes** — leave all of these where they are
  or wireless switching is lost:
  - `0x7E08` (Fn+Tab): battery-level display — floods the LEDs with a battery
    color (red = low) from key *release* until any other keypress dismisses it.
    Harmless but looks like the lighting is "stuck".
  - `0x7E0B` (Fn+Bspc), `0x7E0C` (Fn+Num): still unidentified; possibly
    win-lock / wireless status / factory reset — do not hold them down.
- Layers 2–3: unused clones of layer 0 — free for custom use.

## Linux setup (done on this machine 2026-08-10)

`/etc/udev/rules.d/92-panda20.rules` grants hidraw access:

```
KERNEL=="hidraw*", SUBSYSTEM=="hidraw", ATTRS{idVendor}=="36b0", ATTRS{idProduct}=="3006", MODE="0660", GROUP="users", TAG+="uaccess"
```

`GROUP="users"` is load-bearing: the logind `uaccess` ACL alone did not get
applied on this machine, and without group access Chrome/WebHID fails with
`NotAllowedError` → VIA misreports it as "not a VIA enabled keyboard".

## Gotchas

- Close any usevia.app tab while running `via_keymap.py` — concurrent readers
  on the same hidraw node steal each other's responses.
- The board must be in **wired USB mode**; the raw-HID interface is not
  reachable through the 2.4G dongle.
