# TD(0) tap dance state machine — Keychron V10 Max custom firmware

Source of truth: `dump_a.bin` (flash @0x08000000). Reference sources: pinned Keychron fork
`/Users/dexter/code/qmk-keychron-ref` (QMK 0.23.2 era). Reconstructed code:
`custom_code/tapdance.c`. Recompile check: `tools/tapdance_recompile_check.c`.

## 0. Bottom line

`TD(0)` (0x5700, the Fn key at row 5 / col 7 of layers 0, 1 and 4 — `keymap_recovered.md`) is a
port of the dactyl `LAYR_DOWN` dance with the **gestures shifted one step down**:

| Gesture on Fn (as compiled) | cur_dance value | Effect |
|---|---|---|
| single tap (count==1, released; interrupted or not) | 2 | one-shot **layer 1** (LCTL/arrows "lower") with the `move_to_lower` / `return_to_mouse` bookkeeping (see §3) |
| single tap again with no other key event in between (flag `move_to_lower` still set) | 2 | **lock layer 1**: `layer_clear(); layer_move(1)` |
| single tap while layer 1 is already the locked layer | 2 | `layer_clear()` then one-shot layer 1 (unlocks into a one-shot) |
| single tap while layer 4 (mouse) is active | 2 | `return_to_mouse=1; layer_clear();` one-shot layer 1; when the one-shot ends `oneshot_layer_changed_user(0)` moves back to layer 4 |
| hold ≥ TAPPING_TERM, no other key pressed | 3 | `layer_clear(); layer_move(4)` — **sticky mouse layer** (nothing is done on release) |
| hold, another key pressed while still held (interrupted) | 1 | nothing |
| double tap (count==2, any pressed/interrupted state) | 4 | **lock layer 1**: `layer_clear(); layer_move(1)` |
| triple or more taps | 1 | nothing (no triple-tap state exists in this build) |

Timing: `TAPPING_TERM = 175` ms, `TAPPING_TERM_PER_KEY` defined, no per-key differentiation,
`ONESHOT_TIMEOUT` not defined. `on_reset` is an empty function. `user_data` is NULL and never read.

Compiled in-tree with the dump's compiler (gcc 13.2.1, QMK flags) as part of the final keymap
(`reconstructed_keymap/keymap.c`), all five functions are **masked-identical** to the dump -- same
instructions, register allocation and branch offsets; only BL/B.W displacements and literal-pool
addresses differ (`tools/final_compile_compare.py`). The earlier standalone gcc 15.2 `-Os` check
(`tools/tapdance_recompile_check.c`) gives the same control flow, calls and stores but with r4/r5
swapped and one section-anchored literal instead of two (gcc 15 vs 13 codegen; adding
`-fdata-sections` restores the two literals and the .bss order move_to_lower < return_to_mouse).
The behaviour reconstruction is therefore verified; only the identifier names are borrowed from the
dactyl keymap.

## 1. tap_dance_actions[] (VERIFIED)

`.data` init image @ flash **0x080179C8** → RAM **0x20000E7C** (mapping from the crt0 literal triple @0x080080F8/FC/0x08008100:
`__textdata_base__` 0x0801774C, `__data_base__` 0x20000C00, `__data_end__` 0x200013B8; 0x080179C8 - 0x0801774C + 0x20000C00 = 0x20000E7C).
Bytes read back from the dump:

```
00 00 00 00 00 00 00 00 | 00 00 00 00 | ed d1 00 08 | d9 cd 00 08 | 00 00 00 00 | 00 00 00 00
state (8 bytes, zero)    on_each_tap   on_dance_finished on_reset   on_each_release user_data
                         NULL          0x0800D1ED      0x0800CDD9  NULL           NULL
```

* Struct layout per `quantum/process_keycode/process_tap_dance.h:23-46` (pinned fork):
  `tap_dance_state_t {u16 interrupting_keycode; u8 count; u8 weak_mods; u8 oneshot_mods; bool pressed:1; bool finished:1; bool interrupted:1;}` (byte 5 = bitfield: bit0 pressed, bit1 finished, bit2 interrupted), then 4 fn pointers, then `user_data` — 28 bytes; matches the `movs r2,#28 / mla` stride in `process_tap_dance` (0x08012052-0x08012054) and `tap_dance_task` (0x080120F8-0x080120FA).
