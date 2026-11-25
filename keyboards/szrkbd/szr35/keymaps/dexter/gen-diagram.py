#!/usr/bin/env python3
"""Regenerate keymap-diagram.html from keymap.c (run from anywhere).

Parses every LAYOUT_split_3x5_3 block in keymap.c and renders one panel per
real layer. Any keycode without a label below is an error, so the diagram
cannot silently drift from the keymap.
"""
import json
import os
import re
import sys

HERE = os.path.dirname(os.path.abspath(__file__))

T = {"m": "▽", "cls": "trans"}
X = {"m": "", "cls": "none"}


def sm(m, s=""):
    return {"m": m, "s": s, "cls": "small"}


def lk(m, s="to layer"):
    return {"m": m, "s": s, "cls": "layerkey small"}


def td(m, s):
    return {"m": m, "s": s, "cls": "td"}


LABELS = {
    "_______": T, "KC_NO": X,
    "KC_SPC": "Space", "KC_BSPC": "Bksp", "KC_ESC": "Esc", "KC_DEL": "Del", "KC_ENT": "Enter",
    "KC_TAB": "Tab", "KC_LCTL": "Ctrl", "KC_LSFT": "⇧", "KC_LALT": "Alt",
    "KC_QUOT": "'", "KC_COMM": ",", "KC_DOT": ".", "KC_SLSH": "/", "KC_MINS": "-", "KC_SCLN": ";",
    "KC_GRV": "`", "KC_EQL": "=", "KC_PLUS": "+", "KC_EXLM": "!", "KC_AT": "@", "KC_HASH": "#",
    "KC_DLR": "$", "KC_PERC": "%", "KC_CIRC": "^", "KC_AMPR": "&", "KC_ASTR": "*", "KC_LBRC": "[",
    "KC_RBRC": "]", "KC_COLN": ":", "KC_UNDS": "_", "KC_PIPE": "|", "KC_LPRN": "(", "KC_RPRN": ")",
    "KC_DQUO": "\"", "KC_LCBR": "{", "KC_RCBR": "}", "KC_LT": "<", "KC_GT": ">", "KC_QUES": "?",
    "KC_UP": "↑", "KC_DOWN": "↓", "KC_LEFT": "←", "KC_RGHT": "→",
    "KC_PGUP": sm("PgUp"), "KC_PGDN": sm("PgDn"), "KC_HOME": sm("Home"), "KC_END": "End",
    "KC_PSCR": sm("PrtSc"), "KC_MUTE": sm("Mute"), "KC_VOLU": sm("Vol+"), "KC_VOLD": sm("Vol-"),
    "KC_MPRV": "⏮", "KC_MPLY": "⏯", "KC_MNXT": "⏭", "KC_MSTP": "⏹", "KC_MRWD": "⏪", "KC_MFFD": "⏩",
    "MS_WHLL": sm("Whl←"), "MS_WHLR": sm("Whl→"), "MS_WHLU": sm("Whl↑"), "MS_WHLD": sm("Whl↓"),
    "MS_BTN1": sm("Btn1"), "MS_BTN2": sm("Btn2"), "MS_BTN3": sm("Btn3", "middle"),
    "MS_UP": sm("Ms↑"), "MS_DOWN": sm("Ms↓"), "MS_LEFT": sm("Ms←"), "MS_RGHT": sm("Ms→"),
    "QK_BOOT": sm("BOOT", "bootloader"), "EE_CLR": sm("EEPROM", "clear"), "QK_LEAD": lk("Lead", "leader"),
    "RM_TOGG": sm("RGB", "toggle"), "RM_NEXT": sm("RGB", "next fx"), "RM_PREV": sm("RGB", "prev fx"),
    "RM_HUEU": sm("Hue+"), "RM_SATU": sm("Sat+"), "RM_SPDU": sm("Spd+"), "RM_SPDD": sm("Spd-"),
    "RM_VALU": sm("Bri+"), "RM_VALD": sm("Bri-"),
    "DOT_SLS": sm("./", "macro"), "DIR_UP": sm("../", "macro"), "DBL_DASH": sm("--", "macro"),
    "OSL(_LEADR)": lk("Lead", "oneshot"),
    "TO(_QWERTY)": lk("Base"), "TO(_NUM)": lk("Num"), "TO(_FN)": lk("Fn"), "TO(_RAISE)": lk("Raise"),
    "TO(_RAISE2)": lk("Raise2"), "TO(_LEADR)": lk("Lock", "stay here"),
    "TD(TD_Q_TILD)": td("Q", "2:~"), "TD(TD_Z_GRV)": td("Z", "2:`"), "TD(TD_V_TAB)": td("V", "2:Tab"),
    "TD(TD_S_OSM)": td("S", "2:OSM⇧"), "TD(TD_J_OSM)": td("J", "2:OSM⇧"),
    "TD(TD_D_OSM)": td("D", "2:OSM Alt\n3:Alt lock"),
    "TD(TD_G_CAPS)": td("G", "2:Caps"), "TD(TD_H_CAPS)": td("H", "2:Caps"),
    "TD(LAYR_DOWN)": td("F", "2:Lower\nhold:Mouse"), "TD(LAYR_UP)": td("K", "2:Raise\n3:Raise2"),
    "TD(TD_L_NUM)": td("L", "2:Num lock"),
}
NAMES = {"GRV": "`", "TAB": "Tab", "ENT": "Ent", "EQL": "+", "MINS": "−", "SLSH": "/", "LEFT": "←",
         "RGHT": "→", "RIGHT": "→", "UP": "↑", "DOWN": "↓"}
