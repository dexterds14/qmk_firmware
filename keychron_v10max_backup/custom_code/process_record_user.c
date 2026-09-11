/*
 * Reconstructed from keychron_v10max_backup/dump_a.bin (flash @0x08000000),
 * custom keymap.c translation unit 0x0800CCF0..0x0800D2CC.
 *
 * This file covers:
 *   process_record_user               @0x0800D104 (180 B)
 *   check_unlock_osm                  @0x0800D0B4 (66 B)   -- sub_0800d0b4
 *   find_osm_slot                     @0x0800D090 (32 B)   -- sub_0800d090
 *   handle_oneshots                   @0x0800D010 (110 B)  -- sub_0800d010 (shared body)
 *   oneshot_mods_changed_user         @0x0800D088 (4 B thunk -> 0x0800D010)
 *   oneshot_locked_mods_changed_user  @0x0800D08C (4 B thunk -> 0x0800D010)
 *   the .bss flags they share (0x200015DC..0x200015E9)
 *
 * Evidence and the verified/likely/uncertain split are in process_record_user.md.
 * The tap dance (TD(0)), oneshot_layer_changed_user, leader, keyboard_post_init_user
 * and rgb_matrix_indicators_advanced_user bodies are other targets; they use the same
 * static flags, so when the final keymap.c is assembled, keep ONE definition of each
 * variable below.
 *
 * Compiles against the Keychron wireless_playground fork (QMK 0.23.2 era) keymap for
 * keyboards/keychron/v10_max/ansi_encoder; needs TAP_DANCE_ENABLE = yes (TD(0) compare),
 * RGB_MATRIX_ENABLE (rgb_matrix_set_color_all) and the default (not NO_ACTION_ONESHOT) build.
 */

#include QMK_KEYBOARD_H
#include "keychron_common.h"

/* Layer numbers as used by the code (names borrowed from the dactyl sibling keymap,
 * only the numbers are verified: layer_state_is(1) at 0x0800D12A, TD(0) at 0x0800D11A). */
enum layers {
    _QWERTY = 0,
    _LOWER  = 1,
    _RAISE  = 2,
    _RAISE2 = 3,
    _MOUSE  = 4,
    _LEADR  = 5,
};

/* Custom keycodes: only 0x7E40 and 0x7E41 are tested (0x0800D17E, 0x0800D1A2).
 * SAFE_RANGE == QK_USER == QK_USER_0 == 0x7E40 in this fork (quantum/quantum_keycodes.h:37,
 * quantum/keycodes.h:81/758). Names follow the behaviour: "./" and "../". */
enum custom_keycodes {
    DOT_SLS = SAFE_RANGE, /* 0x7E40: types "./"  */
    DIR_UP,               /* 0x7E41: types "../" */
};

/* Tap-dance index 0 (the only TD in the keymap). The finished/reset bodies are the tap-dance target. */
enum tap_dance_keys {
    LAYR_DOWN = 0,
};

/* ---- shared .bss state (addresses in the dump) -------------------------------------------
 * Declaration order matters for fidelity: GCC emits file-scope statics in REVERSE definition order, so
 * this order (the dactyl's) reproduces the dump layout caps_active 0x200015DC < gui_active DD < shift_active DE
 * < held_osm E0/E4 < move_to_lower E8 < return_to_mouse E9 (verified with gcc 13.2.1 in-tree,
 * tools/final_compile_compare.py section 4). */
static uint8_t return_to_mouse = 0; /* 0x200015E9: set by TD(0) single tap from layer 4, cleared here when layer 1 is not active */
static uint8_t move_to_lower   = 0; /* 0x200015E8: set by TD(0) first single tap, cleared here on any key that is not TD(0) */
#define OSM_HOLD_COUNT 2
static uint16_t *held_osm[OSM_HOLD_COUNT] = {0}; /* 0x200015E0, 0x200015E4: never written non-NULL anywhere in the image */
static uint8_t shift_active    = 0; /* 0x200015DE: "a Shift one-shot is showing" (mods & MOD_MASK_SHIFT) */
static uint8_t gui_active      = 0; /* 0x200015DD: "a GUI one-shot is showing"   (mods & MOD_MASK_GUI)   */
static uint8_t caps_active     = 0; /* 0x200015DC: set/cleared on KC_CAPS press (see below);   read by the indicator hook */

