// FUN_0800b008 @ 0x0800b008  size=616  body=[[0800b008, 0800b083] [0800b08c, 0800b277]]

void FUN_0800b008(void)

{
  char cVar1;
  undefined4 extraout_r1;
  undefined4 extraout_r1_00;
  int iVar2;
  int extraout_r1_01;
  char cVar3;
  undefined4 extraout_r2;
  undefined4 extraout_r2_00;
  undefined4 extraout_r2_01;
  undefined4 extraout_r2_02;
  undefined4 uVar4;
  uint uVar5;
  undefined1 uVar6;
  uint uVar7;
  char *pcVar8;
  uint uVar9;
  byte *pbVar10;
  byte bVar11;
  char cVar12;
  undefined4 local_64;
  byte abStack_60 [4];
  char local_5c;
  byte local_5b;
  undefined1 local_5a;
  undefined1 local_59;
  char local_58;
  undefined2 local_57;
  char local_55 [57];
  
  iVar2 = DAT_40020410;
  bVar11 = 0;
  cVar12 = '\0';
  if (-1 < iVar2 << 0x1e) {
    FUN_08008798(abStack_60,0,0x40);
    FUN_0800ada0((uint)abStack_60,DAT_20000ca2);
    if ((local_5c == -0x56) &&
       (((uVar9 = (uint)local_5b, uVar9 != 0x54 || (local_58 != -0x55)) || ((char)local_57 != 'U')))
       ) {
      local_64._0_2_ = 0;
      uVar4 = extraout_r2;
      if ((int)(uVar9 << 0x1c) < 0) {
        local_64._0_2_ = CONCAT11(local_5a,1);
        FUN_0800a1fc((undefined2)local_64,extraout_r1,extraout_r2);
        uVar4 = extraout_r2_00;
      }
      if ((int)(uVar9 << 0x1f) < 0) {
        FUN_0800adf8();
        switch(local_5a) {
        case 0x20:
          local_64._0_1_ = 4;
          break;
        case 0x21:
          local_64._0_1_ = 2;
          break;
        case 0x22:
          local_64._0_1_ = 3;
          break;
        case 0x23:
          local_64._0_1_ = 5;
          break;
        case 0x24:
          local_64._0_1_ = 6;
          break;
        case 0x25:
          local_64._0_1_ = 7;
          break;
        case 0x26:
          local_64._0_1_ = 8;
        }
        local_64._0_2_ = CONCAT11(local_59,(undefined1)local_64);
        FUN_0800a1fc((undefined2)local_64,extraout_r1_00,extraout_r2_01);
        uVar4 = extraout_r2_02;
      }
      iVar2 = uVar9 << 0x1e;
      if (iVar2 < 0) {
        local_64._0_2_ = CONCAT11(local_58,10);
        FUN_0800a1fc((undefined2)local_64,iVar2,uVar4);
        iVar2 = extraout_r1_01;
      }
      if ((int)(uVar9 << 0x1b) < 0) {
        if (local_55[1] < '\0') {
          uVar7 = ((byte)local_55[1] & 0x7f) * 0x4e2;
        }
        else {
          uVar7 = (uint)(byte)local_55[1] * 0x7d;
        }
        uVar5 = uVar7 / 1000;
        if (7999 < uVar7) {
          uVar5 = uVar5 / 3;
        }
        DAT_20000ca0 = (undefined2)uVar5;
        local_64 = CONCAT31((uint3)(byte)uVar5,0xb);
        FUN_0800a1fc((short)local_64,iVar2,uVar5);
      }
      if ((int)(uVar9 << 0x1d) < 0) {
        FUN_0800c074(1,(uint)local_57);
      }
    }
    if (DAT_20000c73 == '\0') {
      pbVar10 = abStack_60;
    }
    else {
      cVar3 = '1';
      cVar1 = '\0';
      pbVar10 = abStack_60;
      pcVar8 = (char *)((int)&local_57 + 1);
      do {
        if (((*pcVar8 == -0x56) && (pcVar8[1] == 'W')) && (pcVar8[3] == ~pcVar8[2])) {
          cVar12 = pcVar8[4];
          pbVar10 = (byte *)(pcVar8 + 5);
          bVar11 = pcVar8[2];
          cVar1 = DAT_20000c73;
        }
        cVar3 = cVar3 + -1;
        pcVar8 = pcVar8 + 1;
      } while (cVar3 != '\0');
      if (cVar1 == '\0') {
        return;
      }
      DAT_20000c73 = '\0';
      DAT_20000c72 = bVar11;
      DAT_20001510 = cVar12;
    }
    uVar9 = (uint)DAT_20000c72;
    if (uVar9 < 0x3c) {
      DAT_20000c73 = '\x01';
      uVar7 = 0;
      for (iVar2 = 0; iVar2 < (int)(uVar9 - 2); iVar2 = iVar2 + 1) {
        uVar7 = uVar7 + pbVar10[iVar2] & 0xffff;
      }
      if (((uint)pbVar10[uVar9 - 2] == (uVar7 & 0xff)) && ((uint)pbVar10[uVar9 - 1] == uVar7 >> 8))
      {
        bVar11 = *pbVar10;
        uVar9 = uVar9 - 3 & 0xff;
        if (bVar11 == 0xa3) {
          FUN_0800af8c(0xa3,(undefined4 *)(pbVar10 + 1),uVar9,DAT_20001510);
        }
        else if (bVar11 < 0xa4) {
          if (bVar11 == 0xa1) {
            bVar11 = pbVar10[2];
            if (bVar11 < 0x15) {
              if (bVar11 < 0x11) {
                DAT_20000c73 = 1;
                return;
              }
            }
            else if (bVar11 != 0x16) {
              DAT_20000c73 = 1;
              return;
            }
            bVar11 = pbVar10[3];
            if (bVar11 == 2) {
              FUN_0800a8c8(0);
              cVar12 = (char)DAT_20000ca0 + '\x05';
            }
            else if (bVar11 == 3) {
              cVar12 = (char)DAT_20000ca0 + '\n';
            }
            else {
              if (bVar11 != 0) {
                DAT_20000c73 = 1;
                return;
              }
              FUN_0800a8c8(0);
              cVar12 = (char)DAT_20000ca0;
            }
            FUN_0800a8bc(cVar12);
          }
          else if (((bVar11 == 0xa2) && (pbVar10[3] == 0)) && (pbVar10[2] == 0x72)) {
            FUN_0800cb44((undefined4 *)(pbVar10 + 1),uVar9);
          }
        }
        else {
          if (bVar11 == 0xb0) {
            bVar11 = pbVar10[1];
            uVar6 = 1;
          }
          else {
            if (bVar11 != 0xb4) {
              DAT_20000c73 = 1;
              return;
            }
            bVar11 = pbVar10[1];
            uVar6 = 10;
          }
          FUN_0800a1fc(CONCAT11(bVar11,uVar6),uVar9,0);
        }
      }
    }
  }
  return;
}

