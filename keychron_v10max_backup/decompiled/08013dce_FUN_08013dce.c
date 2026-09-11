// FUN_08013dce @ 0x08013dce  size=36  body=[[08013dce, 08013df1]]

void FUN_08013dce(int param_1)

{
  uint uVar1;
  
  *(int *)(param_1 + 0xc) = *(int *)(param_1 + 0xc) + -1;
  uVar1 = *(int *)(param_1 + 0x14) + *(int *)(param_1 + 0x1c);
  *(uint *)(param_1 + 0x14) = uVar1;
  if (*(uint *)(param_1 + 0x18) <= uVar1) {
    *(undefined4 *)(param_1 + 0x14) = *(undefined4 *)(param_1 + 0x24);
  }
  *(undefined4 *)(param_1 + 0x28) = 0;
  if (*(code **)(param_1 + 0x30) == (code *)0x0) {
    return;
  }
                    // WARNING: Could not recover jumptable at 0x08013dee. Too many branches
                    // WARNING: Treating indirect jump as call
  (**(code **)(param_1 + 0x30))();
  return;
}

