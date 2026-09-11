// FUN_0800f81c @ 0x0800f81c  size=62  body=[[0800f81c, 0800f859]]

uint FUN_0800f81c(uint param_1)

{
  ushort uVar1;
  uint uVar2;
  
  uVar2 = param_1;
  if ((param_1 & 0x40) != 0) {
    uVar2 = ~param_1 & 0xff;
  }
  uVar1 = (ushort)uVar2 & 0xf;
  if ((param_1 & 0x40) != 0) {
    uVar1 = uVar1 + 1;
  }
  uVar2 = (uVar2 & 0x3f) >> 4;
  uVar2 = (uint)(byte)(&DAT_08016f94)[uVar2 * 2] +
          ((int)(short)(ushort)(byte)(&DAT_08016f95)[uVar2 * 2] * (int)(short)uVar1 >> 4) & 0xff;
  if ((int)(param_1 << 0x18) < 0) {
    uVar2 = -uVar2 & 0xff;
  }
  return uVar2 ^ 0x80;
}

