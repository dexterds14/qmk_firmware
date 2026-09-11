// FUN_08015e74 @ 0x08015e74  size=20  body=[[08015e74, 08015e87]]

void FUN_08015e74(void)

{
  int iVar1;
  
  iVar1 = DAT_20004b48;
  *(uint *)(DAT_20004b48 + 0xc) = *(uint *)(DAT_20004b48 + 0xc) | 0x80;
  do {
  } while (-1 < *(int *)(iVar1 + 0xc) << 0x19);
  return;
}

