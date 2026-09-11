#pragma once
/* Keychron V10 Max "dexter" keymap -- configuration recovered from the flash dump.
 * Evidence per line: keychron_v10max_backup/RECONSTRUCTION_SPEC.md section "config.h". */

/* Tapping */
#define TAPPING_TERM 175
#define TAPPING_TERM_PER_KEY

/* One-shot */
#define ONESHOT_TAP_TOGGLE 2

/* Leader */
#define LEADER_PER_KEY_TIMING
#define LEADER_TIMEOUT 525

/* Mouse keys (kinetic) */
#define MK_KINETIC_SPEED
#define MOUSEKEY_MOVE_DELTA 45
#define MOUSEKEY_INITIAL_SPEED 30
#define MOUSEKEY_BASE_SPEED 1500
#define MOUSEKEY_INTERVAL 40
#define MOUSEKEY_DELAY 1
#define MOUSEKEY_WHEEL_INITIAL_MOVEMENTS 64
#define MOUSEKEY_WHEEL_BASE_MOVEMENTS 32
#define MOUSEKEY_WHEEL_ACCELERATED_MOVEMENTS 50

/* RGB matrix */
#define RGB_MATRIX_DEFAULT_MODE RGB_MATRIX_TYPING_HEATMAP
