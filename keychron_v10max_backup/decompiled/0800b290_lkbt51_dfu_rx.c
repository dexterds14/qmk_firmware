// lkbt51_dfu_rx @ 0x0800b290  size=148  body=[[0800b290, 0800b323]]

// INFERRED: 0xAA case target of kc_raw_hid_rx

void lkbt51_dfu_rx(char *param_1)

{
  char cVar1;
  uint uVar2;
  uint uVar3;
  byte *pbVar4;
  byte *pbVar5;
  bool bVar6;
  
  if ((((*param_1 == -0x56) && ((byte)param_1[1] - 0x55 < 2)) &&
      (uVar3 = (uint)(byte)param_1[2], uVar3 == (byte)~param_1[3])) && (uVar3 < 0x1c)) {
    pbVar5 = (byte *)(param_1 + 5);
    pbVar4 = (byte *)(param_1 + 4);
    uVar2 = 0;
    while ((int)(pbVar4 + (-4 - (int)param_1)) < (int)(uVar3 - 2)) {
      pbVar4 = pbVar4 + 1;
      uVar2 = uVar2 + *pbVar4 & 0xffff;
    }
    if (((uint)pbVar5[uVar3 - 2] == (uVar2 & 0xff)) && ((uint)pbVar5[uVar3 - 1] == uVar2 >> 8)) {
      cVar1 = param_1[4];
      bVar6 = DAT_20001511 != cVar1;
      if (bVar6) {
        DAT_20001511 = cVar1;
      }
      if ((param_1[5] & 0xf0U) == 0x60) {
        FUN_0800aa20();
        FUN_0800aa64(pbVar5,uVar3 - 2 & 0xff,param_1[1] == 'V',(uint)!bVar6);
        return;
      }
    }
  }
  return;
}