/* ---- one-shot modifier indicator hooks ---------------------------------------------------- */
/*
 * 0x0800D010. Both *_changed_user hooks are one-line wrappers that call this static helper; GCC's
 * sibling-call optimisation turns each wrapper into a 4-byte "b.w" thunk (0x0800D088 =
 * oneshot_mods_changed_user, 0x0800D08C = oneshot_locked_mods_changed_user). No linker ICF is involved.
 *
 * `mods` is the hook ARGUMENT, not the accumulated one-shot state: QMK's add_oneshot_mods() passes only
 * the newly added mods (action_util.c:501), del/clear pass the remaining state. So stacking
 * OSM(Shift) then OSM(GUI) calls this with 0x02 then 0x08 and the second call clears shift_active
 * (black, then yellow) although the Shift one-shot is still pending -- stock core feeding user code.
 *
 * The exact source text is not recoverable; the statement form below reproduces the compiled
 * decision table for all 16 (shift-bits, gui-bits, shift_active, gui_active) combinations
 * (tools/sim_handle_oneshots.py). Note the asymmetry that IS in the binary: when the Shift bits
 * drop and shift_active was set, gui_active is NOT cleared in the same call, even if the GUI bits
 * are also gone (0x0800D02E "cbz r4" returns). This is NOT the dactyl-keymap if/else-if chain
 * (that one differs from the binary in 5 of 16 cases).
 */
static void handle_oneshots(uint8_t mods) {
    if (!(mods & MOD_MASK_SHIFT) && shift_active) {      /* 0x0800D012 ands r5,r0,#0x22 ; 0x0800D01E..0x0800D02C */
        rgb_matrix_set_color_all(0, 0, 0);
        shift_active = 0;
    } else if (!(mods & MOD_MASK_GUI) && gui_active) {   /* 0x0800D016 bic r4,r0,#0x77 ; 0x0800D04A..0x0800D05A */
        rgb_matrix_set_color_all(0, 0, 0);
        gui_active = 0;
    }
    if ((mods & MOD_MASK_SHIFT) && !shift_active) {      /* 0x0800D060..0x0800D074: white */
        rgb_matrix_set_color_all(255, 255, 255);
        shift_active = 1;
    }
    if ((mods & MOD_MASK_GUI) && !gui_active) {          /* 0x0800D030..0x0800D040: yellow */
        rgb_matrix_set_color_all(255, 255, 0);
        gui_active = 1;
    }
}

void oneshot_mods_changed_user(uint8_t mods) {           /* 0x0800D088, called from oneshot_mods_changed_kb 0x0800E3E4 */
    handle_oneshots(mods);
}

void oneshot_locked_mods_changed_user(uint8_t mods) {    /* 0x0800D08C, called from oneshot_locked_mods_changed_kb 0x0800E38C */
    handle_oneshots(mods);
}

/* ---- OSM "unlock" helpers ---------------------------------------------------------------- */
/*
 * 0x0800D090. Verbatim port of the dactyl keymap's find_osm_slot() (there it is dead code; here it
 * is live). The compiled code is a faithful translation of this source INCLUDING its bugs:
 *   - `blank = index` only ever stores NULL;
 *   - `index += sizeof(uint16_t)` advances by 2 elements (4 bytes), so the second probe is
 *     held_osm[0] + 4 bytes, never held_osm[1];
 *   - when held_osm[0] is NULL the second iteration dereferences (uint16_t *)4
 *     (0x0800D0AC "movs r2,#4" -> 0x0800D0A0 "ldrh r1,[r0,#4]" with r0 == 0).
 * On this STM32F401 address 0x00000004 aliases flash 0x08000004 (bootloader reset vector,
 * value 0x0800811D -> halfword 0x811D), which never equals an OSM keycode, so the function
 * returns NULL for every keycode. See the .md for why held_osm[] is always NULL.
 */
uint16_t *find_osm_slot(uint16_t keycode) {
    uint16_t *index = held_osm[0];
    uint16_t *blank = NULL;
    for (int i = 0; i < OSM_HOLD_COUNT; i++) {
        if (index == NULL) {
            blank = index;
        } else if (*(index) == keycode) {
            return index;
        }
        index += sizeof(uint16_t);
    }
    return blank;
}

/*
 * 0x0800D0B4. Port of the dactyl keymap's check_unlock_osm() with the rgblight calls removed.
 * Return value is what process_record_user returns for the four OSM keys (tail call at 0x0800D15A).
 *
 *   slot == NULL          -> true  (0x0800D0F2)  : let QMK process the OSM key normally
 *   get_mods() == 0       -> false (0x0800D0C4)
 *   *slot == keycode      -> false (0x0800D0CE)  : (always the case when slot != NULL, see find_osm_slot)
 *   otherwise             -> clear_oneshot_mods(); clear_oneshot_locked_mods();
 *                            unregister_mods(get_oneshot_mods()); held_osm[] = {0};
 *                            shift_active = gui_active = 0; return false   (0x0800D0D0..0x0800D0F0)
 *
 * Because find_osm_slot() always returns NULL in this image, the effective behaviour is
 * "return true": the OSM keys are handled by stock QMK (with ONESHOT_TAP_TOGGLE 2, verified in
 * process_action at 0x0800D832). The unlock branch is unreachable in practice.
 */
