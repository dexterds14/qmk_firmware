#!/usr/bin/env python3
"""annotate_linkorder.py -- post-process the DP alignment (linkorder_align.py) into the
deliverable functions_linkorder.csv:
  * caller-vote inference: an unmatched dump function called by dump functions whose ref
    counterparts all call the same still-unassigned ref function inherits that symbol
    (resolves the plain-.text libc cluster: memcpy/memset/..., and clones the DP skipped)
  * verified hook overrides for the user's keymap object (caller/pointer evidence)
  * exact-content matching of ref .rodata/.data objects into the dump image
  * coverage numbers and unmatched regions

  uv run --with capstone python3 annotate_linkorder.py --align dump_vs_feat.csv --align-json dump_vs_feat.json
      --det dump_det.json --dump dump_a.bin --ref-map ref1011_feat.map --ref-bin ref1011_feat.bin
      --text-end 0x08016704 --rodata-end 0x08017744 --data-start 0x0801774c --image-end 0x08017F04
      --out functions_linkorder.csv --summary functions_linkorder_summary.json
"""
import sys, os, csv, json, argparse, bisect, struct
sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import linkorder_align as LA

BASE = 0x08000000

# dump_addr -> (name, evidence, confidence)   -- verified by hand from disassembly; see notes
VERIFIED_HOOKS = {
    0x0800cdd8: ('td0_on_reset [user, tap_dance_actions[0].fn.on_reset]', 'pointer word 0x0800cdd9 at flash 0x080179d8 = tap_dance_actions[0].fn.on_reset (layout verified against ref .data at 0x08016e84); body = bx lr', 'verified'),
    0x0800cdda: ('td_oneshot_layer1_helper [user static]', 'tail-called (b.w) from td0_on_dance_finished at 0x0800d216; calls layer_on(1) @0x0800dc64, set_oneshot_layer(1,ONESHOT_START=3) @0x0800e504, clear_oneshot_layer_state(ONESHOT_PRESSED=1) @0x0800e548', 'verified'),
    0x0800cdf4: ('leader_start_user [user]', 'BL target of leader_start @0x08011948 (dump 0x08011940 = leader_start, opsim 1.0 region); body: rgb_matrix_set_color_all(0xff,0,0xff) tail call to 0x0800fee4', 'verified'),
    0x0800cdfe: ('leader_end_user [user]', 'BL target of leader_end @0x0801197c (its only call); body: rgb_matrix_set_color_all(0,0,0), then leader_sequence_one_key/two_keys (0x08011a3c/0x08011a50) chains with register_code (0x0800d570)/unregister_code (0x0800d600) on literal keycodes', 'verified'),
    0x0800cf60: ('keyboard_post_init_user [user]', 'tail-call (b.w) target at 0x0800cd76, last instruction of keyboard_post_init_kb @0x0800cd38 (v10_max.c, opsim 0.91); body: default_layer_set(0) @0x0800dbe2 then rgb_matrix_mode(16) @0x08010d40', 'verified'),
    0x0800cf74: ('rgb_matrix_indicators_advanced_user [user]', 'BL target of rgb_matrix_indicators_advanced_kb @0x08010c4c (its only call); loops led_min..led_max, get_highest_layer via biton16(layer_state|default_layer_state) @0x0800d488, tbb switch over layers 1..5 -> rgb_matrix_set_color @0x0800fe78', 'verified'),
    0x0800d010: ('osm_indicator_helper [user static]', 'tail-called by both 4-byte thunks 0x0800d088/0x0800d08c; masks mods with 0x22 (L/R shift) and ~0x77 (GUI bits); drives rgb_matrix_set_color_all @0x0800fee4 with RAM flags 0x200015dd/0x200015de', 'verified'),
    0x0800d088: ('oneshot_mods_changed_user [user]', 'BL target of oneshot_mods_changed_kb @0x0800e3e4 (8 B, opsim 1.0); body = b.w 0x0800d010', 'verified'),
    0x0800d08c: ('oneshot_locked_mods_changed_user [user]', 'BL target of oneshot_locked_mods_changed_kb @0x0800e38c (8 B, opsim 1.0); body = b.w 0x0800d010', 'verified'),
    0x0800d090: ('osm_lookup_helper [user static]', 'called only from 0x0800d0b4; scans a 2-entry u16 table via pointer at RAM 0x200015e0', 'likely'),
    0x0800d0b4: ('osm_press_handler [user static]', 'tail-called from process_record_user (0x0800d15a) for pressed OSM keycodes {0x52A2,0x52A8,0x52B2,0x52B8}; calls get_mods, clear_oneshot_mods, 0x0800e3b0 (action_util insertion), get_oneshot_mods, unregister_mods', 'verified'),
    0x0800d104: ('process_record_user [user]', 'BL target of process_record_kb @0x0800c6e8 (keychron_task.c, 26 B, opsim 1.0; its only BL); body calls process_record_keychron_common @0x0800c720 first, compares keycode with 0x5700 TD(0), 0x39 KC_CAPS_LOCK (+host_keyboard_led_state), OSM range, movw 0x7e40/0x7e41 (QK_USER_0/1 -> register/unregister KC_DOT 0x37 & KC_SLASH 0x38: "./" and "../")', 'verified'),
    0x0800d1c4: ('td_cur_dance [user static]', 'called only from td0_on_dance_finished; reads state->count ([r0,#2]) and state->interrupted ([r0,#5]); returns 1..4', 'verified'),
    0x0800d1ec: ('td0_on_dance_finished [user, tap_dance_actions[0].fn.on_dance_finished]', 'pointer word 0x0800d1ed at flash 0x080179d4 (tap_dance_actions[0], layout verified against ref); calls cur_dance, layer_clear @0x0800dc34, layer_state_is(1|4) @0x0800dc3c, layer_move(1|4) @0x0800dc58, tail-calls oneshot-layer-1 helper', 'verified'),
    0x0800d25c: ('oneshot_layer_changed_user [user]', 'BL target of oneshot_layer_changed_kb @0x0800e4fc (8 B, opsim 1.0); when layer==0 and RAM flag 0x200015e9 set: layer_clear + layer_move(4)', 'verified'),
}

