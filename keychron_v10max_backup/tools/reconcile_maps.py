#!/usr/bin/env python3
"""Reconcile the two independent function maps of dump_a.bin into functions_final.csv.

Inputs (all in keychron_v10max_backup/):
  functions_matched.csv      Method A  (masked signature matcher, tools/funcmatch.py)
  functions_linkorder.csv    Method B  (link-order alignment, tools/linkorder_align.py)
  dump_symbols_gcc13.json    Method C  (tools/match_ref_funcs.py vs refs/ref1011_feat_gcc13.elf, xPack GCC 13.2.1) - tie-breaker only
  unmatched_regions.csv      Method A caller votes for otherwise unmatched code
  libc_members_placed.json   Ubuntu noble libnewlib 4.4.0 libc_nano.a members placed in the dump (tools/libc_place.py)
Rules:
  * B's function boundaries are the skeleton (its detector was calibrated at 99.6% start recall); A's boundaries win only where
    a byte-level inspection showed B merged/split functions (see OVERRIDES, each entry cites the instructions).
  * A row whose ref_symbol is an 'a|b|c' ambiguous set counts as agreeing with B when B's pick is a member of the set.
  * Every genuine disagreement was resolved by disassembling the dump and the reference ELF; the resolution and evidence are in the
    'evidence' column and in ANALYSIS_functions.md.
Output columns: dump_addr,size,name,status,confidence,evidence
  status: agreed | A-only | B-only | conflict (resolved; name is the winner) | lib-only (Ubuntu newlib member symbol) |
          data (rodata/.data object, from A) | padding | unmatched
"""
import csv, json, re, collections, sys, os
BK = os.path.dirname(os.path.dirname(os.path.abspath(__file__))) + '/'
dump = open(BK + 'dump_a.bin', 'rb').read()
FLASH = 0x08000000
TEXT_END = 0x08016704; RODATA_END = 0x08017744; IMAGE_END = 0x08017F04

# ---------------------------------------------------------------- load
A = []
for r in csv.DictReader(open(BK + 'functions_matched.csv')):
    A.append(dict(start=int(r['dump_addr'], 16), size=int(r['size']), name=r['ref_symbol'].strip(),
                  mtype=r['match_type'], score=float(r['score'] or 0), notes=r['notes'], elfs=r['ref_elf']))
Aby = {a['start']: a for a in A}
B = []
for r in csv.DictReader(open(BK + 'functions_linkorder.csv')):
    nm = r['ref_symbol']; base = nm.split(' [')[0].strip()
    if base.startswith('<data'): base = ''
    B.append(dict(start=int(r['dump_addr'], 16), size=int(r['size']), name=base, rawname=nm, notes=r['notes'],
                  obj=r['obj'], opsim=float(r['opcode_sim']) if r['opcode_sim'] else None))
B.sort(key=lambda x: x['start'])
C = {}
for name, s in json.load(open(BK + 'dump_symbols_gcc13.json'))['symbols'].items():
    if s['candidates'] == 1:
        C.setdefault(int(s['dump_addr'], 16), []).append(name)
AV = {}  # A caller votes from unmatched_regions.csv
for r in csv.DictReader(open(BK + 'unmatched_regions.csv')):
    for tok in r['suggested_names'].split():
        if '=' in tok:
            a, n = tok.split('=', 1); AV.setdefault(int(a, 16), []).append(n)
LIB = json.load(open(BK + 'libc_members_placed.json'))

# ---------------------------------------------------------------- libc symbols (Ubuntu newlib 4.4.0 libc_nano.a)
# choose one member per address range (aliases rand/random, fprintf/dprintf/fwprintf, fflush/fflush_u, signalr vs generic syscall wrappers)
PREFERRED = {'libc_a-rand.o', 'libc_a-fprintf.o', 'libc_a-fflush.o', 'libc_a-signalr.o'}
REJECT = {'libc_a-fscanf.o', 'libc_a-fwscanf.o', 'libc_a-random.o', 'libc_a-dprintf.o', 'libc_a-fwprintf.o', 'libc_a-fflush_u.o',
          'libc_a-fstatr.o', 'libc_a-getentropyr.o', 'libc_a-gettimeofdayr.o', 'libc_a-linkr.o', 'libc_a-mkdirr.o', 'libc_a-statr.o'}
libsyms = []  # (addr,size,name,member,eq)
for m in LIB:
    if m['member'] in REJECT: continue
    syms = m['syms']
    if not syms and m['member'] == 'libc_a-memchr.o':
        syms = [[0, 160, 'memchr']]
    for off, sz, name in syms:
        libsyms.append((FLASH + m['start'] + off, sz, name, m['member'], m['eq']))
