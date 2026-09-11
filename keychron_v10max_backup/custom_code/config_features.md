# Target: configuration constants and enabled features (dump_a.bin, Keychron V10 Max, built 2024-07-09)

All addresses are flash addresses in `dump_a.bin` (base 0x08000000). "ref" = `refs/ref1011_feat.elf` unless
stated (same fork commit, gcc 15.2, keymap with `TAPPING_TERM 140`, `ONESHOT_TAP_TOGGLE 2`, `ONESHOT_TIMEOUT 3000`,
TAP_DANCE/LEADER/MOUSEKEY on, VIA off). Decompiled bodies are in `decompiled/<addr>_*.c`; the disassembly
of the user region is `custom_region_0800CDD8.asm`. Struct layouts used below (from the ref tree,
`quantum/keyboard.h:38`, `quantum/action.h:39-56`): `keyevent_t {col@0,row@1,time@2,type@4,pressed@5}`,
`keyrecord_t {event, tap@6}` = 8 bytes; `tap_t` = interrupted bit0, count = upper nibble.

Confidence tags: **[verified]** = instruction-level evidence in the dump; **[likely]** = follows from verified
facts plus one inference (e.g. source layout); **[uncertain]** = not decidable from the binary.

---

## 1. Tapping (`quantum/action_tapping.c`)

### 1.1 TAPPING_TERM = 175, TAPPING_TERM_PER_KEY defined  [verified]

* `0x0800defc: 20af  movs r0,#175 ; 0x0800defe: 4770 bx lr` -- a 4-byte function that takes the arguments
  `(keycode, record)` and returns the constant 175. It is called exactly where `GET_TAPPING_TERM()` expands
  with `TAPPING_TERM_PER_KEY` (`quantum/action_tapping.h:53-54`), i.e. immediately after
  `get_record_keycode(&tapping_key, false)`:
  * process_tapping, "pressed" branch (`WITHIN_TAPPING_TERM`): `0x0800e00c movs r1,#0; 0x0800e00e mov r0,r4(&tapping_key); 0x0800e010 bl 0x0800d334 <get_record_keycode>; 0x0800e014 mov r1,r4; 0x0800e016 bl 0x0800defc; 0x0800e01a cmp r0,r8; bls`
  * process_tapping, "released" branch: `0x0800e18c bl get_record_keycode; 0x0800e192 bl 0x0800defc; 0x0800e196 cmp r0,r8`
  * waiting_buffer_scan_tap: `0x0800df4c bl get_record_keycode; 0x0800df52 bl 0x0800defc; 0x0800df58 cmp r6,r0`
  * tap_dance_task (`process_tap_dance.c:183`): `0x080120dc bl timer_elapsed; ... 0x080120e8 strd r3,r3,[sp] (zeroed keyrecord_t); 0x080120ec bl 0x0800defc; 0x080120f0 cmp r5,r0; bls`
* Without `TAPPING_TERM_PER_KEY` the constant is compiled inline: the ref build (TAPPING_TERM 140) has
  `cmp r3,#139` at ref 0x0800c068 and 0x0800c1d0 and never calls `get_record_keycode` there.
* `0x0800defc` sits inside the `action_tapping.o` function cluster (debug_waiting_buffer 0x0800de58,
  debug_tapping_key 0x0800de98, waiting_buffer_typed.isra.0 0x0800deb8, **0x0800defc**, waiting_buffer_scan_tap
  0x0800df00, process_tapping 0x0800df94, action_tapping_process 0x0800e21c), not in the keymap.o region
  (0x0800CDD8-0x0800D2CC, which contains no such function). So it is the weak default
  `get_tapping_term(){ return TAPPING_TERM; }` from `action_tapping.c:31-38` **[likely]**, meaning
  `TAPPING_TERM_PER_KEY` is defined in config.h but `get_tapping_term()` is not overridden in keymap.c
  (exactly the 09bf-era dactyl config, `dactyl_reference_summary.md` line 786/816).
* `DYNAMIC_TAPPING_TERM_ENABLE` is off (the function returns an immediate, not a RAM `g_tapping_term`).

### 1.2 QUICK_TAP_TERM = 175 (== TAPPING_TERM), QUICK_TAP_TERM_PER_KEY off  [verified]

* `0x0800e1ae ldrh r3,[r4,#2]; 0x0800e1b0 subs r7,r7,r3; 0x0800e1b2 uxth r7; 0x0800e1b4 cmp r7,#174; 0x0800e1b6 bhi` =
  `TIMER_DIFF_16(event.time, tapping_key.event.time) < 175` (`WITHIN_QUICK_TAP_TERM`, followed by the
  `tap.interrupted` test `0x0800e1ba lsls r2,r3,#31; bmi` and `tap.count>0` test `0x0800e1be cmp r3,#15; bls`).
  Constant inline, no `get_quick_tap_term` call. Either `QUICK_TAP_TERM` is not defined (default = TAPPING_TERM,
  `action_tapping.h:26-27`) or defined as 175 -- indistinguishable; the dactyl configs never set it.

### 1.3 PERMISSIVE_HOLD: off  [verified]

* Source `action_tapping.c:216-231`: with PERMISSIVE_HOLD the branch `!event.pressed && waiting_buffer_typed(event)
  && true` would call `process_record(&tapping_key)`, zero `tapping_key` and return false.
