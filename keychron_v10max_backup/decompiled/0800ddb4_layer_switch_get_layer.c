// layer_switch_get_layer @ 0x0800ddb4  size=58  body=[[0800ddb4, 0800dded]]

// VERIFIED: loops layer 15..0 over bits of (u16@0x2000162E | u16@0x20001630); calls
// 0x0800EA9E(layer,key) and returns first layer whose keycode != 1 (KC_TRNS); else 0

uint layer_switch_get_layer(undefined2 param_1,undefined4 param_2)

{
  uint uVar1;
  uint uVar2;
  ushort uVar3;
  bool bVar4;
  undefined4 local_14;
  
  local_14 = CONCAT22((short)((uint)param_2 >> 0x10),param_1);
  uVar3 = layer_state | default_layer_state;
  uVar2 = 0xf;
  do {
    if (((int)(uint)uVar3 >> (uVar2 & 0xff)) << 0x1f < 0) {
      uVar1 = FUN_0800ea9e(uVar2 & 0xff,local_14);
      if ((uVar1 & 0xffff) != 1) {
        return uVar2 & 0xff;
      }
    }
    bVar4 = uVar2 != 0;
    uVar2 = uVar2 - 1;
  } while (bVar4);
  return 0;
}

