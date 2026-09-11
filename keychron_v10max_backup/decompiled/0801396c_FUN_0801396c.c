// FUN_0801396c @ 0x0801396c  size=110  body=[[0801396c, 080139d9]]

void FUN_0801396c(int param_1,int param_2)

{
  undefined4 uVar1;
  int iVar2;
  undefined *local_28;
  undefined4 local_24;
  undefined4 local_20;
  undefined4 uStack_1c;
  undefined4 local_18;
  undefined4 uStack_14;
  
  *(int *)(param_1 + 0x30) = param_2;
  *(undefined4 *)(param_1 + 0x28) = 0;
  DAT_200049dc = param_1;
  FUN_08013c34();
  *(int *)(param_1 + 0x10) = param_1 + 0x10;
  *(int *)(param_1 + 0x14) = param_1 + 0x10;
  *(undefined4 *)(param_1 + 0x18) = 0xffffffff;
  *(int *)param_1 = param_1;
  *(int *)(param_1 + 4) = param_1;
  *(undefined4 *)(param_1 + 8) = 0;
  *(undefined4 *)(param_1 + 0x2c) = 0;
  *(undefined4 *)(param_1 + 0x1c) = 0;
  uVar1 = FUN_08013cfa();
  *(undefined4 *)(param_1 + 0x20) = uVar1;
  *(undefined4 *)(param_1 + 0x24) = 0;
  *(undefined4 *)(param_1 + 0x5c) = 0;
  iVar2 = FUN_080139ec(param_1,param_1 + 0x34,&DAT_0801680c,0x80);
  *(int *)(param_1 + 0xc) = iVar2;
  *(undefined1 *)(iVar2 + 0x14) = 1;
  local_28 = &DAT_08016811;
  local_24 = *(undefined4 *)(param_2 + 4);
  local_20 = *(undefined4 *)(param_2 + 8);
  uStack_1c = 1;
  local_18 = 0x8013969;
  uStack_14 = 0;
  FUN_08013a50((int)&local_28);
  return;
}

