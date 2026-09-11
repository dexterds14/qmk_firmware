// FUN_0800b5d0 @ 0x0800b5d0  size=200  body=[[0800b5d0, 0800b5e9] [0800b5f0, 0800b69d]]

void FUN_0800b5d0(char *param_1)

{
  byte bVar1;
  uint uVar2;
  
  if (*param_1 != '\x05') {
    DAT_20001574 = *param_1;
  }
  switch(DAT_20001574) {
  case '\0':
    goto switchD_0800b5e6_caseD_0;
  default:
    DAT_20001576 = 0;
    break;
  case '\x02':
    if (DAT_200047cd == 0) goto switchD_0800b5e6_caseD_0;
    if (DAT_200047d0 == 0) {
      DAT_200047cd = DAT_200047cd | 0x80;
      if (DAT_200047c8 != 0) {
        DAT_200047d0 = DAT_200047c8;
      }
      goto switchD_0800b5e6_caseD_0;
    }
    break;
  case '\x03':
    if (DAT_200047cd == 0) goto switchD_0800b5e6_caseD_0;
    uVar2 = (uint)(ushort)DAT_200047c0;
    if (DAT_200047d0 == 0) {
      DAT_200047cd = DAT_200047cd | 0x80;
    }
    else {
      DAT_200047cd = DAT_200047cd & 0x1f;
      uVar2 = DAT_200047c8 - uVar2 & 0xffff;
    }
    DAT_20001576 = (ushort)uVar2;
    goto joined_r0x0800b68a;
  case '\x04':
    if (DAT_200047cd == 0) goto switchD_0800b5e6_caseD_0;
    if ((int)((uint)DAT_200047cd << 0x18) < 0) {
      DAT_200047cd = DAT_200047cd & 0x1f;
      DAT_20001576 = (ushort)DAT_200047c4;
    }
    else {
      DAT_200047cd = DAT_200047cd | 0x80;
      DAT_20001576 = (ushort)DAT_200047c0;
    }
    uVar2 = (uint)DAT_20001576;
joined_r0x0800b68a:
    if (((DAT_200047c8 == 0) || (DAT_200047d0 <= DAT_200047c8)) && (uVar2 != 0)) {
      DAT_200047d0 = DAT_200047d0 + uVar2;
      goto switchD_0800b5e6_caseD_0;
    }
  }
  DAT_200047cd = DAT_200047cd & 0x1f;
  FUN_0800b4c4();
  DAT_200047cd = 0;
  FUN_0800bc70();
switchD_0800b5e6_caseD_0:
  if (DAT_200047cd == 0) {
    FUN_0800b378();
    bVar1 = FUN_08010cf4();
    if (bVar1 == 0) {
      FUN_08010cd4();
      return;
    }
  }
  return;
}

