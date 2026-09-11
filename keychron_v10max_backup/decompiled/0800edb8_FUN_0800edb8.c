// FUN_0800edb8 @ 0x0800edb8  size=152  body=[[0800edb8, 0800ee4f]]

void FUN_0800edb8(int param_1,int param_2,uint param_3)

{
  bool bVar1;
  uint *puVar2;
  uint uVar3;
  uint uVar4;
  uint *puVar5;
  
  uVar3 = (&DAT_08016f34)[param_2];
  if (uVar3 != 0xffffffff) {
    bVar1 = (bool)isCurrentModePrivileged();
    if (bVar1) {
      setBasePriority(0x30);
    }
    uVar4 = 1 << (uVar3 & 0xf);
    FUN_08015338((uint *)(uVar3 & 0xfffffff0),uVar4,1);
    *(short *)((int)(uVar3 & 0xfffffff0) + 0x1a) = (short)uVar4;
    bVar1 = (bool)isCurrentModePrivileged();
    if (bVar1) {
      setBasePriority(0);
    }
    FUN_0800ed36();
    puVar2 = (uint *)(param_1 + -4);
    puVar5 = &DAT_08016f7c;
    do {
      uVar3 = *puVar5;
      puVar2 = puVar2 + 1;
      if ((uVar3 == 0xffffffff) ||
         ((int)((*(uint *)((uVar3 & 0xfffffff0) + 0x10) >> (uVar3 & 0xf)) << 0x1f) < 0)) {
        uVar3 = ~param_3 & *puVar2;
      }
      else {
        uVar3 = *puVar2 | param_3;
      }
      *puVar2 = uVar3;
      puVar5 = puVar5 + 1;
    } while ((uint *)(param_1 + 0x14) != puVar2);
    if ((&DAT_08016f34)[param_2] != 0xffffffff) {
      FUN_0800ed58((&DAT_08016f34)[param_2]);
    }
    FUN_0800ed50();
    return;
  }
  return;
}

