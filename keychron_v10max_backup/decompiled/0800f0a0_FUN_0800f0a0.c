// FUN_0800f0a0 @ 0x0800f0a0  size=30  body=[[0800f0a0, 0800f0bd]]

undefined1 FUN_0800f0a0(int param_1,uint3 param_2,undefined4 param_3)

{
  undefined1 auStack_c [4];
  undefined4 uStack_8;
  
  auStack_c[3] = 0;
  auStack_c._0_3_ = param_2;
  uStack_8 = param_3;
  FUN_0800f1cc((undefined4 *)(auStack_c + 3),param_1,1);
  return auStack_c[3];
}

