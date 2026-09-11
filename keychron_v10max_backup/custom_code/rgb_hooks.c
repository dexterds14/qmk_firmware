/*
 * Reconstructed RGB / indicator / boot hooks of the lost Keychron V10 Max keymap.
 * Recovered from keychron_v10max_backup/dump_a.bin (flash @0x08000000), QMK 0.23.2-era
 * Keychron wireless_playground fork, built 2024-07-09 with arm-none-eabi-gcc 13.2.1 -Os.
 *
 * Evidence per function is in custom_code/rgb_hooks.md. Summary of dump addresses:
 *   keyboard_post_init_user               0x0800CF60  (tail-called from keyboard_post_init_kb @0x0800CD76)
 *   rgb_matrix_indicators_advanced_user   0x0800CF74  (called from stock weak _kb wrapper @0x08010C4C)
 *   handle_oneshots (shared body)         0x0800D010
 *   oneshot_mods_changed_user             0x0800D088  = "b.w 0x0800D010"
 *   oneshot_locked_mods_changed_user      0x0800D08C  = "b.w 0x0800D010"
 *   caps_active   (uint8_t)               RAM 0x200015DC  (written only by process_record_user, KC_CAPS branch)
 *   gui_active    (uint8_t)               RAM 0x200015DD
 *   shift_active  (uint8_t)               RAM 0x200015DE
 *
 * Verification: compiled in-tree with the dump's compiler (gcc 13.2.1) as part of the final keymap
 * (reconstructed_keymap/keymap.c), all four functions and both thunks are masked-identical to the
 * dump (tools/final_compile_compare.py). Two source details were pinned down by that compile-compare
 * (tools/rgb_hooks_spelling_search.py): the flags are uint8_t (bool gives a cbnz/cmp form instead of
 * the dump's `orrs` in the white test) and the switch lists the layers in the order 2, 3, 1, 4, 5
 * (that order reproduces the dump's tbb table 18 03 14 1B 1E with the layer-2 block inline).
 *
 * config.h lines implied by this target (see rgb_hooks.md, "Config"):
 *   #define RGB_MATRIX_DEFAULT_MODE RGB_MATRIX_TYPING_HEATMAP   // compiled default byte 0x41 @0x0800FE1C
 * No rules.mk lines are implied by this target (RGB_MATRIX is enabled by the board's info.json).
 *
 * Hooks checked and found to be the STOCK weak defaults (not implemented by the keymap):
 *   layer_state_set_user 0x0800DC18 (bx lr), default_layer_state_set_user 0x0800DBC4 (bx lr),
 *   housekeeping_task_user 0x0800E768 (bx lr), matrix_scan_user 0x0800ED16 (bx lr),
 *   rgb_matrix_indicators_user 0x0801017A (movs r0,#1; bx lr), led_update_user 0x0800D4B2 (stock).
 */

#include QMK_KEYBOARD_H

/* ---- Indicator state flags (.bss 0x200015DC caps / DD gui / DE shift) ----
 * uint8_t, not bool (see header). GCC emits statics in reverse definition order, so this declaration
 * order (shift, gui, caps -- the dactyl's) yields the ascending dump layout caps < gui < shift. In the
 * full keymap they are preceded by return_to_mouse, move_to_lower and held_osm[] (process_record_user.c). */
static uint8_t shift_active;  /* 0x200015DE: a one-shot Shift mod is active -> board white               */
static uint8_t gui_active;    /* 0x200015DD: a one-shot GUI mod is active -> board yellow                */
static uint8_t caps_active;   /* 0x200015DC: toggled in process_record_user on KC_CAPS press (see note below) */

/* ---- Boot hook -------------------------------------------------------------------------
 * 0x0800CF60: push {r3,lr}; movs r0,#0; bl default_layer_set(0x0800DBE2); pop {r3,lr};
 *             movs r0,#0x10; b.w rgb_matrix_mode(0x08010D40 = "movs r1,#1; b.w rgb_matrix_mode_eeprom_helper")
 * Nothing else: no tap_dance_actions[].user_data store, no rgb_matrix_enable(), no debug flags.
 * rgb_matrix_mode() is the EEPROM-writing variant (not _noeeprom); it is a no-op while RGB is toggled off
 * (rgb_matrix_config.enable == 0) and otherwise unconditionally flags the RGB config for an EEPROM flush.
 * Mode 16 == RGB_MATRIX_TYPING_HEATMAP in this board's animation set (DWARF of refs/ref1011_default.elf;
 * dump's effect switch has 23 cases, RGB_MATRIX_EFFECT_MAX = 23, "cmp r6,#22" @0x08010A8A).
 * default_layer_set(0) forces default_layer_state = 0 (i.e. layer 0) regardless of the Mac/Win DIP
 * switch, which the fork's dip_switch_update_kb (0x0800CD18) had just set to 1<<0 or 1<<2 during init.
 */
