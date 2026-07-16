#include QMK_KEYBOARD_H
// #include "quantum/tap_dance/tap_dance.h"

// LEADER_EXTERNS();
// #define _QWERTY 0
// #define _LOWER 1
// #define _RAISE 2

// #define RAISE MO(_RAISE)
// #define LOWER MO(_LOWER)
#define _QWERTY 0
// #define _COLEMAK 1
// #define _DVORAK 2
#define _LOWER 1
#define _RAISE 2
// #define _ADJUST 16
#define _RAISE2 3
#define _MOUSE 4
#define _LEADR 5
// Phantom layer: never used for key lookups (fully transparent). Its bit in
// layer_state signals "caps lock active" to the slave over the layer-state
// sync, the only master->slave channel that survives LTO uncorrupted.
#define _CAPSIND 6

// Map RGB Layers to colors array entries
enum rgb_layer {
    RGB_RAISE = 0,
    RGB_RAISE2 = 7,
    RGB_LOWER = 2,
    RGB_CAPS_LOCK = 3,
    RGB_LEADER = 1,
    RGB_LEADR = 5,
    RGB_CAPS = 6,
    RGB_MOUSE = 4,
    RGB_ALT_MOD = 8,
};

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
    TD_Q_TILD
};

// Declare the functions to be used with your tap dance key(s)
// Function associated with all tap dances
td_state_t cur_dance(tap_dance_state_t *state);

// Functions associated with individual tap dances
void layr_dn_finished(tap_dance_state_t *state, void *user_data);
void layr_dn_reset(tap_dance_state_t *state, void *user_data);
// void layr_up_finished(tap_dance_state_t *state, void *user_data);
// void layr_up_reset(tap_dance_state_t *state, void *user_data);
static void layer_move_toLower(void);
static void layer_oneshot_Lower(void);
static uint8_t return_to_mouse = 0;
static uint8_t move_to_lower = 0;
#define OSM_HOLD_COUNT 2
// static uint16_t* held_osm[OSM_HOLD_COUNT] = {0}; // make this generic for mod/gui in sway as well as shift!`
// (currently unused - kept commented out for future reference)
static uint8_t shift_active = 0;
static uint8_t leader_active = 0;
static uint8_t gui_active = 0;
static uint8_t alt_active = 0;
// static uint8_t caps_active = 0;
static uint8_t alt_locked = 0;     // mod-lock Alt (triple-tap D, toggles on/off)
static bool caps_state = false;     // caps lock state (direct key + tap dance G/H)
static uint8_t lower_locked = 0;    // lower layer locked (moved to, not oneshot)

