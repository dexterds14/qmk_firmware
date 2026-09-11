// FUN_08011180 @ 0x08011180  size=28  body=[[08011180, 0801119b]]

void FUN_08011180(int param_1,undefined4 param_2,uint param_3)

{
  if ((param_1 != 0) && (DAT_20001f4c == '\0')) {
    FUN_08010a4c(0,param_2,param_3);
    FUN_08011008(0);
  }
  DAT_20001f4c = (char)param_1;
  return;
}

