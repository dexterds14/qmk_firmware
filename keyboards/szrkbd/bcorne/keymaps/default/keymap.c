// Copyright 2026 dexterds14
// SPDX-License-Identifier: GPL-2.0-or-later
//
// PLACEHOLDER default keymap for szrkbd/bcorne. Matrix positions are verified
// from the stock firmware; the keycode assignments below are a best-effort
// QWERTY default for bring-up/testing and are meant to be replaced with your
// real keymap. Argument order matches the LAYOUT macro (= keyboard.json order).

#include QMK_KEYBOARD_H

enum layers { _BASE, _FN };


// LAYOUT argument order (one line per physical row below):
//   left rows 0-3 (row 1/2 col6 = inner-column key, row 3 col6 = knob push),
//   left thumbs; right rows 0-3 (row 1/2 col0 = inner, row 3 col0 = knob
//   push), right thumbs.
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_BASE] = LAYOUT(
        KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_UP,
        KC_CAPS, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_DOWN,
        KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_MUTE,
                                   KC_LCTL, MO(1),   KC_SPC,
                 KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSPC,
        KC_LEFT, KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_ENT,
        KC_RGHT, KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,
        KC_MPLY, KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_DEL,
                                   KC_RGUI, MO(1),   KC_ENT
    ),
    [_FN] = LAYOUT(
        QK_BOOT, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
                                   KC_TRNS, KC_TRNS, KC_TRNS,
                 RM_TOGG, RM_NEXT, RM_HUEU, RM_SATU, RM_VALU, QK_BOOT,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
                                   KC_TRNS, KC_TRNS, KC_TRNS
    ),
};

// Encoder 0 = left knob (pads B9/B8), encoder 1 = right knob (pads B6/B4).
// If a knob turns the "wrong" way, swap its pin_a/pin_b in keyboard.json.
#ifdef ENCODER_MAP_ENABLE
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    [_BASE] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU),  ENCODER_CCW_CW(KC_PGUP, KC_PGDN) },
    [_FN]   = { ENCODER_CCW_CW(RM_PREV, RM_NEXT),  ENCODER_CCW_CW(RM_VALD, RM_VALU) },
};
#endif
