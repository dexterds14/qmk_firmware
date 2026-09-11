#!/usr/bin/env python3
"""Post-process the Ghidra exports in keychron_v10max_backup/.

Prints / writes ghidra_summary.md with:
  * function count and code-region coverage (from ghidra_coverage.txt)
  * the 20 largest functions
  * functions referencing the keymaps[] table (from ghidra_xrefs.json)
  * functions whose decompiled body contains keycode-like constants:
      0x7E40..0x7E4F (QK_USER_n), 0x5700..0x57FF (TD/TO/MO/OSL/OSM... layer & tap-dance range),
      0x7C58 (QK_LEADER), 0x7C00 (QK_BOOT), 0x7013 (NK_TOGG), 0x7701..0x7705 (MC_n),
      0x7E04..0x7E0F (Keychron keycodes)
    and how many *distinct* such constants appear (a switch over keycodes shows several)
"""
import csv, json, os, re, sys
from collections import Counter, defaultdict

HERE = os.path.dirname(os.path.abspath(__file__))
BACKUP = os.path.abspath(os.path.join(HERE, "..", ".."))
DEC = os.path.join(BACKUP, "decompiled")

RANGES = [
    ("QK_USER", 0x7E40, 0x7E4F),
    ("KC_KB(0x7E00-0x7E3F)", 0x7E00, 0x7E3F),
    ("layer/TD range 0x5700-0x57FF", 0x5700, 0x57FF),
    ("QK_LEADER", 0x7C58, 0x7C58),
    ("QK_BOOT", 0x7C00, 0x7C00),
    ("NK_TOGG", 0x7013, 0x7013),
    ("MC_n", 0x7701, 0x7705),
    ("OSM range 0x5400-0x54FF", 0x5400, 0x54FF),  # spec 0.0.3: QK_ONE_SHOT_MOD 0x52A0..0x52BF actually; keep broad
    ("QK_ONE_SHOT_LAYER 0x5280-0x529F", 0x5280, 0x529F),
    ("QK_ONE_SHOT_MOD 0x52A0-0x52BF", 0x52A0, 0x52BF),
    ("QK_TAP_DANCE 0x5700-0x57FF", 0x5700, 0x57FF),
    ("QK_LAYER_MOD/TO/MO 0x5200-0x527F", 0x5200, 0x527F),
    ("QK_RGB/underglow 0x7800-0x78FF", 0x7800, 0x78FF),
    ("QK_RGB_MATRIX 0x7820-0x783F", 0x7820, 0x783F),
]
HEX_RE = re.compile(r"0x([0-9a-fA-F]{4,5})\b")


def load_functions():
    rows = []
    with open(os.path.join(BACKUP, "ghidra_functions.csv"), newline="") as f:
        for r in csv.DictReader(f):
            r["size"] = int(r["size"]); r["addr"] = int(r["entry"], 16)
            rows.append(r)
    return rows


def main():
    fns = load_functions()
    cov = open(os.path.join(BACKUP, "ghidra_coverage.txt")).read().split("\n\n")[0]
    xrefs = json.load(open(os.path.join(BACKUP, "ghidra_xrefs.json")))
    out = []
    out.append("# Ghidra auto-analysis summary (dump_a.bin @ 0x08000000)\n")
    out.append("## Coverage\n```\n" + cov.strip() + "\n```\n")
    out.append(f"Total functions: {len(fns)}\n")

    out.append("## 20 largest functions\n")
    out.append("| entry | size | name | callers | callees | strings |\n|---|---|---|---|---|---|")
    for r in sorted(fns, key=lambda r: -r["size"])[:20]:
        out.append(f"| {r['entry']} | {r['size']} | {r['name']} | {r['n_callers']} | {r['n_callees']} | {r['strings'][:80].replace('|','/')} |")
    out.append("")

    out.append("## Functions referencing keymaps[] (0x080169B8)\n")
    for e in xrefs["functions_referencing_keymaps"]:
        out.append(f"- {e['addr']} {e['name']}")
    out.append("\nLiteral-pool words pointing into keymaps[]:")
    for w in xrefs["literal_words"]:
        rd = ", ".join(f"{r['from']}@{(r['fn'] or {}).get('name','-')}" for r in w["readers"])
        out.append(f"- word {w['word_addr']} = {w['value']} (+{w['offset_in_keymaps']}) inside {(w['inside_fn'] or {}).get('name','-')}; readers: {rd}")
    out.append("")

    # keycode-constant scan over decompiled C
    out.append("## Functions whose decompiled body contains keycode-like constants\n")
    hits = []
    for fn in sorted(os.listdir(DEC)):
        if not fn.endswith(".c") or fn.startswith("_"):
            continue
        body = open(os.path.join(DEC, fn), errors="replace").read()
        consts = Counter()
        tags = defaultdict(set)
        for m in HEX_RE.finditer(body):
            v = int(m.group(1), 16)
            for name, lo, hi in RANGES:
                if lo <= v <= hi:
                    consts[v] += 1
                    tags[name].add(v)
        n_case = body.count("case 0x")
        n_switch = body.count("switch")
        refs_keymaps = "keymaps" in body
        if consts or refs_keymaps:
            hits.append((fn, consts, tags, n_switch, n_case, refs_keymaps))
    hits.sort(key=lambda h: (-len(h[1]), h[0]))
    out.append("| file | distinct keycode consts | switches | cases | refs keymaps | constants |\n|---|---|---|---|---|---|")
    for fn, consts, tags, ns, nc, rk in hits:
        cl = " ".join(f"0x{v:04X}" for v in sorted(consts))
        out.append(f"| {fn} | {len(consts)} | {ns} | {nc} | {'yes' if rk else ''} | {cl[:120]} |")
    out.append("")

    text = "\n".join(out)
    with open(os.path.join(BACKUP, "ghidra_summary.md"), "w") as f:
        f.write(text)
    print(text)


if __name__ == "__main__":
    main()
