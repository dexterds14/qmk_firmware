#include <stdint.h>
#include <stdbool.h>
extern void rgb_matrix_set_color(int index, uint8_t r, uint8_t g, uint8_t b);
extern void rgb_matrix_set_color_all(uint8_t r, uint8_t g, uint8_t b);
extern uint8_t biton16(uint16_t);
extern void default_layer_set(uint16_t);
extern void rgb_matrix_mode(uint8_t);
extern uint16_t layer_state, default_layer_state;
#define get_highest_layer(s) biton16(s)
#define MOD_MASK_SHIFT 0x22
#define MOD_MASK_GUI 0x88
#define RGB_GREEN 0x00,0xFF,0x00
#define RGB_BLUE 0x00,0x00,0xFF
#define RGB_ORANGE 0xFF,0x80,0x00
#define RGB_TEAL 0x00,0x80,0x80
#define RGB_RED 0xFF,0x00,0x00
#define RGB_YELLOW 0xFF,0xFF,0x00
#define RGB_WHITE 0xFF,0xFF,0xFF
#define RGB_OFF 0,0,0

bool caps_active;   /* 0x200015DC */
bool gui_active;    /* 0x200015DD */
bool shift_active;  /* 0x200015DE */

void keyboard_post_init_user(void) {
    default_layer_set(0);
    rgb_matrix_mode(16);
}

bool rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {
    for (uint8_t i = led_min; i < led_max; i++) {
        switch (get_highest_layer(layer_state | default_layer_state)) {
            case 1: rgb_matrix_set_color(i, RGB_GREEN); break;
            case 2: rgb_matrix_set_color(i, RGB_BLUE); break;
            case 3: rgb_matrix_set_color(i, RGB_ORANGE); break;
            case 4: rgb_matrix_set_color(i, RGB_TEAL); break;
            case 5: rgb_matrix_set_color(i, RGB_RED); break;
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

static void handle_oneshots(uint8_t mods) {
    if (!(mods & MOD_MASK_SHIFT) && shift_active) {
        rgb_matrix_set_color_all(RGB_OFF);
        shift_active = false;
    } else if (!(mods & MOD_MASK_GUI) && gui_active) {
        rgb_matrix_set_color_all(RGB_OFF);
        gui_active = false;
    }
    if ((mods & MOD_MASK_SHIFT) && !shift_active) {
        rgb_matrix_set_color_all(RGB_WHITE);
        shift_active = true;
    }
    if ((mods & MOD_MASK_GUI) && !gui_active) {
        rgb_matrix_set_color_all(RGB_YELLOW);
        gui_active = true;
    }
}
void oneshot_mods_changed_user(uint8_t mods) { handle_oneshots(mods); }
void oneshot_locked_mods_changed_user(uint8_t mods) { handle_oneshots(mods); }
