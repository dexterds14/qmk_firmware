// FUN_08015910 @ 0x08015910  size=170  body=[[08015910, 080159b9]]

void FUN_08015910(uint param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  bool bVar1;
  int iVar2;
  int iVar3;
  uint *puVar4;
  int iVar5;
  
  iVar2 = DAT_20004b38;
  iVar3 = DAT_20004b38 + param_1 * 0x20;
  iVar5 = *(int *)(iVar3 + 0xb08);
  *(int *)(iVar3 + 0xb08) = iVar5;
  if ((iVar5 << 0x1c < 0) && (*(int *)(iVar2 + 0x814) << 0x1c < 0)) {
    (**(code **)((&DAT_20004af0)[param_1] + 4))
              (&DAT_20004ae4,param_1,param_3,*(code **)((&DAT_20004af0)[param_1] + 4),param_4);
  }
  if ((iVar5 << 0x1f < 0) && (*(int *)(iVar2 + 0x814) << 0x1f < 0)) {
    iVar2 = (&DAT_20004ae8)[param_1 + 2];
    puVar4 = *(uint **)(iVar2 + 0x18);
    if ((param_1 == 0) &&
       (puVar4[1] == (uint)*(ushort *)(iVar2 + 0x12) * (puVar4[1] / (uint)*(ushort *)(iVar2 + 0x12))
       )) {
      if (*puVar4 < puVar4[4]) {
        *puVar4 = puVar4[4] - *puVar4;
        puVar4[1] = 0;
        bVar1 = (bool)isCurrentModePrivileged();
        if (bVar1) {
          setBasePriority(0x30);
        }
        FUN_08015894(0x20004ae4,0);
        bVar1 = (bool)isCurrentModePrivileged();
        if (!bVar1) {
          return;
        }
        setBasePriority(0);
        return;
      }
    }
    DAT_20004aee = DAT_20004aee & ~(ushort)(1 << (param_1 & 0xff));
    if (*(code **)(iVar2 + 0xc) != (code *)0x0) {
      (**(code **)(iVar2 + 0xc))(&DAT_20004ae4,param_1);
    }
    bVar1 = (bool)isCurrentModePrivileged();
    if (bVar1) {
      setBasePriority(0x30);
    }
    FUN_08013ab0((undefined4 *)(*(int *)((&DAT_20004ae8)[param_1 + 2] + 0x18) + 0xc),
                 *(int *)(*(int *)((&DAT_20004ae8)[param_1 + 2] + 0x18) + 4));
    bVar1 = (bool)isCurrentModePrivileged();
    if (bVar1) {
      setBasePriority(0);
    }
  }
  return;
}

