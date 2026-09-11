// FUN_08010788 @ 0x08010788  size=106  body=[[08010788, 080107f1]]

bool FUN_08010788(char *param_1)

{
  uint uVar1;
  uint uVar2;
  uint uVar3;
  
  uVar1 = FUN_0801017e(*param_1);
  uVar3 = (uVar1 & 0xffff) >> 8;
  uVar2 = FUN_0800fd30((uint)CONCAT12(DAT_2000480b,CONCAT11(DAT_2000480a,DAT_20004809)));
  for (uVar1 = uVar1 & 0xff; (uVar1 & 0xff) < uVar3; uVar1 = uVar1 + 1) {
    if (((&DAT_20000e23)[uVar1] & param_1[1]) != 0) {
      FUN_0800fe78(uVar1,(char)(uVar2 >> 8),(char)uVar2,(char)(uVar2 >> 0x10));
    }
  }
  return uVar3 < 0x58;
}

