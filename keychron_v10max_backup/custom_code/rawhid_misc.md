# Target: raw HID path, remaining unexplained code, compiled-in fork features

Dump: `keychron_v10max_backup/dump_a.bin` (flash 0x08000000). All addresses are flash/RAM addresses
in the dump unless marked *ref* (= `refs/ref1011_default.elf`, same fork commit, gcc 15.2).
Decompiled bodies: `decompiled/<addr>_<name>.c`; disassembly via
`arm-none-eabi-objdump -D -b binary -m arm -M force-thumb --adjust-vma=0x08000000`.

Verdict in one line: **the firmware services raw HID correctly (task wired, endpoints consistent), but
its `raw_hid_receive` only forwards commands 0xAA and 0xAB; 0xA0..0xA3 and every VIA command are
silently dropped.** That is (a) "firmware never answers those commands", and it is the *stock* behaviour
of the fork's non-VIA build, not a bug or a host-side failure.

---

## 1. Raw HID receive path

### 1.1 Call chain main -> raw_hid_receive (VERIFIED, every hop is a direct `bl`/`b.w`)

| step | dump addr | identity | evidence |
|---|---|---|---|
| main | 0x0800F084 | `main` | `bl 0x08012490 platform_setup; bl 0x08012C68 protocol_setup; bl 0x0800E740 keyboard_setup; bl 0x0800F060 protocol_init;` loop `bl 0x0800F072; bl 0x0800E76A; b.n` (0x0800F096..0x0800F09E) |
| loop body 1 | 0x0800F072 | `protocol_task` | `bl 0x08012CA4` (protocol_pre_task = 4-B thunk -> usb_event_queue_task 0x08012A98), `bl 0x0800E7B8` (keyboard_task, 240 B), `b.w 0x08012CA8` |
| loop body 2 | 0x0800E76A | `housekeeping_task` | `bl 0x0800C714` (housekeeping_task_kb, thunk -> keychron_task 0x0800C6D4) ; `bl 0x0800E768` (housekeeping_task_user, `bx lr`) |
| | 0x08012CA8 | `protocol_post_task` | `bl 0x08012C1C ; b.w 0x08013304 (usb_idle_task)` - identical shape to ref 0x08010A1C (`bl raw_hid_task; b.w usb_idle_task`). No `console_task`/`midi_ep_task` => CONSOLE/MIDI off |
| | 0x08012C1C | `raw_hid_task` | literal @0x08012C40 = **0x20000EDC** (= `&usb_endpoints_out[USB_ENDPOINT_OUT_RAW]`); `sub sp,#32; movs r2,#32; movs r3,#0` -> `bl 0x08013078 usb_endpoint_out_receive(ep, buf, 32, TIME_IMMEDIATE)`; `cbnz r0` -> `movs r1,#32; mov r0,sp; bl 0x0800C908` ; `b.n` back to the receive. Same structure as ref 0x08010994 (ref literal 0x20000E68 = ref `usb_endpoints_out`) |
| | **0x0800C908** | **`raw_hid_receive`** (keychron_common.c `#if !defined(VIA_ENABLE)` branch) | 14 bytes `78 03 3b aa 2b 01 d8 01 f7 ff bf b0 47 70` = `ldrb r3,[r0]; subs r3,#0xAA; cmp r3,#1; bhi 0x0800C914; b.w 0x0800C874; bx lr`. **Byte-identical** to ref `raw_hid_receive` @0x0800AC20. Only callers of 0x0800C874 are this function (0x0800C910) and its own `tbb` (ghidra_callgraph.json) |
| | 0x0800C874 | `via_command_kb` (named `kc_raw_hid_rx` in earlier reports) | `tbb` on `data[0]-0xA0` (12 cases): 0xA0 -> `data[1]=2` (PROTOCOL_VERSION) + `raw_hid_send`; 0xA1 -> `'v' itoa(1) '.' itoa(0) '.' itoa(0) ' '` + 20-B memcpy from 0x080167AC `"2024-07-09-13:57:36"` + `raw_hid_send` (= "v1.0.0 2024-07-09-13:57:36", DEVICE_VER 0x0100); 0xA2 -> `data[2]=7` (FEATURE_DEFAULT_LAYER|FEATURE_BLUETOOTH|FEATURE_P2P4G, written at data[2] because `get_support_feature(&data[1])` stores to `[1]` of its argument - same quirk as source); 0xA3 -> `data[1]=get_highest_layer(default_layer_state @0x20001630)`; 0xAA -> `lkbt51_dfu_rx` 0x0800B290; 0xAB -> `factory_test_rx` 0x0800CB90; default -> return 0 |
| | 0x08012C0C | `raw_hid_send` | `if (len==32) send_report(2, data, 32)`; `send_report` 0x08012BC4 -> `usb_endpoint_in_send(&usb_endpoints_in[2] (=0x20000F64+2*0xA8=0x200010B4), data, 32, 10000 ticks=100 ms, false)` |

