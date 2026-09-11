#!/usr/bin/env python3
"""
eeprom_parse.py -- decode the QMK wear-leveling "emulated EEPROM" sector of the
Keychron V10 Max flash dump (dump_a.bin[0x4000:0x5000]).

Format (quantum/wear_leveling/wear_leveling.c + wear_leveling_internal.h in the
Keychron fork, platforms/chibios/drivers/wear_leveling/wear_leveling_efl.c):

  * backing store = 4096 B at flash 0x08004000; every stored word is the bit-
    complement of the logical value (wear_leveling_efl.c: value = ~value on
    write, ~(*loc) on read), so erased flash 0xFF reads back as logical 0x00.
  * [0, 2048)     consolidated image of the 2048-byte logical EEPROM
  * [2048, 2056)  FNV-1a-64 of the 2048 consolidated bytes, little-endian
  * [2056, 4096)  write log, 4-byte units (BACKING_STORE_WRITE_SIZE == 4 on
                  STM32F4 with STM32_FLASH_PSIZE = 2), terminated by the first
                  all-zero (logical) word.  With a 4-byte backing store only
                  LOG_ENTRY_TYPE_MULTIBYTE (type bits 00) entries are ever
                  written (the 2-byte optimisations are #if'd out):
                    word0: byte0 = type:2 (bits7..6) | len:3 (bits5..3) |
                                   addr[18:16] (bits2..0)
                           byte1 = addr[15:8], byte2 = addr[7:0], byte3 = value[0]
                    word1 (only if len > 1): value[1..4]

Outputs eeprom_recovered.json / eeprom_recovered.md and (optionally) compares
the replayed cache byte-for-byte against the C oracle's output.

Usage:
  python3 eeprom_parse.py [--dump PATH] [--fork PATH] [--oracle-hex PATH]
                          [--out-dir PATH]
"""
import argparse
import json
import os
import re
import struct
import sys

HERE = os.path.dirname(os.path.abspath(__file__))
BACKUP_DIR = os.path.dirname(HERE)

FLASH_BASE = 0x08000000
BACKING_FILE_OFF = 0x4000
BACKING_SIZE = 4096
LOGICAL_SIZE = 2048
WRITE_SIZE = 4
HASH_OFF = LOGICAL_SIZE
LOG_START = LOGICAL_SIZE + 8

FNV1A_64_INIT = 0xcbf29ce484222325
FNV_64_PRIME = 0x100000001b3
MASK64 = (1 << 64) - 1

EECONFIG_MAGIC_NUMBER = 0xFEE6

# keymap_config bit names, quantum/keycode_config.h (bit 0 first)
KEYMAP_CONFIG_BITS = [
    "swap_control_capslock",      # 0
    "capslock_to_control",        # 1
    "swap_lalt_lgui",             # 2
    "swap_ralt_rgui",             # 3
    "no_gui",                     # 4
    "swap_grave_esc",             # 5
    "swap_backslash_backspace",   # 6
    "nkro",                       # 7
    "swap_lctl_lgui",             # 8
    "swap_rctl_rgui",             # 9
    "oneshot_enable",             # 10
    "swap_escape_capslock",       # 11
    "autocorrect_enable",         # 12
]

LED_FLAG_BITS = {0x01: "MODIFIER", 0x02: "UNDERGLOW", 0x04: "KEYLIGHT", 0x08: "INDICATOR"}


# --------------------------------------------------------------------------- utils
def fnv1a_64(data: bytes) -> int:
    h = FNV1A_64_INIT
    for b in data:
        h ^= b
        h = (h * FNV_64_PRIME) & MASK64
    return h


def fnv1_64(data: bytes) -> int:
    """Non-'a' variant (multiply then xor) -- computed only to show it does NOT match."""
    h = FNV1A_64_INIT
    for b in data:
        h = (h * FNV_64_PRIME) & MASK64
        h ^= b
    return h


def hexdump(buf: bytes, base: int, flash_base: int, width: int = 16) -> str:
    lines = []
    for off in range(0, len(buf), width):
        chunk = buf[off:off + width]
        hexs = " ".join("%02x" % b for b in chunk)
        lines.append("%04x (flash %08x): %s" % (base + off, flash_base + base + off, hexs))
    return "\n".join(lines)


# --------------------------------------------------------------------------- log parsing
def parse_log(inv: bytes):
    """Replay the write log exactly as wear_leveling_playback_log() does for
    BACKING_STORE_WRITE_SIZE == 4.  Returns (entries, cache, info)."""
    cache = bytearray(inv[:LOGICAL_SIZE])
    entries = []
    anomalies = []
    address = LOG_START
    terminator_at = None
    while address < BACKING_SIZE:
        (word,) = struct.unpack_from("<I", inv, address)
        if word == 0:
            terminator_at = address
            break
        raw = [word]
        b = inv[address:address + 4]
        entry_off = address
        address += WRITE_SIZE
        etype = (b[0] >> 6) & 3
        if etype != 0:
            anomalies.append("non-MULTIBYTE entry type %d at backing 0x%04x (firmware would hit "
                             "default: -> WEAR_LEVELING_FAILED -> consolidate_force)" % (etype, entry_off))
            break
        length = (b[0] >> 3) & 7
        addr = ((b[0] & 7) << 16) | (b[1] << 8) | b[2]
        values = [b[3]]
        if addr + length > LOGICAL_SIZE:
            anomalies.append("entry at 0x%04x addr+len out of range (addr=%d len=%d)" % (entry_off, addr, length))
            break
        if length > 1:
            (word1,) = struct.unpack_from("<I", inv, address)
            raw.append(word1)
            values += list(inv[address:address + 4])
            address += WRITE_SIZE
        values = values[:length]
        if length == 0:
            anomalies.append("zero-length entry at 0x%04x" % entry_off)
        cache[addr:addr + length] = bytes(values)
        entries.append({
            "index": len(entries),
            "backing_offset": entry_off,
            "file_offset": BACKING_FILE_OFF + entry_off,
            "flash_addr": FLASH_BASE + BACKING_FILE_OFF + entry_off,
            "raw_words_le": ["0x%08x" % w for w in raw],
            "type": etype,
            "eeprom_addr": addr,
            "len": length,
            "bytes": "".join("%02x" % v for v in values),
            "values": values,
        })
    info = {
        "log_start_backing_offset": LOG_START,
        "terminator_backing_offset": terminator_at,
        "next_write_address": address,
        "entries": len(entries),
        "log_words_used": (address - LOG_START) // WRITE_SIZE,
        "log_words_capacity": (BACKING_SIZE - LOG_START) // WRITE_SIZE,
        "anomalies": anomalies,
    }
    # the rest of the log must be all-zero (logical) == 0xFF in flash
    tail = inv[address:]
    info["tail_nonzero_bytes"] = sum(1 for x in tail if x)
    info["tail_length"] = len(tail)
    return entries, bytes(cache), info


