// FUN_0800968c @ 0x0800968c  size=54  body=[[0800968c, 080096c1]]

undefined4 FUN_0800968c(uint *param_1,int *param_2)

{
  undefined4 uVar1;
  
  if (param_2[4] == 0) {
    return 0;
  }
  if ((param_1 != (uint *)0x0) && (param_1[8] == 0)) {
    FUN_08009518((int)param_1);
  }
  if ((short)param_2[3] == 0) {
    return 0;
  }
  uVar1 = FUN_08009568(param_1,param_2);
  return uVar1;
}

