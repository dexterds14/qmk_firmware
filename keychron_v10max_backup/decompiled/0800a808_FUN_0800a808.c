// FUN_0800a808 @ 0x0800a808  size=42  body=[[0800a808, 0800a831]]

bool FUN_0800a808(undefined4 *param_1)

{
  uint uVar1;
  uint uVar2;
  
  uVar1 = (uint)DAT_20002592;
  uVar2 = DAT_200025b6 + 1 & 0xff;
  if (uVar1 != uVar2) {
    memcpy((undefined4 *)(&DAT_200025b8 + (uint)DAT_200025b6 * 0x22),param_1,0x22);
    DAT_200025b6 = (ushort)uVar2;
  }
  return uVar1 != uVar2;
}