bool check_unlock_osm(uint16_t keycode) {
    uint16_t *slot = find_osm_slot(keycode);
    if (slot == NULL) {
        slot = &keycode; /* dead store, as in the dactyl source */
        return true;
    }

    /* Turn off the mod-lock if another OSM key is pressed while a mod is already held/locked */
    if (get_mods() && (keycode != *(slot))) {
        clear_oneshot_mods();                 /* 0x0800D0D0 -> 0x0800E424 */
        clear_oneshot_locked_mods();          /* 0x0800D0D4 -> 0x0800E3B0 */
        unregister_mods(get_oneshot_mods());  /* 0x0800D0D8 -> 0x0800E380, 0x0800D0DC -> 0x0800D684 */

        for (int i = 0; i < OSM_HOLD_COUNT; i++) {  /* 0x0800D0E4/0x0800D0E6: str 0,[0x200015E0]; str 0,[0x200015E4] */
            held_osm[i] = NULL;
        }
        shift_active = 0;                     /* 0x0800D0EA strb 0,[0x200015DE] */
        gui_active   = 0;                     /* 0x0800D0EE strb 0,[0x200015DD] */
        return false;
    }
    return false;
}

/* ---- process_record_user ------------------------------------------------------------------- */
/*
 * 0x0800D104. Called first from process_record_kb (0x0800C6E8, keychron_task.c:87-88); if it returns
 * false the Keychron wireless/factory-test handlers are skipped too.
 */
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    /* Keychron common keycodes first (stock template). 0x0800D10A bl 0x0800C720 ; 0x0800D112 beq -> return false */
    if (!process_record_keychron_common(keycode, record)) {
        return false;
    }

    /* clear the 'layer movement flags' unless we are pressing down (TD(0) again) */
    if (move_to_lower && (keycode != TD(LAYR_DOWN))) {      /* 0x0800D114..0x0800D122 (cmp.w r4,#0x5700) */
        move_to_lower = 0;
    }
    /* if we are not on 'lower' don't ever 'return to mouse' */
    if (return_to_mouse && (!layer_state_is(_LOWER))) {     /* 0x0800D124..0x0800D132 (layer_state_is(1)) */
        return_to_mouse = 0;
    }

    /* Only run the following logic on downstrokes */
    if (record->event.pressed) {                             /* 0x0800D134 ldrb r3,[r6,#5] */
        bool is_osm = ((keycode == OSM(MOD_LSFT)) || (keycode == OSM(MOD_RSFT)) ||
                       (keycode == OSM(MOD_LGUI)) || (keycode == OSM(MOD_RGUI)));
        if (is_osm) {                                        /* 0x0800D13C..0x0800D152: (kc-0x52A2)<0x17 && 0x410041>>n & 1 */
            return check_unlock_osm(keycode);                /* 0x0800D15A tail call */
        }

        /* KC_CAPS: remember the state the host LED is ABOUT to take (LED not yet toggled at this point) */
        if (keycode == KC_CAPS && !(host_keyboard_led_state().caps_lock)) {     /* 0x0800D15E..0x0800D16A */
            caps_active = 1;
            return true;
        } else if (keycode == KC_CAPS && (host_keyboard_led_state().caps_lock)) { /* 0x0800D170..0x0800D17C (second call kept) */
            caps_active = 0;
            return true;
        }

        if (keycode == DOT_SLS) {                            /* 0x0800D17E..0x0800D19E */
            register_code(KC_DOT);
            unregister_code(KC_DOT);
            register_code(KC_SLSH);
            unregister_code(KC_SLSH);
            return false;
        }

        if (keycode == DIR_UP) {                             /* 0x0800D1A2..0x0800D1B6 (extra DOT tap, then falls into the DOT_SLS body) */
            register_code(KC_DOT);
            unregister_code(KC_DOT);
            register_code(KC_DOT);
            unregister_code(KC_DOT);
            register_code(KC_SLSH);
            unregister_code(KC_SLSH);
            return false;
        }
    }

    return true;                                             /* 0x0800D16C mov r0,r5 (r5 == true here) */
}

/* No post_process_record_user / pre_process_record_user in this image:
 * 0x0800D2DC is the empty weak post_process_record_user (wrapper post_process_record_kb @0x0800D2DE),
 * 0x0800D2CC is the weak pre_process_record_user returning true (wrapper @0x0800D2D0). */
