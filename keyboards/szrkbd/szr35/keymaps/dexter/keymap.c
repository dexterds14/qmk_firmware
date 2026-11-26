// Copyright 2026 dexterds14
// SPDX-License-Identifier: GPL-2.0-or-later
//
// Port of the szrkbd/bcorne dexter keymap to the 36-key SZR35 (3x5 + 3 thumbs
// per half). The 3x5 letter grid and the thumbs of every bcorne layer are kept
// as-is; the bcorne's number row, 6th columns, centre keys and knobs are gone.
// What they carried now lives on:
//   _NUM  digits on the top row + PgUp/PgDn/Home/End. Locked: double-tap L
//         enters, G leaves, H goes on to _FN.
//   _FN   F-keys, volume/media, tab/window switching. Locked: H goes back to
//         _NUM, G leaves.
//   free slots of the original layers (RGB brightness on RAISE2, + on RAISE,
//   middle click on MOUSE, the Ctrl+Shift+=/- pair on LEADR, ...).
// _NUM and _FN sit BELOW the bcorne layers in the layer stack so a one-shot
// LOWER/RAISE taken from inside _NUM overrides it and then drops back to it.
//
// LAYOUT_split_3x5_3 argument order: rows 0-2 as left 5 then right 5, then
// left thumbs (outer, middle, big) and right thumbs (big, middle, outer).
// The thumb rows are mirrored relative to the bcorne on every layer (its outer
// thumb function is on the big inner key here and vice versa): base is
// Esc/Bksp/Space | Enter/Lead/Del.

#include QMK_KEYBOARD_H

#define _QWERTY 0
#define _NUM 1
#define _FN 2
#define _LOWER 3
#define _RAISE 4
#define _RAISE2 5
#define _MOUSE 6
#define _LEADR 7
// Phantom layers: never used for key lookups (fully transparent). Their bits
// in layer_state signal master-local indicator state (caps lock, alt mod-lock,
// lower layer-lock) to the slave over the layer-state sync, so the slave's
// RGB indicator can render them.
#define _CAPSIND 8
#define _ALTLKIND 9
#define _LOWLKIND 10
#define PHANTOM_LAYERS_MASK (((layer_state_t)1 << _CAPSIND) | ((layer_state_t)1 << _ALTLKIND) | ((layer_state_t)1 << _LOWLKIND))

typedef enum {
    TD_NONE,
    TD_UNKNOWN,
    TD_SINGLE_TAP,
    TD_SINGLE_HOLD,
    TD_DOUBLE_TAP,
    TD_TRIPLE_TAP,
} td_state_t;

typedef struct {
    bool is_press_action;
    td_state_t state;
} td_tap_t;

enum custom_keycodes
{
    DOT_SLS = SAFE_RANGE,
    DIR_UP,
    DBL_DASH
};

enum tap_dance_keys {
    LAYR_DOWN,
    LAYR_UP,
    TD_S_OSM,     // shift OSM - on S key
    TD_J_OSM,
    TD_D_OSM,     // alt OSM - on D key
    TD_H_CAPS,
    TD_G_CAPS,
    TD_V_TAB,
    TD_Q_TILD,
    TD_Z_GRV,
    TD_L_NUM      // double-tap L: move to (locked) _NUM
};

// Declare the functions to be used with your tap dance key(s)
// Function associated with all tap dances
td_state_t cur_dance(tap_dance_state_t *state);

// Functions associated with individual tap dances
void layr_dn_finished(tap_dance_state_t *state, void *user_data);
void layr_dn_reset(tap_dance_state_t *state, void *user_data);
static void layer_move_toLower(void);
static void layer_oneshot_Lower(void);
static uint8_t return_to_mouse = 0;
static uint8_t move_to_lower = 0;
static uint8_t leader_active = 0;
static uint8_t alt_locked = 0;     // mod-lock Alt (triple-tap D, toggles on/off)
static bool caps_state = false;     // caps lock state (direct key + tap dance G/H)
static uint8_t lower_locked = 0;    // lower layer locked (moved to, not oneshot)

