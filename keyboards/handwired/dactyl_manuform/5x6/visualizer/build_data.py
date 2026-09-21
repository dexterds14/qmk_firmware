#!/usr/bin/env python3
"""Generate keymap-data.js for the dactyl_manuform 5x6 visualizer.

Parses the firmware sources (keymap.c, keyboard.json, config.h, quantum/color.h)
and emits a single JSON document the webpage renders. Run from anywhere:

    python3 keyboards/handwired/dactyl_manuform/5x6/visualizer/build_data.py

The script VALIDATES its own output against the sources and exits non-zero on
drift (wrong key counts, unknown TD names, unresolvable colors, ...).
See .ai/visualizer.md for the regeneration rule.
"""

import colorsys
import json
import re
import subprocess
import sys
from pathlib import Path

HERE = Path(__file__).resolve().parent
KB_DIR = HERE.parent
KEYMAP_DIR = KB_DIR / "keymaps" / "default"
REPO = KB_DIR.parents[3]

KEYMAP_C = KEYMAP_DIR / "keymap.c"
KEYBOARD_JSON = KB_DIR / "keyboard.json"
CONFIG_H = KEYMAP_DIR / "config.h"
COLOR_H = REPO / "quantum" / "color.h"
OUT = HERE / "keymap-data.js"

TRANSPARENT = {"_______", "KC_NO", "KC_TRNS"}

# --------------------------------------------------------------------------
# Curated tap-dance semantics. MUST be kept in sync with the *_finished()
# functions in keymap.c (validated: every TD name must exist in the enum).
# --------------------------------------------------------------------------
TD_SEMANTICS = {
    "LAYR_DOWN": {
        "base": "F",
        "tap": "types F",
        "double": "LOWER one-shot; a second double-tap LOCKS LOWER",
        "triple": "LOWER locked (moved-to, not one-shot)",
        "hold": "MOUSE layer (layer_move)",
        "note": "From MOUSE: double-tap goes to LOWER one-shot and returns to MOUSE when the one-shot ends.",
    },
    "LAYR_UP": {
        "base": "K",
        "tap": "types K",
        "double": "RAISE one-shot",
        "triple": "RAISE2 one-shot",
        "hold": "(nothing)",
        "note": None,
    },
    "TD_S_OSM": {
        "base": "S",
        "tap": "types S",
        "double": "one-shot Shift",
        "triple": "(nothing)",
        "hold": "(nothing)",
        "note": None,
    },
    "TD_J_OSM": {
        "base": "J",
        "tap": "types J",
        "double": "one-shot Shift",
        "triple": "(nothing)",
        "hold": "(nothing)",
        "note": None,
    },
    "TD_D_OSM": {
        "base": "D",
        "tap": "types D",
        "double": "one-shot Alt",
        "triple": "toggle Alt mod-lock (held until triple-tapped again)",
        "hold": "(nothing)",
        "note": "Alt mod-lock lights the purple RGB layer and shows LOCK on the OLED.",
    },
    "TD_G_CAPS": {
        "base": "G",
        "tap": "types G",
        "double": "toggle Caps Lock",
        "triple": "(nothing)",
        "hold": "(nothing)",
        "note": None,
    },
    "TD_H_CAPS": {
        "base": "H",
        "tap": "types H",
        "double": "toggle Caps Lock",
        "triple": "(nothing)",
        "hold": "(nothing)",
        "note": None,
    },
    "TD_V_TAB": {
        "base": "V",
        "tap": "types V",
        "double": "Tab",
        "triple": "(nothing)",
        "hold": "(nothing)",
        "note": None,
    },
    "TD_Q_TILD": {
        "base": "Q",
        "tap": "types Q",
        "double": "~ (tilde)",
        "triple": "(nothing)",
        "hold": "(nothing)",
        "note": None,
    },
    "TD_Z_GRV": {
        "base": "Z",
        "tap": "types Z",
        "double": "` (grave/backtick)",
        "triple": "(nothing)",
        "hold": "(nothing)",
        "note": None,
    },
}

# Which real layer (if any) each RGB indicator corresponds to.
RGB_INDICATOR_TARGET = {
    "RAISE": "_RAISE",
    "RAISE2": "_RAISE2",
    "LOWER": "_LOWER",
    "MOUSE": "_MOUSE",
    "LEADR": "_LEADR",
    "CAPS_LOCK": "_CAPSIND",
    "LEADER": None,   # active leader sequence (not a layer)
    "CAPS": None,     # pending one-shot Shift (not a layer)
    "ALT_MOD": None,  # active/locked Alt or GUI mod (not a layer)
}

