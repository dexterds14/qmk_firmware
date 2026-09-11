// FUN_0800ae88 @ 0x0800ae88  size=48  body=[[0800ae88, 0800aeb7]]

void FUN_0800ae88(undefined4 *param_1)

{
  undefined4 *puVar1;
  
  puVar1 = (undefined4 *)FUN_08008798(&DAT_20001519,0,0x3f);
  *(undefined1 *)((int)puVar1 + -1) = 0x41;
  memcpy(puVar1,param_1,0x16);
  FUN_0800aa64((byte *)((int)puVar1 + -1),0x17,'\0',0);
  return;
}

