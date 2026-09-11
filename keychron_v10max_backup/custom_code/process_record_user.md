# process_record_user (0x0800D104) and its helpers

Target: `process_record_user`, `check_unlock_osm` (sub_0800d0b4), `find_osm_slot` (sub_0800d090),
`handle_oneshots` (sub_0800d010) + the two one-shot hook thunks, the shared `.bss` flags, the custom
keycode enum, and the absence of `post_process_record_user`.

Sources used: `dump_a.bin` (objdump listings quoted below, `arm-none-eabi-objdump -D -b binary -m arm
-M force-thumb --adjust-vma=0x08000000`), `decompiled/0800d104_process_record_user.c`,
`decompiled/0800d0b4_FUN_0800d0b4.c`, `decompiled/0800d090_FUN_0800d090.c`, `decompiled/0800d010_FUN_0800d010.c`,
`ghidra_callgraph.json`, `dump_symbols.txt`, `code_anchors_report.txt` section [7], the fork source
`/Users/dexter/code/qmk-keychron-ref` (quantum/action_util.c, quantum/action.c, quantum/keycodes.h,
quantum/modifiers.h, quantum/led.h, keyboards/keychron/common/keychron_task.c), and the dactyl reference
(`refs/dactyl_reference_summary.md`, scratch copies `dactyl_ref/keymap_local-macos.c`, `keymap_09bf262a04.c`).

Reconstructed C: `custom_code/process_record_user.c`. Verification script for the handle_oneshots
decision table: `tools/sim_handle_oneshots.py`.

---

## 1. Summary

```
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (!process_record_keychron_common(keycode, record)) return false;      // 0x0800D10A / 0x0800D112
    if (move_to_lower   && keycode != TD(0))        move_to_lower   = 0;      // 0x0800D114..22  (flag 0x200015E8)
    if (return_to_mouse && !layer_state_is(1))      return_to_mouse = 0;      // 0x0800D124..32  (flag 0x200015E9)
    if (record->event.pressed) {                                              // 0x0800D134
        if (keycode in {OSM(MOD_LSFT),OSM(MOD_LGUI),OSM(MOD_RSFT),OSM(MOD_RGUI)})
            return check_unlock_osm(keycode);                                 // 0x0800D13C..5A (tail call 0x0800D0B4)
        if (keycode == KC_CAPS && !host_keyboard_led_state().caps_lock) { caps_active = 1; return true; } // 0x0800D15E..6A
        if (keycode == KC_CAPS &&  host_keyboard_led_state().caps_lock) { caps_active = 0; return true; } // 0x0800D170..7C
        if (keycode == 0x7E40) { tap DOT, tap SLSH; return false; }           // 0x0800D17E..9E  "./"
        if (keycode == 0x7E41) { tap DOT, tap DOT, tap SLSH; return false; }  // 0x0800D1A2..B6  "../"
    }
    return true;                                                              // 0x0800D16C
}
```

The custom keycode enum is `{ DOT_SLS = SAFE_RANGE (0x7E40), DIR_UP (0x7E41) }` — the behaviour is exactly
the dactyl keymap's `DOT_SLS` ("./") and `DIR_UP` ("../"), so the dactyl names are used. No `QK_USER_2`
(`DBL_DASH`, `KC_MINS` twice) exists anywhere in the image (the only `0x7E4x` compares are at 0x0800D17E
and 0x0800D1A2; `KC_MINS` 0x2D is never passed to register_code in the custom TU).

The OSM path is the dactyl keymap's `find_osm_slot`/`check_unlock_osm` pair (dead code on the dactyl,
**live** here) ported verbatim, including its pointer-arithmetic bug. In this image it is **inert**: the
slot array is never populated, `find_osm_slot()` always returns NULL, `check_unlock_osm()` always returns
true, and the four OSM keys are processed by stock QMK (`ONESHOT_TAP_TOGGLE 2`, verified at 0x0800D832).

