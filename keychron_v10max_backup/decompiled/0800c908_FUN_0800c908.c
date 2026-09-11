// FUN_0800c908 @ 0x0800c908  size=14  body=[[0800c908, 0800c915]]

byte * FUN_0800c908(byte *param_1,int param_2)

{
  byte *pbVar1;
  
  if (*param_1 - 0xaa < 2) {
    pbVar1 = (byte *)kc_raw_hid_rx(param_1,param_2);
    return pbVar1;
  }
  return param_1;
}

