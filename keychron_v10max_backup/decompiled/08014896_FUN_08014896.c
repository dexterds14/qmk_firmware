// FUN_08014896 @ 0x08014896  size=44  body=[[08014896, 080148c1]]

void FUN_08014896(uint param_1)

{
  int iVar1;
  
  iVar1 = 1 << (param_1 & 0x1f);
  (&DAT_e000e180)[param_1 >> 5] = iVar1;
  (&DAT_e000e280)[param_1 >> 5] = iVar1;
  (&DAT_e000e400)[param_1] = 0;
  return;
}

