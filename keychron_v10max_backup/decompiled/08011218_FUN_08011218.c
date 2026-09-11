// FUN_08011218 @ 0x08011218  size=42  body=[[08011218, 08011241]]

undefined4 FUN_08011218(uint param_1)

{
  if ((&DAT_20001ff2)[param_1] != '\0') {
    FUN_080111a0(param_1,1,0,(uint)(&DAT_2000483d + param_1 * 0xc0),0xc0);
  }
  (&DAT_20001ff2)[param_1] = 0;
  return 1;
}