// Fast typing detection
static uint32_t last_keypress_time = 0;
static bool     fast_typing_active = false;
// static uint16_t fast_typing_keycode = KC_NO;
static bool     td_in_progress = false;


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_QWERTY] = LAYOUT_5x6(
        KC_ESC, KC_1, KC_2, KC_3, KC_4, KC_5,                         KC_6, KC_7, KC_8, KC_9, KC_0, KC_BSLS,
        KC_GRV, TD(TD_Q_TILD), KC_W, KC_E, KC_R, KC_T,                         KC_Y, KC_U, KC_I, KC_O, KC_P, KC_MINS,
        OSM(MOD_LSFT), KC_A, TD(TD_S_OSM), TD(TD_D_OSM), TD(LAYR_DOWN),   TD(TD_G_CAPS),  TD(TD_H_CAPS), TD(TD_J_OSM), TD(LAYR_UP), KC_L, KC_QUOT, OSM(MOD_RSFT),
        KC_TAB, KC_Z, KC_X, KC_C, TD(TD_V_TAB), KC_B,                         KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, KC_SCLN,
                       KC_HOME, KC_END,                                                    KC_LCTL, KC_LGUI,
                                        KC_SPC, KC_BSPC,              KC_DEL, KC_ENT,
                                        OSM(MOD_LGUI), OSL(_LEADR), KC_DEL, OSM(MOD_RGUI),
                                        OSL(_LEADR), KC_CAPS,         KC_CAPS, OSL(_LEADR)
    ),

    [_LOWER] = LAYOUT_5x6(
        KC_BSPC, LCTL(KC_1),LCTL(KC_2),KC_NO,LCTL(KC_TAB),QK_BOOT,               LALT(KC_ENT), LALT(KC_LEFT),LALT(KC_RGHT), LCTL(KC_TAB), KC_DEL, KC_PGUP,
        LALT(KC_GRV), LCTL(KC_Q),LCTL(KC_W),KC_LALT,LCTL(KC_R),LCTL(KC_T),       LCTL(KC_Y),LCTL(KC_U),LCTL(KC_I),LCTL(KC_O),LCTL(KC_P),KC_HOME,
        LALT(KC_TAB),LCTL(KC_A),LCTL(KC_S),LCTL(KC_D),LCTL(KC_F),KC_F4,          TO(_QWERTY), KC_UP, KC_LEFT, KC_DOWN, KC_RGHT, KC_END,
        LSFT(KC_TAB),LCTL(KC_Z),LCTL(KC_X),LCTL(KC_C),LCTL(KC_V),LCTL(KC_B),     LCTL(KC_N),DBL_DASH,DOT_SLS,DIR_UP,LCTL(KC_SLSH),KC_PGDN,
                                KC_HOME, KC_END,                                            KC_PGUP, KC_PGDN,
                                                KC_LCTL,  KC_LSFT,            TO(_QWERTY),     KC_ENT,
                                                LGUI(KC_UP),TD(LAYR_DOWN),            LGUI(KC_LEFT),KC_LALT,
                                                KC_SPC,OSL(_LEADR),            KC_LCTL,OSL(_LEADR)

    ),

    [_RAISE] = LAYOUT_5x6(
          KC_F12 , KC_F1 , KC_F2 , KC_F3 , KC_F4 , KC_F5 ,                        KC_F6  , KC_F7 , KC_F8 , KC_F9 ,KC_F10 ,KC_F11 ,
          KC_GRV, KC_EXLM, KC_AT,    KC_HASH, KC_DLR, KC_PERC,                   KC_CIRC, KC_AMPR, KC_ASTR, KC_LBRC, KC_RBRC, KC_PLUS,
           KC_ESC, KC_COLN, KC_EQL,   KC_UNDS, KC_PIPE, TO(_QWERTY),                  TO(_RAISE2), KC_LPRN, KC_RPRN, KC_MINS,   KC_DQUO, KC_VOLU,
           KC_PSCR,    KC_ESC,   KC_GRV, KC_LCBR,   KC_RCBR, KC_CIRC,                 KC_MUTE,    KC_NO, KC_LT,     KC_GT, KC_QUES, KC_VOLD,
                                                   KC_MPLY, KC_MSTP,                            KC_EQL ,KC_SCLN,
                                                  _______,TO(_QWERTY),        TO(_RAISE2), _______,
                                                  _______,TO(_QWERTY),            KC_MFFD, KC_MRWD,
                                                  _______,_______,            _______,_______
    ),
       [_RAISE2] = LAYOUT_5x6(
          KC_F12 , KC_F1 , KC_F2 , KC_F3 , KC_F4 , KC_F5 ,                        KC_F6  , KC_F7 , KC_F8 , KC_F9 ,KC_F10 ,KC_F11 ,
           KC_NO,     QK_BOOT, _______,     KC_NO, TO(_RAISE),    KC_NO,                    TO(_QWERTY), KC_NO,   KC_NO,    KC_NO,  QK_BOOT,   KC_NO,
           _______,KC_LEFT,KC_UP  ,KC_DOWN,KC_RGHT,TO(_QWERTY),                        KC_RPRN,KC_MPRV,KC_MPLY,KC_MNXT,_______,KC_VOLU,
           _______,_______,_______,_______,_______,KC_LPRN,                        _______,_______,_______,_______,_______,KC_VOLD,
                                                  _______,_______,            _______,_______,
                                                  _______,_______,         TO(_QWERTY),_______,
                                                  _______,TO(_RAISE),            _______,_______,
                                                  _______,_______,            _______,_______
    ),
  [_MOUSE] = LAYOUT_5x6(
    KC_F12 , KC_F1 , KC_F2 , KC_F3 , KC_F4 , KC_F5 ,                        KC_F6  , KC_F7 , KC_F8 , KC_F9 ,KC_F10 ,KC_F11 ,
    KC_NO, _______, KC_NO, KC_NO, KC_NO, KC_NO,                            KC_NO, MS_WHLU, MS_WHLD, KC_PLUS, KC_MINS, KC_NO,
    MS_BTN3, MS_WHLL, MS_WHLR, MS_BTN2, MS_BTN1, KC_NO,           TO(_QWERTY), MS_UP, MS_LEFT, MS_DOWN, MS_RGHT, KC_NO,
    KC_NO, KC_LSFT, KC_TAB, MS_WHLU, MS_WHLD, KC_NO,              KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
                                            KC_LCTL,KC_LALT,            _______ ,_______,
                                            OSL(_LEADR), KC_SPC,           TO(_QWERTY),KC_ENT,
                                            _______,TD(LAYR_DOWN),            _______,_______,
                                            _______,_______,            _______,KC_LCTL
    ),
       [_LEADR] = LAYOUT_5x6(
           KC_NO, KC_NO,KC_NO,KC_NO,LALT(KC_F4),KC_NO,                            KC_NO,KC_NO,KC_NO,KC_NO, KC_NO, KC_NO,
  EE_CLR,LCTL(KC_GRV),KC_NO,LCTL(LSFT(KC_E)),LCTL(LSFT(KC_R)),LCTL(LSFT(KC_T)),    KC_NO, KC_NO,KC_NO,LCTL(LSFT(KC_O)),LCTL(LSFT(KC_P)), KC_NO,
  KC_NO, LCTL(LSFT(KC_A)), LCTL(LSFT(KC_S)), LALT(LSFT(KC_D)),LCTL(LSFT(KC_F)),TO(_QWERTY),        KC_NO,LALT(KC_UP),LALT(KC_LEFT),LALT(KC_DOWN),LALT(KC_RIGHT), KC_NO,
  KC_NO, LCTL(LSFT(KC_Z)),KC_NO,LCTL(LSFT(KC_C)),LCTL(LSFT(KC_V)),KC_NO,          LCTL(LSFT(KC_N)), KC_NO, KC_NO, DOT_SLS, KC_NO, KC_NO,
                                                  _______,_______,            KC_EQL ,_______,
                                                  _______,QK_LEAD,            TO(_LEADR),_______,
                                                  _______,QK_LEAD,        _______,_______,
                                                  _______,QK_LEAD,            _______,_______
    ),
       [_CAPSIND] = LAYOUT_5x6(
        _______, _______, _______, _______, _______, _______,                 _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______,                 _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______,                 _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______,                 _______, _______, _______, _______, _______, _______,
                          _______, _______,                                                     _______, _______,
                                            _______, _______,                 _______, _______,
                                            _______, _______,                 _______, _______,
                                            _______, _______,                 _______, _______
    )
};

