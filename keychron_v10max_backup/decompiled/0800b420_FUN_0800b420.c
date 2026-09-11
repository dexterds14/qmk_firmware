// FUN_0800b420 @ 0x0800b420  size=102  body=[[0800b420, 0800b485]]

void FUN_0800b420(uint param_1,uint param_2,undefined4 param_3)

{
  uint uVar1;
  byte bVar2;
  uint uVar3;
  uint extraout_r1;
  undefined4 extraout_r2;
  
  if (param_1 == 0) {
    DAT_20001560 = '\0';
    DAT_2000155c = param_1;
    FUN_0800b378();
    bVar2 = FUN_08010cf4();
    if (bVar2 == 0) {
      FUN_08010cd4();
      return;
    }
  }
  else {
    uVar3 = FUN_0800c48c(param_1,param_2,param_3);
    uVar1 = DAT_2000155c;
    if ((uVar3 < DAT_2000155c) && (uVar1 = uVar3, DAT_20001560 != '\0')) {
      uVar1 = DAT_2000155c + uVar3;
    }
    DAT_2000155c = uVar1;
    if (((DAT_2000155c == 0) || (30000 < uVar3 - DAT_2000155c)) && (DAT_20001560 == '\0')) {
      DAT_20001564 = FUN_08012508();
      DAT_2000155c = FUN_0800c48c(DAT_20001564,extraout_r1,extraout_r2);
      DAT_20001560 = 1;
      FUN_0800b354();
      return;
    }
  }
  return;
}

