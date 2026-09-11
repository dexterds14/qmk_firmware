// FUN_08012d30 @ 0x08012d30  size=58  body=[[08012d30, 08012d69]]

void FUN_08012d30(int param_1,int param_2)

{
  int iVar1;
  int iVar2;
  int local_c;
  
  iVar2 = *(int *)(param_1 + 0x34);
  if (((**(char **)(iVar2 + 0x88) == '\x04') &&
      ((1 << *(sbyte *)(iVar2 + 0x8c) & (uint)*(ushort *)(*(char **)(iVar2 + 0x88) + 8)) == 0)) &&
     (local_c = param_2, iVar1 = FUN_08013eba(iVar2,&local_c), iVar1 != 0)) {
    FUN_08014334(*(int *)(iVar2 + 0x88),(uint)*(byte *)(iVar2 + 0x8c),iVar1,local_c);
  }
  return;
}

