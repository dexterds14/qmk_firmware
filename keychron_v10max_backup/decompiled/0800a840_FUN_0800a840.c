// FUN_0800a840 @ 0x0800a840  size=40  body=[[0800a840, 0800a867]]

bool FUN_0800a840(undefined4 *param_1)

{
  ushort uVar1;
  uint uVar2;
  uint uVar3;
  
  uVar3 = (uint)DAT_20002592;
  uVar2 = (uint)DAT_200025b6;
  if (uVar2 != uVar3) {
    uVar1 = DAT_20002592 + 1;
    memcpy(param_1,(undefined4 *)(&DAT_200025b8 + uVar3 * 0x22),0x22);
    DAT_20002592 = uVar1 & 0xff;
  }
  return uVar2 != uVar3;
}

