// FUN_080140dc @ 0x080140dc  size=18  body=[[080140dc, 080140ed]]

void FUN_080140dc(uint param_1,undefined4 param_2,undefined4 param_3)

{
  (&DAT_20004a64)[(param_1 & 0xf) * 2] = param_2;
  (&DAT_20004a68)[(param_1 & 0xf) * 2] = param_3;
  return;
}

