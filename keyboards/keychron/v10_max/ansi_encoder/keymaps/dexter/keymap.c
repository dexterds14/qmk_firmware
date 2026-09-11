/* Keychron V10 Max ANSI knob (keychron/v10_max/ansi_encoder) -- "dexter" keymap
 *
 * Reconstructed from a flash dump of the lost custom firmware (built 2024-07-09-13:57:36 from
 * Keychron's wireless_playground fork at commit 8e390f92a2, QMK 0.23.2 era, arm-none-eabi-gcc 13.2.1).
 * Every table entry and every behaviour below was recovered from the binary; the evidence trail is in
 * keychron_v10max_backup/RECONSTRUCTION_SPEC.md (per-line confidence) and ANALYSIS.md (addresses).
 * Identifier names follow the author's sibling dactyl_manuform keymap; only values and behaviour are
 * provable from the dump.
 *
 * SPDX-License-Identifier: GPL-2.0-or-later
 */
#include QMK_KEYBOARD_H
#include "keychron_common.h"

enum layers {
    _QWERTY = 0, // base                                    (no indicator colour)
    _LOWER,      // Ctrl-chords / arrows; TD(0) one-shot or lock  (green)
    _RAISE,      // symbols / F-keys, OSL(_RAISE) on right Cmd     (blue)
    _RAISE2,     // Keychron Fn content: RGB, BT hosts, QK_BOOT   (orange)
    _MOUSE,      // mouse keys; TD(0) hold                        (teal)
    _LEADR,      // leader key + Ctrl/Shift chords; OSL(_LEADR)   (red)
};

/* SAFE_RANGE == QK_USER_0 == 0x7E40 in this fork. Only these two custom keycodes exist in the image. */
enum custom_keycodes {
    DOT_SLS = SAFE_RANGE, // 0x7E40: types "./"
    DIR_UP,               // 0x7E41: types "../"
};

enum tap_dance_keys {
    LAYR_DOWN, // TD(0) = 0x5700, the Fn key; the only tap dance in the image
};

/* Values as compiled in cur_dance (dump 0x0800D1C4): 2 / 3 / 4 / 1. There is no TD_TRIPLE_TAP. */
typedef enum {
    TD_NONE,        // 0
    TD_UNKNOWN,     // 1
    TD_SINGLE_TAP,  // 2
    TD_SINGLE_HOLD, // 3
    TD_DOUBLE_TAP,  // 4
} td_state_t;

typedef struct {
    bool       is_press_action;
    td_state_t state;
} td_tap_t;

/* ---- static state --------------------------------------------------------------------------
 * Declared in this order on purpose: GCC emits file-scope statics in reverse definition order, which
 * reproduces the dump's .bss layout 0x200015DC caps_active, DD gui_active, DE shift_active,
 * E0/E4 held_osm[2], E8 move_to_lower, E9 return_to_mouse.
 */
static uint8_t return_to_mouse = 0; // TD(0) tapped on _MOUSE: go back to _MOUSE when the one-shot _LOWER ends
static uint8_t move_to_lower   = 0; // TD(0) tapped once: a second tap with no other key in between locks _LOWER
#define OSM_HOLD_COUNT 2
static uint16_t *held_osm[OSM_HOLD_COUNT] = {0}; // never written non-NULL anywhere in the image (see check_unlock_osm)
static uint8_t shift_active = 0; // a one-shot Shift is showing -> board white
static uint8_t gui_active   = 0; // a one-shot GUI is showing   -> board yellow
static uint8_t caps_active  = 0; // this keyboard toggled caps lock on -> board white

/* Write-only in this firmware: GCC removes every store to it, which is why layr_dn_reset compiles to a
 * bare `bx lr` and layr_dn_finished never stores cur_dance()'s result. Kept for fidelity with the source. */
static td_tap_t layr_dn_tap_state = {.is_press_action = true, .state = TD_NONE};

/* ---- keymap ---------------------------------------------------------------------------------
 * Byte-identical to the dump's keymaps[] at flash 0x080169B8 (6 x 6 x 18 u16, verified by round-trip).
 */
// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_QWERTY] = LAYOUT_ansi_89(
        KC_AUDIO_MUTE,          KC_ESCAPE,       KC_BRIGHTNESS_DOWN, KC_BRIGHTNESS_UP, KC_MCTRL,         KC_LNPAD,              RGB_VAD,                RGB_VAI,           KC_MEDIA_PREV_TRACK, KC_MEDIA_PLAY_PAUSE,   KC_MEDIA_NEXT_TRACK, KC_AUDIO_MUTE,    KC_AUDIO_VOL_DOWN, KC_AUDIO_VOL_UP, KC_INSERT,                                   KC_DELETE,
        KC_BACKSPACE,           OSL(_LEADR),     KC_1,               KC_2,             KC_3,             KC_4,                  KC_5,                   KC_6,              KC_7,                KC_8,                  KC_9,                KC_0,             LSFT(KC_EQUAL),    KC_EQUAL,        KC_BACKSPACE,                                KC_PAGE_UP,
        MC_2,                   KC_GRAVE,        KC_Q,               KC_W,             KC_E,             KC_R,                  KC_T,                                      KC_Y,                KC_U,                  KC_I,                KC_O,             KC_P,              KC_MINUS,        KC_RIGHT_BRACKET,     KC_BACKSLASH,          KC_PAGE_DOWN,
        MC_3,                   OSM(MOD_LSFT),   KC_A,               KC_S,             KC_D,             KC_F,                  KC_G,                                      KC_H,                KC_J,                  KC_K,                KC_L,             KC_QUOTE,          OSM(MOD_RSFT),   KC_SEMICOLON,                                KC_HOME,
        MC_4,                   KC_TAB,                              KC_Z,             KC_X,             KC_C,                  KC_V,                   KC_B,              KC_BACKSPACE,        KC_N,                  KC_M,                KC_COMMA,         KC_DOT,            KC_SLASH,        KC_RIGHT_SHIFT,                     KC_UP,
        MC_5,                   KC_LEFT_CTRL,    KC_CAPS_LOCK,                         OSM(MOD_LGUI),                           KC_SPACE,               TD(LAYR_DOWN),                          KC_ENTER,                                   OSL(_RAISE),                                                                KC_LEFT,      KC_DOWN, KC_RIGHT
    ),
    [_LOWER] = LAYOUT_ansi_89(
        RGB_TOG,                KC_BACKSPACE,    KC_F1,              KC_F2,            KC_F3,            KC_F4,                 KC_F5,                  KC_F6,             KC_F7,               KC_F8,                 KC_F9,               KC_F10,           KC_F11,            KC_F12,          _______,                                     _______,
        QK_MAGIC_TOGGLE_NKRO,   OSL(_LEADR),     LCTL(KC_1),         LCTL(KC_2),       XXXXXXX,          LCTL(KC_TAB),          _______,                _______,           XXXXXXX,             LALT(KC_LEFT),         LALT(KC_RIGHT),      LCTL(KC_TAB),     KC_DELETE,         KC_PAGE_UP,      _______,                                     _______,
        _______,                LALT(KC_GRAVE),  LCTL(KC_Q),         LCTL(KC_W),       KC_LEFT_ALT,      LCTL(KC_R),            LCTL(KC_T),                                LCTL(KC_Y),          LCTL(KC_U),            LCTL(KC_I),          LCTL(KC_O),       LCTL(KC_P),        KC_HOME,         _______,              _______,               _______,
        _______,                LALT(KC_TAB),    LCTL(KC_A),         LCTL(KC_S),       LCTL(KC_D),       LCTL(KC_F),            KC_F4,                                     LCTL(KC_H),          KC_UP,                 KC_LEFT,             KC_DOWN,          KC_RIGHT,          KC_END,          _______,                                     KC_END,
        _______,                LSFT(KC_TAB),                        LCTL(KC_Z),       LCTL(KC_X),       LCTL(KC_C),            LCTL(KC_V),             LCTL(KC_B),        BAT_LVL,             LCTL(KC_N),            LALT(KC_ENTER),      DOT_SLS,          DIR_UP,            LCTL(KC_SLASH),  KC_PAGE_DOWN,                       _______,
        _______,                _______,         KC_SPACE,                             KC_LEFT_CTRL,                            KC_LEFT_SHIFT,          TD(LAYR_DOWN),                          KC_ENTER,                                   TO(_QWERTY),                                                                _______,      _______, _______
    ),
    [_RAISE] = LAYOUT_ansi_89(
        KC_AUDIO_MUTE,          KC_ESCAPE,       KC_F1,              KC_F2,            KC_F3,            KC_F4,                 KC_F5,                  KC_F6,             KC_F7,               KC_F8,                 KC_F9,               KC_F10,           KC_F11,            KC_F12,          KC_INSERT,                                   KC_DELETE,
        MC_1,                   KC_F12,          KC_F1,              KC_F2,            KC_F3,            KC_F4,                 KC_F5,                  KC_F6,             KC_F7,               KC_F8,                 KC_F9,               KC_F10,           KC_F11,            KC_EQUAL,        KC_BACKSPACE,                                KC_PAGE_UP,
        MC_2,                   LSFT(KC_GRAVE),  LSFT(KC_1),         LSFT(KC_2),       LSFT(KC_3),       LSFT(KC_4),            LSFT(KC_5),                                LSFT(KC_6),          LSFT(KC_7),            LSFT(KC_8),          KC_LEFT_BRACKET,  KC_RIGHT_BRACKET,  LSFT(KC_EQUAL),  KC_RIGHT_BRACKET,     KC_BACKSLASH,          KC_PAGE_DOWN,
        MC_3,                   KC_ESCAPE,       LSFT(KC_SEMICOLON), KC_EQUAL,         LSFT(KC_MINUS),   LSFT(KC_BACKSLASH),    KC_BACKSLASH,                              XXXXXXX,             LSFT(KC_9),            LSFT(KC_0),          KC_MINUS,         LSFT(KC_QUOTE),    KC_AUDIO_VOL_UP, KC_ENTER,                                    KC_HOME,
        MC_4,                   KC_PRINT_SCREEN,                     XXXXXXX,          XXXXXXX,          LSFT(KC_LEFT_BRACKET), LSFT(KC_RIGHT_BRACKET), XXXXXXX,           KC_B,                KC_AUDIO_MUTE,         XXXXXXX,             LSFT(KC_COMMA),   LSFT(KC_DOT),      LSFT(KC_SLASH),  KC_AUDIO_VOL_DOWN,                  KC_UP,
        MC_5,                   KC_LEFT_CTRL,    KC_LEFT_GUI,                          KC_LEFT_ALT,                             KC_MEDIA_REWIND,        TO(_QWERTY),                            KC_MEDIA_FAST_FORWARD,                      TO(_RAISE2),                                                                KC_LEFT,      KC_DOWN, KC_RIGHT
    ),
    [_RAISE2] = LAYOUT_ansi_89(
        RGB_TOG,                QK_BOOTLOADER,   KC_BRIGHTNESS_DOWN, KC_BRIGHTNESS_UP, KC_TASK,          KC_FILE,               RGB_VAD,                RGB_VAI,           KC_MEDIA_PREV_TRACK, KC_MEDIA_PLAY_PAUSE,   KC_MEDIA_NEXT_TRACK, KC_AUDIO_MUTE,    KC_AUDIO_VOL_DOWN, KC_AUDIO_VOL_UP, _______,                                     _______,
        _______,                _______,         BT_HST1,            BT_HST2,          BT_HST3,          P2P4G,                 _______,                _______,           _______,             _______,               _______,             _______,          _______,           _______,         _______,                                     _______,
        _______,                RGB_TOG,         RGB_MODE_FORWARD,   RGB_VAI,          RGB_HUI,          RGB_SAI,               RGB_SPI,                                   _______,             _______,               _______,             _______,          _______,           _______,         _______,              _______,               _______,
        _______,                _______,         RGB_MODE_REVERSE,   RGB_VAD,          RGB_HUD,          RGB_SAD,               RGB_SPD,                                   _______,             _______,               _______,             _______,          _______,           _______,         _______,                                     KC_END,
        _______,                _______,                             _______,          _______,          _______,               _______,                BAT_LVL,           BAT_LVL,             QK_MAGIC_TOGGLE_NKRO,  _______,             _______,          _______,           _______,         _______,                            _______,
        _______,                _______,         _______,                              _______,                                 _______,                TO(_RAISE),                             _______,                                    TO(_QWERTY),                                                                _______,      _______, _______
    ),
    [_MOUSE] = LAYOUT_ansi_89(
        RGB_TOG,                _______,         KC_BRIGHTNESS_DOWN, KC_BRIGHTNESS_UP, KC_TASK,          KC_FILE,               RGB_VAD,                RGB_VAI,           KC_MEDIA_PREV_TRACK, KC_MEDIA_PLAY_PAUSE,   KC_MEDIA_NEXT_TRACK, KC_AUDIO_MUTE,    KC_AUDIO_VOL_DOWN, KC_AUDIO_VOL_UP, _______,                                     _______,
        _______,                OSL(_LEADR),     BT_HST1,            BT_HST2,          BT_HST3,          P2P4G,                 _______,                _______,           _______,             _______,               _______,             _______,          _______,           _______,         _______,                                     _______,
        _______,                RGB_TOG,         RGB_MODE_FORWARD,   RGB_VAI,          RGB_HUI,          RGB_SAI,               RGB_SPI,                                   _______,             _______,               _______,             _______,          _______,           _______,         _______,              _______,               _______,
        _______,                KC_MS_BTN3,      KC_MS_WH_LEFT,      KC_MS_WH_RIGHT,   KC_MS_BTN2,       KC_MS_BTN1,            XXXXXXX,                                   XXXXXXX,             KC_MS_UP,              KC_MS_LEFT,          KC_MS_DOWN,       KC_MS_RIGHT,       XXXXXXX,         _______,                                     KC_END,
        _______,                XXXXXXX,                             XXXXXXX,          XXXXXXX,          KC_MS_WH_UP,           KC_MS_WH_DOWN,          XXXXXXX,           BAT_LVL,             QK_MAGIC_TOGGLE_NKRO,  _______,             _______,          _______,           _______,         _______,                            _______,
        _______,                _______,         _______,                              KC_LEFT_CTRL,                            KC_SPACE,               TD(LAYR_DOWN),                          KC_ENTER,                                   TO(_QWERTY),                                                                _______,      _______, _______
    ),
    [_LEADR] = LAYOUT_ansi_89(
        RGB_TOG,                _______,         KC_BRIGHTNESS_DOWN, KC_BRIGHTNESS_UP, KC_TASK,          KC_FILE,               RGB_VAD,                RGB_VAI,           KC_MEDIA_PREV_TRACK, KC_MEDIA_PLAY_PAUSE,   KC_MEDIA_NEXT_TRACK, KC_AUDIO_MUTE,    KC_AUDIO_VOL_DOWN, KC_AUDIO_VOL_UP, _______,                                     _______,
        _______,                QK_LEADER,       XXXXXXX,            XXXXXXX,          XXXXXXX,          LALT(KC_F4),           XXXXXXX,                _______,           _______,             _______,               _______,             _______,          _______,           _______,         _______,                                     _______,
        _______,                LCTL(KC_GRAVE),  XXXXXXX,            XXXXXXX,          LSFT(LCTL(KC_E)), LSFT(LCTL(KC_R)),      LSFT(LCTL(KC_T)),                          XXXXXXX,             XXXXXXX,               XXXXXXX,             LSFT(LCTL(KC_O)), LSFT(LCTL(KC_P)),  XXXXXXX,         _______,              _______,               _______,
        _______,                XXXXXXX,         XXXXXXX,            LSFT(LCTL(KC_S)), LALT(LSFT(KC_D)), LSFT(LCTL(KC_F)),      XXXXXXX,                                   XXXXXXX,             LALT(KC_UP),           LALT(KC_LEFT),       LALT(KC_DOWN),    LALT(KC_RIGHT),    XXXXXXX,         _______,                                     KC_END,
        _______,                XXXXXXX,                             LSFT(LCTL(KC_Z)), XXXXXXX,          LSFT(LCTL(KC_C)),      LSFT(LCTL(KC_V)),       XXXXXXX,           BAT_LVL,             LSFT(LCTL(KC_N)),      XXXXXXX,             XXXXXXX,          DOT_SLS,           XXXXXXX,         XXXXXXX,                            _______,
        _______,                _______,         _______,                              _______,                                 _______,                TO(_QWERTY),                            _______,                                    TO(_LEADR),                                                                 _______,      _______, _______
    )
};

