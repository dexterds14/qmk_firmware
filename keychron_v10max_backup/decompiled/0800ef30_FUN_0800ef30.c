// FUN_0800ef30 @ 0x0800ef30  size=284  body=[[0800ef30, 0800f04b]]

undefined1 FUN_0800ef30(int param_1,int param_2,uint param_3,int param_4)

{
  byte bVar1;
  bool bVar2;
  int iVar3;
  uint *puVar4;
  uint uVar5;
  uint uVar6;
  uint uVar7;
  byte *pbVar8;
  char cVar9;
  uint uVar10;
  int iVar11;
  char cVar12;
  uint uVar13;
  char cVar14;
  
  cVar9 = DAT_200016fb;
  DAT_200016f9 = 0;
  if (DAT_200016fb == '\0') {
    cVar9 = '\0';
    if (param_4 == 0) goto LAB_0800ef92;
  }
  else {
    iVar3 = FUN_08012508();
    uVar5 = iVar3 - DAT_200016fc;
    DAT_200016fc = iVar3;
    if (uVar5 < 0x100) {
      if (uVar5 != 0) goto LAB_0800ef5e;
    }
    else {
      uVar5 = 0xff;
LAB_0800ef5e:
      DAT_200016fb = '\0';
      DAT_200016fa = '\0';
      cVar12 = '\0';
      cVar14 = '\0';
      iVar3 = DAT_20001700;
      for (uVar6 = 0; (uVar6 & 0xff) < param_3; uVar6 = uVar6 + 1) {
        pbVar8 = (byte *)(iVar3 + -1);
        do {
          pbVar8 = pbVar8 + 1;
          bVar1 = *pbVar8;
          if (bVar1 != 0) {
            if ((uVar5 & 0xff) < (uint)bVar1) {
              *pbVar8 = bVar1 - (char)uVar5;
              cVar14 = cVar9;
            }
            else {
              *pbVar8 = 0;
              cVar12 = cVar9;
            }
          }
        } while (pbVar8 != (byte *)(iVar3 + 0x11));
        iVar3 = iVar3 + 0x12;
      }
      if (cVar12 != '\0') {
        DAT_200016fa = '\x01';
      }
      if (cVar14 != '\0') {
        DAT_200016fb = '\x01';
      }
    }
    if (param_4 != 0) goto LAB_0800efa0;
LAB_0800ef92:
    if (DAT_200016fa == '\0') {
      return DAT_200016f9;
    }
    if (cVar9 != '\0') goto LAB_0800efa0;
  }
  DAT_200016fc = FUN_08012508();
LAB_0800efa0:
  iVar3 = DAT_20001700;
  DAT_200016fa = 0;
  puVar4 = (uint *)(param_2 + -4);
  bVar2 = false;
  for (uVar5 = 0; iVar11 = uVar5 * 0x12 + iVar3, (uVar5 & 0xff) < param_3; uVar5 = uVar5 + 1) {
    uVar6 = puVar4[1];
    uVar10 = uVar6 ^ *(uint *)(param_1 + uVar5 * 4);
    uVar7 = 0;
    do {
      uVar13 = 1 << (uVar7 & 0xff);
      if (((uVar10 & uVar13) != 0) && (*(char *)(iVar11 + uVar7) == '\0')) {
        *(undefined1 *)(iVar11 + uVar7) = 0x14;
        uVar6 = uVar6 ^ uVar13;
        bVar2 = true;
      }
      uVar7 = uVar7 + 1;
    } while (uVar7 != 0x12);
    puVar4 = puVar4 + 1;
    *puVar4 = uVar6;
  }
  if (bVar2) {
    DAT_200016f9 = 1;
    DAT_200016fb = '\x01';
  }
  return DAT_200016f9;
}

