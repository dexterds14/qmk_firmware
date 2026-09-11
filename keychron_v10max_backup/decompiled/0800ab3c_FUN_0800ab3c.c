// FUN_0800ab3c @ 0x0800ab3c  size=48  body=[[0800ab3c, 0800ab6b]]

void FUN_0800ab3c(undefined4 *param_1)

{
  undefined4 *puVar1;
  
  puVar1 = (undefined4 *)FUN_08008798(&DAT_20001519,0,0x3f);
  *(undefined1 *)((int)puVar1 + -1) = 0x11;
  memcpy(puVar1,param_1,8);
  FUN_0800aa64((byte *)((int)puVar1 + -1),9,'\x01',0);
  return;
}

