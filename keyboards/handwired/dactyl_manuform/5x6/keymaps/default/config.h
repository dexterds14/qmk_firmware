/*
Copyright 2012 Jun Wako <wakojun@gmail.com>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#define MASTER_LEFT
//#define MASTER_RIGHT

#define SPLIT_USB_DETECT
#define SPLIT_USB_TIMEOUT 2500

// #define AUDIO_PIN B7
// #define B7_AUDIO

#define NO_ACTION_MACRO
#define NO_ACTION_FUNCTION

// 6 real layers + 3 phantom indicator layers (caps/alt-lock/lower-lock, see
// keymap.c) = 9 bits of layer state, so 16-bit (still smaller than the
// 32-bit default)
#define LAYER_STATE_16BIT

#ifndef NO_DEBUG
#define NO_DEBUG
#endif // !NO_DEBUG
#if !defined(NO_PRINT) && !defined(CONSOLE_ENABLE)
#define NO_PRINT
#endif // !NO_PRINT

// #define RGBLIGHT_ENABLE  // or RGB_MATRIX_ENABLE if your board supports it
#define RGBLIGHT_DEFAULT_MODE 1 // 1 = Static Light
#undef RGBLIGHT_ANIMATION
#define RGBLIGHT_LAYERS
// #undef RGBLED_NUM
// #define RGBLED_NUM	24
// #define DRIVER_LED_TOTAL 24
// RGBLED_SPLIT intentionally NOT defined: it would enable the split rgblight
// sync, whose master->slave payloads corrupt under LTO. Instead each half
// renders the full LED buffer locally and derives layer colors from the
// clean layer-state sync (see apply_rgb_layer_state in keymap.c).
// #define RGBLED_SPLIT {12, 12}
#define RGBLIGHT_MAX_LAYERS 9

// #define NO_MUSIC_MODE
// #define NO_MUSIC_MODE
#undef LOCKING_SUPPORT_ENABLE
#undef LOCKING_RESYNC_ENABLE
// #define NO_ACTION_MACRO
// #define NO_ACTION_FUNCTION
// #define NO_ACTION_ONESHOT
// #define EXTRA_SHORT_COMBOS

#define TAPPING_TERM 300
// #define QUICK_TAP_TERM 145
#define FLOW_TAP_TERM 225
// Fast typing threshold (ms)
#define FAST_TYPING_THRESHOLD FLOW_TAP_TERM
// #define PERMISSIVE_HOLD
// #define HOLD_ON_OTHER_KEY_PRESS
// #define TAPPING_TERM_PER_KEY

// #define OLED_ENABLE
#define OLED_BRIGHTNESS 254
// Trimmed font (space..'Z' only) to save ~1KB of flash
#define OLED_FONT_H "keyboards/handwired/dactyl_manuform/5x6/keymaps/default/glcdfont_custom.c"
#define OLED_FONT_START 32
#define OLED_FONT_END 90
// #define OLED_DISPLAY_128X64
#define OLED_DISPLAY_HEIGHT 32
// #define OLED_FONT_WIDTH 6
// #define OLED_FONT_HEIGHT 8
// #define OLED_FONT_START 32
// #define OLED_FONT_END 126
#define OLED_UPDATE_INTERVAL 50
#define OLED_TIMEOUT 300000

#define SPLIT_LAYER_STATE_ENABLE
#define SPLIT_LED_STATE_ENABLE
#define SPLIT_MODS_ENABLE
#define SPLIT_OLED_ENABLE
// #define SPLIT_TRANSPORT_MIRROR
// #define SPLIT_LAYER_TRANSPORT_MIRROR
// #define SPLIT_WPM_ENABLE
// LTO + soft serial at speed 5: keys and layer-state sync are reliable, but
// mods/LED-state/rgblight master->slave payloads corrupt (value-dependent
// byte desync). Timing recalibration via READ_WRITE_*_ADJUST was attempted
// and exhausted (2026-07, see git history): every value that would fix the
// payload reads kills the link first (windows don't overlap). Sidestep:
// rgblight split sync disabled and the slave derives RGB from layer state
// (see keymap.c). Full-revert fallback: LTO off + speed 0 (27510-byte build).
#define SELECT_SOFT_SERIAL_SPEED 5
#define FORCED_SYNC_THROTTLE_MS 50
#define SPLIT_MAX_CONNECTION_ERRORS 50
#define SERIAL_USART_TIMEOUT 10    // USART driver timeout. default 20

// Enable Leader Key and Per-Key Timing for Sequence Timeouts
// #define LEADER_ENABLE
#define LEADER_PER_KEY_TIMING
#define LEADER_TIMEOUT 600

// Oneshot configurations
#define ONESHOT_TAP_TOGGLE 2  /* Tapping this number of times holds the key until tapped once again. */
// #define ONESHOT_TIMEOUT 1000 /* Time (in ms) before the one shot key is released */

// Mouse Keys
// #define MOUSEKEY_ENABLE
#define MK_KINETIC_SPEED
#define MOUSEKEY_MOVE_DELTA 45
#define MOUSEKEY_INITIAL_SPEED 30
#define MOUSEKEY_BASE_SPEED 1500
#undef  MOUSEKEY_INTERVAL
#define MOUSEKEY_INTERVAL 40
#undef  MOUSEKEY_DELAY
#define MOUSEKEY_DELAY 1
// Wheel rates are in scroll events per second (kinetic mode); reduced from
// the original 32/64/50 to ~1/3 (50% cut, then another 33%) to slow scrolling
#define MOUSEKEY_WHEEL_INITIAL_MOVEMENTS 5
#define MOUSEKEY_WHEEL_BASE_MOVEMENTS 192
// This value is only used by the MS_ACL2 key!
// #define MOUSEKEY_WHEEL_ACCELERATED_MOVEMENTS 128

// #ifdef AUDIO_ENABLE
//   #define STARTUP_SONG SONG(CAMPANELLA)
// //   #define AUDIO_INIT_DELAY
// //   #define USB_SUSPEND_WAKEUP_DELAY 200
// //   #undef TEMPO_DEFAULT
// // #define TEMPO_DEFAULT 10
// // #define AUDIO_ENABLE_TONE_MULTIPLEXING
// // #define AUDIO_TONE_MULTIPLEXING_RATE_DEFAULT 10
// #endif

//#define EE_HANDS