Consequence (VERIFIED): with `data[0]` = 0xA0, 0xA1, 0xA2, 0xA3, or any VIA id (0x01..0x1F), `raw_hid_receive`
returns at 0x0800C914 without calling anything. The four "reply" cases inside `via_command_kb` are dead code
in this build. This is exactly what the fork source produces: `keyboards/keychron/v10_max/config.h:74`
`#define RAW_HID_CMD 0xAA ... 0xAB` (under `LK_WIRELESS_ENABLE`) and `keychron_common.c:202-208`
`#if !defined(VIA_ENABLE) void raw_hid_receive(...) { switch (data[0]) { case RAW_HID_CMD: via_command_kb(data, length); } }`.
Only Keychron's VIA builds answer 0xA0..0xA3 (VIA's `raw_hid_receive` routes unknown ids to `via_command_kb`).

### 1.2 OUT endpoint wiring is complete and consistent with a 32-byte RAW interface (VERIFIED)

USB descriptors in rodata (parsed by walking the configuration descriptor):

* Device descriptor @0x08017197: VID 0x3434, PID 0x09A0, bcdDevice 0x0100, EP0 64.
* Configuration descriptor @0x0801713C: wTotalLength 91, **3 interfaces**, bmAttributes 0xA0, 500 mA.
  * IF0 keyboard (boot, HID report 68 B): EP 0x81 IN INTR 8 B, interval 1.
  * **IF1 RAW** (class 03/00/00, HID report length **34**): **EP 0x82 IN INTR 32 B** and **EP 0x02 OUT INTR 32 B**, interval 1 (0x08017170 / 0x08017177).
  * IF2 shared (HID report 182 B): EP 0x83 IN INTR 32 B.
  * No console interface.
* RAW report descriptor @0x080171A9 (34 B): `06 60 FF 09 61 A1 01 09 62 15 00 26 FF 00 95 20 75 08 81 02 09 63 15 00 26 FF 00 95 20 75 08 91 02 C0` = usage page 0xFF60, usage 0x61, 32-byte input (0x62) and output (0x63) reports, no report id - standard QMK raw HID.

Endpoint tables (`.data`, init image at flash `0x0801774C + (RAM - 0x20000C00)`, constants from calibration.txt):