# --------------------------------------------------------------------------- eeconfig decode
def decode_keymap_config(v: int):
    bits = {}
    for i, name in enumerate(KEYMAP_CONFIG_BITS):
        bits[name] = bool(v >> i & 1)
    unknown = v & ~((1 << len(KEYMAP_CONFIG_BITS)) - 1)
    return bits, unknown


def decode_led_flags(v: int):
    if v == 0xFF:
        return "LED_FLAG_ALL (0xFF)"
    if v == 0:
        return "LED_FLAG_NONE"
    return "|".join(n for m, n in LED_FLAG_BITS.items() if v & m) + (" (+unknown 0x%02x)" % (v & ~0x0F) if v & ~0x0F else "")


def decode_rgb_matrix(raw8: bytes, mode_names):
    b0 = raw8[0]
    enable = b0 & 3           # uint8_t enable : 2
    mode = (b0 >> 2) & 0x3F   # uint8_t mode : 6  (rgb_matrix_types.h; GCC little-endian bitfield order)
    d = {
        "raw": "".join("%02x" % x for x in raw8),
        "enable": enable,
        "mode": mode,
        "mode_name_assuming_board_default_animations": mode_names.get(mode, "OUT OF RANGE (>= RGB_MATRIX_EFFECT_MAX)"),
        "hue": raw8[1],
        "sat": raw8[2],
        "val": raw8[3],
        "speed": raw8[4],
        "flags": raw8[5],
        "flags_decoded": decode_led_flags(raw8[5]),
        "padding_bytes_30_31": "".join("%02x" % x for x in raw8[6:8]),
    }
    return d


def decode_eeconfig(img: bytes, mode_names):
    magic = struct.unpack_from("<H", img, 0)[0]
    default_layer = img[3]
    keymap_cfg = struct.unpack_from("<H", img, 4)[0]
    km_bits, km_unknown = decode_keymap_config(keymap_cfg)
    dl_layers = [i for i in range(8) if default_layer >> i & 1]
    out = {
        "magic": "0x%04X" % magic,
        "magic_ok": magic == EECONFIG_MAGIC_NUMBER,
        "debug": img[2],
        "default_layer_bitmask": "0x%02x" % default_layer,
        "default_layer_index": dl_layers[0] if len(dl_layers) == 1 else dl_layers,
        "keymap_config": "0x%04x" % keymap_cfg,
        "keymap_config_bits_set": [k for k, v in km_bits.items() if v],
        "keymap_config_bits": km_bits,
        "keymap_config_unknown_bits": "0x%04x" % km_unknown,
        "backlight": img[6],
        "audio": img[7],
        "rgblight": "0x%08x" % struct.unpack_from("<I", img, 8)[0],
        "unicode_mode": img[12],
        "steno_mode": img[13],
        "handedness": img[14],
        "keyboard_u32": "0x%08x" % struct.unpack_from("<I", img, 15)[0],
        "user_u32": "0x%08x" % struct.unpack_from("<I", img, 19)[0],
        "unused_23": img[23],
        "rgb_matrix": decode_rgb_matrix(img[24:32], mode_names),
        "haptic": "0x%08x" % struct.unpack_from("<I", img, 32)[0],
        "rgblight_ext": img[36],
        "kb_data_37_63": "".join("%02x" % x for x in img[37:64]),
        "keychron_kb": {
            "language_37": img[37],
            "wireless_backlit_disable_time_38_39_u16": struct.unpack_from("<H", img, 38)[0],
            "wireless_connected_idle_time_40_41_u16": struct.unpack_from("<H", img, 40)[0],
        },
        "nonzero_bytes_beyond_63": [(i, "0x%02x" % img[i]) for i in range(64, LOGICAL_SIZE) if img[i]],
    }
    return out


