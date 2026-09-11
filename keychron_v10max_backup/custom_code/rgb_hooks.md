# RGB / indicator / boot hooks — recovered from `dump_a.bin`

Target: `keyboard_post_init_user`, `rgb_matrix_indicators_advanced_user`, `oneshot_mods_changed_user` /
`oneshot_locked_mods_changed_user`, the three indicator flags, the presence/absence of other stock hooks,
and whether Keychron's own indicator path is intact.

Reconstructed code: `custom_code/rgb_hooks.c`. Recompile check: `tools/rgb_hooks_recompile_check.sh`
(+ `.c`). All addresses are flash addresses in `keychron_v10max_backup/dump_a.bin`; disassembly via
`arm-none-eabi-objdump -D -b binary -m arm -M force-thumb --adjust-vma=0x08000000`; decompiles in
`decompiled/<addr>_*.c`; QMK sources from the pinned fork `/Users/dexter/code/qmk-keychron-ref`.

Confidence legend: **[V]** verified against dump instructions, **[L]** likely (strong but indirect),
**[U]** uncertain.

---

## 1. Summary

| Item | Result |
|---|---|
| `keyboard_post_init_user` 0x0800CF60 | **[V]** exactly `default_layer_set(0); rgb_matrix_mode(16);` — nothing else. `rgb_matrix_mode` is the EEPROM-writing variant. Mode 16 = `RGB_MATRIX_TYPING_HEATMAP`. |
| `rgb_matrix_indicators_advanced_user` 0x0800CF74 | **[V]** `for (i = led_min; i < led_max; i++)`: layer colour from `get_highest_layer(layer_state \| default_layer_state)` — L1 green, L2 blue, L3 orange, L4 teal, L5 red, L0 nothing; then per LED: `gui_active` → yellow, else `shift_active \|\| caps_active` → white. Returns `false`. |
| `oneshot_mods_changed_user` 0x0800D088, `oneshot_locked_mods_changed_user` 0x0800D08C | **[V]** both are `b.w 0x0800D010`, a shared body that maintains `shift_active`/`gui_active` from the `mods` argument and fires one-frame `rgb_matrix_set_color_all` (white / yellow / off). Structure differs from the dactyl `handle_oneshots` (no early returns). Recompiles instruction-identical. |
| Flags | **[V]** 0x200015DC `caps_active` (set only by `process_record_user` on `KC_CAPS` press from `host_keyboard_led_state().caps_lock`), 0x200015DD `gui_active`, 0x200015DE `shift_active` (set/cleared in the one-shot body; both cleared in the OSM helper 0x0800D0B4). No leader flag exists. |
| `oneshot_layer_changed_user` 0x0800D25C | **[V]** implemented (tap-dance return-to-mouse logic; belongs to the tap-dance target). |
| `layer_state_set_user` 0x0800DC18, `default_layer_state_set_user` 0x0800DBC4 | **[V]** single `bx lr` = stock weak default / identity. Not implemented. |
| `housekeeping_task_user` 0x0800E768, `matrix_scan_user` 0x0800ED16 | **[V]** `bx lr`, stock. |
| `rgb_matrix_indicators_user` 0x0801017A | **[V]** `movs r0,#1; bx lr`, stock weak. |
| `rgb_matrix_indicators_advanced_kb` 0x08010C4C | **[V]** stock weak wrapper (`push {r3,lr}; bl user; pop`), instruction-identical to ref (only the bl target differs). Intact, not overridden by the fork or the user. |
| Keychron caps-lock LED 48 | **[V]** still active: `os_state_indicate` 0x0800B494 does `rgb_matrix_set_color(48, 255,255,255)` when host caps-lock is on; reached via `rgb_matrix_indicators_kb` 0x0800C702 → `rgb_matrix_indicators_keychron` 0x0800C6C6 → `rgb_matrix_indicators_bt` 0x0800B4C4 (and from `rgb_matrix_none_indicators_kb` 0x0800B800 / `led_update_kb` 0x0800B91C). It is painted after the user's pass over LEDs 36..53, so LED 48 stays white under any layer colour while host caps-lock is on. |
| Config implied | **[V]** `#define RGB_MATRIX_DEFAULT_MODE RGB_MATRIX_TYPING_HEATMAP` (compiled default byte 0x41 vs stock 0x15). HSV/speed/flags defaults unchanged from stock (0,255,255 / 127 / 0xFF). |

