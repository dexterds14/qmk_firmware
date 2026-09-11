// FUN_08011a62 @ 0x08011a62  size=42  body=[[08011a62, 08011a8b]]

int FUN_08011a62(short param_1)

{
  ushort uVar1;
  int iVar2;
  
  uVar1 = param_1 * 0xb5;
  if ((short)uVar1 < 0) {
    iVar2 = (int)(short)(uVar1 - 0x80);
    if (iVar2 < 0) {
      iVar2 = iVar2 + 0xff;
    }
  }
  else {
    iVar2 = uVar1 + 0x80;
  }
  return (iVar2 << 0x10) >> 0x18;
}

