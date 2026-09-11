// FUN_08012350 @ 0x08012350  size=66  body=[[080122fa, 08012319] [08012350, 08012371]]

uint FUN_08012350(uint param_1)

{
  uint uVar1;
  uint uVar2;
  
  if ((DAT_20000ec6 != '\0') && ((char)DAT_200047d4 < '\0')) {
    uVar2 = param_1 >> 3;
    uVar1 = param_1;
    if (param_1 < 0xf0) {
      uVar2 = uVar2 + DAT_20000e98;
      uVar1 = param_1 & 7;
    }
    if (param_1 < 0xf0) {
      *(byte *)(uVar2 + 2) = *(byte *)(uVar2 + 2) & ~(byte)(1 << (uVar1 & 0xff));
    }
    return (uint)(param_1 < 0xf0);
  }
  uVar2 = FUN_080122c8(DAT_20000e9c,param_1);
  return uVar2;
}

