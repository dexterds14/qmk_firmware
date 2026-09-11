// FUN_0800bbc0 @ 0x0800bbc0  size=108  body=[[0800bbc0, 0800bc2b]]

void FUN_0800bbc0(void)

{
  int iVar1;
  
  if (DAT_20004ae4 == '\x05') {
    while (DAT_20004ae4 == '\x05') {
      FUN_0801249e();
      iVar1 = FUN_0801246c();
      if (iVar1 != 0) {
        FUN_08014358(&DAT_20004ae4);
        FUN_08013a7a(30000);
        FUN_08011b84(0xcf);
        FUN_08011d68();
        FUN_08013a7a(1000);
        FUN_08011b84(0xd0);
        FUN_08011d68();
        FUN_08013a7a(1000);
        FUN_08011c48(0xd0);
        FUN_08011d68();
      }
    }
    FUN_0800e4dc();
    FUN_08011d68();
    FUN_08012a98();
    return;
  }
  return;
}

