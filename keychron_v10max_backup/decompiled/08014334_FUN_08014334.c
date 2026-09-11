// FUN_08014334 @ 0x08014334  size=36  body=[[08014334, 08014357]]

void FUN_08014334(int param_1,uint param_2,undefined4 param_3,undefined4 param_4)

{
  undefined4 *puVar1;
  
  puVar1 = *(undefined4 **)(*(int *)(param_1 + param_2 * 4 + 0xc) + 0x14);
  *(ushort *)(param_1 + 8) = (ushort)(1 << (param_2 & 0xff)) | *(ushort *)(param_1 + 8);
  *puVar1 = param_4;
  puVar1[2] = param_3;
  puVar1[1] = 0;
  puVar1[3] = 0;
  FUN_080159c0(param_1,param_2);
  return;
}

