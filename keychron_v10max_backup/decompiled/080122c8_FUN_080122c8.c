// FUN_080122c8 @ 0x080122c8  size=24  body=[[080122c8, 080122df]]

void FUN_080122c8(int param_1,uint param_2)

{
  byte *pbVar1;
  
  pbVar1 = (byte *)(param_1 + 1);
  do {
    pbVar1 = pbVar1 + 1;
    if (*pbVar1 == param_2) {
      *pbVar1 = 0;
    }
  } while (pbVar1 != (byte *)(param_1 + 7));
  return;
}

