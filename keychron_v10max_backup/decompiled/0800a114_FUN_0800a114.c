// FUN_0800a114 @ 0x0800a114  size=66  body=[[0800a114, 0800a151] [0801669c, 0801669f]]

undefined8 FUN_0800a114(undefined4 param_1,int param_2,undefined4 param_3,undefined4 param_4)

{
  ushort uVar1;
  
  uVar1 = *(ushort *)(param_2 + 0xc);
  if ((int)(short)uVar1 << 0x17 < 0) {
    FUN_08016698();
    uVar1 = *(ushort *)(param_2 + 0xc);
  }
  *(ushort *)(param_2 + 0xc) = uVar1 & 0xefff;
  return CONCAT44((int)*(short *)(param_2 + 0xe),param_4);
}

