// FUN_080102a8 @ 0x080102a8  size=170  body=[[080102a8, 08010351]]

bool FUN_080102a8(char *param_1)

{
  byte bVar1;
  undefined3 uVar2;
  uint uVar3;
  uint uVar4;
  code *extraout_r1;
  uint uVar5;
  undefined1 *puVar6;
  uint uVar7;
  uint local_2c;
  
  uVar3 = FUN_0801017e(*param_1);
  uVar5 = (uint)(ushort)DAT_20004810;
  bVar1 = DAT_2000480c >> 1;
  uVar7 = uVar3 & 0xff;
  uVar3 = (uVar3 & 0xffff) >> 8;
  puVar6 = &DAT_20000d07 + uVar7 * 2;
  for (; (uVar7 & 0xff) < uVar3; uVar7 = uVar7 + 1) {
    if (((&DAT_20000e23)[uVar7] & param_1[1]) != 0) {
      uVar2 = (*extraout_r1)((uint)CONCAT12(DAT_2000480b,CONCAT11(DAT_2000480a,DAT_20004809)),
                             (byte)puVar6[0x6c] - 0x70,(byte)puVar6[0x6d] - 0x20,
                             (uVar5 * bVar1 & 0xffff) >> 8);
      local_2c = CONCAT13(local_2c._3_1_,uVar2);
      uVar4 = FUN_0800fd30(local_2c);
      FUN_0800fe78(uVar7,(char)(uVar4 >> 8),(char)uVar4,(char)(uVar4 >> 0x10));
    }
    puVar6 = puVar6 + 2;
  }
  return uVar3 < 0x58;
}

