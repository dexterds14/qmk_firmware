// FUN_08013f26 @ 0x08013f26  size=38  body=[[08013f26, 08013f4b]]

void FUN_08013f26(int param_1,undefined4 param_2)

{
  undefined4 *puVar1;
  uint uVar2;
  
  puVar1 = *(undefined4 **)(param_1 + 0x10);
  *puVar1 = param_2;
  *(int *)(param_1 + 0xc) = *(int *)(param_1 + 0xc) + -1;
  uVar2 = (int)puVar1 + *(int *)(param_1 + 0x1c);
  *(uint *)(param_1 + 0x10) = uVar2;
  if (*(uint *)(param_1 + 0x18) <= uVar2) {
    *(undefined4 *)(param_1 + 0x10) = *(undefined4 *)(param_1 + 0x24);
  }
  *(undefined4 *)(param_1 + 0x28) = 0;
  if (*(code **)(param_1 + 0x30) == (code *)0x0) {
    return;
  }
                    // WARNING: Could not recover jumptable at 0x08013f48. Too many branches
                    // WARNING: Treating indirect jump as call
  (**(code **)(param_1 + 0x30))();
  return;
}

