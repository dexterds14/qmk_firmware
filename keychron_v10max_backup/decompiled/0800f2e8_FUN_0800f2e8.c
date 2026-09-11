// FUN_0800f2e8 @ 0x0800f2e8  size=92  body=[[0800f2e8, 0800f343]]

char FUN_0800f2e8(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  char cVar1;
  bool bVar2;
  int iVar3;
  char cVar4;
  undefined8 local_18;
  
  local_18._0_4_ = param_1;
  local_18._4_4_ = param_2;
  iVar3 = FUN_0800f574(param_1,param_2,param_3,param_4);
  cVar4 = '\0';
  if (iVar3 != 0) {
    cVar1 = FUN_0800f200();
    bVar2 = FUN_0800f2c2(0,0x20001704,0x200);
    cVar4 = '\0';
    if (bVar2) {
      local_18 = FUN_080115f0(0x20001704,0x800);
      bVar2 = FUN_0800f2c2(0x800,(int)&local_18,2);
      cVar4 = bVar2 << 1;
    }
    if (cVar1 == '\x01') {
      FUN_0800f220();
    }
    DAT_20001f04 = 0x808;
  }
  return cVar4;
}

