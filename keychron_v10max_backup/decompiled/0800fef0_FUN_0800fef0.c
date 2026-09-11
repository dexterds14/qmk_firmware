// FUN_0800fef0 @ 0x0800fef0  size=342  body=[[0800fef0, 08010045]]

undefined4 FUN_0800fef0(int param_1)

{
  uint uVar1;
  byte bVar2;
  uint uVar3;
  byte *pbVar4;
  char cVar5;
  byte bVar6;
  undefined1 uVar7;
  char cVar8;
  uint uVar9;
  uint uVar10;
  byte *pbVar11;
  uint uVar12;
  byte *pbVar13;
  ulonglong uVar14;
  byte local_30 [12];
  
  bVar2 = DAT_2000480b;
  uVar9 = (uint)DAT_2000480b;
  uVar1 = (int)(uVar9 * 3) >> 2;
  if (*(char *)(param_1 + 2) != '\0') {
    thunk_FUN_08011378(0,0,0);
    FUN_08008798(&DAT_20001f4e,0,0x6c);
    DAT_20001f19 = '\0';
  }
  pbVar13 = &DAT_20001f4e;
  DAT_20001f18 = DAT_20001f18 + 1;
  uVar10 = 0;
  do {
    uVar12 = 0;
    pbVar11 = pbVar13;
    do {
      if ((DAT_20001f19 == '\0' && (uVar12 & 0xff) == 0) &&
         (uVar14 = FUN_080084ac(), (int)uVar14 < 0x5555555)) {
        *pbVar13 = bVar2;
      }
      else {
        bVar6 = *pbVar11;
        if ((bVar6 != 0) && ((bVar6 < uVar9 && ((uint)DAT_20001f18 == 0xff / uVar9)))) {
          *pbVar11 = bVar6 - 1;
        }
      }
      uVar3 = FUN_0800fe44(uVar12 & 0xff,uVar10,(int)local_30);
      if (uVar3 != 0) {
        bVar6 = *pbVar11;
        if (uVar9 * 3 >> 2 < (uint)bVar6) {
          uVar7 = (undefined1)((int)(uVar1 * (bVar6 - uVar1)) / (int)(uVar9 - uVar1));
          bVar6 = bVar2;
        }
        else {
          uVar7 = 0;
          bVar6 = (byte)((uint)((int)(short)(ushort)bVar2 * (int)(short)(ushort)bVar6) / uVar1);
        }
        FUN_0800fe78((uint)local_30[0],uVar7,bVar6,uVar7);
      }
      uVar12 = uVar12 + 1;
      pbVar11 = pbVar11 + 0x12;
    } while (uVar12 != 6);
    uVar10 = uVar10 + 1 & 0xff;
    pbVar13 = pbVar13 + 1;
  } while (uVar10 != 0x12);
  if ((uint)DAT_20001f18 == 0xff / uVar9) {
    DAT_20001f18 = 0;
  }
  DAT_20001f19 = DAT_20001f19 + 1;
  if (0x1c < DAT_20001f19) {
    DAT_20001f19 = 0;
    cVar8 = '\x05';
    pbVar13 = &DAT_20001fa8;
    do {
      pbVar4 = &DAT_20001fa8;
      cVar5 = '\x12';
      pbVar11 = pbVar13;
      do {
        if ((cVar8 == '\x05') && (uVar9 == *pbVar4)) {
          *pbVar4 = bVar2 - 1;
        }
        cVar5 = cVar5 + -1;
        if (uVar9 <= pbVar11[-0x12]) {
          pbVar11[-0x12] = bVar2 - 1;
          *pbVar11 = bVar2;
        }
        pbVar11 = pbVar11 + 1;
        pbVar4 = pbVar4 + 1;
      } while (cVar5 != '\0');
      cVar8 = cVar8 + -1;
      pbVar13 = pbVar13 + -0x12;
    } while (cVar8 != '\0');
  }
  return 0;
}

