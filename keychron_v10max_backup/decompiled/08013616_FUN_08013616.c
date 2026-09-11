// FUN_08013616 @ 0x08013616  size=54  body=[[08013616, 0801364b]]

void FUN_08013616(int param_1,uint param_2)

{
  int iVar1;
  uint uVar2;
  
  if (param_2 < 2) {
    param_2 = 2;
  }
  uVar2 = 2;
  while( true ) {
    FUN_08013d1c(param_1 + param_2);
    iVar1 = FUN_08013cfa();
    if ((uint)(iVar1 - param_1) < param_2) break;
    param_2 = uVar2 + 1;
    param_1 = iVar1;
    uVar2 = param_2;
  }
  if (2 < uVar2) {
    FUN_080135dc(1);
    return;
  }
  return;
}

