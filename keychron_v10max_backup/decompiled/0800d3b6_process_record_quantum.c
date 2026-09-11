// process_record_quantum @ 0x0800d3b6  size=166  body=[[0800d3b6, 0800d45b]]

// VERIFIED shape: keycode=get_record_keycode(record,1); if preprocess_tap_dance(kc,rec) re-read;
// chain process_record_kb 0x0800C6E8 && process_tap_dance 0x08012040 && process_leader 0x080118F4
// && process_rgb_matrix 0x08011530; if pressed: 0x7C00 QK_BOOT->0x0800D396 0x7C01
// QK_REBOOT->0x0800D3A6 0x7C03 QK_CLEAR_EEPROM->0x0800E5CC+0x0800D3A6 0x7C5A/5B/5C
// OS_ON/OFF/TOGG->0x0800E5C0/E5C6/E5A8; return process_action_kb 0x0800D2D8

undefined4 process_record_quantum(uint *param_1)

{
  char cVar1;
  ushort uVar2;
  int iVar4;
  undefined4 uVar5;
  uint uVar3;
  
  uVar2 = get_record_keycode(param_1,1);
  uVar3 = (uint)uVar2;
  cVar1 = preprocess_tap_dance(uVar3,(int)param_1);
  if (cVar1 != '\0') {
    uVar2 = get_record_keycode(param_1,1);
    uVar3 = (uint)uVar2;
  }
  iVar4 = process_record_kb(uVar3,(int)param_1);
  if ((((iVar4 == 0) || (iVar4 = process_tap_dance(uVar3,(int)param_1), iVar4 == 0)) ||
      (cVar1 = process_leader(uVar3,(int)param_1), cVar1 == '\0')) ||
     (cVar1 = process_rgb_matrix(uVar3,(int)param_1), cVar1 == '\0')) {
LAB_0800d442:
    uVar5 = 0;
  }
  else {
    if (*(char *)((int)param_1 + 5) != '\0') {
      if (uVar3 == 0x7c5a) {
        FUN_0800e5c0();
      }
      else {
        if (uVar3 < 0x7c5b) {
          if (uVar3 != 0x7c01) {
            if (uVar3 != 0x7c03) {
              if (uVar3 == 0x7c00) {
                reset_keyboard();
                goto LAB_0800d442;
              }
              goto LAB_0800d420;
            }
            FUN_0800e5cc();
          }
          soft_reset_keyboard();
          goto LAB_0800d442;
        }
        if (uVar3 == 0x7c5b) {
          FUN_0800e5c6();
        }
        else if (uVar3 == 0x7c5c) {
          FUN_0800e5a8();
        }
      }
    }
LAB_0800d420:
    uVar5 = process_action_kb();
  }
  return uVar5;
}

