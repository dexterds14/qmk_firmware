/* Recompile check for custom_code/tapdance.c: build with
 *   "/Users/dexter/Library/Application Support/qmk/bin/arm-none-eabi-gcc" -mcpu=cortex-m4 -mthumb -Os -ffunction-sections -c tapdance_recompile_check.c -o /tmp/x.o
 *   arm-none-eabi-objdump -d /tmp/x.o
 * and compare with dump_a.bin @ 0x0800D1C4 (cur_dance), 0x0800D1EC (finished), 0x0800CDD8 (reset),
 * 0x0800CDDA (layer_oneshot_Lower), 0x0800D25C (oneshot_layer_changed_user). gcc 15.2 -Os gives
 * byte-identical cur_dance/layer_oneshot_Lower/reset and instruction-identical finished/oneshot hook (r4/r5 swapped). */
#include <stdint.h>
#include <stdbool.h>
typedef struct { uint16_t interrupting_keycode; uint8_t count; uint8_t weak_mods; uint8_t oneshot_mods; bool pressed:1; bool finished:1; bool interrupted:1; } tap_dance_state_t;
typedef enum { TD_NONE, TD_UNKNOWN, TD_SINGLE_TAP, TD_SINGLE_HOLD, TD_DOUBLE_TAP } td_state_t;
typedef struct { bool is_press_action; td_state_t state; } td_tap_t;
static td_tap_t layr_dn_tap_state = { .is_press_action = true, .state = TD_NONE };
extern void layer_clear(void); extern void layer_move(uint8_t); extern bool layer_state_is(uint8_t);
extern void layer_on(uint8_t); extern void set_oneshot_layer(uint8_t, uint8_t); extern void clear_oneshot_layer_state(uint8_t);
static uint8_t return_to_mouse = 0; static uint8_t move_to_lower = 0;
td_state_t cur_dance(tap_dance_state_t *state) {
    if (state->count == 1) { if (!state->pressed) return TD_SINGLE_TAP; else if (!state->interrupted) return TD_SINGLE_HOLD; else return TD_UNKNOWN; }
    else if (state->count == 2) return TD_DOUBLE_TAP;
    else return TD_UNKNOWN;
}
static void layer_move_toLower(void) { layer_clear(); layer_move(1); }
static void layer_oneshot_Lower(void) { layer_on(1); set_oneshot_layer(1, 3); clear_oneshot_layer_state(1); }
void layr_dn_finished(tap_dance_state_t *state, void *user_data) {
    layr_dn_tap_state.state = cur_dance(state);
    switch (layr_dn_tap_state.state) {
        case TD_SINGLE_TAP:
            if (layer_state_is(4)) { return_to_mouse = 1; layer_clear(); layer_oneshot_Lower(); }
            else { if (move_to_lower) { layer_move_toLower(); move_to_lower = 0; }
                   else if (layer_state_is(1)) { layer_clear(); layer_oneshot_Lower(); }
                   else { move_to_lower = 1; layer_oneshot_Lower(); } }
            break;
        case TD_SINGLE_HOLD: layer_clear(); layer_move(4); break;
        case TD_DOUBLE_TAP: layer_move_toLower(); break;
        default: break;
    }
}
void layr_dn_reset(tap_dance_state_t *state, void *user_data) { layr_dn_tap_state.state = TD_NONE; }
void oneshot_layer_changed_user(uint8_t layer) { if (!layer) { if (return_to_mouse) { layer_clear(); layer_move(4); return_to_mouse = 0; } } }
