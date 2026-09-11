// FUN_08014294 @ 0x08014294  size=50  body=[[08014294, 080142c5]]

void FUN_08014294(int param_1,uint param_2,int param_3)

{
  byte *pbVar1;
  
  pbVar1 = *(byte **)(param_3 + 0x14);
  *(int *)(param_1 + param_2 * 4 + 0xc) = param_3;
  if (pbVar1 != (byte *)0x0) {
    FUN_08008798(pbVar1,0,0x14);
  }
  if (*(byte **)(param_3 + 0x18) != (byte *)0x0) {
    FUN_08008798(*(byte **)(param_3 + 0x18),0,0x14);
  }
  FUN_08015730(param_1,param_2);
  return;
}

