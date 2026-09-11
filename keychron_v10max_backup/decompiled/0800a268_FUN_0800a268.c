// FUN_0800a268 @ 0x0800a268  size=36  body=[[0800a268, 0800a28b]]

void FUN_0800a268(undefined4 param_1,undefined4 param_2)

{
  bool bVar1;
  
  bVar1 = FUN_0800c158();
  if (!bVar1) {
    if (DAT_20000c7c != (code *)0x0) {
      (*DAT_20000c7c)(param_1,param_2);
    }
    DAT_20001501 = 4;
    DAT_20001503 = (undefined1)param_1;
  }
  return;
}

