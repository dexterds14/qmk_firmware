#!/usr/bin/env python3
"""Program the ZMX Panda20 numpad over the VIA raw-HID protocol.

No VIA app, no flashing: keycodes are written into the keyboard's own
EEPROM through the same protocol the VIA web app uses, so the vendor
firmware (wireless, RGB, ...) is untouched.

Usage:
  via_keymap.py dump   [file]   # read keymap from board -> text file (default keymap.txt)
  via_keymap.py apply  [file]   # write changed keys from text file -> board (with verify)
  via_keymap.py diff   [file]   # show what apply would change, write nothing
  via_keymap.py show            # print the board's current keymap to stdout

Text format: one block per layer, `[N]` header, then ROWS x COLS keycode
tokens in matrix order. `#` starts a comment. Any keycode can be written
as a hex literal (0x5221) if it has no name here; dump emits hex for
unknown values, so files always round-trip losslessly.
"""

import glob
import os
import re
import sys

VID, PID = "36B0", "3006"
ROWS, COLS = 6, 5
NUM_LAYERS = 4

# ---------------------------------------------------------------- keycodes
# Modern QMK (>= 0.22) keycode values, as used by VIA protocol 12.
BASIC = {
    "KC_NO": 0x00, "KC_TRNS": 0x01,
    "KC_A": 0x04, "KC_B": 0x05, "KC_C": 0x06, "KC_D": 0x07, "KC_E": 0x08,
    "KC_F": 0x09, "KC_G": 0x0A, "KC_H": 0x0B, "KC_I": 0x0C, "KC_J": 0x0D,
    "KC_K": 0x0E, "KC_L": 0x0F, "KC_M": 0x10, "KC_N": 0x11, "KC_O": 0x12,
    "KC_P": 0x13, "KC_Q": 0x14, "KC_R": 0x15, "KC_S": 0x16, "KC_T": 0x17,
    "KC_U": 0x18, "KC_V": 0x19, "KC_W": 0x1A, "KC_X": 0x1B, "KC_Y": 0x1C,
    "KC_Z": 0x1D,
    "KC_1": 0x1E, "KC_2": 0x1F, "KC_3": 0x20, "KC_4": 0x21, "KC_5": 0x22,
    "KC_6": 0x23, "KC_7": 0x24, "KC_8": 0x25, "KC_9": 0x26, "KC_0": 0x27,
    "KC_ENT": 0x28, "KC_ESC": 0x29, "KC_BSPC": 0x2A, "KC_TAB": 0x2B,
    "KC_SPC": 0x2C, "KC_MINS": 0x2D, "KC_EQL": 0x2E, "KC_LBRC": 0x2F,
    "KC_RBRC": 0x30, "KC_BSLS": 0x31, "KC_NUHS": 0x32, "KC_SCLN": 0x33,
    "KC_QUOT": 0x34, "KC_GRV": 0x35, "KC_COMM": 0x36, "KC_DOT": 0x37,
    "KC_SLSH": 0x38, "KC_CAPS": 0x39,
    "KC_F1": 0x3A, "KC_F2": 0x3B, "KC_F3": 0x3C, "KC_F4": 0x3D,
    "KC_F5": 0x3E, "KC_F6": 0x3F, "KC_F7": 0x40, "KC_F8": 0x41,
    "KC_F9": 0x42, "KC_F10": 0x43, "KC_F11": 0x44, "KC_F12": 0x45,
    "KC_PSCR": 0x46, "KC_SCRL": 0x47, "KC_PAUS": 0x48, "KC_INS": 0x49,
    "KC_HOME": 0x4A, "KC_PGUP": 0x4B, "KC_DEL": 0x4C, "KC_END": 0x4D,
    "KC_PGDN": 0x4E, "KC_RGHT": 0x4F, "KC_LEFT": 0x50, "KC_DOWN": 0x51,
    "KC_UP": 0x52,
    "KC_NUM": 0x53, "KC_PSLS": 0x54, "KC_PAST": 0x55, "KC_PMNS": 0x56,
    "KC_PPLS": 0x57, "KC_PENT": 0x58,
    "KC_P1": 0x59, "KC_P2": 0x5A, "KC_P3": 0x5B, "KC_P4": 0x5C,
    "KC_P5": 0x5D, "KC_P6": 0x5E, "KC_P7": 0x5F, "KC_P8": 0x60,
    "KC_P9": 0x61, "KC_P0": 0x62, "KC_PDOT": 0x63,
    "KC_NUBS": 0x64, "KC_APP": 0x65, "KC_PEQL": 0x67,
    "KC_F13": 0x68, "KC_F14": 0x69, "KC_F15": 0x6A, "KC_F16": 0x6B,
    "KC_F17": 0x6C, "KC_F18": 0x6D, "KC_F19": 0x6E, "KC_F20": 0x6F,
    "KC_F21": 0x70, "KC_F22": 0x71, "KC_F23": 0x72, "KC_F24": 0x73,
    "KC_PCMM": 0x85,
    "KC_LCTL": 0xE0, "KC_LSFT": 0xE1, "KC_LALT": 0xE2, "KC_LGUI": 0xE3,
    "KC_RCTL": 0xE4, "KC_RSFT": 0xE5, "KC_RALT": 0xE6, "KC_RGUI": 0xE7,
    # system / consumer (basic range in modern QMK)
    "KC_PWR": 0xA5, "KC_SLEP": 0xA6, "KC_WAKE": 0xA7,
    "KC_MUTE": 0xA8, "KC_VOLU": 0xA9, "KC_VOLD": 0xAA,
    "KC_MNXT": 0xAB, "KC_MPRV": 0xAC, "KC_MSTP": 0xAD, "KC_MPLY": 0xAE,
    "KC_MSEL": 0xAF, "KC_EJCT": 0xB0, "KC_MAIL": 0xB1, "KC_CALC": 0xB2,
    "KC_MYCM": 0xB3, "KC_WSCH": 0xB4, "KC_WHOM": 0xB5, "KC_WBAK": 0xB6,
    "KC_WFWD": 0xB7, "KC_WSTP": 0xB8, "KC_WREF": 0xB9, "KC_WFAV": 0xBA,
    "KC_MFFD": 0xBB, "KC_MRWD": 0xBC, "KC_BRIU": 0xBD, "KC_BRID": 0xBE,
}

