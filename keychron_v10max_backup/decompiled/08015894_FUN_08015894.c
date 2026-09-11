// FUN_08015894 @ 0x08015894  size=122  body=[[08015894, 0801590d]]

void FUN_08015894(int param_1,int param_2)

{
  int iVar1;
  uint *puVar2;
  int iVar3;
  uint uVar4;
  uint uVar5;
  uint *puVar6;
  
  puVar6 = *(uint **)(param_1 + param_2 * 4 + 0xc);
  puVar2 = (uint *)puVar6[6];
  puVar2[4] = *puVar2;
  if ((param_2 == 0) && (0x40 < *puVar2)) {
    *puVar2 = 0x40;
  }
  uVar4 = (uint)*(ushort *)((int)puVar6 + 0x12);
  iVar3 = *(int *)(param_1 + 0x54);
  uVar5 = ((*puVar2 + uVar4) - 1) / uVar4;
  *(uint *)(iVar3 + param_2 * 0x20 + 0xb10) =
       uVar5 * uVar4 + 3 & 0xfffffffc | uVar5 << 0x13 | 0x60000000;
  if ((*puVar6 & 3) == 1) {
    iVar1 = iVar3 + (short)param_2 * 0x20;
    uVar4 = *(uint *)(iVar1 + 0xb00);
    if ((*(uint *)(iVar3 + 0x808) & 0x100) == 0) {
      uVar4 = uVar4 | 0x20000000;
    }
    else {
      uVar4 = uVar4 | 0x10000000;
    }
    *(uint *)(iVar1 + 0xb00) = uVar4;
  }
  iVar3 = iVar3 + (short)param_2 * 0x20;
  *(uint *)(iVar3 + 0xb00) = *(uint *)(iVar3 + 0xb00) | 0x84000000;
  return;
}

