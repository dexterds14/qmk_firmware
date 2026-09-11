// FUN_08016340 @ 0x08016340  size=132  body=[[08016340, 080163c3]]

void FUN_08016340(char *param_1,uint param_2)

{
  bool bVar1;
  code *pcVar2;
  char *pcVar3;
  
  if ((param_2 & 0xc) == 0) {
    pcVar3 = *(char **)(param_1 + 4);
    if (*pcVar3 != '\0') {
      if (((int)(param_2 << 0x1b) < 0) && (*(code **)(pcVar3 + 4) != (code *)0x0)) {
        (**(code **)(pcVar3 + 4))();
      }
      if (-1 < (int)(param_2 << 0x1a)) {
        return;
      }
      pcVar2 = *(code **)(*(int *)(param_1 + 4) + 4);
      if (pcVar2 == (code *)0x0) {
        return;
      }
      *param_1 = '\x04';
      (*pcVar2)(param_1);
      if (*param_1 != '\x04') {
        return;
      }
      *param_1 = '\x03';
      return;
    }
    FUN_0801625c(param_1);
    pcVar2 = *(code **)(pcVar3 + 4);
    if (pcVar2 != (code *)0x0) {
      *param_1 = '\x04';
      (*pcVar2)(param_1);
      if (*param_1 != '\x04') goto LAB_08016362;
    }
    *param_1 = '\x02';
  }
  else {
    FUN_0801357c();
    FUN_0801625c(param_1);
    if (*(code **)(*(int *)(param_1 + 4) + 8) != (code *)0x0) {
      (**(code **)(*(int *)(param_1 + 4) + 8))(param_1);
    }
  }
LAB_08016362:
  bVar1 = (bool)isCurrentModePrivileged();
  if (bVar1) {
    setBasePriority(0x30);
  }
  FUN_08013ab0((undefined4 *)(param_1 + 8),0);
  bVar1 = (bool)isCurrentModePrivileged();
  if (bVar1) {
    setBasePriority(0);
  }
  return;
}

