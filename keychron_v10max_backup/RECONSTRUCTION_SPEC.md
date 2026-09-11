# Keychron V10 Max "dexter" keymap -- reconstruction spec

Final, verified content proposed for `keyboards/keychron/v10_max/ansi_encoder/keymaps/dexter/` in the Keychron
`wireless_playground` fork. Everything here was recovered from `dump_a.bin` (the flash image of the lost custom
firmware, built 2024-07-09-13:57:36). Evidence for every statement is in `ANALYSIS.md` (addresses) and in the
per-target reports `custom_code/*.md`; this file is the deliverable.

Confidence tags: **[V]** verified from dump instructions/bytes (and reproduced by compiling), **[L]** likely
(one inference), **[U]** undecidable from the binary.

## 0. Verification status

The three files below (identical copies in `reconstructed_keymap/`) were compiled in-tree against the pinned fork
`/Users/dexter/code/qmk-keychron-ref` (commit 1011db8c8d, QMK 0.23.2 era) with the dump's compiler generation,
xPack `arm-none-eabi-gcc 13.2.1 20231009`, using QMK's userspace overlay so the fork tree was not touched:

```
X=~/.local/share/xpack-arm-none-eabi-gcc-13.2.1/xpack-arm-none-eabi-gcc-13.2.1-1.1/bin
cd /Users/dexter/code/qmk-keychron-ref
PATH="$X:$PATH" make keychron/v10_max/ansi_encoder:dexter:elf \
    QMK_USERSPACE=<overlay with keyboards/keychron/v10_max/ansi_encoder/keymaps/dexter/> \
    BUILD_DIR=<scratch>/build TOOLCHAIN=$X/arm-none-eabi- -j8
uv run --with pyelftools python3 tools/final_compile_compare.py <scratch>/build/keychron_v10_max_ansi_encoder_dexter.elf
```

Result (`tools/final_compile_compare.py`, artefacts `refs/ref1011_dexter_final_gcc13.{elf,map,bin}`): **ALL IDENTICAL**

| check | result |
|---|---|
| all 17 functions of the user keymap TU (tap dance, leader, boot, indicator, one-shot hooks, OSM helpers, `process_record_user`, keymap introspection) | masked-identical to the dump: same instructions, register allocation and branch offsets; only BL/B.W displacements and literal-pool addresses differ |
| `keymaps[]` 1296 B, `encoder_map[]` 24 B | byte-identical to dump 0x080169B8 / 0x080169A0 |
| `tap_dance_actions[]` init image | same 28-byte shape (NULL / pointer / NULL / NULL) |
| .bss order of the six user statics | identical offsets (caps 0, gui 1, shift 2, held_osm 4, move_to_lower 12, return_to_mouse 13) |
| 41 config-bearing core functions (tapping, one-shot, leader, mousekey, RGB default, feature chain, debounce, bootmagic) | masked-identical -> config.h and rules.mk reproduce the dump's configuration |
| whole-image sweep (908 rebuild functions) | only newlib (different newlib build), `wireless_send_nkro` (fork commit, see section 5), two jump-table functions (`wear_leveling_*`, `mousekey_off`: absolute table words) lack a masked-identical twin |

The build is clean under QMK's `-Werror`.

## 1. Verifier issues and their resolution

Six reconstruction targets were reviewed by three independent verifiers each (control-flow, constants,
compile-and-compare lens). No target was refuted. One issue was rated major; everything else minor. All are resolved
in the files below and in the updated `custom_code/*` reports.

