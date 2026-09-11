// FUN_0800cb44 @ 0x0800cb44  size=74  body=[[0800cb44, 0800cb8d]]

void FUN_0800cb44(undefined4 *param_1,uint param_2)

{
  byte *pbVar1;
  char cVar2;
  byte local_30;
  byte local_2f [29];
  short local_12;
  
  pbVar1 = &local_30;
  FUN_08008798(&local_30,0,0x20);
  local_30 = 0xab;
  memcpy((undefined4 *)local_2f,param_1,param_2);
  cVar2 = '\x01';
  local_12 = 0;
  do {
    pbVar1 = pbVar1 + 1;
    cVar2 = cVar2 + '\x01';
    local_12 = local_12 + (ushort)*pbVar1;
  } while (cVar2 != '\x1d');
  raw_hid_send((undefined4 *)&local_30,0x20);
  return;
}

