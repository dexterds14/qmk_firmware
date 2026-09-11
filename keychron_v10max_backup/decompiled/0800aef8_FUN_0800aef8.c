// FUN_0800aef8 @ 0x0800aef8  size=48  body=[[0800aef8, 0800af27]]

void FUN_0800aef8(byte param_1)

{
  int iVar1;
  
  iVar1 = FUN_08008798(&DAT_2000151a,0,0x3e);
  *(undefined1 *)(iVar1 + -2) = 0x71;
  *(byte *)(iVar1 + -1) = param_1;
  FUN_0800aa20();
  FUN_0800aa64((byte *)(iVar1 + -2),2,'\0',0);
  return;
}

