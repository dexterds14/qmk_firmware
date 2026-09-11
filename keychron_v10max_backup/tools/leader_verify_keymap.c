#include QMK_KEYBOARD_H
#include "keychron_common.h"

enum custom_keycodes { CK0 = SAFE_RANGE, CK1 };
enum td_ids { TD0 };
// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT_ansi_89(
        KC_AUDIO_MUTE, KC_ESCAPE, KC_BRIGHTNESS_DOWN, KC_BRIGHTNESS_UP, KC_MCTRL, KC_LNPAD, RGB_VAD, RGB_VAI, KC_MEDIA_PREV_TRACK, KC_MEDIA_PLAY_PAUSE, KC_MEDIA_NEXT_TRACK, KC_AUDIO_MUTE, KC_AUDIO_VOL_DOWN, KC_AUDIO_VOL_UP, KC_INSERT, KC_DELETE,
        KC_BACKSPACE, OSL(5), KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, LSFT(KC_EQUAL), KC_EQUAL, KC_BACKSPACE, KC_PAGE_UP,
        MC_2, KC_GRAVE, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_MINUS, KC_RIGHT_BRACKET, KC_BACKSLASH, KC_PAGE_DOWN,
        MC_3, OSM(MOD_LSFT), KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, KC_QUOTE, OSM(MOD_RSFT), KC_SEMICOLON, KC_HOME,
        MC_4, KC_TAB, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_BACKSPACE, KC_N, KC_M, KC_COMMA, KC_DOT, KC_SLASH, KC_RIGHT_SHIFT, KC_UP,
        MC_5, KC_LEFT_CTRL, KC_CAPS_LOCK, OSM(MOD_LGUI), KC_SPACE, TD(0), KC_ENTER, OSL(2), KC_LEFT, KC_DOWN, KC_RIGHT
    ),
    [1] = LAYOUT_ansi_89(
        RGB_TOG, KC_BACKSPACE, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, KC_F11, KC_F12, _______, _______,
        QK_MAGIC_TOGGLE_NKRO, OSL(5), LCTL(KC_1), LCTL(KC_2), XXXXXXX, LCTL(KC_TAB), _______, _______, XXXXXXX, LALT(KC_LEFT), LALT(KC_RIGHT), LCTL(KC_TAB), KC_DELETE, KC_PAGE_UP, _______, _______,
        _______, LALT(KC_GRAVE), LCTL(KC_Q), LCTL(KC_W), KC_LEFT_ALT, LCTL(KC_R), LCTL(KC_T), LCTL(KC_Y), LCTL(KC_U), LCTL(KC_I), LCTL(KC_O), LCTL(KC_P), KC_HOME, _______, _______, _______,
        _______, LALT(KC_TAB), LCTL(KC_A), LCTL(KC_S), LCTL(KC_D), LCTL(KC_F), KC_F4, LCTL(KC_H), KC_UP, KC_LEFT, KC_DOWN, KC_RIGHT, KC_END, _______, KC_END,
        _______, LSFT(KC_TAB), LCTL(KC_Z), LCTL(KC_X), LCTL(KC_C), LCTL(KC_V), LCTL(KC_B), BAT_LVL, LCTL(KC_N), LALT(KC_ENTER), CK0, CK1, LCTL(KC_SLASH), KC_PAGE_DOWN, _______,
        _______, _______, KC_SPACE, KC_LEFT_CTRL, KC_LEFT_SHIFT, TD(0), KC_ENTER, TO(0), _______, _______, _______
    ),
    [2] = LAYOUT_ansi_89(
        KC_AUDIO_MUTE, KC_ESCAPE, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, KC_F11, KC_F12, KC_INSERT, KC_DELETE,
        MC_1, KC_F12, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, KC_F11, KC_EQUAL, KC_BACKSPACE, KC_PAGE_UP,
        MC_2, LSFT(KC_GRAVE), LSFT(KC_1), LSFT(KC_2), LSFT(KC_3), LSFT(KC_4), LSFT(KC_5), LSFT(KC_6), LSFT(KC_7), LSFT(KC_8), KC_LEFT_BRACKET, KC_RIGHT_BRACKET, LSFT(KC_EQUAL), KC_RIGHT_BRACKET, KC_BACKSLASH, KC_PAGE_DOWN,
        MC_3, KC_ESCAPE, LSFT(KC_SEMICOLON), KC_EQUAL, LSFT(KC_MINUS), LSFT(KC_BACKSLASH), KC_BACKSLASH, XXXXXXX, LSFT(KC_9), LSFT(KC_0), KC_MINUS, LSFT(KC_QUOTE), KC_AUDIO_VOL_UP, KC_ENTER, KC_HOME,
        MC_4, KC_PRINT_SCREEN, XXXXXXX, XXXXXXX, LSFT(KC_LEFT_BRACKET), LSFT(KC_RIGHT_BRACKET), XXXXXXX, KC_B, KC_AUDIO_MUTE, XXXXXXX, LSFT(KC_COMMA), LSFT(KC_DOT), LSFT(KC_SLASH), KC_AUDIO_VOL_DOWN, KC_UP,
        MC_5, KC_LEFT_CTRL, KC_LEFT_GUI, KC_LEFT_ALT, KC_MEDIA_REWIND, TO(0), KC_MEDIA_FAST_FORWARD, TO(3), KC_LEFT, KC_DOWN, KC_RIGHT
    ),
    [3] = LAYOUT_ansi_89(
        RGB_TOG, QK_BOOTLOADER, KC_BRIGHTNESS_DOWN, KC_BRIGHTNESS_UP, KC_TASK, KC_FILE, RGB_VAD, RGB_VAI, KC_MEDIA_PREV_TRACK, KC_MEDIA_PLAY_PAUSE, KC_MEDIA_NEXT_TRACK, KC_AUDIO_MUTE, KC_AUDIO_VOL_DOWN, KC_AUDIO_VOL_UP, _______, _______,
        _______, _______, BT_HST1, BT_HST2, BT_HST3, P2P4G, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, RGB_TOG, RGB_MODE_FORWARD, RGB_VAI, RGB_HUI, RGB_SAI, RGB_SPI, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, RGB_MODE_REVERSE, RGB_VAD, RGB_HUD, RGB_SAD, RGB_SPD, _______, _______, _______, _______, _______, _______, _______, KC_END,
        _______, _______, _______, _______, _______, _______, BAT_LVL, BAT_LVL, QK_MAGIC_TOGGLE_NKRO, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, TO(2), _______, TO(0), _______, _______, _______
    ),
    [4] = LAYOUT_ansi_89(
        RGB_TOG, _______, KC_BRIGHTNESS_DOWN, KC_BRIGHTNESS_UP, KC_TASK, KC_FILE, RGB_VAD, RGB_VAI, KC_MEDIA_PREV_TRACK, KC_MEDIA_PLAY_PAUSE, KC_MEDIA_NEXT_TRACK, KC_AUDIO_MUTE, KC_AUDIO_VOL_DOWN, KC_AUDIO_VOL_UP, _______, _______,
        _______, OSL(5), BT_HST1, BT_HST2, BT_HST3, P2P4G, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, RGB_TOG, RGB_MODE_FORWARD, RGB_VAI, RGB_HUI, RGB_SAI, RGB_SPI, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, KC_MS_BTN3, KC_MS_WH_LEFT, KC_MS_WH_RIGHT, KC_MS_BTN2, KC_MS_BTN1, XXXXXXX, XXXXXXX, KC_MS_UP, KC_MS_LEFT, KC_MS_DOWN, KC_MS_RIGHT, XXXXXXX, _______, KC_END,
        _______, XXXXXXX, XXXXXXX, XXXXXXX, KC_MS_WH_UP, KC_MS_WH_DOWN, XXXXXXX, BAT_LVL, QK_MAGIC_TOGGLE_NKRO, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, KC_LEFT_CTRL, KC_SPACE, TD(0), KC_ENTER, TO(0), _______, _______, _______
    ),
    [5] = LAYOUT_ansi_89(
        RGB_TOG, _______, KC_BRIGHTNESS_DOWN, KC_BRIGHTNESS_UP, KC_TASK, KC_FILE, RGB_VAD, RGB_VAI, KC_MEDIA_PREV_TRACK, KC_MEDIA_PLAY_PAUSE, KC_MEDIA_NEXT_TRACK, KC_AUDIO_MUTE, KC_AUDIO_VOL_DOWN, KC_AUDIO_VOL_UP, _______, _______,
        _______, QK_LEADER, XXXXXXX, XXXXXXX, XXXXXXX, LALT(KC_F4), XXXXXXX, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, LCTL(KC_GRAVE), XXXXXXX, XXXXXXX, LSFT(LCTL(KC_E)), LSFT(LCTL(KC_R)), LSFT(LCTL(KC_T)), XXXXXXX, XXXXXXX, XXXXXXX, LSFT(LCTL(KC_O)), LSFT(LCTL(KC_P)), XXXXXXX, _______, _______, _______,
        _______, XXXXXXX, XXXXXXX, LSFT(LCTL(KC_S)), LALT(LSFT(KC_D)), LSFT(LCTL(KC_F)), XXXXXXX, XXXXXXX, LALT(KC_UP), LALT(KC_LEFT), LALT(KC_DOWN), LALT(KC_RIGHT), XXXXXXX, _______, KC_END,
        _______, XXXXXXX, LSFT(LCTL(KC_Z)), XXXXXXX, LSFT(LCTL(KC_C)), LSFT(LCTL(KC_V)), XXXXXXX, BAT_LVL, LSFT(LCTL(KC_N)), XXXXXXX, XXXXXXX, CK0, XXXXXXX, XXXXXXX, _______,
        _______, _______, _______, _______, _______, TO(0), _______, TO(5), _______, _______, _______
    ),
};
// clang-format on

