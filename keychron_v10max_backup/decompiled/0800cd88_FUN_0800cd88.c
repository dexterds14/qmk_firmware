// FUN_0800cd88 @ 0x0800cd88  size=38  body=[[0800cd88, 0800cdad]]

undefined4 FUN_0800cd88(void)

{
  uint uVar1;
  
  if (DAT_200015d8 != 0) {
    uVar1 = FUN_0801258c(DAT_200015d8);
    if (uVar1 < 0xbb9) {
      DAT_40020418 = 0x1000;
    }
    else {
      DAT_200015d8 = 0;
      DAT_4002041a = 0x1000;
    }
  }
  return 1;
}

