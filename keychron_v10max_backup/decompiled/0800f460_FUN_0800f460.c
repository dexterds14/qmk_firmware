// FUN_0800f460 @ 0x0800f460  size=240  body=[[0800f460, 0800f54f]]

int FUN_0800f460(undefined4 param_1,uint param_2,uint param_3,uint param_4)

{
  char cVar1;
  int iVar2;
  uint extraout_r1;
  uint uVar3;
  uint extraout_r1_00;
  uint extraout_r1_01;
  uint extraout_r2;
  uint uVar4;
  uint extraout_r2_00;
  uint extraout_r2_01;
  uint extraout_r3;
  uint uVar5;
  uint extraout_r3_00;
  uint extraout_r3_01;
  uint uVar6;
  uint uVar7;
  uint uVar8;
  uint uVar9;
  longlong lVar10;
  uint local_24;
  undefined1 local_20 [4];
  uint uStack_1c;
  
  local_24 = param_2;
  local_20 = (undefined1  [4])param_3;
  uStack_1c = param_4;
  FUN_0800f1e0();
  iVar2 = FUN_0800f5f4();
  if (iVar2 != 0) {
    cVar1 = FUN_0800f29c(0,0x20001704,0x200);
    if (cVar1 != '\0') {
      lVar10 = FUN_080115f0(0x20001704,0x800);
      FUN_0800f29c(0x800,(int)local_20,2);
      if (lVar10 != CONCAT44(uStack_1c,local_20)) {
        FUN_0800f1e0();
      }
      uVar6 = 0x808;
      do {
        cVar1 = FUN_0800f67c(uVar6,&local_24);
        iVar2 = 0;
        uVar3 = extraout_r1;
        uVar4 = extraout_r2;
        uVar5 = extraout_r3;
        uVar8 = uVar6;
        if (cVar1 == '\0') goto LAB_0800f524;
        uVar5 = local_24;
        if (local_24 == 0) break;
        uVar8 = uVar6 + 4;
        local_20 = (undefined1  [4])local_24;
        uVar3 = local_24 & 0xff;
        if ((local_24 & 0xc0) != 0) {
LAB_0800f54a:
          iVar2 = 0;
          goto LAB_0800f524;
        }
        uVar4 = local_24 & 0xff00;
        uVar7 = (local_24 & 7) << 0x10 | (local_24 & 0xffffff) >> 0x10 | uVar4;
        uVar5 = uVar7 + (uVar3 >> 3);
        uVar9 = uVar3 >> 3;
        if (0x800 < uVar5) goto LAB_0800f54a;
        if ((local_24 & 0x30) != 0) {
          cVar1 = FUN_0800f67c(uVar8,&uStack_1c);
          uVar3 = extraout_r1_00;
          uVar4 = extraout_r2_00;
          uVar5 = extraout_r3_00;
          if (cVar1 == '\0') goto LAB_0800f54a;
          uVar8 = uVar6 + 8;
        }
        memcpy((undefined4 *)(&DAT_20001704 + uVar7),(undefined4 *)(local_20 + 3),uVar9);
        uVar3 = extraout_r1_01;
        uVar4 = extraout_r2_01;
        uVar5 = extraout_r3_01;
        uVar6 = uVar8;
      } while (uVar8 < 0x1000);
      iVar2 = 1;
LAB_0800f524:
      DAT_20001f04 = uVar8;
      if (iVar2 == 0) {
        cVar1 = FUN_0800f2e8(0,uVar3,uVar4,uVar5);
        iVar2 = (int)cVar1;
      }
      else {
        iVar2 = FUN_0800f354(iVar2,uVar3,uVar4);
      }
      if (iVar2 != 0) {
        return iVar2;
      }
      FUN_0800f1e0();
      return 0;
    }
    FUN_0800f1e0();
  }
  FUN_0800f1e0();
  return 0;
}

