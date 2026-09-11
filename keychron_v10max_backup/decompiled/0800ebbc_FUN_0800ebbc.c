// FUN_0800ebbc @ 0x0800ebbc  size=190  body=[[0800ebbc, 0800ec79]]

uint FUN_0800ebbc(uint param_1)

{
  uint uVar1;
  
  uVar1 = (uint)(byte)DAT_200047d4;
  if (((int)(uVar1 << 0x1d) < 0) && (((param_1 & 0x14) == 4) != ((param_1 & 0x18) == 8))) {
    param_1 = param_1 ^ 0xc;
  }
  if (((int)(uVar1 << 0x1c) < 0) && (((param_1 & 0x14) == 0x14) != ((param_1 & 0x18) == 0x18))) {
    param_1 = param_1 ^ 0xc;
  }
  if (((int)((uint)DAT_200047d4._1_1_ << 0x1f) < 0) &&
     (((param_1 & 0x11) == 1) != ((param_1 & 0x18) == 8))) {
    param_1 = param_1 ^ 9;
  }
  if (((int)((uint)DAT_200047d4._1_1_ << 0x1e) < 0) &&
     (((param_1 & 0x11) == 0x11) != ((param_1 & 0x18) == 0x18))) {
    param_1 = param_1 ^ 9;
  }
  if ((int)(uVar1 << 0x1b) < 0) {
    param_1 = param_1 & 0xe7;
  }
  return param_1;
}

