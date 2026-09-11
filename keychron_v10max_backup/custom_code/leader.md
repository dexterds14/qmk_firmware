# Leader key -- recovered implementation (Keychron V10 Max, dump_a.bin)

Dump: `/Users/dexter/code/qmk-keychron/keychron_v10max_backup/dump_a.bin` (flash @0x08000000).
Disassembly re-done for this report with
`arm-none-eabi-objdump -D -b binary -m arm -M force-thumb --adjust-vma=0x08000000 --start-address=A --stop-address=B dump_a.bin`
and cross-checked against Ghidra exports in `decompiled/` and the pinned fork source
`/Users/dexter/code/qmk-keychron-ref/quantum/leader.c`, `quantum/process_keycode/process_leader.c`.

Reconstructed code: `custom_code/leader.c`.

## 1. Summary

| Item | Value | Status |
|---|---|---|
| `LEADER_ENABLE` | yes (leader core linked, `process_leader` in the `process_record_quantum` chain) | verified |
| `LEADER_TIMEOUT` | **525 ms** (`movw r3,#0x20d` @0x080119CA; QMK default 300, dactyl 600) | verified |
| `LEADER_PER_KEY_TIMING` | **defined** (`leader_reset_timer` called after each added key @0x0801192A) | verified |
| `LEADER_NO_TIMEOUT` | **not defined** | verified |
| `LEADER_KEY_STRICT_KEY_PROCESSING` | **not defined** (mod-tap / layer-tap reduced to tap key) | verified |
| `leader_start_user` | `rgb_matrix_set_color_all(255, 0, 255)` (magenta), nothing else | verified |
| `leader_end_user` | `rgb_matrix_set_color_all(0, 0, 0)` then 7 **independent `if`** blocks | verified |
| duplicate `KC_F` | both tests reachable; `<LEAD, F>` fires GUI+P, GUI+K **and** GUI+' | verified |
| chords | explicit `register_code`/`unregister_code`, modifier released before the key | verified (bytes) |
| source used `register_code` rather than `tap_code`/`tap_code16` | | likely (see 6) |

## 2. Addresses (all verified from the bytes)

### Leader core (QMK `quantum/leader.c` + `process_leader.c`, compiled unchanged)

| Function | Dump addr | Size | Evidence |
|---|---|---|---|
| `process_leader` | 0x080118F4 | 74 | `movw r3,#0x7c58` (QK_LEADER) @0x08011930; caller `process_record_quantum` 0x0800D3B6 (call graph) |
| `leader_start` | 0x08011940 | 44 | tests `leading`, calls 0x0800CDF4, `timer_read` 0x08012574, `memset(leader_sequence,0,10)` (`movs r2,#10` @0x08011960, tail `b.w memset` 0x08008798) |
| `leader_end` | 0x0801197C | 14 | `strb #0 -> 0x20002008` then `bl 0x0800CDFE` |
| `leader_sequence_active` | 0x08011990 | 6 | `ldrb r0,[0x20002008]` |
| `leader_sequence_add` | 0x0801199C | 26 | `cmp r3,#4` (size < 5), `strh r0,[leader_sequence + size*2]`, `size++` |
| `leader_sequence_timed_out` | 0x080119C0 | 24 | `ldrh leader_time` ; `bl timer_elapsed` 0x0801257E ; `movw r3,#525` ; `ite ls` -> returns `elapsed > 525` |
| `leader_task` | 0x080119DC | 24 | `if (leading && timed_out()) leader_end()` (tail `b.w 0x0801197C`); caller 0x0800E7A4 = `keyboard_task` fragment (calls `tap_dance_task` 0x080120D0, `leader_task`, `dip_switch_read(false)` 0x0801189C -- the exact order of `quantum/keyboard.c` lines ~602-618); 0x0800E7A4 is called from `keyboard_task` 0x0800E7B8 (240 B) |
| `leader_reset_timer` | 0x080119F8 | 12 | `bl timer_read` ; `strh r0,[0x20002006]` |
| `leader_sequence_is` | 0x08011A08 | 46 | five `ldrh`/`cmp` against 0x20001FFC+0,2,4,6,8 |
| `leader_sequence_one_key` | 0x08011A3C | 20 | `leader_sequence_is(kc,0,0,0,0)` |
| `leader_sequence_two_keys` | 0x08011A50 | 18 | `leader_sequence_is(kc1,kc2,0,0,0)` |
| `leader_sequence_three/four/five_keys` | absent | -- | the only callers of 0x08011A08 are 0x08011A3C and 0x08011A50 (call graph) -> garbage-collected, i.e. never used by the keymap |