The one-shot indicator hooks (`oneshot_mods_changed_user`/`oneshot_locked_mods_changed_user`) share one body
that maintains `shift_active` (0x200015DE) / `gui_active` (0x200015DD) and paints the whole matrix white /
yellow / black via `rgb_matrix_set_color_all`. Its decision table is verified; it is **not** the dactyl chain.

There is no `post_process_record_user` (0x0800D2DC is the empty weak default).

---

## 2. Call context and return handling

* `process_record_kb` @0x0800C6E8 (`decompiled/0800c6e8_process_record_kb.c`): `if (!process_record_user(kc, rec)) return false; return FUN_0800c6a0(kc, rec);` — matches the fork's `keychron_task.c:87-93` (`process_record_user` first, then `process_record_keychron`). So a `false` from process_record_user also skips the wireless/factory-test processing. **Verified.**
* Inside process_record_user, `process_record_keychron_common` (0x0800C720; content verified against `keychron_common.c`: switch 0x7E00..0x7E0A) is called **first** (0x0800D10A `bl 0x800c720`); its result is kept in r5 (0x0800D10E) and a zero result returns 0 immediately (0x0800D112 `beq 0x800d19e` -> 0x0800D19E `movs r5,#0` -> 0x0800D16C `mov r0,r5`). This is the stock Keychron keymap template (`keymaps/default/keymap.c:71-76`) with the user logic appended after it. **Verified.**
* Every other exit returns r5 (== true, since r5 != 0 here) except the DOT_SLS/DIR_UP branches which fall into 0x0800D19E (`return false`) and the OSM branch which tail-calls `check_unlock_osm` (0x0800D156 `pop.w {…,lr}` + 0x0800D15A `b.w 0x800d0b4`). **Verified.**

## 3. Instruction-level walk-through of process_record_user

```
0800d104  push {r3,r4,r5,r6,r7,lr}
0800d106  mov r4,r0                      ; keycode
0800d108  mov r6,r1                      ; record
0800d10a  bl  0x800c720                  ; process_record_keychron_common(keycode, record)
0800d10e  mov r5,r0
0800d110  cmp r0,#0 ; 0800d112 beq 0x800d19e   -> return false
0800d114  ldr r3,=0x200015e8 ; ldrb r2,[r3] ; cbz r2,0x800d124
0800d11a  cmp.w r4,#0x5700               ; TD(0)
0800d11e  itt ne ; movne r2,#0 ; strbne r2,[r3]     ; move_to_lower = 0 unless keycode == TD(0)
0800d124  ldr r7,=0x200015e9 ; ldrb r3,[r7] ; cbz r3,0x800d134
0800d12a  movs r0,#1 ; bl 0x800dc3c (layer_state_is) ; cbnz r0,0x800d134
0800d132  strb r0,[r7]                   ; return_to_mouse = 0 (r0 == 0) when layer 1 not active
0800d134  ldrb r3,[r6,#5] ; cbz r3,0x800d16c        ; record->event.pressed (keyevent_t: key u16 @0, time u16 @2, type u8 @4, pressed @5)
0800d138  cmp r4,#0x39 ; beq 0x800d15e              ; KC_CAPS
0800d13c  sub.w r3,r4,#0x5280 ; subs r3,#0x22 ; uxth r3,r3
0800d144  cmp r3,#0x16 ; bhi 0x800d17e               ; keycode - 0x52A2 <= 0x16 ?
0800d148  mov.w r2,#0x410041 ; lsr.w r3,r2,r3 ; lsls r1,r3,#31 ; bpl 0x800d16c   ; bit test (GCC switch lowering)
0800d154  mov r0,r4 ; pop.w {r3-r7,lr} ; b.w 0x800d0b4        ; return check_unlock_osm(keycode)
0800d15e  bl 0x8012148 (host_keyboard_led_state) ; lsls r2,r0,#30 ; bmi 0x800d170   ; bit1 = caps_lock (quantum/led.h:32-33)
0800d166  ldr r3,=0x200015dc ; movs r2,#1 ; strb r2,[r3]      ; caps_active = 1
0800d16c  mov r0,r5 ; pop {…,pc}                              ; return r5 (true)
0800d170  bl 0x8012148 ; lsls r3,r0,#30 ; bpl 0x800d16c       ; second, separate host_keyboard_led_state() call
0800d178  ldr r3,=0x200015dc ; movs r2,#0 ; b 0x800d16a       ; caps_active = 0 ; return true
0800d17e  movw r3,#0x7e40 ; cmp r4,r3 ; bne 0x800d1a2         ; QK_USER_0
0800d186  movs r0,#0x37 ; bl register_code(0x800d570) ; movs r0,#0x37 ; bl unregister_code(0x800d600)
0800d192  movs r0,#0x38 ; bl register_code ; movs r0,#0x38 ; bl unregister_code
0800d19e  movs r5,#0 ; b 0x800d16c                            ; return false
0800d1a2  movw r3,#0x7e41 ; cmp r4,r3 ; bne 0x800d16c         ; QK_USER_1 (else return true)
0800d1aa  movs r0,#0x37 ; bl register_code ; movs r0,#0x37 ; bl unregister_code
0800d1b6  b 0x800d186                                         ; then the "./" body -> "../", return false
0800d1b8  .word 0x200015e8 ; 0x200015e9 ; 0x200015dc
```

