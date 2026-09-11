/*
 * Reconstructed TD(0) tap dance for the Keychron V10 Max custom firmware
 * (dump_a.bin, built 2024-07-09, Keychron wireless_playground fork, QMK 0.23.2 era).
 *
 * Verification: compiled in-tree with the dump's compiler (arm-none-eabi-gcc 13.2.1, QMK flags incl.
 * -fdata-sections) as part of the final keymap (reconstructed_keymap/keymap.c) every function below is
 * masked-identical to the dump (tools/final_compile_compare.py: only BL/B.W displacements and literal-pool
 * addresses differ, register allocation and branch offsets are equal):
 *   cur_dance                  == 0x0800D1C4..0x0800D1E9
 *   layr_dn_finished           == 0x0800D1EC..0x0800D253
 *   layr_dn_reset              == 0x0800CDD8  (bx lr)
 *   layer_oneshot_Lower        == 0x0800CDDA..0x0800CDF3
 *   oneshot_layer_changed_user == 0x0800D25C..0x0800D275
 * (The earlier standalone gcc 15.2 -Os check, tools/tapdance_recompile_check.c, gives the same control
 * flow, calls and stores with r4/r5 swapped and a merged literal pool -- a gcc 15 vs 13 / section-anchor
 * difference, not a reconstruction difference.)
 *
 * Names (TD_SINGLE_TAP, move_to_lower, ...) are taken from the user's dactyl keymap;
 * only the numeric values / addresses / behaviour are provable from the binary.
 *
 * ---- config.h ----------------------------------------------------------
 *   #define TAPPING_TERM 175          // get_tapping_term @0x0800DEFC: movs r0,#175 ; bx lr
 *   #define TAPPING_TERM_PER_KEY      // tap_dance_task @0x080120EC CALLS get_tapping_term
 *                                     // instead of comparing an immediate (cf. ref_feat elf: cmp r0,#140)
 *   // ONESHOT_TIMEOUT is NOT defined (set_oneshot_layer @0x0800E504 never calls timer_read)
 * ---- rules.mk ----------------------------------------------------------
 *   TAP_DANCE_ENABLE = yes
 * ------------------------------------------------------------------------
 */
#include QMK_KEYBOARD_H

/* Layers used by the dance (from keymap_recovered.md): 1 = LCTL/arrows "lower" layer,
 * 4 = mouse-keys layer. TD(0) itself sits at row 5 col 7 (Fn key) of layers 0, 1 and 4. */
enum layers { _QWERTY = 0, _LOWER = 1, _RAISE = 2, _RAISE2 = 3, _MOUSE = 4, _LEADR = 5 };

enum tap_dance_keys { LAYR_DOWN = 0 };          /* TD(0) = 0x5700 is the only tap dance */

/* Values as compiled in cur_dance @0x0800D1C4 (movs r0,#2 / #3 / #4 / #1). */
typedef enum {
    TD_NONE        = 0,   /* never produced by cur_dance */
    TD_UNKNOWN     = 1,   /* count==1 && pressed && interrupted, or count>=3 */
    TD_SINGLE_TAP  = 2,   /* count==1 && !pressed (interrupted or not)        */
    TD_SINGLE_HOLD = 3,   /* count==1 && pressed && !interrupted               */
    TD_DOUBLE_TAP  = 4,   /* count==2 (regardless of pressed/interrupted)      */
} td_state_t;

typedef struct {
    bool       is_press_action;
    td_state_t state;
} td_tap_t;

/* Write-only in this firmware: GCC removes the stores, which is why on_reset
 * compiles to a bare `bx lr` and layr_dn_finished never stores cur_dance()'s result. */
static td_tap_t layr_dn_tap_state = {.is_press_action = true, .state = TD_NONE};

/* .bss byte flags.  RAM 0x200015E8 = move_to_lower, 0x200015E9 = return_to_mouse.
 * GCC emits file-scope statics in reverse definition order, so declaring return_to_mouse first puts
 * move_to_lower at the lower address, exactly as in the dump. */
static uint8_t return_to_mouse = 0;
static uint8_t move_to_lower   = 0;

td_state_t cur_dance(tap_dance_state_t *state) {          /* 0x0800D1C4 */
    if (state->count == 1) {                               /* ldrb r3,[r0,#2]; cmp r3,#1 */
        if (!state->pressed) return TD_SINGLE_TAP;         /* ldrb r3,[r0,#5]; lsls r2,r3,#31; bpl -> movs r0,#2 */
        else if (!state->interrupted) return TD_SINGLE_HOLD; /* tst.w r3,#4; moveq r0,#3 */
        else return TD_UNKNOWN;                            /* movne r0,#1 */
    } else if (state->count == 2) return TD_DOUBLE_TAP;    /* cmp r3,#2; moveq r0,#4 */
    else return TD_UNKNOWN;                                /* movne r0,#1  (NO triple-tap state) */
}

static void layer_move_toLower(void) {                     /* inlined at 0x0800D220-D226 and 0x0800D24C-D252 */
    layer_clear();                                         /* bl 0x0800DC34 = layer_state_set(0) */
    layer_move(_LOWER);                                    /* movs r0,#1; bl 0x0800DC58 = layer_state_set(1<<1) */
}