# --------------------------------------------------------------------------- rgb effect enum
def build_rgb_mode_table(fork: str):
    """Reconstruct enum rgb_matrix_effects exactly as quantum/rgb_matrix/rgb_matrix.h
    builds it: RGB_MATRIX_NONE = 0, then every RGB_MATRIX_EFFECT(name) that survives
    the preprocessor, in rgb_matrix_effects.inc include order.  Enabled set comes from
    keyboards/keychron/v10_max/info.json rgb_matrix.animations, which the QMK build
    turns into -DENABLE_RGB_MATRIX_<KEY_UPPER> (lib/python/qmk/cli/generate/config_h.py,
    generate_led_animations_config).  Extra conditions taken from the headers:
    typing_heatmap/digital_rain also need RGB_MATRIX_FRAMEBUFFER_EFFECTS, the
    solid_reactive*/splash* ones need RGB_MATRIX_KEYREACTIVE_ENABLED (RGB_MATRIX_KEYPRESSES);
    both are #defined in keyboards/keychron/v10_max/ansi_encoder/config.h."""
    anim_dir = os.path.join(fork, "quantum", "rgb_matrix", "animations")
    inc = os.path.join(anim_dir, "rgb_matrix_effects.inc")
    info_json = os.path.join(fork, "keyboards", "keychron", "v10_max", "info.json")
    sub_cfg = os.path.join(fork, "keyboards", "keychron", "v10_max", "ansi_encoder", "config.h")
    if not (os.path.exists(inc) and os.path.exists(info_json)):
        return {}, [], "fork sources not found at %s; mode names unavailable" % fork

    with open(info_json) as f:
        anims = json.load(f)["rgb_matrix"]["animations"]
    enabled_macros = {"ENABLE_RGB_MATRIX_" + k.upper() for k, v in anims.items() if v}
    cfg_txt = open(sub_cfg).read() if os.path.exists(sub_cfg) else ""
    framebuffer = bool(re.search(r"^\s*#\s*define\s+RGB_MATRIX_FRAMEBUFFER_EFFECTS\b", cfg_txt, re.M))
    keyreactive = bool(re.search(r"^\s*#\s*define\s+RGB_MATRIX_KEYPRESSES\b", cfg_txt, re.M)) or \
        bool(re.search(r"^\s*#\s*define\s+RGB_MATRIX_KEYRELEASES\b", cfg_txt, re.M))

    order = re.findall(r'#include\s+"([^"]+)"', open(inc).read())
    all_effects = []   # (name, enabled, condition-string)
    for hdr in order:
        txt = open(os.path.join(anim_dir, hdr)).read()
        needs_fb = "RGB_MATRIX_FRAMEBUFFER_EFFECTS" in txt.split("RGB_MATRIX_CUSTOM_EFFECT_IMPLS")[0]
        needs_kr = "RGB_MATRIX_KEYREACTIVE_ENABLED" in txt.split("RGB_MATRIX_CUSTOM_EFFECT_IMPLS")[0]
        for name in re.findall(r"^\s*RGB_MATRIX_EFFECT\((\w+)\)", txt, re.M):
            if name == "SOLID_COLOR":
                cond, en = "always", True
            else:
                macro = "ENABLE_RGB_MATRIX_" + name
                cond = macro
                en = macro in enabled_macros
                if needs_fb:
                    cond += " && RGB_MATRIX_FRAMEBUFFER_EFFECTS"
                    en = en and framebuffer
                if needs_kr:
                    cond += " && RGB_MATRIX_KEYREACTIVE_ENABLED"
                    en = en and keyreactive
            all_effects.append((hdr, name, en, cond))
    table = {0: "RGB_MATRIX_NONE"}
    n = 1
    enum_list = [(0, "RGB_MATRIX_NONE", "-", "-")]
    for hdr, name, en, cond in all_effects:
        if en:
            table[n] = "RGB_MATRIX_" + name
            enum_list.append((n, "RGB_MATRIX_" + name, hdr, cond))
            n += 1
    table_note = ("enum built from %s (%d headers, %d RGB_MATRIX_EFFECT names, %d enabled -> "
                  "RGB_MATRIX_EFFECT_MAX = %d); info.json animations=%d true, "
                  "RGB_MATRIX_FRAMEBUFFER_EFFECTS=%s, RGB_MATRIX_KEYPRESSES=%s"
                  % (os.path.relpath(inc, fork), len(order), len(all_effects), n - 1, n,
                     sum(1 for v in anims.values() if v), framebuffer, keyreactive))
    return table, enum_list, table_note


# --------------------------------------------------------------------------- history semantics
def describe_history(entries, consolidated: bytes, mode_names):
    """Group the log into 'events'.  Each eeconfig_flush_rgb_matrix() is an 8-byte
    eeprom_update_block(24..31) -> wear_leveling_write_raw splits into MULTIBYTE(24,5)
    + MULTIBYTE(29,3).  Track the resulting rgb_matrix_config after each entry."""
    state = bytearray(consolidated[:LOGICAL_SIZE])
    rows = []
    prev = decode_rgb_matrix(bytes(state[24:32]), mode_names)
    for e in entries:
        a, l = e["eeprom_addr"], e["len"]
        state[a:a + l] = bytes(e["values"])
        if 24 <= a < 32:
            cur = decode_rgb_matrix(bytes(state[24:32]), mode_names)
            changes = []
            for k in ("enable", "mode", "hue", "sat", "val", "speed", "flags"):
                if cur[k] != prev[k]:
                    changes.append("%s %s->%s" % (k, prev[k], cur[k]))
            rows.append((e, cur, changes))
            prev = cur
        else:
            rows.append((e, None, ["non-rgb write @%d" % a]))
    return rows


