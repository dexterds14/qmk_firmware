# Final function map of dump_a.bin (Keychron V10 Max custom firmware, built 2024-07-09)

Reconciliation of Method A (`functions_matched.csv`, masked signature matcher vs six gcc-15.2 reference builds) and Method B (`functions_linkorder.csv`, link-order alignment vs `ref1011_feat`), with two tie-breakers: Method C (`dump_symbols_gcc13.json`, `tools/match_ref_funcs.py` vs the xPack GCC 13.2.1 build `refs/ref1011_feat_gcc13.elf`) and the Ubuntu newlib 4.4.0 `libc_nano.a` member placement (`libc_members_placed.json`, `tools/libc_place.py`, from `lib_match.json`). Script: `tools/reconcile_maps.py` -> `functions_final.csv`, `functions_final_stats.json`; `tools/disasm_hooks.py` -> `hooks_final.json`, `disasm/*.txt`.

Every address below is a flash address in `dump_a.bin` (file offset = address - 0x08000000). 'ref' = `refs/ref1011_feat.elf` unless stated. Verified facts cite the instructions they rest on; inferences are marked.

## 1. Result in numbers

* Rows in `functions_final.csv`: 971 (functions, libc symbols, rodata/.data objects).
* `.text` 0x08008000-0x08016704 = 59140 B: 59058 B named (99.86%). The remaining 82 B are alignment padding (18 gaps of 2-40 zero/`nop` bytes between newlib members, e.g. 40 B of zeros at 0x08008698 before the 64-B-aligned `strlen`, and 2 B before `.rodata`).
* Whole image 0x08008000-0x08017F04 = 65284 B: 62909 B named (96.36%); the unnamed remainder is anonymous rodata/.data (strings, USB descriptors, ChibiOS config structs) that neither method sizes.
* Status counts (rows / bytes): agreed 805 / 47494 B, B-only 63 / 5702 B, lib-only 52 / 5458 B, conflict 14 / 390 B, A-only 3 / 14 B, data 34 / 3851 B.
* Confidence: A-only:high=3, B-only:high=57, B-only:medium=6, agreed:high=768, agreed:medium=37, conflict:high=14, data:high=25, data:medium=9, lib-only:high=48, lib-only:medium=4.
* Method A alone had named 41.9% of the code region (exact+fuzzy) and Method B 88.1% of `.text`; the union plus the libc archive placement names 99.86% of `.text`. Where both named a function they agreed in 805 cases (A's `a|b|c` ambiguous sets count as agreement when B's link-order pick is a member - 130 such tiny identical-body functions: rgb effect wrappers, weak kb/user hooks, get_* accessors, layer_or/and/xor, register/unregister_mods).

## 2. Genuine disagreements and how each was resolved

All by disassembling the dump (`arm-none-eabi-objdump -D -b binary -m arm -M force-thumb --adjust-vma=0x08000000`) against the reference ELF. Winner in bold.

