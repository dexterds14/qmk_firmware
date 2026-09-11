// process_tap_dance @ 0x08012040  size=132  body=[[08012040, 080120c3]]

// VERIFIED: (keycode-0x5700) < 0x100 = QK_TAP_DANCE range; per-dance state stride 0x1C based at
// 0x20000E7C; active-td keycode @0x2000201C

undefined4 process_tap_dance(uint param_1,int param_2)

{
  int iVar1;
  undefined1 uVar2;
  byte bVar3;
  uint uVar4;
  undefined4 *puVar5;
  
  if (param_1 - 0x5700 < 0x100) {
    bVar3 = *(byte *)(param_2 + 5);
    iVar1 = (param_1 & 0xff) * 0x1c;
    puVar5 = (undefined4 *)(&DAT_20000e7c + iVar1);
    (&DAT_20000e81)[iVar1] = (&DAT_20000e81)[iVar1] & 0xfe | bVar3 & 1;
    if (bVar3 == 0) {
      FUN_08011f8c(puVar5,*(undefined4 *)(&DAT_20000e94 + iVar1),
                   *(undefined **)(&DAT_20000e90 + iVar1));
      if (((int)((uint)(byte)(&DAT_20000e81)[iVar1] << 0x1e) < 0) &&
         (FUN_08011f92(puVar5), DAT_2000201c == param_1)) {
        DAT_2000201c = 0;
      }
    }
    else {
      uVar4 = FUN_08012574();
      DAT_2000201a = (undefined2)uVar4;
      (&DAT_20000e7e)[iVar1] = (&DAT_20000e7e)[iVar1] + '\x01';
      uVar2 = FUN_0800e310();
      (&DAT_20000e7f)[iVar1] = uVar2;
      bVar3 = FUN_0800e348();
      (&DAT_20000e7f)[iVar1] = bVar3 | (&DAT_20000e7f)[iVar1];
      uVar2 = FUN_0800e380();
      (&DAT_20000e80)[iVar1] = uVar2;
      FUN_08011f8c(puVar5,*(undefined4 *)(&DAT_20000e94 + iVar1),
                   *(undefined **)(&DAT_20000e84 + iVar1));
      if (((&DAT_20000e81)[iVar1] & 2) != 0) {
        param_1 = 0;
      }
      DAT_2000201c = (ushort)param_1;
    }
  }
  return 1;
}