// Fast typing detection
static uint32_t last_keypress_time = 0;
static bool     fast_typing_active = false;
static bool     td_in_progress = false;


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_QWERTY] = LAYOUT_split_3x5_3(
        TD(TD_Q_TILD), KC_W,          KC_E,          KC_R,          KC_T,                KC_Y,          KC_U,          KC_I,          KC_O,          KC_P,
        KC_A,          TD(TD_S_OSM),  TD(TD_D_OSM),  TD(LAYR_DOWN), TD(TD_G_CAPS),       TD(TD_H_CAPS), TD(TD_J_OSM),  TD(LAYR_UP),   TD(TD_L_NUM),  KC_QUOT,
        TD(TD_Z_GRV),  KC_X,          KC_C,          TD(TD_V_TAB),  KC_B,                KC_N,          KC_M,          KC_COMM,       KC_DOT,        KC_SLSH,
                                      KC_ESC,        KC_BSPC,       KC_SPC,              KC_ENT,        OSL(_LEADR),   KC_DEL
    ),

    // Locked number layer. Everything transparent keeps its base behaviour, so
    // the S/D/F/J/K dances (shift, alt, lower, raise) still work in here.
    [_NUM] = LAYOUT_split_3x5_3(
        KC_1,          KC_2,          KC_3,          KC_4,          KC_5,                KC_6,          KC_7,          KC_8,          KC_9,          KC_0,
        _______,       _______,       _______,       _______,       TO(_QWERTY),         TO(_FN),       _______,       _______,       KC_PGUP,       KC_HOME,
        _______,       _______,       _______,       _______,       _______,             KC_MINS,       KC_DOT,        KC_COMM,       KC_PGDN,       KC_END,
                                      _______,       _______,       _______,             _______,       _______,       _______
    ),

    // Locked function layer: F-keys plus what the bcorne's LOWER number row,
    // RAISE 6th column/centre keys and knobs carried.
    [_FN] = LAYOUT_split_3x5_3(
        KC_F1,         KC_F2,         KC_F3,         KC_F4,         KC_F5,               KC_F6,         KC_F7,         KC_F8,         KC_F9,         KC_F10,
        KC_F11,        KC_F12,        KC_PSCR,       LSFT(KC_TAB),  TO(_QWERTY),         TO(_NUM),      KC_VOLD,       KC_VOLU,       KC_MUTE,       KC_MSTP,
        LCTL(KC_1),    LCTL(KC_2),    LCTL(LSFT(KC_TAB)), LCTL(KC_TAB), LALT(KC_TAB),    LALT(KC_GRV),  LALT(KC_ENT),  KC_MRWD,       KC_MFFD,       KC_NO,
                                      _______,       _______,       _______,             _______,       _______,       _______
    ),

    [_LOWER] = LAYOUT_split_3x5_3(
        LCTL(KC_Q),    LCTL(KC_W),    KC_LALT,       LCTL(KC_R),    LCTL(KC_T),          LCTL(KC_Y),    LCTL(KC_U),    LCTL(KC_I),    LCTL(KC_O),    LCTL(KC_P),
        LCTL(KC_A),    LCTL(KC_S),    LCTL(KC_D),    LCTL(KC_F),    LCTL(KC_0),          TO(_QWERTY),   KC_UP,         KC_LEFT,       KC_DOWN,       KC_RGHT,
        LCTL(KC_Z),    LCTL(KC_X),    LCTL(KC_C),    LCTL(KC_V),    LCTL(KC_B),          LCTL(KC_N),    DBL_DASH,      DOT_SLS,       DIR_UP,        LCTL(KC_SLSH),
                                      KC_SPC,        KC_LSFT,       KC_LCTL,             KC_ENT,        KC_BSPC,       KC_DEL
    ),

    [_RAISE] = LAYOUT_split_3x5_3(
        KC_EXLM,       KC_AT,         KC_HASH,       KC_DLR,        KC_PERC,             KC_CIRC,       KC_AMPR,       KC_ASTR,       KC_LBRC,       KC_RBRC,
        KC_COLN,       KC_EQL,        KC_UNDS,       KC_PIPE,       TO(_QWERTY),         TO(_RAISE2),   KC_LPRN,       KC_RPRN,       KC_MINS,       KC_DQUO,
        KC_ESC,        KC_GRV,        KC_LCBR,       KC_RCBR,       KC_CIRC,             KC_MUTE,       KC_PLUS,       KC_LT,         KC_GT,         KC_QUES,
                                      _______,       _______,       TO(_QWERTY),         KC_SCLN,       _______,       _______
    ),

    [_RAISE2] = LAYOUT_split_3x5_3(
        QK_BOOT,       _______,       EE_CLR,        TO(_RAISE),    RM_PREV,             TO(_QWERTY),   RM_VALD,       RM_VALU,       RM_SPDU,       QK_BOOT,
        KC_LEFT,       KC_UP,         KC_DOWN,       KC_RGHT,       TO(_QWERTY),         KC_RPRN,       KC_MPRV,       KC_MPLY,       KC_MNXT,       _______,
        _______,       _______,       _______,       _______,       KC_LPRN,             RM_TOGG,       RM_NEXT,       RM_HUEU,       RM_SATU,       RM_SPDD,
                                      _______,       _______,       TO(_RAISE),          TO(_QWERTY),   _______,       _______
    ),

    [_MOUSE] = LAYOUT_split_3x5_3(
        _______,       KC_NO,         KC_NO,         KC_NO,         KC_NO,               KC_NO,         MS_WHLU,       MS_WHLD,       KC_PLUS,       KC_MINS,
        MS_WHLL,       MS_WHLR,       MS_BTN2,       MS_BTN1,       MS_BTN3,             TO(_QWERTY),   MS_UP,         MS_LEFT,       MS_DOWN,       MS_RGHT,
        KC_LSFT,       KC_TAB,        MS_WHLU,       MS_WHLD,       KC_LALT,             KC_NO,         KC_NO,         KC_NO,         KC_NO,         KC_NO,
                                      KC_LCTL,       TD(LAYR_DOWN), KC_SPC,              KC_ENT,        TO(_QWERTY),   KC_LCTL
    ),

    [_LEADR] = LAYOUT_split_3x5_3(
        LCTL(KC_GRV),  LALT(KC_F4),   LCTL(LSFT(KC_E)), LCTL(LSFT(KC_R)), LCTL(LSFT(KC_T)),    LCTL(LSFT(KC_EQL)), KC_NO,    KC_NO,         LCTL(LSFT(KC_O)), LCTL(LSFT(KC_P)),
        LCTL(LSFT(KC_A)), LCTL(LSFT(KC_S)), LALT(LSFT(KC_D)), LCTL(LSFT(KC_F)), TO(_QWERTY),   LCTL(LSFT(KC_MINS)), LALT(KC_UP), LALT(KC_LEFT), LALT(KC_DOWN), LALT(KC_RIGHT),
        LCTL(LSFT(KC_Z)), KC_NO,      LCTL(LSFT(KC_C)), LCTL(LSFT(KC_V)), KC_NO,               LCTL(LSFT(KC_N)), LCTL(KC_ENT), KC_NO,       DOT_SLS,       KC_NO,
                                      _______,       _______,       _______,             TO(_LEADR),    QK_LEAD,       _______
    ),

    [_CAPSIND] = LAYOUT_split_3x5_3(
        _______, _______, _______, _______, _______,      _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______,      _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______,      _______, _______, _______, _______, _______,
                          _______,       _______,       _______,             _______,       _______,       _______
    ),

    [_ALTLKIND] = LAYOUT_split_3x5_3(
        _______, _______, _______, _______, _______,      _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______,      _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______,      _______, _______, _______, _______, _______,
                          _______,       _______,       _______,             _______,       _______,       _______
    ),

    [_LOWLKIND] = LAYOUT_split_3x5_3(
        _______, _______, _______, _______, _______,      _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______,      _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______,      _______, _______, _______, _______, _______,
                          _______,       _______,       _______,             _______,       _______,       _______
    )
};

