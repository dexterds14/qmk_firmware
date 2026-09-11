// FUN_080154cc @ 0x080154cc  size=86  body=[[080154cc, 08015521]]

void FUN_080154cc(int param_1)

{
  int iVar1;
  uint uVar2;
  int iVar3;
  int iVar4;
  uint uVar5;
  
  iVar4 = *(int *)(param_1 + 0x54);
  uVar5 = *(uint *)(*(int *)(param_1 + 0x58) + 8);
  uVar2 = 0;
  do {
    iVar3 = iVar4 + uVar2 * 0x20;
    iVar1 = uVar2 * 0x20;
    if (*(int *)(iVar3 + 0x900) < 0) {
      *(uint *)(iVar3 + 0x900) = *(uint *)(iVar3 + 0x900) | 0x40000000;
    }
    if (*(int *)(iVar3 + 0xb00) < 0) {
      *(uint *)(iVar3 + 0xb00) = *(uint *)(iVar3 + 0xb00) | 0x40000000;
    }
    uVar2 = uVar2 + 1;
    iVar1 = iVar4 + iVar1;
    *(undefined4 *)(iVar1 + 0x908) = 0xffffffff;
    *(undefined4 *)(iVar1 + 0xb08) = 0xffffffff;
  } while (uVar2 <= uVar5);
  *(undefined4 *)(iVar4 + 0x81c) = 0x10001;
  return;
}