QUANTUM = {
    "QK_BOOT": 0x7C00, "QK_RBT": 0x7C01, "DB_TOGG": 0x7C02, "EE_CLR": 0x7C03,
    "RGB_TOG": 0x7820, "RGB_MOD": 0x7821, "RGB_RMOD": 0x7822,
    "RGB_HUI": 0x7823, "RGB_HUD": 0x7824, "RGB_SAI": 0x7825,
    "RGB_SAD": 0x7826, "RGB_VAI": 0x7827, "RGB_VAD": 0x7828,
    "RGB_SPI": 0x7829, "RGB_SPD": 0x782A,
    # Panda20 vendor keycodes (VIA customKeycodes -> QK_KB_0..4)
    "MD_24G": 0x7E00, "MD_BLE1": 0x7E01, "MD_BLE2": 0x7E02,
    "MD_BLE3": 0x7E03, "MD_USB": 0x7E04,
}
# macro keys M0..M15
for _i in range(16):
    QUANTUM[f"M{_i}"] = 0x7700 + _i

NAME_TO_VAL = {**BASIC, **QUANTUM}
# aliases accepted on input
for _a, _b in [("KC_TRANSPARENT", "KC_TRNS"), ("_______", "KC_TRNS"),
               ("XXXXXXX", "KC_NO"), ("KC_NLCK", "KC_NUM"),
               ("KC_NUM_LOCK", "KC_NUM"), ("RESET", "QK_BOOT")]:
    NAME_TO_VAL[_a] = NAME_TO_VAL[_b]
VAL_TO_NAME = {}
for _n, _v in {**BASIC, **QUANTUM}.items():
    VAL_TO_NAME.setdefault(_v, _n)

MODS = {"LCTL": 0x01, "LSFT": 0x02, "LALT": 0x04, "LGUI": 0x08,
        "RCTL": 0x11, "RSFT": 0x12, "RALT": 0x14, "RGUI": 0x18}
MOD_ALIAS = {"C": "LCTL", "S": "LSFT", "A": "LALT", "G": "LGUI"}


