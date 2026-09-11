// FUN_0800ab70 @ 0x0800ab70  size=48  body=[[0800ab70, 0800ab9f]]

void FUN_0800ab70(undefined4 *param_1)

{
  undefined4 *puVar1;
  
  puVar1 = (undefined4 *)FUN_08008798(&DAT_20001519,0,0x3f);
  *(undefined1 *)((int)puVar1 + -1) = 0x12;
  memcpy(puVar1,param_1,0x14);
  FUN_0800aa64((byte *)((int)puVar1 + -1),0x15,'\x01',0);
  return;
}

