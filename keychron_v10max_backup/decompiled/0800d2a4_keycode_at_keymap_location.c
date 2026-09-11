// keycode_at_keymap_location @ 0x0800d2a4  size=4  body=[[0800d2a4, 0800d2a7]]

// VERIFIED: 4-byte ICF thunk 'b.w 0x0800D27C' (f7ff bfea); tail-jumped from keymap_key_to_keycode
// @0x0800EA78

ushort keycode_at_keymap_location(uint param_1,uint param_2,uint param_3)

{
  if (((param_1 < 6) && (param_2 < 6)) && (param_3 < 0x12)) {
    return keymaps[param_1][param_2][param_3];
  }
  return 1;
}

