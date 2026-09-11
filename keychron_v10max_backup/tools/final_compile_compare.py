#!/usr/bin/env python3
"""Compile-and-compare check of the FINAL reconstructed keymap (RECONSTRUCTION_SPEC.md) against dump_a.bin.

Usage:
  uv run --with pyelftools python3 tools/final_compile_compare.py <rebuild.elf> [--verbose]

The rebuild is produced OUTSIDE the fork tree with the QMK userspace overlay mechanism, e.g.
  X=~/.local/share/xpack-arm-none-eabi-gcc-13.2.1/xpack-arm-none-eabi-gcc-13.2.1-1.1/bin
  cd /Users/dexter/code/qmk-keychron-ref && PATH="$X:$PATH" \
    make keychron/v10_max/ansi_encoder:dexter:elf QMK_USERSPACE=<overlay> BUILD_DIR=<scratch>/build \
         TOOLCHAIN=$X/arm-none-eabi- -j8
where <overlay>/keyboards/keychron/v10_max/ansi_encoder/keymaps/dexter/ holds keymap.c, config.h, rules.mk
exactly as written in RECONSTRUCTION_SPEC.md.

What is compared (dump address/size from functions_final.csv, rebuild address/size from the ELF symtab):
  1. every function of the user keymap TU: masked byte identity (BL/B.W immediates and literal-pool
     address words are masked, everything else must be equal) -- this proves control flow, immediates,
     register allocation and branch offsets are the same;
  2. keymaps[] (1296 B) and encoder_map[] (24 B): raw byte identity;
  3. tap_dance_actions[] init image: same shape (NULL / pointer positions);
  4. the .bss order of the six user statics (offsets relative to caps_active);
  5. the config-bearing core functions (tapping, one-shot, leader, mousekey, RGB default, feature chain).
Exit status 0 = everything identical, 1 = at least one difference (details printed).
"""
import sys, csv, struct
from elftools.elf.elffile import ELFFile

K = '/Users/dexter/code/qmk-keychron/keychron_v10max_backup'
BASE = 0x08000000
verbose = '--verbose' in sys.argv
args = [a for a in sys.argv[1:] if not a.startswith('--')]
if not args:
    print(__doc__); sys.exit(2)
elf_path = args[0]

dump = open(K + '/dump_a.bin', 'rb').read()
elf = ELFFile(open(elf_path, 'rb'))
segs = []
for seg in elf.iter_segments():
    if seg['p_type'] == 'PT_LOAD' and seg['p_filesz'] > 0:
        segs.append((seg['p_paddr'], seg['p_vaddr'], seg['p_filesz'], seg.data()))

def rbytes(addr, n):
    """Bytes of the rebuild at flash address (LMA) or RAM address (VMA of an initialised .data object)."""
    for pa, va, sz, d in segs:
        if pa <= addr < pa + sz:
            return d[addr - pa:addr - pa + n]
    for pa, va, sz, d in segs:
        if va <= addr < va + sz:
            return d[addr - va:addr - va + n]
    return None

funcs, objs = {}, {}
for s in elf.get_section_by_name('.symtab').iter_symbols():
    t = s['st_info']['type']
    if t == 'STT_FUNC' and s['st_size'] > 0:
        funcs[s.name] = (s['st_value'] & ~1, s['st_size'])
    elif t == 'STT_OBJECT':
        objs[s.name] = (s['st_value'], s['st_size'])

def mask(b):
    """Replace BL / B.W 32-bit encodings by a tag; keep everything else as halfwords."""
    b = bytearray(b); i = 0; out = []
    while i + 1 < len(b):
        hw = b[i] | (b[i + 1] << 8)
        if (hw & 0xF800) == 0xF000 and i + 3 < len(b):
            hw2 = b[i + 2] | (b[i + 3] << 8)
            if (hw2 & 0xD000) in (0xD000, 0x9000):
                out.append('BL' if hw2 & 0x4000 else 'B.W'); i += 4; continue
        out.append(hw); i += 2
    return out

def lit_mask(words):
    """Mask literal-pool words that are flash/RAM/peripheral addresses (high halfword tells)."""
    res = []; i = 0
    while i < len(words):
        if i + 1 < len(words) and isinstance(words[i], int) and isinstance(words[i + 1], int) \
                and words[i + 1] in (0x2000, 0x0801, 0x0800, 0x4002, 0x4001, 0x4000, 0xe000):
            res.append('LIT'); i += 2; continue
        res.append(words[i]); i += 1
    return res