Mask decoding (0x0800D148): bits set in 0x410041 are 0, 6, 16, 22 -> keycodes 0x52A2, 0x52A8, 0x52B2, 0x52B8
= `OSM(MOD_LSFT)`, `OSM(MOD_LGUI)`, `OSM(MOD_RSFT)`, `OSM(MOD_RGUI)` (`OSM(m) = 0x52A0 | (m & 0x1F)`,
quantum/quantum_keycodes.h:109; MOD_LSFT 0x02, MOD_LGUI 0x08, MOD_RSFT 0x12, MOD_RGUI 0x18, quantum/modifiers.h:17-23).
The keymap uses three of them (layer 0: OSM(MOD_LSFT), OSM(MOD_RSFT), OSM(MOD_LGUI)); OSM(MOD_RGUI) is in the
test set but not on any layer — consistent with the dactyl's `is_osm` expression which lists all four.

`register_code` at 0x0800D570 is not in `dump_symbols.txt` by name, but 0x0800D570..0x0800D600 is 0x90 bytes
immediately preceding the matched `unregister_code` (0x0800D600, 114 B), the same sizes/order as in
`refs/ref1011_feat.elf` (`register_code` 0x90 @0800b5e0, `unregister_code` 0x72 @0800b670). **Verified by layout.**

Two separate `host_keyboard_led_state()` calls are kept (0x0800D15E and 0x0800D170) — the compiler cannot merge
calls to a non-pure function, so the source really has the dactyl's two-branch form
`if (KC_CAPS && !caps) {...} else if (KC_CAPS && caps) {...}`. **Verified.**

Semantics of `caps_active` (0x200015DC): at the time `process_record_user` sees the KC_CAPS press the host has
not yet toggled the LED, so `!caps_lock` means "caps is about to turn on" -> flag = 1; `caps_lock` set means
"about to turn off" -> flag = 0. The flag is read only by the indicator hook 0x0800CF74
(`decompiled/0800cf74_FUN_0800cf74.c`: `if (!gui_active) { if (shift_active || caps_active) set_color(i,255,255,255) } else set_color(i,255,255,0)`),
i.e. it mirrors the dactyl's `rgblight_set_layer_state(3, true/false)` "caps indicator". **Verified** (this file
only documents the flag; the indicator body is another target).

## 4. `find_osm_slot` @0x0800D090 and `check_unlock_osm` @0x0800D0B4

### 4.1 Disassembly

