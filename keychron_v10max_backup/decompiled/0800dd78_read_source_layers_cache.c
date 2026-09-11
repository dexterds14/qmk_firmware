// read_source_layers_cache @ 0x0800dd78  size=52  body=[[0800dd78, 0800ddab]]

// INFERRED: callee in the else-branch of get_event_keycode

uint read_source_layers_cache(uint param_1)

{
  uint uVar1;
  undefined *puVar2;
  uint uVar3;
  
  uVar3 = param_1 & 0xff;
  uVar1 = (param_1 & 0xffff) >> 8;
  if (uVar1 < 6) {
    if (0x11 < uVar3) {
      return 0;
    }
    puVar2 = &DAT_200015f5;
    uVar3 = uVar3 + uVar1 * 0x12;
  }
  else {
    if (1 < (uVar1 + 4 & 0xff)) {
      return 0;
    }
    puVar2 = &DAT_200015f1;
  }
  uVar1 = FUN_0800dd0c(uVar3,(int)puVar2);
  return uVar1;
}

