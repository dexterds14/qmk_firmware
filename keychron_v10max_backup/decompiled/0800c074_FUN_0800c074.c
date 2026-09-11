// FUN_0800c074 @ 0x0800c074  size=104  body=[[0800c074, 0800c0db]]

void FUN_0800c074(int param_1,int param_2)

{
  byte bVar1;
  byte *pbVar2;
  char cVar3;
  uint uVar4;
  int iVar5;
  short sVar6;
  uint uVar7;
  
  if (param_1 == 0) {
    uVar7 = ((uint)(param_2 * 0xce4) >> 10) * 0x14;
    uVar4 = 10;
  }
  else {
    uVar7 = param_2 * 0x423;
    uVar4 = 499;
  }
  sVar6 = (short)(uVar7 / uVar4);
  bVar1 = FUN_08010cf4();
  if (bVar1 != 0) {
    cVar3 = '\0';
    iVar5 = 0;
    pbVar2 = &DAT_2000483d;
    do {
      cVar3 = cVar3 + '\x01';
      iVar5 = iVar5 + (uint)*pbVar2;
      pbVar2 = pbVar2 + 1;
    } while (cVar3 != -0x40);
    pbVar2 = (byte *)0x200048fc;
    cVar3 = '\0';
    do {
      cVar3 = cVar3 + '\x01';
      pbVar2 = pbVar2 + 1;
      iVar5 = iVar5 + (uint)*pbVar2;
    } while (cVar3 != -0x40);
    sVar6 = (short)((uint)(iVar5 * 0x3c) / 0x106f8) + sVar6;
  }
  DAT_20000d04 = sVar6;
  return;
}