| address | A vs B | resolution / evidence |
|---|---|---|
| 0x0800811C-0x08008124 | A: Reset_Handler 2 B, BusFault_Handler 4 B, (_unhandled_exception 2 B) / B: INSERTION + "Reset_Handler split1/split2" | **A**. Bytes `e770` (b.n 0x08008000 = _crt0_entry), `f000 f800` (bl 0x08008122), `e7fe` (b.n self) are instruction-identical to ref vectors.S; vector slot 1 = 0x0800811D, slots 2..15 (except SVC) = 0x0800811F. |
| 0x08008124-0x08008158 | A: __port_switch 24, __port_thread_start 16, .zombies 2, __port_switch_from_isr 4, __port_exit_from_isr 6 / B: one 50-B chcoreasm.o section labelled __port_switch (+ INSERTION) | **A** (finer, byte-identical to ref chcoreasm.S: `msr BASEPRI`, `blx r4`, `bl chThdExit`(0x08013A70), `bl chSchDoPreemption`(0x08013928), `svc 0`). Same object, so B is not wrong at object granularity. |
| 0x08008444 | A: __aeabi_idiv0 / B: __aeabi_ldiv0 | alias: both names sit on the same `bx lr` in libgcc _dvmd_tls.o (ref nm 0x08008434 W for both). Not a conflict. |
| 0x08008970 / 0x08008980 | A: {free\|malloc\|raise} ambiguous / B: malloc, free | **B**. 0x08008970 tail-calls 0x08009758 = `_malloc_r` (Ubuntu libc_a-mallocr.o placed at 0x08009710 = sbrk_aligned+_malloc_r, 90.9% bytes equal); 0x08008980 tail-calls 0x08009858 = `_free_r` (libc_a-freer.o 89.9%). |
| 0x0800DEFC | A: get_tapping_term (caller vote) / B: "waiting_buffer_scan_tap split1" and the inference TAPPING_TERM_PER_KEY off | **A**. Body `20af 4770` = movs r0,#175; bx lr. Called from tap_dance_task@0x080120EC after building a keyrecord_t on the stack (`strd r3,r3,[sp]; mov r1,sp; ldrh r0,[active_td]; bl 0x0800DEFC; cmp r5,r0`) where ref tap_dance_task@0x080105EC has `cmp r0,#140` inline; from waiting_buffer_scan_tap@0x0800DF52 (preceded by `bl get_record_keycode` 0x0800D334) where ref has `cmp r2,#139`; and twice from process_tapping (0x0800E016, 0x0800E192). This call shape only exists with TAPPING_TERM_PER_KEY. The body sits at the action_tapping.o link position (after waiting_buffer_typed.isra.0), i.e. it is the weak default returning TAPPING_TERM = 175, not a user override. process_tapping still has `cmp r7,#174` = QUICK_TAP_TERM (= TAPPING_TERM) compared with `<`. |
| 0x0800DF00 | A: unmatched / B: waiting_buffer_scan_tap split2 (148 B) | **B** confirmed: same control flow as ref 0x0800BF3C (`cmp #15`, ring index `and #7`, `bfi #4,#4`, `bl process_record` 0x0800DAD8, tail `b.w debug_waiting_buffer` 0x0800DE58); 16 B larger because the inline TAPPING_TERM compare became two calls. |
| 0x0800E3B0 | A: clear_oneshot_mods (exact) / B: clear_oneshot_locked_mods | **B**. The body clears byte 0x200016A5 and calls 0x0800E38C. 0x200016A5 is also written by add_oneshot_locked_mods@0x0800E394 (A exact) and del_oneshot_locked_mods@0x0800E3C8; the other group (get 0x0800E380, add 0x0800E3EC, del 0x0800E408, clear 0x0800E424) uses 0x200016A6 and calls 0x0800E3E4. Orientation pinned by process_action@0x0800D83A-0x0800D846: `bl register_mods(0x0800D672); bl 0x0800E408; bl 0x0800E394` = quantum/action.c:464-466 `register_mods; del_oneshot_mods; add_oneshot_locked_mods`. Hence 0x200016A6 = oneshot_mods, 0x200016A5 = oneshot_locked_mods, 0x0800E38C = oneshot_locked_mods_changed_kb (-> user 0x0800D08C), 0x0800E3E4 = oneshot_mods_changed_kb (-> user 0x0800D088). A matched the wrong twin because ref_feat contains no clear_oneshot_locked_mods. |
| 0x080119F8 | A: {default_layer_state_set\|layer_state_set} ambiguous / B: leader_reset_timer | **B**. Body `bl timer_read(0x08012574); ldr r3,=0x20002006; strh r0,[r3]`; 0x20002006 is the halfword leader_start@0x08011950-56 writes (leader_time). A already places default_layer_state_set at 0x0800DBD0 and layer_state_set at 0x0800DC24. Exists because LEADER_PER_KEY_TIMING is defined. |
| 0x08016304 / 0x08016340 | A: spi_lld_serve_tx_interrupt 60 B (exact), rx 136 B; C agrees / B: swapped (opsim 0.53) | **A**. 0x08016304 is instruction-identical to ref spi_lld_serve_tx_interrupt 0x08014824 (`tst.w r1,#12; bl chSysHalt; bl spi_lld_stop_abort.isra.0; blx r3; msr BASEPRI,#0x30; bl chThdResumeI`); ref sizes tx 60 / rx 136 match. |
| 0x080166EC-0x08016704 | A: _kill 16, _getpid 4 @0x080166FC, bx-lr set @0x08016700 / B: _kill 20, _getpid @0x08016700 | **A** + link order: _kill ends with the noreturn `bl abort` so B ran it into `movs r0,#1; bx lr` (= _getpid, 4 B); the lone `bx lr` at 0x08016700 is `_fini` (ref order _exit,_kill,_getpid,_fini; B had reported _fini absent). |
| 0x08010E4C | A: rgb_matrix_toggle_eeprom_helper exact @0x08010E7C / B: merged 104-B row increase_val_helper+toggle_eeprom_helper | split into rgb_matrix_increase_val_helper 48 B + rgb_matrix_toggle_eeprom_helper 56 B (ref 44/56). |
| 0x08013CD0 | A: stInit 4 B @0x08013CF6 / B: halInit 42 B (stInit "absent") | halInit is 38 B ending `ldmia.w sp!,{r3,lr}; b.w 0x08013CF6`; 0x08013CF6 `b.w 0x08016578 (st_lld_init)` = stInit. |
| 0x08013B34 | A: chMtxLockS fuzzy from 0x08013B3E / B: chMtxObjectInit 12 B + chMtxLockS @0x08013B40 (opsim 1.0, C agrees) | **B** (A start off by 2). |
| 0x08009344 | A: 4-B ambiguous {_close_r\|_lseek_r\|null_sendchar_func\|...} / lib: __fp_lock | **lib** (findfp.o placement 0x08009344-0x08009568, 201/201 windows, 82% bytes equal). |
| 11 tiny A placements | 2-4 B 'bx lr'/'movs;bx lr' bodies A placed at 0x0800896E, 0x0800A1BA, 0x0800D4AE, 0x0800DBC2, 0x0800FBA8, 0x0801016A, 0x08013AF8, 0x08014894, 0x08014C76, 0x08014E34, 0x08014E38 | dropped: each lies inside a larger function verified by B (opsim >= 0.8 or gcc13 agreement) - function tails, a literal-pool word (0x0801016A = 0x20000D07), or the two return paths of efl_lld_start_erase_sector. |
| 0x08008000 | A: _crt0_entry 116 B + 7 crt0 loop labels / B: _crt0_entry 284 B | kept as one 284-B row (asm local labels listed in the evidence column). |
| B merge labels | B: "oneshot_mods_changed_user+oneshot_mods_changed_kb" @0x0800E3E4, "process_leader+leader_start_user" @0x080118F4 | renamed to the kb/library function alone: the ref's 2-B user stubs are replaced by the user's real hooks at 0x0800D088 and 0x0800CDF4. |

Method C (gcc13) disagreed with A=B only on clone naming (`spi_lld_stop_abort.isra.0` vs `spi_lld_stop_abort`, `chSchDoPreemption` vs `__sch_reschedule_ahead` alias) - same functions.

## 3. Hooks (`hooks_final.json`)

