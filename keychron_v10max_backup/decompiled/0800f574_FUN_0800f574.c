// FUN_0800f574 @ 0x0800f574  size=54  body=[[0800f574, 0800f5a9]]

undefined4 FUN_0800f574(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  uint uVar1;
  uint uVar2;
  undefined4 uVar3;
  undefined8 uVar4;
  
  uVar2 = 0;
  uVar3 = 1;
  while (uVar2 < DAT_20000ea4) {
    uVar2 = uVar2 + 1;
    uVar4 = (**(code **)(*DAT_20001f10 + 0x14))(DAT_20001f10,uVar2);
    if (1 < (uint)uVar4) {
      uVar3 = 0;
    }
    uVar1 = FUN_08013ff4(DAT_20001f10,(uint)((ulonglong)uVar4 >> 0x20));
    if (1 < uVar1) {
      uVar3 = 0;
    }
  }
  return uVar3;
}