def norm(b):
    return tuple(lit_mask(mask(b)))

fail = 0
def report(name, same, extra=''):
    global fail
    if not same: fail += 1
    print(f"  {'OK  ' if same else 'DIFF'} {name}{extra}")

def first_diff(dm, rm):
    for k, (a, b) in enumerate(zip(dm, rm)):
        if a != b:
            return k, a, b
    return len(min(dm, rm, key=len)), None, None

def cmp_func(name, dump_addr, dump_size, rebuild_name=None):
    rn = rebuild_name or name
    if rn not in funcs:
        report(name, False, '  (not in rebuild)'); return
    ra, rs = funcs[rn]
    n = min(rs, dump_size)             # dump sizes from functions_final.csv include pad/pool; ELF sizes exclude the pool
    db = dump[dump_addr - BASE:dump_addr - BASE + n]
    rb = rbytes(ra, n)
    dm, rm = norm(db), norm(rb)
    same = dm == rm
    extra = f"  dump {dump_addr:#010x}/{dump_size} B, rebuild {ra:#010x}/{rs} B, compared {n} B"
    if not same:
        k, a, b = first_diff(dm, rm)
        extra += f"  first diff at halfword {k} (dump {dump_addr + 2 * k:#x}): dump={a if isinstance(a, str) else hex(a)} rebuild={b if isinstance(b, str) else hex(b)}"
    report(name, same, extra)

print('== 1. user keymap TU functions (masked identity) ==')
user_funcs = [
    ('layr_dn_reset',                      0x0800CDD8,   2),
    ('layer_oneshot_Lower',                0x0800CDDA,  26),
    ('leader_start_user',                  0x0800CDF4,  10),
    ('leader_end_user',                    0x0800CDFE, 354),
    ('keyboard_post_init_user',            0x0800CF60,  20),
    ('rgb_matrix_indicators_advanced_user',0x0800CF74, 156),
    ('handle_oneshots',                    0x0800D010, 120),
    ('oneshot_mods_changed_user',          0x0800D088,   4),
    ('oneshot_locked_mods_changed_user',   0x0800D08C,   4),
    ('find_osm_slot',                      0x0800D090,  36),
    ('check_unlock_osm',                   0x0800D0B4,  80),
    ('process_record_user',                0x0800D104, 192),
    ('cur_dance',                          0x0800D1C4,  40),
    ('layr_dn_finished',                   0x0800D1EC, 112),
    ('oneshot_layer_changed_user',         0x0800D25C,  32),
    ('keycode_at_keymap_location_raw',     0x0800D27C,  40),
    ('keycode_at_encodermap_location_raw', 0x0800D2A8,  32),
]
for n, a, s in user_funcs:
    cmp_func(n, a, s)

print('\n== 2. tables (raw byte identity) ==')
def cmp_obj(name, dump_addr, size):
    if name not in objs:
        report(name, False, '  (not in rebuild)'); return
    ra, rs = objs[name]
    rb = rbytes(ra, rs); db = dump[dump_addr - BASE:dump_addr - BASE + size]
    same = (rs == size) and (rb == db)
    report(name, same, f"  dump {dump_addr:#010x}/{size} B, rebuild {ra:#010x}/{rs} B")
cmp_obj('keymaps', 0x080169B8, 1296)
cmp_obj('encoder_map', 0x080169A0, 24)

print('\n== 3. tap_dance_actions[] init image shape ==')
if 'tap_dance_actions' in objs:
    ra, rs = objs['tap_dance_actions']
    rb = rbytes(ra, rs)
    db = dump[0x080179C8 - BASE:0x080179C8 - BASE + 28]
    dw = struct.unpack('<7I', db); rw = struct.unpack('<7I', rb[:28]) if rs >= 28 else None
    shape_ok = rs == 28 and rw is not None and all((a == 0) == (b == 0) for a, b in zip(dw, rw))
    ptr_ok = shape_ok and rw[3] == funcs['layr_dn_finished'][0] | 1 and rw[4] == funcs['layr_dn_reset'][0] | 1
    report('tap_dance_actions', shape_ok and ptr_ok,
           f"  dump words {[hex(w) for w in dw]}  rebuild words {[hex(w) for w in rw] if rw else None} (size {rs})")
else:
    report('tap_dance_actions', False, '  (not in rebuild)')

