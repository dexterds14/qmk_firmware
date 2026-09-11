# Keychron V10 Max (ANSI knob) -- recovery of the lost custom firmware from a flash dump

Consolidated evidence document. All facts below were extracted from `dump_a.bin` (flash image, base 0x08000000)
by disassembly (objdump/capstone), Ghidra decompilation, byte/literal scans and compile-and-compare against
reference builds of the Keychron `wireless_playground` fork; nothing is taken from the sibling dactyl keymap
without a matching instruction in the dump. Addresses are flash addresses (file offset = address - 0x08000000).
Detailed per-target reports: `custom_code/*.md`; final deliverable: `RECONSTRUCTION_SPEC.md` (+ `reconstructed_keymap/`).

## 1. Acquisition

- Board: Keychron V10 Max ANSI with encoder, STM32F401xC (256 KB flash, 64 KB RAM), ROM DFU bootloader
  (`0483:df11`, serial 204C33753632, alt 0 `@Internal Flash /0x08000000/04*016Kg,01*064Kg,01*128Kg`).
- Method: dfu-util 0.11, DFU entered with the reset button under the space bar, switch on Cable (`README_DUMP.txt`, `dfu_list.txt`).
- Files: `dump_a.bin` = `dump_c.bin` (two full 256 KB reads, sha256 `21c97cd5...7e56`), `dump_b.bin` (first 64 KB),
  `optbytes.bin` (`ef aa 10 55 ...`: RDP level 0, no read protection).
- Nothing was flashed back; USB/HID was not touched during the analysis.

## 2. Image layout (`triage.md`, `code_anchors_report.txt`)

| flash range | content |
|---|---|
| 0x08000000-0x080001E0 | vector table, 120 entries (16 core + 104 IRQ = ChibiOS STM32F4 layout); SP 0x20000400, Reset 0x0800811D, default handler 0x0800811F |
| 0x080001E0-0x08004000 | zero fill |
| 0x08004000-0x08005000 | emulated EEPROM (QMK wear-levelling, embedded-flash driver, 2048 B logical / 4096 B backing); rest of sector 1 erased |
| 0x08008000-0x08016704 | `.text`, 59140 B, 931 functions (crt0, ChibiOS, QMK, Keychron fork, newlib) |
| 0x08016704-0x0801774C | `.rodata`: `encoder_map` 0x080169A0 (24 B), `keymaps` 0x080169B8 (1296 B), consumer usage table 0x08016EC8, `rgb_matrix_driver` 0x08016F9C, USB descriptors 0x0801713C / 0x08017197 / 0x080171A9, strings (`Keychron V10 Max` 0x0801679B / 0x08017102, build date `2024-07-09-13:57:36` 0x080167AC, newlib path 0x08017674) |
| 0x0801774C-0x08017F04 | `.data` init image (1976 B) -> RAM 0x20000C00-0x200013B8 (crt0 literal triple @0x080080F8); contains `tap_dance_actions` @0x080179C8, `mk_*` @0x08017A0E-11, `rgb_matrix_timeout` @0x080179F8, USB endpoint tables @0x08017A28 / 0x08017C00 |
| 0x08017F04-0x08040000 | erased (0xFF) |

RAM: `.bss` 0x200013B8-0x20004B88 (zero-filled by crt0 0x080080A0-AE). Notable variables: `layer_state` u16 0x2000162E,
`default_layer_state` u16 0x20001630, `oneshot_layer_data` 0x200016A4, `oneshot_locked_mods` 0x200016A5, `oneshot_mods`
0x200016A6, `weak_mods` 0x200016CF, `real_mods` 0x200016D0, `keymap_config` u16 0x200047D4, leader state 0x20001FFB-0x20002008,
tap-dance core state 0x2000201A / 0x2000201C, `tap_dance_actions[]` 0x20000E7C, user statics 0x200015DC-0x200015E9 (section 8).

## 3. Toolchain, base version, build type (`compare_images.md`, `lib_match.md`, `ANALYSIS_functions.md` sections 7-8)