# extra members verified by direct byte comparison (see ANALYSIS_functions.md, libc section)
libsyms.append((0x0800A180, 16, '_malloc_usable_size_r', 'libc_a-msizer.o', 1.0))
libsyms.append((0x08009BC4, 100, '_realloc_r', 'libc_a-reallocr.o', 0.85))
libsyms.append((0x08009FD0, 4, '__malloc_lock', 'libc_a-mlock.o', 1.0))
libsyms.append((0x08009FD4, 4, '__malloc_unlock', 'libc_a-mlock.o', 1.0))
# merge aliases at identical address (fiprintf/fprintf, _vfiprintf_r/_vfprintf_r ...)
libd = collections.OrderedDict()
for addr, sz, name, mem, eq in sorted(libsyms):
    if addr in libd:
        libd[addr]['name'] += '/' + name
    else:
        libd[addr] = dict(start=addr, size=sz, name=name, member=mem, eq=eq)
LIBC_LO, LIBC_HI = 0x08008448, 0x0800A1C0

# ---------------------------------------------------------------- manual overrides (byte-level inspection)
# start: (name, size, status, confidence, evidence)
OV = {
 0x08008000: ('_crt0_entry', 284, 'agreed', 'high', "A splits the same 284 B into crt0_v7m.S local labels (msloop@0x08008074, psloop@0x08008082, dloop@0x08008092, bloop@0x080080A6, initloop@0x080080BC, endinitloop@0x080080C8, finiloop@0x080080D0); B one section; instruction-identical to ref (opsim 1.00). Literal triple @0x080080F8: __textdata_base__ 0x0801774C, __data_base__ 0x20000C00, __data_end__ 0x200013B8."),
 0x0800811C: ('Reset_Handler', 2, 'conflict', 'high', "A Reset_Handler (exact) vs B 'INSERTION'. Dump 0x0800811C = 'e770 b.n 0x08008000 (_crt0_entry)' == ref vectors.S Reset_Handler; vector slot 1 = 0x0800811D. Resolved: A."),
 0x0800811E: ('BusFault_Handler (weak default ISR aliases: NMI/HardFault/MemManage/BusFault/UsageFault/DebugMon/PendSV/... -> bl _unhandled_exception)', 4, 'conflict', 'high', "A BusFault_Handler (4 B) vs B 'Reset_Handler split1'. Dump 'f000 f800 bl 0x08008122' == ref 0x0800811E (W BusFault_Handler, W NMI_Handler ...); vector slots 2..15 except SVC (0x2C) hold 0x0800811F. Resolved: A."),
 0x08008122: ('_unhandled_exception', 2, 'conflict', 'high', "A (part of BusFault body) vs B 'Reset_Handler split2'. Dump 'e7fe b.n self' == ref _unhandled_exception 0x08008122. Resolved: A."),
 0x08008124: ('__port_switch', 24, 'agreed', 'high', "instruction-identical to ref chcoreasm.S __port_switch (stmdb/vpush/str sp/ldr/mov sp/vpop/ldmia); B's 50-B chcoreasm.o section = A's __port_switch + __port_thread_start + .zombies + __port_switch_from_isr + __port_exit_from_isr."),
 0x0800813C: ('__port_thread_start', 16, 'conflict', 'high', "A __port_thread_start (exact) vs B '__port_switch split2'. Dump 'movs r3,#0; msr BASEPRI,r3; mov r0,r5; blx r4; movs r0,#0; bl 0x08013A70 (chThdExit)' == ref __port_thread_start 0x0800813C. Resolved: A."),
 0x0800814C: ('__port_thread_start.zombies', 2, 'agreed', 'high', "'e7fe b.n self' == ref local label .zombies (chcoreasm.S) inside B's chcoreasm.o section"),
 0x0800814E: ('__port_switch_from_isr', 4, 'A-only', 'high', "'bl 0x08013928 (chSchDoPreemption)' == ref __port_switch_from_isr; B 'INSERTION entry=ptr'"),
 0x08008152: ('__port_exit_from_isr', 6, 'A-only', 'high', "'svc 0; b.n self' + 2 B pad == ref __port_exit_from_isr; B 'INSERTION'"),
 0x08008444: ('__aeabi_idiv0 (= __aeabi_ldiv0)', 4, 'agreed', 'high', "libgcc _dvmd_tls.o 'bx lr' carries both names (ref nm 0x08008434 W __aeabi_idiv0 / W __aeabi_ldiv0); A picked idiv0 (2 B), B ldiv0 (4 B incl. pad). Not a conflict."),
 0x08008970: ('malloc', 16, 'conflict', 'high', "A ambiguous {free|malloc|raise} vs B malloc. Dump 0x08008970: 'ldr r3,=_impure_ptr(0x20000C0C); mov r1,r0; ldr r0,[r3]; b.w 0x08009758' and 0x08009758 = _malloc_r (Ubuntu libc_a-mallocr.o placed at 0x08009710 = sbrk_aligned+_malloc_r, 90.9% bytes equal); newlib malloc.c emits malloc before free. Resolved: B."),
 0x08008980: ('free', 16, 'agreed', 'high', "'... b.w 0x08009858' and 0x08009858 = _free_r (libc_a-freer.o, 89.9% bytes equal)"),
 0x0800DEFC: ('get_tapping_term', 4, 'conflict', 'high', "A get_tapping_term ('movs r0,#175; bx lr', caller vote) vs B 'waiting_buffer_scan_tap split1'. Callers: tap_dance_task@0x080120EC after building a keyrecord_t on the stack (strd r3,r3,[sp]; mov r1,sp; ldrh r0,[active_td]; bl 0x0800DEFC; cmp r5,r0) where ref tap_dance_task@0x080105EC has 'cmp r0,#140' inline; waiting_buffer_scan_tap@0x0800DF52 (right after bl get_record_keycode 0x0800D334) where ref has 'cmp r2,#139'; process_tapping@0x0800E016 and @0x0800E192. That call shape is GET_TAPPING_TERM() with TAPPING_TERM_PER_KEY defined. Body is the weak default returning TAPPING_TERM = 175, at the action_tapping.o link position (after waiting_buffer_typed.isra.0, before waiting_buffer_scan_tap), not in the keymap object. Resolved: A; B's 'TAPPING_TERM_PER_KEY off' inference is wrong."),
 0x0800DF00: ('waiting_buffer_scan_tap', 148, 'B-only', 'high', "same control flow as ref 0x0800BF3C (ldrb [..#6]; cmp #15; ring index and #7; bfi #4,#4 on tap.count; bl process_record 0x0800DAD8; tail b.w debug_waiting_buffer 0x0800DE58); 16 B larger than ref because the inline 'cmp #139' became bl get_record_keycode + bl get_tapping_term. B (split2) + inspection."),
 0x0800E3B0: ('clear_oneshot_locked_mods', 24, 'conflict', 'high', "A clear_oneshot_mods (exact; the only candidate because ref_feat has no clear_oneshot_locked_mods) vs B clear_oneshot_locked_mods. Body clears byte 0x200016A5 then bl 0x0800E38C. 0x200016A5 is the byte written by add_oneshot_locked_mods@0x0800E394 (A exact) and del_oneshot_locked_mods@0x0800E3C8; the oneshot_mods group (get 0x0800E380, add 0x0800E3EC, del 0x0800E408, clear 0x0800E424) uses 0x200016A6 and calls oneshot_mods_changed_kb 0x0800E3E4. Orientation pinned by process_action@0x0800D83A-0x0800D846: bl register_mods(0x0800D672); bl del_oneshot_mods(0x0800E408); bl add_oneshot_locked_mods(0x0800E394) == quantum/action.c:464-466 (tap_count == ONESHOT_TAP_TOGGLE branch). Resolved: B."),
 0x0800E424: ('clear_oneshot_mods', 24, 'agreed', 'high', "clears byte 0x200016A6 (oneshot_mods, see 0x0800E3B0) then bl oneshot_mods_changed_kb 0x0800E3E4; A exact + B"),
 0x0800E38C: ('oneshot_locked_mods_changed_kb', 8, 'agreed', 'high', "A ambiguous 8-B kb-hook set resolved by callers add/clear/del_oneshot_locked_mods (0x200016A5 group); body 'push {r3,lr}; bl 0x0800D08C; pop' -> oneshot_locked_mods_changed_user [user]"),
 0x0800E3E4: ('oneshot_mods_changed_kb', 8, 'agreed', 'high', "B merge label 'oneshot_mods_changed_user+oneshot_mods_changed_kb': only the kb hook lives here ('push {r3,lr}; bl 0x0800D088; pop'); the ref's 2-B user stub is replaced by the user's oneshot_mods_changed_user at 0x0800D088. Callers add/del/clear_oneshot_mods (0x200016A6 group)."),
 0x080119F8: ('leader_reset_timer', 16, 'conflict', 'high', "A ambiguous {default_layer_state_set|layer_state_set} vs B leader_reset_timer. Body 'push {r3,lr}; bl 0x08012574 (timer_read); ldr r3,=0x20002006; strh r0,[r3]; pop' and 0x20002006 is the halfword leader_start@0x08011950-0x08011956 writes (leader_time). A itself places default_layer_state_set at 0x0800DBD0 and layer_state_set at 0x0800DC24. Resolved: B (function exists because LEADER_PER_KEY_TIMING is defined)."),
 0x080118F4: ('process_leader', 76, 'B-only', 'high', "B merge label 'process_leader+leader_start_user': the ref's 2-B leader_start_user stub follows process_leader in process_leader.o; in the dump leader_start_user is the user's 10-B function at 0x0800CDF4, so this row is process_leader alone (calls leader_sequence_add, leader_reset_timer 0x080119F8 -> LEADER_PER_KEY_TIMING)."),
 0x08016304: ('spi_lld_serve_tx_interrupt', 60, 'conflict', 'high', "A tx (exact) + C(gcc13) rx@0x08016340 vs B rx/tx swapped (opsim 0.53 both). Dump 0x08016304 is instruction-identical to ref spi_lld_serve_tx_interrupt 0x08014824 (tst.w r1,#12; bl chSysHalt; bl spi_lld_stop_abort.isra.0; blx cb; msr BASEPRI; bl chThdResumeI); sizes 60/136 match ref 60/136. Resolved: A."),
 0x08016340: ('spi_lld_serve_rx_interrupt', 136, 'conflict', 'high', "see 0x08016304; A fuzzy-anchored 0.94 + gcc13 exact; B swapped. Resolved: A."),
 0x080166EC: ('_kill', 16, 'agreed', 'high', "A {_exit|_kill} 16 B, B _kill 20 B (B absorbed _getpid because _kill ends in the noreturn 'bl abort'); body 'push; ldr r0,=str; bl chSysHalt 0x0801357C; bl abort 0x080085E8' == ref _kill (16 B)."),
 0x080166FC: ('_getpid', 4, 'conflict', 'high', "'movs r0,#1; bx lr' == ref _getpid (4 B); A placed its 4-B ambiguous set here, B put _getpid at 0x08016700. Resolved: A."),
 0x08016700: ('_fini', 2, 'conflict', 'high', "lone 'bx lr' after _getpid at the end of .text (ref syscalls.o/syscall-fallbacks.o order: _exit,_kill,_getpid,_fini); A's 2-B ambiguous set contains _fini, B labelled it _getpid. Resolved: _fini (B reported _fini absent)."),
 0x08010E4C: ('rgb_matrix_increase_val_helper', 48, 'agreed', 'high', "B merged row 104 B 'rgb_matrix_increase_val_helper+rgb_matrix_toggle_eeprom_helper'; A exact rgb_matrix_toggle_eeprom_helper at 0x08010E7C (56 B) splits it (ref sizes 44/56)."),
 0x08010E7C: ('rgb_matrix_toggle_eeprom_helper', 56, 'agreed', 'high', "A exact 56 B; second half of B's merged row"),
 0x08013CD0: ('halInit', 38, 'agreed', 'high', "B halInit 42 B includes stInit; dump halInit ends 'ldmia.w sp!,{r3,lr}; b.w 0x08013CF6' (tail-call stInit); ref halInit 38 B"),
 0x08013CF6: ('stInit', 4, 'A-only', 'high', "'b.w 0x08016578 (st_lld_init)' == ref stInit 4 B; B reported stInit absent (merged into halInit)"),
 0x08013B34: ('chMtxObjectInit', 12, 'B-only', 'high', "B 12 B opsim 1.0; A's fuzzy chMtxLockS start 0x08013B3E is 2 B early"),
 0x08013B40: ('chMtxLockS', 100, 'conflict', 'high', "A chMtxLockS fuzzy from 0x08013B3E (102 B) vs B 0x08013B40 (100 B, opsim 1.00, gcc13 agrees). Boundary resolved: B."),
 0x0800A180: ('_malloc_usable_size_r', 16, 'lib-only', 'high', "Ubuntu libc_a-msizer.o .text 16/16 bytes equal at 0x0800A180; called from _realloc_r@0x08009BD2"),
 0x08009FD0: ('__malloc_lock', 4, 'lib-only', 'high', "'bx lr; nop' == Ubuntu libc_a-mlock.o (two 2-B no-op locks); called from _malloc_r@0x08009778 and _free_r@0x0800986C (bl 0x08009FD0); the other bx-lr pair at 0x08009538/3C belongs to findfp.o (__sfp_lock_acquire/release)"),
 0x08009FD4: ('__malloc_unlock', 4, 'lib-only', 'high', "'bx lr; nop' == libc_a-mlock.o; called from _malloc_r@0x080097BE and _free_r@0x08009842 (bl 0x08009FD4)"),
 0x0800DC3C: ('layer_state_is', 28, 'B-only', 'high', "no ref function (unused in ref builds); body: ldrh layer_state(0x2000162E); if 0 -> return layer==0 (clz/lsr #5) else return (layer_state >> layer) & 1 == action_layer.c layer_state_cmp() inlined into layer_state_is(); called from process_record_user and td0_on_dance_finished with layer 1/4"),
 0x08009BC4: ('_realloc_r', 100, 'lib-only', 'medium', "Ubuntu libc_a-reallocr.o (100 B) 85% bytes equal at 0x08009BC4 (relocations differ); B's 2-window hint 'reallocr.o'"),
}
# user code (keymap.c): both methods identified these; A in hooks.csv/summary, B in functions_linkorder.csv
USER = [
 (0x0800CDD8, 2,   'td0_on_reset [user]', "tap_dance_actions[0].fn.on_reset pointer 0x0800CDD9 at flash 0x080179D8 (.data init image, RAM 0x20000E7C+0x10); body 'bx lr'. A+B."),
 (0x0800CDDA, 26,  'td_oneshot_layer1_helper [user static]', "tail-called (b.w) from td0_on_dance_finished@0x0800D216 and @0x0800D24C/0x0800D258 paths; layer_on(1) 0x0800DC64; set_oneshot_layer(1,ONESHOT_START=3) 0x0800E504; b.w clear_oneshot_layer_state(ONESHOT_PRESSED=1) 0x0800E548. A+B."),
 (0x0800CDF4, 10,  'leader_start_user [user]', "bl from leader_start@0x08011948 (exact leader_start 0x08011940); body movs r2,#255; movs r1,#0; mov r0,r2; b.w rgb_matrix_set_color_all 0x0800FEE4 = (255,0,255). A+B."),
 (0x0800CDFE, 354, 'leader_end_user [user]', "bl from leader_end@0x08011984 (exact leader_end 0x0801197C); 7 leader_sequence_one_key/two_keys checks + register_code/unregister_code chains. A+B; see disasm/leader_end_user_0800CDFE.txt."),
 (0x0800CF60, 20,  'keyboard_post_init_user [user]', "b.w tail-call from keyboard_post_init_kb@0x0800CD76 (last insn of the 80-B v10_max.c hook); body default_layer_set(0) 0x0800DBE2 then b.w rgb_matrix_mode(16) 0x08010D40 (mode 16 = TYPING_HEATMAP per rgb_task_render tbb table). A+B."),
 (0x0800CF74, 156, 'rgb_matrix_indicators_advanced_user [user]', "bl from rgb_matrix_indicators_advanced_kb@0x08010C4E (8-B kb hook); per-LED loop, biton16(layer_state|default_layer_state) tbb switch on layers 1..5, flags 0x200015DC/DD/DE. Literal pool 0x0800CFFC-0x0800D010. A+B."),
 (0x0800D010, 120, 'osm_indicator_helper [user static]', "b.w target of both oneshot_mods_changed_user 0x0800D088 and oneshot_locked_mods_changed_user 0x0800D08C; mods&0x22 (shift) / mods&~0x77 (GUI) -> rgb_matrix_set_color_all + flags 0x200015DE/0x200015DD. A+B."),
 (0x0800D088, 4,   'oneshot_mods_changed_user [user]', "bl from oneshot_mods_changed_kb@0x0800E3E6; body 'b.w 0x0800D010'. A+B."),
 (0x0800D08C, 4,   'oneshot_locked_mods_changed_user [user]', "bl from oneshot_locked_mods_changed_kb@0x0800E38E; body 'b.w 0x0800D010'. A+B."),
 (0x0800D090, 36,  'osm_lookup_helper [user static]', "called only from osm_press_handler 0x0800D0B4; walks a 2-entry table through pointer 0x200015E0 (see disasm). A+B."),
 (0x0800D0B4, 80,  'osm_press_handler [user static]', "tail-called from process_record_user@0x0800D15A for pressed OSM(MOD_LSFT/LGUI/RSFT/RGUI) = 0x52A2/0x52A8/0x52B2/0x52B8; calls osm_lookup_helper, get_mods 0x0800E310, clear_oneshot_mods 0x0800E424, clear_oneshot_locked_mods 0x0800E3B0, get_oneshot_mods 0x0800E380, unregister_mods 0x0800D684. A+B."),
 (0x0800D104, 192, 'process_record_user [user]', "bl from process_record_kb@0x0800C6EE (keychron_task.c, exact 26 B); literal pool to 0x0800D1C4. A+B; see disasm."),
 (0x0800D1C4, 40,  'td_cur_dance [user static]', "bl from td0_on_dance_finished@0x0800D1F0; reads state->count [r0,#2], pressed/interrupted bits [r0,#4]/[r0,#5]; returns 1..4. A+B."),
 (0x0800D1EC, 112, 'td0_on_dance_finished [user]', "tap_dance_actions[0].fn.on_dance_finished pointer 0x0800D1ED at flash 0x080179D4; layer 1/4 logic with flags 0x200015E8/0x200015E9; literal pool to 0x0800D25C. A+B."),
 (0x0800D25C, 32,  'oneshot_layer_changed_user [user]', "bl from oneshot_layer_changed_kb@0x0800E4FE; if layer==0 && flag 0x200015E9: layer_clear 0x0800DC34, layer_move(4) 0x0800DC58, flag=0. A+B."),
 (0x0800D27C, 40,  'keycode_at_keymap_location_raw', "keymap_introspection.c (compiled from the user's keymap TU): cmp r0,#5/r1,#5/r2,#17, 108 u16 per layer, literal 0x080169B8 = keymaps[]. A+B."),
 (0x0800D2A4, 4,   'keycode_at_keymap_location', "b.w 0x0800D27C thunk. A+B."),
 (0x0800D2A8, 32,  'keycode_at_encodermap_location_raw', "literal 0x080169A0 = encoder_map[6][1][2]; cmp #5 layers. A+B."),
 (0x0800D2C8, 4,   'keycode_at_encodermap_location', "b.w 0x0800D2A8 thunk. A+B."),
]
# A tiny-body placements inside larger verified B functions (false positives): dropped
A_DROP = {0x0800896E: 'last bx lr of memcpy (libc_a-memcpy.o 308 B, 100% bytes equal)',
          0x0800A1BA: 'inside _kill_r (libc_a-signalr.o)',
          0x0800D4AE: 'tail of biton16 (B 40 B)', 0x0800DBC2: 'tail of debug_record (B 12 B)',
          0x0800FBA8: 'tail of SPLASH_math (B 78 B)', 0x0801016A: 'literal-pool word 0x20000D07 of process_rgb_matrix',
          0x08013AF8: 'tail of chThdDequeueNextI', 0x08014894: 'tail of nvicEnableVector', 0x08014C76: 'tail of stm32_flash_check_errors',
          0x08014E34: "'movs r0,#0; bx lr' return path inside efl_lld_start_erase_sector (B 70 B opsim 1.0, gcc13 agrees)",
          0x08014E38: "'movs r0,#1; bx lr' return path inside efl_lld_start_erase_sector",
          0x08013CF6: None, 0x080166FC: None,  # handled by OV
         }