RAM: `leading` u8 @0x20002008, `leader_time` u16 @0x20002006, `leader_sequence[5]` u16 @0x20001FFC..0x20002005, `leader_sequence_size` u8 @0x20001FFB (literal pool words @0x0801196C..0x08011978, 0x080119B8/BC, 0x08011A38).
No other function in the image references any of these globals (grep of `decompiled/*.c` for `DAT_20002008|DAT_20002006|DAT_20001ffb|DAT_20001ffc|DAT_20001ffe|DAT_2000200[0-4]` hits only the nine leader-core functions). In particular `process_record_user` (0x0800D104) and `rgb_matrix_indicators_advanced_user` (0x0800CF74) do **not** look at the leader state.

### User hooks (keymap.c)

| Function | Dump addr | Size | Caller |
|---|---|---|---|
| `leader_start_user` | 0x0800CDF4 | 10 | `leader_start` @0x08011948 |
| `leader_end_user` | 0x0800CDFE | 354 | `leader_end` @0x08011984 |

Callees of `leader_end_user`: `rgb_matrix_set_color_all` 0x0800FEE4, `leader_sequence_one_key` 0x08011A3C, `leader_sequence_two_keys` 0x08011A50, `register_code` 0x0800D570 (144 B incl. its literal pool = ref 0x90, instruction-identical), `unregister_code` 0x0800D600 (114 B; ref 0x72, exact). Nothing else.

`rgb_matrix_set_color_all` 0x0800FEE4 = `ldr r3,=0x08016F9C (rgb_matrix_driver) ; ldr r3,[r3,#8] ; bx r3` -> `rgb_matrix_driver.set_color_all` = `snled27351_set_color_all` 0x08011378 (loop over 0x58 LEDs calling `snled27351_set_color` 0x08011338). Standard QMK implementation.

## 3. Configuration -- how each define was decided

### `LEADER_TIMEOUT 525` (verified)
```
080119c0: push {r3, lr}
080119c2: ldr  r3, [pc,#20]      ; =0x20002006 leader_time
080119c4: ldrh r0, [r3]
080119c6: bl   0x0801257e        ; timer_elapsed
080119ca: movw r3, #525          ; 0x20d
080119ce: cmp  r0, r3
080119d0: ite  ls
080119d2: movls r0, #0
080119d4: movhi r0, #1           ; return timer_elapsed(leader_time) > 525
080119d6: pop  {r3, pc}
```
Reference source: `return timer_elapsed(leader_time) > LEADER_TIMEOUT;` (leader.c:71). For comparison the reference ELF `refs/ref1011_feat.elf` compiles the default as `cmp.w r0,#300` @0x0800FB26. So `#define LEADER_TIMEOUT 525`.

### `LEADER_PER_KEY_TIMING` defined (verified)
`process_leader` @0x0801191E `bl leader_sequence_add`; `cbnz r0,0x0801192A`; @0x0801192A `bl 0x080119F8` (`leader_reset_timer`) then `b 0x080118FE` -> `return false` (r5 = 0, the `timed_out` result). The reference emits that call only under `#ifdef LEADER_PER_KEY_TIMING` (process_leader.c:36-38). If the add fails (buffer full, 6th key): @0x08011924 `bl leader_end`, `return true`.

### `LEADER_NO_TIMEOUT` not defined (verified)
Two independent checks against leader.c:
* `leader_sequence_add` 0x0801199C is 26 bytes of straight-line `itttt`/`ite` code with **no** call to `timer_read`; the `#if defined(LEADER_NO_TIMEOUT) if (leader_sequence_size == 0) leader_reset_timer();` branch (leader.c:55-59) is absent.
* `leader_sequence_timed_out` 0x080119C0 does **not** read `leader_sequence_size` (0x20001FFB); the `leader_sequence_size > 0 &&` guard (leader.c:69) is absent.

