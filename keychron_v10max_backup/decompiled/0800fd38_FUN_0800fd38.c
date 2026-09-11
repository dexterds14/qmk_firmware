// FUN_0800fd38 @ 0x0800fd38  size=212  body=[[0800fd38, 0800fe0b]]

void FUN_0800fd38(uint param_1,uint param_2)

{
  int iVar1;
  int iVar2;
  byte bVar3;
  uint uVar4;
  byte *pbVar5;
  byte *pbVar6;
  uint uVar7;
  uint uVar8;
  
  bVar3 = (&DAT_20000d07)[param_2 + param_1 * 0x12];
  if (bVar3 != 0xff) {
    uVar7 = 0;
    do {
      uVar8 = 0;
      pbVar6 = &DAT_20001f4e + uVar7 * 0x12;
      iVar1 = (bVar3 + 0x34) * 2;
      pbVar5 = &DAT_20000d07 + uVar7 * 0x12;
      do {
        if (*pbVar5 != 0xff) {
          if ((param_1 == (uVar7 & 0xff)) && (param_2 == (uVar8 & 0xff))) {
            uVar4 = (byte)(&DAT_20001f4e)[param_2 + param_1 * 0x12] + 0x20;
            if (0xfe < uVar4) {
              uVar4 = 0xff;
            }
            (&DAT_20001f4e)[param_2 + param_1 * 0x12] = (char)uVar4;
          }
          else {
            iVar2 = (*pbVar5 + 0x34) * 2;
            uVar4 = FUN_0800f7aa(((uint)(byte)(&DAT_20000d0b)[iVar1] -
                                 (uint)(byte)(&DAT_20000d0b)[iVar2]) *
                                 ((uint)(byte)(&DAT_20000d0b)[iVar1] -
                                 (uint)(byte)(&DAT_20000d0b)[iVar2]) +
                                 ((uint)(byte)(&DAT_20000d0c)[iVar1] -
                                 (uint)(byte)(&DAT_20000d0c)[iVar2]) *
                                 ((uint)(byte)(&DAT_20000d0c)[iVar1] -
                                 (uint)(byte)(&DAT_20000d0c)[iVar2]) & 0xffff);
            if (uVar4 < 0x29) {
              uVar4 = 0x28 - uVar4 & 0xffff;
              if (0xf < uVar4) {
                uVar4 = 0x10;
              }
              uVar4 = (uint)*pbVar6 + (uVar4 & 0xff);
              if (0xfe < uVar4) {
                uVar4 = 0xff;
              }
              *pbVar6 = (byte)uVar4;
            }
          }
        }
        uVar8 = uVar8 + 1;
        pbVar6 = pbVar6 + 1;
        pbVar5 = pbVar5 + 1;
      } while (uVar8 != 0x12);
      uVar7 = uVar7 + 1;
    } while (uVar7 != 6);
  }
  return;
}