void leader_start_user(void) {
  // sequence started
  // layer_clear();
  // layer_move(_QWERTY);
  // rgblight_set_layer_state(6, false);
  leader_active = 1;
   rgblight_set_layer_state(RGB_LEADER, true);
}

void leader_end_user(void) {
    // Clean up visual state
    rgblight_set_layer_state(RGB_LEADER, false);
    leader_active = 0;

// Global search (Cmd+P, Cmd+K)
    // if (leader_sequence_one_key(KC_S))
    // {
    //     tap_code16(LGUI(KC_P));
    //     tap_code16(LGUI(KC_K));
    // }
    // Control+H
    if (leader_sequence_one_key(KC_H))
    {
        tap_code16(LCTL(KC_H));
    }
    // Copy (Ctrl+Shift+C)
    // else if (leader_sequence_one_key(KC_C))
    // {
    //     tap_code16(LCTL(LSFT(KC_C)));
    // }
    // Quit minicom (Ctrl+A, Ctrl+Z, Ctrl+Q, Enter)
    else if (leader_sequence_two_keys(KC_A, KC_Q))
    {
        tap_code16(LCTL(KC_A));
        tap_code(KC_Z);
        tap_code(KC_Q);
        tap_code(KC_ENT);
    }
    // Save and quit nano (Ctrl+X, Y, Enter)
    else if (leader_sequence_one_key(KC_Y))
    {
        tap_code16(LCTL(KC_X));
        tap_code(KC_Y);
        tap_code(KC_ENT);
    }
    // SWAY: Lock/Hibernate (Ctrl+Alt+I)
    else if (leader_sequence_two_keys(KC_LCTL, KC_I))
    {
        tap_code16(LCA(KC_I));
    }
    // SWAY: Move focus to right split (Cmd+P)
    // else if (leader_sequence_one_key(KC_J))
    // {
    //     tap_code16(LGUI(KC_P));
    // }
    // // SWAY: Move focus to left split (Cmd+')
    // else if (leader_sequence_one_key(KC_F))
    // {
    //     tap_code16(LGUI(KC_QUOT));
    // }
    // Diagonal virtual desktop move (Cmd+Up+Left)
    // else if (leader_sequence_one_key(KC_DEL))
    // {
    //     register_code(KC_LGUI);
    //     register_code(KC_UP);
    //     register_code(KC_LEFT);
    //     unregister_code(KC_LEFT);
    //     unregister_code(KC_UP);
    //     unregister_code(KC_LGUI);
    // }
}

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    // if (!is_keyboard_master()) {
        return OLED_ROTATION_270;  // flips the display vertically
    // }

    return rotation;
}