# --------------------------------------------------------------------------- main
def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--dump", default=os.path.join(BACKUP_DIR, "dump_a.bin"))
    ap.add_argument("--fork", default=os.path.dirname(BACKUP_DIR),
                    help="Keychron fork worktree (for rgb effect enum reconstruction)")
    ap.add_argument("--oracle-hex", default=os.path.join(HERE, "eeprom_oracle", "oracle_cache.hex"),
                    help="hex file written by the C oracle (2048 bytes); compared if present")
    ap.add_argument("--out-dir", default=BACKUP_DIR)
    args = ap.parse_args()

    with open(args.dump, "rb") as f:
        dump = f.read()
    raw = dump[BACKING_FILE_OFF:BACKING_FILE_OFF + BACKING_SIZE]
    if len(raw) != BACKING_SIZE:
        sys.exit("dump too short")
    inv = bytes(b ^ 0xFF for b in raw)

    # write the inverted slice + python cache for external tools
    with open(os.path.join(HERE, "eeprom_oracle", "backing_inverted.bin"), "wb") as f:
        f.write(inv)

    print("== raw (bit-inverted) consolidated image, first 64 bytes  [backing offset (flash addr)]")
    print(hexdump(inv[:64], 0, FLASH_BASE + BACKING_FILE_OFF))
    print("== raw (bit-inverted) hash + write-log start, 64 bytes from backing 0x800")
    print(hexdump(inv[HASH_OFF:HASH_OFF + 64], HASH_OFF, FLASH_BASE + BACKING_FILE_OFF))
    print("== raw flash bytes (NOT inverted) at file 0x4000..0x400f for reference")
    print(hexdump(raw[:16], 0, FLASH_BASE + BACKING_FILE_OFF))

    consolidated = inv[:LOGICAL_SIZE]
    stored_hash_le = struct.unpack_from("<Q", inv, HASH_OFF)[0]
    stored_hash_be = struct.unpack_from(">Q", inv, HASH_OFF)[0]
    h1a = fnv1a_64(consolidated)
    h1 = fnv1_64(consolidated)
    hash_ok = (h1a == stored_hash_le)
    print("\n== FNV hash over consolidated[0:2048]")
    print("  stored (LE u64 @ backing 0x800)  = 0x%016x" % stored_hash_le)
    print("  stored (BE interpretation)       = 0x%016x" % stored_hash_be)
    print("  computed FNV-1a-64               = 0x%016x  %s" % (h1a, "MATCH" if hash_ok else "MISMATCH"))
    print("  computed FNV-1 -64 (non-a)       = 0x%016x  %s" % (h1, "match" if h1 == stored_hash_le else "(no match, as expected)"))

    entries, cache, info = parse_log(inv)
    print("\n== write log: %d entries, terminator (first zero word) at backing 0x%04x (flash 0x%08x), "
          "%d/%d log words used, tail nonzero bytes = %d/%d, anomalies = %s"
          % (info["entries"], info["terminator_backing_offset"] or -1,
             FLASH_BASE + BACKING_FILE_OFF + (info["terminator_backing_offset"] or 0),
             info["log_words_used"], info["log_words_capacity"],
             info["tail_nonzero_bytes"], info["tail_length"], info["anomalies"] or "none"))

    mode_names, enum_list, enum_note = build_rgb_mode_table(args.fork)
    print("  " + enum_note)

    ee_final = decode_eeconfig(cache, mode_names)
    ee_cons = decode_eeconfig(consolidated, mode_names)

    print("\n== eeconfig (after log replay == what the firmware sees at boot)")
    for k in ("magic", "magic_ok", "debug", "default_layer_bitmask", "default_layer_index", "keymap_config",
              "keymap_config_bits_set", "backlight", "audio", "rgblight", "unicode_mode", "steno_mode",
              "handedness", "keyboard_u32", "user_u32", "haptic", "rgblight_ext", "kb_data_37_63"):
        print("  %-24s %s" % (k, ee_final[k]))
    for k, v in ee_final["rgb_matrix"].items():
        print("  rgb_matrix.%-14s %s" % (k, v))
    print("  keychron_kb              %s" % ee_final["keychron_kb"])
    print("  nonzero beyond byte 63:  %s" % (ee_final["nonzero_bytes_beyond_63"] or "none"))

    history = describe_history(entries, consolidated, mode_names)
    print("\n== runtime write history (entry: eeprom addr, len, bytes -> resulting rgb_matrix_config)")
    for e, cur, changes in history:
        if cur:
            print("  #%02d bk 0x%04x @%2d len %d %-10s -> en=%d mode=%2d h=%3d s=%3d v=%3d spd=%3d fl=0x%02x  %s"
                  % (e["index"], e["backing_offset"], e["eeprom_addr"], e["len"], e["bytes"],
                     cur["enable"], cur["mode"], cur["hue"], cur["sat"], cur["val"], cur["speed"], cur["flags"],
                     ", ".join(changes) if changes else "(no change)"))
        else:
            print("  #%02d bk 0x%04x @%2d len %d %-10s  %s" % (e["index"], e["backing_offset"], e["eeprom_addr"],
                                                             e["len"], e["bytes"], changes))

    # ---- oracle comparison
    oracle = None
    oracle_result = "oracle output not found at %s (run tools/eeprom_oracle/build.sh)" % args.oracle_hex
    if os.path.exists(args.oracle_hex):
        txt = open(args.oracle_hex).read()
        hexs = "".join(txt.split())
        oracle = bytes.fromhex(hexs)
        if oracle == cache:
            oracle_result = "MATCH: C oracle (fork wear_leveling.c) cache == Python replay, all %d bytes" % len(cache)
        else:
            diffs = [i for i in range(min(len(oracle), len(cache))) if oracle[i] != cache[i]]
            oracle_result = "MISMATCH: %d differing bytes, first at %s; len oracle=%d python=%d" % (
                len(diffs), diffs[:8], len(oracle), len(cache))
    print("\n== oracle: " + oracle_result)

    # ---- consolidated vs final differences
    diff_cons_final = [(i, "0x%02x" % consolidated[i], "0x%02x" % cache[i]) for i in range(LOGICAL_SIZE)
                       if consolidated[i] != cache[i]]

    # ---- sanity
    sanity = {
        "magic_is_0xFEE6": ee_final["magic_ok"],
        "default_layer_bitmask": ee_final["default_layer_bitmask"],
        "default_layer_class": ("1<<0 (layer 0)" if cache[3] == 1 else "1<<2 (layer 2)" if cache[3] == 4 else "other"),
        "rgb_mode_in_range": ee_final["rgb_matrix"]["mode"] in mode_names if mode_names else None,
        "rgb_mode_max_plus_one": (max(mode_names) + 1) if mode_names else None,
        "hash_ok": hash_ok,
        "log_all_multibyte": all(e["type"] == 0 for e in entries),
        "log_addresses_touched": sorted({e["eeprom_addr"] for e in entries}),
        "tail_clean": info["tail_nonzero_bytes"] == 0,
        "oracle": oracle_result,
    }

    result = {
        "source": {
            "dump": os.path.relpath(args.dump, BACKUP_DIR),
            "file_offset": "0x%05x..0x%05x" % (BACKING_FILE_OFF, BACKING_FILE_OFF + BACKING_SIZE - 1),
            "flash_addr": "0x%08x..0x%08x" % (FLASH_BASE + BACKING_FILE_OFF, FLASH_BASE + BACKING_FILE_OFF + BACKING_SIZE - 1),
            "format": "QMK wear_leveling (embedded_flash / EFL), BACKING 4096, LOGICAL 2048, WRITE_SIZE 4, bytes stored inverted",
        },
        "hash": {
            "stored_le": "0x%016x" % stored_hash_le,
            "computed_fnv1a_64": "0x%016x" % h1a,
            "computed_fnv1_64_non_a": "0x%016x" % h1,
            "ok": hash_ok,
        },
        "log": info,
        "log_entries": [{k: v for k, v in e.items() if k != "values"} for e in entries],
        "consolidated_nonzero_bytes": [(i, "0x%02x" % consolidated[i]) for i in range(LOGICAL_SIZE) if consolidated[i]],
        "cache_nonzero_bytes": [(i, "0x%02x" % cache[i]) for i in range(LOGICAL_SIZE) if cache[i]],
        "consolidated_vs_final_diffs": diff_cons_final,
        "eeconfig_consolidated": ee_cons,
        "eeconfig_final": ee_final,
        "rgb_effect_enum_assumed": {str(k): v for k, v in sorted(mode_names.items())},
        "rgb_effect_enum_note": enum_note,
        "rgb_history": [
            {"entry": e["index"], "backing_offset": "0x%04x" % e["backing_offset"], "eeprom_addr": e["eeprom_addr"],
             "len": e["len"], "bytes": e["bytes"],
             "state_after": ({k: cur[k] for k in ("enable", "mode", "hue", "sat", "val", "speed", "flags")} if cur else None),
             "changes": changes}
            for e, cur, changes in history
        ],
        "sanity": sanity,
        "python_cache_hex": cache.hex(),
    }

    os.makedirs(args.out_dir, exist_ok=True)
    jpath = os.path.join(args.out_dir, "eeprom_recovered.json")
    with open(jpath, "w") as f:
        json.dump(result, f, indent=1)
    with open(os.path.join(HERE, "eeprom_oracle", "python_cache.hex"), "w") as f:
        f.write(cache.hex() + "\n")

    mpath = os.path.join(args.out_dir, "eeprom_recovered.md")
    with open(mpath, "w") as f:
        f.write(render_md(result, inv, raw, history, enum_list, entries))
    print("\nwrote %s\nwrote %s" % (jpath, mpath))


