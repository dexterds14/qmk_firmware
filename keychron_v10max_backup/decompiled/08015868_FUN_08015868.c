// FUN_08015868 @ 0x08015868  size=26  body=[[08015868, 08015881]]

undefined4 FUN_08015868(int param_1,int param_2)

{
  undefined4 uVar1;
  uint uVar2;
  
  uVar2 = *(uint *)(*(int *)(param_1 + 0x54) + (param_2 + 0x48) * 0x20);
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

