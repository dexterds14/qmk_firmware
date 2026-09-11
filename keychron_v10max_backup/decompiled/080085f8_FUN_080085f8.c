// FUN_080085f8 @ 0x080085f8  size=152  body=[[080085f8, 0800868f]]

undefined1 * FUN_080085f8(uint param_1,undefined1 *param_2,uint param_3)

{
  bool bVar1;
  char *pcVar2;
  char cVar3;
  char *pcVar4;
  int iVar5;
  int iVar6;
  char *pcVar7;
  char *pcVar8;
  char local_40 [44];
  
  builtin_strncpy(local_40,"0123456789abcdefghijklmnopqrstuvwxyz",0x25);
  if (param_3 - 2 < 0x23) {
    pcVar7 = param_2 + -1;
    iVar6 = 0;
    do {
      iVar5 = iVar6;
      pcVar7 = pcVar7 + 1;
      *pcVar7 = local_40[param_1 - param_3 * (param_1 / param_3)];
      iVar6 = iVar5 + 1;
      bVar1 = param_3 <= param_1;
      param_1 = param_1 / param_3;
    } while (bVar1);
    param_2[iVar6] = 0;
    if (iVar5 != 0) {
      pcVar7 = param_2 + iVar6;
      pcVar8 = param_2 + -1;
      do {
        pcVar2 = pcVar8 + 1;
        cVar3 = *pcVar2;
        pcVar7 = pcVar7 + -1;
        *pcVar2 = *pcVar7;
        pcVar4 = pcVar8 + (2 - (int)param_2);
        *pcVar7 = cVar3;
        pcVar8 = pcVar2;
      } while ((int)pcVar4 < (int)(param_2 + iVar5 + (-1 - (int)pcVar2)));
    }
    return param_2;
  }
  *param_2 = 0;
  return (undefined1 *)0x0;
}

