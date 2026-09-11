// FUN_08011668 @ 0x08011668  size=92  body=[[08011668, 080116c3]]

void FUN_08011668(void)

{
  undefined4 uVar1;
  uint uVar2;
  byte *pbVar3;
  byte bVar4;
  byte bVar5;
  
  DAT_20001ff5 = 1;
  for (bVar5 = 0; bVar5 < DAT_20001ff5; bVar5 = bVar5 + 1) {
    FUN_08015338((uint *)&DAT_40020400,0x8000,0x20);
    FUN_08015338((uint *)&DAT_40020400,0x4000,0x20);
  }
  FUN_08011660();
  bVar5 = DAT_20001ff5;
  pbVar3 = &DAT_20001ff7;
  for (bVar4 = 0; bVar4 < bVar5; bVar4 = bVar4 + 1) {
    uVar1 = DAT_40020410;
    uVar2 = DAT_40020410;
    *pbVar3 = (byte)(uVar2 >> 0xd) & 2 | (byte)((uint)uVar1 >> 8) >> 7;
    pbVar3 = pbVar3 + 1;
  }
  return;
}

