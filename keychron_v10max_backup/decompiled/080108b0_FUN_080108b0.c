// FUN_080108b0 @ 0x080108b0  size=104  body=[[080108b0, 08010917]]

bool FUN_080108b0(char *param_1)

{
  ushort uVar1;
  uint uVar2;
  uint uVar3;
  
  uVar2 = FUN_0801017e(*param_1);
  uVar3 = uVar2 & 0xff;
  uVar2 = (uVar2 & 0xffff) >> 8;
  if (param_1[2] == '\0') {
    uVar3 = DAT_2000480c + 0x10;
    if (0xfe < uVar3) {
      uVar3 = 0xff;
    }
    if ((((ushort)DAT_20004810 * uVar3 & 0xffffff) >> 8) % 5 == 0) {
      uVar1 = FUN_0800f7f8();
      FUN_0800fe8c((short)uVar1 * 0x58 >> 8,param_1[1]);
    }
  }
  else {
    for (; (int)uVar3 < (int)uVar2; uVar3 = uVar3 + 1) {
      FUN_0800fe8c(uVar3,param_1[1]);
    }
  }
  return uVar2 < 0x58;
}