# rodata objects also content-matched by B (its summary lists them; B's CSV has no data rows)
B_DATA = {'spicfg', 'disconnected_config', 'key_comb_list', 'keymaps', 'ConfigurationDescriptor', '_stm32_dma_streams'}

# ---------------------------------------------------------------- helpers
def aset(name):
    return set(p.strip() for p in name.split('|')) if name else set()
def names_agree(na, nb):
    if not na or not nb: return False
    sb = set(p.strip() for p in nb.split('+'))
    return bool(aset(na) & sb) or na == nb
def conf_for(status, a, b, cnames, libeq=None, agree_vote=False):
    if status == 'lib-only':
        return 'high' if (libeq or 0) >= 0.8 else 'medium'
    if status == 'agreed':
        strong = (a and a['mtype'] in ('exact',)) or (b and b['opsim'] is not None and b['opsim'] >= 0.85) or bool(cnames)
        if a and a['mtype'] == 'exact-ambiguous' and b and b['opsim'] is not None and b['opsim'] >= 0.85: strong = True
        return 'high' if strong else 'medium'
    if status == 'A-only':
        if a['mtype'] == 'exact': return 'high'
        if a['mtype'].startswith('data'): return 'high' if a['mtype'] == 'data' else 'medium'
        return 'medium' if a['mtype'] == 'exact-ambiguous' or a['score'] >= 0.85 else 'low'
    if status == 'B-only':
        if cnames or (b['opsim'] is not None and b['opsim'] >= 0.85) or 'VERIFIED' in b['notes'] or 'HOOK[verified]' in b['notes']:
            return 'high'
        if agree_vote or (b['opsim'] is not None and b['opsim'] >= 0.6) or 'inferred-by' in b['notes']:
            return 'medium'
        return 'low'
    return 'n/a'

