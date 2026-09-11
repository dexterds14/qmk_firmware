// FUN_08013928 @ 0x08013928  size=36  body=[[08013928, 0801394b]]

void FUN_08013928(void)

{
  int *piVar1;
  int *piVar2;
  int iVar3;
  
  piVar2 = DAT_200049ec;
  piVar1 = DAT_200049e0;
  DAT_200049e0 = (int *)*DAT_200049e0;
  *(int ***)((int)DAT_200049e0 + 4) = &DAT_200049e0;
  *(undefined1 *)(piVar1 + 5) = 1;
  DAT_200049ec = piVar1;
  iVar3 = FUN_08013854(piVar2);
  FUN_08008124(piVar1,iVar3);
  return;
}

