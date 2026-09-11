# Dactyl Manuform 5x6 keymap — reference summary for the V10 Max reverse-engineering

Sources (all in `/Users/dexter/code/qmk`, path `keyboards/handwired/dactyl_manuform/5x6/keymaps/default/`):

| Tag used below | Revision | Commit date | Notes |
|---|---|---|---|
| **09bf** | `09bf262a04` | 2026-06-06 02:31 | "Working commit for custom manual home-row mods and macos conversions of shortcuts." First custom commit (869 lines added). |
| **LM** (local-macos HEAD) | `45864d21f7` = `local-macos` | 2026-06-06 03:51 | "Adding a double dash shortcut key, adding caps_lock tap via custom function, tweaking some timings and serial config..." |
| **DS** (dexter-ds HEAD) | `bfec63fcc9` = `dexter-ds/dexter-ds` | 2026-07-16 .. 2026-07-30 | 9 commits: phantom indicator layers, fast-typing detector, leader-on-TD fix, thumb remaps, Z tap dance. |

Extracted copies with the line numbers cited below:
`/private/tmp/claude-501/-Users-dexter-code-qmk/05a2f1c0-36d0-494b-8463-6b0ce77f8bca/scratchpad/dactyl_ref/`
`keymap_local-macos.c` (873 lines), `keymap_dexter-ds_dexter-ds.c` (1183), `keymap_09bf262a04.c` (871), `config_*.h`, `rules_*.mk`.

## 0. Timeline caveat and which version the V10 Max matches

