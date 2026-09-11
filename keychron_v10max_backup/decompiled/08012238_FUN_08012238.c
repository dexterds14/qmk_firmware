// FUN_08012238 @ 0x08012238  size=82  body=[[08012238, 08012289]]

bool FUN_08012238(uint param_1)

{
  byte *pbVar1;
  
  if (param_1 == 0) {
    return false;
  }
  if ((DAT_20000ec6 == '\0') || (-1 < (char)DAT_200047d4)) {
    pbVar1 = (byte *)(DAT_20000e9c + 1);
    do {
      pbVar1 = pbVar1 + 1;
      if (*pbVar1 == param_1) {
        return true;
      }
    } while (pbVar1 != (byte *)(DAT_20000e9c + 7));
  }
  else if (param_1 < 0xf0) {
    return ((uint)*(byte *)(DAT_20000e98 + (param_1 >> 3) + 2) & 1 << (param_1 & 7)) != 0;
  }
  return false;
}