INDICATOR_TRIGGER = {
    "LEADER": "while a leader sequence is recording",
    "CAPS": "pending one-shot Shift",
    "ALT_MOD": "Alt/GUI mod active or mod-locked",
}

MOD_NAMES = {
    "LCTL": "Ctrl", "RCTL": "Ctrl", "LSFT": "Shift", "RSFT": "Shift",
    "LALT": "Alt", "RALT": "Alt", "LGUI": "Cmd", "RGUI": "Cmd",
    "LCA": "Ctrl+Alt", "RCA": "Ctrl+Alt",
    "LSG": "Cmd+Shift", "RSG": "Cmd+Shift",
    "LCG": "Ctrl+Cmd", "RCG": "Ctrl+Cmd",
    "MOD_LSFT": "Shift", "MOD_RSFT": "Shift", "MOD_LALT": "Alt",
    "MOD_RALT": "Alt", "MOD_LGUI": "Cmd", "MOD_RGUI": "Cmd",
    "MOD_LCTL": "Ctrl", "MOD_RCTL": "Ctrl",
}

KEY_LABELS = {
    "KC_ESC": "Esc", "KC_BSLS": "\\", "KC_GRV": "`", "KC_MINS": "-",
    "KC_QUOT": "'", "KC_COMM": ",", "KC_DOT": ".", "KC_SLSH": "/",
    "KC_SCLN": ";", "KC_SPC": "Space", "KC_BSPC": "Bksp", "KC_DEL": "Del",
    "KC_ENT": "Enter", "KC_TAB": "Tab", "KC_CAPS": "Caps",
    "KC_HOME": "Home", "KC_END": "End", "KC_PGUP": "PgUp", "KC_PGDN": "PgDn",
    "KC_LALT": "LAlt", "KC_LCTL": "LCtrl", "KC_LSFT": "LShift",
    "KC_RSFT": "RShift", "KC_LGUI": "LCmd", "KC_RGUI": "RCmd",
    "KC_EXLM": "!", "KC_AT": "@", "KC_HASH": "#", "KC_DLR": "$",
    "KC_PERC": "%", "KC_CIRC": "^", "KC_AMPR": "&", "KC_ASTR": "*",
    "KC_LBRC": "[", "KC_RBRC": "]", "KC_PLUS": "+", "KC_COLN": ":",
    "KC_EQL": "=", "KC_UNDS": "_", "KC_PIPE": "|", "KC_LPRN": "(",
    "KC_RPRN": ")", "KC_DQUO": '"', "KC_LCBR": "{", "KC_RCBR": "}",
    "KC_LT": "<", "KC_GT": ">", "KC_QUES": "?", "KC_TILD": "~",
    "KC_VOLU": "Vol+", "KC_VOLD": "Vol-", "KC_MUTE": "Mute",
    "KC_MPLY": "Play", "KC_MSTP": "Stop", "KC_MPRV": "Prev", "KC_MNXT": "Next",
    "KC_MFFD": "FFwd", "KC_MRWD": "RWnd", "KC_PSCR": "PrtSc",
    "QK_BOOT": "BOOT", "QK_LEAD": "LEAD", "EE_CLR": "EE_CLR",
    "DOT_SLS": "./", "DIR_UP": "../", "DBL_DASH": "--",
    "MS_UP": "M↑", "MS_DOWN": "M↓", "MS_LEFT": "M←", "MS_RGHT": "M→",
    "MS_BTN1": "Btn1", "MS_BTN2": "Btn2", "MS_BTN3": "Btn3",
    "MS_WHLU": "Whl↑", "MS_WHLD": "Whl↓", "MS_WHLL": "Whl←", "MS_WHLR": "Whl→",
    "KC_UP": "↑", "KC_DOWN": "↓", "KC_LEFT": "←", "KC_RGHT": "→",
}

CUSTOM_KEYCODES = {
    "DOT_SLS": "types ./",
    "DIR_UP": "types ../",
    "DBL_DASH": "types --",
}


def die(msg):
    print(f"ERROR: {msg}", file=sys.stderr)
    sys.exit(1)


def strip_comments(text):
    text = re.sub(r"/\*.*?\*/", "", text, flags=re.S)
    text = re.sub(r"//[^\n]*", "", text)
    return text


def balanced_body(text, open_idx, opener="(", closer=")"):
    """Return the text inside the bracket pair starting at open_idx."""
    depth = 0
    for i in range(open_idx, len(text)):
        if text[i] == opener:
            depth += 1
        elif text[i] == closer:
            depth -= 1
            if depth == 0:
                return text[open_idx + 1:i]
    die(f"unbalanced {opener}{closer}")


