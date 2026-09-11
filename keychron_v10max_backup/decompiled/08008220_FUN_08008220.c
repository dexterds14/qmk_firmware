// FUN_08008220 @ 0x08008220  size=10  body=[[08008220, 08008229]]

void FUN_08008220(undefined4 param_1,undefined4 param_2,uint param_3)

{
  uint unaff_r4;
  uint *unaff_r5;
  
  if (unaff_r5 != (uint *)0x0) {
    *unaff_r5 = unaff_r4 >> (param_3 & 0xff);
    unaff_r5[1] = 0;
  }
  return;
}