void keyboard_post_init_user(void) {
    default_layer_set(0);
    rgb_matrix_mode(RGB_MATRIX_TYPING_HEATMAP); /* = rgb_matrix_mode(16) in the binary */
}

/* ---- Per-frame indicator hook -----------------------------------------------------------
 * 0x0800CF74..0x0800D00F. Signature bool(uint8_t led_min, uint8_t led_max); returns false (movs r0,#0 @0x0800CF8A).
 * Called 5x per frame by the stock rgb_matrix_indicators_advanced (0x08010C54) -> weak _kb (0x08010C4C) with
 * ranges [0,18) [18,36) [36,54) [54,72) [72,88) (RGB_MATRIX_LED_PROCESS_LIMIT default (88+4)/5 = 18,
 * rgb_matrix_get_limits @0x0801017E: idx*18, +18, clamp 88).
 *
 * Loop: for (i = led_min; i < led_max; i++)  (uxtb r3,r4; cmp r5,r3; bhi @0x0800CF84-CF88; adds r4,#1 @0x0800CFCA)
 * Layer colour: get_highest_layer(layer_state | default_layer_state)  (ldrh 0x2000162E | ldrh 0x20001630; bl biton16
 *   @0x0800CF90-CF98), then "subs r0,#1; cmp r0,#4; bhi" + tbb @0x0800CFA2 with table bytes {18,03,14,1B,1E}:
 *     layer 1 -> 0x0800CFD6: (0x00,0xFF,0x00) RGB_GREEN
 *     layer 2 -> 0x0800CFAC: (0x00,0x00,0xFF) RGB_BLUE
 *     layer 3 -> 0x0800CFCE: (0xFF,0x80,0x00) RGB_ORANGE
 *     layer 4 -> 0x0800CFDC: (0x00,0x80,0x80) RGB_TEAL
 *     layer 5 -> 0x0800CFE2: (0xFF,0x00,0x00) RGB_RED
 *     layer 0 / >5 -> no per-layer colour (animation shows through)
 * Overlay (after the layer colour, same LED): if gui_active -> (0xFF,0xFF,0x00) RGB_YELLOW @0x0800CFBE-CFC6;
 *   else if (shift_active | caps_active) -> (0xFF,0xFF,0xFF) RGB_WHITE @0x0800CFE8-CFFA.
 * Priority per LED: yellow (OSM GUI) > white (OSM Shift or Caps) > layer colour > animation.
 */
bool rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {
    for (uint8_t i = led_min; i < led_max; i++) {
        switch (get_highest_layer(layer_state | default_layer_state)) { /* case order 2,3,1,4,5 reproduces the dump's block layout */
            case 2: rgb_matrix_set_color(i, RGB_BLUE);   break;
            case 3: rgb_matrix_set_color(i, RGB_ORANGE); break;
            case 1: rgb_matrix_set_color(i, RGB_GREEN);  break;
            case 4: rgb_matrix_set_color(i, RGB_TEAL);   break;
            case 5: rgb_matrix_set_color(i, RGB_RED);    break;
            default: break;
        }
        if (gui_active) {
            rgb_matrix_set_color(i, RGB_YELLOW);
        } else if (shift_active || caps_active) {
            rgb_matrix_set_color(i, RGB_WHITE);
        }
    }
    return false;
}