def encode(tok):
    """keycode token -> 16-bit value"""
    tok = tok.strip()
    if re.fullmatch(r"0x[0-9a-fA-F]+", tok):
        return int(tok, 16)
    if tok in NAME_TO_VAL:
        return NAME_TO_VAL[tok]
    m = re.fullmatch(r"(\w+)\(([^()]*(?:\([^()]*\))?)\)", tok)
    if not m:
        raise ValueError(f"unknown keycode: {tok!r}")
    fn, arg = m.group(1), m.group(2).strip()
    fn = MOD_ALIAS.get(fn, fn)
    layer_fns = {"TO": 0x5200, "MO": 0x5220, "DF": 0x5240, "TG": 0x5260,
                 "OSL": 0x5280, "TT": 0x52C0}
    if fn in layer_fns:
        return layer_fns[fn] | int(arg)
    if fn == "OSM":
        return 0x52A0 | MODS[arg.replace("MOD_", "L").replace("LL", "L")] & 0x1F
    if fn == "LT":
        layer, kc = arg.split(",")
        return 0x4000 | (int(layer) << 8) | encode(kc.strip())
    if fn in MODS:  # LCTL(kc) etc.
        return (MODS[fn] << 8) | encode(arg)
    if fn.endswith("_T") and fn[:-2] in MODS:  # LCTL_T(kc) mod-tap
        return 0x2000 | (MODS[fn[:-2]] << 8) | encode(arg)
    raise ValueError(f"unknown keycode: {tok!r}")


def decode(val):
    """16-bit value -> keycode token (hex if unnamed)"""
    if val in VAL_TO_NAME:
        return VAL_TO_NAME[val]
    for fn, base in [("TO", 0x5200), ("MO", 0x5220), ("DF", 0x5240),
                     ("TG", 0x5260), ("OSL", 0x5280), ("TT", 0x52C0)]:
        if base <= val < base + 0x20:
            return f"{fn}({val - base})"
    if 0x4000 <= val <= 0x4FFF:
        return f"LT({(val >> 8) & 0xF},{decode(val & 0xFF)})"
    if 0x2000 <= val <= 0x3FFF:
        mod = (val >> 8) & 0x1F
        for name, bits in MODS.items():
            if bits == mod:
                return f"{name}_T({decode(val & 0xFF)})"
    if 0x0100 <= val <= 0x1FFF:
        mod = (val >> 8) & 0x1F
        side = "R" if mod & 0x10 else "L"
        bits = [n for b, n in [(0x01, "CTL"), (0x02, "SFT"), (0x04, "ALT"),
                               (0x08, "GUI")] if mod & b]
        if 1 <= len(bits) <= 2:  # encode() parses at most one nesting level
            inner = decode(val & 0xFF)
            for name in reversed(bits):
                inner = f"{side}{name}({inner})"
            return inner
    return f"0x{val:04X}"


# ---------------------------------------------------------------- HID I/O
def find_node():
    for h in glob.glob("/sys/class/hidraw/hidraw*"):
        try:
            ue = open(h + "/device/uevent", "rb").read().upper()
            if VID.encode() in ue and PID.encode() in ue:
                rd = open(h + "/device/report_descriptor", "rb").read()
                if bytes([0x06, 0x60, 0xFF]) in rd:  # usage page 0xFF60
                    return "/dev/" + os.path.basename(h)
        except OSError:
            continue
    sys.exit("Panda20 raw-HID interface not found (is it plugged in via USB?)")


class Board:
    def __init__(self):
        self.fd = os.open(find_node(), os.O_RDWR)

    def xfer(self, cmd, payload=b""):
        pkt = bytes([cmd]) + payload
        os.write(self.fd, b"\x00" + pkt + bytes(32 - len(pkt)))
        resp = os.read(self.fd, 32)
        if resp[0] != cmd:
            raise IOError(f"response mismatch: sent 0x{cmd:02X}, got 0x{resp[0]:02X}"
                          " (close the VIA browser tab and retry)")
        return resp

    def read_keymap(self):
        total = NUM_LAYERS * ROWS * COLS * 2
        buf = b""
        off = 0
        while off < total:
            n = min(28, total - off)
            r = self.xfer(0x12, off.to_bytes(2, "big") + bytes([n]))
            buf += r[4:4 + n]
            off += n
        km = []
        for layer in range(NUM_LAYERS):
            grid = []
            for row in range(ROWS):
                base = (layer * ROWS * COLS + row * COLS) * 2
                grid.append([int.from_bytes(buf[base + c * 2: base + c * 2 + 2], "big")
                             for c in range(COLS)])
            km.append(grid)
        return km

    def set_keycode(self, layer, row, col, val):
        self.xfer(0x05, bytes([layer, row, col]) + val.to_bytes(2, "big"))

    def get_keycode(self, layer, row, col):
        r = self.xfer(0x04, bytes([layer, row, col]))
        return int.from_bytes(r[4:6], "big")


