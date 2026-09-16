# The `dexter` keymap

File: `keyboards/keychron/v10_max/ansi_encoder/keymaps/dexter/keymap.c` (+ `config.h`, `rules.mk`, `readme.md`).
User-facing details are in that `readme.md`; this is the agent-oriented map. Layer tables are
formatted to mirror the physical Alice layout (whitespace only; matrix-column aligned with a gap at the split).

## Layers (`enum layers`)
| # | name | role | indicator colour |
|---|---|---|---|
| 0 | `_QWERTY` | base (recovered). M1 = `GM_TOGG` | heatmap (none) |
| 1 | `_LOWER` | Ctrl-chords/arrows; `DOT_SLS`/`DIR_UP`; reached via one-shot from the Fn tap dance | green |
| 2 | `_RAISE` | symbols/F-keys; has `TO(_RAISE2)` | blue |
| 3 | `_RAISE2` | Keychron Fn: RGB, BT hosts, `QK_BOOTLOADER` on Esc | orange |
| 4 | `_MOUSE` | kinetic mouse keys; reached by holding the Fn tap dance | teal |
| 5 | `_LEADR` | leader key + chords | red |
| 6 | `_GAMING` | stock Windows base (added) | solid blue + blue heatmap |
| 7 | `_GAME_FN` | stock Windows Fn (added) | solid blue + blue heatmap |

Layer state is 16-bit (VIA off), so up to 16 layers are fine.

## Custom keycodes (`enum custom_keycodes`, base `SAFE_RANGE` == `QK_USER` == 0x7E40)
- `DOT_SLS` (0x7E40): types `./` (recovered).
- `DIR_UP` (0x7E41): types `../` (recovered).
- `GM_TOGG` (0x7E42): toggles gaming mode (added).
- Keychron keycodes (`keychron_common.h`, base `QK_KB_0`=0x7E00): `KC_LOPTN`…`KC_SIRI`, `BT_HST1..3`, `P2P4G`, `BAT_LVL` (0x7E0F). `process_record_user` calls `process_record_keychron_common` first, so these keep working.

## Recovered behaviors (faithful to the original dump)
- **Fn key = `TD(LAYR_DOWN)`** tap dance: tap = one-shot `_LOWER`; tap-tap (nothing between) = lock `_LOWER`; hold (~175 ms) = lock `_MOUSE`; double-tap = lock `_LOWER`. `TAPPING_TERM 175` (per-key), `ONESHOT_TAP_TOGGLE 2`.
- **Leader** (`QK_LEADER` on `_LEADR`, ~525 ms per key): F→Cmd+P,Cmd+K (and a second F binding→Cmd+', reproduced as-found); A,Q→Ctrl+A,Z,Q,Enter; Y→Ctrl+X,Y,Enter; LCtrl,I→Ctrl+Alt+I; J→Cmd+P; Del→Cmd+Up+Left.
- **One-shot mod indicators**: pending Shift → board white, pending GUI → yellow; caps-lock (from this kbd) → white.
- Note: the `_LOWER` copy/paste etc. send real **Ctrl** chords (`LCTL(x)`), relying on the macOS "Control→Command" per-keyboard remap for Mac copy/paste (see gotchas.md).

## Gaming mode (added)
- **M1 (`GM_TOGG`)** flips `gaming_mode` and `default_layer_set`s `_GAMING` (RAM-only, so reboot returns to `_QWERTY`; survives sleep).
- `_GAMING` = stock **Windows** base verbatim except: M1 = `GM_TOGG`, Fn thumb = `MO(_GAME_FN)`, right spacebar [5,9] = Enter, right B [4,8] = Backspace (last two mirror the non-gaming layers).
- `_GAME_FN` = stock Windows Fn (F-keys, media, RGB, Bluetooth).
- **RGB**: solid dark navy base with the live typing heatmap recoloured to slate-blue, drawn in `rgb_matrix_indicators_advanced_user` reading `g_rgb_frame_buffer` (the effect stays `RGB_MATRIX_TYPING_HEATMAP`; no EEPROM write). Tunable macros at the top of keymap.c: `GAME_OUTER_*` (6,6,55), `GAME_INNER_*` (45,85,175), `GAME_HEAT_GAIN` 3. Keep green well below blue or the LEDs read teal; set_color is raw PWM so these are literal brightness.

## Battery readout (added) — `BAT_LVL`
- Press: custom mode = tap **Fn** then the **right-B** key; gaming = **hold Fn** then a **B** key.
- **On battery** (wireless): green bar on the number-row LEDs (`BAT_LEVEL_LED_LIST`), length = `battery_get_percentage()/10`.
- **On USB**: full bar, **green = fully charged / red = charging** (read from `BAT_CHARGING_PIN`). A % is unreliable while charging, so charge state is shown instead.
- Static bar for `BATT_SHOW_MS` (3000 ms), no ramp. Keychron's native grow/blink animation is fully suppressed: `BAT_LVL` is swallowed in `process_record_user` on **both press and release** (the fork's native handler ignores press/release and would start its white ramp on the release).
- All in the keymap; no core edits. Uses `usb_power_connected()` (lpm.h) and `battery_get_percentage()` (battery.h).

## Auto-sleep / idle RGB (stock, unchanged — confirmed)
On battery, the board auto-sleeps (STM32 STOP) after the RGB idle timeout (~600 s connected /
~40 s disconnected); LEDs turn off at idle and come back on the first wake keypress. USB power
blocks sleep (`KEEP_USB_CONNECTION_IN_WIRELESS_MODE`). The keymap overrides none of this.