/* Byte-identical to the dump's encoder_map[6][1][2] at flash 0x080169A0 (24 bytes, immediately before keymaps[]). */
#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][2] = {
    [_QWERTY] = {ENCODER_CCW_CW(KC_VOLD, KC_VOLU)},
    [_LOWER]  = {ENCODER_CCW_CW(RGB_VAD, RGB_VAI)},
    [_RAISE]  = {ENCODER_CCW_CW(KC_VOLD, KC_VOLU)},
    [_RAISE2] = {ENCODER_CCW_CW(KC_NO,   KC_NO)},
    [_MOUSE]  = {ENCODER_CCW_CW(KC_NO,   KC_NO)},
    [_LEADR]  = {ENCODER_CCW_CW(RGB_VAD, RGB_VAI)},
};
#endif
// clang-format on

/* ---- TD(LAYR_DOWN): the Fn key --------------------------------------------------------------
 *   single tap            -> one-shot _LOWER (tap again with no key in between -> lock _LOWER;
 *                            tap while _LOWER is locked -> unlock into a one-shot;
 *                            tap while on _MOUSE -> one-shot _LOWER, then return to _MOUSE)
 *   hold (>= 175 ms)      -> lock _MOUSE (sticky; leave with TO(_QWERTY) or another dance)
 *   double tap            -> lock _LOWER
 *   interrupted hold, 3+  -> nothing
 * dump: cur_dance 0x0800D1C4, layr_dn_finished 0x0800D1EC, layr_dn_reset 0x0800CDD8,
 *       layer_oneshot_Lower 0x0800CDDA, oneshot_layer_changed_user 0x0800D25C
 */
