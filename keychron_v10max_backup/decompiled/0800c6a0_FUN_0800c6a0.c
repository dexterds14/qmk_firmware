// FUN_0800c6a0 @ 0x0800c6a0  size=38  body=[[0800c6a0, 0800c6c5]]

undefined4 FUN_0800c6a0(uint param_1,int param_2)

{
  byte bVar1;
  int iVar2;
  undefined4 uVar3;
  
  iVar2 = process_record_wireless(param_1,param_2);
  if ((iVar2 == 0) || (bVar1 = process_record_factory_test(param_1,param_2), bVar1 == 0)) {
    uVar3 = 0;
  }
  else {
    uVar3 = FUN_0800c69c();
  }
  return uVar3;
}

