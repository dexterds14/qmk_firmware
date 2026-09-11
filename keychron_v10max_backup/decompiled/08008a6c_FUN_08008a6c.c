// FUN_08008a6c @ 0x08008a6c  size=46  body=[[08008a6c, 08008a99]]

undefined4 FUN_08008a6c(uint *param_1,uint *param_2,int param_3,int param_4)

{
  uint uVar1;
  byte *pbVar2;
  
  if (param_4 == 0) {
    return 0;
  }
  pbVar2 = (byte *)(param_3 + -1);
  do {
    pbVar2 = pbVar2 + 1;
    uVar1 = FUN_08008a30(param_1,(uint)*pbVar2,param_2);
    if (uVar1 == 0xffffffff) {
      return 0xffffffff;
    }
  } while (pbVar2 != (byte *)(param_4 + param_3 + -1));
  return 0;
}

