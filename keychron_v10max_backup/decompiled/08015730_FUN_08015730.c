// FUN_08015730 @ 0x08015730  size=268  body=[[08015730, 0801583b]]

void FUN_08015730(int param_1,uint param_2)

{
  uint *puVar1;
  uint uVar2;
  uint uVar3;
  uint uVar4;
  int iVar5;
  uint uVar6;
  int iVar7;
  int iVar8;
  
  iVar8 = (int)(short)param_2;
  puVar1 = *(uint **)(param_1 + param_2 * 4 + 0xc);
  iVar5 = *(int *)(param_1 + 0x54);
  uVar6 = *puVar1 & 3;
  uVar3 = uVar6 - 1;
  *(undefined4 *)(iVar5 + param_2 * 0x20 + 0xb10) = 0;
  if (uVar3 < 3) {
    uVar6 = uVar6 << 0x12;
  }
  uVar4 = 1 << (param_2 + 0x10 & 0xff);
  if (uVar3 < 3) {
    uVar6 = uVar6 + 0x10008000;
  }
  else {
    uVar6 = 0x10008000;
  }
  if (puVar1[6] == 0) {
    iVar7 = iVar5 + iVar8 * 0x20;
    *(uint *)(iVar7 + 0xb00) = *(uint *)(iVar7 + 0xb00) & 0xffff7fff;
    uVar4 = *(uint *)(iVar5 + 0x81c) & ~uVar4;
  }
  else {
    *(uint *)(iVar5 + (param_2 + 0x58) * 0x20) = *(ushort *)((int)puVar1 + 0x12) | uVar6;
    uVar4 = uVar4 | *(uint *)(iVar5 + 0x81c);
  }
  *(uint *)(iVar5 + 0x81c) = uVar4;
  *(undefined4 *)(iVar5 + param_2 * 0x20 + 0x910) = 0;
  uVar3 = 1 << (param_2 & 0xff);
  if (puVar1[5] == 0) {
    *(undefined4 *)(iVar5 + (param_2 + 0x3f) * 4 + 4) = 0x2000400;
    FUN_08015522(iVar5,param_2);
    iVar8 = iVar5 + iVar8 * 0x20;
    *(uint *)(iVar8 + 0x900) = *(uint *)(iVar8 + 0x900) & 0xffff7fff;
    uVar3 = *(uint *)(iVar5 + 0x81c) & ~uVar3;
  }
  else {
    uVar4 = (uint)(ushort)((ushort)puVar1[4] >> 2);
    if (1 < (ushort)puVar1[7]) {
      uVar4 = (ushort)puVar1[7] * uVar4;
    }
    uVar2 = *(uint *)(param_1 + 0x5c);
    *(uint *)(param_1 + 0x5c) = uVar4 + uVar2;
    *(uint *)(iVar5 + (param_2 + 0x3f) * 4 + 4) = uVar2 | uVar4 << 0x10;
    FUN_08015522(iVar5,param_2);
    *(uint *)(iVar5 + (param_2 + 0x48) * 0x20) =
         (uint)*(ushort *)(*(int *)(param_1 + iVar8 * 4 + 0xc) + 0x10) | param_2 << 0x16 | uVar6;
    uVar3 = *(uint *)(iVar5 + 0x81c) | uVar3;
  }
  *(uint *)(iVar5 + 0x81c) = uVar3;
  return;
}

