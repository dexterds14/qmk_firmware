// FUN_0800a298 @ 0x0800a298  size=54  body=[[0800a298, 0800a2cd]]

void FUN_0800a298(void)

{
  bool bVar1;
  int iVar2;
  
  bVar1 = FUN_0800c158();
  if ((!bVar1) && (iVar2 = FUN_08012508(), iVar2 != 0)) {
    if ((DAT_20001501 == 5) && (bVar1 = FUN_0800b39c(), !bVar1)) {
      FUN_0800b6ac((uint)DAT_20001501,(uint)DAT_20001503);
    }
    (*DAT_20000c78)(0);
    DAT_20001501 = 5;
  }
  return;
}

