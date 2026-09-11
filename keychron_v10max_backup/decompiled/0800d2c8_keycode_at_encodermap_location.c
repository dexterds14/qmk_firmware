// keycode_at_encodermap_location @ 0x0800d2c8  size=4  body=[[0800d2c8, 0800d2cb]]

// VERIFIED: ICF thunk 'b.w 0x0800D2A8'; tail-jumped from keymap_key_to_keycode @0x0800EA88

undefined2 keycode_at_encodermap_location(uint param_1,int param_2,uint param_3)

{
  if ((param_1 < 6) && (param_2 == 0)) {
    return *(undefined2 *)(&encoder_map + ((param_3 ^ 1) + param_1 * 2) * 2);
  }
  return 1;
}

