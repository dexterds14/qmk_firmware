// FUN_0800bf94 @ 0x0800bf94  size=84  body=[[0800bf94, 0800bfe7]]

undefined4 FUN_0800bf94(int param_1)

{
  undefined4 uVar1;
  uint uVar2;
  
  if (param_1 == 2) {
    if (DAT_2000159c != '\0') {
LAB_0800bfe4:
      uVar1 = 0;
      goto LAB_0800bfd2;
    }
    uVar2 = DAT_e000ed10;
    DAT_e000ed10 = uVar2 | 4;
    uVar2 = DAT_40007000;
    DAT_40007000 = uVar2 | 0xe01;
  }
  else {
    if (param_1 == 3) {
      if (DAT_2000159c != '\0') goto LAB_0800bfe4;
      uVar2 = DAT_e000ed10;
      uVar2 = uVar2 | 4;
    }
    else {
      if (param_1 != 1) goto LAB_0800bfd0;
      if (DAT_2000159c != '\0') goto LAB_0800bfe4;
      uVar2 = DAT_e000ed10;
      uVar2 = uVar2 & 0xfffffffb;
    }
    DAT_e000ed10 = uVar2;
  }
LAB_0800bfd0:
  uVar1 = 1;
LAB_0800bfd2:
  DAT_2000159c = (char)param_1;
  return uVar1;
}