| # | target | severity | issue | resolution (re-checked against the dump) |
|---|---|---|---|---|
| 1 | rawhid_misc | **major** | RULES list omitted `SPACE_CADET_ENABLE = no`, `MAGIC_ENABLE = no`, `GRAVE_ESC_ENABLE = no` (default-on in the fork) | Confirmed: `process_record_quantum` 0x0800D3B6 calls only 0x0800C6E8 process_record_kb, 0x08012040 process_tap_dance, 0x080118F4 process_leader, 0x08011530 process_rgb (sites 0x0800D3D8/E2/EC/F6), then the QK_BOOT/REBOOT/CLEAR_EEPROM/OS_* switch; a build with the three features on adds three calls and a fifth `get_tapping_term` caller. **rules.mk carries the three `= no` lines** (they were already in `config_features.txt`; `rawhid_misc.c` updated). |
| 2 | config_features | minor | ONESHOT_TAP_TOGGLE evidence cited 0x0800D918/D924/D978/D984 (those are the ACT_LAYER bit-op dispatch `ubfx r4,#10,#2`) | Confirmed and corrected: MODS_ONESHOT press path is 0x0800D816 `cmp r8,#0`, 0x0800D824 `cmp r8,#1` -> add_oneshot_mods 0x0800E3EC, 0x0800D832 `cmp r8,#2` -> register_mods 0x0800D672 + del_oneshot_mods 0x0800E408 + add_oneshot_locked_mods 0x0800E394; release 0x0800D84C / 0x0800D866. Value 2 unchanged. Also: QMK 0.23 has no default for this macro, so the blocks' presence alone proves the define (upgraded to [V]). |
| 3 | config_features | minor | TAPPING_TOGGLE evidence cited 0x0800D9D2 (the tbb range check) | Corrected to 0x0800D9E2 `cmp.w r8,#4` / 0x0800D9F4 `cmp.w r8,#5` (OP_TAP_TOGGLE) and 0x0800D878 / 0x0800D880 (MODS_TAP_TOGGLE). Value 5 = default unchanged. |
| 4 | config_features | minor | `MOUSEKEY_DELAY 1`, `MOUSEKEY_WHEEL_BASE_MOVEMENTS 32` tagged verified although undecidable (any 0..9 / equals default) | Tags corrected to [L]; lines kept (dactyl values). |
| 5 | config_features | minor | `wireless_send_nkro` 0x0800A33C differs from the 1011db8c8d build | Confirmed: the dump has the extra `ldr r3,[r5,#20]; adds r0,r4,#1; blx r3` = `wireless_transport.send_nkro(&report->mods)` after `report_buffer_enqueue`; fork commit 0c05eef6cd (2024-06-22) removed exactly that line. **Source tree = fork commit 8e390f92a2 (2024-06-18)**, one commit before the pinned reference; nothing V10-Max-related besides wireless.c changed in between. Recorded in section 5. |
| 6 | rgb_hooks | minor | flags declared `bool`; switch cases 1..5; declaration order caps,gui,shift | Compile-compare with gcc 13.2.1 settled all three: flags are `uint8_t` (bool gives cbnz/cmp instead of the dump's `orrs`), the switch lists cases in the order 2,3,1,4,5 (reproduces tbb table `18 03 14 1B 1E`), and GCC emits statics in reverse definition order so the source order is `return_to_mouse, move_to_lower, held_osm[], shift_active, gui_active, caps_active`. Applied. |
| 7 | rgb_hooks / process_record_user | minor | "ICF-folded" hook thunks; `rgb_matrix_set_color_all` called "a thunk to snled27351_set_color_all"; hook argument semantics | Wording fixed: the two `b.w` thunks are GCC sibling calls into one static helper; 0x0800FEE4 is `rgb_matrix_driver.set_color_all(...)` through the const driver struct 0x08016F9C; `add_oneshot_mods()` passes only the newly added mods to the hook (documented in code comments). |
| 8 | rgb_hooks | minor | DIP-switch blue-board remark; "rewrites EEPROM if it differed"; `dip_switch_update_user` citation; RGB_MATRIX_DEFAULT_MODE file placement | Reworded (runtime toggle only; `rgb_matrix_mode()` is a no-op while RGB is off and always flags a flush; 0x0800CCF0 is the fork's factory_test.c hook). The define's *value* is [V], its *file* (keymap config.h vs keymap.json) is [L]. |
| 9 | tapdance | minor | "instruction-for-instruction" overstated for the gcc 15 check; `get_tapping_term` weak-vs-override left open; second-tap gloss; keychron_common gate | Now verified with gcc 13.2.1 in-tree (masked-identical). `get_tapping_term` 0x0800DEFC is the weak default (it sits in the action_tapping.o cluster between `waiting_buffer_typed.isra.0` 0x0800DEB8 and `waiting_buffer_scan_tap` 0x0800DF00) -> keymap.c must NOT define it. Gloss and gate caveat added to comments. QUICK_TAP_TERM witness (`cmp r7,#174` @0x0800E1B4) added. |
| 10 | leader | minor | OSL(5) comment; `register_code` "140 B vs ref 0x90" | Comment corrected (OSL(5) on layers 0/1/3/4, one-shot consumed by the leader press); 0x0800D570 is 144 B incl. literal pool = ref 0x90, identical. register_code-vs-tap_code upgraded to [V] (variant compiles differ). |
| 11 | rawhid_misc | minor | endpoint field offsets; `rtc_timer_init` naming; 0x60 gate in lkbt51_dfu_rx; 0x08012450 caller | All corrected in `rawhid_misc.md` (config sub-struct at +0x70 = flash 0x08017A98; `rtc_timer_init` 0x0800C488 thunk -> `rtc_timer_clear` 0x0800C46C; `(data[5]&0xF0)==0x60`; main -> protocol_setup 0x08012C68 -> 0x08012450 -> usb_device_state_init 0x0801243C). |
| 12 | process_record_user | minor | "ghidra xrefs" citation for held_osm | Replaced by the literal scan (0x200015E0 only at 0x0800D0B0/0x0800D0F8; 0x200015E4 nowhere). |

One earlier internal report (`ANALYSIS_functions.md` section 3) describes `leader_end_user` as an if/else-if chain with the
second `KC_F` block unreachable. That is superseded: the instruction stream (every `cbz` targets the next test, no `b END`
after any block, single epilogue at 0x0800CF5E) and the compile-compare prove **seven independent `if`s**, so `<LEAD, F>`
fires GUI+P, GUI+K and GUI+'.

## 2. keymap.c

```c
/* Keychron V10 Max ANSI knob (keychron/v10_max/ansi_encoder) -- "dexter" keymap
 *
 * Reconstructed from a flash dump of the lost custom firmware (built 2024-07-09-13:57:36 from
 * Keychron's wireless_playground fork at commit 8e390f92a2, QMK 0.23.2 era, arm-none-eabi-gcc 13.2.1).
 * Every table entry and every behaviour below was recovered from the binary; the evidence trail is in
 * keychron_v10max_backup/RECONSTRUCTION_SPEC.md (per-line confidence) and ANALYSIS.md (addresses).
 * Identifier names follow the author's sibling dactyl_manuform keymap; only values and behaviour are
 * provable from the dump.
 *
 * SPDX-License-Identifier: GPL-2.0-or-later
 */
#include QMK_KEYBOARD_H
#include "keychron_common.h"

enum layers {
    _QWERTY = 0, // base                                    (no indicator colour)
    _LOWER,      // Ctrl-chords / arrows; TD(0) one-shot or lock  (green)
    _RAISE,      // symbols / F-keys, OSL(_RAISE) on right Cmd     (blue)
    _RAISE2,     // Keychron Fn content: RGB, BT hosts, QK_BOOT   (orange)
    _MOUSE,      // mouse keys; TD(0) hold                        (teal)
    _LEADR,      // leader key + Ctrl/Shift chords; OSL(_LEADR)   (red)
};

/* SAFE_RANGE == QK_USER_0 == 0x7E40 in this fork. Only these two custom keycodes exist in the image. */
enum custom_keycodes {
    DOT_SLS = SAFE_RANGE, // 0x7E40: types "./"
    DIR_UP,               // 0x7E41: types "../"
};

enum tap_dance_keys {
    LAYR_DOWN, // TD(0) = 0x5700, the Fn key; the only tap dance in the image
};

/* Values as compiled in cur_dance (dump 0x0800D1C4): 2 / 3 / 4 / 1. There is no TD_TRIPLE_TAP. */
typedef enum {
    TD_NONE,        // 0
    TD_UNKNOWN,     // 1
    TD_SINGLE_TAP,  // 2
    TD_SINGLE_HOLD, // 3
    TD_DOUBLE_TAP,  // 4
} td_state_t;

typedef struct {
    bool       is_press_action;
    td_state_t state;
} td_tap_t;

/* ---- static state --------------------------------------------------------------------------
 * Declared in this order on purpose: GCC emits file-scope statics in reverse definition order, which
 * reproduces the dump's .bss layout 0x200015DC caps_active, DD gui_active, DE shift_active,
 * E0/E4 held_osm[2], E8 move_to_lower, E9 return_to_mouse.
 */
static uint8_t return_to_mouse = 0; // TD(0) tapped on _MOUSE: go back to _MOUSE when the one-shot _LOWER ends
static uint8_t move_to_lower   = 0; // TD(0) tapped once: a second tap with no other key in between locks _LOWER
#define OSM_HOLD_COUNT 2
static uint16_t *held_osm[OSM_HOLD_COUNT] = {0}; // never written non-NULL anywhere in the image (see check_unlock_osm)
static uint8_t shift_active = 0; // a one-shot Shift is showing -> board white
static uint8_t gui_active   = 0; // a one-shot GUI is showing   -> board yellow
static uint8_t caps_active  = 0; // this keyboard toggled caps lock on -> board white

/* Write-only in this firmware: GCC removes every store to it, which is why layr_dn_reset compiles to a
 * bare `bx lr` and layr_dn_finished never stores cur_dance()'s result. Kept for fidelity with the source. */
static td_tap_t layr_dn_tap_state = {.is_press_action = true, .state = TD_NONE};

/* ---- keymap ---------------------------------------------------------------------------------
 * Byte-identical to the dump's keymaps[] at flash 0x080169B8 (6 x 6 x 18 u16, verified by round-trip).
 */
// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_QWERTY] = LAYOUT_ansi_89(
        KC_AUDIO_MUTE, KC_ESCAPE, KC_BRIGHTNESS_DOWN, KC_BRIGHTNESS_UP, KC_MCTRL, KC_LNPAD, RGB_VAD, RGB_VAI, KC_MEDIA_PREV_TRACK, KC_MEDIA_PLAY_PAUSE, KC_MEDIA_NEXT_TRACK, KC_AUDIO_MUTE, KC_AUDIO_VOL_DOWN, KC_AUDIO_VOL_UP, KC_INSERT, KC_DELETE,
        KC_BACKSPACE, OSL(_LEADR), KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, LSFT(KC_EQUAL), KC_EQUAL, KC_BACKSPACE, KC_PAGE_UP,
        MC_2, KC_GRAVE, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_MINUS, KC_RIGHT_BRACKET, KC_BACKSLASH, KC_PAGE_DOWN,
        MC_3, OSM(MOD_LSFT), KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, KC_QUOTE, OSM(MOD_RSFT), KC_SEMICOLON, KC_HOME,
        MC_4, KC_TAB, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_BACKSPACE, KC_N, KC_M, KC_COMMA, KC_DOT, KC_SLASH, KC_RIGHT_SHIFT, KC_UP,
        MC_5, KC_LEFT_CTRL, KC_CAPS_LOCK, OSM(MOD_LGUI), KC_SPACE, TD(LAYR_DOWN), KC_ENTER, OSL(_RAISE), KC_LEFT, KC_DOWN, KC_RIGHT
    ),
    [_LOWER]  = LAYOUT_ansi_89(
        RGB_TOG, KC_BACKSPACE, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, KC_F11, KC_F12, _______, _______,
        QK_MAGIC_TOGGLE_NKRO, OSL(_LEADR), LCTL(KC_1), LCTL(KC_2), XXXXXXX, LCTL(KC_TAB), _______, _______, XXXXXXX, LALT(KC_LEFT), LALT(KC_RIGHT), LCTL(KC_TAB), KC_DELETE, KC_PAGE_UP, _______, _______,
        _______, LALT(KC_GRAVE), LCTL(KC_Q), LCTL(KC_W), KC_LEFT_ALT, LCTL(KC_R), LCTL(KC_T), LCTL(KC_Y), LCTL(KC_U), LCTL(KC_I), LCTL(KC_O), LCTL(KC_P), KC_HOME, _______, _______, _______,
        _______, LALT(KC_TAB), LCTL(KC_A), LCTL(KC_S), LCTL(KC_D), LCTL(KC_F), KC_F4, LCTL(KC_H), KC_UP, KC_LEFT, KC_DOWN, KC_RIGHT, KC_END, _______, KC_END,
        _______, LSFT(KC_TAB), LCTL(KC_Z), LCTL(KC_X), LCTL(KC_C), LCTL(KC_V), LCTL(KC_B), BAT_LVL, LCTL(KC_N), LALT(KC_ENTER), DOT_SLS, DIR_UP, LCTL(KC_SLASH), KC_PAGE_DOWN, _______,
        _______, _______, KC_SPACE, KC_LEFT_CTRL, KC_LEFT_SHIFT, TD(LAYR_DOWN), KC_ENTER, TO(_QWERTY), _______, _______, _______
    ),
    [_RAISE]  = LAYOUT_ansi_89(
        KC_AUDIO_MUTE, KC_ESCAPE, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, KC_F11, KC_F12, KC_INSERT, KC_DELETE,
        MC_1, KC_F12, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, KC_F11, KC_EQUAL, KC_BACKSPACE, KC_PAGE_UP,
        MC_2, LSFT(KC_GRAVE), LSFT(KC_1), LSFT(KC_2), LSFT(KC_3), LSFT(KC_4), LSFT(KC_5), LSFT(KC_6), LSFT(KC_7), LSFT(KC_8), KC_LEFT_BRACKET, KC_RIGHT_BRACKET, LSFT(KC_EQUAL), KC_RIGHT_BRACKET, KC_BACKSLASH, KC_PAGE_DOWN,
        MC_3, KC_ESCAPE, LSFT(KC_SEMICOLON), KC_EQUAL, LSFT(KC_MINUS), LSFT(KC_BACKSLASH), KC_BACKSLASH, XXXXXXX, LSFT(KC_9), LSFT(KC_0), KC_MINUS, LSFT(KC_QUOTE), KC_AUDIO_VOL_UP, KC_ENTER, KC_HOME,
        MC_4, KC_PRINT_SCREEN, XXXXXXX, XXXXXXX, LSFT(KC_LEFT_BRACKET), LSFT(KC_RIGHT_BRACKET), XXXXXXX, KC_B, KC_AUDIO_MUTE, XXXXXXX, LSFT(KC_COMMA), LSFT(KC_DOT), LSFT(KC_SLASH), KC_AUDIO_VOL_DOWN, KC_UP,
        MC_5, KC_LEFT_CTRL, KC_LEFT_GUI, KC_LEFT_ALT, KC_MEDIA_REWIND, TO(_QWERTY), KC_MEDIA_FAST_FORWARD, TO(_RAISE2), KC_LEFT, KC_DOWN, KC_RIGHT
    ),
    [_RAISE2] = LAYOUT_ansi_89(
        RGB_TOG, QK_BOOTLOADER, KC_BRIGHTNESS_DOWN, KC_BRIGHTNESS_UP, KC_TASK, KC_FILE, RGB_VAD, RGB_VAI, KC_MEDIA_PREV_TRACK, KC_MEDIA_PLAY_PAUSE, KC_MEDIA_NEXT_TRACK, KC_AUDIO_MUTE, KC_AUDIO_VOL_DOWN, KC_AUDIO_VOL_UP, _______, _______,
        _______, _______, BT_HST1, BT_HST2, BT_HST3, P2P4G, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, RGB_TOG, RGB_MODE_FORWARD, RGB_VAI, RGB_HUI, RGB_SAI, RGB_SPI, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, RGB_MODE_REVERSE, RGB_VAD, RGB_HUD, RGB_SAD, RGB_SPD, _______, _______, _______, _______, _______, _______, _______, KC_END,
        _______, _______, _______, _______, _______, _______, BAT_LVL, BAT_LVL, QK_MAGIC_TOGGLE_NKRO, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, TO(_RAISE), _______, TO(_QWERTY), _______, _______, _______
    ),
    [_MOUSE]  = LAYOUT_ansi_89(
        RGB_TOG, _______, KC_BRIGHTNESS_DOWN, KC_BRIGHTNESS_UP, KC_TASK, KC_FILE, RGB_VAD, RGB_VAI, KC_MEDIA_PREV_TRACK, KC_MEDIA_PLAY_PAUSE, KC_MEDIA_NEXT_TRACK, KC_AUDIO_MUTE, KC_AUDIO_VOL_DOWN, KC_AUDIO_VOL_UP, _______, _______,
        _______, OSL(_LEADR), BT_HST1, BT_HST2, BT_HST3, P2P4G, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, RGB_TOG, RGB_MODE_FORWARD, RGB_VAI, RGB_HUI, RGB_SAI, RGB_SPI, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, KC_MS_BTN3, KC_MS_WH_LEFT, KC_MS_WH_RIGHT, KC_MS_BTN2, KC_MS_BTN1, XXXXXXX, XXXXXXX, KC_MS_UP, KC_MS_LEFT, KC_MS_DOWN, KC_MS_RIGHT, XXXXXXX, _______, KC_END,
        _______, XXXXXXX, XXXXXXX, XXXXXXX, KC_MS_WH_UP, KC_MS_WH_DOWN, XXXXXXX, BAT_LVL, QK_MAGIC_TOGGLE_NKRO, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, KC_LEFT_CTRL, KC_SPACE, TD(LAYR_DOWN), KC_ENTER, TO(_QWERTY), _______, _______, _______
    ),
    [_LEADR]  = LAYOUT_ansi_89(
        RGB_TOG, _______, KC_BRIGHTNESS_DOWN, KC_BRIGHTNESS_UP, KC_TASK, KC_FILE, RGB_VAD, RGB_VAI, KC_MEDIA_PREV_TRACK, KC_MEDIA_PLAY_PAUSE, KC_MEDIA_NEXT_TRACK, KC_AUDIO_MUTE, KC_AUDIO_VOL_DOWN, KC_AUDIO_VOL_UP, _______, _______,
        _______, QK_LEADER, XXXXXXX, XXXXXXX, XXXXXXX, LALT(KC_F4), XXXXXXX, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, LCTL(KC_GRAVE), XXXXXXX, XXXXXXX, LSFT(LCTL(KC_E)), LSFT(LCTL(KC_R)), LSFT(LCTL(KC_T)), XXXXXXX, XXXXXXX, XXXXXXX, LSFT(LCTL(KC_O)), LSFT(LCTL(KC_P)), XXXXXXX, _______, _______, _______,
        _______, XXXXXXX, XXXXXXX, LSFT(LCTL(KC_S)), LALT(LSFT(KC_D)), LSFT(LCTL(KC_F)), XXXXXXX, XXXXXXX, LALT(KC_UP), LALT(KC_LEFT), LALT(KC_DOWN), LALT(KC_RIGHT), XXXXXXX, _______, KC_END,
        _______, XXXXXXX, LSFT(LCTL(KC_Z)), XXXXXXX, LSFT(LCTL(KC_C)), LSFT(LCTL(KC_V)), XXXXXXX, BAT_LVL, LSFT(LCTL(KC_N)), XXXXXXX, XXXXXXX, DOT_SLS, XXXXXXX, XXXXXXX, _______,
        _______, _______, _______, _______, _______, TO(_QWERTY), _______, TO(_LEADR), _______, _______, _______
    ),
};

/* Byte-identical to the dump's encoder_map[6][1][2] at flash 0x080169A0 (24 bytes, immediately before keymaps[]). */
#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][2] = {
    [_QWERTY] = {ENCODER_CCW_CW(KC_VOLD, KC_VOLU)},
    [_LOWER]  = {ENCODER_CCW_CW(RGB_VAD, RGB_VAI)},
    [_RAISE]  = {ENCODER_CCW_CW(KC_VOLD, KC_VOLU)},
    [_RAISE2] = {ENCODER_CCW_CW(KC_NO,   KC_NO)},
    [_MOUSE]  = {ENCODER_CCW_CW(KC_NO,   KC_NO)},
    [_LEADR]  = {ENCODER_CCW_CW(RGB_VAD, RGB_VAI)},
};
#endif
// clang-format on

/* ---- TD(LAYR_DOWN): the Fn key --------------------------------------------------------------
 *   single tap            -> one-shot _LOWER (tap again with no key in between -> lock _LOWER;
 *                            tap while _LOWER is locked -> unlock into a one-shot;
 *                            tap while on _MOUSE -> one-shot _LOWER, then return to _MOUSE)
 *   hold (>= 175 ms)      -> lock _MOUSE (sticky; leave with TO(_QWERTY) or another dance)
 *   double tap            -> lock _LOWER
 *   interrupted hold, 3+  -> nothing
 * dump: cur_dance 0x0800D1C4, layr_dn_finished 0x0800D1EC, layr_dn_reset 0x0800CDD8,
 *       layer_oneshot_Lower 0x0800CDDA, oneshot_layer_changed_user 0x0800D25C
 */
td_state_t cur_dance(tap_dance_state_t *state) {
    if (state->count == 1) {
        if (!state->pressed) return TD_SINGLE_TAP;
        else if (!state->interrupted) return TD_SINGLE_HOLD;
        else return TD_UNKNOWN;
    } else if (state->count == 2) {
        return TD_DOUBLE_TAP;
    } else {
        return TD_UNKNOWN;
    }
}

static void layer_move_toLower(void) {
    layer_clear();
    layer_move(_LOWER);
}

static void layer_oneshot_Lower(void) {
    layer_on(_LOWER);
    set_oneshot_layer(_LOWER, ONESHOT_START);
    clear_oneshot_layer_state(ONESHOT_PRESSED);
}

void layr_dn_finished(tap_dance_state_t *state, void *user_data) {
    layr_dn_tap_state.state = cur_dance(state);
    switch (layr_dn_tap_state.state) {
        case TD_SINGLE_TAP:
            if (layer_state_is(_MOUSE)) {
                return_to_mouse = 1;
                layer_clear();
                layer_oneshot_Lower();
            } else {
                if (move_to_lower) {
                    layer_move_toLower();
                    move_to_lower = 0;
                } else if (layer_state_is(_LOWER)) {
                    layer_clear();
                    layer_oneshot_Lower();
                } else {
                    move_to_lower = 1;
                    layer_oneshot_Lower();
                }
            }
            break;
        case TD_SINGLE_HOLD:
            layer_clear();
            layer_move(_MOUSE);
            break;
        case TD_DOUBLE_TAP:
            layer_move_toLower();
            break;
        default:
            break;
    }
}

void layr_dn_reset(tap_dance_state_t *state, void *user_data) {
    layr_dn_tap_state.state = TD_NONE;
}

/* .data init image at flash 0x080179C8 -> RAM 0x20000E7C: exactly one 28-byte entry,
 * {on_each_tap NULL, on_dance_finished, on_reset, on_each_release NULL, user_data NULL}. */
tap_dance_action_t tap_dance_actions[] = {
    [LAYR_DOWN] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, layr_dn_finished, layr_dn_reset),
};

void oneshot_layer_changed_user(uint8_t layer) {
    if (!layer) {
        if (return_to_mouse) {
            layer_clear();
            layer_move(_MOUSE);
            return_to_mouse = 0;
        }
    }
}

/* ---- leader key (QK_LEADER on _LEADR, grave position) --------------------------------------
 * dump: leader_start_user 0x0800CDF4, leader_end_user 0x0800CDFE (354 B).
 * The seven tests are INDEPENDENT ifs (not else-if): each failed test branches to the next test and
 * each action block falls through into the next test, so <LEAD, F> fires block 1 AND block 6
 * (GUI+P, GUI+K, then GUI+'). Chords are explicit register/unregister pairs with the modifier released
 * before the key (tap_code16 cannot produce this order). Whether the double F binding was intended
 * is unknowable from the binary; it is reproduced as found.
 */
void leader_start_user(void) {
    rgb_matrix_set_color_all(255, 0, 255);
}

void leader_end_user(void) {
    rgb_matrix_set_color_all(0, 0, 0);

    if (leader_sequence_one_key(KC_F)) {
        register_code(KC_LGUI);
        register_code(KC_P);
        unregister_code(KC_LGUI);
        unregister_code(KC_P);
        register_code(KC_LGUI);
        register_code(KC_K);
        unregister_code(KC_LGUI);
        unregister_code(KC_K);
    }
    if (leader_sequence_two_keys(KC_A, KC_Q)) {
        register_code(KC_LCTL);
        register_code(KC_A);
        unregister_code(KC_LCTL);
        unregister_code(KC_A);
        register_code(KC_Z);
        unregister_code(KC_Z);
        register_code(KC_Q);
        unregister_code(KC_Q);
        register_code(KC_ENT);
        unregister_code(KC_ENT);
    }
    if (leader_sequence_one_key(KC_Y)) {
        register_code(KC_LCTL);
        register_code(KC_X);
        unregister_code(KC_LCTL);
        unregister_code(KC_X);
        register_code(KC_Y);
        unregister_code(KC_Y);
        register_code(KC_ENT);
        unregister_code(KC_ENT);
    }
    if (leader_sequence_two_keys(KC_LCTL, KC_I)) {
        register_code(KC_LCTL);
        register_code(KC_LALT);
        register_code(KC_I);
        unregister_code(KC_LCTL);
        unregister_code(KC_LALT);
        unregister_code(KC_I);
    }
    if (leader_sequence_one_key(KC_J)) {
        register_code(KC_LGUI);
        register_code(KC_P);
        unregister_code(KC_LGUI);
        unregister_code(KC_P);
    }
    if (leader_sequence_one_key(KC_F)) {
        register_code(KC_LGUI);
        register_code(KC_QUOT);
        unregister_code(KC_LGUI);
        unregister_code(KC_QUOT);
    }
    if (leader_sequence_one_key(KC_DEL)) {
        register_code(KC_LGUI);
        register_code(KC_UP);
        register_code(KC_LEFT);
        unregister_code(KC_LGUI);
        unregister_code(KC_UP);
        unregister_code(KC_LEFT);
    }
}

/* ---- boot hook (dump 0x0800CF60) -----------------------------------------------------------
 * default_layer_set(0) undoes the Mac/Win DIP-switch default layer set by dip_switch_update_kb during
 * keyboard_init(), so the board always boots on _QWERTY. rgb_matrix_mode() is the EEPROM-writing variant.
 */
void keyboard_post_init_user(void) {
    default_layer_set(0);
    rgb_matrix_mode(RGB_MATRIX_TYPING_HEATMAP); // mode 16 in this board's effect enumeration
}

/* ---- per-frame indicator (dump 0x0800CF74, 156 B) -------------------------------------------
 * Per LED: layer colour (highest active layer incl. default layer), then yellow if a one-shot GUI is
 * showing, else white if a one-shot Shift or caps lock is showing. Layer 0 leaves the animation visible.
 * The case order 2,3,1,4,5 reproduces the dump's jump-table/block layout with gcc 13.2.1 (behaviour is
 * order-independent).
 */
bool rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {
    for (uint8_t i = led_min; i < led_max; i++) {
        switch (get_highest_layer(layer_state | default_layer_state)) {
            case _RAISE:
                rgb_matrix_set_color(i, RGB_BLUE);
                break;
            case _RAISE2:
                rgb_matrix_set_color(i, RGB_ORANGE);
                break;
            case _LOWER:
                rgb_matrix_set_color(i, RGB_GREEN);
                break;
            case _MOUSE:
                rgb_matrix_set_color(i, RGB_TEAL);
                break;
            case _LEADR:
                rgb_matrix_set_color(i, RGB_RED);
                break;
            default:
                break;
        }
        if (gui_active) {
            rgb_matrix_set_color(i, RGB_YELLOW);
        } else if (shift_active || caps_active) {
            rgb_matrix_set_color(i, RGB_WHITE);
        }
    }
    return false;
}

/* ---- one-shot modifier indicator (dump body 0x0800D010; both hooks tail-call it) -------------
 * `mods` is the hook argument: for add_oneshot_mods() QMK passes only the newly added mods, for
 * del/clear the remaining state. The whole-board set_color_all() calls last one frame; the persistent
 * colour comes from the flags read by rgb_matrix_indicators_advanced_user above.
 */
static void handle_oneshots(uint8_t mods) {
    if (!(mods & MOD_MASK_SHIFT) && shift_active) {
        rgb_matrix_set_color_all(RGB_OFF);
        shift_active = 0;
    } else if (!(mods & MOD_MASK_GUI) && gui_active) {
        rgb_matrix_set_color_all(RGB_OFF);
        gui_active = 0;
    }
    if ((mods & MOD_MASK_SHIFT) && !shift_active) {
        rgb_matrix_set_color_all(RGB_WHITE);
        shift_active = 1;
    }
    if ((mods & MOD_MASK_GUI) && !gui_active) {
        rgb_matrix_set_color_all(RGB_YELLOW);
        gui_active = 1;
    }
}

void oneshot_mods_changed_user(uint8_t mods) {
    handle_oneshots(mods);
}

void oneshot_locked_mods_changed_user(uint8_t mods) {
    handle_oneshots(mods);
}

/* ---- OSM "unlock" helpers (dump 0x0800D090 / 0x0800D0B4) ------------------------------------
 * Verbatim port of the author's dactyl helpers, compiled live here (dead code on the dactyl).
 * They are INERT in this firmware: held_osm[] is never written non-NULL, so find_osm_slot() always
 * returns NULL and check_unlock_osm() always returns true -> the OSM keys are handled by stock QMK
 * (ONESHOT_TAP_TOGGLE 2: double-tap locks the modifier).
 * Quirks reproduced from the binary: `index += sizeof(uint16_t)` advances 2 elements (4 bytes), so
 * the second probe reads *(uint16_t *)4 when held_osm[0] is NULL (flash alias of the reset vector,
 * value 0x811D, never an OSM keycode). Behaviour-identical alternative: delete the is_osm block in
 * process_record_user and these two functions.
 */
uint16_t *find_osm_slot(uint16_t keycode) {
    uint16_t *index = held_osm[0];
    uint16_t *blank = NULL;
    for (int i = 0; i < OSM_HOLD_COUNT; i++) {
        if (index == NULL) {
            blank = index;
        } else if (*(index) == keycode) {
            return index;
        }
        index += sizeof(uint16_t);
    }
    return blank;
}

bool check_unlock_osm(uint16_t keycode) {
    uint16_t *slot = find_osm_slot(keycode);
    if (slot == NULL) {
        slot = &keycode;
        return true;
    }

    // Turn off the mod-lock if another OSM key is pressed while a mod is already held/locked
    if (get_mods() && (keycode != *(slot))) {
        clear_oneshot_mods();
        clear_oneshot_locked_mods();
        unregister_mods(get_oneshot_mods());

        for (int i = 0; i < OSM_HOLD_COUNT; i++) {
            held_osm[i] = NULL;
        }
        shift_active = 0;
        gui_active   = 0;
        return false;
    }
    return false;
}

/* ---- process_record_user (dump 0x0800D104, 192 B) ------------------------------------------ */
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (!process_record_keychron_common(keycode, record)) {
        return false;
    }

    // clear the 'layer movement flags' unless we are pressing TD(LAYR_DOWN) again (press AND release)
    if (move_to_lower && (keycode != TD(LAYR_DOWN))) {
        move_to_lower = 0;
    }
    // if we are not on 'lower' don't ever 'return to mouse'
    if (return_to_mouse && (!layer_state_is(_LOWER))) {
        return_to_mouse = 0;
    }

    // Only run the following logic on downstrokes
    if (record->event.pressed) {
        bool is_osm = ((keycode == OSM(MOD_LSFT)) || (keycode == OSM(MOD_RSFT)) || (keycode == OSM(MOD_LGUI)) || (keycode == OSM(MOD_RGUI)));
        if (is_osm) {
            return check_unlock_osm(keycode);
        }

        // caps indicator: the host LED has not toggled yet, so !caps_lock means "about to turn on"
        if (keycode == KC_CAPS && !(host_keyboard_led_state().caps_lock)) {
            caps_active = 1;
            return true;
        } else if (keycode == KC_CAPS && (host_keyboard_led_state().caps_lock)) {
            caps_active = 0;
            return true;
        }

        if (keycode == DOT_SLS) {
            register_code(KC_DOT);
            unregister_code(KC_DOT);
            register_code(KC_SLSH);
            unregister_code(KC_SLSH);
            return false;
        }

        if (keycode == DIR_UP) {
            register_code(KC_DOT);
            unregister_code(KC_DOT);
            register_code(KC_DOT);
            unregister_code(KC_DOT);
            register_code(KC_SLSH);
            unregister_code(KC_SLSH);
            return false;
        }
    }

    return true;
}
```

### 2.1 Behaviour summary (what the file above does) -- all [V] unless tagged

* **Layers** (numbers verified, names from the author's dactyl keymap [L]): 0 `_QWERTY`, 1 `_LOWER` (Ctrl chords, arrows on
  J/K/L/;, `DOT_SLS`/`DIR_UP` on , .), 2 `_RAISE` (F-keys, shifted symbols), 3 `_RAISE2` (Keychron Fn content: RGB keys, BT
  hosts, `QK_BOOT` on Esc), 4 `_MOUSE` (mouse keys on Caps/A/S/D/F, J/K/L/;), 5 `_LEADR` (`QK_LEADER` on grave, Ctrl+Shift chords).
  Layer access: `OSL(_LEADR)` on the key left of `1` (layers 0/1/3/4), `OSL(_RAISE)` on right Cmd, `TO(_QWERTY)` on right Cmd of
  layers 1-5, `TO(_RAISE2)`/`TO(_RAISE)` chain from layer 2/3, `TD(LAYR_DOWN)` on the Fn key of layers 0/1/4.
* **TD(LAYR_DOWN)** (Fn): single tap -> one-shot `_LOWER`; second tap with no other key event in between -> lock `_LOWER`; tap while
  `_LOWER` is locked -> one-shot `_LOWER` again; tap while on `_MOUSE` -> one-shot `_LOWER` and return to `_MOUSE` afterwards
  (`return_to_mouse`); hold >= 175 ms without another key -> lock `_MOUSE` (sticky); double tap -> lock `_LOWER`; interrupted hold
  or 3+ taps -> nothing. Nothing is typed by the dance. `on_reset` is empty (the mouse layer stays after release).
* **Leader** (`QK_LEADER` on `_LEADR`; 525 ms per key, max 5 keys, mod-tap/layer-tap reduced to their tap key):
  `F` -> GUI+P, GUI+K **and** GUI+' (two independent blocks both match); `A Q` -> Ctrl+A, Z, Q, Enter; `Y` -> Ctrl+X, Y, Enter;
  `LCtrl I` -> Ctrl+Alt+I; `J` -> GUI+P; `Del` -> GUI+Up+Left (GUI released first). Board flashes magenta on start, black on end
  (one frame; usually invisible under the running effect [L]).
* **Custom keycodes**: `DOT_SLS` (0x7E40) types `./`, `DIR_UP` (0x7E41) types `../`, both via register/unregister pairs and `return false`.
* **OSM keys** `OSM(MOD_LSFT)`, `OSM(MOD_RSFT)`, `OSM(MOD_LGUI)`: handled by stock QMK with `ONESHOT_TAP_TOGGLE 2` (tap once =
  one-shot, tap twice = lock). The `check_unlock_osm` path is compiled but inert (`held_osm[]` is never populated).
* **Caps indicator**: pressing `KC_CAPS` sets/clears `caps_active` from the host LED state *before* the toggle -> whole board white
  while this keyboard believes caps lock is on (not resynced from the host; Keychron's own LED-48 white indicator stays host-accurate).
* **RGB**: boots with `default_layer_set(0)` (ignores the Mac/Win DIP position) and `rgb_matrix_mode(RGB_MATRIX_TYPING_HEATMAP)`.
  Each frame: layer colour (1 green, 2 blue, 3 orange, 4 teal, 5 red; 0 = animation visible), then yellow if a one-shot GUI is
  showing, else white if one-shot Shift or caps is showing. One-shot mods also flash the whole board white/yellow/off once.
* **Encoder**: layers 0/2 volume, layers 1/5 RGB brightness, layers 3/4 nothing.
* **Not present**: `layer_state_set_user`, `housekeeping_task_user`, `matrix_scan_user`, `led_update_user`, `pre/post_process_record_user`,
  `get_tapping_term`, `raw_hid_receive`, `encoder_update_user` -- all stock defaults in the dump; do not add them.

## 3. config.h

```c
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
```

| define | value | tag | evidence (dump address) |
|---|---|---|---|
| `TAPPING_TERM` | 175 | [V] | `get_tapping_term` 0x0800DEFC = `movs r0,#175; bx lr`; independent witness `process_tapping` 0x0800E1B4 `cmp r7,#174` (QUICK_TAP_TERM = TAPPING_TERM) |
| `TAPPING_TERM_PER_KEY` | defined | [V] | `GET_TAPPING_TERM` compiled as a *call* at 0x0800DF52, 0x0800E016, 0x0800E192, 0x080120EC (an immediate without it, cf. ref ELF `cmp r0,#140`); the weak default is linked at the action_tapping.o position -> no user override |
| `ONESHOT_TAP_TOGGLE` | 2 | [V] | process_action 0x0800D824 `cmp r8,#1` -> add_oneshot_mods, 0x0800D832 `cmp r8,#2` -> register_mods + del_oneshot_mods + add_oneshot_locked_mods; OP_ONESHOT 0x0800DA46/0x0800DA60 `cmp r8,#1`; no QMK default exists |
| `LEADER_PER_KEY_TIMING` | defined | [V] | `process_leader` 0x0801192A calls `leader_reset_timer` 0x080119F8 after each added key |
| `LEADER_TIMEOUT` | 525 | [V] | `leader_sequence_timed_out` 0x080119CA `movw r3,#0x20d` (default 300, dactyl 600) |
| `MK_KINETIC_SPEED` | defined | [V] | `move_unit` 0x08011A8C / `wheel_unit` 0x08011B14 are the kinetic algorithm |
| `MOUSEKEY_MOVE_DELTA` | 45 | [V] | 0x08011ABA `movs r2,#45` |
| `MOUSEKEY_INITIAL_SPEED` | 30 | [V] | 0x08011AC2 `adds r0,#30`, 0x08011B00 `movs r0,#30` |
| `MOUSEKEY_BASE_SPEED` | 1500 | [V] | 0x08011ACA `movw r3,#1500` |
| `MOUSEKEY_INTERVAL` | 40 | [V] | `.data` mk_interval @0x20000EC5 init 0x28 (flash 0x08017A11); `mousekey_on` 0x08011BAA `subs r0,#160` (= 40<<2) |
| `MOUSEKEY_DELAY` | 1 | [L] | mk_delay = DELAY/10 == 0 lives in .bss (0x20002009); any 0..9 (incl. the kinetic default 5) compiles identically; 1 is the dactyl value |
| `MOUSEKEY_WHEEL_INITIAL_MOVEMENTS` | 64 | [V] | 0x08011B6E `movs r3,#64`, 0x08011B48 `add.w r3,r0,#64`; mk_wheel_interval init 15 = 1000/64 @0x20000EC2 |
| `MOUSEKEY_WHEEL_BASE_MOVEMENTS` | 32 | [V value / L presence] | 0x08011B34, 0x08011B52 `cmp r3,#32` -- equals the QMK default, so the line is undecidable |
| `MOUSEKEY_WHEEL_ACCELERATED_MOVEMENTS` | 50 | [V] | 0x08011B3C, 0x08011B6A `movs r3,#50` (default 48) |
| `RGB_MATRIX_DEFAULT_MODE` | `RGB_MATRIX_TYPING_HEATMAP` (16) | [V value / L spelling & file] | `eeconfig_update_rgb_matrix_default` 0x0800FE1C `movs r3,#0x41` (enable 1, mode 16); stock builds store 0x15 (mode 5); mode 16 = TYPING_HEATMAP by the effect enumeration (`rgb_task_render` tbb case 16 -> heatmap 0x08010920, clamp `cmp #22`) |

Deliberately absent (checked, would change the binary): `ONESHOT_TIMEOUT` (no timer code in `set_oneshot_layer` 0x0800E504 /
`add_oneshot_mods` 0x0800E3EC), `PERMISSIVE_HOLD`, `HOLD_ON_OTHER_KEY_PRESS`, `RETRO_TAPPING`, `QUICK_TAP_TERM` (== TAPPING_TERM),
`TAPPING_TOGGLE` (default 5: 0x0800D9E2/0x0800D9F4), `LEADER_NO_TIMEOUT`, `LEADER_KEY_STRICT_KEY_PROCESSING`, `FORCE_NKRO`,
`RGB_MATRIX_DEFAULT_HUE/SAT/VAL/SPD` (stock 0/255/255/127 at 0x08016710 / 0x0800FE28), `DEBOUNCE` (board 20), `LAYER_STATE_16BIT`
(QMK default for <= 16 layers). Board-level settings (`RGB_MATRIX_TIMEOUT_INFINITE`, `CAPS_LOCK_INDEX 48`, `RAW_HID_CMD 0xAA ... 0xAB`,
`ENCODER_MAP_KEY_DELAY 2`, ...) come from `keyboards/keychron/v10_max/` unchanged.

## 4. rules.mk

```make
# Keychron V10 Max "dexter" keymap -- feature set recovered from the flash dump
# (evidence: keychron_v10max_backup/RECONSTRUCTION_SPEC.md section "rules.mk")
TAP_DANCE_ENABLE = yes
LEADER_ENABLE = yes
MOUSEKEY_ENABLE = yes

# default-on in this fork, provably compiled OUT of the dump
MAGIC_ENABLE = no
GRAVE_ESC_ENABLE = no
SPACE_CADET_ENABLE = no

VIA_ENABLE = no
LTO_ENABLE = no
CONSOLE_ENABLE = no
COMMAND_ENABLE = no
```

| line | tag | evidence |
|---|---|---|
| `TAP_DANCE_ENABLE = yes` | [V] | `process_tap_dance` 0x08012040, `tap_dance_task` 0x080120D0, `tap_dance_actions[]` @0x20000E7C |
| `LEADER_ENABLE = yes` | [V] | `process_leader` 0x080118F4, `leader_task` 0x080119DC, leader.o 0x08011940.. |
| `MOUSEKEY_ENABLE = yes` | [V] | `mousekey_task` 0x08011DF0 (board default anyway; listed because the dactyl rules.mk lists it) |
| `MAGIC_ENABLE = no` | [V] | fork default yes (`builddefs/generic_features.mk`); `process_magic` absent from the image and from the `process_record_quantum` chain -> the keymap's `NK_TOGG` keys are inert and NKRO can never be switched on |
| `GRAVE_ESC_ENABLE = no` | [V] | `process_grave_esc` absent (present in the fork's default build) |
| `SPACE_CADET_ENABLE = no` | [V] | `process_space_cadet`/`perform_space_cadet` absent; `get_tapping_term` has exactly four callers |
| `VIA_ENABLE = no` | [V] | `raw_hid_receive` 0x0800C908 is the fork's non-VIA variant; no dynamic keymap, `keymaps[]` read from flash |
| `LTO_ENABLE = no` | [V] | 931 functions, weak `bx lr` hooks reached via `bl`, 606 exact matches to the non-LTO reference vs 217 to the LTO one |
| `CONSOLE_ENABLE = no`, `COMMAND_ENABLE = no` | [V] (explicit line [U]) | no console interface / `console_task`, no command strings; these are defaults, the dactyl rules.mk wrote them explicitly |

Everything else (encoder + encoder map, dip switch, NKRO, extrakey, bootmagic, RGB matrix, raw HID, wear-levelling EEPROM,
wireless, factory test) is the board's `info.json` / `rules.mk` and is present in the image.

## 5. Behavioural differences that cannot be avoided

1. **Compiler.** The original was built with Debian/Ubuntu `gcc-arm-none-eabi` 13.2.rel1 (GCC 13.2.1 20231009) and
   `libnewlib-arm-none-eabi` 4.4.0.20231231-2 (newlib `__FILE__` path `../../../../../../newlib/libc/stdlib/rand.c`, 30 libc members
   byte-identical). The xPack 13.2.1 used for verification shares the code generator (all QMK code masked-identical) but a different
   newlib build (`rand`, `malloc`, `memcpy`, printf cluster differ in bytes, not behaviour). The QMK-installed gcc 15.2 compiles the
   same source with different register allocation / block placement; behaviour is unchanged, byte identity is not.
2. **Fork revision.** The dump was built from fork commit **8e390f92a2** (2024-06-18). The pinned reference is 1011db8c8d
   (2024-07-01); the only intervening change affecting this board is 0c05eef6cd ("Fixed macro doesn't work correctly with NKRO"),
   which removes a duplicate `wireless_transport.send_nkro()` call in `wireless_send_nkro`. A rebuild from 1011db8c8d or newer carries
   that fix (wireless NKRO reports are sent once instead of twice). Building on the branch HEAD (`/Users/dexter/code/qmk-keychron`)
   additionally picks up every later fork change (e.g. the 2025 partial RGB EEPROM writes, adaptive NKRO) -- the keymap itself
   needs no change for that, but the stock behaviour will not be the 2024 one.
3. **EEPROM state.** The dump's emulated EEPROM held runtime adjustments (RGB hue 8, sat 239, val 47, speed 191, mode 16, RGB
   enabled; keymap_config 0x1400; default layer 0). Reflashing erases sector 1 (0x08004000) -> the board comes up with the compiled
   defaults (heatmap, hue 0, sat 255, val 255, speed 127) until the RGB keys/encoder are used again. `eeprom_recovered.md` lists the
   exact history if the old look should be restored by hand (val steps of 16, speed steps of 16, hue step 8).
4. **Unrecoverable source details** (no effect on behaviour): identifier names (taken from the dactyl keymap), comments, formatting,
   function order in the file, `switch` vs `if/else if` in `process_record_user`, `||` vs `|` in the white test, whether the two
   one-shot hooks called a shared helper or had duplicated bodies, whether `layr_dn_reset` stored `TD_NONE` to a write-only static or
   was empty, whether `QUICK_TAP_TERM`/`MOUSEKEY_WHEEL_BASE_MOVEMENTS` were written explicitly, the exact `MOUSEKEY_DELAY` (0..9)
   and `MOUSEKEY_WHEEL_DELAY` (10..19), and whether `RGB_MATRIX_DEFAULT_MODE` was spelled by name or as 16 and lived in config.h or
   a keymap.json.
5. **Reproduced quirks you may want to change on purpose** (the spec keeps them for fidelity): the double `KC_F` leader binding;
   the inert `check_unlock_osm` block with its `*(uint16_t *)4` read (harmless on STM32, UB in C); `NK_TOGG` keys that do nothing
   because MAGIC is off; caps indicator not synced from the host; the one-shot flags tracking only the last one-shot change.

## 6. Predictions to test on hardware

Tick each after flashing the reconstruction; every line is a consequence of verified code.

- [ ] Boots on layer 0 with the typing-heatmap effect regardless of the Mac/Win DIP position; flipping the switch afterwards turns
      the whole board **blue** (default layer 2) until `TO(_QWERTY)` / reboot. Keychron's white caps-lock LED (index 48) still works.
- [ ] Fn key (row 5, next to space): **tap** -> next key comes from `_LOWER` (board green while active); **tap, tap** (nothing in
      between) -> `_LOWER` locked (green stays); tap again while locked -> one-shot again, then back to base; **hold ~0.2 s**
      -> `_MOUSE` locked (teal), stays after release; **double tap** -> `_LOWER` locked; **hold + press another key** -> nothing.
- [ ] On `_MOUSE`, tap Fn, press one `_LOWER` key -> that key acts from `_LOWER`, then the board is back on `_MOUSE` (teal).
- [ ] Any non-Fn key press or release between two Fn taps cancels the "second tap locks" behaviour.
- [ ] Tapping term ~175 ms (a hold shorter than that counts as a tap).
- [ ] `OSL(_LEADR)` (key left of `1`) then grave = leader; then `F` within 525 ms -> GUI+P, GUI+K, GUI+' all three; `A` `Q` ->
      Ctrl+A, Z, Q, Enter; `Y` -> Ctrl+X, Y, Enter; `LCtrl` `I` -> Ctrl+Alt+I; `J` -> GUI+P; `Del` -> GUI+Up+Left. Waiting > 525 ms
      between keys ends the sequence; a 6th key ends it too.
- [ ] `_LOWER` `,` types `./`, `_LOWER` `.` types `../`, `_LEADR` `.` types `./`.
- [ ] Left Shift position (`OSM(MOD_LSFT)`), `;` position (`OSM(MOD_RSFT)`), left Cmd (`OSM(MOD_LGUI)`): tap once -> next key
      shifted / GUI'd, board flashes then stays **white** (shift) or **yellow** (GUI) until consumed; tap twice -> locked (colour
      stays); tap a third time -> unlocked. `OSM(MOD_RGUI)` is not on any layer.
- [ ] Caps Lock (left Option position): board white while on (from this keyboard's point of view); toggling caps from another
      keyboard desyncs the white board but not LED 48.
- [ ] Layer colours: `_LOWER` green, `_RAISE` (hold right Cmd = OSL) blue, `_RAISE2` orange, `_MOUSE` teal, `_LEADR` red; layer 0
      shows the heatmap.
- [ ] Encoder: volume on layers 0 and 2, RGB brightness on 1 and 5, nothing on 3 and 4.
- [ ] `NK_TOGG` (layers 1/3/4) does nothing (MAGIC off); NKRO stays off.
- [ ] Mouse keys on `_MOUSE` accelerate kinetically (slow start, ~1500 px/s cap; wheel 64 -> 32 -> 50 movements/s).
- [ ] Raw HID: a 32-byte `0xAB 0x08 ...` factory probe (checksum at bytes 30/31, `tools/rawhid_probe.py`) answers with the version
      string `v1.0.0 <build date>`; `0xA0`, `0xA1` and VIA `0x01` probes get **no** answer (non-VIA fork build, by design).
- [ ] `QK_BOOT` on `_RAISE2` Esc enters ROM DFU; Bluetooth/2.4 GHz host keys on `_RAISE2`/`_MOUSE` work as stock.

## 7. Installing

Copy `reconstructed_keymap/{keymap.c,config.h,rules.mk}` over the placeholder
`keyboards/keychron/v10_max/ansi_encoder/keymaps/dexter/` in the fork checkout you build from, then
`qmk compile -kb keychron/v10_max/ansi_encoder -km dexter`. Rebuilding with the verification command in section 0 and
re-running `tools/final_compile_compare.py` is the regression test for any later edit.