void leader_start_user(void) {
    leader_active = 1;
}

void leader_end_user(void) {
    leader_active = 0;

    // Control+H
    if (leader_sequence_one_key(KC_H))
    {
        tap_code16(LCTL(KC_H));
    }
    // Quit minicom (Ctrl+A, Ctrl+Z, Ctrl+Q, Enter)
    else if (leader_sequence_two_keys(KC_A, KC_Q))
    {
        tap_code16(LCTL(KC_A));
        tap_code(KC_Z);
        tap_code(KC_Q);
        tap_code(KC_ENT);
    }
    // Toggle minicom line wrap (Ctrl+A, Z, W)
    else if (leader_sequence_two_keys(KC_A, KC_W))
    {
        tap_code16(LCTL(KC_A));
        tap_code(KC_Z);
        tap_code(KC_W);
    }
    // Save and quit nano (Ctrl+X, Y, Enter)
    else if (leader_sequence_one_key(KC_Y))
    {
        tap_code16(LCTL(KC_X));
        tap_code(KC_Y);
        tap_code(KC_ENT);
    }
    // Alt+Shift+N
    else if (leader_sequence_one_key(KC_N))
    {
        tap_code16(LSA(KC_N));
    }
    // Alt+Esc
    else if (leader_sequence_one_key(KC_ESC))
    {
        tap_code16(LALT(KC_ESC));
    }
    // SWAY: Lock/Hibernate (Ctrl+Alt+I). Leader, C, I -- the bcorne used its
    // centre Ctrl key here, which this board does not have.
    else if (leader_sequence_two_keys(KC_C, KC_I))
    {
        tap_code16(LCA(KC_I));
    }
}

