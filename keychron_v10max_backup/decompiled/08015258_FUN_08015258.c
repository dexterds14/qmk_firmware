// FUN_08015258 @ 0x08015258  size=78  body=[[08015258, 080152a5]]

void FUN_08015258(int param_1)

{
  uint uVar1;
  undefined4 uVar2;
  
  FUN_08014896((uint)*(byte *)(param_1 + 0xb));
  DAT_200024d0 = DAT_200024d0 & ~(1 << *(sbyte *)(param_1 + 10));
  if ((DAT_200024d0 & 0xff) == 0) {
    uVar1 = DAT_40023830;
    DAT_40023830 = uVar1 & 0xffdfffff;
    uVar1 = DAT_40023850;
    DAT_40023850 = uVar1 & 0xffdfffff;
    uVar2 = DAT_40023850;
  }
  if ((DAT_200024d0 & 0xff00) == 0) {
    uVar1 = DAT_40023830;
    DAT_40023830 = uVar1 & 0xffbfffff;
    uVar1 = DAT_40023850;
    DAT_40023850 = uVar1 & 0xffbfffff;
    uVar2 = DAT_40023850;
  }
  return;
}

