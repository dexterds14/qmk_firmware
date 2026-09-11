// FUN_080130c4 @ 0x080130c4  size=38  body=[[080130c4, 080130e9]]

void FUN_080130c4(int *param_1,undefined4 *param_2,uint param_3)

{
  undefined4 uVar1;
  int iVar2;
  
  iVar2 = *param_1;
  if (iVar2 != 0) {
    uVar1 = FUN_08013cfa();
    *(undefined4 *)(iVar2 + 4) = uVar1;
    iVar2 = *param_1;
    *(uint *)(iVar2 + 0x48) = param_3;
    memcpy((undefined4 *)(iVar2 + 8),param_2,param_3);
    return;
  }
  return;
}

