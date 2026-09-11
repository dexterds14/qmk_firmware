/*
 * custom_code/rawhid_misc.c -- raw HID path / misc stock code, Keychron V10 Max dump (dump_a.bin)
 *
 * RESULT: there is NO user-written raw-HID code in this firmware. Everything on the raw HID
 * path is the Keychron fork's stock non-VIA build (keychron_common.c, factory_test.c, lkbt51.c,
 * tmk_core/protocol/chibios/usb_main.c). Do NOT add a raw_hid_receive() to keymap.c: in a
 * non-VIA build keychron_common.c already defines it (non-weak) and the link would fail.
 *
 * What the keymap MUST contribute to reproduce the dump is only configuration (below).
 *
 * ---------------------------------------------------------------------------------------------
 * keymaps/<name>/config.h  (lines implied by THIS target; other targets add their own)
 * ---------------------------------------------------------------------------------------------
 *   #pragma once
 *   #define TAPPING_TERM 175           // 0x0800DEFC: get_tapping_term() weak default = movs r0,#175
 *   #define TAPPING_TERM_PER_KEY       // get_tapping_term() is linked and called (0x0800E016, 0x0800E192, 0x080120EC)
 *   #define ONESHOT_TAP_TOGGLE 2       // process_action 0x0800D698 compares oneshot tap count against 2
 *   // ONESHOT_TIMEOUT: NOT defined (no 3000 immediate in action_util region) -- drop the 3000 used in refs/ref_feat_keymap
 *   // TAPPING_TOGGLE 5, TAP_HOLD_CAPS_DELAY 80, TAP_CODE_DELAY 0 are the defaults seen in process_action
 *   // RAW_HID_CMD is inherited from keyboards/keychron/v10_max/config.h: "0xAA ... 0xAB" (do not override to match the dump)
 *   // Source tree: fork commit 8e390f92a2 (2024-06-18) -- wireless_send_nkro 0x0800A33C still has the direct
 *   //   wireless_transport.send_nkro(&report->mods) call that 0c05eef6cd (2024-06-22) removed; everything else is
 *   //   identical to the pinned 1011db8c8d.
 *
 * ---------------------------------------------------------------------------------------------
 * keymaps/<name>/rules.mk  (implied)
 * ---------------------------------------------------------------------------------------------
 *   VIA_ENABLE = no          # raw_hid_receive is the #if !defined(VIA_ENABLE) variant, no dynamic keymap
 *   TAP_DANCE_ENABLE = yes   # process_tap_dance 0x08012040, tap_dance_actions[] 0x20000E7C
 *   LEADER_ENABLE = yes      # process_leader 0x080118F4
 *   MOUSEKEY_ENABLE = yes    # mousekey_on/off/task present (also default in info.json); the kinetic config lines
 *                            # (MK_KINETIC_SPEED, MOVE_DELTA 45, INITIAL_SPEED 30, BASE_SPEED 1500, INTERVAL 40, ...)
 *                            # are in custom_code/config_features.txt -- move_unit 0x08011A8C is the kinetic variant
 *   MAGIC_ENABLE = no        # default-on in the fork; process_magic absent, process_record_quantum 0x0800D3B6 calls only kb/tap_dance/leader/rgb
 *   GRAVE_ESC_ENABLE = no    # default-on in the fork; process_grave_esc absent
 *   SPACE_CADET_ENABLE = no  # default-on in the fork; process_space_cadet/perform_space_cadet absent, get_tapping_term has exactly 4 callers
 *   # RAW_ENABLE, ENCODER_MAP_ENABLE, NKRO, DIP_SWITCH, RGB_MATRIX, BOOTMAGIC come from the keyboard info.json
 *   # LK_WIRELESS_ENABLE, NO_USB_STARTUP_CHECK, FACTORY_TEST_ENABLE come from v10_max/rules.mk (wireless.mk, keychron_common.mk)
 *   # CONSOLE_ENABLE stays off (no console interface, protocol_post_task has no console_task)
 *
 * ---------------------------------------------------------------------------------------------
 * For reference only: what the dump executes on the raw HID path (stock fork code, reconstructed
 * from 0x08012C1C raw_hid_task, 0x0800C908 raw_hid_receive, 0x0800C874 via_command_kb,
 * 0x08012C0C raw_hid_send). These already exist in the fork tree; they are NOT to be compiled
 * into keymap.c and are kept inside this comment.
 *
 *   void raw_hid_task(void) {                                    // usb_main.c
 *       uint8_t buffer[RAW_EPSIZE];                              // 32
 *       while (receive_report(USB_ENDPOINT_OUT_RAW, buffer, sizeof(buffer)))   // &usb_endpoints_out[0] @0x20000EDC, EP2 OUT, 4x32 B
 *           raw_hid_receive(buffer, sizeof(buffer));
 *   }
 *   void raw_hid_receive(uint8_t *data, uint8_t length) {        // keychron_common.c, VIA_ENABLE undefined
 *       switch (data[0]) {
 *           case 0xAA ... 0xAB:                                  // RAW_HID_CMD from v10_max/config.h (LK_WIRELESS_ENABLE)
 *               via_command_kb(data, length);                    // => 0xA0..0xA3 and VIA 0x01.. are dropped here
 *               break;
 *       }
 *   }
 *   bool via_command_kb(uint8_t *data, uint8_t length) {         // keychron_common.c; 0xA0..0xA3 cases are dead in this build
 *       switch (data[0]) {
 *           case 0xA0: data[1] = 2; raw_hid_send(data, length); break;                       // PROTOCOL_VERSION
 *           case 0xA1: "v1.0.0 " + QMK_BUILDDATE "2024-07-09-13:57:36"; raw_hid_send(...); break;
 *           case 0xA2: data[2] = 0x07; raw_hid_send(...); break;                             // DEFAULT_LAYER|BLUETOOTH|P2P4G
 *           case 0xA3: data[1] = get_highest_layer(default_layer_state); raw_hid_send(...); break;
 *           case 0xAA: lkbt51_dfu_rx(data, length); break;                                   // BT module DFU (0x0800B290)
 *           case 0xAB: factory_test_rx(data, length); break;                                 // factory test (0x0800CB90)
 *           default: return false;
 *       }
 *       return true;
 *   }
 *   void raw_hid_send(uint8_t *data, uint8_t length) {           // usb_main.c
 *       if (length != RAW_EPSIZE) return;
 *       send_report(USB_ENDPOINT_IN_RAW /* index 2 -> EP2 IN */, data, length);
 *   }
 *
 * factory_test_rx(0xAB) checksum rule (0x0800CB9E..): sum16 = sum(data[1..28]); data[30] == sum & 0xFF; data[31] == sum >> 8.
 * Sub-commands present: 0x01 backlight, 0x02 os-switch report, 0x04 INT pin (0xA1/0xA2), 0x05 get transport (replies),
 * 0x07 radio carrier, 0x08 get build time (replies "v1.0.0 2024-07-09-13:57:36"), 0x09 get device id (replies 12 UID bytes).
 * Absent: 0x03 jump-to-bootloader (commented out in source), 0x06 charging ADC, 0x70 pressure test.
 *
 * OPTIONAL (not in the recovered firmware): to make a future build answer 0xA0..0xA3 without VIA, add to the
 * keymap config.h:  #undef RAW_HID_CMD   /  #define RAW_HID_CMD 0xA0 ... 0xAB
 */

#include QMK_KEYBOARD_H

/* Intentionally empty: this target contributes configuration only (see the header comment).
 * The compilable keymap.c for the recovered firmware is assembled from the other targets
 * (keymap table, tap dance, leader, process_record_user, rgb hooks, oneshot hooks). */
