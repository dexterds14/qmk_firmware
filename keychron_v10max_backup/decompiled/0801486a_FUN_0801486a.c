// FUN_0801486a @ 0x0801486a  size=44  body=[[0801486a, 08014895]]

void FUN_0801486a(uint param_1,char param_2)

{
  int iVar1;
  
  (&DAT_e000e400)[param_1] = param_2 << 4;
  iVar1 = 1 << (param_1 & 0x1f);
  (&DAT_e000e280)[param_1 >> 5] = iVar1;
  *(int *)(&DAT_e000e100 + (param_1 >> 5) * 4) = iVar1;
  return;
}

