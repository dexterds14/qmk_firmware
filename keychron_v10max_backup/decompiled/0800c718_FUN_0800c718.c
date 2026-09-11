// FUN_0800c718 @ 0x0800c718  size=60  body=[[0800c718, 0800c71d] [08011844, 08011879]]

void FUN_0800c718(void)

{
  uint uVar1;
  uint uVar2;
  
  uVar1 = DAT_40020410;
  uVar2 = DAT_40020410;
  uVar2 = uVar2 >> 0xd & 2 | (uVar1 & 0xffff) >> 0xf;
  uVar1 = (uint)DAT_20001ff7;
  DAT_20001ff7 = (byte)uVar2 | (byte)(uVar1 << 2);
  DAT_20001ff6 = (&DAT_080170b4)[uVar2 | uVar1 << 2 & 0xf] + DAT_20001ff6;
  DAT_20001ff8 = 1;
  return;
}

