#!/usr/bin/env python3
"""Locate and decode the compiled keymaps[] / encoder_map[] tables in a QMK flash dump.

Usage (run from the fork worktree root so qmk.keycodes finds data/constants):
  <qmk venv python> tools/keymap_decode.py DUMP.bin --spec 0.0.3 \
      --layout keyboards/keychron/v10_max/ansi_encoder/info.json --out OUTDIR

Locates the table structurally: a 6x18 uint16 matrix where all 19 unused cells are 0 on every
layer. Decodes with the QMK keycode spec plus quantum_keycodes.h range arithmetic and Keychron's
custom keycode enum (QK_KB_0..). Emits JSON, Markdown and a LAYOUT_ansi_89-ordered C rendering.
"""
import argparse, json, struct, sys, os

ROWS, COLS = 6, 18
UNUSED = [(0,15),(0,16),(1,15),(1,16),(2,7),(2,16),(3,7),(3,15),(3,16),(4,2),(4,15),(4,17),
          (5,3),(5,5),(5,8),(5,10),(5,12),(5,13),(5,14)]
UIDX = [r*COLS+c for r, c in UNUSED]
LAYER_BYTES = ROWS*COLS*2

# Keychron keychron_common.h enum with LK_WIRELESS_ENABLE, no lock-screen options.
KEYCHRON_KB = {0x7E00:'KC_LOPTN',0x7E01:'KC_ROPTN',0x7E02:'KC_LCMMD',0x7E03:'KC_RCMMD',0x7E04:'KC_MCTRL',
               0x7E05:'KC_LNPAD',0x7E06:'KC_TASK',0x7E07:'KC_FILE',0x7E08:'KC_SNAP',0x7E09:'KC_CTANA',
               0x7E0A:'KC_SIRI',0x7E0B:'BT_HST1',0x7E0C:'BT_HST2',0x7E0D:'BT_HST3',0x7E0E:'P2P4G',0x7E0F:'BAT_LVL'}

MOD_NAMES = [(0x01,'MOD_LCTL'),(0x02,'MOD_LSFT'),(0x04,'MOD_LALT'),(0x08,'MOD_LGUI')]
MOD_FN = {0x01:'LCTL',0x02:'LSFT',0x04:'LALT',0x08:'LGUI',0x11:'RCTL',0x12:'RSFT',0x14:'RALT',0x18:'RGUI'}

def load_spec(version):
    sys.path.insert(0, os.path.join(os.getcwd(), 'lib', 'python'))
    from qmk.keycodes import load_spec as ls
    spec = ls(version)
    table = {int(k, 16): v for k, v in spec['keycodes'].items()}
    return spec, table

def mods_str(m5):
    mods = [n for bit, n in MOD_NAMES if m5 & bit]
    if m5 & 0x10:
        mods = [n.replace('MOD_L', 'MOD_R') for n in mods]
    return '|'.join(mods) if mods else '0'

def basic_name(kc, table, flagged):
    if kc == 0: return 'XXXXXXX'
    if kc == 1: return '_______'
    e = table.get(kc)
    if e:
        return e['key']
    flagged.append(('unknown-basic', kc))
    return '0x%04X' % kc

