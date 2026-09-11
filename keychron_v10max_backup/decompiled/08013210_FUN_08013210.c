// FUN_08013210 @ 0x08013210  size=12  body=[[08013210, 0801321b]]

uint FUN_08013210(int *param_1)

{
  uint uVar1;
  
  uVar1 = 0;
  if ((uint *)*param_1 != (uint *)0x0) {
    uVar1 = (*(uint *)*param_1 & 0x3ff) >> 2;
  }
  return uVar1;
}

