// FUN_08015e90 @ 0x08015e90  size=42  body=[[08015e90, 08015eb9]]

undefined4 FUN_08015e90(int param_1,int param_2,int param_3,undefined1 *param_4)

{
  int iVar1;
  undefined1 *puVar2;
  int iVar3;
  
  iVar3 = *(int *)(param_1 + 4);
  puVar2 = param_4 + param_3;
  iVar1 = param_2 - (int)param_4;
  for (; param_4 != puVar2; param_4 = param_4 + 1) {
    *param_4 = (char)(*(uint *)(iVar3 + 0x50 + ((uint)(param_4 + iVar1) & 0xfffffffc)) >>
                     (((uint)(param_4 + iVar1) & 3) << 3));
  }
  return 0;
}

