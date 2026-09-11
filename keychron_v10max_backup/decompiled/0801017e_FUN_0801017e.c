// FUN_0801017e @ 0x0801017e  size=40  body=[[0801017e, 080101a5]]

uint FUN_0801017e(char param_1)

{
  uint uVar1;
  
  uVar1 = (byte)(param_1 * '\x12') + 0x12 & 0xff;
  if (0x57 < uVar1) {
    uVar1 = 0x58;
  }
  return (uint)(byte)(param_1 * '\x12') | uVar1 << 8;
}