* The V10 Max binary was built **2024-07-09**. In this repo the dactyl keymap did not exist before **2026-06-06** (before `09bf` the path only has upstream QMK commits, last `d5cc00ab62 2024-07-20`). So **neither repo version was "current" when the V10 Max was built** — the dactyl keymap arrived in this repo already fully formed (`09bf` is a "macos conversions" commit of an older, Linux/Sway-era keymap that lived elsewhere). The V10 Max firmware is a sibling of that older, pre-macOS keymap.
* Evidence in the recovered V10 Max table (`keymap_recovered_table.c`) that pins the V10 Max to the **pre-`09bf`, pre-DBL_DASH, Linux (Ctrl, not Cmd) generation**:
  * Layer 1 bottom-right row: `LCTL(KC_N), LALT(KC_ENTER), QK_USER_0, QK_USER_1, LCTL(KC_SLASH)` — identical to `09bf` `_LOWER` line 87: `LCTL(KC_N),LALT(KC_ENT),DOT_SLS,DIR_UP,LCTL(KC_SLSH)`. In **LM** (line 88) the M slot became `DBL_DASH` and `LALT(KC_ENT)` moved to the top row (Y slot, line 85). The V10 Max top row still has `XXXXXXX` in the Y slot (as `09bf` line 84: `KC_NO`).
  * No `QK_USER_2` anywhere in the 6 layers → `DBL_DASH` did not exist → the enum is exactly `{DOT_SLS = SAFE_RANGE, DIR_UP}` as in `09bf` lines 35-39.
  * Layer 1 R slot is `LCTL(KC_R)`; `09bf`/**LM** have the macOS `LGUI(KC_R)` (line 85/86); **DS** reverted to `LCTL(KC_R)` (line 122).
  * Layer 5: `LSFT(LCTL(KC_R))`, `LSFT(LCTL(KC_C))`; **LM** has `LGUI(LSFT(KC_R))`, `LGUI(KC_C)` (lines 128, 130); **DS** has `LCTL(LSFT(...))` (lines 164, 166).
  * Base layer keeps `OSM(MOD_LGUI)` (left Cmd) and `KC_CAPS` (left Option) — the **LM** thumb cluster (line 80-81) has `OSM(MOD_LGUI) ... KC_CAPS`; **DS** dropped `OSM(MOD_LGUI)` (line 116).
  * `OSL(5)` on grave ↔ `OSL(_LEADR)` thumbs; `OSL(2)` on right Cmd ↔ `OSL(_RAISE)` thumb (LM line 79); `TD(0)` on Fn ↔ `TD(LAYR_DOWN)` (index 0 in every version).
* **Practical consequence**: use **LM** (or `09bf`) as the primary reference for behaviour, with macOS substitutions undone (Ctrl instead of Cmd) and without `DBL_DASH`. Use **DS** only for ideas about later refinements (fast-typing detector, layer lock flag, leader-on-TD fix) — those almost certainly are **not** in the 2024 binary.

## 1. Layers and the V10 Max mapping

Both versions (`LM` lines 11-19, `DS` lines 11-19; `DS` adds phantom layers 24-27):

```c
#define _QWERTY 0
#define _LOWER 1
#define _RAISE 2
#define _RAISE2 3
#define _MOUSE 4
#define _LEADR 5
// DS only:
#define _CAPSIND 6
#define _ALTLKIND 7
#define _LOWLKIND 8
#define PHANTOM_LAYERS_MASK (((layer_state_t)1 << _CAPSIND) | ((layer_state_t)1 << _ALTLKIND) | ((layer_state_t)1 << _LOWLKIND))
```

| V10 Max layer | Dactyl layer | Matching content |
|---|---|---|
| 0 | `_QWERTY` | `OSM(MOD_LSFT)`/`OSM(MOD_RSFT)` on the home row ends (LM 76), `KC_TAB` at the left-shift position (LM 77), `OSL(_RAISE)` → `OSL(2)`, `OSL(_LEADR)` → `OSL(5)`, `OSM(MOD_LGUI)`, `KC_CAPS`, `TD(LAYR_DOWN)` → `TD(0)` |
| 1 | `_LOWER` | LM 84-94: `LCTL(x)` letters, `LALT(KC_GRV)`, `LALT(KC_TAB)`, `LSFT(KC_TAB)`, `LALT(KC_LEFT/RGHT)`, `LCTL(KC_TAB)`, `KC_F4` in the G slot (LM 87: `LCTL(KC_F),KC_F4`), arrows `KC_UP, KC_LEFT, KC_DOWN, KC_RGHT` on J K L ; (LM 87), `TO(_QWERTY)`, `KC_SPC/KC_LCTL/KC_LSFT` thumbs, `TD(LAYR_DOWN)`, `OSL(_LEADR)`, `DOT_SLS`, `DIR_UP` |
| 2 | `_RAISE` | LM 96-105: F-keys row, shifted symbols, `KC_COLN, KC_EQL, KC_UNDS, KC_PIPE, KC_BSLS`, `KC_LPRN, KC_RPRN, KC_MINS, KC_DQUO`, `KC_LCBR/KC_RCBR`, `KC_LT/KC_GT/KC_QUES`, `KC_PSCR`, `KC_MUTE/VOLU/VOLD`, `KC_MFFD/KC_MRWD`, `TO(_RAISE2)` + `TO(_QWERTY)` on thumbs (LM 102-103) → V10 `TO(3)`/`TO(0)` |
| 3 | `_RAISE2` | LM 106-115: `QK_BOOT`, `TO(_RAISE)`, `TO(_QWERTY)`; on the V10 Max this layer was filled with the Keychron Fn content (RGB, BT_HST1-3, P2P4G, BAT_LVL, NK_TOGG) but keeps `QK_BOOT` and the `TO(2)`/`TO(0)` thumbs |
| 4 | `_MOUSE` | LM 116-125: `MS_BTN3, MS_WHLL, MS_WHLR, MS_BTN2, MS_BTN1` on the Caps/A/S/D/F slots, `MS_UP, MS_LEFT, MS_DOWN, MS_RGHT` on J/K/L/;, `MS_WHLU/MS_WHLD` on C/V, `OSL(_LEADR)`, `KC_SPC`, `TO(_QWERTY)`, `KC_ENT`, `TD(LAYR_DOWN)`, `KC_LCTL` — position-for-position identical to V10 layer 4 |
| 5 | `_LEADR` | LM 126-135: `LALT(KC_F4)` in the R slot of the number row, `LCTL(KC_GRV)`, `LCTL(LSFT(KC_E/T/O/P/S/F/Z/V/N))`, `LALT(LSFT(KC_D))`, `LALT(KC_UP/LEFT/DOWN/RIGHT)` on J/K/L/;, `DOT_SLS` on `.`, `QK_LEAD` on thumbs (V10: grave), `TO(_QWERTY)`, `TO(_LEADR)` |

Verbatim `LM` keymap (lines 72-136):

```c
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_QWERTY] = LAYOUT_5x6(
        KC_ESC, KC_1, KC_2, KC_3, KC_4, KC_5,                         KC_6, KC_7, KC_8, KC_9, KC_0, KC_BSLS,
        KC_GRV, KC_Q, KC_W, KC_E, KC_R, KC_T,                         KC_Y, KC_U, KC_I, KC_O, KC_P, KC_MINS,
        OSM(MOD_LSFT), KC_A, TD(TD_S_OSM), TD(LAYR_DOWN), TD(TD_F_OSM), TD(TD_G_CAPS),  TD(TD_H_CAPS), TD(TD_J_OSM), TD(LAYR_UP), KC_L, KC_QUOT, OSM(MOD_RSFT),
        KC_TAB, KC_Z, KC_X, KC_C, KC_V, KC_B,                         KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, KC_SCLN,
                       KC_LCTL, KC_LGUI,                                                    KC_HOME, KC_END,
                                        KC_SPC, KC_BSPC,              OSL(_RAISE), KC_ENT,
                                        OSM(MOD_LGUI), OSL(_LEADR), KC_DEL, OSM(MOD_RGUI),
                                        OSL(_LEADR), KC_CAPS,         KC_CAPS, OSL(_LEADR)
    ),

    [_LOWER] = LAYOUT_5x6(
        KC_BSPC, LCTL(KC_1),LCTL(KC_2),KC_NO,LCTL(KC_TAB),_______,               LALT(KC_ENT), LALT(KC_LEFT),LALT(KC_RGHT), LCTL(KC_TAB), KC_DEL, KC_PGUP,
        LALT(KC_GRV), LCTL(KC_Q),LCTL(KC_W),KC_LALT,LGUI(KC_R),LCTL(KC_T),       LCTL(KC_Y),LCTL(KC_U),LCTL(KC_I),LCTL(KC_O),LCTL(KC_P),KC_HOME,
        LALT(KC_TAB),LCTL(KC_A),LCTL(KC_S),LCTL(KC_D),LCTL(KC_F),KC_F4,          TO(_QWERTY), KC_UP, KC_LEFT, KC_DOWN, KC_RGHT, KC_END,
        LSFT(KC_TAB),LCTL(KC_Z),LCTL(KC_X),LCTL(KC_C),LCTL(KC_V),LCTL(KC_B),     LCTL(KC_N),DBL_DASH,DOT_SLS,DIR_UP,LCTL(KC_SLSH),KC_PGDN,
                                QK_BOOT,KC_PSCR,                                            KC_PGUP, KC_PGDN,
                                                KC_LCTL,  LGUI(KC_UP),            TO(_QWERTY),     KC_ENT,
                                                KC_LSFT,TD(LAYR_DOWN),            LGUI(KC_LEFT),KC_LALT,
                                                KC_SPC,OSL(_LEADR),            KC_LCTL,OSL(_LEADR)

    ),

    [_RAISE] = LAYOUT_5x6(
          KC_F12 , KC_F1 , KC_F2 , KC_F3 , KC_F4 , KC_F5 ,                        KC_F6  , KC_F7 , KC_F8 , KC_F9 ,KC_F10 ,KC_F11 ,
          KC_TILD, KC_EXLM, KC_AT,    KC_HASH, KC_DLR, KC_PERC,                   KC_CIRC, KC_AMPR, KC_ASTR, KC_LBRC, KC_RBRC, KC_PLUS,
          KC_ESC, KC_COLN, KC_EQL,   KC_UNDS, KC_PIPE, KC_BSLS,                  TO(_RAISE2), KC_LPRN, KC_RPRN, KC_MINS,   KC_DQUO, KC_VOLU,
          KC_PSCR,    KC_NO,   KC_NO, KC_LCBR,   KC_RCBR, KC_NO,                 KC_MUTE,    KC_NO, KC_LT,     KC_GT, KC_QUES, KC_VOLD,
                                                   KC_MPLY, KC_MSTP,                            KC_EQL ,QK_BOOT,
                                                  _______,_______,        TO(_RAISE2), _______,
                                                  _______,TO(_QWERTY),            KC_MFFD, KC_MRWD,
                                                  _______,_______,            _______,_______
    ),
       [_RAISE2] = LAYOUT_5x6(
          KC_F12 , KC_F1 , KC_F2 , KC_F3 , KC_F4 , KC_F5 ,                        KC_F6  , KC_F7 , KC_F8 , KC_F9 ,KC_F10 ,KC_F11 ,
           KC_NO,     QK_BOOT, _______,     KC_NO, TO(_RAISE),    KC_NO,                    TO(_QWERTY), KC_NO,   KC_NO,    KC_NO,  QK_BOOT,   KC_NO,
          _______,KC_LEFT,KC_UP  ,KC_DOWN,KC_RGHT,KC_LPRN,                        KC_RPRN,KC_MPRV,KC_MPLY,KC_MNXT,_______,KC_VOLU,
          _______,_______,_______,_______,_______,_______,                        _______,_______,_______,_______,_______,KC_VOLD,
                                                  _______,_______,            _______,_______,
                                                  _______,_______,         TO(_QWERTY),_______,
                                                  _______,TO(_RAISE),            _______,_______,
                                                  _______,_______,            _______,_______
    ),
  [_MOUSE] = LAYOUT_5x6(
    KC_F12 , KC_F1 , KC_F2 , KC_F3 , KC_F4 , KC_F5 ,                        KC_F6  , KC_F7 , KC_F8 , KC_F9 ,KC_F10 ,KC_F11 ,
    KC_NO, _______, KC_NO, KC_NO, KC_NO, KC_NO,                            KC_NO, MS_WHLU, MS_WHLD, KC_NO, _______, KC_NO,
    MS_BTN3, MS_WHLL, MS_WHLR, MS_BTN2, MS_BTN1,         KC_NO, TO(_QWERTY), MS_UP, MS_LEFT, MS_DOWN, MS_RGHT, KC_NO,
    KC_NO, KC_NO, KC_NO, MS_WHLU, MS_WHLD, KC_NO,              KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
                                            _______,_______,            _______ ,_______,
                                            OSL(_LEADR), KC_SPC,           TO(_QWERTY),KC_ENT,
                                            _______,TD(LAYR_DOWN),            _______,_______,
                                            _______,_______,            _______,KC_LCTL
    ),
       [_LEADR] = LAYOUT_5x6(
           KC_NO, KC_NO,KC_NO,KC_NO,LALT(KC_F4),KC_NO,                            KC_NO,KC_NO,KC_NO,KC_NO, KC_NO, KC_NO,
  LCTL(KC_GRV),KC_NO,KC_NO,LCTL(LSFT(KC_E)),LGUI(LSFT(KC_R)),LCTL(LSFT(KC_T)),    KC_NO, KC_NO,KC_NO,LCTL(LSFT(KC_O)),LCTL(LSFT(KC_P)), KC_NO,
  KC_NO, KC_NO, LCTL(LSFT(KC_S)), LALT(LSFT(KC_D)),LCTL(LSFT(KC_F)),TO(_QWERTY),        KC_NO,LALT(KC_UP),LALT(KC_LEFT),LALT(KC_DOWN),LALT(KC_RIGHT), KC_NO,
  KC_NO, LCTL(LSFT(KC_Z)),KC_NO,LGUI(KC_C),LCTL(LSFT(KC_V)),KC_NO,          LCTL(LSFT(KC_N)), KC_NO, KC_NO, DOT_SLS, KC_NO, KC_NO,
                                                  _______,_______,            KC_EQL ,_______,
                                                  _______,QK_LEAD,            TO(_LEADR),_______,
                                                  _______,QK_LEAD,        _______,_______,
                                                  _______,QK_LEAD,            _______,_______
    )
};
```

`09bf` differences in `_LOWER` (lines 83-93): top-row Y slot `KC_NO` (not `LALT(KC_ENT)`), M slot `LALT(KC_ENT)` (not `DBL_DASH`), inner thumbs `_______, KC_P0` and `KC_LGUI, LGUI(KC_UP)` (LM: `KC_PGUP, KC_PGDN` / `KC_LCTL, LGUI(KC_UP)`).

**DS** keymap differences worth knowing (lines 108-202): `TD(TD_Q_TILD)` on Q, `TD(TD_D_OSM)` on D, `TD(LAYR_DOWN)` moved to **F**, `TD(TD_Z_GRV)` on Z, `TD(TD_V_TAB)` on V; `_LOWER` G slot `LCTL(KC_0)` (was `KC_F4`), R slot `LCTL(KC_R)`, `LCTL(LSFT(KC_TAB))` added; `_RAISE` has `TO(_QWERTY)` in the B slot and `KC_GRV`/`KC_ESC` extras; `_MOUSE` adds `KC_PLUS/KC_MINS`, `KC_LSFT`, `KC_TAB`; `_LEADR` adds `EE_CLR` in the grave slot and `LCTL(LSFT(KC_A))`; plus three all-`_______` phantom layers 6-8.

## 2. Custom keycodes (enum order) and `process_record_user`

### Enum

`09bf` lines 35-39 (**this is what the V10 Max has**):

```c
enum custom_keycodes
{
    DOT_SLS = SAFE_RANGE,
    DIR_UP
};
```

`LM` lines 35-40 and `DS` lines 56-61:

```c
enum custom_keycodes
{
    DOT_SLS = SAFE_RANGE,
    DIR_UP,
    DBL_DASH
};
```

`SAFE_RANGE == QK_USER == QK_USER_0 == 0x7E40` in the Keychron fork (`/Users/dexter/code/qmk-keychron/quantum/quantum_keycodes.h:37`, `quantum/keycodes.h:758-760`). Therefore, in **every** version:

| V10 Max keycode | Value | Dactyl name | Behaviour |
|---|---|---|---|
| `QK_USER_0` | 0x7E40 | `DOT_SLS` | types `./` (KC_DOT then KC_SLSH) |
| `QK_USER_1` | 0x7E41 | `DIR_UP` | types `../` (KC_DOT, KC_DOT, KC_SLSH) |
| (`QK_USER_2`) | 0x7E42 | `DBL_DASH` (LM/DS only) | types `--` (KC_MINS twice). **Absent from the V10 Max keymap.** |

Placement matches: `_LOWER` `, .` slots hold `DOT_SLS, DIR_UP` (V10 layer 1 `QK_USER_0, QK_USER_1`), `_LEADR` `.` slot holds `DOT_SLS` (V10 layer 5 `QK_USER_0`).

### `process_record_user` — LM (lines 555-666), behaviour-bearing code only

```c
bool process_record_user(uint16_t keycode, keyrecord_t *record)
{
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

    // Only run the following logic on 'donwstrokes' of key presses
    if (record->event.pressed)
    {
        if (keycode == KC_CAPS && !(host_keyboard_led_state().caps_lock))
        {
            rgblight_set_layer_state(3, true); // Caps =

            return true;
        }
        else if (keycode == KC_CAPS && (host_keyboard_led_state().caps_lock))
        {
            rgblight_set_layer_state(3, false);

            return true;
        }

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
```

Lines 558-616 of LM are commented-out remnants of an OSM "unlock" experiment (`check_unlock_osm`, `held_osm[]`, lines 499-553 — defined but **never called**; dead code that LTO drops).

`09bf` (lines 570-670) is the same minus the `DBL_DASH` branch, and the `DOT_SLS`/`DIR_UP` tests are plain `if` rather than `else if` (functionally identical).

### `process_record_user` — DS (lines 722-873), additions over LM

Leader-on-TD intercept (lines 730-743):

```c
    if (record->event.pressed && leader_sequence_active() && !leader_sequence_timed_out())
    {
        uint16_t base = td_base_keycode(keycode);
        if (base != KC_NO)
        {
            if (!leader_sequence_add(base))
            {
                leader_end();
                return true;
            }
            leader_reset_timer();
            return false;
        }
    }
```

Fast-typing detector (lines 771-790):

```c
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
        }
    }
```

Caps handling replaced (lines 827-835):

```c
        if (keycode == KC_CAPS)
        {
            caps_state = !caps_state;
            if (caps_state) layer_on(_CAPSIND);
            else layer_off(_CAPSIND);
            return true;
        }
```

`DOT_SLS`/`DIR_UP`/`DBL_DASH` branches (lines 839-869) are byte-for-byte the LM ones. Helpers `is_td_key` (665-701) and `td_base_keycode` (704-720) are switch statements over the ten `TD(...)` keycodes.

## 3. Tap dances

### Enums

`LM` lines 42-50 (`09bf` identical, lines 41-49):

```c
enum tap_dance_keys {
    LAYR_DOWN,
    LAYR_UP,
    TD_F_OSM,
    TD_J_OSM,
    TD_S_OSM,
    TD_H_CAPS,
    TD_G_CAPS
};
```

`DS` lines 63-74:

```c
enum tap_dance_keys {
    LAYR_DOWN,
    LAYR_UP,
    TD_S_OSM,     // shift OSM - on S key
    TD_J_OSM,
    TD_D_OSM,     // alt OSM - on D key
    TD_H_CAPS,
    TD_G_CAPS,
    TD_V_TAB,
    TD_Q_TILD,
    TD_Z_GRV
};
```

**`TD(0)` = `TD(LAYR_DOWN)` in all versions** (0x5700). On the dactyl it sits on the D key (`LM`) / F key (`DS`) of `_QWERTY`, and on a thumb of `_LOWER` and `_MOUSE` — the same three layers where the V10 Max has `TD(0)` (layers 0, 1, 4, on the Fn key next to the space bar).

State machine types (`LM` 21-33, `DS` 42-54):

```c
typedef enum {
    TD_NONE,        // 0
    TD_UNKNOWN,     // 1
    TD_SINGLE_TAP,  // 2
    TD_SINGLE_HOLD, // 3
    TD_DOUBLE_TAP,  // 4
    TD_TRIPLE_TAP,  // 5
} td_state_t;

typedef struct {
    bool is_press_action;
    td_state_t state;
} td_tap_t;
```

### Action table

`LM` lines 865-873:

```c
tap_dance_action_t tap_dance_actions[] = {
    [LAYR_DOWN] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, layr_dn_finished, layr_dn_reset),
    [LAYR_UP] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, layr_up_finished, layr_up_reset),
    [TD_F_OSM]  = ACTION_TAP_DANCE_FN_ADVANCED(NULL, osm_finished, osm_reset),
    [TD_J_OSM]  = ACTION_TAP_DANCE_FN_ADVANCED(NULL, osm_finished, osm_reset),
    [TD_S_OSM]   = ACTION_TAP_DANCE_FN_ADVANCED(NULL, osm_finished, osm_reset),
    [TD_H_CAPS]  = ACTION_TAP_DANCE_FN_ADVANCED(NULL, osm_finished, osm_reset),
    [TD_G_CAPS]  = ACTION_TAP_DANCE_FN_ADVANCED(NULL, osm_finished, osm_reset),
};
```

`09bf` lines 863-871: same but `[TD_H_CAPS] = ACTION_TAP_DANCE_DOUBLE(KC_H, KC_CAPS)`, `[TD_G_CAPS] = ACTION_TAP_DANCE_DOUBLE(KC_G, KC_CAPS)` (this is the "caps_lock tap via custom function" change in the LM commit message).

`DS` lines 1172-1183: every entry uses `ACTION_TAP_DANCE_FN_ADVANCED(on_each_tap_fn, <finished>, <reset>)` — `on_each_tap` is non-NULL (the fast-typing pass-through).

### user_data

`LM` lines 400-420:

```c
extern tap_dance_action_t tap_dance_actions[];
typedef struct {
    uint16_t keycode;
} td_osm_data_t;
static td_osm_data_t f_data = {KC_F};
static td_osm_data_t j_data = {KC_J};
static td_osm_data_t s_data = {KC_S};
static td_osm_data_t d_data = {KC_D};
static td_osm_data_t g_data = {KC_G};
static td_osm_data_t h_data = {KC_H};

void keyboard_post_init_user(void)
{
    tap_dance_actions[TD_F_OSM].user_data = &f_data;
    tap_dance_actions[TD_J_OSM].user_data = &j_data;
    tap_dance_actions[TD_S_OSM].user_data = &s_data;
    tap_dance_actions[LAYR_DOWN].user_data = &d_data;
    tap_dance_actions[TD_G_CAPS].user_data = &g_data;
    tap_dance_actions[TD_H_CAPS].user_data = &h_data;
    ...
```

`DS` lines 463-489: adds `v_data {KC_V}`, `q_data {KC_Q}`, `z_data {KC_Z}`, `k_data {KC_K}`; `LAYR_DOWN` gets `&f_data`, `LAYR_UP` gets `&k_data`, `TD_D_OSM` gets `&d_data`.

### `cur_dance`

`LM` lines 669-684 (`09bf` 674-689 identical except `state->count == 3` instead of `> 2`):

```c
td_state_t cur_dance(tap_dance_state_t *state) {
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
```

`DS` lines 887-907 prepends:

```c
    if (fast_typing_active && !td_in_progress)
    {
        return TD_UNKNOWN;
    }
```

### LAYR_DOWN (TD index 0) — the dance the V10 Max `TD(0)` almost certainly is

Statics (`LM` 61-64):

```c
static void layer_move_toLower(void);
static void layer_oneshot_Lower(void);
static uint8_t return_to_mouse = 0;
static uint8_t move_to_lower = 0;
```

Helpers (`LM` 745-756):

```c
static void layer_move_toLower(void)
{
  layer_clear();
  layer_move(_LOWER);
}

static void layer_oneshot_Lower(void)
{
  layer_on(_LOWER);
  set_oneshot_layer(_LOWER, ONESHOT_START);
  clear_oneshot_layer_state(ONESHOT_PRESSED);
}
```

Finished / reset (`LM` 759-826; `09bf` 764-831 identical):

```c
void layr_dn_finished(tap_dance_state_t *state, void *user_data) {
    td_osm_data_t *data = (td_osm_data_t *)user_data;
    layr_dn_tap_state.state = cur_dance(state);
    switch (layr_dn_tap_state.state) {
        case TD_SINGLE_TAP:
            register_code(data->keycode);
            unregister_code(data->keycode);
            break;
        case TD_DOUBLE_TAP:
            // if we are currently on MOUSE get it out of the way to go "down"
            if (layer_state_is(_MOUSE))
            {
              return_to_mouse = 1;
              layer_clear();
              layer_oneshot_Lower();
            }
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
            break;
        case TD_SINGLE_HOLD:
                layer_clear();
                layer_move(_MOUSE);
            break;
        case TD_TRIPLE_TAP:
            layer_move_toLower();
            break;
        default:
            break;
    }
}

void layr_dn_reset(tap_dance_state_t *state, void *user_data) {
    layr_dn_tap_state.state = TD_NONE;
}
```

Summary of LAYR_DOWN semantics (LM/09bf):

| Gesture | Effect |
|---|---|
| single tap | tap `user_data->keycode` (KC_D on the dactyl; on the V10 Max Fn key the user_data is unknown — check the disassembly: NULL user_data would dereference address 0, so expect either a different constant, a different pointer, or an empty branch) |
| single hold (not interrupted) | `layer_clear(); layer_move(_MOUSE)` → layer_state = 0x10, **sticky** (no `layer_off` in reset) |
| double tap, from `_MOUSE` | `return_to_mouse = 1; layer_clear();` one-shot `_LOWER`; when the one-shot ends, `oneshot_layer_changed_user` moves back to `_MOUSE` |
| double tap, elsewhere, first time | `move_to_lower = 1;` one-shot `_LOWER` (layer_on(1), `set_oneshot_layer(1, ONESHOT_START)`, `clear_oneshot_layer_state(ONESHOT_PRESSED)`) |
| double tap again immediately (flag still set, i.e. no other key pressed in between — `process_record_user` clears `move_to_lower` on any non-`TD(LAYR_DOWN)` key) | `layer_move_toLower()` → **layer lock** ("moved to") `_LOWER`: `layer_clear(); layer_move(_LOWER)` → layer_state = 0x02 |
| double tap while already on locked `_LOWER` | `layer_clear();` then one-shot `_LOWER` (unlocks into a one-shot) |
| triple tap (count > 2) | `layer_move_toLower()` — lock `_LOWER` directly |

"Layer lock" is therefore not a QMK feature: it is `layer_move(_LOWER)` leaving `_LOWER` as the only active layer; it is released by any `TO(_QWERTY)` key (`TO(0)` on V10 layers 1-5) or by the dance above. `DS` adds an explicit `lower_locked` flag (lines 99, 987-995, 521-541) purely for the indicator.

`oneshot_layer_changed_user` (`LM` 692-711, `DS` 925-944 identical):

```c
void oneshot_layer_changed_user(uint8_t layer) {
  if (!layer)
  {
    if (return_to_mouse)
    {
      layer_clear();
      layer_move(_MOUSE);
      return_to_mouse = 0;
    }
  }
}
```

`DS` `layr_dn_finished` (1005-1067) differs only in: `TD_SINGLE_TAP` → `tap_code(KC_F)` (hard-coded, user_data ignored), an explicit empty `TD_UNKNOWN` case, and `layr_dn_reset` also sets `td_in_progress = false` (1081). `DS` `layer_move_toLower` (987-995) adds `lower_locked = 1; layer_state_set(layer_state);`.

### LAYR_UP (TD index 1)

`LM` 713-743:

```c
void layr_up_finished(tap_dance_state_t *state, void *user_data)
{
    layr_dn_tap_state.state = cur_dance(state);   // NB: shares LAYR_DOWN's state var in LM
    switch (layr_dn_tap_state.state)
    {
        case TD_SINGLE_TAP:
            register_code(KC_K);
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
        default:
            break;
    }
}

void layr_up_reset(tap_dance_state_t *state, void *user_data)
{
    if (layr_dn_tap_state.state == TD_SINGLE_TAP)
    {
        unregister_code(KC_K);
    }
    layr_dn_tap_state.state = TD_NONE;
}
```

`DS` 946-985: own `layr_up_tap_state`, `tap_code(KC_K)` on single tap, no unregister in reset, `td_in_progress = false`. Not present on the V10 Max (only `TD(0)` is used).

### OSM/caps dances (indices 2-6, `osm_finished`/`osm_reset`)

`LM` 828-863:

```c
void osm_finished(tap_dance_state_t *state, void *user_data)
{
    td_osm_data_t *data = (td_osm_data_t *)user_data;
    if (state->count == 1)
    {
        register_code(data->keycode);
    }
    else if (state->count >= 2)
    {
       switch (data->keycode)
        {
            case KC_S:
                set_oneshot_mods(MOD_LALT);
                break;
            case KC_F:
            case KC_J:
                set_oneshot_mods(MOD_LSFT);
                break;
            case KC_G:
            case KC_H:
                tap_code(KC_CAPS);
                break;
            default:
                break;
        }
    }
}

void osm_reset(tap_dance_state_t *state, void *user_data)
{
    td_osm_data_t *data = (td_osm_data_t *)user_data;
    if (state->count == 1)
    {
        unregister_code(data->keycode);
    }
}
```

`09bf` 833-861: `count == 2` only; `KC_S → MOD_LALT`, everything else → `MOD_LSFT`; G/H used `ACTION_TAP_DANCE_DOUBLE`.

`DS` 1084-1170 uses `cur_dance`; double tap: `KC_D → set_oneshot_mods(MOD_LALT)`, `KC_S/KC_J → MOD_LSFT`, `KC_G/KC_H → tap_code(KC_CAPS)` + toggle `caps_state`/`_CAPSIND`, `KC_V → tap_code(KC_TAB)`, `KC_Q → tap_code16(KC_TILD)`, `KC_Z → tap_code(KC_GRV)`; triple tap on D toggles an **alt mod-lock**:

```c
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
                layer_state_set(layer_state);
            }
            break;
```

`DS` fast-typing pass-through (`on_each_tap_fn`, 875-884):

```c
void on_each_tap_fn(tap_dance_state_t *state, void* user_data)
{
    td_osm_data_t *data = (td_osm_data_t *)user_data;

    if (fast_typing_active && !td_in_progress)
    {
        tap_code(data->keycode);
    }
}
```

### ONESHOT handling

* `ONESHOT_TAP_TOGGLE 2` in all three config.h versions (`CL` line 82, `CD` line 114): tapping any `OSL(...)`/`OSM(...)` key twice **locks** it (`OSL(5)` on the V10 Max grave key double-tapped = locked `_LEADR`; `OSM(MOD_LSFT)` double-tapped = locked shift), one more tap unlocks. `ONESHOT_TIMEOUT` is commented out (no timeout).
* The tap dances create one-shot layers manually with `layer_on(L); set_oneshot_layer(L, ONESHOT_START); clear_oneshot_layer_state(ONESHOT_PRESSED);` (`ONESHOT_START = 0b11`, `ONESHOT_PRESSED = 0b01` — `qmk-keychron/quantum/action_util.h:81`).
* OSM indicator hooks (`LM` 450-497; `DS` 559-607): `oneshot_mods_changed_user` and `oneshot_locked_mods_changed_user` both call `handle_oneshots(mods)` which flips `shift_active`/`gui_active` (`DS`: also `alt_active`) and RGB layers 6/1 (`DS`: `RGB_CAPS`/`RGB_ALT_MOD`). Pure indicator logic; on the V10 Max (RGB matrix, no rgblight layers) expect either nothing or a flag-only version.

## 4. Leader key

`LM` lines 138-216 (the fullest set; **best reference for the V10 Max**, whose Sway-era origin matches these sequences):

```c
void leader_start_user(void) {
  leader_active = 1;
  rgblight_set_layer_state(4, true);
}

void leader_end_user(void) {
    // Clean up visual state
    rgblight_set_layer_state(4, false);
    leader_active = 0;

// Global search (Cmd+P, Cmd+K)
    if (leader_sequence_one_key(KC_S))
    {
        tap_code16(LGUI(KC_P));
        tap_code16(LGUI(KC_K));
    }
    // Control+H
    else if (leader_sequence_one_key(KC_H))
    {
        tap_code16(LCTL(KC_H));
    }
    // Copy (Ctrl+Shift+C)
    else if (leader_sequence_one_key(KC_C))
    {
        tap_code16(LCTL(LSFT(KC_C)));
    }
     // Quit minicom (Ctrl+A, Ctrl+Z, Ctrl+Q, Enter)
    else if (leader_sequence_one_key(KC_R))
    {
        // tap_code16(LCTL(KC_A));
        tap_code(KC_R);
        // tap_code(KC_Q);
        // tap_code(KC_ENT);
    }
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
    else if (leader_sequence_one_key(KC_J))
    {
        tap_code16(LGUI(KC_P));
    }
    // SWAY: Move focus to left split (Cmd+')
    else if (leader_sequence_one_key(KC_F))
    {
        tap_code16(LGUI(KC_QUOT));
    }
    // Diagonal virtual desktop move (Cmd+Up+Left)
    else if (leader_sequence_one_key(KC_DEL))
    {
        register_code(KC_LGUI);
        register_code(KC_UP);
        register_code(KC_LEFT);
        unregister_code(KC_LEFT);
        unregister_code(KC_UP);
        unregister_code(KC_LGUI);
    }
}
```

`09bf` lines 146-215: identical to LM.

`DS` lines 204-274: only **H** (`LCTL(KC_H)`), **A Q** (minicom quit), **Y** (nano save+quit) and **LCTL I** (`LCA(KC_I)`) remain active; S, C, J, F, DEL are commented out; `rgblight_set_layer_state(RGB_LEADER, ...)`.

Sequence table (LM/09bf):

| Sequence | Action | Keycodes tapped (hex) |
|---|---|---|
| `S` | `tap_code16(LGUI(KC_P)); tap_code16(LGUI(KC_K));` | 0x0813, 0x080E |
| `H` | `tap_code16(LCTL(KC_H))` | 0x010B |
| `C` | `tap_code16(LCTL(LSFT(KC_C)))` | 0x0306 |
| `R` | `tap_code(KC_R)` | 0x15 |
| `A Q` | `LCTL(KC_A)`, `Z`, `Q`, `ENT` | 0x0104, 0x1D, 0x14, 0x28 |
| `Y` | `LCTL(KC_X)`, `Y`, `ENT` | 0x011B, 0x1C, 0x28 |
| `LCTL I` | `tap_code16(LCA(KC_I))` | 0x050C |
| `J` | `tap_code16(LGUI(KC_P))` | 0x0813 |
| `F` | `tap_code16(LGUI(KC_QUOT))` | 0x0834 |
| `DEL` | register LGUI, UP, LEFT; unregister LEFT, UP, LGUI | 0xE3, 0x52, 0x50 |

Leader config (all versions; `CL` 76-79, `CD` 108-111): `LEADER_PER_KEY_TIMING` defined, `LEADER_TIMEOUT 600` (QMK default is 300 — `qmk-keychron/quantum/leader.c:11`), `LEADER_ENABLE` comes from rules.mk. `QK_LEAD` lives on the `_LEADR` layer only (reached with `OSL(_LEADR)`), as on the V10 Max (`QK_LEADER` = 0x7C58 on layer 5 grave).

Core detail useful for the disassembly: `leader_sequence_one_key(kc)` → `leader_sequence_five_keys(kc,0,0,0,0)` compares a 5-entry `uint16_t leader_sequence[5]` global (`leader.c:17,80`); `leader_end_user` therefore compiles to a chain of 16-bit compares of `leader_sequence[0]` (and `[1]`) against the constants above.

## 5. config.h and rules.mk

### config.h — `CL` = local-macos (`config_local-macos.h`), `C09` = 09bf, `CD` = dexter-ds

| Define | 09bf | LM | DS | QMK default |
|---|---|---|---|---|
| `TAPPING_TERM` | **150** (C09:54) | **140** (CL:54) | **300** (CD:65) | 200 |
| `TAPPING_TERM_PER_KEY` | defined (C09:55) | commented (CL:55) | commented (CD:72) | — |
| `PERMISSIVE_HOLD` | not present | not present | commented (CD:70) | off |
| `HOLD_ON_OTHER_KEY_PRESS` | not present | not present | commented (CD:71) | off |
| `QUICK_TAP_TERM` | — | — | commented `145` (CD:66) | = TAPPING_TERM |
| `FLOW_TAP_TERM` | — | — | **225** (CD:67) | off |
| `FAST_TYPING_THRESHOLD` | — | — | `FLOW_TAP_TERM` = 225 (CD:69) | user define |
| `TAPPING_TOGGLE` | not set | not set | not set | 5 |
| `ONESHOT_TAP_TOGGLE` | **2** (C09:81) | **2** (CL:82) | **2** (CD:114) | 5 |
| `ONESHOT_TIMEOUT` | commented `1000` | commented (CL:83) | commented (CD:115) | none |
| `LEADER_PER_KEY_TIMING` | defined (C09:77) | defined (CL:78) | defined (CD:110) | off |
| `LEADER_TIMEOUT` | **600** (C09:78) | **600** (CL:79) | **600** (CD:111) | 300 |
| `COMBO_*` | none (`EXTRA_SHORT_COMBOS` defined C09:52, no combos) | `EXTRA_SHORT_COMBOS` commented (CL:52) | commented (CD:63) | — |
| `DEBOUNCE` | not set (board default 5) | not set | not set | 5 |
| `NO_ACTION_MACRO` / `NO_ACTION_FUNCTION` | defined | defined (CL:27-28) | defined (CD:27-28) | — |
| `LOCKING_SUPPORT_ENABLE` / `LOCKING_RESYNC_ENABLE` | `#undef` | `#undef` (CL:47-48) | `#undef` (CD:58-59) | — |
| `LAYER_STATE_16BIT` | — | — | defined (CD:33) | 32-bit |
| `RGBLIGHT_DEFAULT_MODE 1`, `#undef RGBLIGHT_ANIMATION`, `RGBLIGHT_LAYERS` | yes | yes (CL:38-40) | yes (CD:43-45) | — |
| `RGBLED_SPLIT {12, 12}` | yes | yes (CL:43) | intentionally **not** defined (CD:49-53); `RGBLIGHT_MAX_LAYERS 9` (CD:54) | — |
| `MK_KINETIC_SPEED` | yes | yes (CL:87) | yes (CD:119) | off |
| `MOUSEKEY_MOVE_DELTA` | 45 | 45 (CL:88) | 45 (CD:120) | 16 |
| `MOUSEKEY_INITIAL_SPEED` | 30 | 30 (CL:89) | 30 (CD:121) | 100 |
| `MOUSEKEY_BASE_SPEED` | 1500 | 1500 (CL:90) | 1500 (CD:122) | 5000 |
| `MOUSEKEY_INTERVAL` | 40 | 40 (CL:92) | 40 (CD:124) | 16/20 |
| `MOUSEKEY_DELAY` | 1 | 1 (CL:94) | 1 (CD:126) | 10 |
| `MOUSEKEY_WHEEL_BASE_MOVEMENTS` | 32 | 32 (CL:95) | 192 (CD:130) | 32 |
| `MOUSEKEY_WHEEL_INITIAL_MOVEMENTS` | 64 | 64 (CL:96) | 5 (CD:129) | 16 |
| `MOUSEKEY_WHEEL_ACCELERATED_MOVEMENTS` | 50 | 50 (CL:97) | commented 128 (CD:132) | 48 |
| Split/serial | `MASTER_LEFT`, `SPLIT_USB_DETECT`, `SPLIT_USB_TIMEOUT 2500`, `SPLIT_LAYER_STATE_ENABLE`, `SPLIT_LED_STATE_ENABLE`, `SPLIT_MODS_ENABLE`, `SPLIT_OLED_ENABLE`, `SELECT_SOFT_SERIAL_SPEED 0`, `SPLIT_MAX_CONNECTION_ERRORS 50` | + `SERIAL_USART_TIMEOUT 10` (CL:74) | `SELECT_SOFT_SERIAL_SPEED 5`, `FORCED_SYNC_THROTTLE_MS 50` (CD:103-104) | n/a for V10 Max |
| OLED | `OLED_BRIGHTNESS 254`, `OLED_DISPLAY_HEIGHT 32`, `OLED_UPDATE_INTERVAL 50`, `OLED_TIMEOUT 300000` | same (CL:58-66) | + custom font `OLED_FONT_START 32`, `OLED_FONT_END 90` (CD:76-79) | n/a |

The LM commit's "tweaking some timings and serial config" = `TAPPING_TERM 150→140`, drop `TAPPING_TERM_PER_KEY`, drop `EXTRA_SHORT_COMBOS`, add `SERIAL_USART_TIMEOUT 10` (see `git diff 09bf262a04 45864d21f7`). No `get_tapping_term()` exists in any version even though `TAPPING_TERM_PER_KEY` was defined in 09bf.

### rules.mk

`09bf` (14 lines):

```make
RGBLIGHT_ENABLE = yes
OLED_ENABLE = yes
LEADER_ENABLE = yes
MOUSEKEY_ENABLE = yes
TAP_DANCE_ENABLE = yes
SPLIT_KEYBOARD = yes
CONSOLE_ENABLE = no
COMMAND_ENABLE = no
SPACE_CADET_ENABLE = no
GRAVE_ESC_ENABLE = no
MAGIC_ENABLE = no
AUTO_SHIFT_ENABLE = no

LTO_ENABLE = yes
```

`LM` adds `NKRO_ENABLE = no`, `AUDIO_ENABLE = no`, `COMMAND_ENABLE = no` (dup), `KEY_LOCK_ENABLE = no` (lines 13-16). `DS` additionally `EXTRAKEY_ENABLE = yes` (line 6) and the LTO comment block (18-24). Note `MAGIC_ENABLE = no` on the dactyl, but the V10 Max keymap contains `QK_MAGIC_TOGGLE_NKRO` (0x7013) so MAGIC was **enabled** there (Keychron default).

## 6. Other hooks

| Hook | LM | DS |
|---|---|---|
| `keyboard_post_init_user` | 412-436: sets TD user_data pointers, `rgblight_layers = my_rgb_layers`, `rgblight_enable()`, 8× `rgblight_set_layer_state(n, false)`, `rgblight_sethsv(94, 255, 50)` | 477-506: same idea, 10 user_data pointers, layer-state resets commented out |
| `layer_state_set_user` | 438-448: `rgblight_set_layer_state(0,_RAISE) (1,_RAISE2) (2,_LOWER) (7,_MOUSE) (5,_LEADR)`; returns state unchanged | 521-541: clears `lower_locked` when `_LOWER` is not in the new state, masks out/re-asserts phantom bits from `caps_state`/`alt_locked`/`lower_locked`, `apply_rgb_layer_state(state)` |
| `housekeeping_task_user` | none | 543-557: slave-side poller that re-applies RGB layer colours when `layer_state` changes |
| `matrix_scan_user` | none | none |
| `post_process_record_user` | none | none |
| `oneshot_layer_changed_user` | 692-711 (return-to-mouse, see §3) | 925-944 identical |
| `oneshot_mods_changed_user` / `oneshot_locked_mods_changed_user` | 479-497 → `handle_oneshots` (450-477) | 589-607 → `handle_oneshots` (559-587) |
| `oled_init_user` / `oled_task_user` | 218-331: rotation 270, banners `CAPS/SHFT/SWAY MODH/QLQL`, per-layer `QMK+ / ---- / ++++ / 2222 / MMMM / LLLL / ERR!` | 276-396: same plus `LOCK` variants and phantom-mask |
| RGB layer segments | 335-397: 8 full-strip segments `{0, 24, HSV_*}` (blue, yellow, green, goldenrod, pink, red, white, teal) | 399-458: 9 segments (adds `HSV_PURPLE`), `enum rgb_layer` 30-40 |
| Caps lock handling | `process_record_user` toggles RGB layer 3 on `KC_CAPS` press based on `host_keyboard_led_state().caps_lock` (617-628); `osm_finished` G/H double tap → `tap_code(KC_CAPS)` ("caps_lock tap via custom function", replaces `ACTION_TAP_DANCE_DOUBLE(KC_x, KC_CAPS)` of 09bf) | `caps_state` flag toggled by `KC_CAPS` press and by G/H double tap, mirrored to `_CAPSIND` phantom layer (827-835, 1104-1110) |
| "Double dash" | `DBL_DASH` custom keycode (LM commit) — **not in V10 Max** | same |
| Dead code | `find_osm_slot`/`check_unlock_osm` (499-553) defined, never called; `held_osm[]` (66) | commented out (609-663) |

None of the OLED/rgblight code applies to the V10 Max (RGB matrix, no OLED); if the V10 Max keymap kept indicator logic it would be in `rgb_matrix_indicators_user`/`rgb_matrix_indicators_advanced_user`, which no dactyl version implements.

Commit-message evolution (dexter-ds): `252629a1ba` initial DS port (fast-typing detector, `TD_V_TAB`, `TD_Q_TILD`, alt mod-lock, custom OLED font), `9edf216c91` right-side colours with LTO, `a846a2eb6d` caps phantom layer, `96473add2d` alt-lock/lower-lock phantom layers, `512bcdc3dc` mouse-wheel speed + right-thumb remap, `99b8e99bb7` leader sequences on TD keys (`td_base_keycode` intercept), `9513f800d7` thumb-cluster remap, `1cdd0c99cd` `KC_F4 → LCTL(KC_0)` on `_LOWER`, `bfec63fcc9` `TD_Z_GRV`.

## 7. What to expect in the V10 Max binary

Target: STM32F401 (Cortex-M4, Thumb-2; `qmk-keychron/keyboards/keychron/v10_max/info.json:6`), board `debounce: 20` (`info.json:76`), `ENCODER_MAP_KEY_DELAY 2`. Keychron keymaps wrap `process_record_user` around `process_record_keychron_common()` (stock keymap.c:71-72), so expect the user's `process_record_user` to call that first or last.

Most likely ported functions/behaviours (pre-09bf generation):

1. **`process_record_user`** with `DOT_SLS`/`DIR_UP` branches: compares against **0x7E40** and **0x7E41**, then `register_code/unregister_code` pairs with **KC_DOT = 0x37** and **KC_SLSH = 0x38** (`./` = 0x37,0x38; `../` = 0x37,0x37,0x38). No **0x7E42**/`KC_MINS 0x2D` double-tap sequence (no `DBL_DASH`) — if a `0x2D,0x2D` sequence *is* present, the binary is newer than assumed. Also look for the `move_to_lower`/`return_to_mouse` flag clears: a compare against **TD(0) = 0x5700** and a `layer_state & 0x2` (`layer_state_is(_LOWER)`) test at the top of the function. A `KC_CAPS = 0x39` compare reading `host_keyboard_led_state()` may or may not survive (its only effect was rgblight).
2. **`tap_dance_actions[]`**: with `TD(0)` only, expect a 1-entry (possibly 7-entry with unused slots) array of `tap_dance_action_t` — on ARM each entry is 28 bytes: `tap_dance_state_t` (6 bytes + 2 pad: `interrupting_keycode u16, count u8, weak_mods u8, oneshot_mods u8, bitfield u8`), then `fn.on_each_tap`, `fn.on_dance_finished`, `fn.on_reset`, `fn.on_each_release` (4 pointers), then `user_data`. For LM-style `ACTION_TAP_DANCE_FN_ADVANCED(NULL, layr_dn_finished, layr_dn_reset)` the first and fourth pointers are NULL. `user_data` is NULL in flash and set at runtime in `keyboard_post_init_user` (store of a RAM address into `tap_dance_actions[0].user_data`, offset +24).
3. **`cur_dance`** (probably inlined into `layr_dn_finished`): loads `count` (offset 2), tests `== 1`, then bitfield byte (offset 5) bits `pressed` (bit0) and `interrupted` (bit2); returns 2/3/1, `== 2` → 4, `> 2` → 5 (09bf: `== 3` → 5).
4. **`layr_dn_finished`** switch on the result: `TD_SINGLE_HOLD` → `layer_clear()` (`layer_state_set(0)`) then `layer_move(4)` (`layer_state_set(0x10)`); `TD_TRIPLE_TAP`/lock path → `layer_state_set(0)` then `layer_state_set(0x2)`; `TD_DOUBLE_TAP` → `layer_state & 0x10` test, `layer_on(1)` (`layer_state_set(layer_state | 2)`), `set_oneshot_layer(1, 3)` and `clear_oneshot_layer_state(1)`, with two byte flags (`return_to_mouse`, `move_to_lower`) in `.bss`. `TD_SINGLE_TAP` → `register_code(data->keycode); unregister_code(...)` reading a u16 through `user_data` — or something else entirely on the V10 Max (Fn key). `layr_dn_reset` just zeroes a byte.
5. **`oneshot_layer_changed_user`**: `if (layer == 0 && return_to_mouse) { layer_state_set(0); layer_state_set(0x10); return_to_mouse = 0; }`.
6. **`leader_start_user` / `leader_end_user`**: chain of compares of the 5×u16 `leader_sequence` global against `KC_S 0x16`, `KC_H 0x0B`, `KC_C 0x06`, `KC_R 0x15`, `KC_A 0x04`+`KC_Q 0x14`, `KC_Y 0x1C`, `KC_LCTL 0xE0`+`KC_I 0x0C`, `KC_J 0x0D`, `KC_F 0x09`, `KC_DEL 0x4C`; actions call `tap_code16` with **0x0813, 0x080E, 0x010B, 0x0306, 0x0104, 0x011B, 0x050C, 0x0834** and `tap_code` with **0x15, 0x1D, 0x14, 0x28, 0x1C**, plus `register_code(0xE3/0x52/0x50)`. `leader_start_user` may reduce to a single byte store (`leader_active = 1`) or be empty.
7. **Timing constants**: `TAPPING_TERM` used by the tap-dance core (`tap_dance_task` compares `timer_elapsed(last_tap_time) > TAPPING_TERM`): expect **150 = 0x96** (09bf-era) or **140 = 0x8C** (LM) rather than the default **200 = 0xC8**; DS-only value **300 = 0x12C** would be a surprise. `LEADER_TIMEOUT` in `leader_sequence_timed_out`: **600 = 0x258** (default 300 = 0x12C). `ONESHOT_TAP_TOGGLE` **2**: in `action.c` the OSL/OSM handling compares the oneshot tap count against 2 (default 5). `FAST_TYPING_THRESHOLD 225 = 0xE1` and `timer_read32()` deltas would indicate the DS-era detector (not expected). Debounce **20** is board-level.
8. **Mousekeys**: `MK_KINETIC_SPEED` build → `mousekey.c` contains `MOUSEKEY_INITIAL_SPEED 30`, `MOUSEKEY_BASE_SPEED 1500 = 0x5DC`, `MOUSEKEY_MOVE_DELTA 45 = 0x2D`, `MOUSEKEY_INTERVAL 40`, `MOUSEKEY_DELAY 1`, wheel **32 / 64 / 50** (vs defaults 100 / 5000 / 16 / 16-20 / 10 / 32 / 16 / 48). Keychron stock builds do not use kinetic mode, so the presence of these constants confirms the config.h was carried over.
9. **`keyboard_post_init_user`**: on the dactyl it set `user_data` pointers and rgblight state; on the V10 Max expect just the `tap_dance_actions[0].user_data = &x_data` store (and possibly nothing else).
10. **Not expected** (dactyl-only): OLED code, `rgblight_*` calls, split hooks, `layer_state_set_user` (unless kept as a stub), `LAYR_UP`, the letter OSM/caps dances, `DBL_DASH`, `td_base_keycode`/`is_td_key`, phantom layers, `LAYER_STATE_16BIT` (V10 Max has 6 layers → default 8-bit/32-bit layer_state per Keychron config).
