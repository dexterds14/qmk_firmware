// FUN_0800fa18 @ 0x0800fa18  size=76  body=[[0800fa18, 0800fa63]]

uint FUN_0800fa18(undefined4 param_1,int param_2,int param_3,int param_4)

{
  int iVar1;
  char local_c;
  uint3 uStack_b;
  
  iVar1 = (param_4 + 0x34) * 2;
  iVar1 = param_3 * ((byte)(&DAT_20000d0c)[iVar1] - 0x20) +
          param_2 * ((byte)(&DAT_20000d0b)[iVar1] - 0x70);
  local_c = (char)param_1;
  if (iVar1 < 0) {
    iVar1 = iVar1 + 0x3f;
  }
  uStack_b = (uint3)((uint)param_1 >> 8);
  return (uint)(byte)(local_c + (char)(iVar1 >> 6)) | (uStack_b & 0xff) << 8 |
         (uStack_b & 0xff00) << 8;
}

