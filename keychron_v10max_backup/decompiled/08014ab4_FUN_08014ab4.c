// FUN_08014ab4 @ 0x08014ab4  size=228  body=[[08014a6e, 08014b51]]

void FUN_08014ab4(void)

{
  uint uVar1;
  undefined4 uVar2;
  int iVar3;
  
  uVar1 = DAT_40023810;
  DAT_40023810 = uVar1 | 0xffffff60;
  uVar1 = DAT_40023810;
  DAT_40023810 = uVar1 & 0x9f;
  uVar2 = DAT_40023810;
  uVar2 = DAT_40023814;
  DAT_40023814 = 0xffffffff;
  uVar2 = DAT_40023814;
  DAT_40023814 = 0;
  uVar2 = DAT_40023814;
  uVar1 = DAT_40023820;
  DAT_40023820 = uVar1 | 0xefffffff;
  uVar1 = DAT_40023820;
  DAT_40023820 = uVar1 & 0x10000000;
  uVar2 = DAT_40023820;
  uVar2 = DAT_40023824;
  DAT_40023824 = 0xffffffff;
  uVar2 = DAT_40023824;
  DAT_40023824 = 0;
  uVar2 = DAT_40023824;
  uVar1 = DAT_40023840;
  DAT_40023840 = uVar1 | 0x10000000;
  uVar1 = DAT_40023860;
  DAT_40023860 = uVar1 | 0x10000000;
  uVar2 = DAT_40023860;
  uVar1 = DAT_40007000;
  DAT_40007000 = uVar1 | 0x100;
  uVar1 = DAT_40023870;
  if ((uVar1 & 0x300) != 0x200) {
    DAT_40023870 = 0x10000;
    DAT_40023870 = 0;
  }
  iVar3 = DAT_40023870;
  if (-1 < iVar3 << 0x10) {
    uVar1 = DAT_40023870;
    DAT_40023870 = uVar1 | 0x200;
    uVar1 = DAT_40023870;
    DAT_40023870 = uVar1 | 0x8000;
  }
  uVar1 = DAT_40007004;
  DAT_40007004 = uVar1 & 0xfffffdff;
  FUN_08015164();
  FUN_0801486a(6,'\x06');
  FUN_0801486a(7,'\x06');
  FUN_0801486a(8,'\x06');
  FUN_0801486a(9,'\x06');
  FUN_0801486a(10,'\x06');
  FUN_0801486a(0x17,'\x06');
  FUN_0801486a(0x28,'\x06');
  FUN_0801486a(0x1c,'\a');
  return;
}