MODS = {"LCTL": "C", "LSFT": "S", "LALT": "A"}


def label(kc):
    if kc in LABELS:
        return LABELS[kc]
    m = re.fullmatch(r"KC_([A-Z0-9])", kc)
    if m:
        return m.group(1)
    m = re.fullmatch(r"KC_(F\d+)", kc)
    if m:
        return m.group(1)
    mods, rest = [], kc
    while True:
        m = re.fullmatch(r"(LCTL|LSFT|LALT)\((.*)\)", rest)
        if not m:
            break
        mods.append(MODS[m.group(1)])
        rest = m.group(2)
    m = re.fullmatch(r"KC_(\w+)", rest)
    if mods and m:
        key = NAMES.get(m.group(1), m.group(1).lower() if len(m.group(1)) == 1 else m.group(1))
        return sm("-".join(mods + [key]))
    sys.exit("gen-diagram.py: no label for keycode %r -- add one to LABELS" % kc)


def split_args(body):
    out, depth, cur = [], 0, ""
    for ch in body:
        if ch == "(":
            depth += 1
        elif ch == ")":
            depth -= 1
        if ch == "," and depth == 0:
            out.append(cur.strip())
            cur = ""
        else:
            cur += ch
    out.append(cur.strip())
    return out


META = [
    ("_QWERTY", "Base (QWERTY)", "#3b5bdb",
     "Default layer. RGB shows the ambient effect (raindrops from royal blue by default)."),
    ("_NUM", "Num", "#f5c518",
     "L 2× = locked (yellow). Digits on the top row, nav on the right outer columns. "
     "G = back to base, H = on to Fn. Dashed keys keep their base behaviour, dances included."),
    ("_FN", "Fn", "#a8d8f0",
     "From Num press H; locked (pale blue). H = back to Num, G = back to base. "
     "F-keys, volume/media, tab and window switching."),
    ("_LOWER", "Lower", "#25c05a",
     "F 2× = oneshot · F 2×,2× or 3× = lock (green, pulsing when locked). Mostly Ctrl-chords."),
    ("_RAISE", "Raise", "#3b82f6", "K 2× = oneshot (blue). Symbols."),
    ("_RAISE2", "Raise2", "#14b8a6",
     "K 3× = oneshot, or Raise then H = sticky (teal). RGB controls, media, arrows, bootloader, EEPROM clear."),
    ("_MOUSE", "Mouse", "#ff3316", "Hold F (coral/red-orange). Cursor on right half, buttons/wheel on left."),
    ("_LEADR", "Shortcuts (LEADR)", "#ef4444",
     "Right middle thumb, oneshot (red). Ctrl+Shift chords; Lead key arms the leader (magenta while recording)."),
]

src = open(os.path.join(HERE, "keymap.c"), encoding="utf-8").read()
src = re.sub(r"//[^\n]*", "", src)
blocks = dict(re.findall(r"\[(_\w+)\]\s*=\s*LAYOUT_split_3x5_3\((.*?)\n    \)", src, re.S))
layers = []
for key, name, color, how in META:
    args = split_args(blocks[key])
    if len(args) != 36:
        sys.exit("layer %s has %d keys, expected 36" % (key, len(args)))
    k = [label(a) for a in args]
    layers.append({
        "name": name, "color": color, "how": how,
        "left": [k[0:5], k[10:15], k[20:25]], "right": [k[5:10], k[15:20], k[25:30]],
        "lthumbs": k[30:33], "rthumbs": k[33:36],
    })

tpl = open(os.path.join(HERE, "keymap-diagram.tpl.html"), encoding="utf-8").read()
out = tpl.replace("/*LAYERS*/", json.dumps(layers, ensure_ascii=False, indent=1))
open(os.path.join(HERE, "keymap-diagram.html"), "w", encoding="utf-8").write(out)
print("wrote keymap-diagram.html (%d layers)" % len(layers))