---

## 2. `keyboard_post_init_user` @ 0x0800CF60 (20 bytes) **[V]**

```
0800cf60: push  {r3, lr}
0800cf62: movs  r0, #0
0800cf64: bl    0x0800dbe2      ; default_layer_set   (= b.w default_layer_state_set 0x0800dbd0, strh -> 0x20001630)
0800cf68: pop.w {r3, lr}
0800cf6c: movs  r0, #0x10       ; 16
0800cf6e: b.w   0x08010d40      ; rgb_matrix_mode
```
Reached by tail call from the fork's `keyboard_post_init_kb` (0x0800CD76 `b.w 0x0800cf60`), whose body
matches `v10_max.c` (palSetLineMode x2, BAT_LOW_LED on, lkbt51_init, wireless_init, timer_read32,
encoder_cb_init, then user).

* `default_layer_set(0)`: argument is literally 0, not `1<<0`. Effect: `default_layer_state = 0` (layer 0).
  This undoes the fork's `dip_switch_update_kb` (0x0800CD18, stock: `default_layer_set(1UL << (active ? 0 : 2))`)
  which ran during `keyboard_init`, so the keyboard always boots on layer 0 regardless of the Mac/Win switch.
  (Flipping the switch later still calls `dip_switch_update_kb`; then `default_layer_state = 1<<2` and the
  indicator below shows layer 2 = blue.) Nothing writes EEPROM here; `eeprom_recovered` default_layer 0 is consistent.
* `rgb_matrix_mode(16)`: 0x08010D40 is `movs r1,#1; b.w 0x08010d04` (= `rgb_matrix_mode_eeprom_helper(mode, true)`),
  identical to `rgb_matrix_mode` in `refs/ref1011_default.elf` @0x0800EB0C. A `movs r1,#0` twin (`_noeeprom`) does
  not exist anywhere in the image (scan of every `movs r1,#0; b.w 0x08010d04` pair: none). So this is the
  EEPROM-writing `rgb_matrix_mode`, not `rgb_matrix_mode_noeeprom`.
  The helper (decompile 0x08010D04): only acts if `rgb_matrix_config.enable`; clamps mode (0→1, ≥23→22),
  sets `rgb_task_state = STARTING`, calls `eeconfig_flag_rgb_matrix(true)`.
* Absent: no `tap_dance_actions[0].user_data` store (dactyl hypothesis item 9 — **not present**), no
  `rgb_matrix_enable()`, no `rgb_matrix_sethsv`, no debug config.

### What mode 16 is **[V]**
`refs/ref1011_default.elf` DWARF (same fork commit, same board → same `ENABLE_RGB_MATRIX_*` set from
`v10_max/info.json`): `RGB_MATRIX_NONE=0, SOLID_COLOR=1, BREATHING=2, CYCLE_LEFT_RIGHT=5, PIXEL_RAIN=15,
TYPING_HEATMAP=16, DIGITAL_RAIN=17, SOLID_REACTIVE_SIMPLE=18, SPLASH=21, EFFECT_MAX=23`.
The dump uses the same enumeration: its `rgb_task_render` (0x08010A4C) has 23 `case`s and the mode clamp
uses `cmp r6,#22` (0x08010A8A) / `movs r3,#22` (0x08010D30) = `EFFECT_MAX-1`. Hence 16 = `RGB_MATRIX_TYPING_HEATMAP`
(needs `RGB_MATRIX_FRAMEBUFFER_EFFECTS`, which `ansi_encoder/config.h` defines). This upgrades the
`eeprom_recovered.md` "likely" to verified.

---

## 3. `rgb_matrix_indicators_advanced_user` @ 0x0800CF74 (156 bytes) **[V]**

