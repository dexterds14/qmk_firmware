// FUN_08013ff4 @ 0x08013ff4  size=56  body=[[08013ff4, 0801402b]]

void FUN_08013ff4(int *param_1,uint param_2)

{
  longlong lVar1;
  int iVar2;
  undefined8 uVar3;
  uint local_14;
  
  local_14 = param_2;
  while (iVar2 = (**(code **)(*param_1 + 0x18))(param_1,&local_14), iVar2 == 1) {
    lVar1 = (ulonglong)local_14 * 100000 + 999;
    uVar3 = FUN_08008158((uint)lVar1,(uint)((ulonglong)lVar1 >> 0x20),1000,0);
    FUN_08013a7a((uint)uVar3);
  }
  return;
}

