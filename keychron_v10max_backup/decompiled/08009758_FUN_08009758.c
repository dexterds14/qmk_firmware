// FUN_08009758 @ 0x08009758  size=252  body=[[08009758, 08009853]]

uint FUN_08009758(undefined4 *param_1,uint param_2)

{
  uint *puVar1;
  uint *puVar2;
  int iVar3;
  uint uVar4;
  uint *puVar5;
  uint *puVar6;
  uint uVar7;
  uint uVar8;
  
  uVar8 = (param_2 + 3 & 0xfffffffc) + 8;
  if (uVar8 < 0xc) {
    uVar8 = 0xc;
  }
  if (((int)uVar8 < 0) || (uVar8 < param_2)) {
    *param_1 = 0xc;
  }
  else {
    FUN_08009fd0();
    puVar5 = DAT_200014f8;
    puVar6 = DAT_200014f8;
    while (puVar1 = puVar5, puVar1 != (uint *)0x0) {
      uVar4 = *puVar1 - uVar8;
      if (-1 < (int)uVar4) {
        if (uVar4 < 0xc) {
          puVar5 = (uint *)puVar1[1];
          if (puVar1 == puVar6) goto LAB_080097bc;
          goto LAB_0800979e;
        }
        puVar2 = (uint *)((int)puVar1 + uVar8);
        *puVar1 = uVar8;
        puVar5 = puVar2;
        if (puVar1 != puVar6) {
          puVar6[1] = (uint)puVar2;
          puVar5 = DAT_200014f8;
        }
        DAT_200014f8 = puVar5;
        *(uint *)((int)puVar1 + uVar8) = uVar4;
        puVar2[1] = puVar1[1];
        puVar5 = DAT_200014f8;
        goto LAB_080097bc;
      }
      puVar6 = puVar1;
      puVar5 = (uint *)puVar1[1];
    }
    puVar1 = (uint *)FUN_08009710(param_1,uVar8);
    if (puVar1 != (uint *)0xffffffff) {
      *puVar1 = uVar8;
      puVar5 = DAT_200014f8;
LAB_080097bc:
      DAT_200014f8 = puVar5;
      FUN_08009fd4();
      puVar6 = puVar1 + 1;
      uVar8 = (int)puVar1 + 0xbU & 0xfffffff8;
      iVar3 = uVar8 - (int)puVar6;
      if (iVar3 != 0) {
        puVar6 = (uint *)((int)puVar6 - uVar8);
      }
      if (iVar3 != 0) {
        *(uint **)((int)puVar1 + iVar3) = puVar6;
      }
      return uVar8;
    }
    puVar6 = DAT_200014f8;
    if (DAT_200014f8 != (uint *)0x0) {
      do {
        puVar1 = puVar6;
        puVar6 = (uint *)puVar1[1];
      } while ((uint *)puVar1[1] != (uint *)0x0);
      uVar4 = *puVar1;
      iVar3 = FUN_080166a4(param_1,0);
      if ((int)puVar1 + uVar4 == iVar3) {
        uVar7 = *puVar1;
        uVar4 = FUN_08009710(param_1,uVar8 - uVar7);
        puVar6 = DAT_200014f8;
        if (uVar4 != 0xffffffff) {
          *puVar1 = *puVar1 + (uVar8 - uVar7);
          puVar5 = (uint *)puVar6[1];
          if ((uint *)puVar6[1] == (uint *)0x0) {
            puVar5 = (uint *)0x0;
          }
          else {
            while (puVar2 = puVar5, puVar2 != puVar1) {
              puVar6 = puVar2;
              puVar5 = (uint *)puVar2[1];
            }
            puVar5 = (uint *)0x0;
LAB_0800979e:
            puVar6[1] = (uint)puVar5;
            puVar5 = DAT_200014f8;
          }
          goto LAB_080097bc;
        }
      }
    }
    *param_1 = 0xc;
    FUN_08009fd4();
  }
  return 0;
}

