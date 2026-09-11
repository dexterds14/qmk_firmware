// FUN_0800abdc @ 0x0800abdc  size=60  body=[[0800abdc, 0800ac17]]

void FUN_0800abdc(char param_1)

{
  int iVar1;
  
  if ((byte)(param_1 + 0x7fU) < 3) {
    iVar1 = FUN_08008798(&DAT_2000151a,0,0x3e);
    *(undefined1 *)(iVar1 + -2) = 0x14;
    *(char *)(iVar1 + -1) = (char)(1 << (uint)(byte)(param_1 + 0x7f));
    FUN_0800aa64((byte *)(iVar1 + -2),2,'\x01',0);
    return;
  }
  return;
}