td_state_t cur_dance(tap_dance_state_t *state) {
    if (state->count == 1) {
        if (!state->pressed) return TD_SINGLE_TAP;
        else if (!state->interrupted) return TD_SINGLE_HOLD;
        else return TD_UNKNOWN;
    } else if (state->count == 2) {
        return TD_DOUBLE_TAP;
    } else {
        return TD_UNKNOWN;
    }
}

static void layer_move_toLower(void) {
    layer_clear();
    layer_move(_LOWER);
}

static void layer_oneshot_Lower(void) {
    layer_on(_LOWER);
    set_oneshot_layer(_LOWER, ONESHOT_START);
    clear_oneshot_layer_state(ONESHOT_PRESSED);
}

void layr_dn_finished(tap_dance_state_t *state, void *user_data) {
    layr_dn_tap_state.state = cur_dance(state);
    switch (layr_dn_tap_state.state) {
        case TD_SINGLE_TAP:
            if (layer_state_is(_MOUSE)) {
                return_to_mouse = 1;
                layer_clear();
                layer_oneshot_Lower();
            } else {
                if (move_to_lower) {
                    layer_move_toLower();
                    move_to_lower = 0;
                } else if (layer_state_is(_LOWER)) {
                    layer_clear();
                    layer_oneshot_Lower();
                } else {
                    move_to_lower = 1;
                    layer_oneshot_Lower();
                }
            }
            break;
        case TD_SINGLE_HOLD:
            layer_clear();
            layer_move(_MOUSE);
            break;
        case TD_DOUBLE_TAP:
            layer_move_toLower();
            break;
        default:
            break;
    }
}