* Dump `0x0800e05c cmp.w fp,#0 (event.pressed); 0x0800e060 bne 0x0800e0ce; 0x0800e062 ldrd r0,r1,[sp]; 0x0800e066 mov r2,fp; 0x0800e068 bl 0x0800deb8 <waiting_buffer_typed>` -- result **discarded**;
  `0x0800e06c ldr r0,[sp]; 0x0800e06e bl 0x0800deb8; 0x0800e072 mov r4,r0; 0x0800e074 cmp r0,#0; 0x0800e076 bne 0x0800e052 (return false)` = the
  `!waiting_buffer_typed` guard of the *next* branch; then `0x0800e07a bl layer_switch_get_action` and the
  ACT_LMODS/ACT_MODS_TAP/ACT_LAYER_TAP switch (`0x0800e07e ubfx r2,r0,#12,#4 ... 0x0800e0b8 adds r3,#32; uxtb; cmp r3,#7` = IS_MODIFIER_KEYCODE, `0x0800e0c2 cmp r3,#239` = OP_TAP_TOGGLE-1).
  No `process_record(&tapping_key)`/`memset` between the two typed calls. The dead first call is a compiler
  artefact of `typed && false`: the ref build, which has no PERMISSIVE_HOLD, shows the identical double call at ref 0x0800c0b2/0x0800c0b8.
* No `get_permissive_hold()` call anywhere (hooks.csv: not found) -> `PERMISSIVE_HOLD_PER_KEY` off.

### 1.4 HOLD_ON_OTHER_KEY_PRESS: off  [verified]

* Source `action_tapping.c:268-283`: with it defined, a press of another key would `process_record(&tapping_key)`, clear `tapping_key`, `debug_tapping_key()`.
* Dump `0x0800e0ce ldrb r3,[r4,#6]; 0x0800e0d0 orr.w r3,r3,#1; 0x0800e0d4 strb r3,[r4,#6]; 0x0800e0d6 b 0x0800e052 (movs r4,#0 -> return false)` -- only `tapping_key.tap.interrupted = true`.
* process_action MT default case (`action.c:498-516`): `0x0800d7c0 register_code` is reached directly for `tap_count>0`
  with no `record->tap.interrupted` test (no `HOLD_ON_OTHER_KEY_PRESS` block). No `get_hold_on_other_key_press` call -> `_PER_KEY` off.

### 1.5 RETRO_TAPPING / RETRO_SHIFT / AUTO_SHIFT: off  [verified]

* `action_exec` 0x0800d50c is 64 bytes (ref with ONESHOT_TIMEOUT: 96): body = `clear_weak_mods` (0x0800e374) if pressed,
  `pre_process_record_quantum` (0x0800d34c), `action_tapping_process` (0x0800e21c). No `retro_tapping_counter++` (`action.c:79-81`).
* process_action 0x0800d698 ends after the layer-LED update (`0x0800daa0..0x0800daad`) and the oneshot release
  block; there is no `is_tap_action`/`retro_tapping_counter` epilogue (`action.c:829-856`) and no `tap_code` call.
* process_tapping has no `MAYBE_RETRO_SHIFTING`/`get_auto_shifted_key` calls; `process_auto_shift` is absent from the image.

### 1.6 TAPPING_TOGGLE = 5 (default)  [verified]

* process_action, ACT_LAYER_TAP `OP_TAP_TOGGLE` (0xF0) case: `0x0800d9e2 cmp.w r8,#4; bhi` (pressed: tap_count < 5 -> `layer_invert` 0x0800dc90)
  and `0x0800d9f4 cmp.w r8,#5` (released: tap_count <= 5). (`0x0800d9d2 cmp r3,#4` is only the `tbb` range check on
  `layer_tap.code - 0xF0` selecting OP_TAP_TOGGLE..OP_ONESHOT, not a tap-count test.) MODS_TAP_TOGGLE (code 0x01) in the same function:
  `pressed: if (5 < tap_count) break; else register_mods` / `released: if (4 < tap_count) break; else unregister_mods`
  = `tap_count <= TAPPING_TOGGLE` / `< TAPPING_TOGGLE` with TAPPING_TOGGLE 5 (`action.c:486-495`, `action_tapping.h:31-32`).

### 1.7 Related defaults seen in process_action

* `TAP_HOLD_CAPS_DELAY 80`, `TAP_CODE_DELAY 0`: `0x0800d892 cmp r6,#0x39 (KC_CAPS); 0x0800d898 moveq.w r0,#8000; 0x0800d89c movne r0,#1; bl chThdSleep`
  (80 ms = 8000 ticks at CH_CFG_ST_FREQUENCY 100 kHz; `wait_ms(0)` -> `chThdSleepMicroseconds(1)` = 1 tick); same at 0x0800da96/0x0800da9a.  [verified, defaults]
* `WAITING_BUFFER_SIZE 8`: `0x0800e268 and.w r4,r4,#7`, `0x0800e2c6 and.w r3,r3,#7`.  [verified, default]

---

## 2. One-shot (`quantum/action_util.c`, `action.c`)

### 2.1 ONESHOT_TAP_TOGGLE = 2  [verified]

