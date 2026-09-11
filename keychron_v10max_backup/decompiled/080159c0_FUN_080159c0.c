// FUN_080159c0 @ 0x080159c0  size=138  body=[[080159c0, 08015a49]]

void FUN_080159c0(int param_1,uint param_2)

{
  int iVar1;
  uint *puVar2;
  int iVar3;
  uint *puVar4;
  uint uVar5;
  
  puVar4 = *(uint **)(param_1 + param_2 * 4 + 0xc);
  iVar1 = *(int *)(param_1 + 0x54);
  puVar2 = (uint *)puVar4[5];
  uVar5 = *puVar2;
  puVar2[4] = uVar5;
  if (uVar5 == 0) {
    uVar5 = 0x80000;
  }
  else {
    if ((param_2 == 0) && (0x40 < uVar5)) {
      *puVar2 = 0x40;
    }
    uVar5 = *puVar2 | ((*puVar2 + (uint)(ushort)puVar4[4]) - 1) / (uint)(ushort)puVar4[4] << 0x13 |
            0x20000000;
  }
  *(uint *)(param_2 * 0x20 + iVar1 + 0x910) = uVar5;
  if ((*puVar4 & 3) == 1) {
    iVar3 = iVar1 + (short)param_2 * 0x20;
    uVar5 = *(uint *)(iVar3 + 0x900);
    if ((*(uint *)(iVar1 + 0x808) & 0x100) == 0) {
      uVar5 = uVar5 | 0x20000000;
    }
    else {
      uVar5 = uVar5 | 0x10000000;
    }
    *(uint *)(iVar3 + 0x900) = uVar5;
  }
  iVar3 = iVar1 + (short)param_2 * 0x20;
  *(uint *)(iVar3 + 0x900) = *(uint *)(iVar3 + 0x900) | 0x84000000;
  *(uint *)(iVar1 + 0x834) = 1 << (param_2 & 0xff) | *(uint *)(iVar1 + 0x834);
  return;
}

