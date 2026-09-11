// FUN_0800f7f8 @ 0x0800f7f8  size=30  body=[[0800f7f8, 0800f815]]

ushort FUN_0800f7f8(void)

{
  DAT_20000ec0 = DAT_20000ec0 * 0x805 + 0x3619;
  return DAT_20000ec0 + (DAT_20000ec0 >> 8) & 0xff;
}

