// Copyright 2026 dexterds14
// SPDX-License-Identifier: GPL-2.0-or-later
//
// Port of the dactyl_manuform/5x6 default keymap's configuration, minus the
// dactyl-specific parts (OLED, rgblight, AVR soft-serial timing workarounds
// -- this board's USART split transport is configured at keyboard level).

#pragma once

// 6 real layers + 3 phantom indicator layers (caps/alt-lock/lower-lock, see
// keymap.c) = 9 bits of layer state, so 16-bit (smaller than the 32-bit
// default)
#define LAYER_STATE_16BIT

#define TAPPING_TERM 280
#define FLOW_TAP_TERM 240
// Fast typing threshold (ms)
#define FAST_TYPING_THRESHOLD FLOW_TAP_TERM

// Leader key
#define LEADER_PER_KEY_TIMING
#define LEADER_TIMEOUT 600

// Tapping an OSM this many times holds the mod until tapped once again
#define ONESHOT_TAP_TOGGLE 2

// The RGB indicator (keymap.c) runs per-frame on both halves and derives
// everything from layer state, mods/oneshot mods, and the host LED state --
// all three must be synced to the slave.
#define SPLIT_LAYER_STATE_ENABLE
#define SPLIT_MODS_ENABLE
#define SPLIT_LED_STATE_ENABLE

// Mouse keys (kinetic mode, tuned on the dactyl)
#define MK_KINETIC_SPEED
#define MOUSEKEY_MOVE_DELTA 45
#define MOUSEKEY_INITIAL_SPEED 30
#define MOUSEKEY_BASE_SPEED 1500
#define MOUSEKEY_INTERVAL 40
#define MOUSEKEY_DELAY 1
// Wheel rates are in scroll events per second (kinetic mode); reduced from
// the original 32/64/50 to ~1/3 (50% cut, then another 33%) to slow scrolling
#define MOUSEKEY_WHEEL_INITIAL_MOVEMENTS 5
#define MOUSEKEY_WHEEL_BASE_MOVEMENTS 192

// Resting look: the dactyl's dim green (rgblight_sethsv(94, 255, 50)).
// Animations remain selectable at runtime via RAISE2's RM_* keys/knobs.
#define RGB_MATRIX_DEFAULT_MODE RGB_MATRIX_SOLID_COLOR
#define RGB_MATRIX_DEFAULT_HUE 94
#define RGB_MATRIX_DEFAULT_SAT 255
#define RGB_MATRIX_DEFAULT_VAL 50
// The layer-indicator overlays paint all 58 WS2812s at full value; cap the
// brightness so worst case (white) stays within USB power budget.
#define RGB_MATRIX_MAXIMUM_BRIGHTNESS 150
#define RGB_MATRIX_SLEEP
