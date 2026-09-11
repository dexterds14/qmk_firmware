// FUN_0800a09c @ 0x0800a09c  size=78  body=[[0800a09c, 0800a0e9]]

undefined4 FUN_0800a09c(undefined4 param_1,int param_2,undefined4 *param_3,uint *param_4)

{
  int iVar1;
  undefined4 uVar2;
  uint uVar3;
  byte abStack_68 [4];
  uint local_64;
  
  if ((*(short *)(param_2 + 0xe) < 0) ||
     (iVar1 = FUN_080166be(param_1,(int)*(short *)(param_2 + 0xe),abStack_68), iVar1 < 0)) {
    uVar3 = 0;
    if ((*(ushort *)(param_2 + 0xc) & 0x80) == 0) {
      uVar2 = 0x400;
    }
    else {
      uVar2 = 0x40;
    }
  }
  else {
    uVar2 = 0x400;
    uVar3 = (uint)((local_64 & 0xf000) == 0x2000);
  }
  *param_4 = uVar3;
  *param_3 = uVar2;
  return 0;
}