* ACT_LAYER_TAP `OP_ONESHOT` (0xF4), `action.c:653-668`:
  `0x0800da2e bl get_oneshot_layer_state; 0x0800da32 cmp r0,#4 (ONESHOT_TOGGLED); beq -> 0x0800da36 bl reset_oneshot_layer; 0x0800da3e bl layer_off`;
  `0x0800da46 cmp.w r8(tap_count),#1; bhi skip -> 0x0800da52 bl layer_on; 0x0800da56 movs r1,#3 (ONESHOT_START); 0x0800da5a bl set_oneshot_layer` = `tap_count < 2`;
  release: `0x0800da60 cmp.w r8,#1; 0x0800da64 bls 0x0800da72 (clear_oneshot_layer_state(1=ONESHOT_PRESSED) @0x0800da72/0x0800da74)` else
  `0x0800da66 bl reset_oneshot_layer; 0x0800da6a movs r1,#4 (ONESHOT_TOGGLED); bl set_oneshot_layer` = `tap_count >= 2`.
  `0x0800da42 movs r7,#0` = `do_release_oneshot = false`.
* MODS_ONESHOT (`action.c:455-478`), press path 0x0800d814-0x0800d84a: `0x0800d816 cmp.w r8,#0` -> `register_mods` 0x0800d672;
  `0x0800d824 cmp.w r8,#1` -> `add_oneshot_mods` 0x0800e3ec; `0x0800d832 cmp.w r8,#2; bne break` -> `register_mods; del_oneshot_mods (0x0800e408);
  add_oneshot_locked_mods (0x0800e394)` = `tap_count == ONESHOT_TAP_TOGGLE`. Release path: `0x0800d84c cmp.w r8,#0` -> `unregister_mods 0x0800d684;
  del_oneshot_mods; del_oneshot_locked_mods 0x0800e3c8`; `0x0800d866 cmp.w r8,#1` + `get_mods` 0x0800e310 / `tst r0,r6`.
  (The `cmp r4,#1/#2/#3` at 0x0800d918-0x0800d924 and 0x0800d978-0x0800d984 belong to the ACT_LAYER / default-layer bit-op dispatch
  `ubfx r4,r4,#10,#2`, not to one-shot.)
* The ref (ONESHOT_TAP_TOGGLE 2) has the same shape. QMK 0.23 has no source default for ONESHOT_TAP_TOGGLE: without a user define the
  `#if defined(ONESHOT_TAP_TOGGLE) && ONESHOT_TAP_TOGGLE > 1` blocks (action.c:461, 653) would be absent entirely.

### 2.2 ONESHOT_TIMEOUT: not defined  [verified]

* `action_exec` 0x0800d50c has no `has_oneshot_layer_timed_out`/`has_oneshot_mods_timed_out` calls (`action.c:98-112`); both
  functions are absent from the image (functions_linkorder_summary.json "ref_functions_absent_from_dump").
* `set_oneshot_layer` 0x0800e504 (48 B vs ref 60 B): `strb r1,[r4] (oneshot_layer_data = layer<<3|state); bl layer_on; bl oneshot_layer_changed_kb` -- no `timer_read` store (`action_util.c:181-183`).
* `add_oneshot_mods` 0x0800e3ec (28 B vs ref 44 B), `del_oneshot_mods` 0x0800e408, `clear_oneshot_mods` 0x0800e424, `reset_oneshot_layer` 0x0800e534 (20 B vs 28 B): no `oneshot_time` writes.
* `get_mods_for_report` 0x0800e43c: `mods = real|weak; if (oneshot_mods) { mods |= oneshot_mods; if (has_anykey()) clear_oneshot_mods(); }` -- no timeout test (`action_util.c:268-272`) and no KEY_OVERRIDE `suppressed_mods` (see section 6).
* The dactyl configs have `ONESHOT_TIMEOUT` commented out -- consistent. The ref build (3000) differs, which explains the size deltas above.

### 2.3 keymap_config default / oneshot_enable  [verified]

* `eeconfig_init_quantum` 0x0800e634: `eeprom_update_word(EECONFIG_KEYMAP(4), 0x1400)` (decompiled `FUN_0800f18c(4,0x1400)`) =
  `oneshot_enable=1, autocorrect_enable=1, nkro=0` (`eeconfig.c`). All OSM/OSL paths test bit 2 of byte 1 of `keymap_config` at 0x200047d5 (`lsls #0x1d` pattern, e.g. 0x0800e504).

---

## 3. Leader (`quantum/leader.c`, `process_leader.c`) -- constants only

* **LEADER_TIMEOUT = 525** [verified]: `leader_sequence_timed_out` 0x080119c0: `0x080119c6 bl timer_elapsed; 0x080119ca movw r3,#0x20d (525); 0x080119ce cmp r0,r3; 0x080119d0 ite ls; movs r0,#0 / movs r0,#1`
  = `timer_elapsed(leader_time) > 525`. Ref: `cmp.w r0,#300` at ref 0x0800fb26 (default). The dactyl configs use 600 -- the V10 Max value differs from both; the source line was evidently `#define LEADER_TIMEOUT 525`.
