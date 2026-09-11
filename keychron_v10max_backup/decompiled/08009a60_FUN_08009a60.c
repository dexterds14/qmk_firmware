// FUN_08009a60 @ 0x08009a60  size=158  body=[[08009a60, 08009afd]]

byte * FUN_08009a60(uint *param_1,uint param_2,uint param_3)

{
  char cVar1;
  char cVar2;
  char cVar3;
  char cVar4;
  byte *pbVar5;
  uint *puVar6;
  byte *pbVar7;
  uint uVar8;
  uint uVar9;
  uint uVar10;
  uint uVar11;
  uint uVar12;
  bool bVar13;
  bool bVar14;
  bool bVar15;
  bool bVar16;
  
  uVar8 = param_2 & 0xff;
  if ((int)param_3 < 0x10) {
joined_r0x08009ac0:
    do {
      if (param_3 == 0) {
        return (byte *)0x0;
      }
      puVar6 = (uint *)((int)param_1 + 1);
      uVar9 = *param_1;
      param_3 = param_3 - 1;
      param_1 = puVar6;
    } while ((byte)uVar9 != uVar8);
  }
  else {
    while( true ) {
      if (((uint)param_1 & 7) == 0) {
        uVar9 = uVar8 | uVar8 << 8;
        uVar9 = uVar9 | uVar9 << 0x10;
        uVar10 = param_3 & 0xfffffff8;
        do {
          puVar6 = param_1 + 2;
          uVar10 = uVar10 - 8;
          uVar11 = *param_1 ^ uVar9;
          uVar12 = param_1[1] ^ uVar9;
          cVar1 = -((char)uVar11 == '\0');
          cVar2 = -((char)(uVar11 >> 8) == '\0');
          cVar3 = -((char)(uVar11 >> 0x10) == '\0');
          cVar4 = -((char)(uVar11 >> 0x18) == '\0');
          uVar11 = CONCAT13(cVar4,CONCAT12(cVar3,CONCAT11(cVar2,cVar1)));
          bVar13 = (char)uVar12 != '\0';
          bVar14 = (char)(uVar12 >> 8) != '\0';
          bVar15 = (char)(uVar12 >> 0x10) != '\0';
          bVar16 = (char)(uVar12 >> 0x18) != '\0';
          uVar12 = CONCAT13(bVar16 * cVar4 - !bVar16,
                            CONCAT12(bVar15 * cVar3 - !bVar15,
                                     CONCAT11(bVar14 * cVar2 - !bVar14,bVar13 * cVar1 - !bVar13)));
          if (uVar12 != 0) {
            if (uVar11 == 0) {
              pbVar7 = (byte *)((int)param_1 + 5);
              uVar11 = uVar12;
            }
            else {
              pbVar7 = (byte *)((int)param_1 + 1);
            }
            if ((uVar11 & 1) == 0) {
              bVar13 = (uVar11 & 0x100) == 0;
              pbVar5 = pbVar7 + 1;
              if (bVar13) {
                pbVar5 = pbVar7 + 2;
              }
              pbVar7 = pbVar5;
              if (bVar13 && (uVar11 & 0x18000) == 0) {
                pbVar7 = pbVar7 + 1;
              }
            }
            return pbVar7 + -1;
          }
          param_1 = puVar6;
        } while (uVar10 != 0);
        param_3 = param_3 & 7;
        goto joined_r0x08009ac0;
      }
      puVar6 = (uint *)((int)param_1 + 1);
      param_3 = param_3 - 1;
      if ((byte)*param_1 == uVar8) break;
      param_1 = puVar6;
      if (param_3 == 0) {
        return (byte *)0x0;
      }
    }
  }
  return (byte *)((int)puVar6 + -1);
}

