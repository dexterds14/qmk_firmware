// FUN_0800f278 @ 0x0800f278  size=30  body=[[0800f278, 0800f295]]

bool FUN_0800f278(int param_1,undefined4 *param_2,uint param_3)

{
  bool bVar1;
  
  bVar1 = param_1 + param_3 < 0x801;
  if (bVar1) {
    memcpy(param_2,(undefined4 *)(&DAT_20001704 + param_1),param_3);
  }
  return bVar1;
}