// #ifdef OLED_ENABLE
// TODO: Do we need newlines here now?
bool oled_task_user(void) {
    // Host Keyboard Layer Status
    // The phantom-layer bit is the reliable caps signal on the slave; the
    // host LED state still covers caps toggled outside this keymap's keys
    if (host_keyboard_led_state().caps_lock || layer_state_is(_CAPSIND))
    {
        oled_write_ln_P(PSTR("CAPS"), false);
        oled_write_ln_P(PSTR("CAPS"), false);
        oled_write_ln_P(PSTR("    "), false);
        oled_write_ln_P(PSTR("    "), false);
    }

    else if (shift_active)
    {
        oled_write_ln_P(PSTR("    "), false);
        oled_write_ln_P(PSTR("    "), false);
        oled_write_ln_P(PSTR("SHFT"), false);
        oled_write_ln_P(PSTR("SHFT"), false);
    }

    else if (gui_active || alt_active || alt_locked)
    {
        oled_write_ln_P(PSTR("    "), false);
        oled_write_ln_P(PSTR("    "), false);
        oled_write_ln_P(PSTR("SWAY"), false);
        oled_write_ln_P(alt_locked ? PSTR("LOCK") : PSTR("MODH"), false);
    }

    else if (leader_active)
    {
        oled_write_ln_P(PSTR("QLQL"), false);
        oled_write_ln_P(PSTR("QLQL"), false);
        oled_write_ln_P(PSTR("QLQL"), false);
        oled_write_ln_P(PSTR("QLQL"), false);
    }
    else
    {
        oled_write_ln_P(PSTR("    "), false);
        oled_write_ln_P(PSTR("    "), false);
        oled_write_ln_P(PSTR("    "), false);
        oled_write_ln_P(PSTR("    "), false);
    }


// write_chars_at_pixel_xy(1,1,"test123", false);
    oled_write_ln_P(PSTR("    "), false);


    // Mask out the phantom caps-indicator bit or it would be the highest
    // layer and land in the default (ERR!) case
    switch (get_highest_layer(layer_state & ~((layer_state_t)1 << _CAPSIND))) {
        case _QWERTY:
            oled_write_ln_P(PSTR("    "), false);
            oled_write_ln_P(PSTR("    "), false);
            oled_write_ln_P(PSTR("QMK+"), false);
            oled_write_ln_P(PSTR("    "), false);

            break;
        case _LOWER:
            oled_write_ln_P(PSTR("----"), false);
            oled_write_ln_P(PSTR("----"), false);
            oled_write_ln_P(PSTR("----"), false);
            oled_write_ln_P(lower_locked ? PSTR("LOCK") : PSTR("----"), false);

            break;
        case _RAISE:
            oled_write_ln_P(PSTR("++++"), false);
            oled_write_ln_P(PSTR("++++"), false);
            oled_write_ln_P(PSTR("++++"), false);
            oled_write_ln_P(PSTR("++++"), false);

            break;
        case _RAISE2:
            oled_write_ln_P(PSTR("2222"), false);
            oled_write_ln_P(PSTR("2222"), false);
            oled_write_ln_P(PSTR("2222"), false);
            oled_write_ln_P(PSTR("2222"), false);

            break;
        case _MOUSE:
            oled_write_ln_P(PSTR("MMMM"), false);
            oled_write_ln_P(PSTR("MMMM"), false);
            oled_write_ln_P(PSTR("MMMM"), false);
            oled_write_ln_P(PSTR("MMMM"), false);

            break;
        case _LEADR:
            oled_write_ln_P(PSTR("LLLL"), false);
             oled_write_ln_P(PSTR("LLLL"), false);
             oled_write_ln_P(PSTR("LLLL"), false);
             oled_write_ln_P(PSTR("LLLL"), false);

            break;
        default:
            // Or use the write_ln shortcut over adding '\n' to the end of your string
            // oled_write_ln_P(PSTR("    "), false);
            // oled_write_ln_P(PSTR("    "), false);
            oled_write_ln_P(PSTR("ERR!"), false);
            // oled_write_ln_P(PSTR("    "), false);
    }

    // // Host Keyboard LED Status
    // led_t led_state = host_keyboard_led_state();
    // oled_write_ln_P(led_state.num_lock ? PSTR("NUM ") : PSTR("    "), false);
    // oled_write_ln_P(led_state.caps_lock ? PSTR("CAP ") : PSTR("    "), false);
    // oled_write_ln_P(led_state.scroll_lock ? PSTR("SCR ") : PSTR("    "), false);

    return false;
}
// #endif