Caller chain (all stock QMK 0.23 code, matched to the ref): `rgb_matrix_task` 0x08011058 →
`rgb_matrix_indicators_advanced` 0x08010C54 (`ldrb iter; subs #1; bl rgb_matrix_get_limits 0x0801017E;
bl 0x08010c4c`) → `rgb_matrix_indicators_advanced_kb` 0x08010C4C (`push {r3,lr}; bl 0x0800cf74; pop {r3,pc}`,
identical to the weak default in the ref @0x0800EA14) → user.

### LED ranges **[V]**
`rgb_matrix_get_limits` 0x0801017E: `r0*9<<1` (=18·(iter-1)), `+18`, clamp to 88. So
`RGB_MATRIX_LED_PROCESS_LIMIT` is the QMK default `(88+4)/5 = 18` and the hook is called 5× per frame with
`(0,18) (18,36) (36,54) (54,72) (72,88)`. Not "all 88 at once" — but the loop covers every LED in each chunk.

### Body
```
0800cf78: ldr r6,=0x2000162e  ; layer_state (u16)
0800cf7a: ldr r7,=0x20001630  ; default_layer_state (u16)
0800cf7c: ldr r8,=0x200015dd  ; gui_active
0800cf80: r5 = led_max ; r4 = i = led_min
0800cf84: uxtb r3,r4 ; cmp r5,r3 ; bhi body      ; while ((uint8_t)i < led_max)
0800cf8a: movs r0,#0 ; pop                       ; return false
0800cf90: ldrh r0,[r6] ; ldrh r3,[r7] ; orrs ; uxth ; bl biton16 (0x0800d488)   ; get_highest_layer(layer_state|default_layer_state)
0800cf9c: subs r0,#1 ; cmp r0,#4 ; bhi 0800cfb8  ; switch: layers 1..5 only
0800cfa2: tbb [pc,r0]   table bytes @0800cfa6 = 18 03 14 1b 1e
   layer1 -> 0800cfd6: r3=0    r2=0xff  (b 0800cfb0: r1=0)      -> set_color(i, 0x00,0xFF,0x00)  GREEN
   layer2 -> 0800cfac: r3=0xff r2=0     r1=0                     -> set_color(i, 0x00,0x00,0xFF)  BLUE
   layer3 -> 0800cfce: r3=0    r2=0x80  r1=0xff                  -> set_color(i, 0xFF,0x80,0x00)  ORANGE
   layer4 -> 0800cfdc: r3=0x80 r2=0x80  (b 0800cfb0: r1=0)      -> set_color(i, 0x00,0x80,0x80)  TEAL
   layer5 -> 0800cfe2: r3=0    r2=0     (b 0800cfd2: r1=0xff)   -> set_color(i, 0xFF,0x00,0x00)  RED
0800cfb4: bl 0x0800fe78  ; rgb_matrix_set_color(i, r1, r2, r3)
0800cfb8: ldrb r3,[r8] ; cbz -> 0800cfe8          ; if (gui_active)
0800cfbe:   r2=0xff r3=0 r1=0xff r0=i ; bl set_color   ->  (0xFF,0xFF,0x00) YELLOW
0800cfca: adds r4,#1 ; b 0800cf84                 ; i++
0800cfe8: ldrb 0x200015de | ldrb 0x200015dc ; beq 0800cfca   ; else if (shift_active | caps_active)
0800cff4:   r3=r2=r1=0xff ; b 0800cfc4 -> set_color(i, 0xFF,0xFF,0xFF)  WHITE
```
Colour constants are exactly QMK `quantum/color.h`: `RGB_GREEN, RGB_BLUE, RGB_ORANGE (FF,80,00), RGB_TEAL
(00,80,80), RGB_RED, RGB_YELLOW, RGB_WHITE`. The values are RGB (not HSV): `rgb_matrix_set_color` 0x0800FE78 is the
stock driver trampoline (`ldr r4,[driver+4]; bx`).

### Semantics **[V]**
* Per-LED priority: **yellow (OSM GUI active) > white (OSM Shift active OR caps flag) > layer colour > animation**.
  Yellow and white are exclusive (`else if`); layer colour is always painted first and then overwritten.
