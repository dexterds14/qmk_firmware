// FUN_08011338 @ 0x08011338  size=50  body=[[08011338, 08011369]]

void FUN_08011338(uint param_1,undefined1 param_2,undefined1 param_3,undefined1 param_4)

{
  int iVar1;
  byte bVar2;
  byte bVar3;
  uint uVar4;
  
  if (param_1 < 0x58) {
    iVar1 = param_1 * 4;
    bVar2 = (&DAT_08016842)[iVar1];
    bVar3 = (&DAT_08016843)[iVar1];
    uVar4 = (byte)(&DAT_08016840)[param_1 * 4] & 3;
    (&DAT_2000483d)[(uint)(byte)(&DAT_08016841)[iVar1] + uVar4 * 0xc0] = param_2;
    (&DAT_2000483d)[(uint)bVar2 + uVar4 * 0xc0] = param_3;
    (&DAT_2000483d)[(uint)bVar3 + uVar4 * 0xc0] = param_4;
    (&DAT_20001ff2)[uVar4] = 1;
  }
  return;
}

