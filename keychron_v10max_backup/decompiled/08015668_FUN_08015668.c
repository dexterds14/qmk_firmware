// FUN_08015668 @ 0x08015668  size=168  body=[[08015668, 0801570f]]

void FUN_08015668(int param_1)

{
  undefined4 *puVar1;
  int iVar2;
  uint uVar3;
  undefined4 uVar4;
  int iVar5;
  uint uVar6;
  
  iVar5 = *(int *)(param_1 + 0x54);
  FUN_08015522(iVar5,0);
  puVar1 = *(undefined4 **)(param_1 + 0x58);
  uVar3 = 0;
  uVar6 = puVar1[2];
  *(undefined4 *)(iVar5 + 0x834) = 0;
  *(undefined4 *)(iVar5 + 0x81c) = 0x10001;
  do {
    iVar2 = iVar5 + uVar3 * 0x20;
    uVar3 = uVar3 + 1;
    *(undefined4 *)(iVar2 + 0x900) = 0x8000000;
    *(undefined4 *)(iVar2 + 0xb00) = 0x8000000;
    *(undefined4 *)(iVar2 + 0x908) = 0xffffffff;
    *(undefined4 *)(iVar2 + 0xb08) = 0xffffffff;
  } while (uVar3 <= uVar6);
  uVar4 = *puVar1;
  iVar2 = *(int *)(param_1 + 0x54);
  *(undefined4 *)(param_1 + 0x5c) = uVar4;
  *(undefined4 *)(iVar5 + 0x24) = uVar4;
  *(undefined4 *)(iVar2 + 0x10) = 0x10;
  do {
  } while ((*(uint *)(iVar2 + 0x10) & 0x10) != 0);
  FUN_080135c8(0x12);
  *(uint *)(iVar5 + 0x800) = *(uint *)(iVar5 + 0x800) & 0xfffff80f;
  *(uint *)(iVar5 + 0x18) = *(uint *)(iVar5 + 0x18) | 0xc0010;
  *(undefined4 *)(iVar5 + 0x810) = 9;
  *(undefined4 *)(iVar5 + 0x814) = 9;
  *(undefined **)(param_1 + 0xc) = &DAT_08017590;
  *(undefined4 *)(iVar5 + 0xb10) = 0x60000000;
  *(undefined4 *)(iVar5 + 0xb00) = 0x10008040;
  *(undefined4 *)(iVar5 + 0x910) = 0;
  *(undefined4 *)(iVar5 + 0x900) = 0x10008040;
  uVar3 = *(uint *)(param_1 + 0x5c);
  *(uint *)(param_1 + 0x5c) = uVar3 + 0x10;
  *(uint *)(iVar5 + 0x28) = uVar3 | 0x100000;
  return;
}