| hook | dump addr | size | status | callers proving identity | disasm |
|---|---|---|---|---|---|
| process_record_user | 0x0800D104 | 192 | custom | process_record_kb@0x0800C6EE bl (keychron_task.c, exact 26 B, both methods) | disasm/process_record_user_0800D104.txt |
| process_record_kb | 0x0800C6E8 | 26 | stock-kb | process_record_quantum@0x0800D3B6 (fuzzy-anchored, 14 BLs vs ref 17: MAGIC/GRAVE_ESC/SPACE_CADET absent) | disasm/process_record_kb_0800C6E8.txt |
| tap_dance_actions[0].fn.on_dance_finished (td0_on_dance_finished) | 0x0800D1EC | 112 | custom | pointer 0x0800D1ED in tap_dance_actions init image @0x080179D4; process_tap_dance_action_on_dance_finished@0x08011FB8 (exact) calls through the table | disasm/td0_on_dance_finished_0800D1EC.txt |
| tap_dance_actions[0].fn.on_reset (td0_on_reset) | 0x0800CDD8 | 2 | custom | pointer 0x0800CDD9 in tap_dance_actions init image @0x080179D8 | disasm/td0_on_reset_0800CDD8.txt |
| tap_dance_actions[0].fn.on_each_tap / on_each_release / user_data | - | - | not-found | words 0x080179D0 / 0x080179DC / 0x080179E0 are 0 |  |
| td_cur_dance (static helper) | 0x0800D1C4 | 40 | custom | td0_on_dance_finished@0x0800D1F0 bl | disasm/td_cur_dance_0800D1C4.txt |
| td_oneshot_layer1_helper (static helper) | 0x0800CDDA | 26 | custom | td0_on_dance_finished b.w tail-calls | disasm/td_oneshot_layer1_helper_0800CDDA.txt |
| leader_end_user | 0x0800CDFE | 354 | custom | leader_end@0x08011984 bl (leader_end exact 20 B) | disasm/leader_end_user_0800CDFE.txt |
| leader_start_user | 0x0800CDF4 | 10 | custom | leader_start@0x08011948 bl (leader_start exact 60 B) | disasm/leader_start_user_0800CDF4.txt |
| housekeeping_task_user | 0x0800E768 | 2 | stock-default | housekeeping_task@0x0800E770 bl |  |
| housekeeping_task_kb | 0x0800C714 | 4 | stock-kb | housekeeping_task@0x0800E76C bl |  |
| matrix_scan_user | 0x0800ED16 | 2 | stock-default | matrix_scan_kb@0x0800ED1A bl |  |
| layer_state_set_user | 0x0800DC18 | 2 | stock-default | layer_state_set_kb@0x0800DC1C bl |  |
| layer_state_set_kb | 0x0800DC1A | 10 | stock-kb | layer_state_set@0x0800DC24 (bl); magic@0x0800ECCC b.w |  |
| default_layer_state_set_user | 0x0800DBC4 | 2 | stock-default | default_layer_state_set_kb@0x0800DBC8 bl |  |
| rgb_matrix_indicators_user | 0x0801017A | 4 | stock-default | rgb_matrix_indicators_kb@0x0800C704 bl |  |
| rgb_matrix_indicators_kb | 0x0800C702 | 18 | stock-kb | rgb_matrix_task@0x08011120 bl | disasm/rgb_matrix_indicators_kb_0800C702.txt |
| rgb_matrix_indicators_advanced_user | 0x0800CF74 | 156 | custom | rgb_matrix_indicators_advanced_kb@0x08010C4E bl (8 B stock kb wrapper, itself bl from rgb_matrix_indicators_advanced@0x08010C66) | disasm/rgb_matrix_indicators_advanced_user_0800CF74.txt |
| rgb_matrix_indicators_advanced_kb | 0x08010C4C | 8 | stock-kb | rgb_matrix_indicators_advanced@0x08010C66 bl |  |
| oneshot_mods_changed_user | 0x0800D088 | 4 | custom | oneshot_mods_changed_kb@0x0800E3E6 bl | disasm/oneshot_mods_changed_user_0800D088.txt |
| oneshot_locked_mods_changed_user | 0x0800D08C | 4 | custom | oneshot_locked_mods_changed_kb@0x0800E38E bl | disasm/oneshot_locked_mods_changed_user_0800D08C.txt |
| osm_indicator_helper (static helper) | 0x0800D010 | 120 | custom | b.w from both oneshot_*_mods_changed_user | disasm/osm_indicator_helper_0800D010.txt |
| oneshot_layer_changed_user | 0x0800D25C | 32 | custom | oneshot_layer_changed_kb@0x0800E4FE bl | disasm/oneshot_layer_changed_user_0800D25C.txt |
| osm_press_handler / osm_lookup_helper (static helpers) | 0x0800D0B4 | 80 | custom | process_record_user@0x0800D15A b.w tail-call | disasm/osm_press_handler_0800D0B4.txt |
| dip_switch_update_kb | 0x0800CD18 | 32 | stock-kb | dip_switch_read@0x0801189C+0x20 bl | disasm/dip_switch_update_kb_0800CD18.txt |
| dip_switch_update_user | 0x0800CCF0 | 40 | stock-kb | dip_switch_update_kb@0x0800CD2C bl |  |
| encoder_update_user / encoder_update_kb | - | - | not-found |  |  |
| keycode_at_encodermap_location_raw | 0x0800D2A8 | 32 | custom | keycode_at_encodermap_location@0x0800D2C8 b.w thunk (called from encoder code) | disasm/keycode_at_encodermap_location_raw_0800D2A8.txt |
| raw_hid_receive | 0x0800C908 | 16 | stock-kb | raw_hid_task@0x08012C1C+0x1C bl | disasm/raw_hid_receive_0800C908.txt |
| keyboard_post_init_user | 0x0800CF60 | 20 | custom | keyboard_post_init_kb@0x0800CD76 b.w tail-call (last insn of the 80-B v10_max.c hook) | disasm/keyboard_post_init_user_0800CF60.txt |
| keyboard_post_init_kb | 0x0800CD38 | 80 | stock-kb | keyboard_init@0x0800E79E bl (keyboard_init exact 28 B) | disasm/keyboard_post_init_kb_0800CD38.txt |
| eeconfig_init_user | 0x0800E61E | 6 | stock-default | eeconfig_init_kb@0x0800E62C bl |  |
| eeconfig_init_kb | 0x0800E624 | 16 | stock-kb | eeconfig_init_quantum@0x0800E634 bl |  |
| get_tapping_term | 0x0800DEFC | 4 | stock-default | tap_dance_task@0x080120EC bl (keyrecord_t built on stack); waiting_buffer_scan_tap@0x0800DF52 bl; process_tapping@0x0800E016 bl; process_tapping@0x0800E192 bl | disasm/get_tapping_term_0800DEFC.txt |
| process_tapping (variant) | 0x0800DF94 | 648 | stock | action_tapping_process@0x0800E21C bl |  |
| tap_dance_task (variant) | 0x080120D0 | 80 | stock | quantum_task@0x0800E7A6 bl | disasm/tap_dance_task_080120D0.txt |
| keycode_at_keymap_location_raw | 0x0800D27C | 40 | custom | keycode_at_keymap_location@0x0800D2A4 b.w thunk | disasm/keycode_at_keymap_location_raw_0800D27C.txt |
| keymap_layer_count_raw / keymap_layer_count | - | - | not-found |  |  |
| pre_process_record_user / post_process_record_user | - | - | stock-default | pre_process_record_kb@0x0800D2D2 bl; post_process_record_kb@0x0800D2E0 bl |  |
| shutdown_user / suspend_power_down_user / suspend_wakeup_init_user / led_update_user / keyboard_pre_init_user | - | - | stock-default | shutdown_kb@0x0800D374; suspend_power_down_kb@0x0801245A; suspend_wakeup_init_kb@0x08012464; led_update_kb@0x0800B91C; keyboard_pre_init_kb@0x0800E734 |  |

