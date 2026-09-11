// FUN_08010440 @ 0x08010440  size=180  body=[[08010440, 080104f3]]

bool FUN_08010440(char *param_1)

{
  undefined3 uVar1;
  uint uVar2;
  uint uVar3;
  uint uVar4;
  uint uVar5;
  code *extraout_r1;
  uint uVar6;
  uint uVar7;
  uint local_2c;
  
  uVar2 = FUN_0801017e(*param_1);
  uVar6 = ((uint)(ushort)DAT_20004810 * (uint)(DAT_2000480c >> 2) & 0xffff) >> 8;
  uVar7 = (uVar2 & 0xffff) >> 8;
  uVar3 = FUN_0800f81c(uVar6 + 0x40 & 0xff);
  uVar4 = FUN_0800f81c(uVar6);
  for (uVar2 = uVar2 & 0xff; (uVar2 & 0xff) < uVar7; uVar2 = uVar2 + 1) {
    if (((&DAT_20000e23)[uVar2] & param_1[1]) != 0) {
      uVar1 = (*extraout_r1)((uint)CONCAT12(DAT_2000480b,CONCAT11(DAT_2000480a,DAT_20004809)),
                             (int)(char)((char)uVar3 + -0x80),(int)(char)((char)uVar4 + -0x80),
                             uVar2 & 0xff,uVar6);
      local_2c = CONCAT13(local_2c._3_1_,uVar1);
      uVar5 = FUN_0800fd30(local_2c);
      FUN_0800fe78(uVar2,(char)(uVar5 >> 8),(char)uVar5,(char)(uVar5 >> 0x10));
    }
  }
  return uVar7 < 0x58;
}

