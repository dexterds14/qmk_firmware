// FUN_0800b4c4 @ 0x0800b4c4  size=250  body=[[0800b4c4, 0800b5bd]]

undefined4 FUN_0800b4c4(void)

{
  byte bVar1;
  bool bVar2;
  uint uVar3;
  byte bVar4;
  undefined1 uVar5;
  undefined4 extraout_r1;
  byte bVar6;
  undefined4 extraout_r2;
  undefined4 extraout_r3;
  uint uVar7;
  
  bVar1 = FUN_0800bbb4();
  if ((bVar1 & 6) != 0) {
    bVar2 = FUN_0800c158();
    if (bVar2) {
      thunk_FUN_08011378(0,0,0);
      return 1;
    }
    bVar2 = FUN_0800c144();
    if (bVar2) {
      thunk_FUN_08011378(0,0,0);
    }
    if ((DAT_20001560 != 0) && (bVar1 = DAT_20001560 & 0xc, (DAT_20001560 & 0xc) == 0)) {
      bVar4 = bVar1;
      if ((DAT_20001560 & 0x80) != 0) {
        bVar4 = 0xff;
      }
      FUN_0800fe78(0x51,bVar4,bVar1,bVar1);
      if ((char)DAT_20001560 < '\0') {
        uVar5 = 0xff;
      }
      else {
        uVar5 = 0;
      }
      FUN_0800fe78(0x53,uVar5,0,0);
    }
    bVar2 = FUN_0800c304();
    if (bVar2 != 0) {
      FUN_0800c314((uint)bVar2,extraout_r1,extraout_r2,extraout_r3);
    }
    if (DAT_200047cd != 0) {
      uVar7 = DAT_200047cd & 0xf;
      if (DAT_200047cc == '\0') {
        if (DAT_20000ca3 != uVar7) {
          bVar1 = DAT_200047cd & 0x10;
          if ((DAT_200047cd & 0x10) == 0) {
            uVar3 = (uint)(byte)(&DAT_0801672b)[uVar7];
          }
          else {
            uVar3 = 0x14;
            bVar1 = 0;
          }
          FUN_0800fe78(uVar3,bVar1,bVar1,bVar1);
          DAT_20000ca3 = (byte)uVar7;
        }
      }
      else {
        thunk_FUN_08011378(0,0,0);
      }
      bVar1 = DAT_200047cd & 0x10;
      if ((int)((uint)DAT_200047cd << 0x18) < 0) {
        if ((DAT_200047cd & 0x10) == 0) {
          bVar4 = 0xff;
          goto LAB_0800b598;
        }
        bVar6 = 0xff;
LAB_0800b560:
        bVar4 = 0;
        bVar1 = 0;
        uVar7 = 0x14;
      }
      else {
        bVar4 = bVar1;
        if ((DAT_200047cd & 0x10) != 0) {
          bVar6 = 0;
          goto LAB_0800b560;
        }
LAB_0800b598:
        uVar7 = (uint)(byte)(&DAT_0801672b)[uVar7];
        bVar6 = bVar1;
      }
      FUN_0800fe78(uVar7,bVar1,bVar6,bVar4);
      goto LAB_0800b5a0;
    }
  }
  FUN_0800b494();
LAB_0800b5a0:
  FUN_0801017a();
  return 1;
}

