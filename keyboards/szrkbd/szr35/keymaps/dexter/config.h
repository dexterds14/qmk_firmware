// Copyright 2026 dexterds14
// SPDX-License-Identifier: GPL-2.0-or-later
//
// Port of the szrkbd/bcorne dexter keymap's configuration. Split transport,
// WS2812 timing and the brightness cap (50, as stock) are keyboard-level.

#pragma once

// 8 real layers + 3 phantom indicator layers (caps/alt-lock/lower-lock, see
// keymap.c) = 11 bits of layer state, so 16-bit (smaller than the 32-bit
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
// all three must be synced to the slave. Layer state is already synced at
// keyboard level (keyboard.json split.transport.sync.layer_state).
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

// Resting look: RAINDROPS from a dark/royal blue base. The effect starts as a
// solid colour and keeps re-colouring one random key at a time to the base
// hue, base-32 or base-64 (so blue drifting through azure to sea green);
// higher speed = more keys changed per second. These are compiled defaults:
// they only apply on a fresh EEPROM (EE_CLR is on RAISE2).
#undef RGB_MATRIX_DEFAULT_MODE
#define RGB_MATRIX_DEFAULT_MODE RGB_MATRIX_RAINDROPS
#undef RGB_MATRIX_DEFAULT_HUE
#define RGB_MATRIX_DEFAULT_HUE 165
#undef RGB_MATRIX_DEFAULT_SAT
#define RGB_MATRIX_DEFAULT_SAT 255
#undef RGB_MATRIX_DEFAULT_VAL
#define RGB_MATRIX_DEFAULT_VAL RGB_MATRIX_MAXIMUM_BRIGHTNESS
#undef RGB_MATRIX_DEFAULT_SPD
#define RGB_MATRIX_DEFAULT_SPD 230
#define RGB_MATRIX_SLEEP