static void layer_oneshot_Lower(void) {                    /* 0x0800CDDA */
    layer_on(_LOWER);                                      /* movs r0,#1; bl 0x0800DC64 */
    set_oneshot_layer(_LOWER, ONESHOT_START);              /* movs r0,#1; movs r1,#3; bl 0x0800E504 */
    clear_oneshot_layer_state(ONESHOT_PRESSED);            /* movs r0,#1; b.w 0x0800E548 */
}

void layr_dn_finished(tap_dance_state_t *state, void *user_data) {   /* 0x0800D1ED (user_data never read) */
    layr_dn_tap_state.state = cur_dance(state);                        /* bl 0x0800D1C4 */
    switch (layr_dn_tap_state.state) {
        case TD_SINGLE_TAP:                                            /* cmp r0,#2 (0x0800D1FA) */
            if (layer_state_is(_MOUSE)) {                              /* movs r0,#4; bl 0x0800DC3C */
                return_to_mouse = 1;                                   /* strb #1 -> 0x200015E9 (0x0800D20C) */
                layer_clear();                                         /* 0x0800D20E */
                layer_oneshot_Lower();                                 /* b.w 0x0800CDDA (0x0800D216) */
            } else {
                if (move_to_lower) {                                   /* ldrb 0x200015E8 (0x0800D21C) */
                    layer_move_toLower();                              /* 0x0800D220-D226 */
                    move_to_lower = 0;                                 /* strb r4(=0) (0x0800D22A) */
                } else if (layer_state_is(_LOWER)) {                   /* movs r0,#1; bl 0x0800DC3C (0x0800D230) */
                    layer_clear();                                     /* bne 0x0800D20E */
                    layer_oneshot_Lower();
                } else {
                    move_to_lower = 1;                                 /* strb #1 -> 0x200015E8 (0x0800D23A) */
                    layer_oneshot_Lower();                             /* b 0x0800D212 */
                }
            }
            break;
        case TD_SINGLE_HOLD:                                           /* cmp r0,#3 -> 0x0800D23E */
            layer_clear();                                             /* bl 0x0800DC34 */
            layer_move(_MOUSE);                                        /* movs r0,#4; b.w 0x0800DC58 */
            break;
        case TD_DOUBLE_TAP:                                            /* cmp r0,#4 -> 0x0800D24C */
            layer_move_toLower();                                      /* bl 0x0800DC34; movs r0,#1; b 0x0800D244 -> layer_move */
            break;
        default:                                                       /* TD_UNKNOWN: bne 0x0800D22C -> pop */
            break;
    }
}

void layr_dn_reset(tap_dance_state_t *state, void *user_data) {       /* 0x0800CDD9: bx lr */
    layr_dn_tap_state.state = TD_NONE;                                 /* store eliminated by GCC (write-only static) */
}

/* .data init image @0x080179C8 -> RAM 0x20000E7C, exactly one 28-byte entry:
 * state={0}, fn={NULL, 0x0800D1ED, 0x0800CDD9, NULL}, user_data=NULL (never written at runtime). */
tap_dance_action_t tap_dance_actions[] = {
    [LAYR_DOWN] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, layr_dn_finished, layr_dn_reset),
};

void oneshot_layer_changed_user(uint8_t layer) {                      /* 0x0800D25C */
    if (!layer) {                                                      /* cbnz r0 -> return */
        if (return_to_mouse) {                                         /* ldrb 0x200015E9 */
            layer_clear();                                             /* bl 0x0800DC34 */
            layer_move(_MOUSE);                                        /* movs r0,#4; bl 0x0800DC58 */
            return_to_mouse = 0;                                       /* strb r4(=layer=0) (0x0800D272) */
        }
    }
}

/* Only the tap-dance-related part of process_record_user @0x0800D104 is shown here;
 * the KC_CAPS / OSM / QK_USER_0-1 branches belong to the other custom_code targets. */
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (!process_record_keychron_common(keycode, record)) {           /* bl 0x0800C720; cbz -> return false */
        return false;                                                  /* Keychron keycodes (BT_HST*, P2P4G, BAT_LVL, KC_TASK, ...) never reach the flag clears */
    }
    /* clear the 'layer movement flags' unless we are pressing down (runs for press AND release events).
     * Note: the TD(0) press itself ends a pending one-shot layer (action.c: clear_oneshot_layer_state(ONESHOT_OTHER_KEY_PRESSED)
     * runs for every key that process_record_quantum does not consume), so the "tap again" case below always sees the
     * one-shot already gone and locks layer 1 via move_to_lower; the layer_state_is(_LOWER) branch is reached only when
     * layer 1 is on for a non-one-shot reason (locked). */
    if (move_to_lower && (keycode != TD(LAYR_DOWN))) {                 /* 0x0800D114-D122: cmp.w r4,#0x5700; itt ne; strb #0 */
        move_to_lower = 0;
    }
    /* if we are not on 'lower' don't ever 'return to mouse' */
    if (return_to_mouse && (!layer_state_is(_LOWER))) {                /* 0x0800D124-D132: movs r0,#1; bl 0x0800DC3C; cbnz; strb r0(=0) */
        return_to_mouse = 0;
    }
    if (record->event.pressed) {                                       /* ldrb r3,[r6,#5]; cbz */
        /* ... KC_CAPS indicator flag, OSM(MOD_LSFT/LGUI/RSFT/RGUI) handling, QK_USER_0 './', QK_USER_1 '../'
         *     (see custom_code/oneshot*.md, custom_code/process_record_user*.md) ... */
    }
    return true;
}
