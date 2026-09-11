#include <stdint.h>
#include <stdbool.h>
extern bool leader_sequence_one_key(uint16_t);
extern bool leader_sequence_two_keys(uint16_t,uint16_t);
extern void register_code(uint8_t);
extern void unregister_code(uint8_t);
extern void rgb_matrix_set_color_all(uint8_t,uint8_t,uint8_t);
extern void tap_code(uint8_t);
extern void tap_code16(uint16_t);
#define KC_F 9
#define KC_A 4
#define KC_Q 0x14
#define KC_Y 0x1c
#define KC_LGUI 0xe3
#define KC_LCTL 0xe0
#define KC_P 0x13
#define KC_K 0x0e
#define KC_Z 0x1d
#define KC_ENT 0x28
/* Variant A: else-if chain (dactyl style) with the first three blocks */
void leader_end_user_elseif(void) {
    rgb_matrix_set_color_all(0, 0, 0);
    if (leader_sequence_one_key(KC_F)) {
        register_code(KC_LGUI);   register_code(KC_P);
        unregister_code(KC_LGUI); unregister_code(KC_P);
    } else if (leader_sequence_two_keys(KC_A, KC_Q)) {
        register_code(KC_LCTL);   register_code(KC_A);
        unregister_code(KC_LCTL); unregister_code(KC_A);
        register_code(KC_Z);      unregister_code(KC_Z);
    } else if (leader_sequence_one_key(KC_Y)) {
        register_code(KC_ENT);    unregister_code(KC_ENT);
    }
}
/* Variant B: same as dump but bare taps via tap_code() (non-LTO) */
void leader_end_user_tapcode(void) {
    if (leader_sequence_two_keys(KC_A, KC_Q)) {
        register_code(KC_LCTL);   register_code(KC_A);
        unregister_code(KC_LCTL); unregister_code(KC_A);
        tap_code(KC_Z); tap_code(KC_Q); tap_code(KC_ENT);
    }
}
/* Variant C: chord via tap_code16(LGUI(KC_P)) */
void leader_end_user_tc16(void) {
    if (leader_sequence_one_key(KC_F)) { tap_code16(0x0800|KC_P); tap_code16(0x0800|KC_K); }
}