- **Compiler**: Debian/Ubuntu packaged `gcc-arm-none-eabi` 13.2.rel1 (GCC 13.2.1 20231009) with `libnewlib-arm-none-eabi`
  4.4.0.20231231-2, i.e. `apt install gcc-arm-none-eabi` on Ubuntu 24.04. Evidence: the newlib `__FILE__` string
  `../../../../../../newlib/libc/stdlib/rand.c` @0x08017674 is exactly the noble package's; 30 `libc_nano.a` members are
  byte-identical modulo relocations (`strlen`, `memcpy`, `memset`, `_vfprintf_r`, ...); libgcc `__udivmoddi4` @0x08008188
  matches only the 13.2.rel1 `libgcc.a`; a same-source rebuild with xPack 13.2.1 matches 507 functions exactly vs 356 for gcc 15.2.
  Neither official Keychron image (GCC 10 Jenkins builds, `refs/official/`) nor the QMK-toolchain gcc 15.2 reproduce the string.
- **Not LTO**: 931 small functions (median 32 B), weak `bx lr` hooks reached via `bl`, 27 four-byte `b.w` sibling-call thunks,
  per-object link order preserved for 874/931 functions; 606 exact matches to the non-LTO reference vs 217 to the LTO one.
- **Base**: Keychron `wireless_playground` fork, **commit 8e390f92a2 (2024-06-18)** = pinned reference 1011db8c8d minus 0c05eef6cd.
  Proof: `wireless_send_nkro` 0x0800A33C still contains the direct `wireless_transport.send_nkro(&report->mods)` call
  (0x0800A37E `ldr r3,[r5,#20]; adds r0,r4,#1; blx r3`) that 0c05eef6cd (2024-06-22) removed, while `factory_test_rx` has the
  device-UUID command 0x09 added by 7fbf1e2af2. Every other fork/core function is instruction-identical to a 1011db8c8d build
  (compile-compare, section 12). QMK 0.23.2 era: 8-byte `keyrecord_t`, `LAYER_STATE_16BIT`, leader.c with `leader_sequence_*`.
- **Build date** 2024-07-09 13:57:36 (string @0x080167AC, also returned by raw-HID 0xA1 / 0xAB 0x08). USB VID 0x3434 PID 0x09A0
  bcdDevice 0x0100 (`v1.0.0`).
- **User code**: exactly one non-stock translation unit, the keymap TU 0x0800CDD8-0x0800D2CC (plus `keymaps[]`, `encoder_map[]`,
  `tap_dance_actions[]`). No fork or core function was modified by the user (every low-similarity Keychron function was checked
  against the fork source; the differences are gcc 13 vs 15 codegen).

## 4. Tables

### 4.1 keymaps[] @0x080169B8 (6 layers x 6 rows x 18 cols u16, `LAYOUT_ansi_89`)