// RGB indicator section (from the bcorne keymap, itself a port of the
// dactyl's rgblight layers). Runs per-frame on both halves; layer state, mods, and
// host LED state are all synced (config.h), so the slave renders everything
// except the master-local leader_active flag -- the same limitation the
// dactyl had.
static void rgb_paint_all(uint8_t led_min, uint8_t led_max, uint8_t hue, uint8_t sat, uint8_t val)
{
    // hsv_to_rgb() does NOT apply the rgb_matrix brightness cap; clamp here
    // so the full-board overlays (incl. white) stay inside the power budget.
    // (rgb_matrix_hsv_to_rgb() has no header prototype, so it can't be
    // called from keymap code -- it is just a weak wrapper around this.)
    if (val > RGB_MATRIX_MAXIMUM_BRIGHTNESS)
    {
        val = RGB_MATRIX_MAXIMUM_BRIGHTNESS;
    }
    HSV hsv = {hue, sat, val};
    RGB rgb = hsv_to_rgb(hsv);
    for (uint8_t i = led_min; i < led_max; i++)
    {
        rgb_matrix_set_color(i, rgb.r, rgb.g, rgb.b);
    }
}

// Lock-pulse timing (ms), same curve as the bcorne. Each half-cycle walks an
// 8-bit phase 0..255 that is then squared; phase 0..15 squares to 0, so that
// stretch is the true-black dwell. On the bcorne the squared value was clamped
// at its brightness cap of 150 (reached at phase 196) and held there; this
// board's cap is lower (RGB_MATRIX_MAXIMUM_BRIGHTNESS, 50), so the clamped
// curve is rescaled to the cap instead of being clamped a second time, which
// would turn most of the cycle into a flat hold.
#define PULSE_SHAPE_CAP 150
#define PULSE_BLACK_MS  64                                 // phase 0..15
#define PULSE_RAMP_MS   1104                               // phase 16..255 (960 * 1.15)
#define PULSE_HALF_MS   (PULSE_BLACK_MS + PULSE_RAMP_MS)   // 1168
#define PULSE_PERIOD_MS (2 * PULSE_HALF_MS)                // 2336

// Breathing value for "locked" indicator states: ~2.3s triangle wave off the
// RGB frame timer (keeps both halves' pulses phase-coherent per frame)
static uint8_t lock_pulse_val(void)
{
    uint16_t t = g_rgb_timer % PULSE_PERIOD_MS;
    if (t >= PULSE_HALF_MS)
    {
        t = PULSE_PERIOD_MS - 1 - t;   // mirror the falling half onto the rising one
    }
    uint8_t phase;
    if (t < PULSE_BLACK_MS)
    {
        phase = t >> 2;                                                      // 0..15
    }
    else
    {
        phase = 16 + (uint32_t)(t - PULSE_BLACK_MS) * 240 / PULSE_RAMP_MS;   // 16..255
    }
    // A linear ramp reads as fast-fade + long bright hold (LED output is
    // linear but eyes are logarithmic: values 128-255 all look "full").
    // Square the phase so the visible fade fills the whole cycle.
    uint16_t v = ((uint16_t)phase * phase) >> 8;                             // 0..~255
    if (v > PULSE_SHAPE_CAP)
    {
        v = PULSE_SHAPE_CAP;
    }
    return (uint8_t)(v * RGB_MATRIX_MAXIMUM_BRIGHTNESS / PULSE_SHAPE_CAP);
}

