// FUN_08008210 @ 0x08008210  size=20  body=[[08008210, 0800821f] [0800840e, 08008411]]

uint FUN_08008210(int param_1,int param_2,uint param_3,uint param_4)

{
  int unaff_r4;
  uint *unaff_r5;
  int unaff_r6;
  int in_r12;
  bool in_ZR;
  bool in_CY;
  
  if (in_CY && !in_ZR) {
    unaff_r4 = unaff_r4 + in_r12;
    param_4 = param_1 - 2;
  }
  if (unaff_r5 != (uint *)0x0) {
    *unaff_r5 = (uint)(unaff_r4 - unaff_r6) >> (param_3 & 0xff);
    unaff_r5[1] = 0;
  }
  return param_4 | param_2 << 0x10;
}

