// FUN_0801622c @ 0x0801622c  size=46  body=[[0801622c, 08016259]]

void FUN_0801622c(int param_1)

{
  ushort uVar1;
  int iVar2;
  uint *puVar3;
  uint uVar4;
  uint uVar5;
  
  puVar3 = *(uint **)(param_1 + 0x1c);
  iVar2 = *(int *)(param_1 + 4);
  uVar1 = *(ushort *)(iVar2 + 0x16);
  *puVar3 = 0;
  uVar5 = *(ushort *)(iVar2 + 0x14) & 0xffffffbb;
  if (*(char *)(iVar2 + 1) == '\0') {
    uVar5 = uVar5 | 0x304;
    uVar4 = uVar1 | 7;
  }
  else {
    uVar4 = uVar1 | 3;
  }
  puVar3[1] = uVar4;
  *puVar3 = uVar5;
  *puVar3 = uVar5 | 0x40;
  return;
}

