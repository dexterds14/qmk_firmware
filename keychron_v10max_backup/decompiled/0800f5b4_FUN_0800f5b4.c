// FUN_0800f5b4 @ 0x0800f5b4  size=38  body=[[0800f5b4, 0800f5d9]]

bool FUN_0800f5b4(int param_1,uint param_2)

{
  int iVar1;
  uint local_14;
  
  local_14 = ~param_2;
  iVar1 = (**(code **)(*DAT_20001f10 + 0xc))
                    (DAT_20001f10,param_1 + DAT_20000ea8,4,&local_14,param_1);
  return iVar1 == 0;
}

