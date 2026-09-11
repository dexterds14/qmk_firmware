// FUN_08010518 @ 0x08010518  size=208  body=[[08010518, 080105e7]]

bool FUN_08010518(char *param_1)

{
  undefined3 uVar1;
  uint uVar2;
  uint uVar3;
  code *extraout_r1;
  uint uVar4;
  uint uVar5;
  int iVar6;
  uint uVar7;
  uint local_2c;
  
  uVar2 = FUN_0801017e(*param_1);
  uVar5 = DAT_2000480c + 1;
  uVar7 = (uVar2 & 0xffff) >> 8;
  uVar2 = uVar2 & 0xff;
  if (0xfe < uVar5) {
    uVar5 = 0xff;
  }
  for (; (uVar2 & 0xff) < uVar7; uVar2 = uVar2 + 1) {
    if (((&DAT_20000e23)[uVar2] & param_1[1]) != 0) {
      iVar6 = (int)(char)(DAT_20004814 + -1);
      while ((uVar3 = 0xffff / uVar5, -1 < iVar6 << 0x18 &&
             (((uint)(byte)(&DAT_20004825)[iVar6] != (uVar2 & 0xff) ||
              (uVar3 = (uint)*(ushort *)(&DAT_20004815 + (iVar6 + 0xc) * 2),
              0xffff / uVar5 <= (uint)*(ushort *)(&DAT_20004815 + (iVar6 + 0xc) * 2)))))) {
        iVar6 = iVar6 + -1;
      }
      uVar4 = DAT_2000480c + 1;
      if (0xfe < uVar4) {
        uVar4 = 0xff;
      }
      uVar1 = (*extraout_r1)((uint)CONCAT12(DAT_2000480b,CONCAT11(DAT_2000480a,DAT_20004809)),
                             (uVar3 * uVar4 & 0xffffff) >> 8);
      local_2c = CONCAT13(local_2c._3_1_,uVar1);
      uVar3 = FUN_0800fd30(local_2c);
      FUN_0800fe78(uVar2,(char)(uVar3 >> 8),(char)uVar3,(char)(uVar3 >> 0x10));
    }
  }
  return uVar7 < 0x58;
}

