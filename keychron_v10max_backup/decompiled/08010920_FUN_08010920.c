// FUN_08010920 @ 0x08010920  size=280  body=[[08010920, 08010a37]]

bool FUN_08010920(char *param_1)

{
  uint uVar1;
  uint uVar2;
  char cVar3;
  short sVar4;
  uint uVar5;
  uint uVar6;
  int iVar7;
  byte bVar8;
  byte *pbVar9;
  byte *pbVar10;
  undefined4 local_30;
  
  uVar1 = FUN_0801017e(*param_1);
  uVar6 = (uVar1 & 0xffff) >> 8;
  if (param_1[2] != '\0') {
    thunk_FUN_08011378(0,0,0);
    FUN_08008798(&DAT_20001f4e,0,0x6c);
  }
  if (*param_1 == '\0') {
    uVar2 = FUN_0801257e((uint)DAT_20001fbc);
    DAT_20001fba = 0x18 < uVar2;
    if ((bool)DAT_20001fba) {
      uVar2 = FUN_08012574();
      DAT_20001fbc = (ushort)uVar2;
    }
  }
  iVar7 = 0;
  bVar8 = 0;
  do {
    cVar3 = '\x12';
    pbVar9 = &DAT_20001f4e + iVar7;
    pbVar10 = &DAT_20000d07 + iVar7;
    do {
      uVar2 = local_30;
      uVar5 = (uint)*pbVar10;
      if (((uVar1 & 0xff) <= uVar5) && (uVar5 < uVar6)) {
        if (((&DAT_20000e23)[uVar5] & param_1[1]) != 0) {
          uVar5 = (uint)*pbVar9;
          sVar4 = (short)(uVar5 + 0xaa);
          if (0xfe < uVar5 + 0xaa) {
            sVar4 = 0xff;
          }
          local_30._3_1_ = SUB41(uVar2,3);
          local_30._0_3_ =
               CONCAT12((char)((uint)((int)(short)(sVar4 * 3 + 2U & 0xff) *
                                     (int)(short)(ushort)DAT_2000480b) >> 8),
                        CONCAT11(DAT_2000480a,
                                 -0x56 - ((byte)(uVar5 - 0x55) &
                                         ~(byte)((int)(uVar5 - 0x55) >> 0x1f))));
          uVar2 = FUN_0800fd30(local_30);
          FUN_0800fe78((uint)*pbVar10,(char)(uVar2 >> 8),(char)uVar2,(char)(uVar2 >> 0x10));
          if (DAT_20001fba != '\0') {
            *pbVar9 = (byte)(uVar5 - 1) & ~(byte)((int)(uVar5 - 1) >> 0x1f);
          }
        }
        bVar8 = bVar8 + 1;
      }
      cVar3 = cVar3 + -1;
      pbVar9 = pbVar9 + 1;
      pbVar10 = pbVar10 + 1;
    } while (cVar3 != '\0');
  } while ((iVar7 != 0x5a) && (iVar7 = iVar7 + 0x12, bVar8 < 0x12));
  return uVar6 < 0x58;
}

