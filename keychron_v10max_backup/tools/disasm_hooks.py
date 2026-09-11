#!/usr/bin/env python3
"""Emit hooks_final.json and symbolized disassemblies of the CUSTOM hook bodies (disasm/<name>_<addr>.txt).
Symbols come from functions_final.csv (tools/reconcile_maps.py). Literal-pool words are resolved: code pointers -> function
name, rodata -> bytes/string, RAM -> known variable name (QMK statics identified by the callers that use them; user statics
are named by their observed use and marked 'inferred')."""
import csv, json, re, subprocess, struct, os
BK = os.path.dirname(os.path.dirname(os.path.abspath(__file__))) + '/'
OD = '/Users/dexter/Library/Application Support/qmk/bin/arm-none-eabi-objdump'
FLASH = 0x08000000; TEXT_END = 0x08016704; RODATA_END = 0x08017744; IMAGE_END = 0x08017F04
dump = open(BK + 'dump_a.bin', 'rb').read()
names = {}; ranges = []
for r in csv.DictReader(open(BK + 'functions_final.csv')):
    st = int(r['dump_addr'], 16); sz = int(r['size']); names[st] = r['name']; ranges.append((st, st + sz, r['name'], sz, r['status']))
def sym(addr):
    a = addr & ~1
    if a in names: return names[a]
    for st, en, n, _, _ in ranges:
        if st <= a < en: return f"{n}+0x{a-st:X}"
    return None
def word(a): return struct.unpack_from('<I', dump, a - FLASH)[0]
RAM = {0x2000162E: 'layer_state (u16; written by layer_state_set 0x0800DC24)', 0x20001630: 'default_layer_state (u16; written by default_layer_state_set 0x0800DBD0)',
       0x200016A5: 'oneshot_locked_mods (u8; add/del/clear_oneshot_locked_mods)', 0x200016A6: 'oneshot_mods (u8; get/add/del/clear_oneshot_mods)',
       0x20000E7C: 'tap_dance_actions[] (.data)', 0x20002006: 'leader_time (u16)', 0x20002008: 'leading (bool)', 0x20001FFB: 'leader_sequence_size (u8)', 0x20001FFC: 'leader_sequence[5] (u16)',
       0x20000C0C: '_impure_ptr',
       0x200015DC: 'USER static (bss): caps-lock-active flag (u8) - set/cleared in process_record_user from host_keyboard_led_state().caps_lock on KC_CAPS press; lights white in indicators (sibling source: caps_active)',
       0x200015DD: 'USER static (bss): gui_active (u8) - set by handle_oneshots/osm_indicator_helper when oneshot mods & 0x88; indicators -> yellow',
       0x200015DE: 'USER static (bss): shift_active (u8) - set by handle_oneshots when oneshot mods & 0x22; indicators -> white',
       0x200015E0: 'USER static (bss): held_osm[0] (uint16_t*) - find_osm_slot/check_unlock_osm',
       0x200015E4: 'USER static (bss): held_osm[1] (uint16_t*)',
       0x200015E8: 'USER static (bss): move_to_lower (u8) - TD(0) single tap from base arms oneshot layer 1 (_LOWER)',
       0x200015E9: 'USER static (bss): return_to_mouse (u8) - TD(0) single tap on layer 4 (_MOUSE): after the oneshot layer finishes, oneshot_layer_changed_user moves back to layer 4'}
