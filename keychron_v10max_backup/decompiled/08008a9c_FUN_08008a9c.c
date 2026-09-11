// FUN_08008a9c @ 0x08008a9c  size=30  body=[[08008a9c, 08008ab9]]

undefined4 FUN_08008a9c(uint *param_1,uint *param_2,undefined4 *param_3)

{
  undefined4 uVar1;
  
  if (param_3[2] == 0) {
    param_3[1] = 0;
    return 0;
  }
  uVar1 = FUN_08008de4(param_1,param_2,param_3);
  param_3[2] = 0;
  param_3[1] = 0;
  return uVar1;
}