bool rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max)
{
    uint8_t osm = get_oneshot_mods() | get_oneshot_locked_mods();

    // Precedence mirrors the dactyl's rgblight layer stacking (higher wins):
    // alt > raise2 > shift > leadr > mouse > caps > lower > leader > raise
    // > fn > num. The two locked layers come last so a one-shot taken from
    // inside them shows its own colour.
    if (layer_state_is(_ALTLKIND) || (osm & (MOD_MASK_ALT | MOD_MASK_GUI)))
    {
        // mod-locked alt breathes; a momentary oneshot alt/GUI stays solid
        uint8_t val = layer_state_is(_ALTLKIND) ? lock_pulse_val() : 255;
        rgb_paint_all(led_min, led_max, 191, 255, val);   // purple (hue/sat of HSV_PURPLE)
    }
    else if (layer_state_is(_RAISE2))
    {
        rgb_paint_all(led_min, led_max, HSV_TEAL);
    }
    else if (osm & MOD_MASK_SHIFT)
    {
        rgb_paint_all(led_min, led_max, HSV_WHITE);
    }
    else if (layer_state_is(_LEADR))
    {
        rgb_paint_all(led_min, led_max, HSV_RED);
    }
    else if (layer_state_is(_MOUSE))
    {
        rgb_paint_all(led_min, led_max, 43, 255, 255);   // yellow (hue/sat of HSV_YELLOW); the bcorne's coral is on _NUM here
    }
    else if (layer_state_is(_CAPSIND) || host_keyboard_led_state().caps_lock)
    {
        // caps lock is a lock state: same white as Shift, but breathing (like
        // locked lower) so it's distinguishable from a momentary Shift oneshot
        rgb_paint_all(led_min, led_max, 0, 0, lock_pulse_val());   // pulsing white (HSV_WHITE hue/sat)
    }
    else if (layer_state_is(_LOWER))
    {
        // locked lower breathes; momentary/oneshot lower stays solid
        uint8_t val = layer_state_is(_LOWLKIND) ? lock_pulse_val() : 255;
        rgb_paint_all(led_min, led_max, 85, 255, val);    // green (hue/sat of HSV_GREEN)
    }
    else if (leader_active)
    {
        rgb_paint_all(led_min, led_max, HSV_MAGENTA);
    }
    else if (layer_state_is(_RAISE))
    {
        rgb_paint_all(led_min, led_max, HSV_BLUE);
    }
    else if (layer_state_is(_FN))
    {
        rgb_paint_all(led_min, led_max, HSV_AZURE);       // pale blue
    }
    else if (layer_state_is(_NUM))
    {
        rgb_paint_all(led_min, led_max, 6, 255, 255);     // coral/red-orange (hue 6), the bcorne's mouse colour
    }

    return false;
}

// forward declaration; initalizated later in the file
extern tap_dance_action_t tap_dance_actions[];
// Setup keycode storage
typedef struct {
    uint16_t keycode;
} td_osm_data_t;
static td_osm_data_t f_data = {KC_F};   // layer down on F key (unused - hardcoded in fn)
static td_osm_data_t j_data = {KC_J};
static td_osm_data_t s_data = {KC_S};   // shift OSM on S key
static td_osm_data_t d_data = {KC_D};   // alt OSM on D key
static td_osm_data_t g_data = {KC_G};
static td_osm_data_t h_data = {KC_H};
static td_osm_data_t v_data = {KC_V};
static td_osm_data_t q_data = {KC_Q};
static td_osm_data_t z_data = {KC_Z};
static td_osm_data_t k_data = {KC_K};
static td_osm_data_t l_data = {KC_L};   // move to _NUM on L key

void keyboard_post_init_user(void)
{
    tap_dance_actions[TD_S_OSM].user_data = &s_data;     // shift OSM on S
    tap_dance_actions[TD_J_OSM].user_data = &j_data;
    tap_dance_actions[TD_D_OSM].user_data = &d_data;     // alt OSM on D
    tap_dance_actions[LAYR_DOWN].user_data = &f_data;    // layer down on F
    tap_dance_actions[TD_G_CAPS].user_data = &g_data;
    tap_dance_actions[TD_H_CAPS].user_data = &h_data;
    tap_dance_actions[TD_V_TAB].user_data = &v_data;
    tap_dance_actions[TD_Q_TILD].user_data = &q_data;
    tap_dance_actions[TD_Z_GRV].user_data = &z_data;
    tap_dance_actions[LAYR_UP].user_data = &k_data;
    tap_dance_actions[TD_L_NUM].user_data = &l_data;
}