def split_args(body):
    """Split a macro body on top-level commas."""
    args, depth, cur = [], 0, ""
    for ch in body:
        if ch == "(":
            depth += 1
        elif ch == ")":
            depth -= 1
        if ch == "," and depth == 0:
            args.append(cur.strip())
            cur = ""
        else:
            cur += ch
    if cur.strip():
        args.append(cur.strip())
    return args


def parse_layer_defines(text):
    text = strip_comments(text)
    layers = {}
    for m in re.finditer(r"#define\s+(_\w+)\s+(\d+)", text):
        layers[m.group(2)] = m.group(1)
    return {name: int(idx) for idx, name in layers.items()}


def parse_phantom_names(text):
    m = re.search(r"#define\s+PHANTOM_LAYERS_MASK(.*)", text)
    if not m:
        return set()
    return set(re.findall(r"<<\s*(_\w+)", m.group(1)))


def extract_layers(code):
    """Return {layer_name: [64 raw keycode tokens]} in layout order."""
    clean = strip_comments(code)
    layers = {}
    for m in re.finditer(r"\[(_\w+)\]\s*=\s*LAYOUT_5x6\s*\(", clean):
        name = m.group(1)
        body = balanced_body(clean, clean.index("(", m.start()))
        layers[name] = split_args(body)
    return layers


def parse_geometry():
    kb = json.loads(KEYBOARD_JSON.read_text())
    layout = kb["layouts"]["LAYOUT_5x6"]["layout"]
    for k in layout:
        k["half"] = "left" if k["matrix"][0] < 6 else "right"
    return layout


def parse_hsv():
    hsv = {}
    for m in re.finditer(r"#define\s+(HSV_\w+)\s+(\d+),\s*(\d+),\s*(\d+)", COLOR_H.read_text()):
        h, s, v = (int(m.group(i)) for i in (2, 3, 4))
        r, g, b = colorsys.hsv_to_rgb(h / 255.0, s / 255.0, v / 255.0)
        hsv[m.group(1)] = "#{:02x}{:02x}{:02x}".format(round(r * 255), round(g * 255), round(b * 255))
    return hsv


def parse_rgb(code, hsv):
    """Return (layer_colors, legend) using the RUNTIME enum->segment mapping."""
    code = strip_comments(code)
    seg_defs = {}
    for m in re.finditer(r"(my_\w+?)\s*\[\]\s*=\s*RGBLIGHT_LAYER_SEGMENTS\((.*?)\);", code, re.S):
        colors = re.findall(r"(HSV_\w+)", m.group(2))
        if colors:
            seg_defs[m.group(1)] = colors[0]
    list_m = re.search(r"RGBLIGHT_LAYERS_LIST\((.*?)\);", code, re.S)
    if not list_m:
        die("RGBLIGHT_LAYERS_LIST not found")
    seg_order = [s.strip() for s in list_m.group(1).split(",") if s.strip()]
    for seg in seg_order:
        if seg not in seg_defs:
            die(f"RGB layer list references unknown segment {seg}")

    enum_m = re.search(r"enum\s+rgb_layer\s*\{(.*?)\}", code, re.S)
    if not enum_m:
        die("enum rgb_layer not found")
    enum_vals = {m.group(1): int(m.group(2)) for m in re.finditer(r"(RGB_\w+)\s*=\s*(\d+)", enum_m.group(1))}

    layer_colors, legend = {}, []
    for rgb_name, idx in enum_vals.items():
        if idx >= len(seg_order):
            die(f"{rgb_name} index {idx} out of range of RGBLIGHT_LAYERS_LIST")
        hexv = hsv[seg_defs[seg_order[idx]]]
        short = rgb_name.replace("RGB_", "")
        target = RGB_INDICATOR_TARGET.get(short)
        if target:
            layer_colors[target] = hexv
        legend.append({
            "name": short,
            "hex": hexv,
            "layer": target,
            "trigger": INDICATOR_TRIGGER.get(short, f"{target} active" if target else short),
        })
    base = re.search(r"rgblight_sethsv\((\d+),\s*(\d+),\s*(\d+)\)", code)
    base_hex = None
    if base:
        h, s, v = (int(base.group(i)) for i in (1, 2, 3))
        r, g, b = colorsys.hsv_to_rgb(h / 255.0, s / 255.0, v / 255.0)
        base_hex = "#{:02x}{:02x}{:02x}".format(round(r * 255), round(g * 255), round(b * 255))
    return layer_colors, legend, base_hex


