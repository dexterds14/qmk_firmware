// FUN_0801584e @ 0x0801584e  size=26  body=[[0801584e, 08015867]]

undefined4 FUN_0801584e(int param_1,int param_2)

{
  undefined4 uVar1;
  uint uVar2;
  
  uVar2 = *(uint *)(*(int *)(param_1 + 0x54) + (param_2 + 0x58) * 0x20);
  uVar1 = 0;
  if ((uVar2 & 0x8000) != 0) {
    if ((uVar2 & 0x200000) == 0) {
      uVar1 = 2;
    }
    else {
      uVar1 = 1;
    }
  }
  return uVar1;
}

