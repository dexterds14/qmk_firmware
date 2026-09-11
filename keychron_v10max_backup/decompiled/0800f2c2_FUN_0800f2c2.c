// FUN_0800f2c2 @ 0x0800f2c2  size=38  body=[[0800f2c2, 0800f2e7]]

bool FUN_0800f2c2(int param_1,int param_2,int param_3)

{
  bool bVar1;
  int iVar2;
  
  iVar2 = 0;
  while( true ) {
    if (iVar2 == param_3) {
      return true;
    }
    bVar1 = FUN_0800f5b4(param_1 + iVar2 * 4,*(uint *)(param_2 + iVar2 * 4));
    if (!bVar1) break;
    iVar2 = iVar2 + 1;
  }
  return bVar1;
}

