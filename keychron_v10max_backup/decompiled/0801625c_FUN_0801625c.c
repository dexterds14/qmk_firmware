// FUN_0801625c @ 0x0801625c  size=160  body=[[0801625c, 080162fb]]

undefined4 FUN_0801625c(undefined1 *param_1)

{
  uint uVar1;
  undefined4 uVar2;
  undefined4 *puVar3;
  int iVar4;
  uint *puVar5;
  
  puVar3 = *(undefined4 **)(param_1 + 0x24);
  puVar5 = (uint *)*puVar3;
  if (*(char *)(*(int *)(param_1 + 4) + 1) == '\0') {
    *puVar5 = *puVar5 & 0xffffffe0;
    do {
    } while ((int)(*puVar5 << 0x1f) < 0);
    iVar4 = *(int *)(param_1 + 0x1c);
    *(int *)puVar3[1] = 0x3d << *(sbyte *)((int)puVar3 + 9);
    do {
    } while (*(int *)(iVar4 + 8) << 0x18 < 0);
    puVar3 = *(undefined4 **)(param_1 + 0x20);
    puVar5 = (uint *)*puVar3;
    *puVar5 = *puVar5 & 0xffffffe0;
    do {
    } while ((int)(*puVar5 << 0x1f) < 0);
    *(int *)puVar3[1] = 0x3d << *(sbyte *)((int)puVar3 + 9);
  }
  else {
    *puVar5 = *puVar5 & 0xffffffe0;
    do {
    } while ((int)(*puVar5 << 0x1f) < 0);
    *(int *)puVar3[1] = 0x3d << *(sbyte *)((int)puVar3 + 9);
    puVar3 = *(undefined4 **)(param_1 + 0x20);
    puVar5 = (uint *)*puVar3;
    *puVar5 = *puVar5 & 0xffffffe0;
    do {
    } while ((int)(*puVar5 << 0x1f) < 0);
    *(int *)puVar3[1] = 0x3d << *(sbyte *)((int)puVar3 + 9);
    if (param_1 == &DAT_20004b50) {
      uVar1 = DAT_40023824;
      DAT_40023824 = uVar1 | 0x1000;
      uVar1 = DAT_40023824;
      DAT_40023824 = uVar1 & 0xffffefff;
      uVar2 = DAT_40023824;
    }
    FUN_0801622c((int)param_1);
  }
  return 0;
}

