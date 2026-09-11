// FUN_0800a190 @ 0x0800a190  size=38  body=[[0800a190, 0800a1b5]]

void FUN_0800a190(int *param_1)

{
  undefined8 uVar1;
  
  DAT_200014fc = 0;
  uVar1 = FUN_080166ec();
  if (((int)uVar1 == -1) && (DAT_200014fc != 0)) {
    *param_1 = DAT_200014fc;
    return;
  }
  return;
}

