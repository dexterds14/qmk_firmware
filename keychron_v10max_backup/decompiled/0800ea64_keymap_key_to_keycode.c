// keymap_key_to_keycode @ 0x0800ea64  size=58  body=[[0800ea64, 0800ea9d]]

// VERIFIED: col=key&0xff row=(key>>8)&0xff; row<6&&col<18 -> keycode_at_keymap_location; row==0xFD
// (KEYLOC_ENCODER_CW) && col==0 -> encodermap(clockwise=1); row==0xFC (KEYLOC_ENCODER_CCW) ->
// clockwise=0; else KC_NO

ushort keymap_key_to_keycode(uint param_1,uint param_2)

{
  ushort uVar1;
  uint uVar2;
  uint uVar3;
  
  uVar3 = param_2 & 0xff;
  uVar2 = (param_2 & 0xffff) >> 8;
  if (uVar2 < 6) {
    if (uVar3 < 0x12) {
      uVar1 = keycode_at_keymap_location(param_1,uVar2,uVar3);
      return uVar1;
    }
  }
  else if (uVar2 == 0xfd) {
    if (uVar3 == 0) {
      uVar2 = 1;
LAB_0800ea86:
      uVar1 = keycode_at_encodermap_location(param_1,uVar3,uVar2);
      return uVar1;
    }
  }
  else if ((uVar2 == 0xfc) && (uVar3 == 0)) {
    uVar2 = 0;
    goto LAB_0800ea86;
  }
  return 0;
}

