// FUN_0800f7aa @ 0x0800f7aa  size=76  body=[[0800f7aa, 0800f7f5]]

uint FUN_0800f7aa(uint param_1)

{
  short sVar1;
  uint uVar2;
  uint uVar3;
  uint uVar4;
  
  if (1 < param_1) {
    if (param_1 < 0x1ee1) {
      uVar2 = (param_1 >> 5) + 8 & 0xff;
    }
    else {
      uVar2 = 0xff;
    }
    uVar4 = 1;
    do {
      uVar3 = uVar4 + uVar2;
      sVar1 = (short)(uVar3 * 0x8000 >> 0x10);
      if (param_1 < (ushort)(sVar1 * sVar1)) {
        uVar2 = (uVar3 >> 1) - 1 & 0xff;
      }
      else {
        if ((int)uVar3 >> 1 == 0xff) {
          return 0xff;
        }
        uVar4 = (uVar3 >> 1) + 1 & 0xff;
      }
    } while (uVar4 <= uVar2);
    param_1 = uVar4 - 1;
  }
  return param_1 & 0xff;
}

