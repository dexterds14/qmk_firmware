// FUN_08010378 @ 0x08010378  size=138  body=[[08010378, 08010401]]

bool FUN_08010378(char *param_1,undefined4 param_2,undefined4 param_3,uint param_4)

{
  byte bVar1;
  undefined3 uVar2;
  uint uVar3;
  uint uVar4;
  code *extraout_r1;
  uint uVar5;
  uint uVar6;
  char *pcVar7;
  
  pcVar7 = param_1;
  uVar3 = FUN_0801017e(*param_1);
  uVar5 = (uint)(ushort)DAT_20004810;
  bVar1 = DAT_2000480c >> 2;
  uVar6 = (uVar3 & 0xffff) >> 8;
  for (uVar3 = uVar3 & 0xff; (uVar3 & 0xff) < uVar6; uVar3 = uVar3 + 1) {
    if (((&DAT_20000e23)[uVar3] & param_1[1]) != 0) {
      uVar2 = (*extraout_r1)((uint)CONCAT12(DAT_2000480b,CONCAT11(DAT_2000480a,DAT_20004809)),
                             uVar3 & 0xff,(bVar1 * uVar5 + uVar5 & 0xffff) >> 8,
                             CONCAT11(DAT_2000480a,DAT_20004809),pcVar7,param_2,param_3,param_4);
      param_4 = CONCAT13((char)(param_4 >> 0x18),uVar2);
      uVar4 = FUN_0800fd30(param_4);
      FUN_0800fe78(uVar3,(char)(uVar4 >> 8),(char)uVar4,(char)(uVar4 >> 0x10));
    }
  }
  return uVar6 < 0x58;
}

