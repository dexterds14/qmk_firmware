// FUN_0801404a @ 0x0801404a  size=26  body=[[0801404a, 08014063]]

undefined4 FUN_0801404a(int *param_1,int param_2)

{
  int iVar1;
  undefined4 uVar2;
  
  iVar1 = (**(code **)(*param_1 + 4))();
  if (*(int *)(iVar1 + 0xc) == 0) {
    uVar2 = *(undefined4 *)(iVar1 + 0x10);
  }
  else {
    uVar2 = *(undefined4 *)(*(int *)(iVar1 + 0xc) + param_2 * 8 + 4);
  }
  return uVar2;
}

