// FUN_0800920c @ 0x0800920c  size=80  body=[[0800920c, 0800925b]]

undefined4 FUN_0800920c(uint param_1)

{
  int *piVar1;
  undefined4 uVar2;
  int iVar3;
  code *pcVar4;
  
  piVar1 = DAT_20000c00;
  if (0x1f < param_1) {
    *DAT_20000c00 = 0x16;
    return 0xffffffff;
  }
  iVar3 = DAT_20000c00[0xf];
  if ((iVar3 != 0) && (pcVar4 = *(code **)(iVar3 + param_1 * 4), pcVar4 != (code *)0x0)) {
    if (pcVar4 != (code *)0x1) {
      if (pcVar4 == (code *)0xffffffff) {
        *DAT_20000c00 = 0x16;
        return 1;
      }
      *(undefined4 *)(iVar3 + param_1 * 4) = 0;
      (*pcVar4)();
    }
    return 0;
  }
  thunk_FUN_080166fc();
  uVar2 = FUN_0800a190(piVar1);
  return uVar2;
}

