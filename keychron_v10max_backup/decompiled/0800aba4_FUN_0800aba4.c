// FUN_0800aba4 @ 0x0800aba4  size=50  body=[[0800aba4, 0800abd5]]

void FUN_0800aba4(undefined4 param_1)

{
  int iVar1;
  
  iVar1 = FUN_08008798(&DAT_2000151b,0,0x3d);
  *(char *)(iVar1 + -2) = (char)param_1;
  *(undefined1 *)(iVar1 + -3) = 0x13;
  *(char *)(iVar1 + -1) = (char)((uint)param_1 >> 8);
  FUN_0800aa64((byte *)(iVar1 + -3),7,'\x01',0);
  return;
}