// RGB Lighting Section
const rgblight_segment_t PROGMEM my_capslock_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 24, HSV_WHITE}       // Light 1 LEDs, starting with LED 3
//     {7, 2, HSV_RED}
);
// Layer 4
const rgblight_segment_t PROGMEM my_layer1_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 24, HSV_BLUE}
);
// Layer 5
const rgblight_segment_t PROGMEM my_layer2_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 24, HSV_MAGENTA}
);

// Layer 3
const rgblight_segment_t PROGMEM my_layer3_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 24, HSV_GREEN}
    // {1, 1, HSV_GREEN}
);

const rgblight_segment_t PROGMEM my_layer4_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 24, HSV_RED}
    // ,
    // {0, 1, HSV_RED}
);

const rgblight_segment_t PROGMEM my_layer5_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 24, HSV_YELLOW}
);

const rgblight_segment_t PROGMEM my_layer6_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    // {0, 24, 94, 240, 65}
    {0, 24, HSV_PINK}
    // ,
    // {0, 1, HSV_MAGENTA}
);

const rgblight_segment_t PROGMEM my_layer7_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    // {0, 24, 94, 240, 65}
    {0, 24, HSV_TEAL}
    // ,
    // {0, 1, HSV_MAGENTA}
);

const rgblight_segment_t PROGMEM my_layer8_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 24, HSV_PURPLE}
);

// Now define the array of layers. Later layers take precedence
const rgblight_segment_t* const PROGMEM my_rgb_layers[] = RGBLIGHT_LAYERS_LIST(
    my_layer1_layer, //0-blue (RAISE)
    my_layer2_layer, //1-purple (RAISE2)
    my_layer3_layer, //2-green (LOWER)
    my_layer5_layer, //3-yellow (Caps Lock)
    my_layer6_layer, //4-pink (LEADER)
    my_layer4_layer, //5-red (LEADR)
    my_capslock_layer,//6-white (Shift OSM)
    my_layer7_layer, //7-teal (MOUSE)
    my_layer8_layer  //8-magenta (Alt mod-hold)
);

// forward declaration; initalizated later in the file
extern tap_dance_action_t tap_dance_actions[];
// Setup keycode storage
typedef struct {
    uint16_t keycode;
} td_osm_data_t;
static td_osm_data_t f_data = {KC_F};   // layer down on F key (unused - hardcoded in fn)
static td_osm_data_t j_data = {KC_J};
static td_osm_data_t s_data = {KC_S};   // shift OSM now on S key
static td_osm_data_t d_data = {KC_D};   // alt OSM now on D key
static td_osm_data_t g_data = {KC_G};
static td_osm_data_t h_data = {KC_H};
static td_osm_data_t v_data = {KC_V};
static td_osm_data_t q_data = {KC_Q};
static td_osm_data_t k_data = {KC_K};

