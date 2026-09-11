// FUN_08009474 @ 0x08009474  size=150  body=[[08009474, 08009509]]

undefined4 * FUN_08009474(undefined4 *param_1)

{
  int iVar1;
  undefined4 *puVar2;
  undefined4 *puVar3;
  
  if (DAT_200014f0 == 0) {
    FUN_080093a4();
  }
  puVar2 = &DAT_20000c50;
  while( true ) {
    do {
      puVar3 = puVar2;
      puVar2 = (undefined4 *)puVar3[2];
      iVar1 = puVar3[1] + -1;
      if (-1 < iVar1) {
        do {
          iVar1 = iVar1 + -1;
          if (*(short *)(puVar2 + 3) == 0) {
            puVar2[3] = 0xffff0001;
            puVar2[1] = 0;
            puVar2[2] = 0;
            puVar2[4] = 0;
            puVar2[5] = 0;
            puVar2[0x19] = 0;
            *puVar2 = 0;
            puVar2[6] = 0;
            FUN_08008798((byte *)(puVar2 + 0x17),0,8);
            puVar2[0xd] = 0;
            puVar2[0xe] = 0;
            puVar2[0x12] = 0;
            puVar2[0x13] = 0;
            return puVar2;
          }
          puVar2 = puVar2 + 0x1a;
        } while (iVar1 != -1);
      }
      puVar2 = (undefined4 *)*puVar3;
    } while ((undefined4 *)*puVar3 != (undefined4 *)0x0);
    puVar2 = (undefined4 *)FUN_08009758(param_1,0x1ac);
    if (puVar2 == (undefined4 *)0x0) break;
    *puVar2 = 0;
    puVar2[1] = 4;
    puVar2[2] = puVar2 + 3;
    FUN_08008798((byte *)(puVar2 + 3),0,0x1a0);
    *puVar3 = puVar2;
  }
  *puVar3 = 0;
  *param_1 = 0xc;
  return (undefined4 *)0x0;
}