```
; find_osm_slot(uint16_t kc) -> uint16_t*
0800d090  ldr r2,=0x200015e0 ; mov r3,r0
0800d094  ldr r0,[r2]                     ; index = held_osm[0]
0800d096  cbz r0,0x800d0ac                ; index == NULL ?
0800d098  ldrh r2,[r0] ; cmp r2,r3 ; beq 0x800d0aa      ; *index == kc -> return index
0800d09e  adds r2,r0,#4                    ; index += sizeof(uint16_t) elements  (= +4 bytes)
0800d0a0  ldrh r1,[r0,#4] ; cmp r1,r3      ; second probe: *(index + 2 elements)
0800d0a4  ite eq ; moveq r0,r2 ; movne r0,#0
0800d0aa  bx lr
0800d0ac  movs r2,#4 ; b 0x800d0a0         ; index == NULL: blank = NULL, index = (uint16_t*)4, probe *(uint16_t*)4 (!)
0800d0b0  .word 0x200015e0

; check_unlock_osm(uint16_t kc) -> bool
0800d0b4  push {r3,r4,r5,lr} ; mov r5,r0
0800d0b8  bl 0x800d090 ; mov r4,r0 ; cbz r0,0x800d0f2   ; slot == NULL -> return true (0800d0f2 movs r0,#1)
0800d0c0  bl 0x800e310 (get_mods) ; cbnz r0,0x800d0ca ; movs r0,#0 ; pop  ; !get_mods() -> return false
0800d0ca  ldrh r3,[r4] ; cmp r3,r5 ; beq 0x800d0c6        ; *slot == kc -> return false
0800d0d0  bl 0x800e424   ; clear_oneshot_mods()
0800d0d4  bl 0x800e3b0   ; clear_oneshot_locked_mods()
0800d0d8  bl 0x800e380   ; get_oneshot_mods()
0800d0dc  bl 0x800d684   ; unregister_mods(^)   (0x0800D684 = if(m){del_mods(m); send_keyboard_report();} == action.c:1043-1047)
0800d0e0  ldr r2,=0x200015e0 ; movs r3,#0 ; str r3,[r2] ; str r3,[r2,#4]   ; held_osm[0] = held_osm[1] = NULL
0800d0e8  ldr r2,=0x200015de ; strb r3,[r2]   ; shift_active = 0
0800d0ec  ldr r2,=0x200015dd ; strb r3,[r2]   ; gui_active = 0
0800d0f0  b 0x800d0c6                         ; return false
```

### 4.2 Source match

This is a line-for-line compilation of the dactyl keymap's (LM lines 499-553, 09bf lines 502-566)

```c
#define OSM_HOLD_COUNT 2
static uint16_t* held_osm[OSM_HOLD_COUNT] = {0};

uint16_t* find_osm_slot(uint16_t keycode) {
  uint16_t* index = held_osm[0];
  uint16_t* blank = NULL;
  for (int i = 0; i < OSM_HOLD_COUNT; i++) {
    if (index == NULL)            blank = index;        // stores NULL
    else if (*(index) == keycode) return index;
    index += sizeof(uint16_t);                          // += 2 elements = 4 bytes
  }
  return blank;
}
bool check_unlock_osm(uint16_t keycode) {
    uint16_t* slot = find_osm_slot(keycode);
    if (slot == NULL) { slot = &keycode; return true; }
    if (get_mods() && (keycode != *(slot))) {
      rgblight_set_layer_state(6, false); rgblight_set_layer_state(1, false);   // <- absent in the V10 Max binary
      clear_oneshot_mods(); clear_oneshot_locked_mods(); unregister_mods(get_oneshot_mods());
      for (int i = 0; i < OSM_HOLD_COUNT; i++) held_osm[i] = NULL;
      shift_active = 0; gui_active = 0;
      return false;
    }
    return false;
}
```

