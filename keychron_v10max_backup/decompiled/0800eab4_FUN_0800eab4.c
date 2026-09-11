// FUN_0800eab4 @ 0x0800eab4  size=250  body=[[0800eab4, 0800ead7] [0800eae0, 0800ebb5]]

uint FUN_0800eab4(uint param_1)

{
  byte bVar1;
  uint uVar2;
  int iVar3;
  
  if (0xe7 < param_1) {
    return param_1;
  }
  if (param_1 < 0xe0) {
    if (param_1 == 0x31) {
      uVar2 = 0x31;
      if (((byte)DAT_200047d4 & 0x40) != 0) {
        uVar2 = 0x2a;
      }
      return uVar2;
    }
    if (0x31 < param_1) {
      if ((param_1 == 0x39) || (param_1 == 0x82)) {
        if (((byte)DAT_200047d4 & 3) != 0) {
          return 0xe0;
        }
        bVar1 = DAT_200047d4._1_1_ & 8;
      }
      else {
        if (param_1 != 0x35) {
          return param_1;
        }
        bVar1 = (byte)DAT_200047d4 & 0x20;
      }
      if (bVar1 != 0) {
        param_1 = 0x29;
      }
      return param_1;
    }
    if (param_1 != 0x29) {
      if (param_1 != 0x2a) {
        return param_1;
      }
      uVar2 = 0x2a;
      if (((byte)DAT_200047d4 & 0x40) != 0) {
        uVar2 = 0x31;
      }
      return uVar2;
    }
    if ((int)((uint)(byte)DAT_200047d4 << 0x1a) < 0) {
      return 0x35;
    }
    uVar2 = 0x29;
    if ((DAT_200047d4._1_1_ & 8) != 0) {
      uVar2 = 0x39;
    }
    return uVar2;
  }
  switch(param_1) {
  case 0xe0:
    if ((int)((uint)(byte)DAT_200047d4 << 0x1f) < 0) {
      return 0x39;
    }
    bVar1 = DAT_200047d4._1_1_ & 1;
    break;
  default:
    goto switchD_0800ead4_caseD_e1;
  case 0xe2:
    bVar1 = (byte)DAT_200047d4 & 4;
    break;
  case 0xe3:
    if ((int)((uint)(byte)DAT_200047d4 << 0x1d) < 0) {
      return 0xe2;
    }
    if ((int)((uint)DAT_200047d4._1_1_ << 0x1f) < 0) {
      return 0xe0;
    }
    goto LAB_0800eb12;
  case 0xe4:
    iVar3 = (uint)DAT_200047d4._1_1_ << 0x1e;
    goto joined_r0x0800eb56;
  case 0xe6:
    iVar3 = (uint)(byte)DAT_200047d4 << 0x1c;
joined_r0x0800eb56:
    if (-1 < iVar3) {
      return param_1;
    }
LAB_0800eb44:
    if (((byte)DAT_200047d4 & 0x10) == 0) {
      uVar2 = 0xe7;
    }
    else {
      uVar2 = 0;
    }
    return uVar2;
  case 0xe7:
    if ((int)((uint)(byte)DAT_200047d4 << 0x1c) < 0) {
      return 0xe6;
    }
    if ((int)((uint)DAT_200047d4._1_1_ << 0x1e) < 0) {
      return 0xe4;
    }
    goto LAB_0800eb44;
  }
  if (bVar1 != 0) {
LAB_0800eb12:
    if (((byte)DAT_200047d4 & 0x10) == 0) {
      uVar2 = 0xe3;
    }
    else {
      uVar2 = 0;
    }
    return uVar2;
  }
switchD_0800ead4_caseD_e1:
  return param_1;
}