MANUAL_LABELS = {  # dump_addr -> (symbol, ref_sym_for_addr_or_None, note)
    0x0800d27c: ('keycode_at_keymap_location_raw', 'keycode_at_keymap_location_raw', 'VERIFIED: pool word 0x080169b8 (= keymaps[] table, byte-identical to ref table) at 0x0800d2a0; 6x6x18 index math (muls #0x6c, mla #0x12); opsim 1.0 in earlier DP run'),
    0x0800d2a4: ('keycode_at_keymap_location', 'keycode_at_keymap_location', 'VERIFIED: 4-byte b.w thunk to 0x0800d27c'),
    0x0800d2a8: ('keycode_at_encodermap_location_raw', 'keycode_at_encodermap_location_raw', 'VERIFIED: pool word 0x080169a0 (= encoder_map[], 24 B before keymaps) at 0x0800d2c4'),
    0x0800d2c8: ('keycode_at_encodermap_location', 'keycode_at_encodermap_location', 'VERIFIED: 4-byte b.w thunk to 0x0800d2a8'),
    0x0800dc3c: ('layer_state_is [QMK action_layer.c; absent from ref build (unused there)]', None, 'LIKELY: called from user code with a layer index; body: ldrh layer_state @RAM 0x2000162e, clz/asr bit test -> bool (== layer_state_is/layer_state_cmp)'),
    0x0800e3b0: ('clear_oneshot_locked_mods [QMK action_util.c; absent from ref build]', None, 'VERIFIED by body: if (byte @0x200016a5) { byte=0; oneshot_locked_mods_changed_kb(0) @0x0800e38c } == clear_oneshot_locked_mods(); called from user OSM handler 0x0800d0b4'),
    0x080119f8: ('leader_reset_timer [QMK leader.c; absent from ref build]', None, 'VERIFIED by body: leader_time(@0x20002006) = timer_read() @0x08012574; called from process_leader after leader_sequence_add -> LEADER_PER_KEY_TIMING defined in the user config'),
    0x0800f344: ('<data: literal pool of preceding wear_leveling function>', None, 'NOT CODE: nop.w pad + 64-bit FNV-1a offset basis 0xcbf29ce484222325 (wear_leveling.c) + RAM ptr 0x20001704; detector false split'),
    0x0800f550: ('<data: literal pool of preceding wear_leveling function>', None, 'NOT CODE: 64-bit FNV-1a offset basis 0xcbf29ce484222325 + RAM ptr 0x20001704; detector false split'),
    0x08011df0: ('mousekey_task', 'mousekey_task', 'VERIFIED by call position: 7th BL of keyboard_task (dump 0x0800e7b8, opsim 0.95, 16 BLs = ref) where the ref calls mousekey_task; sits between should_mousekey_report_send and _process_tap_dance_action_fn exactly as in the ref link order; 412 B vs ref 372 B. DP had merged it with the two space-cadet functions, which are absent from the dump (process_record_quantum has 14 BLs vs ref 17: no process_space_cadet/process_magic/process_grave_esc)'),
    0x0800883c: ('memcpy [full newlib memcpy-armv7m.S]', 'memcpy', 'VERIFIED by call position: process_tapping (dump 0x0800df94, opsim 0.80) calls it 5x exactly where the ref calls memcpy 5x; 308 B (ref nano stub 28 B)'),
    0x08008798: ('memset [full newlib memset.c -O2]', 'memset', 'VERIFIED by call position: process_tapping calls it 2x where ref calls memset 2x; leader_start tail-calls it with (buf,0,10) as ref leader_start calls memset; 164 B (ref nano 16 B)'),
}