* Layer colours: 1 green, 2 blue, 3 orange, 4 teal, 5 red; layer 0 (and any layer >5) leaves the animation
  (typing heatmap) visible. Since `default_layer_state` is OR-ed in, a Mac→Win DIP toggle at runtime
  (`default_layer_set(1<<2)`) paints the board blue when no higher layer is active; at boot this does not happen because
  `keyboard_post_init_user` resets `default_layer_state` to 0 after `dip_switch_init`.
* Whenever layer ≥1 or any flag is set, every LED is overwritten each frame, so the RGB animation is only visible
  on layer 0 with no indicator active.
* Return value `false` (the stock weak returns `true`); nothing in the call chain consumes it.
* `get_highest_layer(...)` is evaluated inside the loop (the `bl biton16` is in the loop body) — matches a source
  that calls it in the loop (cannot be hoisted across an external call by the compiler).

### Recompile check **[V]**
In-tree compile with the dump's compiler (gcc 13.2.1, QMK flags) as part of the final keymap: the function is
**masked-identical** to 0x0800CF74..0x0800D00F (`tools/final_compile_compare.py`). Two source details were pinned
down by that compile-compare (`tools/rgb_hooks_spelling_search.py`, 2880 variants): (1) the three flags are
`uint8_t`, not `bool` — with `bool` gcc 13 emits `ldrb; cbnz; ldrb; cmp; beq` for the white test whereas the dump
has `orrs` of both bytes (which `||` and `|` both produce for `uint8_t`, so that spelling stays undecidable);
(2) the `switch` lists the cases in the order 2, 3, 1, 4, 5 — that order reproduces the dump's tbb table
`18 03 14 1B 1E` with the layer-2 block inline; the natural order 1..5 gives `03 14 17 1B 1E` with gcc 13 as well,
so this is a source-order fact, not a compiler-version effect. Switch vs if/else-if chain remains indistinguishable.

---

## 4. One-shot modifier indicator: 0x0800D088 / 0x0800D08C → body 0x0800D010 **[V]**

* 0x0800D088 = `b.w 0x0800d010`, called from `oneshot_mods_changed_kb` 0x0800E3E4 (`clear_oneshot_mods` 0x0800E424
  clears 0x200016A6 = `oneshot_mods` and calls it) ⇒ `oneshot_mods_changed_user`.
* 0x0800D08C = `b.w 0x0800d010`, called from `oneshot_locked_mods_changed_kb` 0x0800E38C (`clear_oneshot_locked_mods`
  0x0800E3B0 clears 0x200016A5 = `oneshot_locked_mods`) ⇒ `oneshot_locked_mods_changed_user`.
  Two 4-byte thunks to one body = two identical functions (a shared static helper, or ICF).
* The body uses its `mods` **argument** (not `get_oneshot_mods()`): `ands r5,r0,#0x22` (`MOD_MASK_SHIFT`),
  `bic r4,r0,#0x77` (≡ `mods & 0x88` = `MOD_MASK_GUI`, as bits 0x77 are the only other bits of a u8).

`mods` is the hook ARGUMENT: QMK's `add_oneshot_mods()` (used by OSM taps, `action.c:460`) passes only the newly added
mods (`action_util.c:501`), while del/set/clear pass the resulting state. So the flags reflect the last one-shot change:
stacking OSM(Shift) then OSM(GUI) yields calls with 0x02 then 0x08, and the second call turns the board yellow and drops
`shift_active` although Shift is still pending. Stock core feeding user code; the reconstruction reproduces it.

Behaviour table derived from the disassembly (S/G = shift/gui bit in `mods`; s/g = `shift_active`/`gui_active`):