### `LEADER_KEY_STRICT_KEY_PROCESSING` not defined (verified)
```
08011910: sub.w r3, r4, #0x2000
08011914: cmp.w r3, #0x3000
08011918: it    cc
0801191a: uxtbcc r4, r4          ; if 0x2000 <= keycode < 0x5000: keycode &= 0xFF
```
= the `#ifndef LEADER_KEY_STRICT_KEY_PROCESSING` block (process_leader.c:24-30): QK_MOD_TAP (0x2000-0x3FFF) and QK_LAYER_TAP (0x4000-0x4FFF) are reduced to their tap keycode before being added to the sequence (gcc merged the two range tests).

### `LEADER_ENABLE = yes` (verified)
`process_leader` is called from `process_record_quantum` 0x0800D3B6 (call graph) and `leader_task` from the `keyboard_task` fragment 0x0800E7A4, exactly as `quantum/quantum.c:357-358` and `quantum/keyboard.c:609-610` under `#ifdef LEADER_ENABLE`.

## 4. `leader_start_user` @0x0800CDF4 (verified)
```
0800cdf4: movs r2, #255
0800cdf6: movs r1, #0
0800cdf8: mov  r0, r2
0800cdfa: b.w  0x0800fee4        ; rgb_matrix_set_color_all(255, 0, 255)
```
Sets every LED to magenta (r=255, g=0, b=255) and returns. **No RAM store** -- there is no `leader_active` flag in this firmware (the dactyl's `leader_active = 1` / `rgblight_set_layer_state(4,true)` is not present).

Practical note (analysis, not a dump fact): `rgb_matrix_set_color_all` is a buffer-only write into the LED driver's RAM buffer (`snled27351_set_color_all` 0x08011378 loops over 0x58 LEDs, no flush) outside the rgb_matrix render/flush state machine; the running effect (mode 16, enabled) normally overwrites the buffer before the next flush, so the magenta may be entirely invisible. The intent is clear but the visible effect on the real board is probably negligible.

## 5. `leader_end_user` @0x0800CDFE (verified)

Prologue: `movs r2,#0 ; push {r3,lr} ; mov r0,r2 ; mov r1,r2 ; bl rgb_matrix_set_color_all` -> `rgb_matrix_set_color_all(0,0,0)` unconditionally (0x0800CDFE..0x0800CE06).

Then seven tests. Each test's failure branch (`cbz r0, NEXT`) targets the **next test**, and each action block **falls through** into the next test (no `b END` after any block). That is the code shape of seven independent `if` statements. An `if / else if` chain would have emitted an unconditional branch to the epilogue after every action block; there is none. The function epilogue is `pop {r3,pc}` @0x0800CF5E, reached only by the last test's failure branch; the last action block ends in a tail call (`ldmia sp!,{r3,lr}` ; `b.w unregister_code`).

| # | Test (addr) | Sequence after LEAD | Action block (addr range) | Keys sent (order) |
|---|---|---|---|---|
| 1 | `one_key(KC_F=0x09)` @0x0800CE0A, `cbz -> 0x0800CE42` | F | 0x0800CE12..0x0800CE3E | reg LGUI(0xE3), reg P(0x13), unreg LGUI, unreg P, reg LGUI, reg K(0x0E), unreg LGUI, unreg K  => **GUI+P, GUI+K** |
| 2 | `two_keys(KC_A=0x04, KC_Q=0x14)` @0x0800CE42 (`movs r1,#0x14 ; movs r0,#4`), `cbz -> 0x0800CE88` | A, Q | 0x0800CE4C..0x0800CE84 | reg LCTL(0xE0), reg A, unreg LCTL, unreg A, reg/unreg Z(0x1D), reg/unreg Q(0x14), reg/unreg ENTER(0x28) => **Ctrl+A, Z, Q, Enter** (quit minicom) |
| 3 | `one_key(KC_Y=0x1C)` @0x0800CE88, `cbz -> 0x0800CEC0` | Y | 0x0800CE90..0x0800CEBC | reg LCTL, reg X(0x1B), unreg LCTL, unreg X, reg/unreg Y(0x1C), reg/unreg ENTER => **Ctrl+X, Y, Enter** (nano save+quit) |
| 4 | `two_keys(KC_LCTL=0xE0, KC_I=0x0C)` @0x0800CEC0 (`movs r1,#0xc ; movs r0,#0xe0`), `cbz -> 0x0800CEEE` | LCtrl, I | 0x0800CECA..0x0800CEEA | reg LCTL, reg LALT(0xE2), reg I(0x0C), unreg LCTL, unreg LALT, unreg I => **Ctrl+Alt+I** |
| 5 | `one_key(KC_J=0x0D)` @0x0800CEEE, `cbz -> 0x0800CF0E` | J | 0x0800CEF6..0x0800CF0A | reg LGUI, reg P, unreg LGUI, unreg P => **GUI+P** |
| 6 | `one_key(KC_F=0x09)` @0x0800CF0E, `cbz -> 0x0800CF2E` | F | 0x0800CF16..0x0800CF2A | reg LGUI, reg QUOTE(0x34), unreg LGUI, unreg QUOTE => **GUI+'** |
| 7 | `one_key(KC_DEL=0x4C)` @0x0800CF2E, `cbz -> 0x0800CF5E` | Delete | 0x0800CF36..0x0800CF5A | reg LGUI, reg UP(0x52), reg LEFT(0x50), unreg LGUI, unreg UP, unreg LEFT (tail call) => **GUI+Up+Left** |

Keycode values used: 0x04 A, 0x09 F, 0x0C I, 0x0D J, 0x0E K, 0x13 P, 0x14 Q, 0x1B X, 0x1C Y, 0x1D Z, 0x28 ENTER, 0x34 QUOTE, 0x4C DELETE, 0x50 LEFT, 0x52 UP, 0xE0 LCTL, 0xE2 LALT, 0xE3 LGUI (USB HID usage codes = QMK basic keycodes).

### The duplicate `KC_F` test (0x0800CE0A and 0x0800CF0E)
It is **not** an if/else-if ordering artefact and **not** a different arity -- both are `leader_sequence_one_key(KC_F)` (`movs r0,#9 ; bl 0x08011A3C`). Because the blocks are independent `if`s, when the sequence is exactly `<LEAD, F>` block 1 runs (GUI+P, GUI+K), control falls through blocks 2-5 (their tests fail), then block 6 runs (GUI+'), then block 7's test fails and the function returns. Net effect of `LEAD F`: **GUI+P, GUI+K, GUI+'** in that order. Compared with the dactyl (section 7) block 1 is bound to `KC_S` there; on the V10 Max it was bound to `KC_F`, colliding with the "focus left split" binding. Whether this collision was intentional is not decidable from the binary (uncertain); the reconstruction reproduces it faithfully and flags it.

## 6. `register_code`/`unregister_code` vs `tap_code`/`tap_code16`

Verified at the byte level: `leader_end_user` calls only `register_code` (0x0800D570) and `unregister_code` (0x0800D600), and for every chord it releases the **modifier first, then the key** (e.g. 0x0800CE1E unreg LGUI, 0x0800CE24 unreg P). QMK's `tap_code16()` cannot produce this: `register_code16` applies the modifier via `register_weak_mods()`/`register_mods()` (never `register_code(KC_LGUI)`) and `unregister_code16` releases the key first (`quantum/quantum.c` register_code16/unregister_code16). So the chords are explicit register/unregister in source regardless of build options.

For the bare taps (Z, Q, ENTER, Y) the bytes `register_code(x); unregister_code(x)` would also be what LTO-inlined `tap_code(x)` (with `TAP_CODE_DELAY 0`) produces. Evidence that the build was **not** LTO, making explicit calls the likely source form:
* no `tap_code`, `tap_code_delay`, `tap_code16` or `register_code16` function exists in the image -- the only callers of `register_code` are 0x0800C720 (`process_record_keychron_common`), 0x0800CDFE, 0x0800D104 (`process_record_user`), 0x0800D698 (`process_action`);
* `leader_start_user` (10 B) and `leader_end_user` are called once each via `bl` from `leader_start`/`leader_end` instead of being inlined -- with LTO gcc inlines called-once functions across TUs;
* `compare_images.md`: the LTO reference build matches the dump far worse than the non-LTO one (16-B blocks: 13.8 % vs 28.7 %; 64-B: 5.6 % vs 11.4 %).
Rating: **verified** by compile-compare — the in-tree gcc 13.2.1 build of this exact source is masked-identical to the dump for all 13 leader functions, while `tap_code()` taps compile to `bl tap_code` (`tools/leader_variants_check.c`) and the plain non-LTO rebuild keeps both hooks as separate `bl`-called functions like the dump. Only a local macro expanding to `register_code(k); unregister_code(k)` would be indistinguishable (no behavioural difference). Side fact: `tap_code` is absent from the image because `SPACE_CADET_ENABLE = no` removed its only stock caller, `perform_space_cadet`.

## 7. Comparison with the dactyl leader table (`refs/dactyl_reference_summary.md` section 4, LM/09bf)

| Sequence | Dactyl LM / 09bf | V10 Max dump | Match? |
|---|---|---|---|
| S | `tap_code16(LGUI(KC_P)); tap_code16(LGUI(KC_K))` | bound to **F** instead (block 1) | keys same, trigger differs |
| H | `tap_code16(LCTL(KC_H))` | **absent** | dactyl-only |
| C | `tap_code16(LCTL(LSFT(KC_C)))` | **absent** | dactyl-only |
| R | `tap_code(KC_R)` | **absent** | dactyl-only |
| A Q | Ctrl+A, Z, Q, Enter | same keys (explicit register/unregister) | same |
| Y | Ctrl+X, Y, Enter | same keys | same |
| LCTL I | `tap_code16(LCA(KC_I))` | reg LCTL, LALT, I / unreg LCTL, LALT, I | same chord |
| J | `tap_code16(LGUI(KC_P))` | same | same |
| F | `tap_code16(LGUI(KC_QUOT))` | same (block 6) | same |
| DEL | reg LGUI, UP, LEFT; unreg **LEFT, UP, LGUI** | reg LGUI, UP, LEFT; unreg **LGUI, UP, LEFT** | same keys, release order differs |
| control flow | `if / else if` chain | 7 independent `if`s | differs |
| `LEADER_TIMEOUT` | 600 | **525** | differs |
| `LEADER_PER_KEY_TIMING` | defined | defined | same |
| start/end visuals | `leader_active` flag + `rgblight_set_layer_state(4, ...)` | `rgb_matrix_set_color_all(255,0,255)` / `(0,0,0)`, no flag | differs (RGB matrix board) |
| DS "leader-on-TD" intercept in `process_record_user` | DS only | **absent** (`process_record_user` calls no leader function; call graph) | not in 2024 binary |

Dactyl behaviours the dump does NOT contain: H, C and R sequences; the `leader_active` flag; the else-if exclusivity; any three-or-more-key sequence.

## 8. Confidence

Verified (bytes + reference source): all addresses, RAM layout, the 7 sequences and their exact key order, the independent-`if` structure and the double firing of `<LEAD,F>`, `LEADER_TIMEOUT 525`, `LEADER_PER_KEY_TIMING`, absence of `LEADER_NO_TIMEOUT`/`LEADER_KEY_STRICT_KEY_PROCESSING`, the RGB calls and colours, the absence of a leader flag and of any leader use in `process_record_user`/indicators.
Likely: non-LTO build, hence bare taps written as `register_code(x); unregister_code(x)` rather than `tap_code(x)`.
Uncertain: whether the F/F collision and the 525 ms value were intentional; whether the magenta flash was ever visible (effect-dependent).

## 9. Provenance note
`/Users/dexter/code/qmk-keychron/keyboards/keychron/v10_max/ansi_encoder/keymaps/dexter/` (branch HEAD tree) is an **untracked placeholder** created 2026-09-10 21:45 (no git history, `config.h` says "placeholder values until verified", no leader hooks). It is not the lost source and was not used as evidence.