print('\n== 4. .bss layout of the user statics (offsets relative to caps_active) ==')
want = {'caps_active': 0, 'gui_active': 1, 'shift_active': 2, 'held_osm': 4, 'move_to_lower': 12, 'return_to_mouse': 13}
if all(n in objs for n in want):
    base = objs['caps_active'][0]
    got = {n: objs[n][0] - base for n in want}
    report('static order', got == want, f"  dump offsets {want}  rebuild offsets {got}  (caps_active @ {base:#010x})")
else:
    missing = [n for n in want if n not in objs]
    report('static order', False, f"  missing symbols {missing} (optimised away?)")

print('\n== 5. config-bearing core functions (masked identity) ==')
core = [
    ('get_tapping_term', 0x0800DEFC, 4), ('waiting_buffer_scan_tap', 0x0800DF00, 148), ('process_tapping', 0x0800DF94, 648),
    ('action_tapping_process', 0x0800E21C, 196), ('process_action', 0x0800D698, 1052), ('action_exec', 0x0800D50C, 64),
    ('set_oneshot_layer', 0x0800E504, 48), ('add_oneshot_mods', 0x0800E3EC, 28), ('del_oneshot_mods', 0x0800E408, 28),
    ('clear_oneshot_mods', 0x0800E424, 24), ('reset_oneshot_layer', 0x0800E534, 20), ('get_mods_for_report', 0x0800E43C, 48),
    ('leader_sequence_timed_out', 0x080119C0, 28), ('process_leader', 0x080118F4, 74), ('leader_reset_timer', 0x080119F8, 16),
    ('leader_sequence_add', 0x0801199C, 36), ('leader_start', 0x08011940, 60), ('leader_end', 0x0801197C, 20),
    ('move_unit', 0x08011A8C, 136), ('wheel_unit', 0x08011B14, 112), ('mousekey_on', 0x08011B84, 196), ('mousekey_task', 0x08011DF0, 412),
    ('eeconfig_update_rgb_matrix_default', 0x0800FE14, 44), ('process_record_quantum', 0x0800D3B6, 166), ('quantum_task', 0x0800E7A4, 20),
    ('action_for_keycode', 0x0800E8B0, 436), ('debounce', 0x0800EF30, 304), ('bootmagic_lite', 0x0800EC98, 42), ('tap_dance_task', 0x080120D0, 80),
    ('process_tap_dance', 0x08012040, 144), ('eeconfig_init_quantum', 0x0800E634, 144), ('rgb_matrix_mode_eeprom_helper', 0x08010D04, 60),
    ('process_rgb_matrix', 0x08010060, 268), ('keyboard_init', 0x0800E788, 28), ('raw_hid_receive', 0x0800C908, 14),
    ('process_record_kb', 0x0800C6E8, 26), ('keyboard_post_init_kb', 0x0800CD38, 80), ('rgb_matrix_indicators_kb', 0x0800C702, 18),
    ('send_nkro_report', 0x0800E4A4, 56), ('rgb_matrix_task', 0x08011058, 216), ('rgb_matrix_indicators_advanced', 0x08010C54, 28),
]
for n, a, s in core:
    cmp_func(n, a, s)

print('\n== 6. whole-image sweep: rebuild functions without a masked-identical dump function ==')
dfuncs = []
with open(K + '/functions_final.csv') as f:
    for r in csv.DictReader(f):
        dfuncs.append((int(r['dump_addr'], 16), int(r['size']), r['name']))
dhash = {}
for da, ds, dn in dfuncs:
    body = dump[da - BASE:da - BASE + ds]
    for trim in (0, 2, 4):          # functions_final.csv sizes may include 2/4 B of pad or pool
        if ds - trim > 0:
            dhash.setdefault(norm(body[:ds - trim]), []).append((da, ds, dn))
unm = []
for n, (ra, rs) in funcs.items():
    b = rbytes(ra, rs)
    if b is None: continue
    if norm(b) not in dhash:
        unm.append((ra, rs, n))
unm.sort()
print(f"  rebuild functions: {len(funcs)}; without masked-identical dump match: {len(unm)}")
for ra, rs, n in unm:
    print(f"    {ra:#010x} {rs:5d} {n}")

print('\nRESULT:', 'ALL IDENTICAL' if fail == 0 else f'{fail} DIFFERENCE(S)')
sys.exit(0 if fail == 0 else 1)
