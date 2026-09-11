// FUN_08014e6e @ 0x08014e6e  size=70  body=[[08014e6e, 08014eb3]]

undefined4 FUN_08014e6e(int *param_1,int param_2)

{
  int iVar1;
  uint uVar2;
  undefined4 uVar3;
  int *piVar4;
  int iVar5;
  int *piVar6;
  
  if ((char)param_1[1] == '\x05') {
    uVar3 = 1;
  }
  else {
    iVar5 = *(int *)(param_1[8] + 0x14);
    iVar1 = FUN_08014030(param_1,param_2);
    piVar6 = (int *)(iVar5 + iVar1);
    *(undefined1 *)(param_1 + 1) = 3;
    uVar2 = FUN_0801404a(param_1,param_2);
    piVar4 = piVar6;
    do {
      if (piVar4 == (int *)((uVar2 & 0xfffffffc) + (int)piVar6)) {
        uVar3 = 0;
        goto LAB_08014e9e;
      }
      iVar1 = *piVar4;
      piVar4 = piVar4 + 1;
    } while (iVar1 == -1);
    uVar3 = 5;
LAB_08014e9e:
    *(undefined1 *)(param_1 + 1) = 2;
  }
  return uVar3;
}

