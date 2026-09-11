// FUN_0800e46c @ 0x0800e46c  size=48  body=[[0800e46c, 0800e49b]]

void FUN_0800e46c(void)

{
  byte *pbVar1;
  byte bVar2;
  int iVar3;
  
  pbVar1 = DAT_20000e9c;
  bVar2 = FUN_0800e43c();
  *pbVar1 = bVar2;
  pbVar1 = DAT_20000e9c;
  iVar3 = FUN_080089d4((int *)DAT_20000e9c,(int *)&DAT_2000169c,8);
  if (iVar3 != 0) {
    memcpy((undefined4 *)&DAT_2000169c,(undefined4 *)pbVar1,8);
    FUN_08012150();
    return;
  }
  return;
}

