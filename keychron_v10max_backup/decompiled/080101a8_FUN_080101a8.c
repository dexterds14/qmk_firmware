// FUN_080101a8 @ 0x080101a8  size=206  body=[[080101a8, 08010275]]

bool FUN_080101a8(char *param_1,undefined *param_2)

{
  byte bVar1;
  short sVar2;
  undefined3 uVar3;
  uint uVar4;
  uint uVar5;
  short sVar6;
  undefined1 *puVar7;
  uint uVar8;
  uint uVar9;
  uint local_2c;
  
  uVar4 = FUN_0801017e(*param_1);
  uVar9 = (uint)(ushort)DAT_20004810;
  bVar1 = DAT_2000480c >> 1;
  uVar8 = uVar4 & 0xff;
  uVar4 = (uVar4 & 0xffff) >> 8;
  puVar7 = &DAT_20000d07 + uVar8 * 2;
  for (; (uVar8 & 0xff) < uVar4; uVar8 = uVar8 + 1) {
    if (((&DAT_20000e23)[uVar8] & param_1[1]) != 0) {
      sVar6 = (byte)puVar7[0x6c] - 0x70;
      sVar2 = (byte)puVar7[0x6d] - 0x20;
      uVar5 = FUN_0800f7aa((uint)(ushort)(sVar2 * sVar2 + sVar6 * sVar6));
      uVar3 = (*(code *)param_2)((uint)CONCAT12(DAT_2000480b,CONCAT11(DAT_2000480a,DAT_20004809)),
                                 (int)sVar6,(int)sVar2,uVar5,(bVar1 * uVar9 & 0xffff) >> 8);
      local_2c = CONCAT13(local_2c._3_1_,uVar3);
      uVar5 = FUN_0800fd30(local_2c);
      FUN_0800fe78(uVar8,(char)(uVar5 >> 8),(char)uVar5,(char)(uVar5 >> 0x10));
    }
    puVar7 = puVar7 + 2;
  }
  return uVar4 < 0x58;
}

