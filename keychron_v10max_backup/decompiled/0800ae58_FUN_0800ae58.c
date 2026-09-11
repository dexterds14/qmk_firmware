// FUN_0800ae58 @ 0x0800ae58  size=44  body=[[0800ae58, 0800ae83]]

void FUN_0800ae58(undefined1 param_1)

{
  int iVar1;
  
  iVar1 = FUN_08008798(&DAT_2000151a,0,0x3e);
  *(undefined1 *)(iVar1 + -2) = 0x33;
  *(undefined1 *)(iVar1 + -1) = param_1;
  FUN_0800aa64((byte *)(iVar1 + -2),2,'\0',0);
  return;
}