layer_state_t layer_state_set_user(layer_state_t state)
{
    // Leaving _LOWER always drops the lock (checked against the incoming
    // state, not the not-yet-updated layer_state global)
    if (!layer_state_cmp(state, _LOWER))
    {
        lower_locked = 0;
    }

    // Re-assert the phantom indicator bits from the master-local flags: the
    // layer_clear()/layer_move() calls elsewhere in this keymap would
    // otherwise silently drop them
    state &= ~PHANTOM_LAYERS_MASK;
    if (caps_state)   state |= (layer_state_t)1 << _CAPSIND;
    if (alt_locked)   state |= (layer_state_t)1 << _ALTLKIND;
    if (lower_locked) state |= (layer_state_t)1 << _LOWLKIND;

    return state;
}

bool is_td_key(uint16_t keycode)
{
    // handle tap dance keycodes directly before unwrapping
    switch (keycode)
    {
        case TD(LAYR_DOWN):
        case TD(LAYR_UP):
        case TD(TD_S_OSM):
        case TD(TD_J_OSM):
        case TD(TD_D_OSM):
        case TD(TD_H_CAPS):
        case TD(TD_G_CAPS):
        case TD(TD_V_TAB):
        case TD(TD_Q_TILD):
        case TD(TD_Z_GRV):
        case TD(TD_L_NUM):
            return true;
    }

    return false;
}

// Base letter for each tap-dance key, used while a leader sequence records.
// This switch must be updated whenever TD keys change, or leader sequences on
// those keys silently break.
static uint16_t td_base_keycode(uint16_t keycode)
{
    switch (keycode)
    {
        case TD(LAYR_DOWN):  return KC_F;
        case TD(LAYR_UP):    return KC_K;
        case TD(TD_S_OSM):   return KC_S;
        case TD(TD_J_OSM):   return KC_J;
        case TD(TD_D_OSM):   return KC_D;
        case TD(TD_H_CAPS):  return KC_H;
        case TD(TD_G_CAPS):  return KC_G;
        case TD(TD_V_TAB):   return KC_V;
        case TD(TD_Q_TILD):  return KC_Q;
        case TD(TD_Z_GRV):   return KC_Z;
        case TD(TD_L_NUM):   return KC_L;
    }
    return KC_NO;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record)
{
    // While a leader sequence is recording, tap-dance keys must act as their
    // base letter: the leader core stores TD keycodes raw (never matching
    // KC_H etc. in leader_end_user) and the dance would still fire and type
    // the letter ~TAPPING_TERM later. Mirror process_leader here — add the
    // base keycode to the sequence and consume the event before the
    // tap-dance/leader processors see it.
    if (record->event.pressed && leader_sequence_active() && !leader_sequence_timed_out())
    {
        uint16_t base = td_base_keycode(keycode);
        if (base != KC_NO)
        {
            if (!leader_sequence_add(base))
            {
                leader_end();
                return true;
            }
            leader_reset_timer();
            return false;
        }
    }

    // clear the 'layer movement flags' unless we are pressing down
    if (move_to_lower && (keycode != TD(LAYR_DOWN)))
    {
      move_to_lower = 0;
    }
    // if we are not on 'lower' don't ever 'return to mouse'
    if (return_to_mouse && (!layer_state_is(_LOWER)))
    {
      return_to_mouse = 0;
    }

    // Fast typing detection
    if (record->event.pressed)
    {
        uint32_t now = timer_read32();
        uint32_t delta = now - last_keypress_time;
        fast_typing_active = (last_keypress_time != 0 && delta <= FAST_TYPING_THRESHOLD);
        last_keypress_time = now;

        if (is_td_key(keycode))
        {
            if (!fast_typing_active)
            {
                td_in_progress = true;
            }
        }
    }

    // Only run the following logic on 'downstrokes' of key presses
    if (record->event.pressed)
    {
        if (keycode == KC_CAPS)
        {
            caps_state = !caps_state;
            // Raising/lowering the phantom layer shows the yellow indicator
            // on both halves via layer_state_set_user / the layer-state sync
            if (caps_state) layer_on(_CAPSIND);
            else layer_off(_CAPSIND);
            return true;
        }

      else if (keycode == DOT_SLS)
      {
        register_code(KC_DOT);
        unregister_code(KC_DOT);
        register_code(KC_SLSH);
        unregister_code(KC_SLSH);

        return false;
      }

      else if (keycode == DIR_UP)
      {
        register_code(KC_DOT);
        unregister_code(KC_DOT);
        register_code(KC_DOT);
        unregister_code(KC_DOT);
        register_code(KC_SLSH);
        unregister_code(KC_SLSH);

        return false;
      }

      else if (keycode == DBL_DASH)
      {
        register_code(KC_MINS);
        unregister_code(KC_MINS);
        register_code(KC_MINS);
        unregister_code(KC_MINS);

        return false;
      }
    }

  return true;
}

