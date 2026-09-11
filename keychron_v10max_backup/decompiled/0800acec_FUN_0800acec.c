// FUN_0800acec @ 0x0800acec  size=60  body=[[0800acec, 0800ad27]]

void FUN_0800acec(undefined1 param_1,undefined4 param_2)

{
  int iVar1;
  
  iVar1 = FUN_08008798(&DAT_2000151c,0,0x3c);
  *(char *)(iVar1 + -2) = (char)param_2;
  *(undefined1 *)(iVar1 + -4) = 0x22;
  *(undefined1 *)(iVar1 + -3) = param_1;
  *(char *)(iVar1 + -1) = (char)((uint)param_2 >> 8);
  FUN_0800aa20();
  FUN_0800aa64((byte *)(iVar1 + -4),4,'\x01',0);
  return;
}

