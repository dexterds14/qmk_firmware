// FUN_0800aebc @ 0x0800aebc  size=56  body=[[0800aebc, 0800aef3]]

void FUN_0800aebc(undefined4 *param_1)

{
  uint uVar1;
  undefined4 *puVar2;
  
  uVar1 = FUN_080086c0((uint)param_1);
  puVar2 = (undefined4 *)FUN_08008798(&DAT_20001519,0,0x3f);
  *(undefined1 *)((int)puVar2 + -1) = 0x45;
  memcpy(puVar2,param_1,uVar1 & 0xff);
  FUN_0800aa64((byte *)((int)puVar2 + -1),uVar1 + 1 & 0xff,'\0',0);
  return;
}

