// FUN_0800e21c @ 0x0800e21c  size=178  body=[[0800e21c, 0800e2cd]]

void FUN_0800e21c(uint param_1,undefined4 param_2)

{
  byte bVar1;
  char cVar2;
  uint uVar3;
  uint local_28;
  undefined4 local_24;
  uint local_20;
  undefined4 uStack_1c;
  
  local_28 = param_1;
  local_24 = param_2;
  bVar1 = FUN_0800df94(&local_28);
  if (bVar1 == 0) {
    local_20 = local_28;
    uStack_1c = local_24;
    if ((char)local_24 != '\0') {
      uVar3 = DAT_20001633 + 1 & 7;
      if (uVar3 == DAT_20001632) {
        FUN_0800db44();
        DAT_20001632 = bVar1;
        DAT_20001633 = bVar1;
        FUN_08008798((byte *)&DAT_20001674,0,8);
      }
      else {
        memcpy((undefined4 *)(&DAT_20001634 + (uint)DAT_20001633 * 8),&local_20,8);
        DAT_20001633 = (byte)uVar3;
        FUN_0800de58();
      }
    }
  }
  else if ((char)local_24 != '\0') {
    FUN_0800dbb8();
  }
  while (((uint)DAT_20001633 != (uint)DAT_20001632 &&
         (cVar2 = FUN_0800df94((uint *)(&DAT_20001634 + (uint)DAT_20001632 * 8)), cVar2 != '\0'))) {
    FUN_0800dbb8();
    DAT_20001632 = DAT_20001632 + 1 & 7;
  }
  return;
}