* **LEADER_PER_KEY_TIMING defined** [verified]: process_leader 0x080118f4: after a successful `leader_sequence_add` (0x0801191e -> 0x0801199c) it calls `0x0801192a bl 0x080119f8` = `leader_reset_timer()` (`leader_time = timer_read()`, only compiled under `LEADER_PER_KEY_TIMING`, `process_leader.c`). `leader_reset_timer` is absent from the ref build (functions_linkorder.csv: "absent from ref build").
* **LEADER_NO_TIMEOUT not defined** [verified]: `leader_sequence_add` 0x0801199c has no `leader_sequence_size == 0 -> leader_reset_timer()` block; `leader_sequence_timed_out` has no `leader_sequence_size > 0` term.
* **LEADER_KEY_STRICT_KEY_PROCESSING not defined** [verified]: `0x08011910 sub.w r3,r4,#0x2000; 0x08011914 cmp.w r3,#0x3000; it lo; uxtb r4,r4` strips MT/LT keycodes to their tap keycode.
* `leader_sequence[5]` at 0x20001ffc, `leader_sequence_size` 0x20001ffb (cap `cmp r3,#4` at 0x080119a0), `leading` 0x20002008, `leader_time` 0x20002006. Behaviour of `leader_end_user` (0x0800cdfe) is the leader target's job.

---

## 4. Mouse keys (`quantum/mousekey.c`) -- MK_KINETIC_SPEED

Mode [verified]: `move_unit` 0x08011a8c is the kinetic algorithm (`mousekey.c:189-214`): `timer_elapsed(mouse_timer)/50`
(`0x08011aa2 ldrh r0,[r3] (mouse_timer @0x2000200e); bl timer_elapsed; udiv by 50`), quadratic accumulation, `speed / (1000/mk_interval)`
(`0x08011ad4 ldr r3,=mk_interval; 0x08011ad6 ldrb r2,[r3]; 0x08011ad8 mov.w r3,#1000`), clamp `0x08011aec cmp r0,#127; movcs r0,#127`.
`mousekey_task` 0x08011df0 uses `mk_delay*10`/`mk_interval` and `mk_wheel_delay*10`/`mk_wheel_interval` exactly as `mousekey.c:342-379`. Not MK_3_SPEED, not MK_COMBINED, not MOUSEKEY_INERTIA.

| macro | value | evidence | conf. |
|---|---|---|---|
| MK_KINETIC_SPEED | defined | structure above; `const uint16_t mk_*_speed` folded to immediates | verified |
| MOUSEKEY_MOVE_DELTA | **45** (default 16) | `0x08011aba movs r2,#45` (used as `45*t` and `(45*t*t)>>1`) | verified |
| MOUSEKEY_INITIAL_SPEED | **30** (default 100) | `0x08011ac2 adds r0,#30`; `0x08011b00 movs r0,#30` (no-repeat path) | verified |
| MOUSEKEY_BASE_SPEED | **1500** (default 5000) | `0x08011aca movw r3,#1500` (clamp `0x5db <` -> 0x5dc) | verified |
| MOUSEKEY_DECELERATED_SPEED | 400 (default) | `0x08011af4 mov.w r0,#400` (accel bit0) | verified |
| MOUSEKEY_ACCELERATED_SPEED | 3000 (default) | `0x08011afa movw r0,#3000` (accel bit2) | verified |
| MOUSEKEY_MOVE_MAX | 127 (default) | `0x08011aec cmp r0,#127` | verified |
| MOUSEKEY_INTERVAL | **40** (default 10 kinetic) | `.data` `mk_interval` @0x20000EC5 init byte = 0x28 (flash 0x08017A11); `mousekey_on` 0x08011baa `subs r0,#160` = `timer_read() - (MOUSEKEY_INTERVAL << 2)` (`mousekey.c:389`) | verified |
| MOUSEKEY_DELAY | **1** (default 5 kinetic) | `mk_delay = MOUSEKEY_DELAY/10` compiled to 0: variable lives in .bss @0x20002009 (read `DAT_20002009*10` in mousekey_task 0x08011df0), i.e. DELAY in 0..9; dactyl value 1 | likely (value), verified (<10) |
| MOUSEKEY_WHEEL_INITIAL_MOVEMENTS | **64** (default 16) | `wheel_unit` 0x08011b6e `movs r3,#64`; `0x08011b48 add.w r3,r0,#64`; `.data mk_wheel_interval` @0x20000EC2 = 0x000F = 1000/64 (flash 0x08017A0E) | verified |
| MOUSEKEY_WHEEL_BASE_MOVEMENTS | **32** (= default) | `0x08011b34 cmp r3,#32` (`mk_wheel_interval != 32`), `0x08011b52 cmp r3,#32; 0x08011b56 movcs r3,#32` | value verified; presence of the line undecidable (equals the default) |
| MOUSEKEY_WHEEL_ACCELERATED_MOVEMENTS | **50** (default 48) | `0x08011b3c movs r3,#50`, `0x08011b6a movs r3,#50` | verified |
| MOUSEKEY_WHEEL_DECELERATED_MOVEMENTS | 8 (default) | `0x08011b66 movs r3,#8` | verified |
| MOUSEKEY_WHEEL_DELAY | 10 (default) | `.data mk_wheel_delay` @0x20000EC4 = 0x01 = WHEEL_DELAY/10 -> 10..19 | likely |

This is exactly the dactyl kinetic block (`dactyl_reference_summary.md` 804-812: 45 / 30 / 1500 / 40 / 1 / 32 / 64 / 50).

---

## 5. Debounce, matrix, bootmagic, encoder