void on_each_tap_fn(tap_dance_state_t *state, void* user_data)
{
    td_osm_data_t *data = (td_osm_data_t *)user_data;

    if (fast_typing_active && !td_in_progress)
    {
        tap_code(data->keycode);
    }
}

// Determine the current tap dance state
td_state_t cur_dance(tap_dance_state_t *state) {
    if (fast_typing_active && !td_in_progress)
    {
        return TD_UNKNOWN;
    }

    if (state->count == 1) {
        if (!state->pressed) return TD_SINGLE_TAP;
        else if (!state->interrupted)
        {
            return TD_SINGLE_HOLD;
        }
        else
        {
            // Interrupted while still held: another key rolled in before
            // TAPPING_TERM expired (typing from idle, e.g. "fun" with F
            // still down when U lands). Emit the tap instead of swallowing
            // it; a deliberate hold isn't usable before the term anyway.
            return TD_SINGLE_TAP;
        }
    }
    else if (state->count == 2) return TD_DOUBLE_TAP;
    else if (state->count > 2) return TD_TRIPLE_TAP;
    else return TD_UNKNOWN;
}

// Initialize tap structure associated with each tap dance key
static td_tap_t layr_dn_tap_state = {
    .is_press_action = true,
    .state = TD_NONE
};

static td_tap_t layr_up_tap_state = {
    .is_press_action = true,
    .state = TD_NONE
};

static td_tap_t osm_tap_state = {
    .is_press_action = true,
    .state = TD_NONE
};

void oneshot_layer_changed_user(uint8_t layer) {
  // is the oneshot finished?
  if (!layer)
  {
    if (return_to_mouse)
    {
      layer_clear();
      layer_move(_MOUSE);
      return_to_mouse = 0;
    }
  }
}

void layr_up_finished(tap_dance_state_t *state, void *user_data)
{
    layr_up_tap_state.state = cur_dance(state);
    switch (layr_up_tap_state.state)
    {
        case TD_SINGLE_TAP:
            tap_code(KC_K);
            break;
        case TD_DOUBLE_TAP:
            layer_on(_RAISE);
            set_oneshot_layer(_RAISE, ONESHOT_START);
            clear_oneshot_layer_state(ONESHOT_PRESSED);
            break;
        case TD_TRIPLE_TAP:
            layer_on(_RAISE2);
            set_oneshot_layer(_RAISE2, ONESHOT_START);
            clear_oneshot_layer_state(ONESHOT_PRESSED);
            break;
        case TD_UNKNOWN:
            break;
        default:
            break;
    }
}

void layr_up_reset(tap_dance_state_t *state, void *user_data)
{
    layr_up_tap_state.state = TD_NONE;

    td_in_progress = false;
}

static void layer_move_toLower(void)
{
  layer_clear();
  layer_move(_LOWER);
  lower_locked = 1;
  // Re-run layer_state_set_user so the just-set lock reaches the phantom bit
  // (and through it, the slave's RGB indicator)
  layer_state_set(layer_state);
}

static void layer_oneshot_Lower(void)
{
  layer_on(_LOWER);
  set_oneshot_layer(_LOWER, ONESHOT_START);
  clear_oneshot_layer_state(ONESHOT_PRESSED);
}

// Functions that control what our tap dance key does
void layr_dn_finished(tap_dance_state_t *state, void *user_data) {
    layr_dn_tap_state.state = cur_dance(state);
    switch (layr_dn_tap_state.state) {
        case TD_SINGLE_TAP:
            tap_code(KC_F);
            break;
        case TD_DOUBLE_TAP:
            // if we are currently on MOUSE get it out of the way to go "down"
            if (layer_state_is(_MOUSE))
            {
              return_to_mouse = 1;
              layer_clear();
              layer_oneshot_Lower();
            }
            else
            {
              // did we just come from pressing 'lower' once?
              if (move_to_lower)
              {
                layer_move_toLower();
                move_to_lower = 0;
              }
              else if (layer_state_is(_LOWER))
              {
                layer_clear();
                layer_oneshot_Lower();
              }
              else
              {
                move_to_lower = 1;
                layer_oneshot_Lower();
              }
            }
            break;
        case TD_SINGLE_HOLD:
            layer_clear();
            layer_move(_MOUSE);
            break;
        case TD_TRIPLE_TAP:
            layer_move_toLower();
            break;
        case TD_UNKNOWN:
            break;
        default:
            break;
    }
}