* `usb_endpoints_out[0]` RAM 0x20000EDC (init image 0x08017A28; the `config` sub-struct is at +0x70 = flash 0x08017A98, the first 0x70 bytes are zero): `ep_config` all zero (fork builds with `USB_ENDPOINTS_ARE_REORDERABLE`: the OUT half shares the IN entry's ep_config), `config.usbp` = 0x20004AE4 (&USBD1), **ep = 2, buffer_capacity = 4, buffer_size = 32**, buffer = 0x20002070, timed_out = 0. Ref image at 0x20000E68: `b44a0020 02000000 04000000 20000000 f41e0020` = same fields (ep 2, capacity 4, size 32).
* `usb_endpoints_in[]` RAM 0x20000F64, stride 0xA8 (from `send_report` 0x08012BC4: `0x20000F64 + idx*0xA8`): [0] shared: mode 3 INTR, in_max 32, ep 3; [1] keyboard: in_max 8, ep 1; **[2] RAW: mode 3, in_cb 0x08012ECB (`usb_endpoint_in_tx_complete_cb`), out_cb 0x08012F61 (`usb_endpoint_out_rx_complete_cb`), in_max 32, out_max 32, ep 2, is_shared 1** (RAM 0x200010B4, init 0x08017C00). Index 2 is exactly what `raw_hid_send` passes, and the enum order SHARED, KEYBOARD, RAW matches `usb_endpoints.h`.
* `init_usb_driver` 0x08012B50: `usb_endpoint_in_init/start` for 0x20000F64, 0x2000100C, 0x200010B4; **`usb_endpoint_out_init` 0x08012DE0 + `usb_endpoint_out_start` 0x08012E28 for 0x20000EDC** (`out_params[ep-1] = endpoint`, 0x08012E2E-0x08012E36); then usbStop, `chThdSleep(5000)` = 50 ms, `usbStart(usbp, &usbcfg @0x080170C4 -> usb_event_cb 0x080129B5)`.
* `usb_event_cb` 0x080129B4, case `USB_EVENT_CONFIGURED` (2): `usb_endpoint_in_configure_cb` 0x08012E94 (-> `usbInitEndpointI` 0x08014294) for the three IN entries (ep 2's entry carries the OUT size/callback, so EP2 OUT is initialised here), then **`usb_endpoint_out_configure_cb(0x20000EDC)` 0x08012EB4 = `ibqResetI` 0x08013D52 + `usb_start_receive` 0x08012D6A** (`usbStartReceiveI` 0x08014310 when `usbp->state == USB_ACTIVE` and the ep is not already receiving). `usb_endpoint_out_rx_complete_cb` 0x08012F60 re-arms via `usb_start_receive` @0x08012F96.
* `usb_endpoint_out_receive` 0x08013078: returns true only if `usbp->state == USB_ACTIVE (4)` and `ibqReadTimeout` 0x08013DF2 returned exactly `size` bytes.

So the OUT report reaches `raw_hid_task` -> `raw_hid_receive`; nothing is missing or disabled. The only filter is `data[0] in {0xAA,0xAB}`.

### 1.3 What the board *does* answer - a host-side probe that must work

`factory_test_rx` 0x0800CB90 (0xAB): verifies `sum(data[1..28]) & 0xFF == data[30]` and `sum >> 8 == data[31]`
(loop 0x0800CB9E.., matches factory_test.c:323-328), then `switch(data[1])`:
1 backlight test mode, 2 OS-switch reporting, 4 INT pin test (0xA1 -> `lkbt51_send_cmd(0x72 IO_TEST)`, 0xA2 -> write A4),
5 GET_TRANSPORT (reply: 5, `get_transport()`, `readPin(B0)`), 7 RADIO_CARRIER (`0x73` to lkbt51 if ch<79),
**8 GET_BUILD_TIME (reply "v1.0.0 2024-07-09-13:57:36")**, 9 GET_DEVICE_ID (reply 9, 12, UID @0x1FFF7A10/20/30).
Case 3 JUMP_TO_BL is absent (commented out in source), 6 CHARGING_ADC absent (`BATTERY_CHARGE_DONE_DETECT_ADC` undefined), 0x70 absent (`WERELESS_PRESSURE_TEST` undefined).
`factory_test_send` 0x0800CB44 builds `[0xAB, payload..., 0.., cksum_lo @30, cksum_hi @31]` and calls `raw_hid_send(buf, 32)`.

Probe (32 bytes, no report id; on macOS hidapi prepend a 0x00 report-id byte, i.e. write 33 bytes):

    AB 08 00*28 08 00      -> expect 32-byte reply: AB 08 'v' '1' '.' '0' '.' '0' ' ' "2024-07-09-13:57:36\0" 00.. <cksum lo> <cksum hi>
    AB 09 00*28 09 00      -> expect: AB 09 0C <12 UID bytes> ... cksum
    AB 05 00*28 05 00      -> expect: AB 05 <transport> <B0 level> ... cksum

Open the interface with usage_page 0xFF60 / usage 0x61 (IF1). If these probes also time out, the host path is at fault;
if they answer, the earlier 0xA0/0xA1/0x01 timeouts are fully explained by the firmware filter above.
Script (not executed here): `tools/rawhid_probe.py`.

### 1.4 0xAA path (BT module DFU) - present

`lkbt51_dfu_rx` 0x0800B290: requires `data[0]==0xAA`, `data[1] in {'U'(0x55),'V'(0x56)}`, `data[2] == ~data[3]` (len/~len), len < 28,
16-bit checksum over the payload, **and `(data[5] & 0xF0) == 0x60`** (0x0800B2EA-0x0800B2F8, lkbt51.c:666; other payloads are dropped without reply), then `lkbt51_wake()` 0x0800AA20 and `lkbt51_send_cmd(&data[5], len-2, data[1]=='V', !new_sn)` 0x0800AA64.
Replies come asynchronously from `lkbt51_dfu_tx` 0x0800AF8C (`[0x03,0xAA,0x57,len,~len,sn,rsp,data...]` via `raw_hid_send`, second packet when len>25) when the module sends `LKBT51_EVT_OTA_RSP`.

---

## 2. Remaining unnamed / ambiguous functions

Everything below is **stock fork/QMK/ChibiOS/newlib code**; no additional user code exists outside the
0x0800CCF0..0x0800D2CC translation unit already covered by the other targets.

### 2.1 Large functions

| dump | size | identity | confidence | evidence |
|---|---|---|---|---|
| 0x0800D698 | 1010 | `process_action` (quantum/action.c) | VERIFIED | sole caller `process_record_handler` 0x0800DAB4 (`ldrh r1,[r0]; ldrb r0,[r0,#5]; bl 0x0800DE10 store_or_get_action; bl 0x0800DCD8 layer_debug; bl 0x0800DBE0 default_layer_debug; b.w 0x0800D698`, ref size 0x22 = 34 B, identical). Body: switch on `action.kind.id` (bits 12-15): 0/1 LMODS/RMODS, 2/3 MODS_TAP, 4 USAGE (0x4000 system -> `host_system_send` 0x08012188, 0x4400 consumer -> `host_consumer_send` 0x080121B8), 5 MOUSEKEY (`register_mouse` 0x0800D55A), 8 LAYER bit-ops (`default_layer_or/and/xor/set`, `layer_or/and/xor/state_set`), 9 LAYER_MODS, 0xA/0xB LAYER_TAP(_EXT) with ops 0xF0 TAP_TOGGLE (`layer_invert`), 0xF1/0xF2 ON_OFF/OFF_ON, 0xF3 SET_CLEAR (`layer_clear`/`layer_move`), 0xF4 ONESHOT (`set_oneshot_layer` 0x0800E504, `reset_oneshot_layer` 0x0800E534, `clear_oneshot_layer_state` 0x0800E548). `keymap_config.oneshot_enable` = byte 0x200047D5 bit 2. Tap delay `chThdSleep(code==0x39 ? 8000 : 1)` = `wait_ms(TAP_HOLD_CAPS_DELAY 80)` / `wait_ms(TAP_CODE_DELAY 0)` at CH_CFG_ST_FREQUENCY 100000. Head test `(code <= MODS_TAP_TOGGLE || tap_count == 0)` for LMODS_TAP/RMODS_TAP matches fork action.c:377. 40/40 callees resolve to matched symbols. |
| 0x0800E8B0 | 432 | `action_for_keycode` (quantum/keymap_common.c) | VERIFIED | caller `action_for_key` 0x0800EA9E (matched). `keycode_config` 0x0800EAB4 first, then: <0xA5 -> ACTION_KEY; 0xA5..0xA7 -> 0x4000|(kc-0x24) system; 0xA8..0xC2 -> 0x4400|table consumer; 0xCD..0xDF -> 0x5000|kc mouse; 0x0100..0x1FFF -> MODS_KEY via `mod_config` 0x0800EBBC; 0x2000..0x3FFF -> MODS_TAP_KEY; 0x4000..0x4FFF -> LT 0xA000; 0x5000..0x51FF -> LM 0x9000; TO 0x5200 -> 0x8D00; MO 0x5220 -> 0xA0F1; DF 0x5240 -> 0x8C00; TG 0x5260 -> 0x8A00; OSL 0x5280 -> 0xA0F4; OSM 0x52A0 -> 0x2000|mods<<8; TT 0x52C0 -> 0xA0F0; else 0. |
| 0x0800A98C | 130 | `lkbt51_init(bool wakeup_from_low_power_mode)` | VERIFIED | `if (!arg)`: GPIOC pin 0x10 (**C4 = LKBT51_RESET_PIN**) output, BSRR reset (0x4002081A), `chThdSleep(100)` = `wait_ms(1)`, BSRR set (0x40020818). `if (SPID1.state @0x20004B50 == SPI_UNINIT)`: A5 output+high, A5/A6/A7 mode 0x282 = `PAL_MODE_ALTERNATE(5)` (SPI1), `spiInit` (thunk 0x0801410C -> 0x080163C8) with the early-return duplicate for `wakeup`. Then GPIOA pin 0x10 (**A4 = BLUETOOTH_INT_OUTPUT_PIN**) output+high, GPIOB pin 0x02 (**B1 = LKBT51_INT_INPUT_PIN**) mode 0x20 = `PAL_MODE_INPUT_PULLUP`. Matches lkbt51.c:179-211 and v10_max/config.h pins. Called `lkbt51_init(false)` from `keyboard_post_init_kb` 0x0800CD38 (`movs r0,#0; bl` @0x0800CD5C). |
| 0x0800A240 | 40 | `wireless_init` | VERIFIED | `wireless_state @0x20001501 = WT_INITIALIZED(1)`; `wireless_event_queue_init` 0x0800A1D8, `report_buffer_init` 0x0800A7CC, `indicator_init` 0x0800B328, `battery_init` 0x0800C058, `lpm_init` 0x0800BC8C, then tail `b.w 0x0800C488` = `rtc_timer_init` (4-byte thunk `b.w 0x0800C46C` = `rtc_timer_clear` -> `rtcSetTime` 0x08014104). Same order as wireless.c:88-105 with `BLUETOOTH_INT_INPUT_PIN` undefined. |
| 0x0800C810 | 84 | `encoder_cb_init` (keychron_common.c) | VERIFIED | `_pal_lld_enablepadevent(GPIOB, 15, 3)` and `(GPIOB, 14, 3)` = `palEnableLineEvent(B15/B14, BOTH_EDGES)`; `palSetLineCallbackI(B15/B14, 0x0800C719, NULL)`. ENCODERS_PAD_A B15, PAD_B B14 per info.json. Also called from `lpm_task` 0x0800BDCC @0x0800BE96 (re-init after low power). |
| 0x0800C718 | 6+54 | `encoder0_pad_cb` -> inlined `encoder_inerrupt_read(0)` (body split to 0x08011844) | VERIFIED | reads GPIOB IDR 0x40020410 bits 15/14, updates `encoder_state` 0x20001FF7 / `encoder_pulses` 0x20001FF6 via LUT 0x080170B4, sets flag 0x20001FF8 = 1. |

### 2.2 Keychron glue (keychron_task.c / v10_max.c) - all stock, order stock

| dump | identity | evidence |
|---|---|---|
| 0x0800C6E8 | `process_record_kb` | `process_record_user` 0x0800D104 first; only if true -> 0x0800C6A0. |
| 0x0800C6A0 | `process_record_keychron` | `process_record_wireless` 0x0800A788 && `process_record_factory_test` 0x0800C928 && `process_record_keychron_kb` 0x0800C69C (weak, `movs r0,#1; bx lr`). |
| 0x0800C6D4 / 0x0800C714 | `keychron_task` / `housekeeping_task_kb` (thunk) | `wireless_tasks` 0x0800B972, `factory_test_task` 0x0800CA84, `keychron_common_task` 0x0800C7DC (Siri: release 0xE3+0x2C after 500 ms), `keychron_task_kb` 0x0800CD88. Called from `housekeeping_task` 0x0800E76A before `housekeeping_task_user` 0x0800E768. |
| 0x0800C702 / 0x0800C6C6 | `rgb_matrix_indicators_kb` / `rgb_matrix_indicators_keychron` | `rgb_matrix_indicators_user` 0x0801017A (weak true) then `rgb_matrix_indicators_bt` 0x0800B4C4 + `factory_test_indicator` 0x0800CA18. Caller `rgb_matrix_task` 0x08011058. |
| 0x0800CD88 | `keychron_task_kb` | power-on LED **B12** (BSRR 0x40020418/0x4002041A, mask 0x1000) for 3000 ms from `power_on_indicator_timer` 0x200015D8. |
| 0x0800CDB8 | `lpm_is_kb_idle` | `timer==0 && !factory_reset_indicating()` 0x0800CA74; caller `lpm_task` 0x0800BDCC. |
| 0x0800CD38 | `keyboard_post_init_kb` | A10/A9 input, B12 high, `lkbt51_init(false)`, `wireless_init`, `timer_read32`, `encoder_cb_init`, `b.w keyboard_post_init_user` 0x0800CF60. |
| 0x0800CD18 / 0x0800CCF0 | `dip_switch_update_kb` / `dip_switch_update_user` (factory_test.c) | `if (index==0) default_layer_set(...)`; user hook reports OS switch through `factory_test_send` 0x0800CB44 when enabled. |

### 2.3 4-byte weak returning a constant: `get_tapping_term` = 175 (VERIFIED identity; config implication LIKELY)

0x0800DEFC: `movs r0,#0xAF; bx lr`. Callers: `process_tapping` 0x0800DF94 @0x0800E016 and @0x0800E192, each right after
`bl 0x0800D334 get_record_keycode(&tapping_key,false)` with `r1 = &tapping_key` - the `WITHIN_TAPPING_TERM` macro expanded with
`GET_TAPPING_TERM(keycode, record) = get_tapping_term(...)` (action_tapping.h:53-54, only when `TAPPING_TERM_PER_KEY`);
`tap_dance_task` 0x080120D0 @0x080120EC with a zeroed `keyrecord_t` on the stack (`strd r3,r3,[sp]; mov r1,sp`) = process_tap_dance.c:183;
and 0x0800DF00 @0x0800DF52 (waiting-buffer scan). The link-order file mislabels it "waiting_buffer_scan_tap split1" (opsim 0.04) - ignore that.
=> `#define TAPPING_TERM 175` and `#define TAPPING_TERM_PER_KEY` (weak default body, so no user `get_tapping_term()` override).
Note: `refs/ref_feat_keymap/config.h` uses `TAPPING_TERM 140`; the dump says **175**.

Other constants read off `process_action`: `TAPPING_TOGGLE` = 5 (default; `tap_count <= 5` on release / `< 5` on press for TT and MODS_TAP_TOGGLE),
**`ONESHOT_TAP_TOGGLE` = 2** (`#if ONESHOT_TAP_TOGGLE > 1` blocks present; compares against 2 in MODS_ONESHOT press path and OP_ONESHOT press/release),
`TAP_HOLD_CAPS_DELAY` 80 / `TAP_CODE_DELAY` 0 (defaults). No `movw #3000` anywhere in the action_util region 0x0800E2E0..0x0800E4E0
=> `ONESHOT_TIMEOUT` most likely **not** defined (ref_feat defines 3000 - remove it). OSM target should confirm.

### 2.4 Ambiguous ICF pairs resolved by how `process_action` uses them (LIKELY; consistent with OSM helper 0x0800D0B4)

`IS_MODIFIER_KEYCODE(code)||code==KC_NO` branch -> 0x0800E31C `add_mods` / else 0x0800E354 `add_weak_mods`; release: 0x0800E32C `del_mods` / 0x0800E364 `del_weak_mods`.
MODS_ONESHOT press tap_count==1 -> 0x0800E3EC `add_oneshot_mods`; ==2 -> 0x0800D672 `register_mods`, 0x0800E408 `del_oneshot_mods`, 0x0800E394 `add_oneshot_locked_mods`;
release -> 0x0800D684 `unregister_mods`, 0x0800E408 `del_oneshot_mods`, 0x0800E3C8 `del_oneshot_locked_mods` (action.c:453-475).
RAM: `oneshot_layer_data` 0x200016A4, `oneshot_locked_mods` 0x200016A5 (0x0800E3B0 `clear_oneshot_locked_mods` -> 0x0800E38C `oneshot_locked_mods_changed_kb` -> user 0x0800D08C),
`oneshot_mods` 0x200016A6 (0x0800E424 `clear_oneshot_mods` -> 0x0800E3E4 `oneshot_mods_changed_kb` -> user 0x0800D088; 0x0800E380 `get_oneshot_mods`).

### 2.5 Tiny `bx lr`-class functions with no callers (19) - all explained

Vector table: 0x0800811C (Reset_Handler thunk), 0x0800811E (`_unhandled_exception`).
Function-pointer targets in const tables: 0x0800CDD8 `td0_on_reset` (pointer 0x0800CDD9 in `tap_dance_actions` init image 0x080179D8), 0x0800EC80 `sendchar`, 0x0800EC84 `null_sendchar_func`, 0x080127FC ChibiOS `dummy_cb`, 0x08013968 `__idle_thread`, 0x08014D08 `efl_lld_get_descriptor` (EFL vmt), 0x08015E8C `_getsize` (vmt).
Thunk chain (has a caller after all): main -> `protocol_setup` 0x08012C68 (`b.w 0x08012450`) -> 0x08012450 (`b.w 0x0801243C`) -> `usb_device_state_init` 0x0801243C (also called directly from `usb_event_queue_task` @0x08012B02).
newlib leftovers: 0x08008694, 0x08009344, 0x080093A0, 0x08009538, 0x0800953C, 0x0800A110; syscall stubs 0x080166FC (`_getpid`, reached via thunk 0x0800A1BC), 0x08016700 (final 2-byte stub, `_fini`/`__aeabi_idiv0` class).
All other <=4-byte functions have callers and link-order identities (weak `*_user`/`*_kb` defaults, e.g. 0x0800D2CC `pre_process_record_user`, 0x0800D2DC `post_process_record_user`, 0x0800D370 `shutdown_user`, 0x0800E75C `is_keyboard_master`, 0x08011890 `dip_switch_update_mask_user`, wireless `*_kb` hooks 0x0800A42C..0x0800A436).

### 2.6 55 functions with no identification from any matcher - newlib 4.4.0 libc_nano internals (VERIFIED as library, not custom)

All lie in 0x08008178..0x0800A1BC. lib_match.md places newlib members there (vfprintf_i @0x9C28, vfprintf @0x8C10, fvwrite @0x8F14, signal @0x91EA,
findfp @0x9474, fflush @0x95EA, mallocr @0x97C2, makebuf @0xA068, memmove @0x9914, rand @0x84AC, strlen @0x86C0, wsetup @0x9B00, freer @0x98B4,
memchr @0x9A60, utoa @0x85F8, wbuf @0x8D44, stdio @0xA0F8, memcmp @0x89D4, fwalk @0x9A14, ...) and libgcc `_udivmoddi4` @0x8188.
The only entries from QMK code into this region are: `rand` 0x080084AC <- `DIGITAL_RAIN` 0x0800FEF0; `malloc` 0x08008970 <- debounce init 0x0800EEF8 and `free` 0x08008980 <- `debounce_free` 0x0800EF1C;
`itoa` 0x080085BC <- `via_command_kb`/`factory_test_rx`; `strlen` 0x080086C0 <- lkbt51 0x0800AC68/0x0800AEBC; memset/memcpy/memcmp; `__errno` 0x080085E8 <- syscalls.
The whole stdio cluster (`__assert_func` 0x08008544 -> fiprintf -> `_vfiprintf` 0x08008ABC/0x08008DE4 -> `__sfvwrite`/`__swbuf`/`__smakebuf`/`__sfp`/fflush/malloc, `abort`->`raise` signal.o)
is reachable only through `__assert_func`, called by `rand` (0x080084AC), `malloc` glue (0x08008448) and 0x08008584 (newlib `_REENT_CHECK` paths; the `rand.c` path string at 0x08017xxx belongs to it).

---

## 3. Compiled-in fork features (all VERIFIED from matched symbols / structure)

| feature | state | evidence |
|---|---|---|
| `LK_WIRELESS_ENABLE` (wireless.mk) | on | wireless.c (`wireless_init` 0x0800A240, `wireless_connect` 0x0800A298, `process_record_wireless` 0x0800A788 with BT_HST1..P2P4G/BAT_LVL 0x7E0B..0x7E0F), report_buffer.c (0x0800A7CC..0x0800A8D4), lkbt51.c (`lkbt51_init` 0x0800A98C, `lkbt51_dfu_tx/rx` 0x0800AF8C/0x0800B290), indicator.c (0x0800B354.., `rgb_matrix_indicators_bt` 0x0800B4C4), transport.c (`bt_transport_enable` 0x0800B990, `p24g_transport_enable` 0x0800B9F8, `get_transport` 0x0800BBB4), lpm.c (`lpm_init` 0x0800BC8C, `lpm_task` 0x0800BDCC, `enter_power_mode` 0x0800BFF4), battery.c (0x0800C144..0x0800C1AC), bat_level_animation.c (0x0800C304..0x0800C43C), rtc_timer.c (`rtc_lld_get_time` 0x08016130, `rtcSetTime` thunk 0x08014104), keychron_wireless_common.c (`keychron_wireless_common_task` 0x0800C5C4). |
| `NO_USB_STARTUP_CHECK` (wireless.mk) | on | `protocol_pre_task` 0x08012CA4 is a bare `b.w usb_event_queue_task` - no `USB_SUSPENDED` wait loop. |
| `FACTORY_TEST_ENABLE` (keychron_common.mk) | on | `process_record_factory_test` 0x0800C928 (FN_KEY_1 MO(1)=0x5221, FN_KEY_2 MO(3)=0x5223), `factory_test_task` 0x0800CA84 (eeconfig_init/rgb_matrix_init reset path), `factory_test_indicator` 0x0800CA18, `factory_test_rx/send` 0x0800CB90/0x0800CB44, `factory_timer_start` 0x0800C918, `factory_reset_indicating` 0x0800CA74, `dip_switch_update_user` 0x0800CCF0. |
| BT-module DFU over raw HID (0xAA) | on | `lkbt51_dfu_rx` 0x0800B290, `lkbt51_dfu_tx` 0x0800AF8C (both under `RAW_ENABLE` in lkbt51.c). |
| MCU DFU / bootloader | ROM DFU (`stm32-dfu`) | `enter_bootloader_mode_if_requested` 0x08012600, `bootloader_marker_active` 0x080125CC; QK_BOOT 0x7C00 handled in `process_record_quantum` 0x0800D3B6 / `reset_keyboard` 0x0800D396; factory 0xAB 0x03 "JumpToBootloader" is compiled out (commented in source, absent in dump). No symbol literally named `dfu_info` exists in the fork or the dump. |
| `VIA_ENABLE` | **off** | `raw_hid_receive` is the keychron_common.c non-VIA variant (1.1); no via.c/dynamic_keymap symbols; `keymap_key_to_keycode` 0x0800EA64 -> `keycode_at_keymap_location_raw` reads `keymaps[]` in flash (0x080169B8). |
| `RAW_ENABLE` | on (info.json `"raw": true`) | IF1/EP2 descriptors, endpoint tables, `raw_hid_task` (1.2). |
| `CONSOLE_ENABLE` | off | no console interface, `protocol_post_task` lacks `console_task`. |
| encoder + `ENCODER_MAP_ENABLE` | on | `encoder_cb_init`, `encoder_map[6][1][2]` @0x080169A0. |
| MAGIC / GRAVE_ESC / SPACE_CADET (default-on in the fork, `builddefs/generic_features.mk:16-19`) | **off** -- `process_record_quantum` 0x0800D3B6 calls only process_record_kb, process_tap_dance, process_leader, process_rgb (0x0800D3D8/E2/EC/F6); a rebuild with them on adds three calls and a 5th `get_tapping_term` caller (perform_space_cadet). The keymap's `NK_TOGG` keys are therefore inert. |
| dip switch, NKRO, mousekey (kinetic: MK_KINETIC_SPEED with MOVE_DELTA 45 / INITIAL_SPEED 30 / BASE_SPEED 1500 / INTERVAL 40 -- see config_features.txt), extrakey, bootmagic, RGB matrix (snled27351 SPI), wear-leveling EEPROM (embedded flash), tap dance, leader | on | `dip_switch_update_kb` 0x0800CD18; `send_nkro_report` 0x0800E4A4; `mousekey_on/off/task` 0x08011B84/0x08011C48/0x08011DF0; `host_system_send/consumer_send`; `bootmagic_lite` 0x0800EC98; `snled27351_set_color` 0x08011338, `rgb_matrix_init` 0x08010C70; `wear_leveling_*`/`backing_store_*` 0x0800F1E0..0x0800F67C; `process_tap_dance` 0x08012040; `process_leader` 0x080118F4. |
| `process_record_kb` / `keychron_task` order | stock | section 2.2. |

---

## 4. Verified / likely / uncertain summary

VERIFIED: 1.1 chain and the 0xAA..0xAB filter (byte-identical to ref); 1.2 descriptors, endpoint tables, init/configure path; 1.3 factory-test command set and checksum rule;
identities in 2.1, 2.2, 2.3 (function identity), 2.5, 2.6 (library, not user code); 3 feature table.
VERIFIED (upgraded): `ONESHOT_TAP_TOGGLE 2` -- QMK 0.23 has no default for it, so the `cmp #1/#2` blocks at 0x0800D824/0x0800D832/0x0800DA46/0x0800DA60 can only come from the keymap config; `ONESHOT_TIMEOUT` undefined -- structurally, add_oneshot_mods 0x0800E3EC / set_oneshot_layer 0x0800E504 contain no timer_read call. `TAPPING_TERM 175` + `TAPPING_TERM_PER_KEY` with the WEAK default (no user override): 0x0800DEFC sits at the action_tapping.o link position between waiting_buffer_typed.isra.0 and waiting_buffer_scan_tap, and the gcc 13.2.1 rebuild reproduces the same layout.
LIKELY: 2.4 ICF pair resolution.
UNCERTAIN: nothing material. The host-side write path was not tested here (never touch USB); the 0xAB probes in 1.3 decide it.

Dactyl reference vs dump: the dactyl summary predicted TAPPING_TERM 150/140 - the dump has 175; predicted `ONESHOT_TAP_TOGGLE 2` - confirmed; predicted no `ONESHOT_TIMEOUT` - consistent.
No dactyl-derived raw-HID behaviour exists and none is in the dump (the user keymap adds no raw HID code).