rows = []
def add(start, size, name, status, conf, ev):
    rows.append(dict(start=start, size=size, name=name, status=status, confidence=conf, evidence=ev))

conflict_log = []
covered = set()
# ---------------------------------------------------------------- 1. overrides + user code
for st, (name, size, status, conf, ev) in OV.items():
    add(st, size, name, status, conf, ev); covered.add(st)
    if status == 'conflict': conflict_log.append((st, name, ev))
for st, size, name, ev in USER:
    a_hook = 'hooks.csv' if name.split(' [')[0] in ('process_record_user','leader_start_user','leader_end_user','keyboard_post_init_user','rgb_matrix_indicators_advanced_user','keycode_at_keymap_location_raw','keycode_at_encodermap_location_raw') else 'summary'
    add(st, size, name, 'agreed', 'high', ev); covered.add(st)
# ---------------------------------------------------------------- 2. libc cluster from the Ubuntu newlib archive
b_in_libc = [b for b in B if LIBC_LO <= b['start'] < LIBC_HI]
for addr, s in libd.items():
    if addr in covered: continue
    a = Aby.get(addr); b = next((x for x in b_in_libc if x['start'] == addr), None)
    na = a['name'] if a else ''; nb = b['name'] if b else ''
    ln = s['name']
    lset = set(ln.split('/'))
    agree_a = bool(aset(na) & lset); agree_b = bool(set(nb.split('+')) & lset) if nb else False
    ev = f"Ubuntu noble libnewlib 4.4.0.20231231-2 libc_nano.a member {s['member']} placed by tools/lib_match.py windows + direct byte compare ({s['eq']*100:.1f}% of member .text bytes equal at its placement; differences = relocations); symbol offset from the member's symbol table."
    if agree_a and agree_b: status = 'agreed'; ev = 'A+B+' + ev
    elif agree_a: status = 'agreed'; ev = 'A(' + a['mtype'] + ')+lib ' + ev + (f" B: {nb or 'unidentified libc'}" )
    elif agree_b: status = 'agreed'; ev = 'B(' + (b['notes'][:60]) + ')+lib ' + ev
    elif na or nb:
        status = 'conflict'
        ev = f"A={na or '-'} B={nb or '-'} lib={ln}: resolved by the archive member placement (position + bytes). " + ev
        conflict_log.append((addr, ln, ev))
    else:
        status = 'lib-only'
    conf = conf_for(status, a, b, C.get(addr), libeq=s['eq'])
    if status == 'agreed' and s['eq'] >= 0.8: conf = 'high'
    if status == 'conflict': conf = 'high'
    add(addr, s['size'], ln, status, conf, ev); covered.add(addr)
