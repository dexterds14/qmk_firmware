/*
 * Leader key -- reconstructed from the Keychron V10 Max flash dump
 *   /Users/dexter/code/qmk-keychron/keychron_v10max_backup/dump_a.bin
 * Evidence and per-line address citations: custom_code/leader.md
 *
 * Target: QMK 0.23.2-era Keychron fork (wireless_playground ~1011db8c8d), keymap.c.
 *
 * ---- rules.mk ----
 *   LEADER_ENABLE = yes
 *
 * ---- config.h ----
 *   #define LEADER_PER_KEY_TIMING          // process_leader calls leader_reset_timer() after every added key (0x0801192A)
 *   #define LEADER_TIMEOUT 525             // leader_sequence_timed_out(): timer_elapsed(leader_time) > 525 (movw r3,#0x20d @0x080119CA)
 *   // LEADER_NO_TIMEOUT                : NOT defined (no size==0 timer reset in leader_sequence_add @0x0801199C,
 *   //                                    no size>0 test in leader_sequence_timed_out @0x080119C0)
 *   // LEADER_KEY_STRICT_KEY_PROCESSING : NOT defined (mod-tap/layer-tap reduced to tap keycode @0x08011910..0x0801191A)
 *
 * QK_LEADER (0x7C58) sits on layer 5 at the grave position (keymap_recovered.md, layer 5 row 1).
 * Layer 5 is a one-shot layer (OSL(5) on layers 0, 1, 3 and 4) that is consumed by the QK_LEADER press
 * itself, so the sequence keys below are read from whatever layer is active underneath (normally the
 * base layer; layer 1 or 4 if TD(0) locked one of them).
 *
 * Verification: compiled in-tree with gcc 13.2.1 (the dump's compiler) both hooks are masked-identical
 * to the dump (tools/final_compile_compare.py; earlier per-target check refs/ref1011_leader_verify_gcc13.elf).
 * An else-if chain, tap_code() taps or tap_code16() chords each compile to a different instruction
 * stream (tools/leader_variants_check.c), so the source form below is the only one consistent with the bytes.
 */

#include QMK_KEYBOARD_H

/* 0x0800CDF4 (10 bytes): movs r2,#0xff ; movs r1,#0 ; mov r0,r2 ; b.w rgb_matrix_set_color_all
 * -> rgb_matrix_set_color_all(r=255, g=0, b=255).  No flag is stored anywhere. */
void leader_start_user(void) {
    rgb_matrix_set_color_all(255, 0, 255);
}

/* 0x0800CDFE..0x0800CF5F (354 bytes).
 *
 * IMPORTANT: the seven tests are INDEPENDENT `if` statements, not an `else if` chain.
 * Every failed test branches to the *next* test, and every action block falls straight
 * through into the *next* test as well (e.g. 0x0800CE10 `cbz r0,0x0800CE42` and the first
 * block's last instruction at 0x0800CE3E is immediately followed by the second test at
 * 0x0800CE42).  Consequently the two KC_F tests (0x0800CE0A and 0x0800CF0E) are BOTH
 * reachable and BOTH fire for the sequence <LEAD, F>: GUI+P, GUI+K, then GUI+'.
 *
 * Chords are typed with explicit register_code()/unregister_code() calls, releasing the
 * modifier BEFORE the key (this order cannot be produced by tap_code16(), which goes through
 * register_weak_mods()/unregister_code16() and releases the key first).
 */
void leader_end_user(void) {
    rgb_matrix_set_color_all(0, 0, 0);                        /* 0x0800CDFE..0x0800CE06 */

    if (leader_sequence_one_key(KC_F)) {                      /* 0x0800CE0A: movs r0,#9 ; bl leader_sequence_one_key */
        register_code(KC_LGUI);   register_code(KC_P);        /* 0x0800CE12..0x0800CE1A */
        unregister_code(KC_LGUI); unregister_code(KC_P);      /* 0x0800CE1E..0x0800CE26 */
        register_code(KC_LGUI);   register_code(KC_K);        /* 0x0800CE2A..0x0800CE32 */
        unregister_code(KC_LGUI); unregister_code(KC_K);      /* 0x0800CE36..0x0800CE3E */
    }
    if (leader_sequence_two_keys(KC_A, KC_Q)) {               /* 0x0800CE42: movs r1,#0x14 ; movs r0,#4 ; bl leader_sequence_two_keys */
        register_code(KC_LCTL);   register_code(KC_A);        /* 0x0800CE4C..0x0800CE54 */
        unregister_code(KC_LCTL); unregister_code(KC_A);      /* 0x0800CE58..0x0800CE60 */
        register_code(KC_Z);      unregister_code(KC_Z);      /* 0x0800CE64..0x0800CE6C */
        register_code(KC_Q);      unregister_code(KC_Q);      /* 0x0800CE70..0x0800CE78 */
        register_code(KC_ENT);    unregister_code(KC_ENT);    /* 0x0800CE7C..0x0800CE84 */
    }
    if (leader_sequence_one_key(KC_Y)) {                      /* 0x0800CE88: movs r0,#0x1c */
        register_code(KC_LCTL);   register_code(KC_X);        /* 0x0800CE90..0x0800CE98 */
        unregister_code(KC_LCTL); unregister_code(KC_X);      /* 0x0800CE9C..0x0800CEA4 */
        register_code(KC_Y);      unregister_code(KC_Y);      /* 0x0800CEA8..0x0800CEB0 */
        register_code(KC_ENT);    unregister_code(KC_ENT);    /* 0x0800CEB4..0x0800CEBC */
    }
    if (leader_sequence_two_keys(KC_LCTL, KC_I)) {            /* 0x0800CEC0: movs r1,#0xc ; movs r0,#0xe0 */
        register_code(KC_LCTL);   register_code(KC_LALT);   register_code(KC_I);    /* 0x0800CECA..0x0800CED8 */
        unregister_code(KC_LCTL); unregister_code(KC_LALT); unregister_code(KC_I);  /* 0x0800CEDC..0x0800CEEA */
    }
    if (leader_sequence_one_key(KC_J)) {                      /* 0x0800CEEE: movs r0,#0xd */
        register_code(KC_LGUI);   register_code(KC_P);        /* 0x0800CEF6..0x0800CEFE */
        unregister_code(KC_LGUI); unregister_code(KC_P);      /* 0x0800CF02..0x0800CF0A */
    }
    if (leader_sequence_one_key(KC_F)) {                      /* 0x0800CF0E: movs r0,#9  -- second KC_F test, reachable */
        register_code(KC_LGUI);   register_code(KC_QUOT);     /* 0x0800CF16..0x0800CF1E */
        unregister_code(KC_LGUI); unregister_code(KC_QUOT);   /* 0x0800CF22..0x0800CF2A */
    }
    if (leader_sequence_one_key(KC_DEL)) {                    /* 0x0800CF2E: movs r0,#0x4c */
        register_code(KC_LGUI);   register_code(KC_UP);   register_code(KC_LEFT);   /* 0x0800CF36..0x0800CF44 */
        unregister_code(KC_LGUI); unregister_code(KC_UP); unregister_code(KC_LEFT); /* 0x0800CF48..0x0800CF5A (last one is a tail call) */
    }
}
