// FUN_0800a3d4 @ 0x0800a3d4  size=54  body=[[0800a3d4, 0800a409]]

void FUN_0800a3d4(uint param_1,undefined4 param_2)

{
  bool bVar1;
  
  bVar1 = FUN_0800c158();
  if (!bVar1) {
    if (param_1 != 0) {
      if ((DAT_20001503 == param_1) && (DAT_20001501 == '\x03')) {
        return;
      }
      DAT_20001503 = (byte)param_1;
      DAT_20001502 = 0;
    }
    (*DAT_20000c78)(param_1,param_2);
    DAT_20001501 = '\x05';
  }
  return;
}

