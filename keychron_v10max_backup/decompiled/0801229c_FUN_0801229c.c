// FUN_0801229c @ 0x0801229c  size=44  body=[[0801229c, 080122c7]]

void FUN_0801229c(int param_1,uint param_2)

{
  int iVar1;
  int iVar2;
  byte *pbVar3;
  
  iVar1 = 0;
  pbVar3 = (byte *)(param_1 + 1);
  iVar2 = -1;
  do {
    pbVar3 = pbVar3 + 1;
    if (*pbVar3 == param_2) {
      return;
    }
    if ((iVar2 == -1) && (*pbVar3 == 0)) {
      iVar2 = (int)(char)iVar1;
    }
    iVar1 = iVar1 + 1;
  } while (iVar1 != 6);
  if (iVar2 != -1) {
    *(char *)(param_1 + iVar2 + 2) = (char)param_2;
  }
  return;
}

