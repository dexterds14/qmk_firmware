// FUN_080141de @ 0x080141de  size=34  body=[[080141de, 080141ff]]

void FUN_080141de(char *param_1,uint param_2,uint param_3)

{
  bool bVar1;
  int iVar2;
  
  bVar1 = (bool)isCurrentModePrivileged();
  if (bVar1) {
    setBasePriority(0x30);
  }
  iVar2 = FUN_080141a4(param_1,param_2,param_3);
  if (iVar2 == 0) {
    FUN_080141ac(param_1,0xffffffff);
  }
  bVar1 = (bool)isCurrentModePrivileged();
  if (bVar1) {
    setBasePriority(0);
  }
  return;
}