`status`: custom = body is user code (matches no reference weak default); stock-default = the QMK weak default body at its library link position; stock-kb = Keychron/keyboard-level implementation unchanged from the fork; not-found = not in the image.

### tap_dance_actions init image

Flash 0x080179C8 -> RAM 0x20000E7C (RAM = flash - __textdata_base__(0x0801774C) + __data_base__(0x20000C00) from crt0 literal triple @0x080080F8; RAM address also the literal at process_tap_dance@0x08012040+0x84). Words: 0x00000000 0x00000000 0x00000000 0x0800D1ED 0x0800CDD9 0x00000000 0x00000000. One 28-B entry: state = 0x00000000 (count/interrupted/pressed/... zero-init); state_pad = 0x00000000; on_each_tap = 0x00000000 (NULL); on_dance_finished = 0x0800D1ED -> td0_on_dance_finished [user]; on_reset = 0x0800CDD9 -> td0_on_reset [user]; on_each_release = 0x00000000 (NULL); user_data = 0x00000000 (NULL). 0x200016A7 0x200016C7 0x0800EC85 (nkro/keyboard report pointers 0x200016A7 0x200016C7 + fn ptr = following .data object; so exactly one tap-dance entry)

### encoder_map (rodata 0x080169A0, 24 B, 24 B before keymaps[])

* layer0: ENCODER_CCW_CW(KC_VOLU, KC_VOLD)  [0x00A9,0x00AA]
* layer1: ENCODER_CCW_CW(RGB_VAI, RGB_VAD)  [0x7827,0x7828]
* layer2: ENCODER_CCW_CW(KC_VOLU, KC_VOLD)  [0x00A9,0x00AA]
* layer3: ENCODER_CCW_CW(KC_NO, KC_NO)  [0x0000,0x0000]
* layer4: ENCODER_CCW_CW(KC_NO, KC_NO)  [0x0000,0x0000]
* layer5: ENCODER_CCW_CW(RGB_VAI, RGB_VAD)  [0x7827,0x7828]

Keycode values from quantum/keycodes.h of the fork: KC_AUDIO_VOL_UP 0x00A9 (KC_VOLU), KC_AUDIO_VOL_DOWN 0x00AA (KC_VOLD), RGB_VAI 0x7827, RGB_VAD 0x7828. `ENCODER_CCW_CW(a,b)` stores a at index 0 (CCW) and b at index 1 (CW).

### What the custom hooks do (from `disasm/`, cross-checked with the sibling source `keymaps/default/keymap.c` of the user's dactyl_manuform build - see `refs/dactyl_reference_summary.md`)