* **Algorithm sym_eager_pk, DEBOUNCE = 20** [verified]: `debounce` 0x0800ef30 matches `sym_eager_pk.o` (opsim 0.85; counters array, `counters_need_update`/`matrix_need_update`/`cooked_changed` at 0x200016fb/fa/f9, `timer_read32`);
  `transfer_matrix_values` store `*debounce_pointer = DEBOUNCE`: `0x0800efb8 mov.w sl,#20`. `debounce_init` 0x0800eef8: `malloc(num_rows*18)` (MATRIX_COLS 18). Board default (`v10_max/info.json` debounce 20, sym_eager_pk) -- not a user setting.
  Cross-check: `bootmagic_lite` 0x0800ec98 waits `0x0800ec9e mov.w r0,#4000` ticks = 40 ms = `DEBOUNCE*2`.
* **BOOTMAGIC row 0 / col 1** [verified]: `bootmagic_lite`: `matrix_get_row(0)` then bit 1 test (`iVar1 << 0x1e < 0`), then `eeconfig_disable` + `bootloader_jump`. Board default `[0,1]`.
* **ENCODER_MAP_KEY_DELAY 2** [verified]: encoder_read 0x080116d0 `movs r0,#0xc8; bl chThdSleep` (200 ticks = 2 ms) around each `action_exec` (board config).
* **MATRIX_IO_DELAY 10**: board config; `matrix_output_select_delay` 0x0800ed36 matched.

---

## 6. Feature presence (rules.mk) -- from `process_record_quantum` 0x0800d3b6, `quantum_task` 0x0800e7a4, `pre_process_record_quantum` 0x0800d34c, `action_for_keycode` 0x0800e8b0

`process_record_quantum` chain (decompiled/0800d3b6): `process_record_kb (0x0800c6e8) && process_tap_dance (0x08012040) && process_leader (0x080118f4) && process_rgb (0x08011530)`; then, if pressed, `QK_BOOT 0x7c00 -> reset_keyboard`, `QK_REBOOT 0x7c01 -> soft_reset_keyboard`, `QK_CLEAR_EEPROM 0x7c03 -> eeconfig_disable + soft_reset`, `OS_ON/OFF/TOGG 0x7c5a/5b/5c -> oneshot_enable/disable/toggle`; then `process_action_kb`. Ref default has, in addition, `process_space_cadet`, `process_magic`, `process_grave_esc` (ref process_record_quantum 198 B vs 166 B here).

