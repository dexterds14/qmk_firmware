// YMD09 as a nav/layer pad -- an adaptation of the ZMX Panda20 layout
// (keyboards/zmx/panda20/keymap.txt). The Panda20's arrow cluster and its
// two custom layers used exactly the 7-8-9/4-5-6/1-2-3 positions, so they
// transfer here spatially; keys the Panda20 had outside that block are
// dropped (Alt+F/D/S/A row, Alt+G, End).
//
// Bottom-row layer keys are one-shot with lock (ONESHOT_TAP_TOGGLE 2 in
// config.h): tap = next keypress on layer, double-tap = lock, tap again =
// unlock, hold = momentary.

#include QMK_KEYBOARD_H

enum layers {
    _BASE,
    _SWAY,  // sway movement (Alt chords), bottom-right
    _CTLX,  // ctrl-x chords, bottom-middle
    _SHORT, // shortcuts, bottom-left
    _WORK,  // sway workspace switching, entered from _SWAY bottom-middle
};

enum custom_keycodes {
    // Quit minicom (Ctrl+A, Z, Q, Enter) -- the bcorne "a-q" leader
    // sequence as a direct macro.
    MINICOM_QUIT = SAFE_RANGE,
    // Save and quit nano (Ctrl+X, Y, Enter) -- the bcorne "y" leader.
    NANO_SAVEQUIT,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    [_BASE] = LAYOUT(
        KC_PGUP,     KC_UP,      KC_PGDN,
        KC_LEFT,     KC_DOWN,    KC_RGHT,
        OSL(_SHORT), OSL(_CTLX), OSL(_SWAY)
    ),

    [_SWAY] = LAYOUT(
        LALT(KC_U), LALT(KC_J), LALT(KC_O),
        LALT(KC_K), LALT(KC_L), LALT(KC_QUOT),
        LALT(KC_I), OSL(_WORK), KC_TRNS
    ),

    [_CTLX] = LAYOUT(
        LCTL(KC_0),         LCTL(KC_1), LCTL(KC_2),
        LCTL(LSFT(KC_TAB)), KC_NO,      LCTL(KC_TAB),
        LCTL(KC_GRV),       KC_TRNS,    LCTL(KC_B)
    ),

    [_SHORT] = LAYOUT(
        QK_BOOT,      NANO_SAVEQUIT,    KC_NO,
        MINICOM_QUIT, LCTL(LSFT(KC_C)), LCTL(LSFT(KC_V)),
        KC_TRNS,      KC_NO,            KC_NO
    ),

    // Sway workspace switching ($mod = Alt; ws1..6 = f/d/s/a/g/h in the
    // sway config). Arranged 5-4-6 over 3-2-1 by workspace number.
    // Bottom-middle repeats OSL(_WORK) so tapping it always unlocks a
    // stuck layer, even if _SWAY has already dropped off underneath.
    [_WORK] = LAYOUT(
        LALT(KC_G), LALT(KC_A), LALT(KC_H),
        LALT(KC_S), LALT(KC_D), LALT(KC_F),
        KC_NO,      OSL(_WORK), KC_NO
    ),

};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case MINICOM_QUIT:
            if (record->event.pressed) {
                tap_code16(LCTL(KC_A));
                tap_code(KC_Z);
                tap_code(KC_Q);
                tap_code(KC_ENT);
            }
            return false;
        case NANO_SAVEQUIT:
            if (record->event.pressed) {
                tap_code16(LCTL(KC_X));
                tap_code(KC_Y);
                tap_code(KC_ENT);
            }
            return false;
    }
    return true;
}

// Whole-board solid color per active layer. One-shot arming raises the
// layer in layer_state just like a lock does, so the color doubles as
// "layer armed" feedback. Values stay low: 9 LEDs, but also no reason to
// glare.
bool rgb_matrix_indicators_user(void) {
    switch (get_highest_layer(layer_state)) {
        case _SWAY:
            rgb_matrix_set_color_all(200, 0, 160); // magenta
            break;
        case _CTLX:
            rgb_matrix_set_color_all(0, 160, 40); // green
            break;
        case _SHORT:
            rgb_matrix_set_color_all(200, 110, 0); // amber
            break;
        case _WORK:
            rgb_matrix_set_color_all(80, 0, 200); // purple
            break;
        default:
            rgb_matrix_set_color_all(10, 10, 10); // dim white
            break;
    }
    return false;
}