KC = {0x28: 'KC_ENTER', 0x29: 'KC_ESC', 0x2A: 'KC_BSPC', 0x2B: 'KC_TAB', 0x2C: 'KC_SPC', 0x2D: 'KC_MINS', 0x2E: 'KC_EQL', 0x2F: 'KC_LBRC', 0x30: 'KC_RBRC',
      0x31: 'KC_BSLS', 0x33: 'KC_SCLN', 0x34: 'KC_QUOT', 0x35: 'KC_GRV', 0x36: 'KC_COMM', 0x37: 'KC_DOT', 0x38: 'KC_SLSH', 0x39: 'KC_CAPS', 0x4C: 'KC_DEL',
      0x4F: 'KC_RGHT', 0x50: 'KC_LEFT', 0x51: 'KC_DOWN', 0x52: 'KC_UP', 0xE0: 'KC_LCTL', 0xE1: 'KC_LSFT', 0xE2: 'KC_LALT', 0xE3: 'KC_LGUI', 0xE4: 'KC_RCTL',
      0xE5: 'KC_RSFT', 0xE6: 'KC_RALT', 0xE7: 'KC_RGUI', 0x5700: 'TD(0)', 0x7E40: 'QK_USER_0 (SAFE_RANGE+0)', 0x7E41: 'QK_USER_1 (SAFE_RANGE+1)',
      0x52A2: 'OSM(MOD_LSFT)', 0x52A8: 'OSM(MOD_LGUI)', 0x52B2: 'OSM(MOD_RSFT)', 0x52B8: 'OSM(MOD_RGUI)', 0x7C58: 'QK_LEADER', 0x7C00: 'QK_BOOT', 0x5280: 'QK_ONE_SHOT_MOD base'}
for i in range(26): KC[0x04 + i] = 'KC_' + chr(ord('A') + i)
for i in range(9): KC[0x1E + i] = 'KC_' + str(i + 1)
KC[0x27] = 'KC_0'
for i in range(12): KC[0x3A + i] = 'KC_F' + str(i + 1)
def describe(w):
    if (w & ~1) in names or 0x08008000 <= w < TEXT_END:
        s = sym(w); return f"code ptr -> {s}" if s else 'code ptr (unnamed)'
    if TEXT_END <= w < IMAGE_END:
        b = dump[w - FLASH: w - FLASH + 16]
        txt = ''.join(chr(c) if 32 <= c < 127 else '.' for c in b)
        s = sym(w)
        kind = 'rodata' if w < RODATA_END else '.data-init image'
        return f"{kind} @0x{w:08X}" + (f" ({s})" if s else '') + f": {b.hex(' ')} |{txt}|"
    if 0x20000000 <= w < 0x20010000:
        if w in RAM: return f"RAM {RAM[w]}"
        near = [k for k in RAM if 0 < w - k <= 8]
        return f"RAM 0x{w:08X}" + (f" (= {RAM[max(near)]} + {w-max(near)})" if near else ' (unnamed)')
    return f"const 0x{w:08X} ({w})"
