// FUN_08011398 @ 0x08011398  size=166  body=[[08011398, 0801143d]]

void FUN_08011398(int param_1,int param_2,int param_3,int param_4)

{
  byte bVar1;
  uint uVar2;
  int iVar3;
  byte bVar4;
  byte bVar5;
  byte bVar6;
  uint uVar7;
  uint uVar8;
  uint uVar9;
  
  iVar3 = param_1 * 4;
  bVar5 = (&DAT_08016842)[iVar3];
  bVar1 = (&DAT_08016843)[iVar3];
  uVar2 = (byte)(&DAT_08016840)[param_1 * 4] & 3;
  uVar9 = (uint)((byte)(&DAT_08016841)[iVar3] >> 3);
  uVar8 = (uint)(bVar5 >> 3);
  uVar7 = (uint)(bVar1 >> 3);
  bVar4 = *(byte *)(uVar2 * 0x18 + 0x20001fc2 + uVar9);
  bVar6 = (byte)(1 << ((byte)(&DAT_08016841)[iVar3] & 7));
  if (param_2 == 0) {
    bVar6 = bVar4 & ~bVar6;
  }
  else {
    bVar6 = bVar6 | bVar4;
  }
  iVar3 = uVar2 * 0x18 + 0x20001fc2;
  *(byte *)(iVar3 + uVar9) = bVar6;
  bVar4 = *(byte *)(iVar3 + uVar8);
  bVar5 = (byte)(1 << (bVar5 & 7));
  if (param_3 == 0) {
    bVar4 = bVar4 & ~bVar5;
  }
  else {
    bVar4 = bVar4 | bVar5;
  }
  iVar3 = uVar2 * 0x18 + 0x20001fc2;
  *(byte *)(iVar3 + uVar8) = bVar4;
  bVar5 = *(byte *)(iVar3 + uVar7);
  bVar1 = (byte)(1 << (bVar1 & 7));
  if (param_4 == 0) {
    bVar5 = bVar5 & ~bVar1;
  }
  else {
    bVar5 = bVar5 | bVar1;
  }
  *(byte *)(uVar2 * 0x18 + 0x20001fc2 + uVar7) = bVar5;
  (&DAT_20001fc0)[uVar2] = 1;
  return;
}