void keyboard_post_init_user(void)
{
    // oled_set_rotation(OLED_ROTATION_270);
    tap_dance_actions[TD_S_OSM].user_data = &s_data;     // shift OSM on S
    tap_dance_actions[TD_J_OSM].user_data = &j_data;
    tap_dance_actions[TD_D_OSM].user_data = &d_data;     // alt OSM on D
    tap_dance_actions[LAYR_DOWN].user_data = &f_data;    // layer down on F
    tap_dance_actions[TD_G_CAPS].user_data = &g_data;
    tap_dance_actions[TD_H_CAPS].user_data = &h_data;
    tap_dance_actions[TD_V_TAB].user_data = &v_data;
    tap_dance_actions[TD_Q_TILD].user_data = &q_data;
    tap_dance_actions[LAYR_UP].user_data = &k_data;

    // Enable the LED layers
    rgblight_layers = my_rgb_layers;

    rgblight_enable();
    // rgblight_set_layer_state(RGB_RAISE, false); // Blue (RAISE)
    // rgblight_set_layer_state(RGB_RAISE2, false); // Purple (RAISE2)
    // rgblight_set_layer_state(RGB_LOWER, false); // Green (LOWER)
    // rgblight_set_layer_state(RGB_CAPS_LOCK, false); // Yellow (Caps Lock)
    // rgblight_set_layer_state(RGB_LEADER, false); // Pink (LEADER)
    // rgblight_set_layer_state(RGB_LEADR, false); // Red (LEADR)
    // rgblight_set_layer_state(RGB_CAPS, false); // White (Shift OSM)
    // rgblight_set_layer_state(RGB_MOUSE, false); // Teal (MOUSE)
    // rgblight_set_layer_state(RGB_ALT_MOD, false); // Magenta (Alt mod-hold)
    rgblight_sethsv(94, 255, 50); // Default/base color

}

// Applied locally on EACH half: the split rgblight sync is disabled (LTO
// corrupts its master->slave payloads), so both halves derive their layer
// colors from layer_state, which syncs reliably.
static void apply_rgb_layer_state(layer_state_t state)
{
    rgblight_set_layer_state(RGB_RAISE, layer_state_cmp(state, _RAISE));
    rgblight_set_layer_state(RGB_RAISE2, layer_state_cmp(state, _RAISE2));
    rgblight_set_layer_state(RGB_LOWER, layer_state_cmp(state, _LOWER));
    rgblight_set_layer_state(RGB_MOUSE, layer_state_cmp(state, _MOUSE));
    rgblight_set_layer_state(RGB_LEADR, layer_state_cmp(state, _LEADR));
    rgblight_set_layer_state(RGB_CAPS_LOCK, layer_state_cmp(state, _CAPSIND));
}

layer_state_t layer_state_set_user(layer_state_t state)
{
    // Re-assert the caps indicator bit: the layer_clear()/layer_move() calls
    // elsewhere in this keymap would otherwise silently drop it
    if (caps_state)
    {
        state |= (layer_state_t)1 << _CAPSIND;
    }
    else
    {
        state &= ~((layer_state_t)1 << _CAPSIND);
    }

    apply_rgb_layer_state(state);

    if (!layer_state_is(_LOWER))
    {
        lower_locked = 0;
    }

  return state;
}

void housekeeping_task_user(void)
{
    // The slave receives layer_state by direct assignment (no
    // layer_state_set_user callback), so poll for changes and apply the RGB
    // layer colors locally.
    if (!is_keyboard_master())
    {
        static layer_state_t last_state = 0;
        if (layer_state != last_state)
        {
            last_state = layer_state;
            apply_rgb_layer_state(layer_state);
        }
    }
}

