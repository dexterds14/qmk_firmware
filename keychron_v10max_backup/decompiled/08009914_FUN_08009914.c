// FUN_08009914 @ 0x08009914  size=254  body=[[08009914, 08009a11]]

void FUN_08009914(undefined4 *param_1,undefined4 *param_2,uint param_3)

{
  undefined4 *puVar1;
  undefined4 *puVar2;
  undefined4 *puVar3;
  int iVar4;
  uint uVar5;
  undefined1 *puVar6;
  undefined4 *puVar7;
  
  if ((param_2 < param_1) && (puVar3 = (undefined4 *)((int)param_2 + param_3), param_1 < puVar3)) {
    puVar6 = (undefined1 *)((int)param_1 + param_3);
    if (param_3 == 0) {
      return;
    }
    do {
      puVar3 = (undefined4 *)((int)puVar3 + -1);
      puVar6 = puVar6 + -1;
      *puVar6 = *(undefined1 *)puVar3;
    } while (param_2 != puVar3);
    return;
  }
  if (param_3 < 0x10) {
    if (param_3 == 0) {
      return;
    }
  }
  else if ((((uint)param_1 | (uint)param_2) & 3) == 0) {
    puVar1 = param_2 + 4;
    puVar3 = param_1;
    do {
      *puVar3 = puVar1[-4];
      puVar3[1] = puVar1[-3];
      puVar3[2] = puVar1[-2];
      puVar3[3] = puVar1[-1];
      puVar1 = puVar1 + 4;
      puVar3 = puVar3 + 4;
    } while (puVar1 != (undefined4 *)((int)param_2 + (param_3 - 0x10 & 0xfffffff0) + 0x20));
    iVar4 = (param_3 - 0x10 >> 4) + 1;
    puVar3 = param_2 + iVar4 * 4;
    uVar5 = param_3 & 0xf;
    puVar1 = param_1 + iVar4 * 4;
    if ((param_3 & 0xc) != 0) {
      puVar2 = puVar1 + -1;
      puVar7 = puVar3;
      do {
        puVar2 = puVar2 + 1;
        *puVar2 = *puVar7;
        puVar7 = puVar7 + 1;
      } while (puVar2 != (undefined4 *)((uVar5 - 4 & 0xfffffffc) + (int)puVar1));
      iVar4 = (uVar5 - 4 >> 2) + 1;
      uVar5 = param_3 & 3;
      puVar1 = puVar1 + iVar4;
      puVar3 = puVar3 + iVar4;
    }
    if (uVar5 != 0) {
      puVar6 = (undefined1 *)((int)puVar1 + -1);
      puVar1 = puVar3;
      do {
        puVar2 = (undefined4 *)((int)puVar1 + 1);
        puVar6 = puVar6 + 1;
        *puVar6 = *(undefined1 *)puVar1;
        puVar1 = puVar2;
      } while (puVar2 != (undefined4 *)(uVar5 + (int)puVar3));
    }
    return;
  }
  puVar6 = (undefined1 *)((int)param_1 + -1);
  puVar3 = param_2;
  do {
    puVar1 = (undefined4 *)((int)puVar3 + 1);
    puVar6 = puVar6 + 1;
    *puVar6 = *(undefined1 *)puVar3;
    puVar3 = puVar1;
  } while (puVar1 != (undefined4 *)(param_3 + (int)param_2));
  return;
}

