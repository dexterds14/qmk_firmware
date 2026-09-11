// FUN_08009bc4 @ 0x08009bc4  size=100  body=[[08009bc4, 08009c27]]

undefined4 * FUN_08009bc4(undefined4 *param_1,undefined4 *param_2,uint param_3)

{
  uint uVar1;
  undefined4 *puVar2;
  
  if (param_2 == (undefined4 *)0x0) {
    puVar2 = (undefined4 *)FUN_08009758(param_1,param_3);
    return puVar2;
  }
  if (param_3 != 0) {
    uVar1 = FUN_0800a180(param_1,(int)param_2);
    if ((param_3 <= uVar1) && (uVar1 >> 1 < param_3)) {
      return param_2;
    }
    puVar2 = (undefined4 *)FUN_08009758(param_1,param_3);
    if (puVar2 != (undefined4 *)0x0) {
      if (uVar1 <= param_3) {
        param_3 = uVar1;
      }
      memcpy(puVar2,param_2,param_3);
      FUN_08009858(param_1,(int)param_2);
    }
    return puVar2;
  }
  FUN_08009858(param_1,(int)param_2);
  return (undefined4 *)0x0;
}