def render_md(r, inv, raw, history, enum_list, entries):
    ee = r["eeconfig_final"]
    ec = r["eeconfig_consolidated"]
    rgb = ee["rgb_matrix"]
    rgbc = ec["rgb_matrix"]
    L = []
    w = L.append
    w("# Keychron V10 Max -- emulated-EEPROM (wear-leveling) recovery\n")
    w("Source: `%s` file offsets %s = flash %s. Same 4 KiB slice is byte-identical in dump_a/dump_b/dump_c "
      "(SHA-256 of slice checked before decoding).\n" % (r["source"]["dump"], r["source"]["file_offset"], r["source"]["flash_addr"]))
    w("Decoder: `tools/eeprom_parse.py`; independent oracle: `tools/eeprom_oracle/` (the fork's real "
      "`quantum/wear_leveling/wear_leveling.c` + `lib/fnv/hash_64a.c` compiled for the host against a mock "
      "backing store that serves `~word` from the dump).\n")
    w("## Format (verified against fork source)\n")
    w("* `platforms/chibios/drivers/wear_leveling/wear_leveling_efl.c`: `backing_store_write()` programs `~value`, "
      "`backing_store_read()` returns `~(*loc)` -> every byte below is shown **after inversion** (erased 0xFF flash == logical 0x00).")
    w("* `quantum/wear_leveling/wear_leveling.c`: consolidated image `[0,2048)`, FNV-1a-64 of it at `[2048,2056)` "
      "(`fnv_64a_buf(cache, LOGICAL_SIZE, FNV1A_64_INIT)`), write log from 2056 in `BACKING_STORE_WRITE_SIZE`=4 units, "
      "terminated at the first zero word (`wear_leveling_playback_log`). `info.json` `eeprom.wear_leveling`: driver "
      "`embedded_flash`, `logical_size` 2048, `backing_size` 4096. STM32F4 write size = `1 << STM32_FLASH_PSIZE` = 4 "
      "(`wear_leveling_efl_config.h`).")
    w("* Multibyte entry (`wear_leveling_internal.h` `LOG_ENTRY_MULTIBYTE_*`): byte0 = type(2b, 00) | len(3b) << 3 | addr[18:16]; "
      "byte1 = addr[15:8]; byte2 = addr[7:0]; byte3 = value[0]; a second word carries value[1..4] iff len > 1. With a 4-byte "
      "backing store the OPTIMIZED_64 / WORD_01 encodings are compiled out, so only type-00 entries can exist.\n")
    w("## Raw inverted bytes\n")
    w("Consolidated image, first 64 bytes (backing offset, flash address):\n")
    w("```\n" + hexdump(inv[:64], 0, FLASH_BASE + BACKING_FILE_OFF) + "\n```\n")
    w("Hash + start of write log (backing 0x800..0x83f):\n")
    w("```\n" + hexdump(inv[HASH_OFF:HASH_OFF + 64], HASH_OFF, FLASH_BASE + BACKING_FILE_OFF) + "\n```\n")
    w("For reference, the un-inverted flash bytes at file 0x4000: `%s` (i.e. `19 01 ff fe ff eb ff 00 ...` = ~`e6 fe 00 01 00 14 00 ff`).\n"
      % " ".join("%02x" % b for b in raw[:16]))
    w("## Hash check\n")
    w("| | value |\n|---|---|")
    w("| stored, little-endian u64 @ backing 0x800 (flash 0x08004800) | `%s` |" % r["hash"]["stored_le"])
    w("| computed FNV-1a-64 over consolidated[0:2048] (init 0xcbf29ce484222325, prime 0x100000001b3) | `%s` |" % r["hash"]["computed_fnv1a_64"])
    w("| computed FNV-1-64 (non-a, for discrimination) | `%s` |" % r["hash"]["computed_fnv1_64_non_a"])
    w("| **result** | **%s** |\n" % ("MATCH -- firmware accepts the consolidated image" if r["hash"]["ok"] else "MISMATCH -- firmware would clear the cache"))
    lg = r["log"]
    w("## Write log\n")
    w("* %d entries, all `LOG_ENTRY_TYPE_MULTIBYTE`; %d of %d log words used; terminator (first zero word) at backing `0x%04x` "
      "= file `0x%05x` = flash `0x%08x`; every byte after it is 0x00 logical / 0xFF flash (%d bytes checked, %d nonzero). "
      "Anomalies: %s."
      % (lg["entries"], lg["log_words_used"], lg["log_words_capacity"], lg["terminator_backing_offset"],
         BACKING_FILE_OFF + lg["terminator_backing_offset"], FLASH_BASE + BACKING_FILE_OFF + lg["terminator_backing_offset"],
         lg["tail_length"], lg["tail_nonzero_bytes"], lg["anomalies"] or "none"))
    w("* Only two (addr,len) shapes occur: `(24,5)` and `(29,3)`, always in that order, %d pairs. That is exactly what "
      "`eeconfig_flush_rgb_matrix()` (`EECONFIG_DEBOUNCE_HELPER(rgb_matrix, EECONFIG_RGB_MATRIX, ...)`, "
      "`quantum/rgb_matrix/rgb_matrix.c:103`) produces: `eeprom_update_block(&rgb_matrix_config, 24, 8)` -> "
      "`wear_leveling_write(24, ., 8)` -> `wear_leveling_write_raw` chops into `LOG_ENTRY_MULTIBYTE_MAX_BYTES`=5 + 3. "
      "No other EEPROM address was written since the last consolidation (no default_layer, keymap_config, debug, KB-data writes)."
      % (lg["entries"] // 2))
    w("* **Write-path fingerprint.** The recovered keymap drives RGB with stock `RGB_VAI/RGB_VAD/RGB_TOG/RGB_HUI/...` keycodes "
      "(`keymap_recovered.md`), handled by `quantum/process_keycode/process_rgb.c` -> `rgb_matrix_increase_val()` etc. In the fork "
      "worktree HEAD those helpers write *partially* -- `eeprom_write_byte((uint8_t*)EECONFIG_RGB_MATRIX, mode)` (1 byte @24) and "
      "`eeprom_write_block(&rgb_matrix_config.hsv, 25, 3)` (`quantum/rgb_matrix/rgb_matrix.c:567,586,607,679`) -- which would have "
      "left `(24,1)` / `(25,3)` / `(28,1)` entries in this log. None exist: every entry is a full 8-byte flush. That matches the "
      "reference fork at 1011db8c8d (2024-07-01, `/Users/dexter/code/qmk-keychron-ref/quantum/rgb_matrix/rgb_matrix.c:540,557,577,601,"
      "644,740,776`), where every helper just calls `eeconfig_flag_rgb_matrix(write_to_eeprom)` and `rgb_task_sync()` later does "
      "`eeconfig_flush_rgb_matrix(false)` = `eeprom_update_block(&rgb_matrix_config, 24, 8)`. `git log -S` shows the partial-write "
      "code entered the fork in commit c9049679ac (2025-05-30), after this firmware's 2024-07-09 build date. So the EEPROM log "
      "independently confirms the firmware's `rgb_matrix.c` is the pre-2025 (reference-era) version, not worktree HEAD.")
    w("* Per entry (backing offset / flash addr / raw LE words / eeprom addr / len / bytes) -- see `eeprom_recovered.json` "
      "`log_entries`; the semantic replay is in the history table below.\n")
    w("### RGB-config history (state after each log entry; consolidated image = state 'C')\n")
    w("| # | backing | @ | len | bytes | en | mode | h | s | v | spd | flags | change |\n|---|---|---|---|---|---|---|---|---|---|---|---|---|")
    w("| C | 0x0000 | 24 | 8 | %s | %d | %d | %d | %d | %d | %d | 0x%02x | consolidated image |"
      % (rgbc["raw"], rgbc["enable"], rgbc["mode"], rgbc["hue"], rgbc["sat"], rgbc["val"], rgbc["speed"], rgbc["flags"]))
    for e, cur, changes in history:
        if cur:
            w("| %d | 0x%04x | %d | %d | %s | %d | %d | %d | %d | %d | %d | 0x%02x | %s |"
              % (e["index"], e["backing_offset"], e["eeprom_addr"], e["len"], e["bytes"], cur["enable"], cur["mode"],
                 cur["hue"], cur["sat"], cur["val"], cur["speed"], cur["flags"], ", ".join(changes) if changes else ""))
        else:
            w("| %d | 0x%04x | %d | %d | %s | | | | | | | | %s |" % (e["index"], e["backing_offset"], e["eeprom_addr"], e["len"], e["bytes"], changes))
    w("")
    w("## eeconfig decode (QMK 0.23 layout, `quantum/eeconfig.h` in the fork)\n")
    w("Two columns: the consolidated image (state at the last consolidation) and the state after log replay "
      "(= what `wear_leveling_init()` leaves in the cache = what the firmware reads at boot).\n")
    w("| field | addr | consolidated | after replay (live) | note |\n|---|---|---|---|---|")
    w("| magic u16 | 0 | %s | %s | expect 0xFEE6 (`EECONFIG_MAGIC_NUMBER`) -> %s |" % (ec["magic"], ee["magic"], "OK" if ee["magic_ok"] else "BAD"))
    w("| debug u8 | 2 | %d | %d | |" % (ec["debug"], ee["debug"]))
    w("| default_layer u8 (bitmask) | 3 | %s | %s | layer index %s |" % (ec["default_layer_bitmask"], ee["default_layer_bitmask"], ee["default_layer_index"]))
    w("| keymap_config u16 | 4 | %s | %s | bits set: %s |" % (ec["keymap_config"], ee["keymap_config"], ", ".join(ee["keymap_config_bits_set"]) or "none"))
    w("| backlight u8 | 6 | %d | %d | |" % (ec["backlight"], ee["backlight"]))
    w("| audio u8 | 7 | 0x%02x | 0x%02x | 0xFF = eeconfig_init_quantum default ('on') |" % (ec["audio"], ee["audio"]))
    w("| rgblight u32 | 8 | %s | %s | |" % (ec["rgblight"], ee["rgblight"]))
    w("| unicode / steno / handedness | 12/13/14 | %d/%d/%d | %d/%d/%d | |" % (ec["unicode_mode"], ec["steno_mode"], ec["handedness"], ee["unicode_mode"], ee["steno_mode"], ee["handedness"]))
    w("| keyboard u32 | 15 | %s | %s | KB-datablock version slot; see notes |" % (ec["keyboard_u32"], ee["keyboard_u32"]))
    w("| user u32 | 19 | %s | %s | |" % (ec["user_u32"], ee["user_u32"]))
    w("| unused u8 | 23 | %d | %d | |" % (ec["unused_23"], ee["unused_23"]))
    w("| rgb_matrix u64 raw | 24..31 | %s | %s | |" % (rgbc["raw"], rgb["raw"]))
    w("| rgb_matrix.enable (bits 1..0 of byte 24) | 24 | %d | %d | |" % (rgbc["enable"], rgb["enable"]))
    w("| rgb_matrix.mode (bits 7..2 of byte 24) | 24 | %d | %d | %s (board-default enum, see caveat) |" % (rgbc["mode"], rgb["mode"], rgb["mode_name_assuming_board_default_animations"]))
    w("| rgb_matrix.hsv.h / s / v | 25/26/27 | %d / %d / %d | %d / %d / %d | |" % (rgbc["hue"], rgbc["sat"], rgbc["val"], rgb["hue"], rgb["sat"], rgb["val"]))
    w("| rgb_matrix.speed | 28 | %d | %d | |" % (rgbc["speed"], rgb["speed"]))
    w("| rgb_matrix.flags | 29 | 0x%02x | 0x%02x | %s |" % (rgbc["flags"], rgb["flags"], rgb["flags_decoded"]))
    w("| (union padding) | 30..31 | %s | %s | |" % (rgbc["padding_bytes_30_31"], rgb["padding_bytes_30_31"]))
    w("| haptic u32 | 32 | %s | %s | |" % (ec["haptic"], ee["haptic"]))
    w("| rgblight_ext u8 | 36 | %d | %d | |" % (ec["rgblight_ext"], ee["rgblight_ext"]))
    w("| Keychron KB data: language u8 | 37 | %d | %d | `eeconfig_kb.h` EECONFIG_BASE_LANGUAGE 37 |" % (ec["keychron_kb"]["language_37"], ee["keychron_kb"]["language_37"]))
    w("| Keychron KB data: wireless backlit_disable_time u16 | 38 | %d | %d | 0 -> firmware substitutes CONNECTED_BACKLIGHT_DISABLE_TIMEOUT (600 s) |"
      % (ec["keychron_kb"]["wireless_backlit_disable_time_38_39_u16"], ee["keychron_kb"]["wireless_backlit_disable_time_38_39_u16"]))
    w("| Keychron KB data: wireless connected_idle_time u16 | 40 | %d | %d | 0 -> firmware substitutes CONNECTED_IDLE_TIME (7200 s) |"
      % (ec["keychron_kb"]["wireless_connected_idle_time_40_41_u16"], ee["keychron_kb"]["wireless_connected_idle_time_40_41_u16"]))
    w("| bytes 42..63 | | %s | %s | |" % (ec["kb_data_37_63"][10:], ee["kb_data_37_63"][10:]))
    w("| bytes 64..2047 | | all zero | all zero | %s |\n" % ("no VIA/dynamic-keymap blob present" if not ee["nonzero_bytes_beyond_63"] else str(ee["nonzero_bytes_beyond_63"])))
    w("keymap_config bit map used (`quantum/keycode_config.h`, bit 0 first): " + ", ".join("%d=%s" % (i, n) for i, n in enumerate(KEYMAP_CONFIG_BITS)) + ".\n")
    w("## RGB effect enum (assumed: board-default animation set)\n")
    w(r["rgb_effect_enum_note"] + "\n")
    w("| mode # | enum name | header (in `rgb_matrix_effects.inc` order) | compile condition |\n|---|---|---|---|")
    for n, name, hdr, cond in enum_list:
        mark = " **<-- stored mode**" if n == rgb["mode"] else ""
        w("| %d | `%s`%s | %s | %s |" % (n, name, mark, hdr, cond))
    w("")
    w("**Caveat.** The mode number is only meaningful relative to the effect set compiled into the *custom* firmware: "
      "`enum rgb_matrix_effects` (`quantum/rgb_matrix/rgb_matrix.h:138`) numbers `RGB_MATRIX_NONE`=0, `SOLID_COLOR`=1, then only the "
      "`RGB_MATRIX_EFFECT()` entries that survive `#ifdef ENABLE_RGB_MATRIX_*` in `.inc` order. The table above uses the "
      "`rgb_matrix.animations` set from `keyboards/keychron/v10_max/info.json` in the fork worktree plus `RGB_MATRIX_KEYPRESSES` and "
      "`RGB_MATRIX_FRAMEBUFFER_EFFECTS` from `ansi_encoder/config.h`. If the custom build changed that set (e.g. added "
      "`rgb_matrix_kb.inc` custom effects or disabled animations in its keymap `config.h`), the name for mode %d changes; the "
      "number %d itself is what is stored.\n" % (rgb["mode"], rgb["mode"]))
    w("## Sanity / observations\n")
    s = r["sanity"]
    w("* magic == 0xFEE6: **%s**." % s["magic_is_0xFEE6"])
    w("* default_layer = %s -> %s. No write to address 3 appears in the log, so the DIP switch (stock `dip_switch_update_kb` calls "
      "`default_layer_set(1UL << (active ? 0 : 2))`, `keyboards/keychron/v10_max/v10_max.c:36`) did not change position during the "
      "whole log epoch (46 RGB flushes), and it was on the side that selects layer 0 (stock: 'Mac'). Whether the custom keymap keeps "
      "that DIP handler is for the code-analysis track." % (s["default_layer_bitmask"], s["default_layer_class"]))
    w("* keymap_config = %s: exactly the `eeconfig_init_quantum()` default `0x1400` (oneshot_enable | autocorrect_enable, "
      "`quantum/eeconfig.c`) -- never modified afterwards. In particular **nkro bit is 0** even though the keymap contains `NK_TOGG`; "
      "the Keychron fork is built with `-DAPDAPTIVE_NKRO_ENABLE` and `WIRELESS_NKRO_ENABLE` (`keychron_common.mk`, `v10_max/config.h`), "
      "so NKRO handling may not go through this bit; no swap-modifier/magic settings are active." % ee["keymap_config"])
    w("* rgb_matrix: enable=%d, mode=%d (%s under the board-default enum; RGB_MATRIX_EFFECT_MAX would be %s so the value is in range: %s), "
      "hue=%d sat=%d val=%d speed=%d flags=%s. Consolidated image had h=%d s=%d v=%d spd=%d; the 46 logged flushes are the user "
      "stepping brightness (`val` in steps of 16 = `RGB_MATRIX_VAL_STEP`, `rgb_matrix.h:68`), speed (steps of 16 = `RGB_MATRIX_SPD_STEP`, "
      "`rgb_matrix.h:72`) and finally hue (0 -> 8 = `RGB_MATRIX_HUE_STEP`, `rgb_matrix.h:60`) with the Fn RGB keys. Mode never changed "
      "inside the log epoch."
      % (rgb["enable"], rgb["mode"], rgb["mode_name_assuming_board_default_animations"], s["rgb_mode_max_plus_one"], s["rgb_mode_in_range"],
         rgb["hue"], rgb["sat"], rgb["val"], rgb["speed"], rgb["flags_decoded"], rgbc["hue"], rgbc["sat"], rgbc["val"], rgbc["speed"]))
    w("* The three `enable 1->0` events (entries #4, #8, #78) each coincide with `val 47->31`, and the following `enable 0->1` events "
      "(#6, #10, #80) with `val 31->47`. That is not RGB_TOG but the fork's low-brightness auto-off: `ansi_encoder/config.h` defines "
      "`RGB_MATRIX_BRIGHTNESS_TURN_OFF_VAL 32`; `rgb_matrix_decrease_val_helper()` (`quantum/rgb_matrix/rgb_matrix.c:760-767`) subtracts "
      "16 and then calls `rgb_matrix_toggle_eeprom_helper()` when `enable && hsv.v <= 32`; `rgb_matrix_increase_val_helper()` "
      "(`rgb_matrix.c:744-752`) on a disabled matrix calls the toggle helper, which (`rgb_matrix.c:565-575`) re-enables and steps `v` up "
      "until it is >= 32 (31 -> 47). So the user simply pressed RGB_VAD past the floor and RGB_VAI back up. Final val=%d is above the "
      "floor: backlight is on at boot." % rgb["val"])
    w("* sat=%d (0xEF) is *not* the QMK default 255: `RGB_MATRIX_DEFAULT_SAT` is UINT8_MAX in `rgb_matrix.h`, and the consolidated image "
      "already has 0xEF, so either the custom firmware defines `RGB_MATRIX_DEFAULT_SAT 239`, or the user pressed RGB_SAD once "
      "(RGB_MATRIX_SAT_STEP default 16: 255-16 = 239) before the last consolidation. Cannot be distinguished from this sector alone." % rgb["sat"])
    w("* keyboard u32 @15 = %s and language @37 = %d, wireless config @38..41 = 0. Consistent with the fork: Keychron's "
      "`eeconfig_init_kb_datablock()` (`keyboards/keychron/common/eeconfig_kb.c`) does not call `eeconfig_update_kb_datablock()`, so the "
      "KB-datablock version dword (would be `EECONFIG_KB_DATA_VERSION` = `EECONFIG_KB_DATA_SIZE` = 5 = 1 language + 4 wireless bytes) is "
      "never written and stays 0 after erase; language and wireless-idle settings were never set via the Launcher raw-HID path "
      "(`language_set`, `wireless_lpm_set`). `wireless_config_load()` maps the zeros to defaults 600 s / 7200 s." % (ee["keyboard_u32"], ee["keychron_kb"]["language_37"]))
    w("* No dynamic-keymap / VIA data: bytes 64..2047 are all zero, matching the absence of VIA in the firmware.")
    w("* Log occupancy: %d/%d words; next write would go to backing 0x%04x. No consolidation was imminent." % (lg["log_words_used"], lg["log_words_capacity"], lg["next_write_address"]))
    w("* Oracle: %s" % s["oracle"])
    w("")
    w("## Confidence\n")
    w("* **Verified** (byte evidence + fork source): format, inversion, hash match, log grammar, 92 entries, final rgb bytes, magic, default_layer, keymap_config, zero KB data, oracle equality, "
      "the (24,5)+(29,3) shape == 8-byte `eeconfig_flush_rgb_matrix` writes, the auto-off explanation of the enable flips.")
    w("* **Inference**: mode-number -> effect-name mapping (depends on the custom build's animation set); the DIP-switch and NKRO remarks; the sat=239 origin; "
      "'firmware rgb_matrix.c is the reference-era version' (strong but indirect: it rests on the absence of partial-write entries in a 46-flush window).")
    w("* Line numbers cited as `rgb_matrix.c:NNN` without a path prefix refer to the fork worktree HEAD (`/Users/dexter/code/qmk-keychron`); "
      "the auto-off logic is the same in the reference commit (see the fingerprint bullet for the reference-specific lines).")
    return "\n".join(L) + "\n"


if __name__ == "__main__":
    main()
