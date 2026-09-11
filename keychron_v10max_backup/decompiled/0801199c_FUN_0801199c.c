// FUN_0801199c @ 0x0801199c  size=26  body=[[0801199c, 080119b5]]

bool FUN_0801199c(undefined2 param_1)

{
  uint uVar1;
  
  uVar1 = (uint)DAT_20001ffb;
  if (uVar1 < 5) {
    (&DAT_20001ffc)[uVar1] = param_1;
    DAT_20001ffb = DAT_20001ffb + 1;
  }
  return uVar1 < 5;
}

