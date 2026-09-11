// FUN_08009a14 @ 0x08009a14  size=68  body=[[08009a14, 08009a57]]

uint FUN_08009a14(undefined4 param_1,undefined *param_2,int *param_3)

{
  uint uVar1;
  int iVar2;
  int iVar3;
  uint uVar4;
  
  uVar4 = 0;
  do {
    iVar2 = param_3[2];
    iVar3 = param_3[1] + -1;
    if (-1 < iVar3) {
      do {
        if ((1 < *(ushort *)(iVar2 + 0xc)) && (*(short *)(iVar2 + 0xe) != -1)) {
          uVar1 = (*(code *)param_2)(param_1,iVar2);
          uVar4 = uVar4 | uVar1;
        }
        iVar3 = iVar3 + -1;
        iVar2 = iVar2 + 0x68;
      } while (iVar3 != -1);
    }
    param_3 = (int *)*param_3;
  } while (param_3 != (int *)0x0);
  return uVar4;
}

