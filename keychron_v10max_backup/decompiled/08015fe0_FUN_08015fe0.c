// FUN_08015fe0 @ 0x08015fe0  size=106  body=[[08015fe0, 08016049]]

void FUN_08015fe0(void)

{
  undefined *puVar1;
  undefined *extraout_r1;
  uint uVar2;
  
  FUN_080140f8((undefined4 *)&DAT_20004b44);
  puVar1 = &DAT_40002800;
  DAT_20004b48 = &DAT_40002800;
  DAT_40002824 = 0xca;
  DAT_40002824 = 0x53;
  uVar2 = DAT_4000280c;
  if ((uVar2 & 0x10) == 0) {
    FUN_08015e74();
    *(undefined4 *)(extraout_r1 + 8) = 0;
    *(undefined4 *)(extraout_r1 + 0x40) = 0;
    *(undefined4 *)(extraout_r1 + 0xc) = 0x80;
    *(undefined4 *)(extraout_r1 + 0x10) = 0x1f03ff;
    *(undefined4 *)(extraout_r1 + 0x10) = 0x1f03ff;
    uVar2 = *(uint *)(extraout_r1 + 0xc) & 0xffffff7f;
    puVar1 = extraout_r1;
  }
  else {
    uVar2 = DAT_4000280c;
    uVar2 = uVar2 & 0xffffffdf;
  }
  *(uint *)(puVar1 + 0xc) = uVar2;
  DAT_20004b4c = 0;
  FUN_080152b0(0x620000,1);
  FUN_0801486a(2,'\x0f');
  FUN_0801486a(3,'\x0f');
  FUN_0801486a(0x29,'\x0f');
  return;
}

