// FUN_0800fc20 @ 0x0800fc20  size=70  body=[[0800fc20, 0800fc65]]

uint FUN_0800fc20(int param_1,uint param_2)

{
  short sVar1;
  ushort uVar2;
  uint uVar3;
  byte bVar4;
  
  if (param_1 != 0) {
    uVar2 = (ushort)(param_1 >> 0x1f);
    sVar1 = ((ushort)param_1 ^ uVar2) - uVar2;
    if ((int)param_2 < 0) {
      bVar4 = 0x60 - (char)((int)(((int)sVar1 + param_2) * 0x20) / (int)((int)sVar1 - param_2));
    }
    else {
      bVar4 = 0x20 - (char)((int)((param_2 - (int)sVar1) * 0x20) / (int)((int)sVar1 + param_2));
    }
    uVar3 = (uint)bVar4;
    if (param_1 < 0) {
      uVar3 = -uVar3 & 0xff;
    }
    return uVar3;
  }
  return (param_2 >> 0x1f) << 7;
}