# ---------------------------------------------------------------- text file
HEADER = """\
# ZMX Panda20 keymap — matrix is 6 rows x 5 cols; not every position has a key.
# Keys are referred to by their PHYSICAL (stock-layer) names. Column guide
# for every layer grid below (col0..col4 left to right):
#
#   row 0:  Esc     Fn      Tab     --      Bspc
#   row 1:  Num     /       *       -       --
#   row 2:  7       8       9       +       --
#   row 3:  4       5       6       --      --
#   row 4:  1       --      2       3       --
#   row 5:  0       .       Enter   --      --
#
# ("--" = no physical key: keep KC_NO. Note 1/2/3 skip col1, and Enter is
#  row 5 col 2, not row 4. [0,3] only exists on the split-backspace variant.)
# Tokens: QMK names (KC_*, MO(n), LT(n,kc), LCTL(kc), MD_USB, M0..M15, ...) or hex 0x____.
"""


ROW_GUIDE = ["Esc | Fn | Tab | -- | Bspc",
             "Num | / | * | -",
             "7 | 8 | 9 | +",
             "4 | 5 | 6",
             "1 | -- | 2 | 3",
             "0 | . | Enter"]


def fmt_keymap(km):
    out = [HEADER]
    for layer, grid in enumerate(km):
        out.append(f"[{layer}]")
        width = max(len(decode(v)) for row in grid for v in row) + 2
        for r, row in enumerate(grid):
            cells = "".join(decode(v).ljust(width) for v in row)
            out.append(f"{cells.ljust(5 * width)}#  {ROW_GUIDE[r]}")
        out.append("")
    return "\n".join(out)


def parse_keymap(text):
    km, cur = {}, None
    for lineno, line in enumerate(text.splitlines(), 1):
        line = line.split("#", 1)[0].strip()
        if not line:
            continue
        m = re.fullmatch(r"\[(\d+)\]", line)
        if m:
            cur = int(m.group(1))
            km[cur] = []
            continue
        if cur is None:
            sys.exit(f"line {lineno}: keycodes before any [layer] header")
        toks = line.split()
        if len(toks) != COLS:
            sys.exit(f"line {lineno}: expected {COLS} keycodes, got {len(toks)}")
        try:
            km[cur].append([encode(t) for t in toks])
        except ValueError as e:
            sys.exit(f"line {lineno}: {e}")
    for layer, grid in km.items():
        if len(grid) != ROWS:
            sys.exit(f"layer {layer}: expected {ROWS} rows, got {len(grid)}")
    return [km[i] for i in range(NUM_LAYERS)] if sorted(km) == list(range(NUM_LAYERS)) \
        else sys.exit(f"file must define layers 0..{NUM_LAYERS - 1}")


# ---------------------------------------------------------------- commands
def changes(cur, new):
    for layer in range(NUM_LAYERS):
        for r in range(ROWS):
            for c in range(COLS):
                if cur[layer][r][c] != new[layer][r][c]:
                    yield layer, r, c, cur[layer][r][c], new[layer][r][c]


def main():
    args = sys.argv[1:]
    cmd = args[0] if args else "show"
    path = args[1] if len(args) > 1 else os.path.join(os.path.dirname(__file__), "keymap.txt")

    board = Board()
    cur = board.read_keymap()

    if cmd == "show":
        print(fmt_keymap(cur))
    elif cmd == "dump":
        with open(path, "w") as f:
            f.write(fmt_keymap(cur))
        print(f"wrote {path}")
    elif cmd in ("apply", "diff"):
        new = parse_keymap(open(path).read())
        delta = list(changes(cur, new))
        if not delta:
            print("board already matches file — nothing to do")
            return
        for layer, r, c, old, newv in delta:
            print(f"layer {layer} [{r},{c}]: {decode(old)} -> {decode(newv)}")
        if cmd == "diff":
            return
        for layer, r, c, _, newv in delta:
            board.set_keycode(layer, r, c, newv)
            got = board.get_keycode(layer, r, c)
            if got != newv:
                sys.exit(f"VERIFY FAILED at layer {layer} [{r},{c}]: "
                         f"wrote 0x{newv:04X}, read back 0x{got:04X}")
        print(f"applied + verified {len(delta)} change(s)")
    else:
        sys.exit(__doc__)


if __name__ == "__main__":
    main()