/* ---- One-shot modifier indicator ----------------------------------------------------------
 * Shared body 0x0800D010..0x0800D07D; both user hooks are 4-byte "b.w 0x0800D010" thunks
 * (0x0800D088 <- oneshot_mods_changed_kb 0x0800E3E4, 0x0800D08C <- oneshot_locked_mods_changed_kb 0x0800E38C).
 * Uses the mods ARGUMENT: "ands r5,r0,#0x22" (MOD_MASK_SHIFT) and "bic r4,r0,#0x77" (== mods & 0x88, MOD_MASK_GUI).
 * Behaviour table verified against the disassembly (S/G = shift/gui bit in mods, s/g = flags):
 *   S=0,s=1        : set_color_all(OFF), s=0;                 then if G && !g: set_color_all(YELLOW), g=1
 *   S=0,s=0,G=0    : if g: set_color_all(OFF), g=0
 *   S=0,s=0,G=1    : if !g: set_color_all(YELLOW), g=1
 *   S=1,G=0        : if g: set_color_all(OFF), g=0;           then if !s: set_color_all(WHITE), s=1
 *   S=1,G=1        : if !s: set_color_all(WHITE), s=1;        then if !g: set_color_all(YELLOW), g=1
 * NOTE: this is NOT the dactyl handle_oneshots() (which has "return;" after every branch and would emit
 * only one action per call); the structure below recompiles to the identical instruction sequence.
 * `mods` is the hook argument: add_oneshot_mods() passes only the newly ADDED mods (action_util.c:501),
 * del/clear pass the remaining state, so the flags track the last one-shot change (stacking OSM(Shift)
 * then OSM(GUI) turns the board yellow and drops shift_active while Shift is still pending).
 * The set_color_all() calls only last one frame (the animation repaints); the persistent board colour
 * comes from the flags read every frame by rgb_matrix_indicators_advanced_user above.
 * The flags are also cleared (both to 0) by the OSM helper at 0x0800D0B4 (strb @0x0800D0EA/0x0800D0EE),
 * which belongs to the process_record_user target.
 */
static void handle_oneshots(uint8_t mods) {
    if (!(mods & MOD_MASK_SHIFT) && shift_active) {
        rgb_matrix_set_color_all(RGB_OFF);
        shift_active = 0;
    } else if (!(mods & MOD_MASK_GUI) && gui_active) {
        rgb_matrix_set_color_all(RGB_OFF);
        gui_active = 0;
    }
    if ((mods & MOD_MASK_SHIFT) && !shift_active) {
        rgb_matrix_set_color_all(RGB_WHITE);
        shift_active = 1;
    }
    if ((mods & MOD_MASK_GUI) && !gui_active) {
        rgb_matrix_set_color_all(RGB_YELLOW);
        gui_active = 1;
    }
}

void oneshot_mods_changed_user(uint8_t mods) {
    handle_oneshots(mods);
}

void oneshot_locked_mods_changed_user(uint8_t mods) {
    handle_oneshots(mods);
}

/* ---- Where caps_active is written (belongs to the process_record_user target, shown for completeness) ----
 * 0x0800D134: ldrb r3,[r6,#5]      ; record->event.pressed
 * 0x0800D138: cmp r4,#0x39         ; KC_CAPS
 * 0x0800D15E: bl host_keyboard_led_state; lsls r2,r0,#30; bmi 0x0800D170   ; caps_lock bit clear ->
 * 0x0800D166: strb #1 -> 0x200015DC                                          ;   caps_active = true
 * 0x0800D170: bl host_keyboard_led_state; lsls r3,r0,#30; bpl ret            ; caps_lock bit set ->
 * 0x0800D178: strb #0 -> 0x200015DC                                          ;   caps_active = false
 * i.e. exactly the dactyl LM lines 183-191 with rgblight_set_layer_state(3, x) replaced by the flag:
 *
 *   if (record->event.pressed) {
 *       if (keycode == KC_CAPS && !host_keyboard_led_state().caps_lock) {
 *           caps_active = true;
 *       } else if (keycode == KC_CAPS && host_keyboard_led_state().caps_lock) {
 *           caps_active = false;
 *       }
 *       ...
 *   }
 * Nothing else writes 0x200015DC (literal-pool scan of the whole code region).
 */

/* ---- Related but NOT part of this file's hooks ----
 * oneshot_layer_changed_user 0x0800D25C IS implemented (tap-dance "return to mouse layer" logic, flag 0x200015E9):
 *     void oneshot_layer_changed_user(uint8_t layer) {
 *         if (layer == 0 && return_to_mouse) { layer_clear(); layer_move(4); return_to_mouse = false; }
 *     }
 *   -> documented/owned by the tap-dance target.
 * leader_start_user 0x0800CDF4 = rgb_matrix_set_color_all(0xFF,0x00,0xFF) (RGB_MAGENTA, one-frame flash;
 *   "movs r2,#0xff; movs r1,#0; mov r0,r2; b.w 0x0800FEE4");
 *   leader_end_user 0x0800CDFE starts with rgb_matrix_set_color_all(0,0,0) (RGB_OFF) -> leader target.
 *   Neither touches the three flags above; there is no "leader active" flag in this firmware.
 */
