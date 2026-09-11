// FUN_080130ea @ 0x080130ea  size=22  body=[[080130ea, 080130ff]]

void FUN_080130ea(int *param_1,undefined4 param_2,int param_3)

{
  int iVar1;
  uint uVar2;
  
  iVar1 = *param_1;
  if (iVar1 != 0) {
    uVar2 = *(uint *)(iVar1 + 0x48);
    *(uint *)(param_3 + 0x48) = uVar2;
    memcpy((undefined4 *)(param_3 + 8),(undefined4 *)(iVar1 + 8),uVar2);
    return;
  }
  return;
}

