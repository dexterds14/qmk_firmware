// FUN_0800af8c @ 0x0800af8c  size=124  body=[[0800af8c, 0800b007]]

// WARNING: Type propagation algorithm not settling

void FUN_0800af8c(undefined1 param_1,undefined4 *param_2,uint param_3,undefined1 param_4)

{
  byte local_38 [4];
  byte local_34;
  undefined1 local_33;
  undefined1 local_32;
  undefined4 auStack_31 [7];
  
  FUN_08008798(local_38,0,0x20);
  local_38[0] = 3;
  local_38[1] = 0xaa;
  local_38[2] = 0x57;
  local_38[3] = (byte)param_3;
  local_34 = ~local_38[3];
  local_33 = param_4;
  local_32 = param_1;
  memcpy(auStack_31,param_2,param_3);
  raw_hid_send((undefined4 *)local_38,0x20);
  if (0x19 < param_3) {
    FUN_08008798((byte *)((int)local_38 + 1),0,0x1f);
    local_38[0] = 3;
    memcpy((undefined4 *)((int)local_38 + 1),(undefined4 *)((int)param_2 + 0x19),param_3 - 0x19);
    raw_hid_send((undefined4 *)local_38,0x20);
  }
  return;
}