Every quirk of the source is visible in the object code: the 4-byte stride (`adds r2,r0,#4` / `ldrh r1,[r0,#4]`),
the NULL case probing address 4 (`movs r2,#4` then the shared `ldrh r1,[r0,#4]` with r0 = 0), the NULL-returning
`blank`, the `get_mods()` gate, the `*slot != keycode` gate, the two 32-bit zero stores (two pointer slots), and
the two flag clears in source order (shift_active then gui_active). On the dactyl this pair was **never called**;
on the V10 Max the commented-out `is_osm` block of the dactyl `process_record_user` (LM lines 583-587) is active.
**Verified** (identity of the source construct); the rgblight calls are absent (no call between 0x0800D0CE and 0x0800D0D0).

### 4.3 Effective behaviour: inert

1. `held_osm[]` (0x200015E0/0x200015E4) is only ever **written with zero** (0x0800D0E4/0x0800D0E6). A raw scan of
   `dump_a.bin` for the 32-bit word 0x200015E0 finds exactly two literals, 0x0800D0B0 (find_osm_slot pool) and 0x0800D0F8
   (check_unlock_osm pool); the word 0x200015E4 occurs nowhere; no movw/movt encodings of 0x15DC..0x15E9 exist in the code;
   the neighbouring literal holders cannot reach the slots by base+offset (0x0800CF74..0x0800D010 has no store instruction,
   0x0800D1EC..0x0800D2CC stores only `strb [rX,#0]` to E8/E9) (`grep -l DAT_200015e0 decompiled/*.c` agrees). `check_unlock_osm`'s `slot = &keycode` is a dead store to a local.
2. They live in `.bss` and are zeroed at boot: crt0 @0x08008000 copies `.data` from 0x0801774C to
   [0x20000C00, 0x200013B8) (0x0800808C-0x0800809E, table words @0x080080F8) and zero-fills
   [0x200013B8, 0x20004B88) (0x080080A0-0x080080AE, words @0x08008104/0x08008108). 0x200015E0 is inside the zero-fill range.
3. Therefore `find_osm_slot` always takes the `index == NULL` path and the second iteration compares
   `*(uint16_t *)0x00000004` with the keycode. On the STM32F401 booting from main flash, 0x00000000 aliases
   0x08000000; the dump's word at offset 4 is the bootloader reset vector 0x0800811D, halfword = **0x811D**
   (`dump_a.bin[4:6]`), which is none of 0x52A2/0x52A8/0x52B2/0x52B8. So `find_osm_slot` returns NULL,
   `check_unlock_osm` returns **true**, and `process_record_user` returns true for the four OSM keys.
4. Net effect: OSM(MOD_LSFT/RSFT/LGUI) behave as stock QMK one-shot mods. `ONESHOT_TAP_TOGGLE` is **2** in this
   build: process_action's MODS_ONESHOT press path compares tap_count with 0, 1, 2
   (0x0800D816 `cmp.w r8,#0`, 0x0800D824 `cmp.w r8,#1` -> add_oneshot_mods 0x0800E3EC, 0x0800D832 `cmp.w r8,#2` ->
   register_mods 0x0800D672, del_oneshot_mods 0x0800E408, add_oneshot_locked_mods 0x0800E394), which is
   `quantum/action.c:456-467` with `ONESHOT_TAP_TOGGLE == 2`. Double-tapping an OSM key locks the modifier;
   the release path (0x0800D866 `cmp.w r8,#1` + get_mods) is `action.c:475-480`. (This constant belongs to the
   config target; it is recorded here because it defines what "OSM handling" actually does on this board.)

