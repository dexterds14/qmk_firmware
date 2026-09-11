// FUN_0800f13c @ 0x0800f13c  size=52  body=[[0800f13c, 0800f16f]]

void FUN_0800f13c(int *param_1,uint param_2,uint param_3,int param_4)

{
  int iVar1;
  int iStack_18;
  
  iVar1 = -(param_3 + 7 & 0xfffffff8);
  iStack_18 = param_4;
  FUN_0800f1cc((undefined4 *)((int)&iStack_18 + iVar1),param_2,param_3);
  iVar1 = FUN_080089d4(param_1,(int *)((int)&iStack_18 + iVar1),param_3);
  if (iVar1 != 0) {
    FUN_0800f1d6(param_1,param_2,param_3);
  }
  return;
}

