// itoa @ 0x080085bc  size=44  body=[[080085bc, 080085e7]]

// VERIFIED use: kc_raw_hid_rx case 0xA1 calls (1,&data[2],16),(0,&data[4],16),(0,&data[6],16) =
// get_firmware_version() itoa(...,16) for DEVICE_VER 0x0100

undefined1 * itoa(uint param_1,undefined1 *param_2,uint param_3)

{
  undefined1 *puVar1;
  
  if (param_3 - 2 < 0x23) {
    puVar1 = param_2;
    if ((param_3 == 10) && ((int)param_1 < 0)) {
      puVar1 = param_2 + 1;
      *param_2 = 0x2d;
      param_1 = -param_1;
    }
    FUN_080085f8(param_1,puVar1,param_3);
    return param_2;
  }
  *param_2 = 0;
  return (undefined1 *)0x0;
}

