// FUN_0800e4a4 @ 0x0800e4a4  size=48  body=[[0800e4a4, 0800e4d3]]

void FUN_0800e4a4(void)

{
  int *piVar1;
  byte bVar2;
  int iVar3;
  
  piVar1 = DAT_20000e98;
  bVar2 = FUN_0800e43c();
  *(byte *)((int)piVar1 + 1) = bVar2;
  piVar1 = DAT_20000e98;
  iVar3 = FUN_080089d4(DAT_20000e98,(int *)&DAT_2000167c,0x20);
  if (iVar3 != 0) {
    memcpy((undefined4 *)&DAT_2000167c,piVar1,0x20);
    FUN_08012160((undefined1 *)piVar1);
    return;
  }
  return;
}

