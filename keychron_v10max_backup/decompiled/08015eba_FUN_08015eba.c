// FUN_08015eba @ 0x08015eba  size=58  body=[[08015eba, 08015ef3]]

undefined4 FUN_08015eba(int param_1,int param_2,int param_3,byte *param_4)

{
  int iVar1;
  int iVar2;
  byte *pbVar3;
  int iVar4;
  uint uVar5;
  
  pbVar3 = param_4 + param_3;
  iVar4 = *(int *)(param_1 + 4) + 0x50;
  iVar2 = param_2 - (int)param_4;
  for (; param_4 != pbVar3; param_4 = param_4 + 1) {
    uVar5 = (uint)(param_4 + iVar2) & 0xfffffffc;
    iVar1 = ((uint)(param_4 + iVar2) & 3) << 3;
    *(uint *)(iVar4 + uVar5) = (uint)*param_4 << iVar1 | *(uint *)(iVar4 + uVar5) & ~(0xff << iVar1)
    ;
  }
  return 0;
}

