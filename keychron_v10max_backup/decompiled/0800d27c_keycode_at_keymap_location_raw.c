// keycode_at_keymap_location_raw @ 0x0800d27c  size=36  body=[[0800d27c, 0800d29f]]

// VERIFIED: cmp r0#5/r1#5/r2#17 bhi -> movs r0#1 (KC_TRNS); idx = layer*0x6C + row*18 + col; ldr
// r3=[0x0800D2A0]=0x080169B8 keymaps; ldrh.w r0=[r3 + idx*2]; bx lr  (0x0800D27C-0x0800D29F)

ushort keycode_at_keymap_location_raw(uint param_1,uint param_2,uint param_3)

{
  if (((param_1 < 6) && (param_2 < 6)) && (param_3 < 0x12)) {
    return keymaps[param_1][param_2][param_3];
  }
  return 1;
}