* Exactly one entry: the next 28 bytes at 0x080179E4 (`a7 16 00 20 c7 16 00 20 85 ec 00 08 ...`) are not a tap-dance entry (`code_anchors_report.txt` §5).
* The RAM address 0x20000E7C appears as a literal only at 0x0801203C, 0x080120C4, 0x0801211C (all inside process_tap_dance.c code), and no literal in 0x20000E80..0x20000E97 exists anywhere in flash (a direct field address such as `&tap_dance_actions[0].user_data` = 0x20000E94 would show up); 0x20000E98 (6 core references) is the next `.data` object — **no keymap code writes `user_data`** at runtime (unlike the dactyl's `keyboard_post_init_user`). `keyboard_post_init_user` @0x0800CF60 only calls `default_layer_set` and `rgb_matrix_mode(16)`.
* `fn.on_each_tap = NULL`, `fn.on_each_release = NULL`, `user_data = NULL` ⇒ exactly the expansion of
  `ACTION_TAP_DANCE_FN_ADVANCED(NULL, <finished>, <reset>)` (`process_tap_dance.h:71-72`: `{ .fn = {a, b, c, NULL}, .user_data = NULL }`).

```c
tap_dance_action_t tap_dance_actions[] = {
    [0] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, layr_dn_finished, layr_dn_reset),
};
```

## 2. cur_dance @ 0x0800D1C4 (VERIFIED, byte-identical recompile)

```
0800d1c4: 7883       ldrb  r3,[r0,#2]      ; state->count
0800d1c6: 2b01       cmp   r3,#1
0800d1c8: d108       bne   0x800d1dc
0800d1ca: 7943       ldrb  r3,[r0,#5]      ; bitfield byte
0800d1cc: 07da       lsls  r2,r3,#31       ; bit0 = pressed
0800d1ce: d50a       bpl   0x800d1e6       ; !pressed -> return 2
0800d1d0: f013 0f04  tst.w r3,#4           ; bit2 = interrupted
0800d1d4: bf0c       ite   eq
0800d1d6: 2003       moveq r0,#3           ; pressed && !interrupted -> 3
0800d1d8: 2001       movne r0,#1           ; pressed &&  interrupted -> 1
0800d1da: 4770       bx    lr
0800d1dc: 2b02       cmp   r3,#2
0800d1de: bf0c       ite   eq
0800d1e0: 2004       moveq r0,#4           ; count==2 -> 4
0800d1e2: 2001       movne r0,#1           ; count>=3 (or 0) -> 1
0800d1e4: 4770       bx    lr
0800d1e6: 2002       movs  r0,#2
0800d1e8: 4770       bx    lr
```

Enum as compiled (names are the dactyl's; values are the dump's):

| value | name (dactyl) | condition |
|---|---|---|
| 0 | TD_NONE | never returned |
| 1 | TD_UNKNOWN | count==1 && pressed && interrupted; or count ∉ {1,2} |
| 2 | TD_SINGLE_TAP | count==1 && !pressed (the `interrupted` bit is NOT examined) |
| 3 | TD_SINGLE_HOLD | count==1 && pressed && !interrupted |
| 4 | TD_DOUBLE_TAP | count==2 |

There is **no TD_TRIPLE_TAP (5)**: `count>2` falls into the `movne r0,#1` at 0x0800D1E2. Since
`cur_dance` is an out-of-line, externally visible function, its return values are exactly what the
source returned (no caller-driven folding possible), so the source had `else return TD_UNKNOWN;` for
`count != 1,2` — not the dactyl LM `count > 2 → TD_TRIPLE_TAP` / 09bf `count == 3 → TD_TRIPLE_TAP`.

## 3. on_dance_finished @ 0x0800D1ED (VERIFIED)

```
0800d1ec: push {r3,r4,r5,lr}
0800d1ee: bl   0x800d1c4              ; cur_dance(state)   (r1 = user_data is never used)
0800d1f2: cmp r0,#3 ; beq 0x800d23e   ; TD_SINGLE_HOLD
0800d1f6: cmp r0,#4 ; beq 0x800d24c   ; TD_DOUBLE_TAP
0800d1fa: cmp r0,#2 ; bne 0x800d22c   ; not TD_SINGLE_TAP -> return (default: break)
--- case 2 (single tap) ---
0800d1fe: movs r0,#4 ; bl 0x800dc3c   ; layer_state_is(4)
0800d204: mov r4,r0 ; cbz r0,0x800d21a
0800d208: ldr r3,=0x200015e9 ; movs r2,#1 ; strb r2,[r3]   ; return_to_mouse = 1
0800d20e: bl 0x800dc34                ; layer_clear()
0800d212: pop {r3,r4,r5,lr} ; b.w 0x800cdda                ; tail-call layer_oneshot_Lower()
0800d21a: ldr r5,=0x200015e8 ; ldrb r3,[r5] ; cbz r3,0x800d22e   ; if (move_to_lower)
0800d220: bl 0x800dc34 ; movs r0,#1 ; bl 0x800dc58          ;   layer_clear(); layer_move(1)
0800d22a: strb r4,[r5]  (r4==0)                             ;   move_to_lower = 0
0800d22c: pop {r3,r4,r5,pc}
0800d22e: movs r0,#1 ; bl 0x800dc3c ; cmp r0,#0 ; bne 0x800d20e  ; else if (layer_state_is(1)) { layer_clear(); oneshot }
0800d238: movs r3,#1 ; strb r3,[r5] ; b 0x800d212           ; else { move_to_lower = 1; oneshot }
--- case 3 (hold) ---
0800d23e: bl 0x800dc34 ; movs r0,#4 ; pop {..lr} ; b.w 0x800dc58   ; layer_clear(); layer_move(4)
--- case 4 (double tap) ---
0800d24c: bl 0x800dc34 ; movs r0,#1 ; b 0x800d244            ; layer_clear(); layer_move(1)
0800d254: .word 0x200015e9 ; 0800d258: .word 0x200015e8
```

Helper `layer_oneshot_Lower` @ **0x0800CDDA** (byte-identical recompile):
`movs r0,#1; bl 0x0800DC64 (layer_on(1)); movs r0,#1; movs r1,#3; bl 0x0800E504 (set_oneshot_layer(1, ONESHOT_START=0b11)); movs r0,#1; b.w 0x0800E548 (clear_oneshot_layer_state(ONESHOT_PRESSED=0b01))`.
ONESHOT_* values: `quantum/action_util.h:81`.

Callee identities (all verified from their bodies, `layer_state` = u16 @0x2000162E because
`LAYER_STATE_16BIT`):
* 0x0800DC24 `layer_state_set(state)`: `bl 0x0800DC1A (layer_state_set_kb → 0x0800DC18 layer_state_set_user = bx lr, i.e. weak default) ; strh r0,[0x2000162E]`.
* 0x0800DC34 `layer_clear`: `movs r0,#0; b.w 0x0800DC24` (`action_layer.c:133-135`).
* 0x0800DC3C `layer_state_is(l)`: `layer_state==0 ? l==0 : (layer_state>>l)&1` (`action_layer.c:141-154`).
* 0x0800DC58 `layer_move(l)`: `1<<l; uxth; b.w 0x0800DC24` (`action_layer.c:160-162`).
* 0x0800DC64 `layer_on(l)` (matched symbol): `layer_state | 1<<l → layer_state_set`.
* 0x0800E504 `set_oneshot_layer(layer,state)`: tests `keymap_config` byte1 bit2 (= bit 10 `oneshot_enable`; EEPROM `keymap_config`=0x1400 has it set), stores `layer<<3|state` to 0x200016A4 (`oneshot_layer_data`), `layer_on`, `oneshot_layer_changed_kb(get_oneshot_layer())` (`action_util.c:177-188`). No `timer_read()` call ⇒ `ONESHOT_TIMEOUT` not defined.
* 0x0800E548 `clear_oneshot_layer_state` (matched symbol; callees `layer_off` 0x0800DC7C, `reset_oneshot_layer` 0x0800E534 → `oneshot_layer_changed_kb` 0x0800E4FC → `oneshot_layer_changed_user` 0x0800D25C).

Reconstruction:

```c
void layr_dn_finished(tap_dance_state_t *state, void *user_data) {
    layr_dn_tap_state.state = cur_dance(state);        // store eliminated (write-only static), see §4
    switch (layr_dn_tap_state.state) {
        case TD_SINGLE_TAP:
            if (layer_state_is(_MOUSE)) { return_to_mouse = 1; layer_clear(); layer_oneshot_Lower(); }
            else if (move_to_lower)     { layer_move_toLower(); move_to_lower = 0; }
            else if (layer_state_is(_LOWER)) { layer_clear(); layer_oneshot_Lower(); }
            else                        { move_to_lower = 1; layer_oneshot_Lower(); }
            break;
        case TD_SINGLE_HOLD: layer_clear(); layer_move(_MOUSE); break;
        case TD_DOUBLE_TAP:  layer_move_toLower(); break;       // layer_clear(); layer_move(_LOWER);
        default: break;
    }
}
```

`user_data` is never dereferenced (r1 is dead from entry) — consistent with `user_data == NULL`.

## 4. on_reset @ 0x0800CDD9 (VERIFIED empty; cause LIKELY)

`0800cdd8: 4770 bx lr` — a 2-byte empty function. The recompile test shows that the dactyl's
`layr_dn_reset(){ layr_dn_tap_state.state = TD_NONE; }` compiles to exactly `bx lr` when
`layr_dn_tap_state` is a write-only static (GCC marks it `writeonly` and removes all stores; the same
optimisation removes the store in `layr_dn_finished`, which is why 0x0800D1EC compares r0 directly
after `bl cur_dance`). An empty-bodied source function would compile identically, so the two are
indistinguishable and behaviourally irrelevant.

Consequence (QMK core, `process_tap_dance.c:102-110`): on reset only the core work happens
(`del_weak_mods`, `del_mods(oneshot_mods)`, `send_keyboard_report`, state zeroed). Nothing turns the
mouse layer off on release ⇒ the hold result is sticky.

## 5. RAM flags (VERIFIED — literal scan of the whole dump)

| addr | name (dactyl) | set | cleared | read |
|---|---|---|---|---|
| 0x200015E8 | `move_to_lower` (u8, .bss) | 0x0800D238-D23A (finished: single tap, not on L4, flag clear, not on L1) | 0x0800D22A (finished, after locking L1); 0x0800D11A-D122 (process_record_user: **any key event whose keycode != 0x5700**, press or release) | 0x0800D21C, 0x0800D116 |
| 0x200015E9 | `return_to_mouse` (u8, .bss) | 0x0800D208-D20C (finished: single tap while `layer_state_is(4)`) | 0x0800D272 (oneshot_layer_changed_user(0) after `layer_move(4)`); 0x0800D12A-D132 (process_record_user: when `!layer_state_is(1)`) | 0x0800D264, 0x0800D126 |

Literal-pool occurrences of 0x200015E8: 0x0800D1B8 (process_record_user), 0x0800D258 (finished).
Of 0x200015E9: 0x0800D1BC, 0x0800D254, 0x0800D278 (oneshot_layer_changed_user). No other function
references either byte (the neighbouring 0x200015DC/DD/DE/E0 literals belong to the caps/OSM
indicator code and none of those functions index past their own byte). Both are in `.bss`
(0x200013B8..0x20004B88) ⇒ zero at boot.

### process_record_user @ 0x0800D104 — tap-dance part

```
0800d10a: bl 0x800c720                 ; process_record_keychron_common(); r5 = result; beq -> return false
0800d114: ldr r3,=0x200015e8 ; ldrb r2,[r3] ; cbz r2,0x800d124
0800d11a: cmp.w r4,#0x5700 ; itt ne ; movs r2,#0 ; strb r2,[r3]     ; if (move_to_lower && keycode != TD(0)) move_to_lower = 0;
0800d124: ldr r7,=0x200015e9 ; ldrb r3,[r7] ; cbz r3,0x800d134
0800d12a: movs r0,#1 ; bl 0x800dc3c ; cbnz r0,0x800d134 ; strb r0,[r7] ; if (return_to_mouse && !layer_state_is(1)) return_to_mouse = 0;
0800d134: ldrb r3,[r6,#5] ; cbz -> return true         ; if (record->event.pressed) { ... other targets ... }
```

Both clears run **before** the `pressed` test, i.e. on presses and releases alike, and after
`process_record_keychron_common` (Keychron template). `process_record_kb → process_record_user` runs
before `process_tap_dance` and before action.c's one-shot handling (`quantum.c:323`, `action.c:274-283`),
so on the second Fn tap the flag survives (keycode == TD(0)) and layer 1 is still on when the
`return_to_mouse` guard runs.

### oneshot_layer_changed_user @ 0x0800D25C (VERIFIED, sole callee of oneshot_layer_changed_kb 0x0800E4FC)

```
0800d25c: push {r3,r4,r5,lr} ; mov r4,r0 ; cbnz r0,0x800d274        ; if (!layer)
0800d262: ldr r5,=0x200015e9 ; ldrb r3,[r5] ; cbz r3,0x800d274      ;   if (return_to_mouse)
0800d268: bl 0x800dc34 ; movs r0,#4 ; bl 0x800dc58                  ;     layer_clear(); layer_move(4);
0800d272: strb r4,[r5]  (r4 == layer == 0)                          ;     return_to_mouse = 0;
```

How it fires: after `layer_oneshot_Lower()` the one-shot state is `ONESHOT_START & ~ONESHOT_PRESSED =
ONESHOT_OTHER_KEY_PRESSED`; the next key press makes `process_action` call
`clear_oneshot_layer_state(ONESHOT_OTHER_KEY_PRESSED)` (`action.c:384`) → state 0 → `layer_off(1)`,
`reset_oneshot_layer()` → `oneshot_layer_changed_kb(0)` → this hook (`action_util.c:204-211, 193-199`).

## 6. Timing (VERIFIED)

* `tap_dance_task` @0x080120D0: `ldrh r0,[0x2000201A] (last_tap_time); bl 0x0801257E (timer_elapsed)` …
  `strd r3,r3,[sp]` (zeroed `&(keyrecord_t){}`), `ldrh r0,[0x2000201C] (active_td)`, **`bl 0x0800DEFC`**,
  `cmp r5,r0; bls return` — i.e. `timer_elapsed(last_tap_time) <= get_tapping_term(active_td, &rec)`
  (`process_tap_dance.c:183`).
* Independent witness for the value: `process_tapping` @0x0800E1B4 `cmp r7,#174` is `WITHIN_QUICK_TAP_TERM`
  with `QUICK_TAP_TERM` defaulting to `TAPPING_TERM` (`action_tapping.h:26-27`) => `QUICK_TAP_TERM == TAPPING_TERM == 175`,
  which also rules out "TAPPING_TERM left at 200 plus a user `get_tapping_term` returning 175" and shows QUICK_TAP_TERM is not set separately
  (ref1011_default: `cmp r3,#199`; ref1011_feat: `cmp r3,#139`).
* **0x0800DEFC = `get_tapping_term`: `movs r0,#175 ; bx lr`** (4 bytes, no keycode test). ⇒
  **`TAPPING_TERM = 175`** (0xAF). Other callers: `waiting_buffer_scan_tap` 0x0800DF00 (site 0x0800DF52) and
  `process_tapping` 0x0800DF94 (sites 0x0800E016, 0x0800E192; identified by its constant signature `cmp r3,#239`,
  `and.w #240; cmp #240`, `cmp r7,#174`, the same sequence as the ref ELFs' process_tapping) — the three
  `WITHIN_TAPPING_TERM` uses of action_tapping.c (lines 197, 384, 509).
* Because a **call** is emitted (not an immediate), `GET_TAPPING_TERM` expanded to
  `get_tapping_term(...)`, which requires **`TAPPING_TERM_PER_KEY`** (`quantum/action_tapping.h:53-58`;
  `DYNAMIC_TAPPING_TERM_ENABLE` would load a global instead). Contrast: `refs/ref1011_feat.elf`
  (TAPPING_TERM 140, no PER_KEY) compiles `tap_dance_task` with `cmp r0,#140` at 0x080105EC.
* The body has no per-key logic: either the weak default `get_tapping_term` from
  `action_tapping.c:31-36` (returns `TAPPING_TERM`) or a user override returning 175 unconditionally —
  indistinguishable; the effective tapping term is 175 ms for every key. This mirrors the dactyl 09bf
  config (`TAPPING_TERM_PER_KEY` defined, no `get_tapping_term()` written), but with 175 instead of 150.
* `ONESHOT_TIMEOUT`: not defined (no `timer_read` in `set_oneshot_layer` 0x0800E504-0x0800E522).
* No `on_each_tap` ⇒ nothing happens at press time; everything happens when the dance finishes
  (after TAPPING_TERM from the last press, or immediately when another key interrupts —
  `preprocess_tap_dance`, `process_tap_dance.c:129-150`, after which the interrupting key is re-looked-up
  on the new layer, `quantum.c:280-284`).

## 7. Differences from the dactyl LAYR_DOWN (refs/dactyl_reference_summary.md §3)

| # | Dactyl LM/09bf | V10 Max dump | Evidence |
|---|---|---|---|
| 1 | `TD_SINGLE_TAP` → `register/unregister_code(user_data->keycode)` (types D) | **case 2 runs the one-shot-LOWER / move_to_lower / return_to_mouse logic** (dactyl's `TD_DOUBLE_TAP` body) | 0x0800D1FA `cmp r0,#2` → 0x0800D1FE… |
| 2 | `TD_DOUBLE_TAP` → that one-shot logic | **case 4 (count==2) → `layer_clear(); layer_move(1)`** (dactyl's `TD_TRIPLE_TAP` body) | 0x0800D1F6/0x0800D24C |
| 3 | `TD_TRIPLE_TAP` (5) for count>2 (LM) / ==3 (09bf) | **no value 5**; count>2 → 1 → no-op | 0x0800D1DC-D1E4 |
| 4 | `TD_SINGLE_HOLD` → `layer_clear(); layer_move(_MOUSE)` | identical (layer 4) | 0x0800D23E-D248 |
| 5 | `user_data = &d_data` set in `keyboard_post_init_user` | `user_data` NULL, never written, never read | init image 0x080179E0; literal scan; r1 dead in 0x0800D1EC |
| 6 | `layr_dn_reset` stores `TD_NONE` | `bx lr` (store eliminated or absent) — no behavioural difference | 0x0800CDD8; recompile test |
| 7 | `TAPPING_TERM` 150 (09bf) / 140 (LM) / 300 (DS) | **175** | 0x0800DEFC |
| 8 | `TAPPING_TERM_PER_KEY` defined only in 09bf, never with a `get_tapping_term` | defined, weak/constant `get_tapping_term` | 0x080120EC call vs ref_feat immediate |
| 9 | `process_record_user` flag clears (LM 169-176) | identical | 0x0800D114-D132 |
| 10 | `oneshot_layer_changed_user` (LM 692-711) | identical | 0x0800D25C |
| 11 | `layer_oneshot_Lower` / `layer_move_toLower` helpers | identical (`layer_move_toLower` inlined twice) | 0x0800CDDA; 0x0800D220, 0x0800D24C |
| 12 | DS-only: `on_each_tap_fn`, `fast_typing_active`, `td_in_progress`, `lower_locked`, `tap_code(KC_F)` | **absent** (`on_each_tap` NULL, no such flags) | init image; literal scan |
| 13 | `layer_state_set_user` (rgblight layers) | not overridden (`layer_state_set_user` = `bx lr` @0x0800DC18) | 0x0800DC1A/DC18 |

Items 1-3 are the substantive behavioural differences: on the V10 Max Fn key a **single tap** gives the
one-shot layer-1 behaviour (with the double-tap-to-lock via `move_to_lower`), a **double tap** locks
layer 1, a **hold** locks the mouse layer 4; there is no "type a character" action and no triple tap.

## 8. Confidence

* VERIFIED: everything in §1-§6 above (all cited instructions are in the dump; recompile matches).
* LIKELY: the identifier names (`move_to_lower`, `return_to_mouse`, `TD_*`, `layr_dn_*`) and the
  existence of the write-only `layr_dn_tap_state`; that 0x0800DF00/0x0800DF94 are action_tapping.c.
* RESOLVED: `get_tapping_term` is the weak default from `action_tapping.c:31-35`, not a keymap override — 0x0800DEFC
  sits inside the action_tapping.o cluster (between `waiting_buffer_typed.isra.0` 0x0800DEB8 and `waiting_buffer_scan_tap`
  0x0800DF00), far from the keymap TU 0x0800CDD8-0x0800D2CC, and the gcc 13.2.1 rebuild without any override reproduces the same
  4-byte body at the same relative position. So `config.h` defines `TAPPING_TERM 175` + `TAPPING_TERM_PER_KEY` and keymap.c
  must NOT define `get_tapping_term()`.
* UNCERTAIN / unobservable: whether `layr_dn_reset` had an (eliminated) store or an empty body.
* Caveat for claim 8 (flag clears in `process_record_user`): they run for any key event that
  `process_record_keychron_common` passes through — Keychron keycodes (BT_HST1..3, P2P4G, BAT_LVL, KC_TASK, KC_FILE, ...)
  return early at 0x0800D112 and never reach them.
