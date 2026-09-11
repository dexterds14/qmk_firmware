// FUN_08014310 @ 0x08014310  size=36  body=[[08014310, 08014333]]

void FUN_08014310(int param_1,uint param_2,undefined4 param_3,undefined4 param_4)

{
  undefined4 *puVar1;
  
  puVar1 = *(undefined4 **)(*(int *)(param_1 + param_2 * 4 + 0xc) + 0x18);
  *(ushort *)(param_1 + 10) = (ushort)(1 << (param_2 & 0xff)) | *(ushort *)(param_1 + 10);
  *puVar1 = param_4;
  puVar1[2] = param_3;
  puVar1[1] = 0;
  puVar1[3] = 0;
  FUN_08015894(param_1,param_2);
  return;
}

