// FUN_080141bc @ 0x080141bc  size=34  body=[[080141bc, 080141dd]]

void FUN_080141bc(char *param_1,uint param_2,uint param_3,uint param_4)

{
  bool bVar1;
  int iVar2;
  
  bVar1 = (bool)isCurrentModePrivileged();
  if (bVar1) {
    setBasePriority(0x30);
  }
  iVar2 = FUN_08014196(param_1,param_2,param_3,param_4);
  if (iVar2 == 0) {
    FUN_080141ac(param_1,0xffffffff);
  }
  bVar1 = (bool)isCurrentModePrivileged();
  if (bVar1) {
    setBasePriority(0);
  }
  return;
}

