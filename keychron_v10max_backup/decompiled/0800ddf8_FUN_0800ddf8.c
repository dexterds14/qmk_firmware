// FUN_0800ddf8 @ 0x0800ddf8  size=24  body=[[0800ddf8, 0800de0f]]

void FUN_0800ddf8(undefined2 param_1,undefined4 param_2)

{
  uint uVar1;
  undefined4 local_c;
  
  local_c = CONCAT22((short)((uint)param_2 >> 0x10),param_1);
  uVar1 = layer_switch_get_layer(param_1,param_2);
  FUN_0800ea9e(uVar1,local_c);
  return;
}

