// FUN_0800aa64 @ 0x0800aa64  size=200  body=[[0800aa64, 0800ab2b]]

void FUN_0800aa64(byte *param_1,uint param_2,char param_3,int param_4)

{
  byte *pbVar1;
  uint uVar2;
  byte local_58 [4];
  undefined1 local_54;
  char local_53;
  char local_52;
  char local_51;
  char local_50;
  undefined4 auStack_4f [14];
  
  FUN_08008798(local_58,0,0x40);
  if (param_4 == 0) {
    DAT_20001512 = DAT_20001512 + '\x01';
  }
  if (DAT_20001512 == '\0') {
    DAT_20001512 = '\x01';
  }
  uVar2 = 0;
  for (pbVar1 = param_1; pbVar1 != param_1 + param_2; pbVar1 = pbVar1 + 1) {
    uVar2 = *pbVar1 + uVar2 & 0xffff;
  }
  local_58[0] = 0x84;
  local_58[1] = 0x7e;
  local_54 = 0xaa;
  local_52 = (char)param_2 + '\x02';
  local_51 = -3 - (char)param_2;
  local_50 = DAT_20001512;
  local_53 = param_3 + 'U';
  memcpy(auStack_4f,(undefined4 *)param_1,param_2);
  local_58[param_2 + 9 & 0xff] = (byte)uVar2;
  local_58[param_2 + 10 & 0xff] = (byte)(uVar2 >> 8);
  DAT_20000ca2 = 0x40;
  FUN_08014120(&DAT_20004b50,&DAT_08016714);
  FUN_0801415e(0x20004b50);
  FUN_080141de(&DAT_20004b50,param_2 + 0xb & 0xff,(uint)local_58);
  *(short *)(*(int *)(DAT_20004b54 + 0xc) + 0x18) =
       (short)(1 << (*(uint *)(DAT_20004b54 + 0x10) & 0xff));
  FUN_08014142(&DAT_20004b50);
  return;
}

