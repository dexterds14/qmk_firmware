// FUN_08011480 @ 0x08011480  size=40  body=[[08011480, 080114a7]]

uint FUN_08011480(uint param_1)

{
  char cVar1;
  uint uVar2;
  
  uVar2 = param_1;
  if ((&DAT_20001fc0)[param_1] != '\0') {
    cVar1 = FUN_080111a0(param_1,0,0,param_1 * 0x18 + 0x20001fc2,0x18);
    uVar2 = (uint)cVar1;
  }
  (&DAT_20001fc0)[param_1] = 0;
  return uVar2;
}

