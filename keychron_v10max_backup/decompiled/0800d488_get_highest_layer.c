// get_highest_layer @ 0x0800d488  size=40  body=[[0800d488, 0800d4af]]

// VERIFIED use: kc_raw_hid_rx case 0xA3 calls it on default_layer_state and stores the byte result
// (keychron_raw_hid.c: data[1] = get_highest_layer(default_layer_state))

int get_highest_layer(uint param_1)

{
  int iVar1;
  
  if (param_1 >> 8 == 0) {
    iVar1 = 0;
  }
  else {
    iVar1 = 8;
    param_1 = param_1 >> 8;
  }
  if (param_1 >> 4 != 0) {
    iVar1 = iVar1 + 4;
    param_1 = param_1 >> 4;
  }
  if (param_1 >> 2 != 0) {
    iVar1 = iVar1 + 2;
    param_1 = param_1 >> 2;
  }
  if (param_1 >> 1 != 0) {
    iVar1 = iVar1 + 1;
  }
  return iVar1;
}

