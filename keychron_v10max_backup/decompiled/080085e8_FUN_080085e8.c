// FUN_080085e8 @ 0x080085e8  size=16  body=[[080085e8, 080085f7]]

undefined1 * FUN_080085e8(void)

{
  bool bVar1;
  char *pcVar2;
  char cVar3;
  undefined1 *puVar4;
  uint extraout_r2;
  char *pcVar5;
  uint uVar6;
  int iVar7;
  int iVar8;
  char *pcVar9;
  char *pcVar10;
  undefined8 uVar11;
  char acStack_48 [44];
  
  FUN_0800920c(6);
  uVar11 = FUN_080166dc();
  puVar4 = (undefined1 *)((ulonglong)uVar11 >> 0x20);
  builtin_strncpy(acStack_48,"0123456789abcdefghijklmnopqrstuvwxyz",0x25);
  if (extraout_r2 - 2 < 0x23) {
    pcVar9 = puVar4 + -1;
    uVar6 = (uint)uVar11;
    iVar8 = 0;
    do {
      iVar7 = iVar8;
      pcVar9 = pcVar9 + 1;
      *pcVar9 = acStack_48[uVar6 - extraout_r2 * (uVar6 / extraout_r2)];
      iVar8 = iVar7 + 1;
      bVar1 = extraout_r2 <= uVar6;
      uVar6 = uVar6 / extraout_r2;
    } while (bVar1);
    puVar4[iVar8] = 0;
    if (iVar7 != 0) {
      pcVar9 = puVar4 + iVar8;
      pcVar10 = puVar4 + -1;
      do {
        pcVar2 = pcVar10 + 1;
        cVar3 = *pcVar2;
        pcVar9 = pcVar9 + -1;
        *pcVar2 = *pcVar9;
        pcVar5 = pcVar10 + (2 - (int)puVar4);
        *pcVar9 = cVar3;
        pcVar10 = pcVar2;
      } while ((int)pcVar5 < (int)(puVar4 + iVar7 + (-1 - (int)pcVar2)));
    }
    return puVar4;
  }
  *puVar4 = 0;
  return (undefined1 *)0x0;
}