**Verified**: 1-3 (addresses, stores, boot zeroing, the constant at address 4). **Likely**: that the address-0 alias
is flash (standard BOOT0=0 configuration; the bootloader's initial SP 0x20000400 at offset 0 is consistent). Even
if the alias were different, the code path is only reachable if that halfword equals an OSM keycode.

Recommendation for a rebuild: keep the code for fidelity (it is what the image contains) **or** delete the
`is_osm` block — behaviour is identical. Keeping it means shipping a NULL+4 dereference (UB); a newer compiler
may legitimately turn it into anything. The safe, behaviour-identical version is to drop the block.

## 5. `handle_oneshots` @0x0800D010 and the two hooks

### 5.1 Which hook is which

* `oneshot_mods_changed_kb` = 0x0800E3E4 (`push; bl 0x800d088; pop`), `oneshot_locked_mods_changed_kb` = 0x0800E38C (`push; bl 0x800d08c; pop`).
  Identification: in the action_util.c object (0x0800E310..0x0800E43C) the functions are emitted callee-first per
  variable group: `get_oneshot_mods` 0x0800E380 (returns byte @0x200016A6), then group A on **0x200016A5**
  {changed_kb 0x0800E38C, add 0x0800E394, clear 0x0800E3B0, del 0x0800E3C8} = source order add/set/clear/del of the
  `oneshot_locked_mods` block (action_util.c:57-80, `set_` unused), then group B on **0x200016A6**
  {changed_kb 0x0800E3E4, add 0x0800E3EC, del 0x0800E408, clear 0x0800E424} = source order add/del/set/clear of
  `oneshot_mods` (action_util.c:495-544, `set_` unused). `get_mods_for_report` 0x0800E43C reads 0x200016D0 (real
  mods), 0x200016CF (weak mods) and **0x200016A6** as `oneshot_mods` (`if (oneshot_mods) {mods |= …; if (has_anykey()) clear_oneshot_mods();}`
  with `bl 0x800e424` at 0x0800E456 = action_util.c:263-279). So 0x200016A6 = `oneshot_mods`, 0x200016A5 =
  `oneshot_locked_mods`, 0x0800D088 = `oneshot_mods_changed_user`, 0x0800D08C = `oneshot_locked_mods_changed_user`. **Verified.**
* Both thunks are `b.w 0x800d010` (0x0800D088, 0x0800D08C): GCC sibling-call optimisation of two one-line wrappers that
  each just call the static `handle_oneshots(mods)` (dactyl LM lines 479-497); the same pattern appears at 0x0800D15A and
  0x0800C6FC. No linker ICF is involved (GNU ld does not fold code). **Verified.**

### 5.2 Body

```
0800d010  push {r3-r7,lr}
0800d012  ands r5,r0,#0x22          ; S = mods & MOD_MASK_SHIFT
0800d016  bic  r4,r0,#0x77          ; G = mods & MOD_MASK_GUI (0x88)
0800d01a  bne 0x800d044             ; S != 0 -> skip shift-clear
0800d01c  ldr r6,=0x200015de ; ldrb r3,[r6] ; cbz r3,0x800d044      ; !S && shift_active ?
0800d022  set_color_all(0,0,0) (0800fee4) ; strb r5,[r6]            ; black; shift_active = 0
0800d02e  cbz r4,0x800d042          ; !G -> return (gui_active NOT touched)
0800d030  ldr r4,=0x200015dd ; ldrb r2,[r4] ; cbnz r2,0x800d042    ; G && !gui_active ?
0800d036  set_color_all(0xff,0xff,0) ; movs r3,#1 ; strb r3,[r4]   ; yellow; gui_active = 1
0800d042  pop
0800d044  and r6,r4,#0xff ; cbnz r4,0x800d078
0800d04a  ldr r7,=0x200015dd ; ldrb r3,[r7] ; cbz r3,0x800d05c      ; !G && gui_active ?
0800d050  set_color_all(0,0,0) ; strb r6,[r7]                       ; black; gui_active = 0
0800d05c  cmp r5,#0 ; beq 0x800d042 ; (S:) 
0800d060  ldr r5,=0x200015de ; ldrb r3,[r5] ; bne 0x800d02e         ; S && !shift_active ?
0800d068  set_color_all(0xff,0xff,0xff) ; movs r3,#1 ; strb r3,[r5] ; white; shift_active = 1 ; b 0x800d02e
0800d078  cmp r5,#0 ; bne 0x800d060 ; b 0x800d030
0800d080  .word 0x200015de ; 0x200015dd
```

Decision table (S = shift bits present, G = gui bits present; verified by emulating this control flow for all
16 combinations, `tools/sim_handle_oneshots.py`):

| condition | action |
|---|---|
| `!S && shift_active` | black, `shift_active = 0`, **then only** `G && !gui_active` -> yellow; return (gui_active never cleared here) |
| else `!G && gui_active` | black, `gui_active = 0` |
| `S && !shift_active` | white (255,255,255), `shift_active = 1` |
| `G && !gui_active` | yellow (255,255,0), `gui_active = 1` |

Equivalent C (one faithful rendering — the exact source text is not recoverable):

```c
static void handle_oneshots(uint8_t mods) {
    if (!(mods & MOD_MASK_SHIFT) && shift_active)     { rgb_matrix_set_color_all(0,0,0);       shift_active = 0; }
    else if (!(mods & MOD_MASK_GUI) && gui_active)    { rgb_matrix_set_color_all(0,0,0);       gui_active   = 0; }
    if ((mods & MOD_MASK_SHIFT) && !shift_active)     { rgb_matrix_set_color_all(255,255,255); shift_active = 1; }
    if ((mods & MOD_MASK_GUI)   && !gui_active)       { rgb_matrix_set_color_all(255,255,0);   gui_active   = 1; }
}
```

The dactyl LM `handle_oneshots` (an exclusive if/else-if chain with `return`s, lines 450-477) differs from the
binary in 5 of 16 cases (e.g. S,G,!sf,!gf: binary sets both white and yellow; dactyl only white). So the V10 Max
version was rewritten — **the dactyl chain is NOT what the dump contains.** `rgblight_set_layer_state(6/1, …)` was
replaced by `rgb_matrix_set_color_all` (0x0800FEE4 = `ldr r3,=0x08016F9C (rgb_matrix_driver); ldr r3,[r3,#8]; bx r3`, i.e.
`rgb_matrix_driver.set_color_all(...)` through the const driver struct whose slot 8 is `snled27351_set_color_all` 0x08011379).
Colours: white = shift one-shot/lock active, yellow = GUI one-shot/lock active, black = cleared. **Verified.**
(These flags are also consumed by the indicator hook 0x0800CF74 each frame; that body is another target.)

## 6. Shared `.bss` flag map

| address | name (this reconstruction) | written by | read by |
|---|---|---|---|
| 0x200015DC | `caps_active` | process_record_user KC_CAPS branch (1 / 0) | indicator 0x0800CF74 |
| 0x200015DD | `gui_active` | handle_oneshots; zeroed in check_unlock_osm | handle_oneshots, indicator 0x0800CF74 |
| 0x200015DE | `shift_active` | handle_oneshots; zeroed in check_unlock_osm | handle_oneshots, indicator 0x0800CF74 |
| 0x200015E0, 0x200015E4 | `held_osm[2]` (uint16_t *) | zeroed in check_unlock_osm only | find_osm_slot |
| 0x200015E8 | `move_to_lower` | TD(0) finished 0x0800D1EC (=1 / =0); cleared here if keycode != TD(0) | TD(0) finished |
| 0x200015E9 | `return_to_mouse` | TD(0) finished (=1 when layer 4 active); cleared here if !layer_state_is(1); cleared in oneshot_layer_changed_user 0x0800D25C | oneshot_layer_changed_user |

Declaration order (from the addresses, GCC emitting statics in reverse definition order): `return_to_mouse, move_to_lower,
held_osm[], shift_active, gui_active, caps_active` — the dactyl LM order (`process_record_user.c` follows it).
The names for E8/E9 come from the dactyl source, whose `process_record_user` prologue is identical to
0x0800D114-0x0800D132 (`move_to_lower && keycode != TD(LAYR_DOWN)`, `return_to_mouse && !layer_state_is(_LOWER)`)
and whose TD(0) finished handler sets them the same way (`decompiled/0800d1ec_FUN_0800d1ec.c`: `if layer_state_is(4) -> 0x200015E9 = 1`, `0x200015E8 = 1` in the first-double-tap branch). **Verified semantics, likely names.**

## 7. `post_process_record_user`, `pre_process_record_user`

`post_process_record_quantum` 0x0800D35E calls `post_process_record_kb` 0x0800D2DE (`push; bl 0x800d2dc; pop`), and
0x0800D2DC is a bare `bx lr` — the weak empty `post_process_record_user`. Likewise `pre_process_record_kb` 0x0800D2D0
calls 0x0800D2CC which is `movs r0,#1; bx lr` (weak `pre_process_record_user` returning true). **No custom post/pre
hooks exist. Verified.**

## 8. Differences from the dactyl reference (what the dump does / does not contain)

| dactyl (LM/09bf) | V10 Max dump |
|---|---|
| `is_osm ... return check_unlock_osm(keycode)` commented out | **active** (0x0800D13C-0x0800D15A) |
| `check_unlock_osm` has two `rgblight_set_layer_state` calls | removed |
| `KC_CAPS` -> `rgblight_set_layer_state(3, …)` | -> byte flag 0x200015DC (consumed by the RGB-matrix indicator) |
| `DBL_DASH` (LM only) | **absent** (no 0x7E42 compare, no KC_MINS taps) |
| `handle_oneshots` exclusive if/else-if chain with returns | rewritten; decision table in section 5.2 |
| `rgblight_set_layer_state(6/1, …)` in handle_oneshots | `rgb_matrix_set_color_all` white / yellow / black |
| `process_record_user` starts with the flag clears | starts with `process_record_keychron_common` (Keychron template), then the flag clears |
| DOT_SLS / DIR_UP bodies | identical (register/unregister pairs, `return false`) |

## 9. Verified / likely / uncertain

**Verified (instruction-level):** call order and return handling (section 2); the two flag-clear rules with the
`TD(0)` and `layer_state_is(1)` tests; the pressed-only gate; the KC_CAPS two-call form and the flag values; the
OSM key set {0x52A2, 0x52A8, 0x52B2, 0x52B8} and the tail call; the "./" and "../" sequences via
`register_code`/`unregister_code` (not `tap_code`) and their `return false`; `find_osm_slot`/`check_unlock_osm`
control flow, stores and callees; `held_osm[]` never populated and zero at boot; `*(uint16_t*)4 == 0x811D`;
`ONESHOT_TAP_TOGGLE == 2`; the handle_oneshots decision table; hook identities (0x0800D088 = mods, 0x0800D08C = locked);
no post/pre_process_record_user.

**Likely:** variable names (`move_to_lower`, `return_to_mouse`, `shift_active`, `gui_active`, `held_osm`,
`caps_active` — the first five are the dactyl names of variables with identical use; `caps_active` is a
commented-out dactyl name); the enum names `DOT_SLS`/`DIR_UP` (behaviour identical to the dactyl keycodes of the
same value); that the source form is an if-chain rather than a `switch` (GCC 13 converts either to the same
bit-test code); the exact statement structure of `handle_oneshots` (only its input/output table is verified);
that the address-0 alias is flash (bootloader vector table).

**Uncertain:** nothing behaviour-relevant. Layer enum names are borrowed from the dactyl (only the numbers 0/1/4 are used by this code).

## 10. Open questions (for other targets / the integrator)

* The indicator hook 0x0800CF74 (`rgb_matrix_indicators_advanced_user`) consumes `caps_active`, `shift_active`,
  `gui_active`; its per-layer colours and the two-colour override should be reconstructed there with the flag
  names used here.
* `rgb_matrix_set_color_all` inside the one-shot hooks only paints the current frame (the effect and the indicator
  hook repaint every frame); the persistent white/yellow comes from 0x0800CF74 reading the flags. The rebuild can
  keep the calls for fidelity; they are harmless.
* Whether to keep the UB-laden `find_osm_slot` in the rebuilt keymap (fidelity) or drop the `is_osm` block
  (identical behaviour, no UB). This report recommends dropping it or at least fixing the stride if the user wants
  the "unlock" feature to actually work.