#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][2] = {
    [0] = {ENCODER_CCW_CW(KC_VOLD, KC_VOLU)}, [1] = {ENCODER_CCW_CW(KC_VOLD, KC_VOLU)}, [2] = {ENCODER_CCW_CW(KC_VOLD, KC_VOLU)},
    [3] = {ENCODER_CCW_CW(RGB_VAD, RGB_VAI)}, [4] = {ENCODER_CCW_CW(KC_VOLD, KC_VOLU)}, [5] = {ENCODER_CCW_CW(KC_VOLD, KC_VOLU)},
};
#endif

static void td0_finished(tap_dance_state_t *state, void *user_data) {
    if (state->count == 1) { set_oneshot_layer(1, ONESHOT_START); clear_oneshot_layer_state(ONESHOT_PRESSED); }
    else if (state->count == 2) { layer_move(1); }
}
static void td0_reset(tap_dance_state_t *state, void *user_data) { (void)state; (void)user_data; }
tap_dance_action_t tap_dance_actions[] = {
    [TD0] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, td0_finished, td0_reset),
};

/* ---- reconstructed leader hooks (custom_code/leader.c) ---- */
void leader_start_user(void) {
    rgb_matrix_set_color_all(255, 0, 255);
}

void leader_end_user(void) {
    rgb_matrix_set_color_all(0, 0, 0);

    if (leader_sequence_one_key(KC_F)) {
        register_code(KC_LGUI);   register_code(KC_P);
        unregister_code(KC_LGUI); unregister_code(KC_P);
        register_code(KC_LGUI);   register_code(KC_K);
        unregister_code(KC_LGUI); unregister_code(KC_K);
    }
    if (leader_sequence_two_keys(KC_A, KC_Q)) {
        register_code(KC_LCTL);   register_code(KC_A);
        unregister_code(KC_LCTL); unregister_code(KC_A);
        register_code(KC_Z);      unregister_code(KC_Z);
        register_code(KC_Q);      unregister_code(KC_Q);
        register_code(KC_ENT);    unregister_code(KC_ENT);
    }
    if (leader_sequence_one_key(KC_Y)) {
        register_code(KC_LCTL);   register_code(KC_X);
        unregister_code(KC_LCTL); unregister_code(KC_X);
        register_code(KC_Y);      unregister_code(KC_Y);
        register_code(KC_ENT);    unregister_code(KC_ENT);
    }
    if (leader_sequence_two_keys(KC_LCTL, KC_I)) {
        register_code(KC_LCTL);   register_code(KC_LALT);   register_code(KC_I);
        unregister_code(KC_LCTL); unregister_code(KC_LALT); unregister_code(KC_I);
    }
    if (leader_sequence_one_key(KC_J)) {
        register_code(KC_LGUI);   register_code(KC_P);
        unregister_code(KC_LGUI); unregister_code(KC_P);
    }
    if (leader_sequence_one_key(KC_F)) {
        register_code(KC_LGUI);   register_code(KC_QUOT);
        unregister_code(KC_LGUI); unregister_code(KC_QUOT);
    }
    if (leader_sequence_one_key(KC_DEL)) {
        register_code(KC_LGUI);   register_code(KC_UP);   register_code(KC_LEFT);
        unregister_code(KC_LGUI); unregister_code(KC_UP); unregister_code(KC_LEFT);
    }
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (!process_record_keychron_common(keycode, record)) return false;
    switch (keycode) {
        case CK0: if (record->event.pressed) { tap_code16(KC_MINS); tap_code16(KC_MINS); } return false;
        case CK1: if (record->event.pressed) { tap_code16(KC_DOT); tap_code16(KC_SLSH); } return false;
    }
    return true;
}
