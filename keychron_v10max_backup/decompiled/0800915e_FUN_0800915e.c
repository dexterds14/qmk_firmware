// FUN_0800915e @ 0x0800915e  size=78  body=[[0800915e, 080091ab]]

undefined4 FUN_0800915e(int *param_1,int param_2)

{
  undefined4 uVar1;
  int iVar2;
  code *pcVar3;
  bool in_ZR;
  bool in_CY;
  
  if (in_CY && !in_ZR) {
    *param_1 = 0x16;
    return 0xffffffff;
  }
  iVar2 = param_1[0xf];
  if ((iVar2 != 0) && (pcVar3 = *(code **)(iVar2 + param_2 * 4), pcVar3 != (code *)0x0)) {
    if (pcVar3 != (code *)0x1) {
      if (pcVar3 == (code *)0xffffffff) {
        *param_1 = 0x16;
        return 1;
      }
      *(undefined4 *)(iVar2 + param_2 * 4) = 0;
      (*pcVar3)(param_2);
    }
    return 0;
  }
  thunk_FUN_080166fc();
  uVar1 = FUN_0800a190(param_1);
  return uVar1;
}

