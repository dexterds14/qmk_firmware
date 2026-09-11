// FUN_0800d50c @ 0x0800d50c  size=64  body=[[0800d50c, 0800d54b]]

void FUN_0800d50c(uint param_1,uint param_2,uint param_3,undefined4 param_4)

{
  int iVar1;
  char local_13;
  uint local_10;
  uint local_c;
  
  local_13 = (char)(param_2 >> 8);
  if (local_13 != '\0') {
    local_10 = param_3;
    local_c = param_4;
    FUN_0800e374();
  }
  local_c = param_2 & 0xffff;
  local_10 = param_1;
  if (((param_2 & 0xff) == 0) || (iVar1 = FUN_0800d34c(&local_10), iVar1 != 0)) {
    FUN_0800e21c(local_10,local_c);
  }
  return;
}

