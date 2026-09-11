// FUN_0800a1fc @ 0x0800a1fc  size=56  body=[[0800a1fc, 0800a233]]

undefined4 FUN_0800a1fc(undefined2 param_1,undefined4 param_2,undefined4 param_3)

{
  char cVar1;
  uint uVar2;
  undefined2 local_14;
  undefined2 uStack_12;
  undefined4 uStack_10;
  
  _local_14 = CONCAT22((short)((uint)param_2 >> 0x10),param_1);
  uVar2 = DAT_20002590 + 1 & 0xf;
  cVar1 = (char)uVar2;
  if (DAT_20002591 == uVar2) {
    DAT_20002591 = cVar1 + 1U & 0xf;
  }
  uStack_10 = param_3;
  memcpy((undefined4 *)(&DAT_20002570 + (uint)DAT_20002590 * 2),(undefined4 *)&local_14,2);
  DAT_20002590 = cVar1;
  return 1;
}

