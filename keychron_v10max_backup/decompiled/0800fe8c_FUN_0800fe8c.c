// FUN_0800fe8c @ 0x0800fe8c  size=78  body=[[0800fe8c, 0800fed9]]

void FUN_0800fe8c(uint param_1,byte param_2)

{
  ushort uVar1;
  ushort uVar2;
  uint uVar3;
  undefined4 local_10;
  
  if ((param_2 & (&DAT_20000e23)[param_1]) != 0) {
    uVar1 = FUN_0800f7f8();
    uVar2 = FUN_0800f7f8();
    local_10._3_1_ = (undefined1)(param_1 >> 0x18);
    local_10._0_3_ =
         CONCAT12(DAT_2000480b,
                  CONCAT11((char)((int)((uint)uVar2 << 0x10) >> 0x11) + '\x7f',(char)uVar1));
    uVar3 = FUN_0800fd30(local_10);
    FUN_0800fe78(param_1,(char)(uVar3 >> 8),(char)uVar3,(char)(uVar3 >> 0x10));
    return;
  }
  return;
}

