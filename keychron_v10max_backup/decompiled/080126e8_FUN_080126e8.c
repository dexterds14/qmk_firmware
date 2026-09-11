// FUN_080126e8 @ 0x080126e8  size=208  body=[[080126e8, 080127b7]]

undefined1 FUN_080126e8(uint param_1,short param_2,int param_3,uint param_4)

{
  undefined1 uVar1;
  uint uVar2;
  
  if (DAT_20002058 == '\0') {
    uVar1 = 0;
    if (param_1 != 0xffffffff) {
      for (uVar2 = 2; uVar2 < param_4; uVar2 = (uVar2 & 0x7fff) << 1) {
      }
      if (uVar2 - 2 < 0xff) {
        DAT_20002054 = param_2 << 7;
        if (param_3 == 2) {
          DAT_20002054 = DAT_20002054 | 2;
        }
        else if (param_3 == 3) {
          DAT_20002054 = DAT_20002054 | 3;
        }
        else if (param_3 == 1) {
          DAT_20002054 = DAT_20002054 | 1;
        }
        if (uVar2 == 0x20) {
          DAT_20002054 = DAT_20002054 | 0x20;
        }
        else if (uVar2 < 0x21) {
          if (uVar2 == 8) {
            DAT_20002054 = DAT_20002054 | 0x10;
          }
          else if (uVar2 == 0x10) {
            DAT_20002054 = DAT_20002054 | 0x18;
          }
          else if (uVar2 == 4) {
            DAT_20002054 = DAT_20002054 | 8;
          }
        }
        else if (uVar2 == 0x80) {
          DAT_20002054 = DAT_20002054 | 0x30;
        }
        else if (uVar2 == 0x100) {
          DAT_20002054 = DAT_20002054 | 0x38;
        }
        else if (uVar2 == 0x40) {
          DAT_20002054 = DAT_20002054 | 0x28;
        }
        DAT_20002050 = param_1 & 0xf;
        DAT_2000204c = (uint *)(param_1 & 0xfffffff0);
        DAT_20002058 = '\x01';
        FUN_08015338(DAT_2000204c,1 << DAT_20002050,1);
        FUN_08014120(&DAT_20004b50,&DAT_20002040);
        FUN_0801415e(0x20004b50);
        uVar1 = 1;
      }
    }
  }
  else {
    uVar1 = 0;
  }
  return uVar1;
}