| feature | verdict | evidence |
|---|---|---|
| TAP_DANCE_ENABLE = yes | verified | `process_tap_dance` 0x08012040 (exact), `tap_dance_task` 0x080120d0 called from quantum_task 0x0800e7a4+2, `tap_dance_actions[]` @0x20000E7C (1 entry) |
| LEADER_ENABLE = yes | verified | `process_leader` 0x080118f4, `leader_task` 0x080119dc from quantum_task+6, `leader.o` functions 0x08011940-0x08011a62 |
| MOUSEKEY_ENABLE = yes | verified | `mousekey_task` 0x08011df0 called from keyboard_task 0x0800e7b8; `action_for_keycode` maps 0xCD-0xDF -> `0x5000\|kc` (ACT_MOUSEKEY) |
| EXTRAKEY_ENABLE = yes | verified | `action_for_keycode`: consumer 0xA8-0xC2 via table 0x08016efe -> `0x4400\|usage`, system 0xA5-0xA7 -> `0x4000\|...`; `host_consumer_send` 0x080121b8 |
| NKRO_ENABLE = yes, default off, FORCE_NKRO no | verified | `send_nkro_report` 0x0800e4a4, `host_nkro_send` 0x08012160, `send_nkro` 0x08012bee present; `eeconfig_init_quantum` writes keymap_config 0x1400 (nkro bit 0); `keyboard_init` 0x0800e788 (28 B, exact) has no FORCE_NKRO write; EEPROM log shows keymap_config never rewritten |
| MAGIC_ENABLE = **no** | verified | `process_magic` absent (ref has it, 452 B); not in the process_record_quantum chain (0x0800d3d8/e2/ec/f6 = process_record_kb, process_tap_dance, process_leader, process_rgb only; the ref default build's `nm` lists process_magic/process_grave_esc/process_space_cadet); `builddefs/generic_features.mk:16-19` default all three to yes and no board/common file overrides them. (`action_for_keycode` returning ACTION_NO for 0x7000-0x70FF is true of every build and does not discriminate.) Consequence: `QK_MAGIC_TOGGLE_NKRO` (0x7013) on layers 1/3/4 of the recovered keymap is **inert**; NKRO can never be switched on. (`keycode_config` 0x0800eab4 and `magic()` 0x0800eccc are the always-built `keycode_config.c`/`magic.c`, not MAGIC_ENABLE.) |
| GRAVE_ESC_ENABLE = **no** | verified | `process_grave_esc` absent (ref: 76 B); not in the chain |
| SPACE_CADET_ENABLE = **no** | verified | `process_space_cadet`/`perform_space_cadet` absent (ref: 152+184 B); not in the chain |
| VIA_ENABLE = no | verified | no `process_record_via`, no VIA eeprom layout; `via_command_kb` 0x0800c874 is the fork's always-built raw-HID handler (`keychron_common.c`) |
| COMBO_ENABLE = no | verified | `keyrecord_t` is 8 bytes: waiting_buffer stride `lsl #3` (0x0800e276 `add.w r0,r3,r0,lsl #3`, memcpy 8 at 0x0800e27a/0x0800dfe4), `IS_TAPPING_RECORD` compares only `ldrh [r4,#0]` vs `ldrh [r5,#0]` (0x0800e02a-0x0800e032) not a keycode; `pre_process_record_quantum` 0x0800d34c = `get_record_keycode; pre_process_record_kb` only |
| REPEAT_KEY_ENABLE = no | verified | same 8-byte `keyrecord_t` (no `keycode` field, `action.h:53-55`); no `process_repeat_key` |
| KEY_OVERRIDE_ENABLE = no | verified | `get_mods_for_report` 0x0800e43c has no `suppressed_mods`/`weak_override_mods` (`action_util.c:275-279`); no key_override task in quantum_task |
| CAPS_WORD_ENABLE = no | verified | quantum_task 0x0800e7a4 = tap_dance_task, leader_task, dip_switch_read only; no `process_caps_word` in chain |
| AUTO_SHIFT_ENABLE = no | verified | see 1.5 |
| DYNAMIC_MACRO_ENABLE = no | verified | not in chain (would be first) |
| DYNAMIC_TAPPING_TERM_ENABLE = no | verified | 1.1 |
| SWAP_HANDS_ENABLE = no | verified | `action_for_keycode` has no 0x5600 range; no `process_hand_swap` in action_exec |
| CONSOLE_ENABLE = no, COMMAND_ENABLE = no | verified | no debug/console strings in the image (`strings` finds no "Tapping:", "OVERFLOW", "command"); `print_set_sendchar` 0x0800ec88 / `null_sendchar_func` 0x0800ec84 only; `NO_DEBUG` also evident: `process_record_quantum` lacks `QK_DEBUG_TOGGLE` 0x7c02 |
| SEND_STRING | unused | `send_char`/`send_string_with_delay` absent (gc'd); leader/user code uses `register_code`/`unregister_code` (0x0800d570/0x0800d600) |
| ENCODER_MAP_ENABLE = yes | verified | `encoder_map[6][1][2]` @0x080169a0, `keycode_at_encodermap_location_raw` 0x0800d2a8 (board default) |
| DIP_SWITCH_ENABLE = yes | verified | `dip_switch_read` 0x0801189c (pin A8), `dip_switch_update_kb` 0x0800cd18 = stock `default_layer_set(1 << (active ? 0 : 2))` |
| RAW_ENABLE = yes | verified | `raw_hid_receive` 0x0800c908 -> `via_command_kb` |
| BOOTMAGIC_ENABLE = yes | verified | section 5 |
| RGB_MATRIX_ENABLE = yes | verified | section 7 |
| LK_WIRELESS_ENABLE, FACTORY_TEST_ENABLE (fork) | verified | `process_record_wireless` 0x0800a788, `process_record_factory_test` 0x0800c928 in `process_record_keychron` 0x0800c6a0 |
| LTO_ENABLE = no | verified | section 8 |

`LAYER_STATE_16BIT` [verified]: `layer_state_set` 0x0800dc24 `strh r0,[r3]` to 0x2000162E, `default_layer_state_set` 0x0800dbd0 `strh` to 0x20001630, `layer_state_is` 0x0800dc3c `ldrh`. (This is the QMK default when none of LAYER_STATE_8/16/32BIT is defined, `quantum/action_layer.h:45-46`; neither the board nor the keymap needs to define it.)

---

## 7. RGB matrix settings compiled in

* **RGB_MATRIX_DEFAULT_MODE = 16 = RGB_MATRIX_TYPING_HEATMAP** (user setting) [verified value, likely spelling]:
  `eeconfig_update_rgb_matrix_default` 0x0800fe14: `0x0800fe1c movs r3,#0x41; 0x0800fe1e strb.w r3,[r0],#1` -> `rgb_matrix_config.enable = 1 (bits 0-1), mode = 0x41>>2 = 16`.
  The ref build (no user RGB config) stores `#0x15` at ref 0x0800dec4 = mode 5 = `RGB_MATRIX_CYCLE_LEFT_RIGHT` (the `rgb_matrix.h:81` default). Mode 16 is TYPING_HEATMAP in this board's enumeration: computed from
  `rgb_matrix_effects.inc` order + `v10_max/info.json` animations = {1 SOLID_COLOR, 2 BREATHING, 3 BAND_SPIRAL_VAL, 4 CYCLE_ALL, 5 CYCLE_LEFT_RIGHT, 6 CYCLE_UP_DOWN, 7 RAINBOW_MOVING_CHEVRON, 8 CYCLE_OUT_IN, 9 CYCLE_OUT_IN_DUAL, 10 CYCLE_PINWHEEL, 11 CYCLE_SPIRAL, 12 DUAL_BEACON, 13 RAINBOW_BEACON, 14 JELLYBEAN_RAINDROPS, 15 PIXEL_RAIN, **16 TYPING_HEATMAP**, 17 DIGITAL_RAIN, 18 SOLID_REACTIVE_SIMPLE, 19 SOLID_REACTIVE_MULTIWIDE, 20 SOLID_REACTIVE_MULTINEXUS, 21 SPLASH, 22 SOLID_SPLASH}, EFFECT_MAX 23 -- confirmed by the mode clamp `0x08010d12 cmp r3,#22 / 0x08010d30 movs r3,#22` in `rgb_matrix_mode_eeprom_helper` 0x08010d04, and by `process_rgb_matrix` 0x08010060: `0x0801010a and.w r3,r3,#0xfc; 0x0801010e cmp r3,#0x40` (`mode == 16`) gating `process_rgb_matrix_typing_heatmap` (0x0800fd38).
  `keyboard_post_init_user` 0x0800cf60 additionally calls `default_layer_set(0)` and `rgb_matrix_mode(16)` (`0x0800cf6c movs r0,#16; b.w 0x08010d40`), i.e. the user forced the heatmap both at compile time and at every boot. EEPROM log (eeprom_recovered.md) shows mode 16 throughout.
* **Default HSV = {0, 255, 255}, RGB_MATRIX_MAXIMUM_BRIGHTNESS = 255 (default)** [verified]: `0x0800fe18 ldr r1,=0x08016710; movs r2,#3; bl memcpy` copies rodata `00 ff ff` (hue 0, sat 255, val 255 = `RGB_MATRIX_DEFAULT_VAL` = MAXIMUM_BRIGHTNESS); `rgb_matrix_increase_val_helper` 0x08010e4c saturates `val+16` at 0xff (`if (0xfe < uVar1) uVar1 = 0xff`) -> `RGB_MATRIX_VAL_STEP 16`, max 255.
* **Speed 127, flags 0xFF (defaults)** [verified]: `0x0800fe28 movw r3,#0xff7f; strh r3,[r4,#4]`.
* **RGB_MATRIX_TIMEOUT = RGB_MATRIX_TIMEOUT_INFINITE (board config)** [verified]: `.data rgb_matrix_timeout` @0x20000EAC init = 0xFFFFFFFF (flash 0x080179F8); `rgb_matrix_timeouted` 0x08010fb0 `return rgb_anykey_timer(0x20001f48) > rgb_matrix_timeout(0x20000eac)`.
* **RGB_MATRIX_KEYPRESSES + RGB_MATRIX_FRAMEBUFFER_EFFECTS (board config)** [verified]: `process_rgb_matrix` 0x08010060 computes `led_count` only when `pressed` (decompiled `if (param_3 == 0) uVar6 = 0`), keeps `last_hit_buffer` with `LED_HITS_TO_REMEMBER 8` (`0x08010092 cmp r3,#8; 0x08010096 rsb sl,r4,#8`), and calls the heatmap.
* **RGB_MATRIX_BRIGHTNESS_TURN_OFF_VAL 32 (board config)** [verified]: `rgb_matrix_decrease_val_helper` 0x08010f1c: `if (enabled && val < 0x21) rgb_matrix_toggle_eeprom_helper()`.
* `RGB_MATRIX_LED_COUNT 88`, `DRIVER_COUNT 2`, SPI SNLED27351: board config (driver functions 0x08011200-0x080114b0 matched).

---

## 8. LTO verdict: **not LTO** [verified]

* Image: 931 functions in 59140 B of .text (functions_linkorder.csv; includes a 7.5 KB full-newlib printf cluster 0x08008448-0x0800a1c0 that the nano-newlib refs lack). Reference non-LTO gcc-15 build: 797 functions / 53070 B (feat), 768 / 51364 (default); LTO refs: 404 / 48792 (feat_lto), 387 / 47202 (default_lto).
* 606 dump functions byte-match the non-LTO ref exactly vs 217 against the LTO ref (coverage.txt); the LTO refs' 12 functions >= 512 B (heavy inlining) vs 8 in non-LTO and 10 here.
* Weak hook stubs survive as separate 2-byte `bx lr` functions (`layer_state_set_user` 0x0800dc18, `housekeeping_task_user` 0x0800e768, `matrix_scan_user` 0x0800ed16, `default_layer_state_set_user` 0x0800dbc4, `td0_on_reset` 0x0800cdd8) and are reached by `bl` -- LTO would have inlined/removed them.
* The 27 four-byte `b.w` functions (e.g. `eeconfig_init` 0x0800e6c4 -> `eeconfig_init_quantum`, `keycode_at_keymap_location` 0x0800d2a4 -> `_raw`, `oneshot_mods_changed_user` 0x0800d088 -> 0x0800d010, `chSysTimerHandlerI` 0x08013594) are ordinary `-O2` sibling-call tail thunks; the non-LTO ref has 24 of them, the LTO ref 15. No identical-code folding is involved (GCC does not ICF on this target).
* Per-object link order is preserved (`functions_linkorder.csv` aligns 874/931 functions in object order) -- another non-LTO signature.

---

## 9. Fork/core functions modified by the user?  **None found** -- but the source tree is one commit older than the pinned reference

`wireless_send_nkro` 0x0800a33c (100 B) differs from the 1011db8c8d build (96 B): after `report_buffer_enqueue` (0x0800a37a) the dump executes
`0x0800a37e ldr r3,[r5,#20]; adds r0,r4,#1; blx r3` = `wireless_transport.send_nkro(&report->mods)`. That line was removed by fork commit
0c05eef6cd (2024-06-22, "Fixed macro doesn't work correctly with NKRO"); its parent 8e390f92a2 (2024-06-18) is the newest commit whose
wireless.c has it, and the commit before that (7fbf1e2af2, factory-test UUID command 0x09) is present in the dump. So the firmware was built
from **fork commit 8e390f92a2**, not a user edit. No V10 Max/common source other than wireless.c changed between 8e390f92a2 and 1011db8c8d
(1011db8c8d only adds K11 Max files), so the pinned reference is otherwise exact. A rebuild from 1011db8c8d carries the 0c05eef6cd
wireless-NKRO fix as its only behavioural deviation in stock code.

All Keychron-fork functions with imperfect opcode similarity were checked against the fork source (`qmk-keychron-ref`); every difference is gcc 13.2 vs 15.2 code generation, not a semantic change:

| dump | ref sym | opsim | check |
|---|---|---|---|
| 0x0800c6a0 | process_record_keychron (keychron_task.c:29) | 0.69 | `process_record_wireless && process_record_factory_test && process_record_keychron_kb` -- identical logic |
| 0x0800c702 | rgb_matrix_indicators_kb (keychron_task.c:96) | 0.62 | `if (rgb_matrix_indicators_user()) rgb_matrix_indicators_keychron()` -- identical |
| 0x0800cd38 | keyboard_post_init_kb (v10_max.c:44) | 0.91 | palSetLineMode A10/A9 (`_pal_lld_setgroupmode` 0x08015338 x2), `GPIOB->BSRR=0x1000` (B12 on), `lkbt51_init(0)`, `wireless_init`, `power_on_indicator_timer = timer_read32`, `encoder_cb_init`, tail-call `keyboard_post_init_user` -- identical |
| 0x0800c810 | encoder_cb_init (keychron_common.c:110) | 0.76 | `palEnableLineEvent` B15/B14 both edges (0x08015410 (0x40020400,0xf/0xe,3)), `palSetLineCallback(..., encoder0_pad_cb 0x0800c719)` x2; extra `isCurrentModePrivileged/setBasePriority` guards are the inlined `osalSysLock` of gcc 13 |
| 0x0800cd18 | dip_switch_update_kb (v10_max.c) | -- | stock `default_layer_set(1 << (active ? 0 : 2))`, then `dip_switch_update_user` |
| 0x0800c720 | process_record_keychron_common | 1.00 exact | unmodified (mac_keycode[] 0x0801683c, key_comb_list[] 0x0801682c stock) |
| 0x0800c874 / 0x0800c928 / 0x0800cb90 | via_command_kb / process_record_factory_test / factory_test_rx | 1.00 | unmodified |
| 0x0800a98c-0x0800af5c | lkbt51.o (send_*, set_param 0.53, read, ...) | 0.5-0.9 | sizes within +-4 B of ref, same call graphs; low opsim comes from memset/memcpy inlining and register allocation (gcc 13 vs 15). Not examined instruction by instruction -> **[uncertain: no evidence of modification]** |
| 0x0800b420 / 0x0800b4c4 | indicator_battery_low_backlit_enable (116 vs 128 B) / rgb_matrix_indicators_bt (268 vs 276 B) | 0.73 / 0.88 | same call graphs (8/8, 11/11); size deltas consistent with compiler version. **[uncertain: no evidence of modification]** |

The only non-stock code in the image is the keymap.c region 0x0800CDD8-0x0800D27C (tap dance, leader hooks, OSM helpers, indicator hook, `process_record_user`, `keyboard_post_init_user`, `oneshot_*_changed_user`) plus the tables `keymaps[]`/`encoder_map[]`/`tap_dance_actions[]`. `rgb_matrix_indicators_advanced_user` 0x0800cf74 is a user hook, not a core modification.

---

## 10. Where the dactyl reference and the dump disagree

* `TAPPING_TERM`: dactyl 150 (09bf) / 140 (LM); dump **175**.
* `LEADER_TIMEOUT`: dactyl 600; dump **525**.
* `TAPPING_TERM_PER_KEY`: dactyl 09bf defines it without a `get_tapping_term`; dump does the same (weak default used) -- agrees with 09bf, not LM.
* `MAGIC_ENABLE = no` is carried over from the dactyl rules.mk even though the V10 Max keymap contains `NK_TOGG` (dead key). `dactyl_reference_summary.md` line 839 assumed MAGIC was enabled on the V10 Max -- the dump shows it is **not**.
* `ONESHOT_TIMEOUT`: both off. `ONESHOT_TAP_TOGGLE 2`: both.
* Mouse keys: all seven dactyl kinetic values match the dump (DELAY exact value not recoverable, any 0..9 compiles identically).
* `DEBOUNCE`: dactyl not set (board 5); V10 Max board 20 (not a user define).
* RGB: dactyl used RGBLIGHT layers; the V10 Max sets `RGB_MATRIX_DEFAULT_MODE` to the typing heatmap (16) -- V10-Max-specific.

---

## 11. Open questions

1. Whether `QUICK_TAP_TERM` was written explicitly as 175 or left undefined (identical code).
2. Exact `MOUSEKEY_DELAY` (0..9 all compile to `mk_delay = 0`; dactyl says 1) and `MOUSEKEY_WHEEL_DELAY` (10..19 -> 1; default 10).
3. Whether `RGB_MATRIX_DEFAULT_MODE` was spelled `RGB_MATRIX_TYPING_HEATMAP` or as the literal 16 (same binary).
4. Whether `COMMAND_ENABLE = no` / `CONSOLE_ENABLE = no` / `AUTO_SHIFT_ENABLE = no` were written explicitly (they are the defaults; only MAGIC/GRAVE_ESC/SPACE_CADET = no are provably explicit because the fork defaults them to yes).
5. lkbt51.o / indicator.o low-similarity functions were judged by size + call graph only (section 9).