def decode(kc, table, flagged):
    if kc <= 0x00FF:
        return basic_name(kc, table, flagged)
    if 0x0100 <= kc <= 0x1FFF:            # QK_MODS
        m5 = (kc >> 8) & 0x1F; base = kc & 0xFF
        inner = basic_name(base, table, flagged)
        # single-mod convenience wrappers
        if m5 in MOD_FN: return '%s(%s)' % (MOD_FN[m5], inner)
        names = [n for bit, n in [(0x01,'LCTL'),(0x02,'LSFT'),(0x04,'LALT'),(0x08,'LGUI')] if m5 & bit]
        if m5 & 0x10: names = ['R'+n[1:] for n in names]
        for n in names: inner = '%s(%s)' % (n, inner)
        return inner
    if 0x2000 <= kc <= 0x3FFF:            # MT
        m5 = (kc >> 8) & 0x1F; base = kc & 0xFF
        inner = basic_name(base, table, flagged)
        flagged.append(('MT', kc))
        if m5 in MOD_FN: return '%s_T(%s)' % (MOD_FN[m5], inner)
        return 'MT(%s, %s)' % (mods_str(m5), inner)
    if 0x4000 <= kc <= 0x4FFF:            # LT
        flagged.append(('LT', kc))
        return 'LT(%d, %s)' % ((kc >> 8) & 0xF, basic_name(kc & 0xFF, table, flagged))
    if 0x5000 <= kc <= 0x51FF:
        flagged.append(('LM', kc)); return 'LM(%d, %s)' % ((kc >> 5) & 0xF, mods_str(kc & 0x1F))
    for base, name in [(0x5200,'TO'),(0x5220,'MO'),(0x5240,'DF'),(0x5260,'TG'),(0x5280,'OSL'),(0x52A0,'OSM'),(0x52C0,'TT')]:
        if base <= kc < base + 0x20:
            if name in ('TO','DF','TG','OSL','OSM','TT'): flagged.append((name, kc))
            if name == 'OSM': return 'OSM(%s)' % mods_str(kc & 0x1F)
            return '%s(%d)' % (name, kc & 0x1F)
    if 0x5600 <= kc <= 0x56FF:
        flagged.append(('SH', kc))
        e = table.get(kc)
        return e['key'] if e else 'SH_T(%s)' % basic_name(kc & 0xFF, table, flagged)
    if 0x5700 <= kc <= 0x57FF:
        flagged.append(('TD', kc)); return 'TD(%d)' % (kc & 0xFF)
    if 0x7700 <= kc <= 0x777F:
        flagged.append(('MACRO', kc)); return 'MC_%d' % (kc & 0x7F)
    if 0x7E00 <= kc <= 0x7E3F:
        if kc in KEYCHRON_KB: return KEYCHRON_KB[kc]
        flagged.append(('CUSTOM_KB', kc)); return 'USER_KC_%02X /*0x%04X*/' % (kc - 0x7E10, kc)
    if 0x7E40 <= kc <= 0x7FFF:
        flagged.append(('QK_USER', kc)); return 'QK_USER_%d' % (kc - 0x7E40)
    if kc >= 0x8000:
        flagged.append(('UNICODE', kc)); return 'UC(0x%04X)' % (kc & 0x7FFF)
    e = table.get(kc)
    if e:
        if 0x7C00 <= kc <= 0x7DFF or 0x7000 <= kc <= 0x70FF: flagged.append(('QUANTUM/MAGIC', kc))
        return e['key']
    flagged.append(('unknown', kc))
    return '0x%04X' % kc

def find_table(b, start, end):
    cands = []
    for off in range(start, end - LAYER_BYTES, 2):
        w = struct.unpack_from('<%dH' % (ROWS*COLS), b, off)
        if any(w[i] for i in UIDX): continue
        used = [w[i] for i in range(ROWS*COLS) if i not in UIDX]
        if sum(1 for x in used if x) < 50: continue
        cands.append(off)
    groups = []
    for off in cands:
        if groups and off == groups[-1][-1] + LAYER_BYTES: groups[-1].append(off)
        else: groups.append([off])
    groups = [g for g in groups if len(g) >= 2]
    return groups

