// FUN_0800b82c @ 0x0800b82c  size=154  body=[[0800b82c, 0800b8c5]]

void FUN_0800b82c(void)

{
  uint uVar1;
  
  if ((DAT_2000156c != 0) && (uVar1 = FUN_0801258c(DAT_2000156c), 1000 < uVar1)) {
    uVar1 = DAT_40020414;
    DAT_40020414 = uVar1 ^ 0x1000;
    DAT_2000156c = FUN_08012508();
    uVar1 = FUN_0801258c(DAT_20001568);
    if (10000 < uVar1) {
      uVar1 = DAT_40020410;
      if ((uVar1 & 0x1000) == 0) {
        DAT_20001568 = 0;
        DAT_2000156c = 0;
      }
    }
  }
  if (DAT_20001560 != 0) {
    if ((DAT_20001560 & 0xc) != 0) {
LAB_0800b876:
      DAT_20001560 = 0;
      FUN_0800bc70();
      return;
    }
    uVar1 = FUN_0801258c(DAT_20001564);
    if (uVar1 < 0x3e9) {
      if ((DAT_20001560 & 0xc) != 0) goto LAB_0800b876;
    }
    else {
      if ((int)((uint)DAT_20001560 << 0x18) < 0) {
        DAT_20001560 = (DAT_20001560 & 0x7f) + 1;
      }
      else {
        DAT_20001560 = DAT_20001560 | 0x80;
      }
      DAT_20001564 = FUN_08012508();
      if (((DAT_20001560 & 0xc) != 0) && (uVar1 = FUN_0800b81c(), uVar1 != 0)) {
        FUN_08010cd4();
        return;
      }
    }
  }
  return;
}

