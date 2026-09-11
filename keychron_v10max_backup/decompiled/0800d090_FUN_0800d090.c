// FUN_0800d090 @ 0x0800d090  size=32  body=[[0800d090, 0800d0af]]

ushort * FUN_0800d090(uint param_1)

{
  ushort *puVar1;
  
  if (DAT_200015e0 == (ushort *)0x0) {
    puVar1 = (ushort *)&Reset;
  }
  else {
    if (*DAT_200015e0 == param_1) {
      return DAT_200015e0;
    }
    puVar1 = DAT_200015e0 + 2;
  }
  if (DAT_200015e0[2] != param_1) {
    puVar1 = (ushort *)0x0;
  }
  return puVar1;
}