void layr_dn_reset(tap_dance_state_t *state, void *user_data) {
    layr_dn_tap_state.state = TD_NONE;
}

/* .data init image at flash 0x080179C8 -> RAM 0x20000E7C: exactly one 28-byte entry,
 * {on_each_tap NULL, on_dance_finished, on_reset, on_each_release NULL, user_data NULL}. */
tap_dance_action_t tap_dance_actions[] = {
    [LAYR_DOWN] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, layr_dn_finished, layr_dn_reset),
};

void oneshot_layer_changed_user(uint8_t layer) {
    if (!layer) {
        if (return_to_mouse) {
            layer_clear();
            layer_move(_MOUSE);
            return_to_mouse = 0;
        }
    }
}

/* ---- leader key (QK_LEADER on _LEADR, grave position) --------------------------------------
 * dump: leader_start_user 0x0800CDF4, leader_end_user 0x0800CDFE (354 B).
 * The seven tests are INDEPENDENT ifs (not else-if): each failed test branches to the next test and
 * each action block falls through into the next test, so <LEAD, F> fires block 1 AND block 6
 * (GUI+P, GUI+K, then GUI+'). Chords are explicit register/unregister pairs with the modifier released
 * before the key (tap_code16 cannot produce this order). Whether the double F binding was intended
 * is unknowable from the binary; it is reproduced as found.
 */
