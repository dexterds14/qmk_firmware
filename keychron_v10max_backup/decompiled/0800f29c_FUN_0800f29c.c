// FUN_0800f29c @ 0x0800f29c  size=38  body=[[0800f29c, 0800f2c1]]

undefined1 FUN_0800f29c(int param_1,int param_2,int param_3)

{
  char cVar1;
  int iVar2;
  
  iVar2 = 0;
  while( true ) {
    if (iVar2 == param_3) {
      return 1;
    }
    cVar1 = FUN_0800f67c(param_1 + iVar2 * 4,(uint *)(param_2 + iVar2 * 4));
    if (cVar1 == '\0') break;
    iVar2 = iVar2 + 1;
  }
  return 0;
}