* **process_record_user** (0x0800D104, 192 B): calls `process_record_keychron_common` first (returns false -> return false). If `move_to_lower` (0x200015E8) is set and the key is not TD(0) (`cmp.w r4,#0x5700`) it is cleared. If `return_to_mouse` (0x200015E9) is set and `layer_state_is(1)` is false it is cleared. On press: `KC_CAPS` (0x39) -> reads `host_keyboard_led_state()` bit 1 (caps_lock) and stores the flag 0x200015DC; keycodes in OSM range with `(kc-0x52A2) <= 22` and bit set in mask 0x410041 -> OSM(MOD_LSFT)=0x52A2, OSM(MOD_LGUI)=0x52A8, OSM(MOD_RSFT)=0x52B2, OSM(MOD_RGUI)=0x52B8 -> tail-call `check_unlock_osm` (0x0800D0B4); `QK_USER_0` (0x7E40) -> register/unregister KC_DOT (0x37) then KC_SLSH (0x38) = types `./` and returns false; `QK_USER_1` (0x7E41) -> KC_DOT then falls into the QK_USER_0 block = `../`, returns false. Everything else returns true.
* **check_unlock_osm / find_osm_slot** (0x0800D0B4 / 0x0800D090): `find_osm_slot(kc)` loads `held_osm[0]` (0x200015E0), compares `*p` and `*(uint16_t*)((char*)p+4)` with kc (the source's `index += sizeof(uint16_t)` on a `uint16_t*`, i.e. +4 bytes) and returns the matching pointer, else NULL (when `held_osm[0]` is NULL the compiled code reads address 0x00000004 - the vector-table word 0x0800811D - and never matches; harmless UB inherited from the source). `check_unlock_osm`: no slot -> return true (key processed normally); `get_mods()==0` -> return false; `*slot == kc` -> return false (always true when a slot was found, so the following block is dead in this build); otherwise clear_oneshot_mods, clear_oneshot_locked_mods, unregister_mods(get_oneshot_mods()), held_osm[0..1]=NULL, shift_active=gui_active=0, return false. Net effect in this build: the four OSM keys are always passed through (return true) because `held_osm` is never written anywhere in the image (both words only ever zeroed).
* **handle_oneshots** (0x0800D010, tail-called by both `oneshot_mods_changed_user` 0x0800D088 and `oneshot_locked_mods_changed_user` 0x0800D08C): shift = mods & 0x22, gui = mods & 0x88. If shift and !shift_active -> `rgb_matrix_set_color_all(255,255,255)`, shift_active=1; if !shift and shift_active -> set_color_all(0,0,0), shift_active=0; if gui and !gui_active -> set_color_all(255,255,0), gui_active=1; if !gui and gui_active -> set_color_all(0,0,0), gui_active=0.
* **rgb_matrix_indicators_advanced_user** (0x0800CF74): for each LED led_min..led_max: layer = `biton16(layer_state | default_layer_state)` (0x2000162E | 0x20001630); `tbb` on layer: 1 -> (0,255,0), 2 -> (0,0,255), 3 -> (255,128,0), 4 -> (0,128,128), 5 -> (255,0,0) via `rgb_matrix_set_color`; layer 0 -> nothing. Then if gui_active -> (255,255,0) on that LED; else if shift_active || caps flag -> (255,255,255). Returns false.
* **TD(0)** (`td0_on_dance_finished` 0x0800D1EC, `cur_dance` 0x0800D1C4 returning TD_UNKNOWN=1/TD_SINGLE_TAP=2/TD_SINGLE_HOLD=3/TD_DOUBLE_TAP=4 exactly as the source enum, `td0_on_reset` = empty): HOLD -> `layer_clear(); layer_move(4)`; DOUBLE_TAP -> `layer_clear(); layer_move(1)`; SINGLE_TAP -> if `layer_state_is(4)`: return_to_mouse=1, layer_clear, `layer_oneshot_Lower()` (0x0800CDDA: layer_on(1); set_oneshot_layer(1, ONESHOT_START); clear_oneshot_layer_state(ONESHOT_PRESSED)); elif move_to_lower: layer_clear; layer_move(1); move_to_lower=0; elif `layer_state_is(1)`: layer_clear + layer_oneshot_Lower; else move_to_lower=1 + layer_oneshot_Lower. `oneshot_layer_changed_user` (0x0800D25C): when the oneshot layer ends (layer==0) and return_to_mouse: layer_clear; layer_move(4); return_to_mouse=0. (In the sibling source layer 1 = _LOWER and layer 4 = _MOUSE.)
* **leader_start_user** (0x0800CDF4): `rgb_matrix_set_color_all(255,0,255)`. **leader_end_user** (0x0800CDFE): `rgb_matrix_set_color_all(0,0,0)`, then seven INDEPENDENT `if` blocks (superseding an earlier reading as an else-if chain: every `cbz` targets the next test, no block ends in a branch to the epilogue, and the gcc 13.2.1 compile-compare of independent ifs is masked-identical while an else-if chain is not -- see custom_code/leader.md): F -> LGUI+P, LGUI+K; (A,Q) -> LCTL+A, Z, Q, ENTER; Y -> LCTL+X, Y, ENTER; (LCTL,I) -> LCTL+LALT+I; J -> LGUI+P; F -> LGUI+QUOTE (also fires for <LEAD,F>, after the first block); DEL -> LGUI+UP, LEFT. All with register_code/unregister_code pairs (no tap_code16/SEND_STRING in the image).
* **keyboard_post_init_user** (0x0800CF60): `default_layer_set(0); rgb_matrix_mode(16)`; mode 16 = RGB_MATRIX_TYPING_HEATMAP (rgb_task_render@0x08010A8A `cmp r6,#22; tbb`, case 16 @0x08010BF4 -> `bl TYPING_HEATMAP` 0x08010920; the 22 enabled effects are exactly `info.json` `rgb_matrix.animations` of the fork: 1 SOLID_COLOR, 2 BREATHING, 3 BAND_SPIRAL_VAL, 4 CYCLE_ALL, 5 CYCLE_LEFT_RIGHT, 6 CYCLE_UP_DOWN, 7 RAINBOW_MOVING_CHEVRON, 8 CYCLE_OUT_IN, 9 CYCLE_OUT_IN_DUAL, 10 CYCLE_PINWHEEL, 11 CYCLE_SPIRAL, 12 DUAL_BEACON, 13 RAINBOW_BEACON, 14 JELLYBEAN_RAINDROPS, 15 PIXEL_RAIN (inlined), 16 TYPING_HEATMAP, 17 DIGITAL_RAIN, 18 SOLID_REACTIVE_SIMPLE, 19 SOLID_REACTIVE_MULTIWIDE, 20 SOLID_REACTIVE_MULTINEXUS, 21 SPLASH, 22 SOLID_SPLASH).

### User statics (.bss, no init image)

| RAM | meaning |
|---|---|
| 0x200015DC | USER static (bss): caps-lock-active flag (u8) - set/cleared in process_record_user from host_keyboard_led_state().caps_lock on KC_CAPS press; lights white in indicators (sibling source: caps_active) |
| 0x200015DD | USER static (bss): gui_active (u8) - set by handle_oneshots/osm_indicator_helper when oneshot mods & 0x88; indicators -> yellow |
| 0x200015DE | USER static (bss): shift_active (u8) - set by handle_oneshots when oneshot mods & 0x22; indicators -> white |
| 0x200015E0 | USER static (bss): held_osm[0] (uint16_t*) - find_osm_slot/check_unlock_osm |
| 0x200015E4 | USER static (bss): held_osm[1] (uint16_t*) |
| 0x200015E8 | USER static (bss): move_to_lower (u8) - TD(0) single tap from base arms oneshot layer 1 (_LOWER) |
| 0x200015E9 | USER static (bss): return_to_mouse (u8) - TD(0) single tap on layer 4 (_MOUSE): after the oneshot layer finishes, oneshot_layer_changed_user moves back to layer 4 |

Other RAM cells used by the hooks: 0x2000162E layer_state, 0x20001630 default_layer_state, 0x200016A5 oneshot_locked_mods, 0x200016A6 oneshot_mods, 0x20000E7C tap_dance_actions, 0x20002006 leader_time, 0x20002008 leading.

## 4. Custom / not-explained-by-reference code regions (final)

| start | size | what it is |
|---|---|---|
| 0x0800CDD8 | 1188 | USER keymap.c code (15 functions): td0_on_reset 2, layer_oneshot_Lower 26, leader_start_user 10, leader_end_user 354, keyboard_post_init_user 20, rgb_matrix_indicators_advanced_user 156, handle_oneshots 120, oneshot_mods_changed_user 4, oneshot_locked_mods_changed_user 4, find_osm_slot 36, check_unlock_osm 80, process_record_user 192, cur_dance 40, td0_on_dance_finished 112, oneshot_layer_changed_user 32 (0x0800CDD8-0x0800D27C). Both methods, all callers/pointers verified. |
| 0x0800D27C | 80 | keymap_introspection.c compiled from the user TU: keycode_at_keymap_location_raw 40 (literal keymaps 0x080169B8, 6x6x18), thunk 4, keycode_at_encodermap_location_raw 32 (literal encoder_map 0x080169A0), thunk 4. Stock code, user constants. |
| 0x0800DC3C | 28 | layer_state_is (action_layer.c) - library function absent from the reference builds (nothing calls it there), kept alive by the user code. |
| 0x0800E3B0 | 24 | clear_oneshot_locked_mods (action_util.c) - absent from ref_feat, called from check_unlock_osm. |
| 0x080119F8 | 16 | leader_reset_timer (leader.c) - present because LEADER_PER_KEY_TIMING is defined; called from process_leader@0x080118F4. |
| 0x0800DEFC | 4 | get_tapping_term weak default (movs r0,#175) - present because TAPPING_TERM_PER_KEY is defined (below the 16-B threshold, listed for completeness). |
| 0x08008448 | 7544 | libc cluster in plain *(.text): Ubuntu/Debian libnewlib-arm-none-eabi 4.4.0.20231231-2 libc_nano.a members (rand, assert, itoa, abort, utoa, strlen, memset, memcpy, malloc, fprintf, memcmp, nano-vfprintf, wbuf, fvwrite, signal, findfp, fflush, mallocr, freer, memmove, fwalk, memchr, wsetup, reallocr, nano-vfprintf_i, mlock, makebuf, stdio, msizer, signalr) - fully named in functions_final.csv; not user code. |
| 0x080169A0 | 24 | encoder_map[6][1][2] rodata (user table). |
| 0x080169B8 | 1296 | keymaps[6][6][18] rodata (user table; byte-identical to refs/ref_feat_keymap). |
| 0x080179C8 | 28 | tap_dance_actions[1] .data init image (user table): {0,0, NULL, 0x0800D1ED, 0x0800CDD9, NULL, NULL}. |

No other unexplained code: every remaining `.text` function is a stock QMK/ChibiOS/Keychron function (A exact/fuzzy, B alignment, or both) or the padding listed in section 1.

## 5. libc cluster (0x08008448-0x0800A1C0)

| start | .text B | member | bytes equal | window hits | symbols |
|---|---|---|---|---|---|
| 0x08008448 | 252 | libc_a-rand.o | 85.7% | 111/111 | srand, rand |
| 0x08008544 | 76 | libc_a-assert.o | 69.7% | 17/17 | __assert_func, __assert |
| 0x08008590 | 88 | libc_a-itoa.o | 90.9% | 36/36 | __itoa, itoa |
| 0x080085E8 | 16 | libc_a-abort.o (B: opsim 0.91 vs gcc15 ref) | 50% (2 BL relocs) | - | abort |
| 0x080085F8 | 160 | libc_a-utoa.o | 96.9% | 137/137 | __utoa, utoa |
| 0x080086C0 | 216 | libc_a-strlen.o | 100.0% | 201/201 | strlen |
| 0x08008798 | 164 | libc_a-memset.o | 100.0% | 149/149 | memset |
| 0x0800883C | 308 | libc_a-memcpy.o | 100.0% | 293/293 | memcpy |
| 0x08008970 | 32 | libc_a-malloc.o | 65.6% (2 b.w + 2 literals) | - | malloc, free |
| 0x08008990 | 68 | libc_a-fprintf.o | 85.3% | 15/15 | _fiprintf_r, _fprintf_r, fiprintf, fprintf |
| 0x080089D4 | 92 | libc_a-memcmp.o | 100.0% | 77/77 | memcmp |
| 0x08008A30 | 788 | libc_a-nano-vfprintf.o | 93.5% | 568/568 | __sfputc_r, __sfputs_r, __sprint_r, _vfiprintf_r, _vfprintf_r, vfiprintf, vfprintf |
| 0x08008D44 | 160 | libc_a-wbuf.o | 88.1% | 72/72 | __swbuf_r, __swbuf |
| 0x08008DE4 | 768 | libc_a-fvwrite.o | 93.5% | 522/522 | __sfvwrite_r |
| 0x080090E4 | 608 | libc_a-signal.o | 92.6% | 353/353 | _init_signal_r, _signal_r, _raise_r, __sigtramp_r, raise, signal, _init_signal, __sigtramp |
| 0x08009344 | 548 | libc_a-findfp.o | 82.1% | 201/201 | __fp_lock, stdio_exit_handler, cleanup_stdio, __fp_unlock, global_stdio_init.part.0, __sfp, __sinit, __sfp_lock_acquire, __sfp_lock_release, __fp_lock_all, __fp_unlock_all |
| 0x08009568 | 424 | libc_a-fflush.o | 94.6% | 327/327 | __sflush_r, _fflush_r, fflush |
| 0x08009710 | 328 | libc_a-mallocr.o | 90.9% | 169/169 | sbrk_aligned, _malloc_r |
| 0x08009858 | 188 | libc_a-freer.o | 89.9% | 106/106 | _free_r |
| 0x08009914 | 256 | libc_a-memmove.o | 100.0% | 241/241 | memmove |
| 0x08009A14 | 68 | libc_a-fwalk.o | 100.0% | 53/53 | _fwalk_sglue |
| 0x08009A60 | 160 | libc_a-memchr.o | 100.0% | 145/145 | memchr |
| 0x08009B00 | 196 | libc_a-wsetup.o | 94.9% | 120/120 | __swsetup_r |
| 0x08009BC4 | 100 | libc_a-reallocr.o | 85.0% | 2 (windows) | _realloc_r |
| 0x08009C28 | 936 | libc_a-nano-vfprintf_i.o | 98.8% | 875/875 | _printf_common, _printf_i |
| 0x08009FD0 | 8 | libc_a-mlock.o | 100% | - | __malloc_lock, __malloc_unlock (bl from _malloc_r@0x08009778/0x080097BE, _free_r@0x0800986C/0x08009842) |
| 0x08009FD8 | 276 | libc_a-makebuf.o | 94.2% | 169/169 | __smakebuf_r, __swhatbuf_r |
| 0x0800A0EC | 148 | libc_a-stdio.o | 86.5% | 67/67 | __sread, __seofread, __swrite, __sseek, __sclose |
| 0x0800A180 | 16 | libc_a-msizer.o | 100% | - | _malloc_usable_size_r (bl from _realloc_r@0x08009BD2) |
| 0x0800A190 | 48 | libc_a-signalr.o | 77.1% | 6/6 | _kill_r, _getpid_r |

Alias members with identical code were dropped in favour of the one the callers need (rand over random, fprintf/fiprintf over dprintf/fwprintf because `__assert_func` calls fiprintf, fflush over fflush_unlocked, signalr over the six generic `_xxx_r` syscall wrappers because the tail `b.w 0x080166FC` is `_getpid_r -> _getpid`). Method B's reading 'full newlib' was half right: it is Debian's *nano* newlib, which is built without `-ffunction-sections` (hence one contiguous plain `.text` blob pulled in archive order) and with the optimized assembly memcpy/memset/strlen/memchr/memmove.

## 6. Config inferences (all from dump bytes)

* **TAPPING_TERM**: 175 (get_tapping_term default body movs r0,#175; process_tapping cmp r7,#174 for QUICK_TAP_TERM)
* **TAPPING_TERM_PER_KEY**: defined (four bl get_tapping_term call sites; ref without it inlines cmp #TAPPING_TERM)
* **ONESHOT_TAP_TOGGLE**: 2 (process_action@0x0800D832 cmp.w r8,#2 -> register_mods; del_oneshot_mods; add_oneshot_locked_mods = action.c:462-466)
* **ONESHOT_TIMEOUT**: not defined (no has_oneshot_*_timed_out bodies; add_oneshot_mods 24 B has no timer_read; set_oneshot_layer 48 B)
* **LEADER_PER_KEY_TIMING**: defined (leader_reset_timer 0x080119F8 present and called from process_leader)
* **LEADER_TIMEOUT**: 525 (leader_sequence_timed_out@0x080119C0 movw #0x20D) - from Method B, not re-verified here
* **VIA_ENABLE**: no (raw_hid_receive = keychron_common.c #else stub; no via_/dynamic_keymap_ functions)
* **ENCODER_MAP_ENABLE**: yes (encoder_map @0x080169A0, keycode_at_encodermap_location_raw present, no encoder_update_*)
* **TAP_DANCE_ENABLE / LEADER_ENABLE / MOUSEKEY_ENABLE**: yes / yes / yes (process_tap_dance exact; leader_* exact; mousekey_task 412 B @0x08011DF0)
* **MAGIC_ENABLE / GRAVE_ESC_ENABLE / SPACE_CADET_ENABLE**: no (process_magic/process_grave_esc/process_space_cadet absent; process_record_quantum has 14 BLs vs ref 17) - Method B, consistent with A leaving no unmatched code of those sizes
* **RGB default mode**: rgb_matrix_mode(16) in keyboard_post_init_user = TYPING_HEATMAP (dump tbb case table)


These agree with the user's sibling dactyl keymap config (`TAPPING_TERM 150` + `TAPPING_TERM_PER_KEY`, `ONESHOT_TAP_TOGGLE 2`, `LEADER_PER_KEY_TIMING`, `LEADER_TIMEOUT 600`, `ONESHOT_TIMEOUT` commented out) except the numeric TAPPING_TERM (175 here) and LEADER_TIMEOUT (525 here). `refs/ref_feat_keymap/config.h` should be changed to `TAPPING_TERM 175`, add `TAPPING_TERM_PER_KEY`, `LEADER_PER_KEY_TIMING`, `LEADER_TIMEOUT 525`, and drop `ONESHOT_TIMEOUT`.

## 7. LTO verdict: NOT an LTO build (both methods agree; re-checked)

* Weak defaults survive as separate 2/4-B functions reached by `bl`: housekeeping_task_user 0x0800E768 (`bx lr`, bl from housekeeping_task@0x0800E770), matrix_scan_user 0x0800ED16, layer_state_set_user 0x0800DC18, default_layer_state_set_user 0x0800DBC4, keyboard_pre_init_user 0x0800E732, rgb_matrix_indicators_user 0x0801017A, eeconfig_init_user 0x0800E61E, get_tapping_term 0x0800DEFC; 4-B tail-call thunks exist (housekeeping_task_kb 0x0800C714 `b.w keychron_task`, keycode_at_keymap_location 0x0800D2A4, stInit 0x08013CF6). LTO inlines all of these.
* Per-TU compiler clones are present (`waiting_buffer_typed.isra.0` 0x0800DEB8, `jellybean_raindrops_set_color.isra.0` 0x0800FE8C, `spi_lld_stop_abort.isra.0` 0x0801625C, `otg_epout_handler.constprop.0`), and 817/817 consecutive matched functions keep the reference's per-object link order over 101 objects (Method B).
* Method A: 21036 B exact vs the three non-LTO refs against 4838 B vs the three LTO refs (same 4x ratio as the known non-LTO Keychron stock build: 26.1% vs 7.5%).
* Size distribution: 931 detected functions, median 32 B (non-LTO ref: 915 sections, median 32; LTO ref: 407 sections, median 52). Image 98052 B > non-LTO ref_feat 95280 B >> LTO 88168 B; the surplus is the 3.9 KB larger Debian libc plus 1 KB user code.

## 8. Compiler guess (reconciled)

**Debian/Ubuntu packaged Arm toolchain: `gcc-arm-none-eabi` 13.2.rel1 (GCC 13.2.1 20231009) with `libnewlib-arm-none-eabi` 4.4.0.20231231-2 - i.e. `apt install gcc-arm-none-eabi` on Ubuntu 24.04 (noble) / Debian testing in mid-2024.** Evidence, strongest first:

1. The newlib `__FILE__` string in the dump, `../../../../../../newlib/libc/stdlib/rand.c` @0x08017674, is exactly the string inside Ubuntu noble's `libnewlib-arm-none-eabi_4.4.0.20231231-2_all.deb` `libc_nano.a` (`compare_images.md`, `refs/toolchain_debs_SOURCES.txt`); the jammy 3.3.0 package has 8 levels, Arm GNU / xPack / crosstool-NG builds have absolute paths.
2. 30 members of that `libc_nano.a` are byte-identical to the dump modulo relocations (section 5: strlen/memset/memcpy/memcmp/memmove/memchr/fwalk 100%, _printf_i 98.8%, ...) and account for the whole 7544-B libc cluster; the gcc-15.2 QMK toolchain's newlib-nano matched 1 member (160 B) and jammy's 3 members.
3. libgcc: the 700-B `__udivmoddi4` at 0x08008188 matched the Ubuntu noble `gcc-arm-none-eabi_13.2.rel1-2` `libgcc.a` member (`lib_match.md`: 1 member, 700 B) and neither the 14.2.rel1 nor the gcc-15.2 libgcc (684 B there).
4. Same-source rebuild with xPack GCC 13.2.1 (`refs/ref1011_feat_gcc13.elf`, the same GCC 13.2.1 20231009 code generator as Arm's 13.2.Rel1 that Debian packages): `tools/match_ref_funcs.py` finds 507 exact masked functions / 31432 B in the dump, versus 356 / 17278 B for the gcc-15.2 build of the same sources (the ~500 B of TD/leader code present only in the feat keymap cannot explain a 14 KB difference). Method B's opcode similarity (dump vs gcc-15: mean 0.920) is consistent with a neighbouring GCC major.
5. Method A's rate vs gcc-15 (32% exact, above the GCC-10 stock build's 26%, far below same-compiler 90%) and Method B's 'GCC 13/14, in-tree build dir, non-function-sectioned nano libs' both point the same way; B's specific 'Homebrew formula' hypothesis is superseded by the Debian evidence (Homebrew's newlib is not built with the Debian relative path).

Not verified: the exact Debian package revision (13.2.rel1-2 vs -1) and whether the build ran on Ubuntu or Debian - both ship the same upstream 13.2.rel1 tarball. A rebuild of ref_feat with that toolchain (available as the two .debs listed in `refs/toolchain_debs_SOURCES.txt`) should reproduce the dump's code section byte-for-byte except for the keymap.c differences.

## 9. Open questions

* `held_osm[]` is never written in the image, so `check_unlock_osm` always returns true for the four OSM keys; if the recovered keymap.c is meant to reproduce behaviour exactly, reproducing this dead logic is optional. The source's `slot = &keycode` is the same no-op.
* The second `leader_sequence_one_key(KC_F)` branch (LGUI+QUOTE) IS reachable (independent ifs, see section 3 correction): <LEAD,F> fires GUI+P, GUI+K and GUI+'. Whether that double binding was intended is unknowable; the sibling source has S/H/C/R sequences in that position.
* LEADER_TIMEOUT 525 rests on a single `movw #0x20D` in leader_sequence_timed_out (Method B); TAPPING_TERM 175 rests on `movs r0,#175` in get_tapping_term plus `cmp r7,#174` in process_tapping (two independent sites).
* 1188 B of user code vs the 244-B ref placeholder means the source keymap.c needs the functions listed in section 3; the recovered keymaps[] table, encoder_map and tap_dance_actions are exact.
* Anonymous rodata/.data (about 2.3 KB: strings, USB descriptors, ChibiOS config structs, `.data` init images of stock objects) is unnamed but stock; the 34 named data objects are in `functions_final.csv` with status `data`.
