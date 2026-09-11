// FUN_0800fe44 @ 0x0800fe44  size=34  body=[[0800fe44, 0800fe65]]

uint FUN_0800fe44(int param_1,int param_2,int param_3)

{
  uint uVar1;
  
  uVar1 = FUN_0800fe40();
  if ((&DAT_20000d07)[param_2 + param_1 * 0x12] != -1) {
    *(undefined1 *)(param_3 + uVar1) = (&DAT_20000d07)[param_2 + param_1 * 0x12];
    uVar1 = uVar1 + 1 & 0xff;
  }
  return uVar1;
}

