// FUN_0800c314 @ 0x0800c314  size=100  body=[[0800c314, 0800c377]]

void FUN_0800c314(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  uint uVar1;
  uint uVar2;
  byte *pbVar3;
  byte bVar4;
  undefined4 uStack_24;
  undefined4 uStack_20;
  undefined4 uStack_1c;
  
  uStack_24 = param_2;
  uStack_20 = param_3;
  uStack_1c = param_4;
  memcpy(&uStack_24,(undefined4 *)&DAT_08016790,10);
  uVar1 = 0;
  do {
    uVar2 = uVar1 + 1;
    FUN_0800fe78(uVar1,0,0,0);
    uVar1 = uVar2;
  } while (uVar2 != 0x59);
  if ((DAT_200015b4 & 0xfd) == 1) {
    pbVar3 = (byte *)&uStack_24;
    for (bVar4 = 0; (uint)bVar4 < DAT_200015ac / 10; bVar4 = bVar4 + 1) {
      FUN_0800fe78((uint)*pbVar3,DAT_200015a6,DAT_200015a5,DAT_200015a4);
      pbVar3 = pbVar3 + 1;
    }
  }
  return;
}