def parse_timings(config_text):
    out = {}
    for key in ("TAPPING_TERM", "FLOW_TAP_TERM", "LEADER_TIMEOUT", "ONESHOT_TAP_TOGGLE"):
        m = re.search(rf"#define\s+{key}\s+(\d+)", config_text)
        if m:
            out[key] = int(m.group(1))
    return out


def parse_td_enum(code):
    code = strip_comments(code)
    m = re.search(r"enum\s+tap_dance_keys\s*\{(.*?)\}", code, re.S)
    if not m:
        die("enum tap_dance_keys not found")
    names = []
    for line in m.group(1).split(","):
        line = line.strip()
        if line:
            names.append(line)
    return names


def friendly_key(tok):
    tok = tok.strip()
    if tok in KEY_LABELS:
        return KEY_LABELS[tok]
    m = re.fullmatch(r"KC_(\w)", tok)
    if m:
        return m.group(1)
    m = re.fullmatch(r"KC_(\w+)", tok)
    if m:
        return m.group(1).replace("_", " ").title()
    return tok


def render_chord(tok):
    """Render LCTL(LSFT(KC_E)) -> 'Ctrl+Shift+E'. Returns (label, is_chord)."""
    m = re.fullmatch(r"(LCTL|RCTL|LSFT|RSFT|LALT|RALT|LGUI|RGUI|LCA|RCA|LSG|RSG|LCG|RCG)\((.*)\)", tok)
    if not m:
        return friendly_key(tok), False
    mod = MOD_NAMES[m.group(1)]
    inner, was_chord = render_chord(m.group(2))
    return f"{mod}+{inner}", True


def parse_leader(code):
    """Parse leader_end_user(): active and commented-out sequences."""
    fn_m = re.search(r"void\s+leader_end_user\s*\(void\)\s*\{", code)
    if not fn_m:
        die("leader_end_user not found")
    body = balanced_body(code, code.index("{", fn_m.start()), "{", "}")
    lines = body.splitlines()

    seqs = []
    last_comment = None
    i = 0
    while i < len(lines):
        raw = lines[i]
        stripped = raw.strip()
        is_c = stripped.startswith("//")
        content = re.sub(r"^\s*(?://\s*)*", "", raw)

        cond = re.search(r"leader_sequence_(one|two|three)_keys?\((.*?)\)", content)
        if cond:
            arity = {"one": 1, "two": 2, "three": 3}[cond.group(1)]
            keys = [friendly_key(k) for k in cond.group(2).split(",")]
            if len(keys) != arity:
                die(f"leader sequence arity mismatch: {cond.group(0)}")
            active = not is_c
            actions, registers = [], []
            j = i + 1
            while j < len(lines):
                nxt_raw = lines[j]
                nxt_c = nxt_raw.strip().startswith("//")
                if nxt_c != is_c:
                    break
                nxt = re.sub(r"^\s*(?://\s*)*", "", nxt_raw).strip()
                if not nxt or nxt in ("{", "}"):
                    j += 1
                    continue
                if "leader_sequence_" in nxt:
                    break
                tc = re.match(r"tap_code(?:16)?\((.*)\);", nxt)
                rc = re.match(r"register_code\((.*)\);", nxt)
                if tc:
                    label, _ = render_chord(tc.group(1))
                    actions.append(label)
                elif rc:
                    label, _ = render_chord(rc.group(1))
                    if label not in registers:
                        registers.append(label)
                else:
                    break
                j += 1
            if actions:
                action = " then ".join(actions)
            elif registers:
                action = "+".join(registers)
            else:
                die(f"leader sequence with no actions: {keys}")
            seqs.append({
                "keys": keys,
                "action": action,
                "active": active,
                "note": last_comment if last_comment else None,
            })
            last_comment = None
            i = j
            continue

        if is_c and content.strip() and "leader_sequence_" not in content:
            last_comment = content.strip()
        elif not is_c and stripped:
            last_comment = None
        i += 1
    return seqs


