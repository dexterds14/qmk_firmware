// FUN_08014462 @ 0x08014462  size=22  body=[[08014462, 08014477]]

void FUN_08014462(char *param_1)

{
  if (*param_1 == '\x05') {
    *param_1 = param_1[0x50];
    if ((code *)**(undefined4 **)(param_1 + 4) != (code *)0x0) {
                    // WARNING: Could not recover jumptable at 0x08014474. Too many branches
                    // WARNING: Treating indirect jump as call
      (*(code *)**(undefined4 **)(param_1 + 4))();
      return;
    }
  }
  return;
}

