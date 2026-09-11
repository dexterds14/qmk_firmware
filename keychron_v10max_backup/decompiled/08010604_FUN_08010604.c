// FUN_08010604 @ 0x08010604  size=284  body=[[08010604, 0801071f]]

bool FUN_08010604(uint param_1,char *param_2,undefined *param_3)

{
  short sVar1;
  uint uVar2;
  uint uVar3;
  uint uVar4;
  uint uVar5;
  short sVar6;
  uint uVar7;
  undefined1 *puVar8;
  uint uVar9;
  byte *pbVar10;
  uint uVar11;
  undefined4 local_30;
  
  uVar2 = FUN_0801017e(*param_2);
  uVar7 = (uint)DAT_20004814;
  uVar9 = uVar2 & 0xff;
  puVar8 = &DAT_20000d07 + uVar9 * 2;
  uVar2 = (uVar2 & 0xffff) >> 8;
  for (; (uVar9 & 0xff) < uVar2; uVar9 = uVar9 + 1) {
    if (((&DAT_20000e23)[uVar9] & param_2[1]) != 0) {
      memcpy(&local_30,(undefined4 *)&DAT_20004809,3);
      uVar5 = 0;
      pbVar10 = &DAT_20004814 + param_1;
      for (uVar3 = param_1; (uVar3 & 0xff) < uVar7; uVar3 = uVar3 + 1) {
        sVar1 = (ushort)(byte)puVar8[0x6c] - (ushort)pbVar10[1];
        sVar6 = (ushort)(byte)puVar8[0x6d] - (ushort)pbVar10[9];
        uVar4 = FUN_0800f7aa((uint)(ushort)(sVar1 * sVar1 + sVar6 * sVar6));
        uVar11 = DAT_2000480c + 1;
        local_30._0_3_ = CONCAT12((char)uVar5,(undefined2)local_30);
        if (0xfe < uVar11) {
          uVar11 = 0xff;
        }
        uVar5 = (*(code *)param_3)(local_30,(int)sVar1,(int)sVar6,uVar4,
                                   (*(ushort *)(&DAT_20004815 + (uVar3 + 0xc) * 2) * uVar11 &
                                   0xffffff) >> 8);
        local_30._0_2_ = (undefined2)uVar5;
        uVar5 = (uVar5 & 0xffffff) >> 0x10;
        pbVar10 = pbVar10 + 1;
      }
      local_30._0_3_ =
           CONCAT12((char)((uint)((int)(short)(ushort)DAT_2000480b * (int)(short)uVar5) >> 8),
                    (undefined2)local_30);
      uVar3 = FUN_0800fd30(local_30);
      FUN_0800fe78(uVar9,(char)(uVar3 >> 8),(char)uVar3,(char)(uVar3 >> 0x10));
    }
    puVar8 = puVar8 + 2;
  }
  return uVar2 < 0x58;
}