| Case | Actions, in order |
|---|---|
| S=0, s=1 | `set_color_all(0,0,0)`, s=0 (0x0800D022-D02C); then **only if G**: if !g `set_color_all(FF,FF,00)`, g=1 (0x0800D030-D040). g is *not* cleared here even if G=0 (`cbz r4 → pop` @0x0800D02E). |
| S=0, s=0, G=0 | if g: `set_color_all(0,0,0)`, g=0 (0x0800D04A-D05A); return |
| S=0, s=0, G=1 | if !g: `set_color_all(FF,FF,00)`, g=1 (0x0800D07C → D030) |
| S=1, G=0 | if g: `set_color_all(0,0,0)`, g=0; then if !s: `set_color_all(FF,FF,FF)`, s=1 (0x0800D05C-D076 → D02E → pop) |
| S=1, G=1 | if !s: `set_color_all(FF,FF,FF)`, s=1; then if !g: `set_color_all(FF,FF,00)`, g=1 (0x0800D078 → D060 → D02E → D030) |

The only C structure that yields exactly these orders (calls to the same external function cannot be reordered)
is the one in `rgb_hooks.c`:
```c
if (!(mods & MOD_MASK_SHIFT) && shift_active)      { OFF;    shift_active = false; }
else if (!(mods & MOD_MASK_GUI) && gui_active)     { OFF;    gui_active   = false; }
if ((mods & MOD_MASK_SHIFT) && !shift_active)      { WHITE;  shift_active = true;  }
if ((mods & MOD_MASK_GUI)   && !gui_active)        { YELLOW; gui_active   = true;  }
```
**Recompiled with gcc 15.2 -Os this produces the identical 0x6E-byte instruction sequence** (every opcode and
branch offset equal to 0x0800D010..0x0800D07D: `bne +0x34`, `cbz r4,+0x32`, `cbnz r4,+0x68`, `bne +0x1e`,
`b +0x20`, ...), and the two wrappers compile to the same `b.w` thunks. Colours: white for Shift, yellow for GUI,
off when released; `rgb_matrix_set_color_all` 0x0800FEE4 is the stock driver trampoline (→ `snled27351_set_color_all`).

**Dactyl comparison:** the dactyl `handle_oneshots` (LM 450-477) has a `return;` after every branch and tests
`(mods & SHIFT && !shift_active)` first; it would emit at most one action per call (e.g. S=1,G=0,g=1 gives only
"on shift", no "off gui"). The dump does two actions in that case. So the V10 Max version is a different
(earlier) formulation — the dactyl code is **not** what is in the dump. The dactyl's "flag-only version" guess is
half right: flags plus one-frame `set_color_all` flashes.

Practical effect: `set_color_all` only survives until the next animation frame; the persistent white/yellow
board comes from `rgb_matrix_indicators_advanced_user` reading the flags every frame. `ONESHOT_TAP_TOGGLE`/locked
one-shots therefore keep the board coloured until the lock is released (both hooks share the body).

---

## 5. The three flag bytes **[V]**

Literal-pool scan of the whole code region (0x08008000..0x08016704) for the addresses; every reference:

| RAM | Name | Readers | Writers |
|---|---|---|---|
| 0x200015DC | `caps_active` | indicator 0x0800CFEA | `process_record_user`: `strb #1` @0x0800D16A when `KC_CAPS` pressed and `host_keyboard_led_state().caps_lock`==0 (0x0800D15E `bl 0x08012148`, `lsls r2,r0,#30; bmi`), `strb #0` @0x0800D17A when it was 1 (second `bl host_keyboard_led_state` @0x0800D170). Nothing else. |
| 0x200015DD | `gui_active` | indicator 0x0800CFB8 (via r8) | one-shot body 0x0800D040 (=1), 0x0800D05A (=0); OSM helper 0x0800D0B4 `strb #0` @0x0800D0EE |
| 0x200015DE | `shift_active` | indicator 0x0800CFEC | one-shot body 0x0800D02C (=0), 0x0800D074 (=1); OSM helper `strb #0` @0x0800D0EA |

* Meaning: `caps_active` = "this keyboard toggled caps lock on" (mirrors the dactyl LM `process_record_user`
  lines 183-191 with `rgblight_set_layer_state(3,x)` replaced by the flag). It is not synced from the host LED
  report (`led_update_user` 0x0800D4B2 is stock), so caps toggled from another device desyncs it; the Keychron
  LED-48 indicator (below) remains host-accurate.
