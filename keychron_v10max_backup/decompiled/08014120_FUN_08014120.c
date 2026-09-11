// FUN_08014120 @ 0x08014120  size=34  body=[[08014120, 08014141]]

void FUN_08014120(char *param_1,undefined4 param_2)

{
  bool bVar1;
  int iVar2;
  char cVar3;
  
  bVar1 = (bool)isCurrentModePrivileged();
  if (bVar1) {
    setBasePriority(0x30);
  }
  *(undefined4 *)(param_1 + 4) = param_2;
  iVar2 = FUN_080163f4(param_1);
  if (iVar2 == 0) {
    cVar3 = '\x02';
  }
  else {
    cVar3 = '\x01';
  }
  *param_1 = cVar3;
  bVar1 = (bool)isCurrentModePrivileged();
  if (bVar1) {
    setBasePriority(0);
  }
  return;
}

