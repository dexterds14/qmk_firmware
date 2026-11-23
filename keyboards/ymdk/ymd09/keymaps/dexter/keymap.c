// YMD09 as a nav/layer pad -- an adaptation of the ZMX Panda20 layout
// (keyboards/zmx/panda20/keymap.txt). The Panda20's sway-movement block
// and its custom layers used exactly the 7-8-9/4-5-6/1-2-3 positions, so
// they transfer here spatially; keys the Panda20 had outside that block
// are dropped (Alt+F/D/S/A row, Alt+G, Home/End).
//
// Base is the sway movement layer (Alt chords). Bottom row: workspace
// layer (left), Ctl-X (middle), arrows/PgUp/PgDn (right). Shortcuts are
// on the arrows layer's bottom-left.
//
// Bottom-row layer keys are one-shot with lock (ONESHOT_TAP_TOGGLE 2 in
// config.h): tap = next keypress on layer, double-tap = lock, tap again =
// unlock, hold = momentary. A locked layer's color breathes; a one-shot
// (armed) layer's is steady.

#include QMK_KEYBOARD_H

enum layers {
    _BASE,   // sway movement (Alt chords)
    _ARROWS, // arrows + PgUp/PgDn, bottom-right
    _CTLX,   // ctrl-x chords, bottom-middle
    _SHORT,  // shortcuts, bottom-left of _ARROWS
    _WORK,   // sway workspace switching, bottom-left
};

enum custom_keycodes {
    // Quit minicom (Ctrl+A, Z, Q, Enter) -- the bcorne "a-q" leader
    // sequence as a direct macro.
    MINICOM_QUIT = SAFE_RANGE,
    // Save and quit nano (Ctrl+X, Y, Enter) -- the bcorne "y" leader.
    NANO_SAVEQUIT,
    // Drop every layer and any one-shot / locked one-shot state: one tap
    // back to base, whether the current layer is armed or locked.
    LAYER_EXIT,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    [_BASE] = LAYOUT(
        LALT(KC_U),  LALT(KC_J), LALT(KC_O),
        LALT(KC_K),  LALT(KC_L), LALT(KC_QUOT),
        OSL(_WORK),  OSL(_CTLX), OSL(_ARROWS)
    ),

    // Bottom-right is TRNS so it resolves to the base OSL(_ARROWS) and
    // tap-toggles the lock. Bottom-middle is Enter, so Ctl-X is not
    // reachable from here.
    [_ARROWS] = LAYOUT(
        KC_PGUP,     KC_UP,   KC_PGDN,
        KC_LEFT,     KC_DOWN, KC_RGHT,
        OSL(_SHORT), KC_ENT,  KC_TRNS
    ),

    [_CTLX] = LAYOUT(
        LCTL(KC_0),         LCTL(KC_1), LCTL(KC_2),
        LCTL(LSFT(KC_TAB)), KC_NO,      LCTL(KC_TAB),
        LCTL(KC_GRV),       KC_TRNS,    LCTL(KC_B)
    ),

    // Entered with a single tap on _ARROWS' bottom-left, so this layer is
    // normally one-shot, not locked. Bottom-left is LAYER_EXIT, not
    // OSL(_SHORT): on an armed layer its own OSL counts as the second tap
    // of a double-tap and locks it instead of leaving, and the next quick
    // tap then lands on the base OSL(_WORK) as a further sequential tap
    // (QMK counts taps per key position, not per keycode). Not TRNS
    // either -- that would land on the base OSL(_WORK) directly.
    [_SHORT] = LAYOUT(
        QK_BOOT,      NANO_SAVEQUIT,    KC_NO,
        MINICOM_QUIT, LCTL(LSFT(KC_C)), LCTL(LSFT(KC_V)),
        LAYER_EXIT,   KC_NO,            KC_NO
    ),

    // Sway workspace switching ($mod = Alt; ws1..6 = f/d/s/a/g/h in the
    // sway config). Arranged 5-4-6 over 3-2-1 by workspace number.
    // Bottom-left repeats the base OSL(_WORK) so tapping it locks /
    // unlocks.
    [_WORK] = LAYOUT(
        LALT(KC_G), LALT(KC_A), LALT(KC_H),
        LALT(KC_S), LALT(KC_D), LALT(KC_F),
        OSL(_WORK), KC_NO,      KC_NO
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
        case LAYER_EXIT:
            if (record->event.pressed) {
                reset_oneshot_layer();
                layer_clear();
            }
            return false;
    }
    return true;
}

