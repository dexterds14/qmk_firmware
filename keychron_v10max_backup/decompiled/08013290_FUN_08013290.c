// FUN_08013290 @ 0x08013290  size=22  body=[[08013290, 080132a5]]

uint FUN_08013290(int param_1,uint param_2)

{
  uint *puVar1;
  
  if ((param_2 < 9) && (puVar1 = *(uint **)(param_1 + param_2 * 4), puVar1 != (uint *)0x0)) {
    return (*puVar1 & 0x3ff) >> 2;
  }
  return 0;
}

