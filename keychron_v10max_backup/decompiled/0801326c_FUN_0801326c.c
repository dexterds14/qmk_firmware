// FUN_0801326c @ 0x0801326c  size=32  body=[[0801326c, 0801328b]]

void FUN_0801326c(int param_1,int param_2,int param_3)

{
  int *piVar1;
  
  if (((param_2 - 1U < 8) && (piVar1 = *(int **)(param_1 + param_2 * 4), piVar1 != (int *)0x0)) &&
     (*piVar1 = param_3 << 2, param_3 != 0)) {
    DAT_200022ec = DAT_200022ec | 1;
  }
  return;
}