def main():
    ap = argparse.ArgumentParser()
    ap.add_argument('dump'); ap.add_argument('--spec', default='0.0.3')
    ap.add_argument('--layout', required=True); ap.add_argument('--out', required=True)
    ap.add_argument('--base', type=lambda x: int(x, 0), default=0x08000000)
    ap.add_argument('--offset', type=lambda x: int(x, 0), help='force table offset')
    ap.add_argument('--layers', type=int, help='force layer count')
    a = ap.parse_args()
    b = open(a.dump, 'rb').read()
    end = len(b.rstrip(b'\xff'))
    spec, table = load_spec(a.spec)
    lay = json.load(open(a.layout))['layouts']
    lname = list(lay.keys())[0]; order = [tuple(k['matrix']) for k in lay[lname]['layout']]
    if a.offset:
        off = a.offset; nl = a.layers or 1
    else:
        groups = find_table(b, 0x8000, end)
        if not groups: sys.exit('no keymap table found')
        g = max(groups, key=len); off = g[0]; nl = len(g)
        print('candidates:', [(hex(x[0]), len(x)) for x in groups])
    print('keymaps @ file 0x%05x (flash 0x%08x), %d layers, %d bytes' % (off, a.base+off, nl, nl*LAYER_BYTES))
    layers = []; flagged = []
    for L in range(nl):
        w = struct.unpack_from('<%dH' % (ROWS*COLS), b, off + L*LAYER_BYTES)
        layers.append(w)
    # encoder map candidate right after the table: nl x 1 x 2 x u16
    enc_off = off + nl*LAYER_BYTES
    enc = [struct.unpack_from('<2H', b, enc_off + 4*L) for L in range(nl)]
    out = {'source': os.path.basename(a.dump), 'table_file_offset': off, 'table_flash_addr': a.base+off,
           'layers_count': nl, 'layout': lname, 'spec': a.spec, 'matrix': {'rows': ROWS, 'cols': COLS},
           'raw_matrix_hex': [['0x%04X' % w[r*COLS+c] for r in range(ROWS) for c in range(COLS)] for w in layers],
           'layers': [], 'encoder_map_candidate': {'file_offset': enc_off, 'raw': [['0x%04X' % x for x in e] for e in enc]},
           'flagged': []}
    md = ['# Recovered keymap (%s, %d layers, table @ 0x%08X)\n' % (lname, nl, a.base+off)]
    c_lines = ['const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {']
    for L, w in enumerate(layers):
        fl = []
        names = [decode(w[r*COLS+c], table, fl) for (r, c) in order]
        out['layers'].append(names)
        out['flagged'].append(sorted(set((k, '0x%04X' % v) for k, v in fl)))
        flagged += [(L, k, v) for k, v in fl]
        md.append('\n## Layer %d\n' % L)
        md.append('| r\\c | ' + ' | '.join(str(c) for c in range(COLS)) + ' |')
        md.append('|' + '---|' * (COLS+1))
        for r in range(ROWS):
            md.append('| %d | ' % r + ' | '.join(decode(w[r*COLS+c], table, []) if (r, c) not in UNUSED else '' for c in range(COLS)) + ' |')
        # C rendering, one line per physical row
        c_lines.append('    [%d] = %s(' % (L, lname))
        row_groups = {}
        for (r, c), n in zip(order, names): row_groups.setdefault(r, []).append(n)
        for r in range(ROWS):
            c_lines.append('        ' + ', '.join(row_groups[r]) + (',' if r < ROWS-1 else ''))
        c_lines.append('    ),')
    c_lines.append('};')
    enc_names = []
    for L, (cw, ccw) in enumerate(enc):
        enc_names.append({'cw': decode(cw, table, []), 'ccw': decode(ccw, table, [])})
    out['encoder_map_candidate']['decoded'] = enc_names
    md.append('\n## Encoder map candidate @ 0x%08X (cw, ccw per layer)\n' % (a.base+enc_off))
    for L, e in enumerate(enc_names): md.append('- layer %d: cw=%s ccw=%s' % (L, e['cw'], e['ccw']))
    md.append('\n## Flagged (non-basic) keycodes per layer\n')
    for L, f in enumerate(out['flagged']): md.append('- layer %d: %s' % (L, ', '.join('%s %s' % x for x in f) or 'none'))
    os.makedirs(a.out, exist_ok=True)
    json.dump(out, open(os.path.join(a.out, 'keymap_recovered.json'), 'w'), indent=1)
    open(os.path.join(a.out, 'keymap_recovered.md'), 'w').write('\n'.join(md) + '\n')
    open(os.path.join(a.out, 'keymap_recovered_table.c'), 'w').write('\n'.join(c_lines) + '\n')
    print('\n'.join(c_lines))
    print('\nencoder candidates:', enc_names)
    print('\nflagged:', sorted(set('%s 0x%04X' % (k, v) for _, k, v in flagged)))

if __name__ == '__main__':
    main()
