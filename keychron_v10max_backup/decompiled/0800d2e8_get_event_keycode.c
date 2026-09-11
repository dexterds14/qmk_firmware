// get_event_keycode @ 0x0800d2e8  size=70  body=[[0800d2e8, 0800d32d]]

// VERIFIED shape of action.c get_event_keycode(): if !disable_action_cache(@0x200015F0) { if
// pressed && update_layer_cache: layer_switch_get_layer + update_source_layers_cache else
// read_source_layers_cache } else layer_switch_get_layer; tail b.w keymap_key_to_keycode 0x0800EA64

ushort get_event_keycode(uint param_1,undefined4 param_2,int param_3)

{
  ushort uVar1;
  uint uVar2;
  undefined1 local_b;
  
  if (disable_action_cache == '\0') {
    local_b = (char)((uint)param_2 >> 8);
    if ((local_b == '\0') || (param_3 == 0)) {
      uVar2 = read_source_layers_cache(param_1);
    }
    else {
      uVar2 = layer_switch_get_layer((short)param_1,param_2);
      update_source_layers_cache(param_1,uVar2);
    }
  }
  else {
    uVar2 = layer_switch_get_layer((short)param_1,param_2);
  }
  uVar1 = keymap_key_to_keycode(uVar2,param_1);
  return uVar1;
}