# ---------------------------------------------------------------- 3. remaining B functions
lib_ranges = [(r['start'], r['start'] + r['size']) for r in rows]
def in_any(addr, ranges):
    return any(lo <= addr < hi for lo, hi in ranges)
for b in B:
    st = b['start']
    if st in covered or in_any(st, lib_ranges): continue
    a = Aby.get(st); na = a['name'] if a else ''; nb = b['name']
    cn = C.get(st, [])
    if b['rawname'].startswith('<data'):
        add(st, b['size'], 'literal pool (wear_leveling FNV-1a 64-bit basis 0xCBF29CE484222325 + RAM ptr 0x20001704)', 'B-only', 'high', "not code: " + b['notes']); covered.add(st); continue
    if not nb and not na:
        seg = dump[st - FLASH: st - FLASH + b['size']]
        if all(x == 0 for x in seg) or all(seg[i:i+2] in (b'\x00\xbf', b'\x00\x00') for i in range(0, len(seg) - 1, 2)):
            add(st, b['size'], '<zero padding>', 'padding', 'n/a', 'all-zero bytes between libc members'); covered.add(st); continue
        add(st, b['size'], '', 'unmatched', 'n/a', 'libc cluster, no newlib member matched: ' + b['notes'][:120]); covered.add(st); continue
    vote = AV.get(st, [])
    if na and nb:
        if names_agree(na, nb):
            ev = f"A {a['mtype']} {a['score']:.2f}" + (" (ambiguous set resolved by B link-order/callgraph)" if '|' in na else '') + f"; B align {b['notes'][:80]}" + (f"; gcc13 ref agrees ({cn[0]})" if cn else '')
            status = 'agreed'
        else:
            status = 'conflict'; ev = f"UNRESOLVED A={na} B={nb}"
            conflict_log.append((st, nb, ev))
    elif nb:
        status = 'B-only'
        ev = f"B align {b['notes'][:100]}" + (f"; gcc13 ref agrees ({cn[0]})" if cn else '') + (f"; A caller-vote agrees ({vote[0]})" if vote and names_agree(vote[0], nb) else '')
        if vote and names_agree(vote[0], nb): status = 'agreed'
    elif na:
        status = 'A-only'; ev = f"A {a['mtype']} {a['score']:.2f}; B: {b['notes'][:80]}"
    else:
        status = 'unmatched'; ev = b['notes'][:120]
    name = nb if nb else (na if na else '')
    if status == 'agreed' and '|' in na and nb: name = nb
    if '+' in name and status != 'conflict': ev += f"; B merged label kept"
    conf = conf_for(status, a, b, cn, agree_vote=bool(vote and nb and names_agree(vote[0], nb)))
    if status == 'agreed' and vote and not na: conf = 'medium' if (b['opsim'] or 0) < 0.85 and not cn else 'high'
    add(st, b['size'], name, status, conf, ev); covered.add(st)
