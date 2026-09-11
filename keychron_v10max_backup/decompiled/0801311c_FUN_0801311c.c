// FUN_0801311c @ 0x0801311c  size=60  body=[[0801311c, 08013157]]

void FUN_0801311c(int param_1,byte *param_2,uint param_3)

{
  undefined4 uVar1;
  int iVar2;
  int iVar3;
  
  if (*param_2 < 9) {
    iVar2 = (int)(short)(ushort)*param_2;
    iVar3 = *(int *)(param_1 + iVar2 * 4);
    if (iVar3 != 0) {
      uVar1 = FUN_08013cfa();
      *(undefined4 *)(iVar3 + 4) = uVar1;
      iVar2 = *(int *)(param_1 + iVar2 * 4);
      *(uint *)(iVar2 + 0x48) = param_3;
      memcpy((undefined4 *)(iVar2 + 8),(undefined4 *)param_2,param_3);
      return;
    }
  }
  return;
}

