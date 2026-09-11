// FUN_08012e46 @ 0x08012e46  size=40  body=[[08012e46, 08012e6d]]

void FUN_08012e46(int *param_1)

{
  undefined4 *puVar1;
  
  *(undefined1 *)(param_1 + 2) = 1;
  FUN_08013afa(param_1,-2);
  FUN_08013ea2(param_1);
  puVar1 = (undefined4 *)param_1[0x29];
  if (puVar1 != (undefined4 *)0x0) {
                    // WARNING: Could not recover jumptable at 0x08012e6a. Too many branches
                    // WARNING: Treating indirect jump as call
    (*(code *)puVar1[3])(*puVar1);
    return;
  }
  return;
}

