// FUN_080116d0 @ 0x080116d0  size=342  body=[[080116d0, 08011825]]

byte FUN_080116d0(void)

{
  uint uVar1;
  char cVar2;
  char cVar3;
  uint uVar4;
  uint extraout_r2;
  uint extraout_r2_00;
  uint extraout_r2_01;
  uint extraout_r2_02;
  bool bVar5;
  uint uVar6;
  uint uVar7;
  uint uVar8;
  byte bVar9;
  byte bVar10;
  undefined4 local_48;
  uint local_44;
  undefined4 local_40;
  uint local_3c;
  undefined4 local_38;
  uint local_34;
  undefined4 local_30;
  uint local_2c;
  undefined1 auStack_28 [4];
  
  bVar9 = 0;
  for (bVar10 = 0; uVar8 = (uint)bVar10, uVar8 < DAT_20001ff5; bVar10 = bVar10 + 1) {
    uVar4 = DAT_40020410;
    uVar6 = DAT_40020410;
    uVar4 = (uVar4 & 0xffff) >> 0xf;
    uVar6 = uVar6 >> 0xd & 2;
    uVar7 = uVar6 | uVar4;
    if ((((byte)(&DAT_20001ff7)[uVar8] & 3) != uVar7) || ((&DAT_20001ff8)[uVar8] != '\0')) {
      uVar1 = (uint)(byte)(&DAT_20001ff7)[uVar8] << 2;
      (&DAT_20001ff7)[uVar8] = (byte)uVar7 | (byte)uVar1;
      cVar3 = (&DAT_080170b4)[uVar7 | uVar1 & 0xf] + (&DAT_20001ff6)[uVar8];
      (&DAT_20001ff6)[uVar8] = cVar3;
      if (((byte)(cVar3 + 3U) < 7) && ((uVar6 | uVar4) != 3)) {
        bVar5 = false;
      }
      else {
        if ('\0' < cVar3) {
          (&DAT_20001ff4)[uVar8] = (&DAT_20001ff4)[uVar8] + '\x01';
          uVar4 = FUN_08012574();
          local_3c = CONCAT22(local_3c._2_2_,0x103);
          local_40 = CONCAT22((short)uVar4,CONCAT11(0xfc,bVar10));
          FUN_0800d50c(local_40,local_3c,extraout_r2,0x103);
          FUN_08013a7a(200);
          uVar4 = FUN_08012574();
          local_44 = CONCAT22(local_44._2_2_,3);
          local_48 = CONCAT22((short)uVar4,CONCAT11(0xfc,bVar10));
          FUN_0800d50c(local_48,local_44,extraout_r2_00,3);
          FUN_08013a7a(200);
        }
        cVar2 = (&DAT_20001ff6)[uVar8];
        if (cVar2 < '\0') {
          (&DAT_20001ff4)[uVar8] = (&DAT_20001ff4)[uVar8] + -1;
          uVar4 = FUN_08012574();
          local_2c = CONCAT22(local_2c._2_2_,0x102);
          local_30 = CONCAT22((short)uVar4,CONCAT11(0xfd,bVar10));
          FUN_0800d50c(local_30,local_2c,extraout_r2_01,auStack_28);
          FUN_08013a7a(200);
          uVar4 = FUN_08012574();
          local_34 = CONCAT22(local_34._2_2_,2);
          local_38 = CONCAT22((short)uVar4,CONCAT11(0xfd,bVar10));
          FUN_0800d50c(local_38,local_34,extraout_r2_02,2);
          FUN_08013a7a(200);
        }
        bVar5 = cVar2 < '\0' || '\0' < cVar3;
        (&DAT_20001ff6)[uVar8] = 0;
      }
      bVar9 = bVar9 | bVar5;
      (&DAT_20001ff8)[uVar8] = 0;
    }
  }
  return bVar9;
}