void leader_start_user(void) {
    rgb_matrix_set_color_all(255, 0, 255);
}

void leader_end_user(void) {
    rgb_matrix_set_color_all(0, 0, 0);

    if (leader_sequence_one_key(KC_F)) {
        register_code(KC_LGUI);
        register_code(KC_P);
        unregister_code(KC_LGUI);
        unregister_code(KC_P);
        register_code(KC_LGUI);
        register_code(KC_K);
        unregister_code(KC_LGUI);
        unregister_code(KC_K);
    }
    if (leader_sequence_two_keys(KC_A, KC_Q)) {
        register_code(KC_LCTL);
        register_code(KC_A);
        unregister_code(KC_LCTL);
        unregister_code(KC_A);
        register_code(KC_Z);
        unregister_code(KC_Z);
        register_code(KC_Q);
        unregister_code(KC_Q);
        register_code(KC_ENT);
        unregister_code(KC_ENT);
    }
    if (leader_sequence_one_key(KC_Y)) {
        register_code(KC_LCTL);
        register_code(KC_X);
        unregister_code(KC_LCTL);
        unregister_code(KC_X);
        register_code(KC_Y);
        unregister_code(KC_Y);
        register_code(KC_ENT);
        unregister_code(KC_ENT);
    }
    if (leader_sequence_two_keys(KC_LCTL, KC_I)) {
        register_code(KC_LCTL);
        register_code(KC_LALT);
        register_code(KC_I);
        unregister_code(KC_LCTL);
        unregister_code(KC_LALT);
        unregister_code(KC_I);
    }
    if (leader_sequence_one_key(KC_J)) {
        register_code(KC_LGUI);
        register_code(KC_P);
        unregister_code(KC_LGUI);
        unregister_code(KC_P);
    }
    if (leader_sequence_one_key(KC_F)) {
        register_code(KC_LGUI);
        register_code(KC_QUOT);
        unregister_code(KC_LGUI);
        unregister_code(KC_QUOT);
    }
    if (leader_sequence_one_key(KC_DEL)) {
        register_code(KC_LGUI);
        register_code(KC_UP);
        register_code(KC_LEFT);
        unregister_code(KC_LGUI);
        unregister_code(KC_UP);
        unregister_code(KC_LEFT);
    }
}

/* ---- boot hook (dump 0x0800CF60) -----------------------------------------------------------
 * default_layer_set(0) undoes the Mac/Win DIP-switch default layer set by dip_switch_update_kb during
 * keyboard_init(), so the board always boots on _QWERTY. rgb_matrix_mode() is the EEPROM-writing variant.
 */
void keyboard_post_init_user(void) {
    default_layer_set(0);
    rgb_matrix_mode(RGB_MATRIX_TYPING_HEATMAP); // mode 16 in this board's effect enumeration
}

/* ---- per-frame indicator (dump 0x0800CF74, 156 B) -------------------------------------------
 * Per LED: layer colour (highest active layer incl. default layer), then yellow if a one-shot GUI is
 * showing, else white if a one-shot Shift or caps lock is showing. Layer 0 leaves the animation visible.
 * The case order 2,3,1,4,5 reproduces the dump's jump-table/block layout with gcc 13.2.1 (behaviour is
 * order-independent).
 */
