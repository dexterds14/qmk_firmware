// FUN_08015164 @ 0x08015164  size=54  body=[[08015164, 08015199]]

void FUN_08015164(void)

{
  int iVar1;
  
  iVar1 = 0;
  DAT_200024d0 = 0;
  do {
    *(undefined4 *)(&DAT_080174c4)[iVar1 * 3] = 0;
    (&DAT_200024d4)[iVar1 * 2] = 0;
    iVar1 = iVar1 + 1;
  } while (iVar1 != 0x10);
  DAT_40026008 = 0xffffffff;
  DAT_4002600c = 0xffffffff;
  DAT_40026408 = 0xffffffff;
  DAT_4002640c = 0xffffffff;
  return;
}

