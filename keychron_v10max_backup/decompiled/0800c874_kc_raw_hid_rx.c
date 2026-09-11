// kc_raw_hid_rx @ 0x0800c874  size=104  body=[[0800c874, 0800c885] [0800c896, 0800c8a1] [0800c8ae, 0800c8db] [0800c8e2, 0800c8fd]]

// WARNING: Possible PIC construction at 0x0800c8fc: Changing call to branch
// WARNING: Possible PIC construction at 0x0800c8f8: Changing call to branch
// WARNING: Possible PIC construction at 0x0800c8f2: Changing call to branch
// WARNING: Possible PIC construction at 0x0800c8ec: Changing call to branch
// WARNING: Possible PIC construction at 0x0800c8da: Changing call to branch
// WARNING: Removing unreachable block (ram,0x0800c8ec)
// WARNING: Removing unreachable block (ram,0x0800c8f2)
// WARNING: Removing unreachable block (ram,0x0800c8f8)
// WARNING: Removing unreachable block (ram,0x0800c8fc)
// WARNING: Removing unreachable block (ram,0x0800c8da)
// VERIFIED vs keychron_raw_hid.c kc_raw_hid_rx: ldrb data[0]; subs #0xA0; cmp #0xB; tbb @0x0800C882
// (12 cases 0xA0..0xAB); case 0xA1 copies build-date string 0x080167AC (get_firmware_version); 0xAA
// -> 0x0800B290 (lkbt51_dfu_rx); 0xAB -> 0x0800CB90 (factory_test_rx)

undefined4 kc_raw_hid_rx(byte *param_1,int param_2)

{
  int iVar1;
  
  switch(*param_1) {
  case 0xa0:
    param_1[1] = 2;
    break;
  case 0xa1:
    param_1[1] = 0x76;
    itoa(1,param_1 + 2,0x10);
    param_1[3] = 0x2e;
    itoa(0,param_1 + 4,0x10);
    param_1[5] = 0x2e;
    itoa(0,param_1 + 6,0x10);
    param_1[7] = 0x20;
    memcpy((undefined4 *)(param_1 + 8),(undefined4 *)"2024-07-09-13:57:36",0x14);
    break;
  case 0xa2:
    param_1[2] = 7;
    break;
  case 0xa3:
    iVar1 = get_highest_layer((uint)default_layer_state);
    param_1[1] = (byte)iVar1;
    break;
  default:
    return 0;
  case 0xaa:
    lkbt51_dfu_rx((char *)param_1);
    return 1;
  case 0xab:
    factory_test_rx(param_1);
    return 1;
  }
  raw_hid_send((undefined4 *)param_1,param_2);
  return 1;
}