bool rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {
    for (uint8_t i = led_min; i < led_max; i++) {
        switch (get_highest_layer(layer_state | default_layer_state)) {
            case _RAISE:
                rgb_matrix_set_color(i, RGB_BLUE);
                break;
            case _RAISE2:
                rgb_matrix_set_color(i, RGB_ORANGE);
                break;
            case _LOWER:
                rgb_matrix_set_color(i, RGB_GREEN);
                break;
            case _MOUSE:
                rgb_matrix_set_color(i, RGB_TEAL);
                break;
            case _LEADR:
                rgb_matrix_set_color(i, RGB_RED);
                break;
            default:
                break;
        }
        if (gui_active) {
            rgb_matrix_set_color(i, RGB_YELLOW);
        } else if (shift_active || caps_active) {
            rgb_matrix_set_color(i, RGB_WHITE);
        }
    }
    return false;
}

/* ---- one-shot modifier indicator (dump body 0x0800D010; both hooks tail-call it) -------------
 * `mods` is the hook argument: for add_oneshot_mods() QMK passes only the newly added mods, for
 * del/clear the remaining state. The whole-board set_color_all() calls last one frame; the persistent
 * colour comes from the flags read by rgb_matrix_indicators_advanced_user above.
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

/* ---- OSM "unlock" helpers (dump 0x0800D090 / 0x0800D0B4) ------------------------------------
 * Verbatim port of the author's dactyl helpers, compiled live here (dead code on the dactyl).
 * They are INERT in this firmware: held_osm[] is never written non-NULL, so find_osm_slot() always
 * returns NULL and check_unlock_osm() always returns true -> the OSM keys are handled by stock QMK
 * (ONESHOT_TAP_TOGGLE 2: double-tap locks the modifier).
 * Quirks reproduced from the binary: `index += sizeof(uint16_t)` advances 2 elements (4 bytes), so
 * the second probe reads *(uint16_t *)4 when held_osm[0] is NULL (flash alias of the reset vector,
 * value 0x811D, never an OSM keycode). Behaviour-identical alternative: delete the is_osm block in
 * process_record_user and these two functions.
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

bool check_unlock_osm(uint16_t keycode) {
    uint16_t *slot = find_osm_slot(keycode);
    if (slot == NULL) {
        slot = &keycode;
        return true;
    }

    // Turn off the mod-lock if another OSM key is pressed while a mod is already held/locked
    if (get_mods() && (keycode != *(slot))) {
        clear_oneshot_mods();
        clear_oneshot_locked_mods();
        unregister_mods(get_oneshot_mods());

        for (int i = 0; i < OSM_HOLD_COUNT; i++) {
            held_osm[i] = NULL;
        }
        shift_active = 0;
        gui_active   = 0;
        return false;
    }
    return false;
}

/* ---- process_record_user (dump 0x0800D104, 192 B) ------------------------------------------ */
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (!process_record_keychron_common(keycode, record)) {
        return false;
    }

    // clear the 'layer movement flags' unless we are pressing TD(LAYR_DOWN) again (press AND release)
    if (move_to_lower && (keycode != TD(LAYR_DOWN))) {
        move_to_lower = 0;
    }
    // if we are not on 'lower' don't ever 'return to mouse'
    if (return_to_mouse && (!layer_state_is(_LOWER))) {
        return_to_mouse = 0;
    }

    // Only run the following logic on downstrokes
    if (record->event.pressed) {
        bool is_osm = ((keycode == OSM(MOD_LSFT)) || (keycode == OSM(MOD_RSFT)) || (keycode == OSM(MOD_LGUI)) || (keycode == OSM(MOD_RGUI)));
        if (is_osm) {
            return check_unlock_osm(keycode);
        }

        // caps indicator: the host LED has not toggled yet, so !caps_lock means "about to turn on"
        if (keycode == KC_CAPS && !(host_keyboard_led_state().caps_lock)) {
            caps_active = 1;
            return true;
        } else if (keycode == KC_CAPS && (host_keyboard_led_state().caps_lock)) {
            caps_active = 0;
            return true;
        }

        if (keycode == DOT_SLS) {
            register_code(KC_DOT);
            unregister_code(KC_DOT);
            register_code(KC_SLSH);
            unregister_code(KC_SLSH);
            return false;
        }

        if (keycode == DIR_UP) {
            register_code(KC_DOT);
            unregister_code(KC_DOT);
            register_code(KC_DOT);
            unregister_code(KC_DOT);
            register_code(KC_SLSH);
            unregister_code(KC_SLSH);
            return false;
        }
    }

    return true;
}