# ---------------------------------------------------------------- 4. A rows not represented (data objects, A-only functions in gaps)
final_ranges = [(r['start'], r['start'] + r['size']) for r in rows]
for a in A:
    st = a['start']
    if st in covered: continue
    if st in A_DROP:
        if A_DROP[st]: conflict_log.append((st, '(dropped A tiny body)', f"A {a['name'][:40]} {a['size']} B: {A_DROP[st]}"))
        continue
    if a['mtype'].startswith('data'):
        nm = a['name']
        status = 'data'
        ev = f"A rodata/.data object match ({a['mtype']} {a['score']:.2f})" + ("; B content-matched too" if (aset(nm) & B_DATA) else '')
        add(st, a['size'], nm, status, 'high' if a['mtype'] == 'data' else 'medium', ev); covered.add(st); continue
    if in_any(st, final_ranges):
        # inside a final function: boundary disagreement not covered by OV -> log and skip
        host = next(r for r in rows if r['start'] <= st < r['start'] + r['size'])
        conflict_log.append((st, host['name'], f"A {a['name'][:50]} ({a['mtype']}, {a['size']} B) lies inside final {host['name']}@0x{host['start']:08X}; kept host"))
        continue
    add(st, a['size'], a['name'], 'A-only', conf_for('A-only', a, None, C.get(st)), f"A {a['mtype']} {a['score']:.2f}; no B function starts here")
    covered.add(st)
