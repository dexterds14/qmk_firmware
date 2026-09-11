// FUN_080134ac @ 0x080134ac  size=38  body=[[080134ac, 080134d1]]

uint FUN_080134ac(int param_1,int param_2,int param_3)

{
  uint uVar1;
  uint uVar2;
  
  uVar2 = param_3 + DAT_200049d0 + param_2 + -1 & -param_2;
  uVar1 = param_1 + uVar2;
  if ((DAT_200049d4 < uVar1) || (uVar1 < DAT_200049d0)) {
    uVar2 = 0;
    uVar1 = DAT_200049d0;
  }
  DAT_200049d0 = uVar1;
  return uVar2;
}

