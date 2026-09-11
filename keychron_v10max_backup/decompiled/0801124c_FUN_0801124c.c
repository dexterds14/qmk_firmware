// FUN_0801124c @ 0x0801124c  size=226  body=[[0801124c, 0801132d]]

void FUN_0801124c(uint param_1)

{
  undefined4 auStack_f4 [3];
  byte abStack_e8 [24];
  byte abStack_d0 [192];
  
  FUN_08015338((uint *)(*(uint *)(&DAT_20000eb8 + param_1 * 4) & 0xfffffff0),
               1 << (*(uint *)(&DAT_20000eb8 + param_1 * 4) & 0xf),1);
  *(short *)((*(uint *)(&DAT_20000eb8 + param_1 * 4) & 0xfffffff0) + 0x18) =
       (short)(1 << (*(uint *)(&DAT_20000eb8 + param_1 * 4) & 0xf));
  FUN_08011200(param_1,3,0);
  FUN_08011200(param_1,3,0x13);
  FUN_08011200(param_1,3,0x14);
  FUN_08011200(param_1,3,0x15);
  FUN_08011200(param_1,3,0x16);
  FUN_08011200(param_1,3,0x1a);
  FUN_08008798(abStack_e8,0,0x18);
  FUN_080111a0(param_1,0,0,(uint)abStack_e8,0x18);
  FUN_08008798(abStack_d0,0,0xc0);
  FUN_080111a0(param_1,1,0,(uint)abStack_d0,0xc0);
  memcpy(auStack_f4,(undefined4 *)"            ",0xc);
  FUN_080111a0(param_1,4,0,(uint)auStack_f4,0xc);
  FUN_08011200(param_1,3,0);
  return;
}

