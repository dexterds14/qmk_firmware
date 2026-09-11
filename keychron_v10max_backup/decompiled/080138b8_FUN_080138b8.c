// FUN_080138b8 @ 0x080138b8  size=24  body=[[080138b8, 080138cf]]

void FUN_080138b8(undefined1 param_1)

{
  int iVar1;
  
  iVar1 = (int)DAT_200049ec;
  *(undefined1 *)((int)DAT_200049ec + 0x14) = param_1;
  DAT_200049ec = DAT_200049e0;
  DAT_200049e0 = (int *)*DAT_200049e0;
  *(int ***)((int)DAT_200049e0 + 4) = &DAT_200049e0;
  *(undefined1 *)(DAT_200049ec + 5) = 1;
  FUN_08008124(DAT_200049ec,iVar1);
  return;
}