Decoded in `keymap_recovered.md` (per-layer grids), `keymap_recovered.json`, `keymap_recovered_table.c`; round-trip verified
(a rebuild of the table is byte-identical). Layer roles (names are the author's dactyl names):

| layer | role | distinctive keys |
|---|---|---|
| 0 `_QWERTY` | base | `OSL(5)` left of 1, `OSM(MOD_LSFT)` at Caps, `OSM(MOD_RSFT)` at `'`, `KC_CAPS` at left Option, `OSM(MOD_LGUI)` at left Cmd, `TD(0)` at Fn, `OSL(2)` at right Cmd, `KC_TAB` at left Shift, `KC_BSPC` at the B duplicate, Keychron `MC_2..MC_5` macro column |
| 1 `_LOWER` | Ctrl chords / navigation | `LCTL(x)` letters, arrows on J K L ;, `LALT(KC_GRAVE)`, `LALT(KC_TAB)`, `LSFT(KC_TAB)`, `DOT_SLS` `DIR_UP` on , ., `KC_F4` at G, `NK_TOGG`, `TD(0)`, `TO(0)`, `RGB_TOG`, F-row |
| 2 `_RAISE` | symbols / F-keys | shifted symbols, `KC_PSCR`, media, `TO(3)`, `TO(0)` |
| 3 `_RAISE2` | Keychron Fn | `QK_BOOT` (Esc), `BT_HST1-3`, `P2P4G`, RGB keys, `BAT_LVL`, `NK_TOGG`, `TO(2)`, `TO(0)` |
| 4 `_MOUSE` | mouse keys | `KC_MS_*` on Caps/A/S/D/F and J/K/L/;, wheel on C/V, BT hosts, `TD(0)`, `TO(0)`, `OSL(5)` |
| 5 `_LEADR` | leader / chords | `QK_LEADER` (grave), `LALT(KC_F4)`, `LCTL(LSFT(x))` chords, `LALT(arrows)`, `DOT_SLS`, `TO(0)`, `TO(5)` |

Non-basic keycodes present: `MC_1..MC_5` (0x7701-05), `OSL(2/5)`, `OSM(MOD_LSFT/LGUI/RSFT)`, `TD(0)` 0x5700, `TO(0/2/3/5)`,
`QK_USER_0/1` 0x7E40/41, `NK_TOGG` 0x7013, `QK_BOOT` 0x7C00, `QK_LEADER` 0x7C58, Keychron `BT_HST1-3` / `P2P4G` / `BAT_LVL` / `KC_TASK` / `KC_FILE`.

### 4.2 encoder_map[6][1][2] @0x080169A0

Index 0 = clockwise, index 1 = counter-clockwise (`ENCODER_CCW_CW(ccw, cw)` stores `{cw, ccw}`):
L0 `{KC_VOLU, KC_VOLD}`, L1 `{RGB_VAI, RGB_VAD}`, L2 `{KC_VOLU, KC_VOLD}`, L3 `{KC_NO, KC_NO}`, L4 `{KC_NO, KC_NO}`, L5 `{RGB_VAI, RGB_VAD}`.
Reader: `keycode_at_encodermap_location_raw` 0x0800D2A8 (literal 0x080169A0, `cmp r0,#5`, `eor r2,#1`). No `encoder_update_user`.

### 4.3 tap_dance_actions[] (init image 0x080179C8 -> RAM 0x20000E7C)

One 28-byte entry: `{state 0, on_each_tap NULL, on_dance_finished 0x0800D1ED, on_reset 0x0800CDD9, on_each_release NULL, user_data NULL}`
= `ACTION_TAP_DANCE_FN_ADVANCED(NULL, layr_dn_finished, layr_dn_reset)`. `user_data` is never written (no literal in
0x20000E80..0x20000E97 anywhere in flash; 0x20000E98 is the next `.data` object).

## 5. EEPROM state at dump time (`eeprom_recovered.md`, oracle-verified against the fork's wear_leveling.c)

- Wear-levelling image valid (FNV-1a-64 hash matches); consolidated image + 92 log entries, all 8-byte `rgb_matrix_config` flushes.
- `magic` 0xFEE6; `debug` 0; `default_layer` 0x01 (layer 0); `keymap_config` 0x1400 (oneshot_enable + autocorrect_enable, **nkro 0**);
  `rgb_matrix`: enable 1, **mode 16** (typing heatmap), hue 8, sat 239, val 47, speed 191, flags 0xFF. Keychron KB data all zero
  (language 0, wireless timeouts -> defaults 600 s / 7200 s). No VIA / dynamic-keymap blob (bytes 64..2047 zero).
- The log shows the user stepping brightness (RGB_VAD/VAI in steps of 16, including three auto-off/on crossings at val 32), speed and
  finally hue; the mode never changed. hue/sat/val/speed are runtime adjustments, not compiled defaults (compiled: 0/255/255/127).

## 6. Custom code -- every function in the keymap TU (0x0800CDD8-0x0800D2CC)

| address | size | function (reconstructed name) | behaviour | key evidence |
|---|---|---|---|---|
| 0x0800CDD8 | 2 | `layr_dn_reset` (`tap_dance_actions[0].fn.on_reset`) | empty (`bx lr`) -> the hold result (mouse layer) is sticky | pointer 0x0800CDD9 @0x080179D8; a store to a write-only static compiles to the same `bx lr` |
| 0x0800CDDA | 26 | `layer_oneshot_Lower` (static) | `layer_on(1); set_oneshot_layer(1, ONESHOT_START); clear_oneshot_layer_state(ONESHOT_PRESSED)` | `movs r0,#1; bl 0x0800DC64`; `movs r1,#3; bl 0x0800E504`; `movs r0,#1; b.w 0x0800E548` |
| 0x0800CDF4 | 10 | `leader_start_user` | `rgb_matrix_set_color_all(255,0,255)`, no flag | `movs r2,#255; movs r1,#0; mov r0,r2; b.w 0x0800FEE4`; caller `leader_start` 0x08011948 |
| 0x0800CDFE | 354 | `leader_end_user` | black, then 7 **independent** `if`s: F -> GUI+P, GUI+K; A,Q -> Ctrl+A, Z, Q, Enter; Y -> Ctrl+X, Y, Enter; LCtl,I -> Ctrl+Alt+I; J -> GUI+P; F -> GUI+'; Del -> GUI+Up+Left; all via `register_code` / `unregister_code`, modifier released first | tests at 0x0800CE0A / CE42 / CE88 / CEC0 / CEEE / CF0E / CF2E, each `cbz` -> next test, no `b END`, single epilogue 0x0800CF5E; `leader_sequence_one_key` 0x08011A3C, `two_keys` 0x08011A50 |
| 0x0800CF60 | 20 | `keyboard_post_init_user` | `default_layer_set(0); rgb_matrix_mode(16)` (EEPROM-writing variant) | `movs r0,#0; bl 0x0800DBE2`; `movs r0,#16; b.w 0x08010D40` (= `movs r1,#1; b.w rgb_matrix_mode_eeprom_helper`); tail-called from `keyboard_post_init_kb` 0x0800CD76 |
| 0x0800CF74 | 156 | `rgb_matrix_indicators_advanced_user` | per LED in [led_min,led_max): layer colour of `get_highest_layer(layer_state\|default_layer_state)` (1 green, 2 blue, 3 orange, 4 teal, 5 red), then `gui_active` -> yellow else `shift_active\|\|caps_active` -> white; returns false | `ldrh 0x2000162E \| ldrh 0x20001630; bl biton16 0x0800D488; subs #1; cmp #4; tbb` table `18 03 14 1B 1E`; colours at 0x0800CFAC / CFCE / CFD6 / CFDC / CFE2; flags 0x200015DD / DE / DC; called 5x per frame (18-LED chunks) from stock `rgb_matrix_indicators_advanced_kb` 0x08010C4C |
| 0x0800D010 | 120 | `handle_oneshots` (static) | `if(!S&&s){off;s=0} else if(!G&&g){off;g=0}; if(S&&!s){white;s=1}; if(G&&!g){yellow;g=1}` with S = `mods&0x22`, G = `mods&0x88` | `ands r5,r0,#0x22; bic r4,r0,#0x77`; `set_color_all` calls 0x0800D028 / D03A / D056 / D06E; decision table verified for all 16 inputs (`tools/sim_handle_oneshots.py`) |
| 0x0800D088 / 0x0800D08C | 4 / 4 | `oneshot_mods_changed_user` / `oneshot_locked_mods_changed_user` | `b.w 0x0800D010` (sibling calls) | callers `oneshot_mods_changed_kb` 0x0800E3E4 (var 0x200016A6) / `oneshot_locked_mods_changed_kb` 0x0800E38C (var 0x200016A5) |
| 0x0800D090 | 36 | `find_osm_slot` | walks `held_osm[]` through pointer 0x200015E0 with a 4-byte stride (the source's `index += sizeof(uint16_t)`), probes `*(uint16_t*)4` when NULL; always returns NULL here | `ldr r0,[0x200015E0]; cbz -> movs r2,#4; ldrh r1,[r0,#4]`; word at 0x00000004 = 0x0800811D |
| 0x0800D0B4 | 80 | `check_unlock_osm` | slot NULL -> true; else get_mods / `*slot!=kc` -> clear one-shot mods + locked mods, `unregister_mods(get_oneshot_mods())`, zero `held_osm[]`, `shift_active`, `gui_active`, false. **Inert**: `held_osm[]` is only ever zeroed | `bl 0x0800E424 / E3B0 / E380 / D684`; `str 0 [0x200015E0],[+4]`; literals of 0x200015E0 only at 0x0800D0B0 / 0x0800D0F8 |
| 0x0800D104 | 192 | `process_record_user` | `process_record_keychron_common` first (false -> false); clear `move_to_lower` unless keycode == TD(0); clear `return_to_mouse` unless `layer_state_is(1)`; on press: 4 OSM keys -> `check_unlock_osm`; `KC_CAPS` -> `caps_active` = !host caps LED; 0x7E40 -> `./` false; 0x7E41 -> `../` false; else true | `bl 0x0800C720`; `cmp.w r4,#0x5700`; `bl layer_state_is(1)`; `ldrb [r6,#5]`; OSM mask `sub #0x5280; subs #0x22; cmp #22; mov.w r2,#0x410041` (bits 0,6,16,22 = 0x52A2/A8/B2/B8); `bl host_keyboard_led_state 0x08012148; lsls #30`; `movw #0x7E40 / #0x7E41`; `register_code` 0x0800D570 / `unregister_code` 0x0800D600 with 0x37 / 0x38 |
| 0x0800D1C4 | 40 | `cur_dance` | count==1: !pressed -> 2, !interrupted -> 3, else 1; count==2 -> 4; else 1 (no triple-tap value) | `ldrb [r0,#2]; cmp #1; ldrb [r0,#5]; lsls #31; tst #4; ite eq; moveq #3; movne #1; cmp #2; moveq #4; movne #1` |
| 0x0800D1EC | 112 | `layr_dn_finished` (`fn.on_dance_finished`) | 3 (hold) -> `layer_clear(); layer_move(4)`; 4 (double) -> `layer_clear(); layer_move(1)`; 2 (tap): on layer 4 -> `return_to_mouse=1; layer_clear(); layer_oneshot_Lower()`; else `move_to_lower` -> lock layer 1, clear flag; else layer 1 active -> `layer_clear(); layer_oneshot_Lower()`; else `move_to_lower=1; layer_oneshot_Lower()`; 1 -> nothing; `user_data` never read | `bl 0x0800D1C4; cmp #3 beq 0x0800D23E; cmp #4 beq 0x0800D24C; cmp #2 bne pop`; `layer_state_is` 0x0800DC3C, `layer_clear` 0x0800DC34, `layer_move` 0x0800DC58; flag stores 0x0800D20C / D22A / D23A |
| 0x0800D25C | 32 | `oneshot_layer_changed_user` | `if (layer==0 && return_to_mouse) { layer_clear(); layer_move(4); return_to_mouse=0; }` | `cbnz r0; ldr r5,=0x200015E9; ldrb; cbz; bl layer_clear; movs r0,#4; bl layer_move; strb r4,[r5]`; sole callee of `oneshot_layer_changed_kb` 0x0800E4FC |
| 0x0800D27C / 0x0800D2A4 | 40 / 4 | `keycode_at_keymap_location_raw` / wrapper | bounds 6/6/18, stride 108 u16, literal `keymaps` 0x080169B8 | keymap_introspection.c compiled into the keymap TU |
| 0x0800D2A8 / 0x0800D2C8 | 32 / 4 | `keycode_at_encodermap_location_raw` / wrapper | 6 layers, 1 encoder, literal 0x080169A0 | " |

Stock weak defaults confirmed **not** implemented by the keymap: `layer_state_set_user` 0x0800DC18, `default_layer_state_set_user`
0x0800DBC4, `housekeeping_task_user` 0x0800E768, `matrix_scan_user` 0x0800ED16, `rgb_matrix_indicators_user` 0x0801017A,
`led_update_user` 0x0800D4B2, `pre_process_record_user` 0x0800D2CC, `post_process_record_user` 0x0800D2DC, `eeconfig_init_user`
0x0800E61E, `get_tapping_term` 0x0800DEFC (weak default in action_tapping.o), `raw_hid_receive` 0x0800C908 (fork's non-VIA
variant), `dip_switch_update_user` 0x0800CCF0 (fork's factory_test.c). Keychron glue (`process_record_kb` 0x0800C6E8 calls
`process_record_user` first; `keychron_task` 0x0800C6D4; `rgb_matrix_indicators_kb` 0x0800C702 with the LED-48 caps indicator
via `os_state_indicate` 0x0800B494; `keyboard_post_init_kb` 0x0800CD38; `dip_switch_update_kb` 0x0800CD18) is stock and in stock order.

## 7. Core code paths that shape the behaviour (all stock, all matched)

- `process_record_quantum` 0x0800D3B6: `process_record_kb` -> `process_tap_dance` -> `process_leader` -> `process_rgb` -> QK_BOOT /
  REBOOT / CLEAR_EEPROM / OS_ON / OFF / TOGG -> `process_action_kb`. No magic, grave-esc, space-cadet, combo, key-override, caps-word,
  dynamic-macro, repeat-key, auto-shift.
- `quantum_task` 0x0800E7A4: `tap_dance_task` 0x080120D0, `leader_task` 0x080119DC, `dip_switch_read`.
- `process_action` 0x0800D698 (1010 B): ONESHOT_TAP_TOGGLE 2 paths, TAPPING_TOGGLE 5, `TAP_HOLD_CAPS_DELAY 80` / `TAP_CODE_DELAY 0`
  (`chThdSleep(KC_CAPS ? 8000 : 1)` at the 100 kHz tick).
- `process_tapping` 0x0800DF94 / `waiting_buffer_scan_tap` 0x0800DF00 / `tap_dance_task`: call `get_tapping_term` 0x0800DEFC (= 175)
  four times; `QUICK_TAP_TERM` inline `cmp r7,#174`; no PERMISSIVE_HOLD / HOLD_ON_OTHER_KEY_PRESS / RETRO_TAPPING code.
- Leader core 0x080118F4-0x08011A61 (`leader_reset_timer` present = per-key timing, timeout `movw #525`, MT/LT reduced to the tap key).
- Mouse keys: kinetic `move_unit` 0x08011A8C / `wheel_unit` 0x08011B14; `.data` `mk_interval` 40, `mk_wheel_interval` 15, `mk_wheel_delay` 1.
- RGB: `eeconfig_update_rgb_matrix_default` 0x0800FE14 stores mode 16 (0x41), HSV 0/255/255, speed 127, flags 0xFF; `rgb_task_render`
  0x08010A4C has 23 effects (clamp `cmp #22`), case 16 = typing heatmap 0x08010920; `RGB_MATRIX_LED_PROCESS_LIMIT` 18 (5 chunks of 88 LEDs);
  `rgb_matrix_timeout` infinite; `BRIGHTNESS_TURN_OFF_VAL` 32; `CAPS_LOCK_INDEX` 48.
- Debounce `sym_eager_pk`, `DEBOUNCE` 20 (0x0800EFB8); bootmagic row 0 col 1; `ENCODER_MAP_KEY_DELAY` 2.
- NKRO code linked, default off (`keymap_config` 0x1400 written by `eeconfig_init_quantum` 0x0800E658), un-toggleable (no `process_magic`).

## 8. User statics (.bss, zero at boot)

| RAM | name | written by | read by |
|---|---|---|---|
| 0x200015DC | `caps_active` u8 | `process_record_user` (KC_CAPS press, from the host LED state) | indicator hook |
| 0x200015DD | `gui_active` u8 | `handle_oneshots`; zeroed by `check_unlock_osm` | `handle_oneshots`, indicator hook |
| 0x200015DE | `shift_active` u8 | `handle_oneshots`; zeroed by `check_unlock_osm` | `handle_oneshots`, indicator hook |
| 0x200015E0/E4 | `held_osm[2]` (uint16_t*) | zeroed by `check_unlock_osm` only | `find_osm_slot` |
| 0x200015E8 | `move_to_lower` u8 | `layr_dn_finished` (=1 first tap, =0 after lock); cleared by `process_record_user` for any non-TD(0) event | `layr_dn_finished` |
| 0x200015E9 | `return_to_mouse` u8 | `layr_dn_finished` (=1 on layer 4); cleared by `oneshot_layer_changed_user` and by `process_record_user` when layer 1 is off | `oneshot_layer_changed_user` |

Ascending addresses = reverse declaration order (GCC), hence the source declared `return_to_mouse, move_to_lower, held_osm[],
shift_active, gui_active, caps_active` (the dactyl LM order). Whole-flash literal scans show no other function references these bytes.

## 9. Configuration constants (keymap level; board settings excluded)

| define | value | evidence |
|---|---|---|
| `TAPPING_TERM` | 175 | 0x0800DEFC `movs r0,#175; bx lr`; 0x0800E1B4 `cmp r7,#174` |
| `TAPPING_TERM_PER_KEY` | defined | `get_tapping_term` called (0x0800DF52, 0x0800E016, 0x0800E192, 0x080120EC) instead of an immediate; weak default body, no override |
| `ONESHOT_TAP_TOGGLE` | 2 | 0x0800D824 `cmp r8,#1` / 0x0800D832 `cmp r8,#2` (MODS_ONESHOT), 0x0800DA46 / 0x0800DA60 (OP_ONESHOT); no QMK default exists |
| `ONESHOT_TIMEOUT` | not defined | no `timer_read` in `set_oneshot_layer` 0x0800E504 / `add_oneshot_mods` 0x0800E3EC; no `has_oneshot_*_timed_out` |
| `LEADER_PER_KEY_TIMING` | defined | 0x0801192A `bl leader_reset_timer` |
| `LEADER_TIMEOUT` | 525 | 0x080119CA `movw r3,#0x20d` |
| `LEADER_NO_TIMEOUT`, `LEADER_KEY_STRICT_KEY_PROCESSING` | not defined | `leader_sequence_add` has no timer reset; 0x08011910 `sub.w r3,r4,#0x2000; cmp.w r3,#0x3000; it cc; uxtbcc r4,r4` |
| `MK_KINETIC_SPEED` + `MOUSEKEY_MOVE_DELTA 45`, `INITIAL_SPEED 30`, `BASE_SPEED 1500`, `INTERVAL 40`, `WHEEL_INITIAL_MOVEMENTS 64`, `WHEEL_ACCELERATED_MOVEMENTS 50` | as listed | 0x08011ABA / AC2 / ACA, `.data` 0x08017A11 = 0x28, 0x08011B6E / B48, 0x08011B3C / B6A |
| `MOUSEKEY_DELAY` | 0..9 (dactyl 1) | `mk_delay` in .bss 0x20002009 |
| `MOUSEKEY_WHEEL_BASE_MOVEMENTS` | 32 (= default) | 0x08011B34 / B52 |
| `RGB_MATRIX_DEFAULT_MODE` | 16 = `RGB_MATRIX_TYPING_HEATMAP` | 0x0800FE1C `movs r3,#0x41` (stock builds: 0x15) |
| `PERMISSIVE_HOLD`, `HOLD_ON_OTHER_KEY_PRESS`, `RETRO_TAPPING`, `QUICK_TAP_TERM`, `TAPPING_TOGGLE`, `FORCE_NKRO`, `DEBOUNCE`, RGB HSV/SPD defaults | not defined / default | `process_tapping` 0x0800E062-0x0800E0D6, `action_exec` 0x0800D50C, 0x0800D9E2 / D9F4, `keyboard_init` 0x0800E788, board `info.json` |

## 10. Features (rules.mk)

On, keymap level: `TAP_DANCE_ENABLE`, `LEADER_ENABLE`, `MOUSEKEY_ENABLE`. Off although the fork defaults them on: `MAGIC_ENABLE`,
`GRAVE_ESC_ENABLE`, `SPACE_CADET_ENABLE` (functions absent, `process_record_quantum` chain short, only four `get_tapping_term` callers).
Off: `VIA_ENABLE`, `LTO_ENABLE`, `CONSOLE_ENABLE`, `COMMAND_ENABLE`, `COMBO`, `KEY_OVERRIDE`, `CAPS_WORD`, `AUTO_SHIFT`, `DYNAMIC_MACRO`,
`REPEAT_KEY`, `SWAP_HANDS`, `DYNAMIC_TAPPING_TERM`. Board/fork features present: encoder + `ENCODER_MAP`, `DIP_SWITCH`, `NKRO`,
`EXTRAKEY`, `BOOTMAGIC`, `RGB_MATRIX` (SNLED27351 SPI, 88 LEDs), `RAW`, wear-levelling EEPROM, `LK_WIRELESS_ENABLE`
(`NO_USB_STARTUP_CHECK`), `FACTORY_TEST_ENABLE`, BT-module DFU over raw HID 0xAA.

## 11. Raw HID conclusion (`custom_code/rawhid_misc.md`)

The firmware services raw HID correctly (EP2 IN/OUT 32 B, `raw_hid_task` 0x08012C1C polled every main-loop iteration,
OUT endpoint armed at configuration and re-armed after each packet), but `raw_hid_receive` 0x0800C908 -- byte-identical to
the fork's non-VIA `keychron_common.c` -- forwards only `data[0]` in {0xAA, 0xAB} (`subs r3,#0xAA; cmp r3,#1; bhi ret`),
because `RAW_HID_CMD` is `0xAA ... 0xAB` and `VIA_ENABLE` is off. Hence 0xA0..0xA3 (Keychron launcher protocol) and all VIA ids
are dropped silently -- firmware-side, by design, not a host failure. The board does answer factory-test packets
`0xAB <cmd> ... <cksum16 of bytes 1..28 at 30/31>` for cmd 0x05 (transport), 0x08 (build time "v1.0.0 2024-07-09-13:57:36"),
0x09 (12-byte UID); probe script `tools/rawhid_probe.py` (not executed). No user raw-HID code exists; the keymap must not
define `raw_hid_receive` (duplicate symbol).

## 12. Verification performed

- Per-target reconstructions (`custom_code/{tapdance,process_record_user,leader,rgb_hooks,config_features,rawhid_misc}.md/.c`)
  each reviewed by three independent verifiers; no target refuted; all issues resolved (list in `RECONSTRUCTION_SPEC.md` section 1).
- Standalone recompiles (`tools/tapdance_recompile_check.c`, `tools/rgb_hooks_recompile_check.sh`, `tools/leader_variants_check.c`,
  `tools/rgb_hooks_spelling_search.py`) excluded alternative source forms (else-if leader chain, `tap_code()` / `tap_code16()`,
  `bool` flags, other switch orders, the dactyl `handle_oneshots` chain).
- Per-target in-tree compiles with gcc 13.2.1: `refs/ref1011_leader_verify_gcc13.*`, `refs/ref1011_config_verify_gcc13.*`.
- **Final**: the complete `reconstructed_keymap/{keymap.c,config.h,rules.mk}` compiled in-tree with gcc 13.2.1 via QMK's userspace
  overlay (`refs/ref1011_dexter_final_gcc13.{elf,map,bin}`) and compared by `tools/final_compile_compare.py`: all 17 user functions
  masked-identical, both tables byte-identical, tap-dance table shape identical, .bss layout identical, 41 config-bearing core
  functions masked-identical; the whole-image sweep leaves only newlib, `wireless_send_nkro` (fork revision) and two jump-table
  functions unmatched.

## 13. Open questions / unrecoverable

- Names, comments, formatting and function order of the original source; `switch` vs `if` chains; `||` vs `|`; whether the two
  one-shot hooks shared a helper; whether `layr_dn_reset` stored to a write-only static; exact `MOUSEKEY_DELAY` (0..9) and
  `MOUSEKEY_WHEEL_DELAY` (10..19); whether `QUICK_TAP_TERM`, `MOUSEKEY_WHEEL_BASE_MOVEMENTS`, `CONSOLE/COMMAND_ENABLE = no` were
  written explicitly; spelling / location of `RGB_MATRIX_DEFAULT_MODE`.
- Intent behind the double `KC_F` leader binding (GUI+P, GUI+K, GUI+' on one sequence), `LEADER_TIMEOUT 525` (dactyl uses 600),
  the inert OSM unlock block, and `NK_TOGG` keys under `MAGIC_ENABLE = no`.
- Exact Debian package revision of the toolchain (13.2.rel1-1 vs -2) and host distribution.
- Host side: whether the user's raw-HID tooling selected the right interface (usage page 0xFF60 / usage 0x61); the 0xAB probes decide it.
- lkbt51.o / indicator.o functions with 0.5-0.9 opcode similarity were judged unmodified by size and call graph only (all other stock
  code is instruction-identical after masking).

## 14. File index (`keychron_v10max_backup/`)

- `dump_a.bin`, `dump_b.bin`, `dump_c.bin`, `optbytes.bin`, `sha256.txt`, `README_DUMP.txt`, `dfu_list.txt` -- acquisition.
- `triage.md/.json`, `strings_classified.md/.json`, `compare_images.md/.json`, `lib_match.md/.json`, `calibration.txt`, `coverage.txt`
  -- image triage, toolchain identification, matcher calibration.
- `keymap_recovered.{md,json,_table.c}`, `eeprom_recovered.{md,json}` -- tables and EEPROM.
- `code_anchors_report.txt/.json`, `dump_symbols*.{json,txt}`, `functions_matched.csv`, `functions_linkorder*.csv/json`,
  `functions_final.csv`, `functions_final_stats.json`, `hooks.csv`, `hooks_final.json`, `ANALYSIS_functions.md`, `unmatched_regions.csv`,
  `libc_members_placed.json`, `custom_region_0800CDD8.asm`, `disasm/`, `decompiled/` (903 Ghidra decompiles), `ghidra_*` -- function map.
- `custom_code/` -- per-target evidence reports and reconstructed C; `reconstructed_keymap/` -- the final three files;
  `RECONSTRUCTION_SPEC.md` -- the deliverable.
- `refs/` -- reference ELF/map/bin builds (`ref1011_*`), official Keychron images, dactyl reference summary, toolchain notes.
- `tools/` -- all scripts (decoders, matchers, Ghidra runner, recompile checks, `final_compile_compare.py`, `rawhid_probe.py`).
