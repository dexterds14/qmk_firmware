// get_record_keycode @ 0x0800d334  size=24  body=[[0800d334, 0800d34b]]

// VERIFIED: loads record->event (ldrh [r0] [r0+2] [r0+4]) and tail-jumps b.w 0x0800D2E8
// get_event_keycode

ushort get_record_keycode(uint *param_1,int param_2)

{
  ushort uVar1;
  
  uVar1 = get_event_keycode(*param_1,(uint)(ushort)param_1[1],param_2);
  return uVar1;
}