def decode_token(tok):
    tok = tok.strip()
    if tok in TRANSPARENT:
        return {"raw": tok, "label": "", "kind": "transparent"}

    m = re.fullmatch(r"TD\((\w+)\)", tok)
    if m:
        name = m.group(1)
        sem = TD_SEMANTICS.get(name, {})
        return {"raw": tok, "label": sem.get("base", name), "kind": "tapdance", "td": name}

    m = re.fullmatch(r"OSL\((_\w+)\)", tok)
    if m:
        return {"raw": tok, "label": f"OSL {m.group(1)}", "kind": "oneshot_layer", "layer": m.group(1)}

    m = re.fullmatch(r"OSM\((\w+)\)", tok)
    if m:
        return {"raw": tok, "label": f"one-shot {MOD_NAMES.get(m.group(1), m.group(1))}",
                "kind": "oneshot_mod", "mod": m.group(1)}

    m = re.fullmatch(r"TO\((_\w+)\)", tok)
    if m:
        return {"raw": tok, "label": f"→ {m.group(1)}", "kind": "layer_switch", "layer": m.group(1)}

    m = re.fullmatch(r"MO\((_\w+)\)", tok)
    if m:
        return {"raw": tok, "label": f"hold {m.group(1)}", "kind": "momentary", "layer": m.group(1)}

    if tok in CUSTOM_KEYCODES:
        return {"raw": tok, "label": KEY_LABELS.get(tok, tok), "kind": "custom", "detail": CUSTOM_KEYCODES[tok]}

    label, is_chord = render_chord(tok)
    if is_chord:
        return {"raw": tok, "label": label, "kind": "chord"}

    if tok in ("QK_BOOT", "QK_LEAD", "EE_CLR"):
        return {"raw": tok, "label": KEY_LABELS[tok], "kind": "special"}

    return {"raw": tok, "label": label, "kind": "basic"}


def main():
    code = KEYMAP_C.read_text()
    config = CONFIG_H.read_text()

    layer_names = parse_layer_defines(code)
    phantoms = parse_phantom_names(code)
    raw_layers = extract_layers(code)
    geometry = parse_geometry()
    hsv = parse_hsv()
    layer_colors, legend, base_hex = parse_rgb(code, hsv)
    timings = parse_timings(config)
    td_enum = parse_td_enum(code)
    leader_seqs = parse_leader(code)

    # ---- validation -----------------------------------------------------
    n = len(geometry)
    for name, toks in raw_layers.items():
        if len(toks) != n:
            die(f"layer {name} has {len(toks)} keys, layout has {n}")
    for name in raw_layers:
        if name not in layer_names:
            die(f"layer {name} has no #define")
    used_td = set()
    for toks in raw_layers.values():
        for t in toks:
            m = re.fullmatch(r"TD\((\w+)\)", t.strip())
            if m:
                used_td.add(m.group(1))
    unknown = used_td - set(td_enum)
    if unknown:
        die(f"TD() names not in tap_dance_keys enum: {sorted(unknown)}")
    missing_sem = used_td - set(TD_SEMANTICS)
    if missing_sem:
        die(f"TD keys used but missing curated semantics: {sorted(missing_sem)}")
    for ph in phantoms:
        if ph in raw_layers and any(t.strip() not in TRANSPARENT for t in raw_layers[ph]):
            die(f"phantom layer {ph} is not fully transparent")
    if not any(s["active"] for s in leader_seqs):
        die("no active leader sequences parsed")

    # ---- assemble -------------------------------------------------------
    layers = []
    for name in sorted(layer_names, key=lambda k: layer_names[k]):
        toks = raw_layers.get(name, [])
        layers.append({
            "index": layer_names[name],
            "name": name,
            "phantom": name in phantoms,
            "rgb": layer_colors.get(name),
            "keys": [decode_token(t) for t in toks],
        })

    try:
        commit = subprocess.run(["git", "-C", str(REPO), "rev-parse", "--short", "HEAD"],
                              capture_output=True, text=True, timeout=10).stdout.strip()
    except Exception:
        commit = "unknown"

    data = {
        "meta": {
            "keyboard": "handwired/dactyl_manuform/5x6",
            "keymap": "default",
            "sourceCommit": commit,
            "generatedBy": "build_data.py",
        },
        "geometry": geometry,
        "layers": layers,
        "tapDances": TD_SEMANTICS,
        "leader": {"timeoutMs": timings.get("LEADER_TIMEOUT"), "sequences": leader_seqs},
        "customKeycodes": CUSTOM_KEYCODES,
        "timings": timings,
        "rgbLegend": legend,
        "baseColor": base_hex,
    }

    OUT.write_text("// Generated by build_data.py -- do not edit by hand.\n"
                  "window.KEYMAP_DATA = " + json.dumps(data, indent=1) + ";\n")
    active = sum(1 for s in leader_seqs if s["active"])
    disabled = len(leader_seqs) - active
    print(f"wrote {OUT.relative_to(REPO)}")
    print(f"  layers: {len(layers)} ({len(phantoms)} phantom), keys/layer: {n}")
    print(f"  tap dances: {len(td_enum)} defined, {len(used_td)} used on base layer")
    print(f"  leader sequences: {active} active, {disabled} disabled")
    print(f"  timings: {timings}")


if __name__ == "__main__":
    main()