void handle_oneshots(uint8_t mods)
{
    if (mods & MOD_MASK_SHIFT && !shift_active)
    {
        rgblight_set_layer_state(RGB_CAPS, true);
        shift_active = 1;
        return;
    }
    else if ((mods & (MOD_MASK_ALT | MOD_MASK_GUI)) && !(alt_active || gui_active))
    {
      rgblight_set_layer_state(RGB_ALT_MOD, true);
      alt_active = mods & MOD_MASK_ALT ? 1 : 0;
      gui_active = mods & MOD_MASK_GUI ? 1 : 0;
      return;
    }
    else if (!(mods & MOD_MASK_SHIFT) && shift_active)
    {
        rgblight_set_layer_state(RGB_CAPS, false);
        shift_active = 0;
        return;
    }
    else if (!(mods & (MOD_MASK_ALT | MOD_MASK_GUI)) && !alt_locked)
    {
      rgblight_set_layer_state(RGB_ALT_MOD, false);
      alt_active = 0;
      gui_active = 0;
      return;
    }
}

void oneshot_mods_changed_user(uint8_t mods)
{
    handle_oneshots(mods);

    // rgblight_set_layer_state(3, true);
}

void oneshot_locked_mods_changed_user(uint8_t mods)
{

      handle_oneshots(mods);

        // clear_oneshot_mods();
        // clear_oneshot_locked_mods();
        // unregister_mods(mods);
    // }

    // rgblight_set_layer_state(3, true);
}

// uint16_t* find_osm_slot(uint16_t keycode)
// {
//   uint16_t* index = held_osm[0];
//   uint16_t* blank = NULL;
//   for (int i= 0; i < OSM_HOLD_COUNT; i++)
//   {
//     if (index == NULL)
//     {
//       blank = index;
//     }
//     else if (*(index) == keycode)
//     {
//       return index;
//     }

//     index += sizeof(uint16_t);
//   }

//   return blank; // return empty slot if no match
// }

// bool check_unlock_osm(uint16_t keycode/*, bool keycode_is_osm, keyrecord_t *record*/)
// {
//     uint16_t* slot = find_osm_slot(keycode);
//     if (slot == NULL)
//     {
//       slot = &keycode; // store the new keycode

//       return true;
//     }

//     // Turn off the shift-lock if we are pressing a shift key when shift is already locked
//     if (get_mods() && (keycode != *(slot)))
//     {
//       rgblight_set_layer_state(6, false);
//       rgblight_set_layer_state(1, false);

//       clear_oneshot_mods();
//       clear_oneshot_locked_mods();
//       unregister_mods(get_oneshot_mods());

//       // clear the 'holds' array
//       for (int i = 0; i < OSM_HOLD_COUNT; i++)
//       {
//         held_osm[i] = NULL;
//       }

//       shift_active = 0;
//       gui_active = 0;

//       return false;
//     }

//     return false;
// }

bool is_td_key(uint16_t keycode)
{
    // if ((get_mods() & (MOD_MASK_CG | MOD_BIT_LALT)) != 0)
    // {
    //     return false;
    // }

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
            return true;
    }

    // unwrap mod-tap/layer-tap and check the tap keycode
    // switch (get_tap_keycode(keycode))
    // {
    //     case KC_SPC:
    //     case KC_A ... KC_Z:
    //     case KC_DOT:
    //     case KC_COMM:
    //     case KC_SCLN:
    //     case KC_SLSH:
    //         return true;
    // }

    return false;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record)
{

    // if (get_mods() & MOD_MASK_SHIFT)
    // {
    //     rgblight_set_layer_state(3, true);
    // }

    // else
    // {
    //     rgblight_set_layer_state(3, false);
    // }
    // }

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

    // if (get_oneshot_mods() & MOD_MASK_SHIFT)
    // {
    // Fast typing detection
    if (record->event.pressed /* && is_flow_tap_key(keycode) */)
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
            // else
            // {
            //     fast_typing_keycode = keycode;
            // }
        }

    }

    // Only run the following logic on 'donwstrokes' of key presses
    if (record->event.pressed)
    {
    //   bool is_osm = ( (keycode == OSM(MOD_LSFT)) || (keycode == OSM(MOD_RSFT)) || (keycode == OSM(MOD_LGUI)) || (keycode == OSM(MOD_RGUI)) );
    //   if (is_osm)
    //   {
    //     return check_unlock_osm(keycode);
    //   }

      // is_osm = (keycode == OSM(MOD_LGUI));
      // if (is_osm)
      // {
      //   return check_unlock_osm(keycode, is_osm);
      // }

      // else if (keycode == OSM(MOD_RSFT) && !held_shift)
      // {
      //   held_shift = OSM(MOD_RSFT);
      // }
      // else
      // {
      //   held_shift = 0;
      // }
      // uint16_t mods, locked_mods = 0;
      // rgblight_set_layer_state(3, false);
      // mods = get_oneshot_mods();
      // locked_mods = get_oneshot_locked_mods();
      // uint16_t shift = MOD_LSFT | MOD_RSFT;



      // else if (!mods && !locked_mods)
      // {
      //   held_shift = 0;
      // }
        if (keycode == KC_CAPS)
        {
            caps_state = !caps_state;
            // Raising/lowering the phantom layer lights the yellow RGB layer
            // on both halves via layer_state_set_user / the slave poller
            if (caps_state) layer_on(_CAPSIND);
            else layer_off(_CAPSIND);
            return true;
        }

        // }

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
        // state->interrupted = false;
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
            return TD_UNKNOWN;
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
  if (layer == 1) {
    // do something?
  }
  // is the oneshot finished?
  if (!layer)
  {
    if (return_to_mouse)
    {
      layer_clear();
      layer_move(_MOUSE);
      return_to_mouse = 0;
    }
    // if (move_to_lower)
    // {
    //   // layer_move_toLower();
    //   // move_to_lower = 0;
    // }
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
            // if (state->interrupted)
            // {
            //     register_code(KC_K);
            // }
            break;
        default:
            break;
    }
}

