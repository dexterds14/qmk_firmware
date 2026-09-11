// Vector14C_IRQ67_OTG_FS @ 0x08015b5c  size=706  body=[[08015b5c, 08015dff] [08015e04, 08015e21]]

void Vector14C_IRQ67_OTG_FS(undefined4 param_1,undefined4 param_2,undefined1 *param_3)

{
  bool bVar1;
  undefined4 extraout_r1;
  undefined1 *puVar2;
  undefined1 *extraout_r1_00;
  undefined1 *extraout_r1_01;
  undefined1 *extraout_r1_02;
  undefined1 *extraout_r1_03;
  undefined1 *extraout_r1_04;
  undefined1 *extraout_r1_05;
  undefined1 *extraout_r1_06;
  int iVar3;
  int extraout_r1_07;
  int extraout_r1_08;
  undefined1 *extraout_r2;
  undefined4 extraout_r2_00;
  undefined1 *extraout_r2_01;
  undefined1 *extraout_r2_02;
  undefined1 *extraout_r2_03;
  undefined1 *extraout_r2_04;
  undefined1 *extraout_r2_05;
  undefined1 *extraout_r2_06;
  undefined1 *extraout_r2_07;
  undefined1 *extraout_r2_08;
  undefined1 *extraout_r2_09;
  int extraout_r2_10;
  undefined1 *puVar4;
  undefined4 extraout_r3;
  uint uVar5;
  undefined1 *puVar6;
  int iVar7;
  undefined1 *extraout_r3_00;
  undefined1 *extraout_r3_01;
  undefined1 *extraout_r3_02;
  undefined1 *extraout_r3_03;
  undefined1 *extraout_r3_04;
  int iVar8;
  uint uVar9;
  undefined1 *puVar10;
  uint *puVar11;
  int *piVar12;
  
  iVar8 = DAT_20004b38;
  uVar9 = *(uint *)(DAT_20004b38 + 0x14) & *(uint *)(DAT_20004b38 + 0x18);
  *(uint *)(DAT_20004b38 + 0x14) = uVar9;
  if ((uVar9 & 0x1000) == 0) {
    if ((int)uVar9 < 0) {
      if ((*(uint *)(iVar8 + 0xe00) & 3) != 0) {
        *(uint *)(iVar8 + 0xe00) = *(uint *)(iVar8 + 0xe00) & 0xfffffffc;
      }
      *(uint *)(iVar8 + 0x804) = *(uint *)(iVar8 + 0x804) & 0xfffffffe;
      FUN_08014462(&DAT_20004ae4);
      param_3 = extraout_r2;
    }
    if ((int)(uVar9 << 0x14) < 0) {
      FUN_080154cc(0x20004ae4);
      FUN_08014406(&DAT_20004ae4,extraout_r1,extraout_r2_00,extraout_r3);
      param_3 = extraout_r2_01;
    }
    if ((int)(uVar9 << 0x12) < 0) {
      uVar5 = *(uint *)(iVar8 + 0xc) & 0xffffc3ff;
      if ((*(uint *)(iVar8 + 0x808) & 6) == 0) {
        uVar5 = uVar5 | 0x2400;
      }
      else {
        uVar5 = uVar5 | 0x1400;
      }
      *(uint *)(iVar8 + 0xc) = uVar5;
    }
    puVar2 = (undefined1 *)(uVar9 << 0x1c);
    if ((int)puVar2 < 0) {
      if (*(int *)(DAT_20004ae8 + 0xc) == 0) {
        *(uint *)(iVar8 + 0x18) = *(uint *)(iVar8 + 0x18) & 0xfffffff7;
      }
      if (DAT_20004ae4 == '\x05') {
        if ((*(uint *)(iVar8 + 0xe00) & 3) != 0) {
          *(uint *)(iVar8 + 0xe00) = *(uint *)(iVar8 + 0xe00) & 0xfffffffc;
        }
        FUN_08014462(&DAT_20004ae4);
        puVar2 = extraout_r1_00;
        param_3 = extraout_r2_02;
      }
      if (*(code **)(DAT_20004ae8 + 0xc) != (code *)0x0) {
        (**(code **)(DAT_20004ae8 + 0xc))(&DAT_20004ae4);
        puVar2 = extraout_r1_01;
        param_3 = extraout_r2_03;
      }
    }
    iVar3 = DAT_20004b38;
    puVar6 = (undefined1 *)(uVar9 << 0xb);
    if ((int)puVar6 < 0) {
      puVar2 = (undefined1 *)0x0;
      do {
        iVar7 = iVar3 + (int)puVar2 * 0x20;
        param_3 = (undefined1 *)(*(uint *)(iVar7 + 0x900) & 0xc0000);
        if ((param_3 == (undefined1 *)0x40000) &&
           (param_3 = *(undefined1 **)(iVar7 + 0x900), (int)param_3 < 0)) {
          *(uint *)(iVar7 + 0x900) = *(uint *)(iVar7 + 0x900) | 0x48000000;
          do {
          } while (*(int *)(iVar7 + 0x900) < 0);
          FUN_08015522(DAT_20004b38,(int)puVar2);
          DAT_20004aec = DAT_20004aec & ~(ushort)(1 << (int)puVar2);
          if (*(code **)((&DAT_20004ae8)[(int)(puVar2 + 2)] + 8) != (code *)0x0) {
            (**(code **)((&DAT_20004ae8)[(int)(puVar2 + 2)] + 8))(&DAT_20004ae4,puVar2);
          }
          bVar1 = (bool)isCurrentModePrivileged();
          if (bVar1) {
            setBasePriority(0x30);
          }
          FUN_08013ab0((undefined4 *)(*(int *)((&DAT_20004ae8)[(int)(puVar2 + 2)] + 0x14) + 0xc),0);
          bVar1 = (bool)isCurrentModePrivileged();
          param_3 = extraout_r2_04;
          if (bVar1) {
            setBasePriority(0);
          }
        }
        puVar6 = *(undefined1 **)(DAT_20004b3c + 8);
        puVar2 = (undefined1 *)((uint)(puVar2 + 1) & 0xff);
      } while (puVar2 <= puVar6);
    }
    iVar3 = DAT_20004b38;
    if ((int)(uVar9 << 10) < 0) {
      puVar10 = (undefined1 *)0x0;
      do {
        param_3 = (undefined1 *)(iVar3 + (int)puVar10 * 0x20);
        if (((*(uint *)(param_3 + 0xb00) & 0xc0000) == 0x40000) && (*(int *)(param_3 + 0xb00) < 0))
        {
          DAT_20004aee = DAT_20004aee & ~(ushort)(1 << (int)puVar10);
          if (*(code **)((&DAT_20004ae8)[(int)(puVar10 + 2)] + 0xc) != (code *)0x0) {
            (**(code **)((&DAT_20004ae8)[(int)(puVar10 + 2)] + 0xc))(&DAT_20004ae4,puVar10);
          }
          bVar1 = (bool)isCurrentModePrivileged();
          if (bVar1) {
            setBasePriority(0x30);
          }
          FUN_08013ab0((undefined4 *)(*(int *)((&DAT_20004ae8)[(int)(puVar10 + 2)] + 0x18) + 0xc),
                       *(int *)(*(int *)((&DAT_20004ae8)[(int)(puVar10 + 2)] + 0x18) + 4));
          bVar1 = (bool)isCurrentModePrivileged();
          puVar2 = extraout_r1_02;
          param_3 = extraout_r2_05;
          if (bVar1) {
            setBasePriority(0);
          }
        }
        puVar6 = *(undefined1 **)(DAT_20004b3c + 8);
        puVar10 = (undefined1 *)((uint)(puVar10 + 1) & 0xff);
      } while (puVar10 <= puVar6);
    }
    if ((int)(uVar9 << 0x1b) < 0) {
      uVar5 = *(uint *)(DAT_20004b38 + 0x20);
      puVar10 = (undefined1 *)((uVar5 & 0x7fff) >> 4);
      puVar6 = (undefined1 *)(uVar5 & 0xf);
      param_3 = (undefined1 *)(uVar5 & 0x1e0000);
      if (param_3 == (undefined1 *)0x40000) {
        puVar11 = (uint *)(DAT_20004b38 + 0x1000);
        piVar12 = *(int **)((&DAT_20004ae8)[(int)(puVar6 + 2)] + 0x18);
        puVar4 = (undefined1 *)piVar12[2];
        iVar3 = *piVar12;
        iVar7 = piVar12[1];
        uVar5 = 0;
        for (puVar2 = (undefined1 *)0x0; puVar10 != puVar2; puVar2 = puVar2 + 1) {
          if (((uint)puVar2 & 3) == 0) {
            uVar5 = *puVar11;
          }
          if (puVar2 < (undefined1 *)(iVar3 - iVar7)) {
            *puVar4 = (char)uVar5;
            uVar5 = uVar5 >> 8;
            puVar4 = puVar4 + 1;
          }
        }
        puVar6 = *(undefined1 **)((&DAT_20004ae8)[(int)(puVar6 + 2)] + 0x18);
        *(undefined1 **)(puVar6 + 8) = puVar10 + *(int *)(puVar6 + 8);
        param_3 = puVar10 + *(int *)(puVar6 + 4);
        *(undefined1 **)(puVar6 + 4) = param_3;
      }
      else if (param_3 == (undefined1 *)0xc0000) {
        puVar6 = *(undefined1 **)((&DAT_20004af0)[(int)puVar6] + 0x20);
        puVar11 = (uint *)(DAT_20004b38 + 0x1000);
        uVar5 = 0;
        for (param_3 = (undefined1 *)0x0; puVar10 != param_3; param_3 = param_3 + 1) {
          puVar2 = (undefined1 *)((int)param_3 << 0x1e);
          if (puVar2 == (undefined1 *)0x0) {
            uVar5 = *puVar11;
          }
          if (param_3 < &NMI) {
            *puVar6 = (char)uVar5;
            uVar5 = uVar5 >> 8;
            puVar6 = puVar6 + 1;
          }
        }
      }
    }
    iVar8 = *(int *)(iVar8 + 0x818);
    if ((int)(uVar9 << 0xc) < 0) {
      puVar2 = (undefined1 *)(iVar8 << 0xf);
      if ((int)puVar2 < 0) {
        FUN_08015910(0,puVar2,param_3,puVar6);
        puVar2 = extraout_r1_03;
        puVar6 = extraout_r3_00;
      }
      param_3 = (undefined1 *)(iVar8 << 0xe);
      if ((int)param_3 < 0) {
        FUN_08015910(1,puVar2,param_3,puVar6);
        puVar2 = extraout_r1_04;
        param_3 = extraout_r2_06;
      }
      puVar6 = (undefined1 *)(iVar8 << 0xd);
      if ((int)puVar6 < 0) {
        FUN_08015910(2,puVar2,param_3,puVar6);
        puVar2 = extraout_r1_05;
        param_3 = extraout_r2_07;
        puVar6 = extraout_r3_01;
      }
      if (iVar8 << 0xc < 0) {
        FUN_08015910(3,puVar2,param_3,puVar6);
        puVar2 = extraout_r1_06;
        param_3 = extraout_r2_08;
        puVar6 = extraout_r3_02;
      }
    }
    if ((int)(uVar9 << 0xd) < 0) {
      if (iVar8 << 0x1f < 0) {
        FUN_08015a4c(0,puVar2,param_3,puVar6);
        param_3 = extraout_r2_09;
        puVar6 = extraout_r3_03;
      }
      iVar3 = iVar8 << 0x1e;
      if (iVar3 < 0) {
        FUN_08015a4c(1,iVar3,param_3,puVar6);
        iVar3 = extraout_r1_07;
        puVar6 = extraout_r3_04;
      }
      iVar7 = iVar8 << 0x1d;
      if (iVar7 < 0) {
        FUN_08015a4c(2,iVar3,iVar7,puVar6);
        iVar3 = extraout_r1_08;
        iVar7 = extraout_r2_10;
      }
      if (iVar8 << 0x1c < 0) {
        FUN_08015a4c(3,iVar3,iVar7,iVar8 << 0x1c);
      }
    }
  }
  else {
    FUN_08014396(&DAT_20004ae4);
  }
  FUN_08013c7c();
  return;
}

