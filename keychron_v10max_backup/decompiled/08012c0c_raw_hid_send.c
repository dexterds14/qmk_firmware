// raw_hid_send @ 0x08012c0c  size=16  body=[[08012c0c, 08012c1b]]

// VERIFIED use: called (data,length) at the end of kc_raw_hid_rx for the replying cases exactly
// where keychron_raw_hid.c calls raw_hid_send(data, length)

void raw_hid_send(undefined4 *param_1,int param_2)

{
  if (param_2 == 0x20) {
    FUN_08012bc4(2,param_1,0x20);
    return;
  }
  return;
}