BR = re.compile(r'\b(bl|blx|b\.w|b\.n|cbz|cbnz|b(?:eq|ne|cs|cc|hs|lo|mi|pl|vs|vc|hi|ls|ge|lt|gt|le)(?:\.n|\.w)?)\b')
def disasm(start, size, fname):
    end = start + size
    out = subprocess.run([OD, '-D', '-b', 'binary', '-m', 'arm', '-M', 'force-thumb', '--adjust-vma=0x08000000',
                          f'--start-address={start:#x}', f'--stop-address={end:#x}', BK + 'dump_a.bin'], capture_output=True, text=True).stdout
    lines = [l for l in out.splitlines() if re.match(r'\s*[0-9a-f]+:\t', l)]
    pool = set()
    for l in lines:
        m = re.search(r'\[pc, #\d+\]\s+@ \(?(0x[0-9a-f]+)', l)
        if m: pool.add(int(m.group(1), 16))
    res = []; skip_until = 0; last_cmp = None; last_imm = {}
    for l in lines:
        addr = int(l.split(':')[0], 16)
        if addr < skip_until: continue
        if addr in pool:
            w = word(addr); res.append(f" {addr:08x}:\t{w:08x}     \t.word\t0x{w:08X}\t; {describe(w)}"); skip_until = addr + 4; continue
        ann = []
        m = re.search(r'\ttbb\t\[pc, (r\d+)\]', l)
        if m and last_cmp is not None:
            n = last_cmp + 1; base = addr + 4
            for i in range(n):
                off = dump[base + i - FLASH]; ann.append(f"case {i} -> 0x{base+2*off:08X}")
            res.append(l + '\t; ' + '; '.join(ann)); skip_until = base + ((n + 1) // 2) * 2
            res.append(f" {base:08x}:\t{dump[base-FLASH:skip_until-FLASH].hex(' ')}\t.byte\t(tbb table, {n} entries)"); continue
        mb = BR.search(l)
        if mb:
            tg = re.findall(r'0x([0-9a-f]+)', l.split('\t')[-1])
            if tg:
                t = int(tg[-1], 16)
                s = sym(t)
                ann.append(('-> ' + s) if not (start <= t < end) else 'local')
        m = re.search(r'\[pc, #\d+\]\s+@ \(?(0x[0-9a-f]+)', l)
        if m:
            pa = int(m.group(1), 16); w = word(pa); ann.append(f"= 0x{w:08X} {describe(w)}")
        m = re.search(r'\t(movs|movw|mov\.w|cmp|cmp\.w|subs|sub\.w|adds|add\.w)\t(r\d+),\s*(?:r\d+,\s*)?#(\d+)', l)
        if m:
            v = int(m.group(3)); last_cmp = v if m.group(1).startswith('cmp') else last_cmp
            if v in KC and (v >= 0x100 or fname in ('leader_end_user', 'process_record_user', 'osm_press_handler', 'osm_lookup_helper')):
                ann.append(KC[v])
        else:
            if re.search(r'\tcmp', l): last_cmp = None
        res.append(l + ('\t; ' + '; '.join(ann) if ann else ''))
    return res
# ------------------------------------------------------------------ hook table
def find(name):
    for st, en, n, sz, status in ranges:
        if n.split(' [')[0] == name: return st, sz
    return None, None
def rowdict(name, status, callers, note, custom=False, addr=None, size=None, disasm_file=None):
    if addr is None: addr, size = find(name)
    d = dict(hook=name, dump_addr=(f"0x{addr:08X}" if addr else None), size=size, status=status, callers=callers, evidence=note)
    if disasm_file: d['disasm'] = 'disasm/' + disasm_file
    return d
CUSTOM = [  # name in functions_final, file stem
 ('process_record_user', 'process_record_user'), ('td0_on_dance_finished', 'td0_on_dance_finished'), ('td0_on_reset', 'td0_on_reset'),
 ('td_cur_dance', 'td_cur_dance'), ('td_oneshot_layer1_helper', 'td_oneshot_layer1_helper'), ('leader_end_user', 'leader_end_user'),
 ('leader_start_user', 'leader_start_user'), ('keyboard_post_init_user', 'keyboard_post_init_user'),
 ('rgb_matrix_indicators_advanced_user', 'rgb_matrix_indicators_advanced_user'), ('oneshot_mods_changed_user', 'oneshot_mods_changed_user'),
 ('oneshot_locked_mods_changed_user', 'oneshot_locked_mods_changed_user'), ('osm_indicator_helper', 'osm_indicator_helper'),
 ('osm_lookup_helper', 'osm_lookup_helper'), ('osm_press_handler', 'osm_press_handler'), ('oneshot_layer_changed_user', 'oneshot_layer_changed_user'),
 ('keycode_at_keymap_location_raw', 'keycode_at_keymap_location_raw'), ('keycode_at_encodermap_location_raw', 'keycode_at_encodermap_location_raw'),
 ('get_tapping_term', 'get_tapping_term'), ('tap_dance_task', 'tap_dance_task'), ('process_record_kb', 'process_record_kb'),
 ('rgb_matrix_indicators_kb', 'rgb_matrix_indicators_kb'), ('keyboard_post_init_kb', 'keyboard_post_init_kb'), ('dip_switch_update_kb', 'dip_switch_update_kb'),
 ('raw_hid_receive', 'raw_hid_receive')]
os.makedirs(BK + 'disasm', exist_ok=True)
files = {}
for nm, stem in CUSTOM:
    st, sz = find(nm)
    if st is None: print('missing', nm); continue
    fn = f"{stem}_{st:08X}.txt"
    body = disasm(st, sz, stem)
    hdr = [f"; {nm}  dump 0x{st:08X}..0x{st+sz:08X} ({sz} B)  source: dump_a.bin, objdump -D -b binary -m arm -M force-thumb --adjust-vma=0x08000000",
           f"; symbols from functions_final.csv (tools/reconcile_maps.py); '; -> name' = branch target, '; = 0x..' = literal-pool value, '.word' = pool entry", '']
    open(BK + 'disasm/' + fn, 'w').write('\n'.join(hdr + body) + '\n'); files[nm] = fn
# tap_dance_actions init image
TD_FLASH = 0x080179C8
td = [word(TD_FLASH + 4 * i) for i in range(7)]
td_img = dict(flash_addr=f"0x{TD_FLASH:08X}", ram_addr='0x20000E7C', mapping='RAM = flash - __textdata_base__(0x0801774C) + __data_base__(0x20000C00) from crt0 literal triple @0x080080F8; RAM address also the literal at process_tap_dance@0x08012040+0x84',
              entry_size=28, entries=1,
              words=[f"0x{w:08X}" for w in td],
              decoded=dict(state=f"0x{td[0]:08X} (count/interrupted/pressed/... zero-init)", state_pad=f"0x{td[1]:08X}", on_each_tap=f"0x{td[2]:08X} (NULL)" if td[2] == 0 else f"0x{td[2]:08X}",
                           on_dance_finished=f"0x{td[3]:08X} -> {sym(td[3])}", on_reset=f"0x{td[4]:08X} -> {sym(td[4])}",
                           on_each_release=f"0x{td[5]:08X} (NULL)" if td[5] == 0 else f"0x{td[5]:08X}", user_data=f"0x{td[6]:08X} (NULL)" if td[6] == 0 else f"0x{td[6]:08X}"),
              next_object=f"0x{word(TD_FLASH+28):08X} 0x{word(TD_FLASH+32):08X} 0x{word(TD_FLASH+36):08X} (nkro/keyboard report pointers 0x200016A7 0x200016C7 + fn ptr = following .data object; so exactly one tap-dance entry)")
# encoder_map
ENC = 0x080169A0
enc = [struct.unpack_from('<H', dump, ENC - FLASH + 2 * i)[0] for i in range(12)]
ENCN = {0xA9: 'KC_VOLU', 0xAA: 'KC_VOLD', 0x7827: 'RGB_VAI', 0x7828: 'RGB_VAD', 0: 'KC_NO'}
enc_map = {f"layer{i}": f"ENCODER_CCW_CW({ENCN.get(enc[2*i], hex(enc[2*i]))}, {ENCN.get(enc[2*i+1], hex(enc[2*i+1]))})  [0x{enc[2*i]:04X},0x{enc[2*i+1]:04X}]" for i in range(6)}
hooks = [
 rowdict('process_record_user', 'custom', ['process_record_kb@0x0800C6EE bl (keychron_task.c, exact 26 B, both methods)'],
         "192 B incl. literal pool (0x0800D1B8-0x0800D1C4). Calls process_record_keychron_common first; TD(0)=0x5700 press clears flag 0x200015E8; layer_state_is(1)==false clears 0x200015E9; KC_CAPS press -> host_keyboard_led_state().caps_lock -> flag 0x200015DC; pressed OSM(MOD_LSFT/LGUI/RSFT/RGUI) (0x52A2/A8/B2/B8 via sub #0x52A2, mask 0x410041) -> tail-call osm_press_handler; QK_USER_0 -> register/unregister KC_DOT, KC_SLSH ('./'), QK_USER_1 -> KC_DOT then falls into QK_USER_0 ('../'); both return false. A+B agree on address/size/semantics.", disasm_file=files['process_record_user']),
 rowdict('process_record_kb', 'stock-kb', ['process_record_quantum@0x0800D3B6 (fuzzy-anchored, 14 BLs vs ref 17: MAGIC/GRAVE_ESC/SPACE_CADET absent)'],
         "keychron_task.c: bl process_record_user then b.w process_record_keychron 0x0800C6A0. Exact match in both methods.", disasm_file=files['process_record_kb']),
 rowdict('tap_dance_actions[0].fn.on_dance_finished (td0_on_dance_finished)', 'custom', ['pointer 0x0800D1ED in tap_dance_actions init image @0x080179D4', 'process_tap_dance_action_on_dance_finished@0x08011FB8 (exact) calls through the table'],
         "112 B incl. pool (0x0800D24C-0x0800D25C). r0=td_cur_dance(state): 3 (hold) -> layer_clear; layer_move(4); 4 (double tap) -> layer_clear; layer_move(1); 2 (single tap) -> if layer_state_is(4): flag 0x200015E9=1, layer_clear, tail td_oneshot_layer1_helper; elif flag 0x200015E8: layer_clear, layer_move(1), flag=0; elif layer_state_is(1): layer_clear + helper; else flag 0x200015E8=1 + helper.", addr=find('td0_on_dance_finished')[0], size=find('td0_on_dance_finished')[1], disasm_file=files['td0_on_dance_finished']),
 rowdict('tap_dance_actions[0].fn.on_reset (td0_on_reset)', 'custom', ['pointer 0x0800CDD9 in tap_dance_actions init image @0x080179D8'], "2 B: bx lr (empty reset callback).", addr=find('td0_on_reset')[0], size=2, disasm_file=files['td0_on_reset']),
 rowdict('tap_dance_actions[0].fn.on_each_tap / on_each_release / user_data', 'not-found', ['words 0x080179D0 / 0x080179DC / 0x080179E0 are 0'], "NULL in the init image."),
 rowdict('td_cur_dance (static helper)', 'custom', ['td0_on_dance_finished@0x0800D1F0 bl'], "40 B: count==1 -> (!pressed:2 | pressed&&!interrupted:3 | else 1); count==2 -> 4; else 1 (same coding as the common 'cur_dance' example: SINGLE_TAP=2? see disasm for exact constants).", addr=find('td_cur_dance')[0], size=find('td_cur_dance')[1], disasm_file=files['td_cur_dance']),
 rowdict('td_oneshot_layer1_helper (static helper)', 'custom', ['td0_on_dance_finished b.w tail-calls'], "26 B: layer_on(1); set_oneshot_layer(1, ONESHOT_START=3); b.w clear_oneshot_layer_state(ONESHOT_PRESSED=1).", addr=find('td_oneshot_layer1_helper')[0], size=26, disasm_file=files['td_oneshot_layer1_helper']),
 rowdict('leader_end_user', 'custom', ['leader_end@0x08011984 bl (leader_end exact 20 B)'], "354 B: rgb_matrix_set_color_all(0,0,0); then 7 sequence checks (see disasm): F -> LGUI+P, LGUI+K; A,Q -> LCTL+A, Z, Q, ENTER; Y -> LCTL+X, Y, ENTER; LCTL,I -> LCTL+LALT+I; J -> LGUI+P; F -> LGUI+QUOTE (dead: shadowed by the first F check); DEL -> LGUI+UP, LEFT. All via register_code/unregister_code (no register_code16/tap_code16/SEND_STRING in the image).", disasm_file=files['leader_end_user']),
 rowdict('leader_start_user', 'custom', ['leader_start@0x08011948 bl (leader_start exact 60 B)'], "10 B: rgb_matrix_set_color_all(255,0,255).", disasm_file=files['leader_start_user']),
 rowdict('housekeeping_task_user', 'stock-default', ['housekeeping_task@0x0800E770 bl'], "2 B 'bx lr' weak default at 0x0800E768 (keyboard.o position); not user-defined."),
 rowdict('housekeeping_task_kb', 'stock-kb', ['housekeeping_task@0x0800E76C bl'], "4 B 'b.w keychron_task 0x0800C6D4' (keychron_task.c)."),
 rowdict('matrix_scan_user', 'stock-default', ['matrix_scan_kb@0x0800ED1A bl'], "2 B 'bx lr' default at 0x0800ED16; matrix_scan_kb 0x0800ED18 8 B stock."),
 rowdict('layer_state_set_user', 'stock-default', ['layer_state_set_kb@0x0800DC1C bl'], "2 B 'bx lr' default at 0x0800DC18; layer_state_set_kb 0x0800DC1A (8 B: push; bl user; pop) stock; layer_state_set 0x0800DC24 exact."),
 rowdict('layer_state_set_kb', 'stock-kb', ['layer_state_set@0x0800DC24 (bl)', 'magic@0x0800ECCC b.w'], "8 B stock wrapper."),
 rowdict('default_layer_state_set_user', 'stock-default', ['default_layer_state_set_kb@0x0800DBC8 bl'], "2 B 'bx lr' at 0x0800DBC4; default_layer_state_set_kb 0x0800DBC6 8 B stock; default_layer_state_set 0x0800DBD0 writes 0x20001630."),
 rowdict('rgb_matrix_indicators_user', 'stock-default', ['rgb_matrix_indicators_kb@0x0800C704 bl'], "4 B 'movs r0,#1; bx lr' at 0x0801017A (rgb_matrix.o position, after rgb_matrix_none_indicators); A ambiguous set resolved by B/caller."),
 rowdict('rgb_matrix_indicators_kb', 'stock-kb', ['rgb_matrix_task@0x08011120 bl'], "18 B keychron_task.c: if (!rgb_matrix_indicators_user()) return false; rgb_matrix_indicators_keychron(); B opsim 0.62 + gcc13 agree; A left unmatched (compiler variant).", disasm_file=files['rgb_matrix_indicators_kb']),
 rowdict('rgb_matrix_indicators_advanced_user', 'custom', ['rgb_matrix_indicators_advanced_kb@0x08010C4E bl (8 B stock kb wrapper, itself bl from rgb_matrix_indicators_advanced@0x08010C66)'],
         "156 B incl. pool (0x0800CFFC-0x0800D010). For i in led_min..led_max: layer = biton16(layer_state|default_layer_state); tbb switch layer 1..5 -> rgb_matrix_set_color(i, rgb): L1 (0,255,0) L2 (0,0,255) L3 (255,128,0) L4 (0,128,128) L5 (255,0,0); then if flag 0x200015DD -> (255,255,0); else if flag 0x200015DE || flag 0x200015DC -> (255,255,255). Returns false.", disasm_file=files['rgb_matrix_indicators_advanced_user']),
 rowdict('rgb_matrix_indicators_advanced_kb', 'stock-kb', ['rgb_matrix_indicators_advanced@0x08010C66 bl'], "8 B: push; bl advanced_user; pop (exact-ambiguous resolved by caller in A, opsim 1.0 in B)."),
 rowdict('oneshot_mods_changed_user', 'custom', ['oneshot_mods_changed_kb@0x0800E3E6 bl'], "4 B 'b.w osm_indicator_helper 0x0800D010'.", disasm_file=files['oneshot_mods_changed_user']),
 rowdict('oneshot_locked_mods_changed_user', 'custom', ['oneshot_locked_mods_changed_kb@0x0800E38E bl'], "4 B 'b.w osm_indicator_helper 0x0800D010'.", disasm_file=files['oneshot_locked_mods_changed_user']),
 rowdict('osm_indicator_helper (static helper)', 'custom', ['b.w from both oneshot_*_mods_changed_user'], "120 B incl. pool; see disasm for the shift(0x22)/GUI(0x88) -> colour/flag logic.", addr=find('osm_indicator_helper')[0], size=120, disasm_file=files['osm_indicator_helper']),
 rowdict('oneshot_layer_changed_user', 'custom', ['oneshot_layer_changed_kb@0x0800E4FE bl'], "32 B: if (layer==0 && flag 0x200015E9) { layer_clear(); layer_move(4); flag=0; }", disasm_file=files['oneshot_layer_changed_user']),
 rowdict('osm_press_handler / osm_lookup_helper (static helpers)', 'custom', ['process_record_user@0x0800D15A b.w tail-call'], "80 B + 36 B; see disasm.", addr=find('osm_press_handler')[0], size=80, disasm_file=files['osm_press_handler']),
 rowdict('dip_switch_update_kb', 'stock-kb', ['dip_switch_read@0x0801189C+0x20 bl'], "32 B v10_max.c (opsim 1.0, callgraph 3/3 in B): default_layer_set(1UL<<(active?2:0)); dip_switch_update_user(...). A left it unmatched (compiler variant).", disasm_file=files['dip_switch_update_kb']),
 rowdict('dip_switch_update_user', 'stock-kb', ['dip_switch_update_kb@0x0800CD2C bl'], "40 B Keychron factory_test.c version at 0x0800CCF0 (opsim 0.89), calls factory_test_send; not the user's."),
 rowdict('encoder_update_user / encoder_update_kb', 'not-found', [], "Not in the image: ENCODER_MAP_ENABLE path (keycode_at_encodermap_location_raw + encoder_read 0x080116D0 / encoder_init 0x08011668 match the ref)."),
 rowdict('keycode_at_encodermap_location_raw', 'custom', ['keycode_at_encodermap_location@0x0800D2C8 b.w thunk (called from encoder code)'], f"32 B; literal 0x080169A0 = encoder_map[6][1][2] (24 B): " + '; '.join(f"{k}: {v}" for k, v in enc_map.items()), disasm_file=files['keycode_at_encodermap_location_raw']),
 rowdict('raw_hid_receive', 'stock-kb', ['raw_hid_task@0x08012C1C+0x1C bl'], "14 B (+2 pad) keychron_common.c #else branch (VIA off): b.w via_command_kb 0x0800C874 (148 B exact). A exact vs default/feat refs only; B opsim 0.92.", disasm_file=files['raw_hid_receive']),
 rowdict('keyboard_post_init_user', 'custom', ['keyboard_post_init_kb@0x0800CD76 b.w tail-call (last insn of the 80-B v10_max.c hook)'], "20 B: default_layer_set(0) then b.w rgb_matrix_mode(16); mode 16 = TYPING_HEATMAP (rgb_task_render@0x08010A8E 'cmp r6,#22; tbb' case 16 -> bl TYPING_HEATMAP 0x08010920; 22 enabled effects = info.json animations).", disasm_file=files['keyboard_post_init_user']),
 rowdict('keyboard_post_init_kb', 'stock-kb', ['keyboard_init@0x0800E79E bl (keyboard_init exact 28 B)'], "80 B v10_max.c: _pal_lld_setgroupmode x2, lkbt51_init, wireless_init, timer_read32, encoder_cb_init, then b.w keyboard_post_init_user (B opsim 0.91; A fuzzy-anchored).", disasm_file=files['keyboard_post_init_kb']),
 rowdict('eeconfig_init_user', 'stock-default', ['eeconfig_init_kb@0x0800E62C bl'], "6 B default at 0x0800E61E: b.w eeconfig_update_user 0x0800E616 (exact)."),
 rowdict('eeconfig_init_kb', 'stock-kb', ['eeconfig_init_quantum@0x0800E634 bl'], "14 B (+2) exact: eeconfig_update_kb 0x0800E60E + eeconfig_init_user."),
 rowdict('get_tapping_term', 'stock-default', ['tap_dance_task@0x080120EC bl (keyrecord_t built on stack)', 'waiting_buffer_scan_tap@0x0800DF52 bl', 'process_tapping@0x0800E016 bl', 'process_tapping@0x0800E192 bl'],
         "4 B 'movs r0,#175; bx lr' at 0x0800DEFC (action_tapping.o position) = the weak default returning TAPPING_TERM=175, compiled because TAPPING_TERM_PER_KEY is defined (the ref without it inlines 'cmp #140'). Not overridden by the user. Method B's 'PER_KEY off' was wrong (conflict resolved by the four call sites).", disasm_file=files['get_tapping_term']),
 rowdict('process_tapping (variant)', 'stock', ['action_tapping_process@0x0800E21C bl'], "648 B at 0x0800DF94 (ref 584 B, opsim 0.80): two bl get_tapping_term + 'cmp r7,#174' (QUICK_TAP_TERM = TAPPING_TERM = 175, no QUICK_TAP_TERM_PER_KEY); no PERMISSIVE_HOLD/HOLD_ON_OTHER_KEY_PRESS/RETRO_TAPPING getters (get_permissive_hold/get_hold_on_other_key_press/get_retro_tapping absent in both methods).", addr=0x0800DF94, size=648),
 rowdict('tap_dance_task (variant)', 'stock', ['quantum_task@0x0800E7A6 bl'], "80 B at 0x080120D0 (ref 60 B) - the extra 20 B are the keyrecord_t stack frame + bl get_tapping_term.", addr=0x080120D0, size=80, disasm_file=files['tap_dance_task']),
 rowdict('keycode_at_keymap_location_raw', 'custom', ['keycode_at_keymap_location@0x0800D2A4 b.w thunk'], "40 B: 6 layers x 6 rows x 18 cols (cmp #5/#5/#17, muls #0x6C), literal 0x080169B8 = keymaps[] (1296 B, byte-identical to refs/ref_feat_keymap).", disasm_file=files['keycode_at_keymap_location_raw']),
 rowdict('keymap_layer_count_raw / keymap_layer_count', 'not-found', [], "Absent from the dump and from every reference ELF (gc-sections removes it: nothing calls it without VIA/dynamic keymaps); keymap_introspection object is exactly 80 B (4 functions 0x0800D27C-0x0800D2CC)."),
 rowdict('pre_process_record_user / post_process_record_user', 'stock-default', ['pre_process_record_kb@0x0800D2D2 bl', 'post_process_record_kb@0x0800D2E0 bl'], "4 B 'movs r0,#1; bx lr' at 0x0800D2CC and 2 B 'bx lr' at 0x0800D2DC (quantum.o position, exact-ambiguous in A, opsim 1.0 in B)."),
 rowdict('shutdown_user / suspend_power_down_user / suspend_wakeup_init_user / led_update_user / keyboard_pre_init_user', 'stock-default', ['shutdown_kb@0x0800D374', 'suspend_power_down_kb@0x0801245A', 'suspend_wakeup_init_kb@0x08012464', 'led_update_kb@0x0800B91C', 'keyboard_pre_init_kb@0x0800E734'], "all tiny weak defaults at their stock positions (A exact-ambiguous resolved by caller, B match)."),
]
res = dict(generated_by='tools/disasm_hooks.py', dump='dump_a.bin', tap_dance_actions_init_image=td_img, encoder_map=dict(flash_addr=f"0x{ENC:08X}", layers=enc_map), hooks=hooks,
           user_statics_bss=dict((f"0x{k:08X}", v) for k, v in RAM.items() if 0x200015DC <= k <= 0x200015E9),
           config_inferences={
             'TAPPING_TERM': '175 (get_tapping_term default body movs r0,#175; process_tapping cmp r7,#174 for QUICK_TAP_TERM)',
             'TAPPING_TERM_PER_KEY': 'defined (four bl get_tapping_term call sites; ref without it inlines cmp #TAPPING_TERM)',
             'ONESHOT_TAP_TOGGLE': '2 (process_action@0x0800D832 cmp.w r8,#2 -> register_mods; del_oneshot_mods; add_oneshot_locked_mods = action.c:462-466)',
             'ONESHOT_TIMEOUT': 'not defined (no has_oneshot_*_timed_out bodies; add_oneshot_mods 24 B has no timer_read; set_oneshot_layer 48 B)',
             'LEADER_PER_KEY_TIMING': 'defined (leader_reset_timer 0x080119F8 present and called from process_leader)',
             'LEADER_TIMEOUT': '525 (leader_sequence_timed_out@0x080119C0 movw #0x20D) - from Method B, not re-verified here',
             'VIA_ENABLE': 'no (raw_hid_receive = keychron_common.c #else stub; no via_/dynamic_keymap_ functions)',
             'ENCODER_MAP_ENABLE': 'yes (encoder_map @0x080169A0, keycode_at_encodermap_location_raw present, no encoder_update_*)',
             'TAP_DANCE_ENABLE / LEADER_ENABLE / MOUSEKEY_ENABLE': 'yes / yes / yes (process_tap_dance exact; leader_* exact; mousekey_task 412 B @0x08011DF0)',
             'MAGIC_ENABLE / GRAVE_ESC_ENABLE / SPACE_CADET_ENABLE': 'no (process_magic/process_grave_esc/process_space_cadet absent; process_record_quantum has 14 BLs vs ref 17) - Method B, consistent with A leaving no unmatched code of those sizes',
             'RGB default mode': 'rgb_matrix_mode(16) in keyboard_post_init_user = TYPING_HEATMAP (dump tbb case table)'})
json.dump(res, open(BK + 'hooks_final.json', 'w'), indent=1)
print('hooks:', len(hooks), 'disasm files:', len(files)); print(json.dumps(td_img['decoded'], indent=1)); print(json.dumps(enc_map, indent=1))