void layr_up_reset(tap_dance_state_t *state, void *user_data)
{
    // if (layr_up_tap_state.state == TD_SINGLE_TAP ||
    //     (layr_up_tap_state.state == TD_UNKNOWN && state->interrupted))
    // {
    //     unregister_code(KC_K);
    // }
    layr_up_tap_state.state = TD_NONE;

    td_in_progress = false;
}

static void layer_move_toLower(void)
{
  layer_clear();
  layer_move(_LOWER);
  lower_locked = 1;
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
              // layer_on(_MOUSE);
            }
            // if we are already on _LOWER now got to just a oneshot
            // else if (layer_state_is(_LOWER))
            // {
            //   // move_to_lower = 1;
            //   layer_clear();
            //   layer_oneshot_Lower();
            // }
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
            // layr_dn_tap_state.state = TD_NONE;
            break;
        case TD_SINGLE_HOLD:
            // if (state->keycode == LAYR_DOWN)
            // {
                layer_clear();
                layer_move(_MOUSE);
            // }
            break;
        case TD_TRIPLE_TAP:
            layer_move_toLower();
            break;
        case TD_UNKNOWN:
            // if (state->interrupted)
            // {
            //     register_code(KC_F);
            // }
            break;
        default:
            break;
    }
}

void layr_dn_reset(tap_dance_state_t *state, void *user_data) {
    // If the key was held down and now is released then switch off the layer
    // if (layr_dn_tap_state.state == TD_SINGLE_HOLD) {
    //     layer_off(_MY_LAYER);
    // }
    // if (layr_dn_tap_state.state == TD_SINGLE_TAP ||
    //     (layr_dn_tap_state.state == TD_UNKNOWN && state->interrupted))
    // {
    //     unregister_code(KC_F);
    // }
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
                    rgblight_set_layer_state(RGB_ALT_MOD, true);
                    alt_active = 1;
                }
                else
                {
                    unregister_mods(MOD_BIT(KC_LALT));
                    set_oneshot_locked_mods(get_oneshot_locked_mods() & ~MOD_LALT);
                    rgblight_set_layer_state(RGB_ALT_MOD, false);
                    alt_active = 0;
                }
            }
            break;
        case TD_UNKNOWN:
            // if (state->interrupted)
            // {
            //     register_code(data->keycode);
            // }
            break;
        default:
            break;
    }
}

void osm_reset(tap_dance_state_t *state, void *user_data)
{
    // td_osm_data_t *data = (td_osm_data_t *)user_data;
    // if (data == NULL) return;
    // if (osm_tap_state.state == TD_SINGLE_TAP ||
    //     (osm_tap_state.state == TD_UNKNOWN && state->interrupted))
    // {
    //     unregister_code(data->keycode);
    // }
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
};
