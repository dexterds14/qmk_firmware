// FUN_08014d0c @ 0x08014d0c  size=46  body=[[08014d0c, 08014d39]]

bool FUN_08014d0c(int param_1,int param_2,uint param_3,undefined4 *param_4)

{
  bool bVar1;
  
  bVar1 = *(char *)(param_1 + 4) == '\x05';
  if (!bVar1) {
    *(undefined1 *)(param_1 + 4) = 3;
    *(undefined4 *)(*(int *)(param_1 + 0x1c) + 0xc) = 0xffff;
    memcpy(param_4,(undefined4 *)(param_2 + *(int *)(*(int *)(param_1 + 0x20) + 0x14)),param_3);
    *(undefined1 *)(param_1 + 4) = 2;
  }
  return bVar1;
}

