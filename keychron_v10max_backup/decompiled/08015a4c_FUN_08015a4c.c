// FUN_08015a4c @ 0x08015a4c  size=268  body=[[08015a4c, 08015b57]]

void FUN_08015a4c(uint param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  bool bVar1;
  uint uVar2;
  uint uVar3;
  int iVar4;
  uint *puVar5;
  code *pcVar6;
  uint uVar7;
  undefined4 *puVar8;
  int iVar9;
  uint uVar10;
  undefined4 *puVar11;
  int iVar12;
  uint uVar13;
  
  iVar9 = DAT_20004b38;
  iVar4 = DAT_20004b38 + param_1 * 0x20;
  uVar10 = *(uint *)(iVar4 + 0x908);
  *(uint *)(iVar4 + 0x908) = uVar10;
  if (((uVar10 & 1) != 0) && (*(int *)(iVar9 + 0x810) << 0x1f < 0)) {
    puVar5 = *(uint **)((&DAT_20004ae8)[param_1 + 2] + 0x14);
    if (*puVar5 < puVar5[4]) {
      *puVar5 = puVar5[4] - *puVar5;
      puVar5[1] = 0;
      bVar1 = (bool)isCurrentModePrivileged();
      if (bVar1) {
        setBasePriority(0x30);
      }
      FUN_080159c0(0x20004ae4,param_1);
      bVar1 = (bool)isCurrentModePrivileged();
      if (bVar1) {
        setBasePriority(0);
      }
    }
    else {
      iVar4 = 1 << (param_1 & 0xff);
      DAT_20004aec = DAT_20004aec & ~(ushort)iVar4;
      pcVar6 = *(code **)((&DAT_20004ae8)[param_1 + 2] + 8);
      if (pcVar6 != (code *)0x0) {
        (*pcVar6)(&DAT_20004ae4,param_1,iVar4,pcVar6,param_4);
      }
      bVar1 = (bool)isCurrentModePrivileged();
      if (bVar1) {
        setBasePriority(0x30);
      }
      FUN_08013ab0((undefined4 *)(*(int *)((&DAT_20004ae8)[param_1 + 2] + 0x14) + 0xc),0);
      bVar1 = (bool)isCurrentModePrivileged();
      if (bVar1) {
        setBasePriority(0);
      }
    }
  }
  iVar4 = DAT_20004b38;
  if (((uVar10 & 0x80) != 0) &&
     (uVar10 = 1 << (param_1 & 0xff), (*(uint *)(iVar9 + 0x834) & uVar10) != 0)) {
    iVar12 = (&DAT_20004af0)[param_1];
    puVar5 = *(uint **)(iVar12 + 0x14);
    uVar13 = *puVar5;
    puVar8 = (undefined4 *)(DAT_20004b38 + (param_1 + 1 & 0xff) * 0x1000);
    iVar9 = param_1 * 0x20 + DAT_20004b38;
    while (uVar3 = puVar5[1], uVar3 < uVar13) {
      uVar2 = (uint)*(ushort *)(iVar12 + 0x10);
      uVar7 = uVar13 - uVar3;
      if (uVar2 <= uVar7) {
        uVar7 = uVar2;
      }
      if ((*(uint *)(iVar9 + 0x918) & 0xffff) * 4 < uVar7) {
        return;
      }
      uVar2 = puVar5[2];
      puVar11 = (undefined4 *)(uVar2 - 4);
      do {
        puVar11 = puVar11 + 1;
        *puVar8 = *puVar11;
      } while (4 < (uVar2 - (int)puVar11) + uVar7);
      puVar5[2] = uVar2 + uVar7;
      puVar5[1] = uVar3 + uVar7;
    }
    *(uint *)(iVar4 + 0x834) = *(uint *)(iVar4 + 0x834) & ~uVar10;
  }
  return;
}