rows.sort(key=lambda r: r['start'])
# ---------------------------------------------------------------- 5. overlap check + write
prev = None
for r in rows:
    if prev and r['start'] < prev['start'] + prev['size'] and not (prev['status'] == 'data' or r['status'] == 'data'):
        print(f"WARN overlap 0x{prev['start']:08X} {prev['name']} ({prev['size']}) with 0x{r['start']:08X} {r['name']}", file=sys.stderr)
    prev = r
with open(BK + 'functions_final.csv', 'w', newline='') as f:
    w = csv.writer(f)
    w.writerow(['dump_addr', 'size', 'name', 'status', 'confidence', 'evidence'])
    for r in rows:
        w.writerow([f"0x{r['start']:08X}", r['size'], r['name'], r['status'], r['confidence'], r['evidence']])
# stats
cnt = collections.Counter(); byt = collections.Counter()
for r in rows:
    cnt[r['status']] += 1; byt[r['status']] += r['size']
text_named = sum(r['size'] for r in rows if r['start'] < TEXT_END and r['status'] not in ('unmatched', 'padding') and r['name'])
text_total = TEXT_END - 0x08008000
region_named = sum(r['size'] for r in rows if r['status'] not in ('unmatched', 'padding') and r['name'])
stats = dict(rows=len(rows), by_status=dict(cnt), bytes_by_status=dict(byt), text_bytes=text_total, text_named=text_named,
             text_named_pct=round(100 * text_named / text_total, 2), region_bytes=IMAGE_END - 0x08008000, region_named=region_named,
             region_named_pct=round(100 * region_named / (IMAGE_END - 0x08008000), 2),
             conflicts=[dict(addr=f"0x{a:08X}", name=n, note=e) for a, n, e in sorted(conflict_log)])
json.dump(stats, open(BK + 'functions_final_stats.json', 'w'), indent=1)
print(json.dumps({k: v for k, v in stats.items() if k != 'conflicts'}, indent=1))
print('conflicts logged:', len(conflict_log))
for a, n, e in sorted(conflict_log): print(f"  0x{a:08X} {n}: {e[:110]}")
