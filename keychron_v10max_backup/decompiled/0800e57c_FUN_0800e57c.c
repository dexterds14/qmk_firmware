// FUN_0800e57c @ 0x0800e57c  size=38  body=[[0800e57c, 0800e5a1]]

void FUN_0800e57c(uint param_1)

{
  uint uVar1;
  uint uVar2;
  
  uVar1 = (DAT_200047d4._1_1_ & 7) >> 2;
  if (uVar1 != param_1) {
    uVar2 = DAT_200047d4._1_1_ & 0xfffffffb | (param_1 & 1) << 2;
    DAT_200047d4 = CONCAT11((char)uVar2,(undefined1)DAT_200047d4);
    FUN_0800e606((uint)DAT_200047d4,uVar1,&DAT_200047d4,uVar2);
    FUN_0800e548(2);
    return;
  }
  return;
}

