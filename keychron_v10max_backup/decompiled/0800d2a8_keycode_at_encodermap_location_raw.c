// keycode_at_encodermap_location_raw @ 0x0800d2a8  size=26  body=[[0800d2a8, 0800d2c1]]

// VERIFIED: layer<6 && encoder_idx==0; idx = layer*2 + (clockwise^1); ldr
// r3=[0x0800D2C4]=0x080169A0 encoder_map; ldrh.w [r3 + idx*2]; else movs r0#1

undefined2 keycode_at_encodermap_location_raw(uint param_1,int param_2,uint param_3)

{
  if ((param_1 < 6) && (param_2 == 0)) {
    return *(undefined2 *)(&encoder_map + ((param_3 ^ 1) + param_1 * 2) * 2);
  }
  return 1;
}