* `gui_active` / `shift_active` = "a one-shot GUI / Shift modifier is currently active (or locked)".
* There is **no leader flag**: `leader_start_user` 0x0800CDF4 is only `rgb_matrix_set_color_all(0xFF,0x00,0xFF)`
  (magenta, one frame) and `leader_end_user` 0x0800CDFE starts with `rgb_matrix_set_color_all(0,0,0)`; neither
  touches RAM flags (dactyl's `leader_active` variable is **not present**).
* .bss layout DC/DD/DE then 0x200015E0/E4 (`held_osm[]`, a 2-pointer table used by the OSM helper) and 0x200015E8/E9
  (tap-dance flags). GCC emits file-scope statics in REVERSE definition order (verified with both gcc 13.2.1 and 15.2 in-tree),
  so the declaration order in the TU was `return_to_mouse, move_to_lower, held_osm[], shift_active, gui_active, caps_active`
  — exactly the dactyl LM order — **[V]** (the reverse of what an earlier draft of this report assumed).

---

## 6. Other hooks — stock or custom? **[V]**

| Hook | Dump | Verdict |
|---|---|---|
| `layer_state_set_user` | 0x0800DC18 `bx lr`, called from `layer_state_set_kb` 0x0800DC1A (`push; bl; pop`), then `layer_state_set` 0x0800DC24 stores u16 → 0x2000162E | stock weak (or an identity implementation — indistinguishable and behaviourally identical). No per-layer logic here. |
| `default_layer_state_set_user` | 0x0800DBC4 `bx lr` | stock |
| `housekeeping_task_user` | 0x0800E768, 2 bytes `bx lr` (hooks.csv exact match) | stock (dactyl DS poller **not present**) |
| `matrix_scan_user` | 0x0800ED16, 2 bytes | stock |
| `rgb_matrix_indicators_user` | 0x0801017A `movs r0,#1; bx lr` | stock weak |
| `led_update_user` / `led_set_user` | 0x0800D4B2 / 0x0800D4B0, stock matches | stock |
| `oneshot_layer_changed_user` | 0x0800D25C: `if (layer==0 && *0x200015E9) { layer_clear(); layer_move(4); *0x200015E9 = 0; }` | **custom** (tap-dance "return to mouse layer"; owned by the tap-dance target) |
| `eeconfig_init_user`, `shutdown_user`, `suspend_*_user`, `pre/post_process_record_user` | stock matches (hooks.csv) | stock |
| `dip_switch_update_user` | 0x0800CCF0 = the fork's own `factory_test.c` implementation (OS-switch report via `factory_test_send`; instruction-identical to ref @0x0800B004) | fork code, not keymap code |

## 7. Keychron's own indicator path **[V]**

* `rgb_matrix_indicators_advanced_kb` 0x08010C4C is the stock weak wrapper; the fork never overrides it.
* `rgb_matrix_indicators_kb` 0x0800C702 = fork `keychron_task.c`: `if (rgb_matrix_indicators_user()) rgb_matrix_indicators_keychron();`
  → 0x0800C6C6 = `rgb_matrix_indicators_bt()` 0x0800B4C4 + `factory_test_indicator()` 0x0800CA18, `return true`.
* 0x0800B4C4 = `indicator.c` `LED_INDICATORS_KB` (`rgb_matrix_indicators_bt`): battery-critical blackout, low-battery
  LEDs `{81, 83}` (`set_color(0x51/0x53, …)`, `LOW_BAT_IND_INDEX`), BT host LEDs `{17,18,19}` (table 0x0801672B) /
  P2P4G LED 20 (`0x14`), else `os_state_indicate()`.
* `os_state_indicate` 0x0800B494: `if (!(get_transport()==USB && usb_state==SUSPENDED) && host_keyboard_led_state().caps_lock)
  rgb_matrix_set_color(0x30 /*48 = CAPS_LOCK_INDEX*/, 0xFF,0xFF,0xFF);` — present and unchanged.
* Order inside a frame (dump `rgb_matrix_task` 0x08011110-0x0801112A): `rgb_task_render(effect)`; if `effect` and
  `rgb_task_state == FLUSHING` (`cmp r3,#2` — i.e. after the last of the 5 iterations) → `rgb_matrix_indicators_kb()`
  (Keychron caps LED 48 white); then `rgb_matrix_indicators_advanced(&params)` for the last chunk `(72,88)` only.
  LED 48 was painted by the user hook in iteration 3 `(36,54)` in an earlier `rgb_matrix_task` call, so **the Keychron
  white caps-lock LED 48 wins over the user's layer colour whenever host caps lock is on**; when the user's `caps_active`
  is set the whole board is white anyway.
* `rgb_matrix_none_indicators_kb` 0x0800B800 and `led_update_kb` 0x0800B91C also call `os_state_indicate` (stock fork).

## 8. Config **[V]**

`eeconfig_update_rgb_matrix_default` 0x0800FE14: `movs r3,#0x41; strb` → `rgb_config_t` byte 0 = `enable:2 = 1,
mode:6 = 0x41>>2 = 16`; `memcpy(hsv, 0x08016710, 3)` = `{0, 255, 255}`; `strh 0xff7f,[+4]` → speed 0x7F, flags 0xFF.
The stock reference (`ref1011_default.elf` @0x0800DB3C) has `movs r3,#0x15` (mode 5 = `RGB_MATRIX_CYCLE_LEFT_RIGHT`,
QMK's fallback default) and the same HSV/speed/flags. Therefore the keymap's `config.h` contained:

```c
#define RGB_MATRIX_DEFAULT_MODE RGB_MATRIX_TYPING_HEATMAP
```
and did **not** change `RGB_MATRIX_DEFAULT_HUE/SAT/VAL/SPD` (all stock). The EEPROM contents (mode 16, hue 8,
sat 239, val 47, speed 191 from `eeprom_recovered`) are runtime adjustments via the RGB keys/encoder, not compiled
defaults; `keyboard_post_init_user` re-forces mode 16 at every boot while RGB is enabled (`rgb_matrix_mode()` returns early
when `rgb_matrix_config.enable == 0`) and unconditionally flags the RGB config for an EEPROM flush.

No `rules.mk` lines are implied by this target: `RGB_MATRIX_ENABLE` comes from the board `info.json`; the one-shot
hooks need no feature flag.

## 9. Dactyl hypotheses vs. dump

| Dactyl expectation | Dump |
|---|---|
| `keyboard_post_init_user` stores `tap_dance_actions[0].user_data` | **Not present** — only `default_layer_set(0)` + `rgb_matrix_mode(16)`. |
| `handle_oneshots` with early `return`s | **Different structure** (see §4); same intent (shift/gui flags). |
| `layer_state_set_user` drives per-layer colours | **Not present**; per-layer colours are computed each frame in `rgb_matrix_indicators_advanced_user` instead. |
| `leader_active` flag | **Not present**; leader start/end only flash magenta/off. |
| "no dactyl version implements `rgb_matrix_indicators_*`" | The V10 Max **does** implement `rgb_matrix_indicators_advanced_user` (§3). |
| Caps handling via `host_keyboard_led_state().caps_lock` on `KC_CAPS` press | **Present**, flag-based (§5). |
| Dactyl colours blue/yellow/green/goldenrod/pink/red/white/teal (rgblight HSV layers) | V10 Max uses RGB constants green/blue/orange/teal/red for layers 1-5, white/yellow for Shift/GUI-or-caps. |

## 10. Open questions

* Exact source spelling of two codegen details in the indicator loop (case order in the `switch`; `||` vs `|` in the
  white test) — semantics verified, spelling **[L]** (gcc 13.2 vs local 15.2 differences).
* Whether `oneshot_mods_changed_user`/`oneshot_locked_mods_changed_user` were two literal copies or one static helper
  — indistinguishable after ICF/tail-call; reconstruction uses a helper.
* Whether `layer_state_set_user` was absent or an explicit identity `return state;` — indistinguishable (`bx lr`).
