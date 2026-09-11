// FUN_08012914 @ 0x08012914  size=64  body=[[08012914, 08012953]]

undefined4 * FUN_08012914(int param_1)

{
  undefined4 *puVar1;
  
  DAT_20002060 = 0;
  DAT_2000205c = FUN_08012cb8((uint)*(ushort *)(param_1 + 0x46),
                              (undefined *)(uint)*(ushort *)(param_1 + 0x48),
                              (uint)*(ushort *)(param_1 + 0x4a),&DAT_20002060);
  puVar1 = (undefined4 *)0x0;
  if (DAT_20002060 != 0) {
    puVar1 = &DAT_2000205c;
  }
  return puVar1;
}