void layr_dn_reset(tap_dance_state_t *state, void *user_data) {
    layr_dn_tap_state.state = TD_NONE;

    td_in_progress = false;
}

void osm_finished(tap_dance_state_t *state, void *user_data)
{
    td_osm_data_t *data = (td_osm_data_t *)user_data;
    if (data == NULL) return;
    osm_tap_state.state = cur_dance(state);
    switch (osm_tap_state.state)
    {
        case TD_SINGLE_TAP:
            tap_code(data->keycode);
            break;
        case TD_DOUBLE_TAP:
            switch (data->keycode)
            {
                case KC_D:
                    set_oneshot_mods(MOD_LALT);
                    break;
                case KC_S:
                case KC_J:
                    set_oneshot_mods(MOD_LSFT);
                    break;
                case KC_G:
                case KC_H:
                    tap_code(KC_CAPS);
                    caps_state = !caps_state;
                    if (caps_state) layer_on(_CAPSIND);
                    else layer_off(_CAPSIND);
                    break;
                case KC_V:
                    tap_code(KC_TAB);
                    break;
                case KC_Q:
                    tap_code16(KC_TILD);
                    break;
                case KC_Z:
                    tap_code(KC_GRV);
                    break;
                case KC_L:
                    // locked number layer; G (TO(_QWERTY)) leaves it
                    layer_clear();
                    layer_move(_NUM);
                    break;
                default:
                    break;
            }
            break;
        case TD_TRIPLE_TAP:
            if (data->keycode == KC_D)  // only D key supports mod-lock toggle
            {
                alt_locked = !alt_locked;  // toggle state
                if (alt_locked)
                {
                    register_mods(MOD_BIT(KC_LALT));
                    set_oneshot_locked_mods(get_oneshot_locked_mods() | MOD_LALT);
                }
                else
                {
                    unregister_mods(MOD_BIT(KC_LALT));
                    set_oneshot_locked_mods(get_oneshot_locked_mods() & ~MOD_LALT);
                }
                // No layer transition happens here, so refresh the phantom
                // bits explicitly to publish the lock state to the slave
                layer_state_set(layer_state);
            }
            break;
        case TD_UNKNOWN:
            break;
        default:
            break;
    }
}

void osm_reset(tap_dance_state_t *state, void *user_data)
{
    osm_tap_state.state = TD_NONE;

    td_in_progress = false;
}

tap_dance_action_t tap_dance_actions[] = {
    [LAYR_DOWN] = ACTION_TAP_DANCE_FN_ADVANCED(on_each_tap_fn, layr_dn_finished, layr_dn_reset),
    [LAYR_UP] = ACTION_TAP_DANCE_FN_ADVANCED(on_each_tap_fn, layr_up_finished, layr_up_reset),
    [TD_D_OSM]  = ACTION_TAP_DANCE_FN_ADVANCED(on_each_tap_fn, osm_finished, osm_reset),
    [TD_J_OSM]  = ACTION_TAP_DANCE_FN_ADVANCED(on_each_tap_fn, osm_finished, osm_reset),
    [TD_S_OSM]   = ACTION_TAP_DANCE_FN_ADVANCED(on_each_tap_fn, osm_finished, osm_reset),
    [TD_H_CAPS]  = ACTION_TAP_DANCE_FN_ADVANCED(on_each_tap_fn, osm_finished, osm_reset),
    [TD_G_CAPS]  = ACTION_TAP_DANCE_FN_ADVANCED(on_each_tap_fn, osm_finished, osm_reset),
    [TD_V_TAB]   = ACTION_TAP_DANCE_FN_ADVANCED(on_each_tap_fn, osm_finished, osm_reset),
    [TD_Q_TILD]   = ACTION_TAP_DANCE_FN_ADVANCED(on_each_tap_fn, osm_finished, osm_reset),
    [TD_Z_GRV]    = ACTION_TAP_DANCE_FN_ADVANCED(on_each_tap_fn, osm_finished, osm_reset),
    [TD_L_NUM]    = ACTION_TAP_DANCE_FN_ADVANCED(on_each_tap_fn, osm_finished, osm_reset),
};
