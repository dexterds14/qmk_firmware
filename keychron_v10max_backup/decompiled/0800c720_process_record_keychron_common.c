// process_record_keychron_common @ 0x0800c720  size=158  body=[[0800c720, 0800c72d] [0800c73a, 0800c7c9]]

// VERIFIED: switch 0x7E00-0x7E03 (KC_LOPTN..KC_RCMMD via mac_keycode table @0x0800EA3C) 0x7E04
// KC_MCTRL->0xC1 0x7E05 KC_LNPAD->0xC2 0x7E06-0x7E09 KC_TASK..KC_CTANA via key_comb_list
// @0x0801682C stride 4 (keychron_common.c:87)

undefined4 process_record_keychron_common(int param_1,int param_2)

{
  byte bVar1;
  uint uVar2;
  int iVar3;
  int extraout_r1;
  char cVar4;
  byte bVar5;
  
  switch(param_1) {
  case 0x7e00:
  case 0x7e01:
  case 0x7e02:
  case 0x7e03:
    uVar2 = (uint)*(byte *)(param_1 + 0x800ea3c);
    cVar4 = *(char *)(param_2 + 5);
    break;
  case 0x7e04:
    cVar4 = *(char *)(param_2 + 5);
    uVar2 = 0xc1;
    break;
  case 0x7e05:
    cVar4 = *(char *)(param_2 + 5);
    uVar2 = 0xc2;
    break;
  case 0x7e06:
  case 0x7e07:
  case 0x7e08:
  case 0x7e09:
    iVar3 = param_1 + -0x7e06;
    if (*(char *)(param_2 + 5) == '\0') {
      bVar1 = (&key_comb_list)[iVar3 * 4];
      for (bVar5 = 0; (uint)bVar5 < (uint)bVar1; bVar5 = bVar5 + 1) {
        unregister_code((uint)(byte)(&DAT_0801682d)[(uint)bVar5 + iVar3 * 4],param_2);
        param_2 = extraout_r1;
      }
      return 0;
    }
    bVar1 = (&key_comb_list)[iVar3 * 4];
    for (bVar5 = 0; (uint)bVar5 < (uint)bVar1; bVar5 = bVar5 + 1) {
      register_code((uint)(byte)(&DAT_0801682d)[(uint)bVar5 + iVar3 * 4]);
    }
    return 0;
  case 0x7e0a:
    if (*(char *)(param_2 + 5) == '\0') {
      return 0;
    }
    if (DAT_200015c8 == '\0') {
      DAT_200015c8 = '\x01';
      register_code(0xe3);
      register_code(0x2c);
    }
    DAT_200015c4 = FUN_08012508();
    return 0;
  default:
    return 1;
  }
  if (cVar4 == '\0') {
    unregister_code(uVar2,param_2);
  }
  else {
    register_code(uVar2);
  }
  return 0;
}

