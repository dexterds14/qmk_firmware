// FUN_08014d3a @ 0x08014d3a  size=176  body=[[08014d3a, 08014de9]]

int FUN_08014d3a(int param_1,uint param_2,int param_3,undefined1 *param_4)

{
  byte bVar1;
  int iVar2;
  uint uVar3;
  uint uVar4;
  int iVar5;
  int iVar6;
  undefined1 *puVar7;
  uint local_24;
  
  if (*(char *)(param_1 + 4) == '\x05') {
    iVar2 = 1;
  }
  else {
    iVar5 = *(int *)(param_1 + 0x1c);
    iVar6 = *(int *)(param_1 + 0x20);
    *(undefined1 *)(param_1 + 4) = 4;
    *(undefined4 *)(iVar5 + 0xc) = 0xffff;
    *(uint *)(iVar5 + 0x10) = *(uint *)(iVar5 + 0x10) & 0xfffffcff;
    *(uint *)(iVar5 + 0x10) = *(uint *)(iVar5 + 0x10) | 0x200;
    *(uint *)(iVar5 + 0x10) = *(uint *)(iVar5 + 0x10) | 1;
    local_24 = param_2;
    do {
      if (param_3 == 0) {
        iVar2 = 0;
        break;
      }
      uVar4 = *(uint *)(iVar6 + 4);
      bVar1 = 0;
      while( true ) {
        uVar3 = (uint)bVar1;
        bVar1 = bVar1 + 1;
        if (uVar4 <= uVar3) break;
        *(undefined1 *)((int)&local_24 + uVar3) = 0xff;
      }
      iVar2 = *(int *)(iVar6 + 0x14);
      uVar4 = param_2 & 0xfffffffc;
      puVar7 = param_4;
      do {
        param_4 = puVar7 + 1;
        *(undefined1 *)((int)&local_24 + (param_2 & 3)) = *puVar7;
        param_2 = param_2 + 1;
        param_3 = param_3 + -1;
        if ((param_2 & 3) == 0) break;
        puVar7 = param_4;
      } while (param_3 != 0);
      *(uint *)(iVar2 + uVar4) = local_24;
      do {
      } while (*(int *)(iVar5 + 0xc) << 0xf < 0);
      iVar2 = FUN_08014c54(param_1);
    } while (iVar2 == 0);
    *(uint *)(iVar5 + 0x10) = *(uint *)(iVar5 + 0x10) & 0xfffffffe;
    *(undefined1 *)(param_1 + 4) = 2;
  }
  return iVar2;
}

