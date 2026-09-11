// FUN_08013ac4 @ 0x08013ac4  size=28  body=[[08013ac4, 08013adf]]

undefined4 FUN_08013ac4(int param_1,uint param_2)

{
  int *piVar1;
  undefined4 uVar2;
  int *piVar3;
  
  piVar1 = DAT_200049ec;
  if (param_2 != 0) {
    piVar3 = *(int **)(param_1 + 4);
    *DAT_200049ec = param_1;
    piVar1[1] = (int)piVar3;
    *piVar3 = (int)piVar1;
    *(int **)(param_1 + 4) = piVar1;
    uVar2 = FUN_080138d4(4,param_2);
    return uVar2;
  }
  return 0xffffffff;
}

