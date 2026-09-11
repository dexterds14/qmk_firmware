// FUN_0800de10 @ 0x0800de10  size=66  body=[[0800de10, 0800de51]]

void FUN_0800de10(int param_1,uint param_2)

{
  uint uVar1;
  
  if (disable_action_cache != '\0') {
    FUN_0800ddf8((short)param_2,param_2);
    return;
  }
  if (param_1 == 0) {
    uVar1 = read_source_layers_cache(param_2);
  }
  else {
    uVar1 = layer_switch_get_layer((short)param_2,param_2);
    update_source_layers_cache(param_2,uVar1);
  }
  FUN_0800ea9e(uVar1,param_2);
  return;
}