DEFAULT_STUBS = {  # hooks confirmed NOT user-defined: BL target is the weak default stub (size, caller)
    0x0800e768: 'housekeeping_task_user (2 B default stub; BL from housekeeping_task @0x0800e76a)',
    0x0800dc18: 'layer_state_set_user (2 B default; BL from layer_state_set_kb @0x0800dc1a)',
    0x0800dbc4: 'default_layer_state_set_user (2 B default)',
    0x0800e61e: 'eeconfig_init_user (default; BL from eeconfig_init_kb @0x0800e624)',
    0x0800ed16: 'matrix_scan_user (2 B default)',
    0x0801017a: 'rgb_matrix_indicators_user (4 B default)',
    0x0800ccf0: 'dip_switch_update_user (Keychron factory_test.c version, opsim 0.89)',
    0x0800c908: 'raw_hid_receive (keychron_common.c non-VIA stub, opsim 0.92 -> VIA off)',
}


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument('--align', required=True)
    ap.add_argument('--align-json', required=True)
    ap.add_argument('--det', required=True)
    ap.add_argument('--dump', required=True)
    ap.add_argument('--ref-map', required=True)
    ap.add_argument('--ref-bin', required=True)
    ap.add_argument('--text-end', type=lambda x: int(x, 0), required=True)
    ap.add_argument('--rodata-end', type=lambda x: int(x, 0), required=True)
    ap.add_argument('--data-start', type=lambda x: int(x, 0), required=True)
    ap.add_argument('--image-end', type=lambda x: int(x, 0), required=True)
    ap.add_argument('--out', required=True)
    ap.add_argument('--summary', required=True)
    args = ap.parse_args()

    rows = list(csv.DictReader(open(args.align)))
    J = json.load(open(args.align_json))
    det = json.load(open(args.det))
    dump = open(args.dump, 'rb').read()
    A, ran, rsecs, rents = LA.load_ref(args.ref_map, args.ref_bin, libc_front=True)
    ref_by_sym = {}
    for a in A:
        ref_by_sym.setdefault(a.sym, a)
    rstarts = [f.addr for f in sorted(A, key=lambda f: f.addr)]
    rsorted = sorted(A, key=lambda f: f.addr)
    def rcont(addr):
        i = bisect.bisect_right(rstarts, addr) - 1
        return rsorted[i] if i >= 0 and rsorted[i].addr <= addr < rsorted[i].end else None
    ref_callees = {a.sym: [rcont(t).sym for t in a.bl if rcont(t)] for a in A}

    dfuncs = det['funcs']
    dstarts = [f['start'] for f in dfuncs]
    def dcont(addr):
        i = bisect.bisect_right(dstarts, addr) - 1
        return dfuncs[i] if i >= 0 and dfuncs[i]['start'] <= addr < dfuncs[i]['end'] else None
    dcallers = {}
    for f in dfuncs:
        for t in f['bl']:
            g = dcont(t)
            if g:
                dcallers.setdefault(g['start'], []).append(f['start'])

    byaddr = {int(r['dump_addr'], 16): r for r in rows}

    # ---- 0. libc cluster: the reference (nano newlib, function sections at the tail) and the dump
    # (full newlib in plain .text at the front) have different function sets/sizes; DP labels there
    # are only kept when the opcode sequence agrees (opsim >= 0.8) and it is a 1:1 match.
    first_text_star = min((int(r['dump_addr'], 16) for r in rows if r['ref_symbol'] == 'wreless_keyboard_leds'), default=None)
    libc_lo, libc_hi = 0x08008448, (first_text_star or 0x0800a1c0)
    discarded = 0
    for r in rows:
        a = int(r['dump_addr'], 16)
        if libc_lo <= a < libc_hi and r['ref_symbol']:
            ok = r['opcode_sim'] and float(r['opcode_sim']) >= 0.8 and r['notes'].startswith('match')
            if not ok:
                r['notes'] = f"libc cluster: DP label '{r['ref_symbol']}' discarded (opsim {r['opcode_sim'] or 'n/a'}, {r['notes'].split(';')[0]})"
                r['ref_symbol'] = ''; r['ref_addr'] = ''; r['ref_size'] = ''; r['alignment_score'] = ''; r['obj'] = ''
                discarded += 1
    assigned_syms = set()
    for r in rows:
        for sym_ in r['ref_symbol'].split('+'):
            if sym_:
                assigned_syms.add(sym_)
    # ---- 0b. call-position inference: k-th BL of a well matched dump function <-> k-th BL of its ref
    pos_votes = {}
    dfunc_by_start = {f['start']: f for f in dfuncs}
    for r in rows:
        if not r['ref_symbol'] or '+' in r['ref_symbol'] or not r['notes'].startswith('match'):
            continue
        if not r['opcode_sim'] or float(r['opcode_sim']) < 0.8:
            continue
        rf = ref_by_sym.get(r['ref_symbol']); df = dfunc_by_start.get(int(r['dump_addr'], 16))
        if not rf or not df or len(rf.bl) != len(df['bl']) or not rf.bl:
            continue
        for tb, rb in zip(df['bl'], rf.bl):
            g = dcont(tb); rg = rcont(rb)
            if g and rg:
                pos_votes.setdefault(g['start'], {}).setdefault(rg.sym, 0)
                pos_votes[g['start']][rg.sym] += 1
    pos_inferred = 0
    for r in rows:
        if r['ref_symbol']:
            continue
        a = int(r['dump_addr'], 16)
        v = pos_votes.get(a)
        if not v:
            continue
        sym_, n = max(v.items(), key=lambda kv: kv[1]); tot = sum(v.values())
        if n >= 2 and n / tot >= 0.7 and sym_ not in assigned_syms:
            rf = ref_by_sym[sym_]
            r['ref_symbol'] = sym_; r['ref_addr'] = f"0x{rf.addr:08x}"; r['ref_size'] = str(rf.size); r['obj'] = rf.obj
            r['notes'] = f"inferred-by-call-position ({n}/{tot} positional votes = {sym_}); size dump {r['size']} vs ref {rf.size}; " + r['notes']
            assigned_syms.add(sym_); pos_inferred += 1

    # ---- 1. caller-vote inference for unmatched dump functions
    inferred = 0
    for r in rows:
        if r['ref_symbol']:
            continue
        a = int(r['dump_addr'], 16)
        callers = [byaddr.get(c) for c in dcallers.get(a, [])]
        callers = [c for c in callers if c and c['ref_symbol'] and '+' not in c['ref_symbol']]
        if not callers:
            continue
        votes = {}
        for c in callers:
            csym = c['ref_symbol']
            cands = [s for s in ref_callees.get(csym, []) if s not in assigned_syms and s not in VERIFIED_HOOKS.values()]
            for s in set(cands):
                votes[s] = votes.get(s, 0) + 1
        if not votes:
            continue
        best = max(votes.items(), key=lambda kv: kv[1])
        total = len(callers)
        rf0 = ref_by_sym[best[0]]
        plausible = LA.size_sim(rf0.size, int(r['size'])) >= 0.4 or best[1] >= 3
        if best[1] >= 1 and best[1] == total and list(votes.values()).count(best[1]) == 1 and plausible:
            sym = best[0]; rf = ref_by_sym[sym]
            r['ref_symbol'] = sym; r['ref_addr'] = f"0x{rf.addr:08x}"; r['ref_size'] = str(rf.size)
            r['alignment_score'] = ''
            r['notes'] = f"inferred-by-callers ({best[1]}/{total} matched callers call {sym} in ref); size dump {r['size']} vs ref {rf.size}; " + r['notes']
            r['obj'] = rf.obj
            assigned_syms.add(sym); inferred += 1

    # ---- 2. verified hook overrides (keymap object region)
    for a, (name, ev, conf) in VERIFIED_HOOKS.items():
        r = byaddr.get(a)
        if r is None:
            continue
        base = name.split(' ')[0]
        rf = ref_by_sym.get(base) or ref_by_sym.get({'td0_on_dance_finished': 'td0_finished', 'td0_on_reset': 'td0_reset'}.get(base, ''))
        r['ref_symbol'] = name
        r['ref_addr'] = f"0x{rf.addr:08x}" if rf else ''
        r['ref_size'] = str(rf.size) if rf else ''
        r['alignment_score'] = ''
        r['notes'] = f"HOOK[{conf}]: {ev}"
        r['obj'] = 'keymap.c (user)'
    for a, (name, refsym, note) in MANUAL_LABELS.items():
        r = byaddr.get(a)
        if r is None:
            continue
        rf = ref_by_sym.get(refsym) if refsym else None
        r['ref_symbol'] = name; r['ref_addr'] = f"0x{rf.addr:08x}" if rf else ''; r['ref_size'] = str(rf.size) if rf else ''
        r['alignment_score'] = ''; r['notes'] = note
        if rf:
            r['obj'] = rf.obj
    for a, note in DEFAULT_STUBS.items():
        r = byaddr.get(a)
        if r is not None:
            r['notes'] = 'HOOK-DEFAULT: ' + note + '; ' + r['notes']

    # ---- 3. region tags
    for r in rows:
        a = int(r['dump_addr'], 16)
        if first_text_star and 0x08008448 <= a < first_text_star:
            r['region'] = 'libc in *(.text) (newlib without -ffunction-sections)'
        elif 0x0800cdd8 <= a < 0x0800d27c:
            r['region'] = 'keymap.c user code'
        elif 0x0800d27c <= a < 0x0800d2cc:
            r['region'] = 'keymap_introspection'
        else:
            r['region'] = ''
        if not r['ref_symbol']:
            if libc_lo <= a < libc_hi:
                r['notes'] = 'libc (full newlib, unidentified); ' + r['notes']
            elif not r['notes'].startswith('INSERTION'):
                r['notes'] = 'INSERTION (no ref function); ' + r['notes']

    # ---- 4. rodata / data content matching
    ro_hits = LA.rodata_content_match(rents, args.ref_bin, dump, args.text_end, args.rodata_end)
    ro_cov = []
    for e, hits in ro_hits:
        if len(hits) == 1:
            ro_cov.append((hits[0], hits[0] + e['size'], e['name']))
    data_ents = [e for e in rents if e['outsec'] == '.data' and e['name'] != '*fill*' and e['size'] >= 8]
    rbin = open(args.ref_bin, 'rb').read()
    dload = rsecs['data'][2]; dram = rsecs['data'][0]
    data_cov = []
    region = dump[args.data_start - BASE:args.image_end - BASE]
    for e in data_ents:
        off = dload + (e['addr'] - dram) - BASE
        pat = rbin[off:off + e['size']]
        if len(set(pat)) <= 1:
            continue
        pos = region.find(pat)
        if pos != -1 and region.find(pat, pos + 1) == -1:
            data_cov.append((args.data_start + pos, args.data_start + pos + e['size'], e['name']))

    def merge(iv):
        iv = sorted(iv)
        out = []
        for s, e, n in iv:
            if out and s <= out[-1][1]:
                out[-1] = (out[-1][0], max(out[-1][1], e), out[-1][2])
            else:
                out.append((s, e, n))
        return out
    ro_cov = merge(ro_cov); data_cov = merge(data_cov)
    ro_bytes = sum(e - s for s, e, _ in ro_cov); data_bytes = sum(e - s for s, e, _ in data_cov)

    # ---- 5. coverage & unmatched regions
    text_start = 0x08008000
    text_bytes = args.text_end - text_start
    matched_text = sum(int(r['size']) for r in rows if r['ref_symbol'] and '[user' not in r['ref_symbol'] and not r['ref_symbol'].startswith('<data'))
    user_bytes = sum(int(r['size']) for r in rows if '[user' in r['ref_symbol'])
    data_in_text = sum(int(r['size']) for r in rows if r['ref_symbol'].startswith('<data'))
    libc_ident = sum(int(r['size']) for r in rows if r['ref_symbol'] and libc_lo <= int(r['dump_addr'], 16) < libc_hi)
    libc_total = sum(int(r['size']) for r in rows if libc_lo <= int(r['dump_addr'], 16) < libc_hi)
    final_syms = set()
    for r in rows:
        base = r['ref_symbol'].split(' [')[0]
        for sym_ in base.split('+'):
            if sym_:
                final_syms.add(sym_)
    final_syms |= {'td0_reset', 'td0_finished'}   # user tap-dance callbacks are present under their dump names
    absent = [dict(sym=a.sym, addr=f"0x{a.addr:08x}", size=a.size, obj=a.obj) for a in A if a.sym not in final_syms and not LA.is_libc_obj(a.obj)]
    unmatched = [(int(r['dump_addr'], 16), int(r['dump_addr'], 16) + int(r['size']), r) for r in rows if not r['ref_symbol']]
    regions = []
    for s, e, r in sorted(unmatched):
        note = f"entry={r.get('notes', '')}"
        if regions and s == regions[-1][1]:
            regions[-1] = (regions[-1][0], e, regions[-1][2] + 1)
        else:
            regions.append((s, e, 1))
    whole = args.image_end - text_start
    summary = dict(
        text_range=[f"0x{text_start:08x}", f"0x{args.text_end:08x}"], text_bytes=text_bytes,
        matched_text_bytes=matched_text, user_code_bytes=user_bytes,
        text_coverage_pct=round(100.0 * matched_text / text_bytes, 2),
        text_plus_user_pct=round(100.0 * (matched_text + user_bytes) / text_bytes, 2),
        rodata_range=[f"0x{args.text_end:08x}", f"0x{args.rodata_end:08x}"], rodata_bytes=args.rodata_end - args.text_end,
        rodata_content_matched_bytes=ro_bytes, rodata_matched_objects=len(ro_cov),
        data_range=[f"0x{args.data_start:08x}", f"0x{args.image_end:08x}"], data_bytes=args.image_end - args.data_start,
        data_content_matched_bytes=data_bytes,
        whole_region_bytes=whole,
        whole_region_matched_pct=round(100.0 * (matched_text + ro_bytes + data_bytes) / whole, 2),
        whole_region_matched_or_user_pct=round(100.0 * (matched_text + user_bytes + ro_bytes + data_bytes) / whole, 2),
        inferred_by_callers=inferred, inferred_by_call_position=pos_inferred, libc_labels_discarded=discarded,
        libc_cluster=dict(start=f"0x{libc_lo:08x}", end=f"0x{libc_hi:08x}", bytes=libc_total, identified_bytes=libc_ident),
        data_bytes_inside_text=data_in_text,
        ref_functions_absent_from_dump=absent,
        unmatched_text_regions=[dict(start=f"0x{s:08x}", size=e - s, functions=n) for s, e, n in regions],
        n_functions=len(rows), n_matched=sum(1 for r in rows if r['ref_symbol']),
    )
    with open(args.out, 'w', newline='') as fh:
        w = csv.DictWriter(fh, fieldnames=['dump_addr', 'size', 'ref_symbol', 'ref_addr', 'ref_size', 'alignment_score', 'notes', 'region', 'obj', 'opcode_sim'], extrasaction='ignore')
        w.writeheader()
        for r in rows:
            w.writerow(r)
    json.dump(summary, open(args.summary, 'w'), indent=1)
    print(json.dumps(summary, indent=1))
    print("rodata matched objects (first 12):", [(f"0x{s:08x}", e - s, n[:30]) for s, e, n in ro_cov[:12]])
    print("data matched objects:", [(f"0x{s:08x}", e - s, n[:30]) for s, e, n in data_cov[:12]])


if __name__ == '__main__':
    main()
