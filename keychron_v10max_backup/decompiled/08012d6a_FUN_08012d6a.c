// FUN_08012d6a @ 0x08012d6a  size=54  body=[[08012d6a, 08012d9f]]

void FUN_08012d6a(int param_1)

{
  int iVar1;
  
  if (((**(char **)(param_1 + 0x70) == '\x04') &&
      ((1 << *(sbyte *)(param_1 + 0x74) & (uint)*(ushort *)(*(char **)(param_1 + 0x70) + 10)) == 0))
     && (iVar1 = FUN_08013d68(param_1), iVar1 != 0)) {
    FUN_08014310(*(int *)(param_1 + 0x70),(uint)*(byte *)(param_1 + 0x74),iVar1,
                 *(int *)(param_1 + 0x1c) + -4);
    return;
  }
  return;
}