// Per-layer colors. Colors follow the layer's contents, not its position:
// sway is magenta (it was the bottom-right layer before the base/arrows
// flip), arrows are dim white. Values stay low: 9 LEDs, but also no reason
// to glare.
typedef struct {
    uint8_t r, g, b;
} layer_rgb_t;

static const layer_rgb_t layer_colors[] = {
    [_BASE]   = {200, 0, 160},  // magenta (sway)
    [_ARROWS] = {10, 10, 10},   // dim white
    [_CTLX]   = {0, 160, 40},   // green
    [_SHORT]  = {200, 110, 0},  // amber
    [_WORK]   = {80, 0, 200},   // purple
};

// The layer a layer-switching keycode moves to, or -1 if kc is not one.
static int8_t layer_key_target(uint16_t kc) {
    if (kc == LAYER_EXIT) return _BASE;
    if (IS_QK_ONE_SHOT_LAYER(kc)) return QK_ONE_SHOT_LAYER_GET_LAYER(kc);
    if (IS_QK_TO(kc)) return QK_TO_GET_LAYER(kc);
    if (IS_QK_MOMENTARY(kc)) return QK_MOMENTARY_GET_LAYER(kc);
    if (IS_QK_TOGGLE_LAYER(kc)) return QK_TOGGLE_LAYER_GET_LAYER(kc);
    return -1;
}

// Lock-pulse timing and curve, copied from the szrkbd/bcorne dexter keymap
// (see its lock_pulse_val() for the reasoning): ~2.3 s triangle wave off
// the RGB frame timer, phase squared so the fade fills the whole cycle,
// down to true black with no floor.
#define PULSE_BLACK_MS  64                                 // phase 0..15
#define PULSE_RAMP_MS   1104                               // phase 16..255
#define PULSE_HALF_MS   (PULSE_BLACK_MS + PULSE_RAMP_MS)   // 1168
#define PULSE_PERIOD_MS (2 * PULSE_HALF_MS)                // 2336

static uint8_t lock_pulse_val(void) {
    uint16_t t = g_rgb_timer % PULSE_PERIOD_MS;
    if (t >= PULSE_HALF_MS) t = PULSE_PERIOD_MS - 1 - t; // mirror the falling half
    uint8_t phase;
    if (t < PULSE_BLACK_MS) {
        phase = t >> 2;                                                     // 0..15
    } else {
        phase = 16 + (uint32_t)(t - PULSE_BLACK_MS) * 240 / PULSE_RAMP_MS;  // 16..255
    }
    return (uint8_t)(((uint16_t)phase * phase) >> 8);                       // 0..~255
}

// The whole board glows the active layer's color. One-shot arming raises
// the layer in layer_state just like a lock does, so the color doubles as
// "layer armed" feedback. When the layer is locked (its OSL double-tapped)
// the background breathes; the layer keys below stay steady so they remain
// readable.
//
// Each layer key then shows the color of the layer it moves to. Keys are
// resolved the way a press would be (layer_switch_get_layer), so a TRNS
// key that falls through to a base-layer OSL counts too. A key that
// targets the layer already showing is its lock / unlock key; it shows
// the base color instead, since unlocking returns to base (and in the
// layer's own color it would blend in).
bool rgb_matrix_indicators_user(void) {
    uint8_t top = get_highest_layer(layer_state);
    if (top >= ARRAY_SIZE(layer_colors)) top = _BASE;
    layer_rgb_t bg = layer_colors[top];
    if ((get_oneshot_layer_state() & ONESHOT_TOGGLED) && get_oneshot_layer() == top) {
        uint16_t v = lock_pulse_val();
        bg.r       = (bg.r * v) >> 8;
        bg.g       = (bg.g * v) >> 8;
        bg.b       = (bg.b * v) >> 8;
    }
    rgb_matrix_set_color_all(bg.r, bg.g, bg.b);

    for (uint8_t row = 0; row < MATRIX_ROWS; row++) {
        for (uint8_t col = 0; col < MATRIX_COLS; col++) {
            uint8_t led = g_led_config.matrix_co[row][col];
            if (led == NO_LED) continue;

            keypos_t pos    = {.row = row, .col = col};
            uint16_t kc     = keymap_key_to_keycode(layer_switch_get_layer(pos), pos);
            int8_t   target = layer_key_target(kc);
            if (target < 0 || target >= (int8_t)ARRAY_SIZE(layer_colors)) continue;
            if (target == top) target = _BASE;

            layer_rgb_t c = layer_colors[target];
            rgb_matrix_set_color(led, c.r, c.g, c.b);
        }
    }
    return false;
}
