// FUN_080086c0 @ 0x080086c0  size=216  body=[[080086c0, 08008797]]

int FUN_080086c0(uint param_1)

{
  char cVar1;
  char cVar2;
  char cVar3;
  char cVar4;
  int iVar5;
  int iVar6;
  uint *puVar7;
  uint uVar8;
  uint uVar9;
  uint uVar10;
  bool bVar11;
  bool bVar12;
  bool bVar13;
  bool bVar14;
  
  HintPreloadData(param_1);
  puVar7 = (uint *)(param_1 & 0xfffffff8);
  HintPreloadData(puVar7 + 8);
  if ((param_1 & 7) != 0) {
    uVar9 = puVar7[1];
    iVar6 = -(param_1 & 7);
    HintPreloadData(puVar7 + 0x10);
    uVar10 = -1 << ((param_1 & 3) << 3);
    uVar8 = *puVar7 | ~uVar10;
    if ((param_1 & 4) == 0) goto LAB_080086ee;
    uVar9 = uVar9 | ~uVar10;
    uVar8 = 0xffffffff;
    goto LAB_080086ee;
  }
  iVar5 = -8;
  do {
    uVar9 = puVar7[1];
    HintPreloadData(puVar7 + 0x10);
    iVar6 = iVar5 + 8;
    uVar8 = *puVar7;
LAB_080086ee:
    cVar1 = -((char)uVar8 == '\0');
    cVar2 = -((char)(uVar8 >> 8) == '\0');
    cVar3 = -((char)(uVar8 >> 0x10) == '\0');
    cVar4 = -((char)(uVar8 >> 0x18) == '\0');
    uVar8 = CONCAT13(cVar4,CONCAT12(cVar3,CONCAT11(cVar2,cVar1)));
    bVar11 = (char)uVar9 != '\0';
    bVar12 = (char)(uVar9 >> 8) != '\0';
    bVar13 = (char)(uVar9 >> 0x10) != '\0';
    bVar14 = (char)(uVar9 >> 0x18) != '\0';
    uVar9 = CONCAT13(bVar14 * cVar4 - !bVar14,
                     CONCAT12(bVar13 * cVar3 - !bVar13,
                              CONCAT11(bVar12 * cVar2 - !bVar12,bVar11 * cVar1 - !bVar11)));
    iVar5 = iVar6;
    if (uVar9 != 0) break;
    uVar8 = puVar7[2];
    uVar9 = puVar7[3];
    iVar5 = iVar6 + 8;
    cVar1 = -((char)uVar8 == '\0');
    cVar2 = -((char)(uVar8 >> 8) == '\0');
    cVar3 = -((char)(uVar8 >> 0x10) == '\0');
    cVar4 = -((char)(uVar8 >> 0x18) == '\0');
    uVar8 = CONCAT13(cVar4,CONCAT12(cVar3,CONCAT11(cVar2,cVar1)));
    bVar11 = (char)uVar9 != '\0';
    bVar12 = (char)(uVar9 >> 8) != '\0';
    bVar13 = (char)(uVar9 >> 0x10) != '\0';
    bVar14 = (char)(uVar9 >> 0x18) != '\0';
    uVar9 = CONCAT13(bVar14 * cVar4 - !bVar14,
                     CONCAT12(bVar13 * cVar3 - !bVar13,
                              CONCAT11(bVar12 * cVar2 - !bVar12,bVar11 * cVar1 - !bVar11)));
    if (uVar9 != 0) break;
    uVar8 = puVar7[4];
    uVar9 = puVar7[5];
    iVar5 = iVar6 + 0x10;
    cVar1 = -((char)uVar8 == '\0');
    cVar2 = -((char)(uVar8 >> 8) == '\0');
    cVar3 = -((char)(uVar8 >> 0x10) == '\0');
    cVar4 = -((char)(uVar8 >> 0x18) == '\0');
    uVar8 = CONCAT13(cVar4,CONCAT12(cVar3,CONCAT11(cVar2,cVar1)));
    bVar11 = (char)uVar9 != '\0';
    bVar12 = (char)(uVar9 >> 8) != '\0';
    bVar13 = (char)(uVar9 >> 0x10) != '\0';
    bVar14 = (char)(uVar9 >> 0x18) != '\0';
    uVar9 = CONCAT13(bVar14 * cVar4 - !bVar14,
                     CONCAT12(bVar13 * cVar3 - !bVar13,
                              CONCAT11(bVar12 * cVar2 - !bVar12,bVar11 * cVar1 - !bVar11)));
    if (uVar9 != 0) break;
    uVar8 = puVar7[6];
    uVar9 = puVar7[7];
    puVar7 = puVar7 + 8;
    iVar5 = iVar6 + 0x18;
    cVar1 = -((char)uVar8 == '\0');
    cVar2 = -((char)(uVar8 >> 8) == '\0');
    cVar3 = -((char)(uVar8 >> 0x10) == '\0');
    cVar4 = -((char)(uVar8 >> 0x18) == '\0');
    uVar8 = CONCAT13(cVar4,CONCAT12(cVar3,CONCAT11(cVar2,cVar1)));
    bVar11 = (char)uVar9 != '\0';
    bVar12 = (char)(uVar9 >> 8) != '\0';
    bVar13 = (char)(uVar9 >> 0x10) != '\0';
    bVar14 = (char)(uVar9 >> 0x18) != '\0';
    uVar9 = CONCAT13(bVar14 * cVar4 - !bVar14,
                     CONCAT12(bVar13 * cVar3 - !bVar13,
                              CONCAT11(bVar12 * cVar2 - !bVar12,bVar11 * cVar1 - !bVar11)));
  } while (uVar9 == 0);
  if (uVar8 == 0) {
    iVar5 = iVar5 + 4;
    uVar8 = uVar9;
  }
  return iVar5 + ((uint)LZCOUNT(uVar8 << 0x18 | (uVar8 >> 8 & 0xff) << 0x10 |
                                (uVar8 >> 0x10 & 0xff) << 8 | uVar8 >> 0x18) >> 3);
}

