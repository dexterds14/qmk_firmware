// FUN_08014478 @ 0x08014478  size=700  body=[[08014478, 08014733]]

void FUN_08014478(char *param_1,int param_2)

{
  byte bVar1;
  bool bVar2;
  undefined4 *puVar3;
  ushort uVar4;
  uint uVar5;
  undefined4 uVar6;
  undefined *puVar7;
  uint uVar8;
  int iVar9;
  
  if (param_1[0x34] != '\0') {
    param_1[0x34] = '\0';
  }
  FUN_08015882((int)param_1,param_2,(undefined4 *)(param_1 + 0x44));
  if ((*(code **)(*(int *)(param_1 + 4) + 8) == (code *)0x0) ||
     (iVar9 = (**(code **)(*(int *)(param_1 + 4) + 8))(param_1), iVar9 == 0)) {
    bVar1 = param_1[0x44];
    uVar8 = bVar1 & 0x60;
    if ((bVar1 & 0x60) != 0) {
LAB_080144a2:
      FUN_08015e38((int)param_1,0);
      FUN_08015e24((int)param_1,0);
      if ((code *)**(undefined4 **)(param_1 + 4) != (code *)0x0) {
        (*(code *)**(undefined4 **)(param_1 + 4))(param_1,6);
      }
      param_1[0x34] = '\x06';
      return;
    }
    uVar5 = bVar1 & 0x7f | (uint)(byte)param_1[0x45] << 8;
    if (uVar5 == 0x302) {
      if (param_1[0x46] != '\0') goto LAB_080144a2;
      bVar1 = param_1[0x48];
      uVar8 = bVar1 & 0xf;
      if ((bVar1 & 0xf) != 0) {
        if ((int)((uint)bVar1 << 0x18) < 0) {
          FUN_08015e38((int)param_1,uVar8);
        }
        else {
          FUN_08015e24((int)param_1,uVar8);
        }
      }
      goto LAB_08014616;
    }
    if (uVar5 < 0x303) {
      if (uVar5 == 0x100) {
        if (param_1[0x46] != '\x01') goto LAB_080144a2;
        uVar4 = *(ushort *)(param_1 + 0x4c) & 0xfffd;
      }
      else {
        if (uVar5 < 0x101) {
          if (uVar5 == 1) {
LAB_080145c4:
            puVar7 = &DAT_08017380;
          }
          else {
            if (uVar5 != 2) {
              if (uVar5 != 0) goto LAB_080144a2;
              *(char **)(param_1 + 0x38) = param_1 + 0x4c;
              param_1[0x3c] = '\x02';
              param_1[0x3d] = '\0';
              param_1[0x3e] = '\0';
              param_1[0x3f] = '\0';
              goto LAB_0801454e;
            }
            uVar8 = (byte)param_1[0x48] & 0xf;
            if ((int)((uint)(byte)param_1[0x48] << 0x18) < 0) {
              iVar9 = FUN_08015868((int)param_1,uVar8);
            }
            else {
              iVar9 = FUN_0801584e((int)param_1,uVar8);
            }
            if (iVar9 == 1) {
              puVar7 = &DAT_0801737c;
            }
            else {
              if (iVar9 != 2) goto LAB_080144a2;
              puVar7 = &DAT_0801737e;
            }
          }
          *(undefined **)(param_1 + 0x38) = puVar7;
          param_1[0x3c] = '\x02';
          param_1[0x3d] = '\0';
          param_1[0x3e] = '\0';
          param_1[0x3f] = '\0';
          goto LAB_0801454e;
        }
        if (uVar5 == 0x102) {
          if (param_1[0x46] != '\0') goto LAB_080144a2;
          bVar1 = param_1[0x48];
          uVar8 = bVar1 & 0xf;
          if ((bVar1 & 0xf) != 0) {
            if ((int)((uint)bVar1 << 0x18) < 0) {
              FUN_08015e60((int)param_1,uVar8);
            }
            else {
              FUN_08015e4c((int)param_1,uVar8);
            }
          }
          goto LAB_08014616;
        }
        if ((uVar5 != 0x300) || (param_1[0x46] != '\x01')) goto LAB_080144a2;
        uVar4 = *(ushort *)(param_1 + 0x4c) | 2;
      }
      *(ushort *)(param_1 + 0x4c) = uVar4;
      *(uint *)(param_1 + 0x38) = uVar8;
      *(uint *)(param_1 + 0x3c) = uVar8;
    }
    else {
      if (uVar5 != 0x800) {
        if (uVar5 < 0x801) {
          if (uVar5 != 0x500) {
            if ((1 < uVar5 - 0x600) ||
               (puVar3 = (undefined4 *)
                         (**(code **)(*(int *)(param_1 + 4) + 4))
                                   (param_1,param_1[0x47],param_1[0x46],
                                    *(undefined2 *)(param_1 + 0x48)), puVar3 == (undefined4 *)0x0))
            goto LAB_080144a2;
            *(undefined4 *)(param_1 + 0x38) = puVar3[1];
            uVar6 = *puVar3;
            goto LAB_080145b0;
          }
          if (*(short *)(param_1 + 0x44) == 0x500) {
            param_1[0x4e] = param_1[0x46];
            FUN_08015718((int)param_1);
            if ((code *)**(undefined4 **)(param_1 + 4) != (code *)0x0) {
              (*(code *)**(undefined4 **)(param_1 + 4))(param_1,1);
            }
            *param_1 = '\x03';
          }
        }
        else {
          if (uVar5 != 0x900) {
            if (uVar5 != 0xc02) goto LAB_080144a2;
            goto LAB_080145c4;
          }
          if (*param_1 == '\x04') {
            bVar2 = (bool)isCurrentModePrivileged();
            if (bVar2) {
              setBasePriority(0x30);
            }
            FUN_080142c6((int)param_1);
            bVar2 = (bool)isCurrentModePrivileged();
            if (bVar2) {
              setBasePriority(uVar8);
            }
            param_1[0x4f] = (char)uVar8;
            *param_1 = '\x03';
            if ((code *)**(undefined4 **)(param_1 + 4) != (code *)0x0) {
              (*(code *)**(undefined4 **)(param_1 + 4))(param_1);
            }
          }
          if (param_1[0x46] != '\0') {
            param_1[0x4f] = param_1[0x46];
            *param_1 = '\x04';
            if ((code *)**(undefined4 **)(param_1 + 4) != (code *)0x0) {
              (*(code *)**(undefined4 **)(param_1 + 4))(param_1,2);
            }
          }
        }
LAB_08014616:
        param_1[0x38] = '\0';
        param_1[0x39] = '\0';
        param_1[0x3a] = '\0';
        param_1[0x3b] = '\0';
        param_1[0x3c] = '\0';
        param_1[0x3d] = '\0';
        param_1[0x3e] = '\0';
        param_1[0x3f] = '\0';
LAB_0801454e:
        param_1[0x40] = '\0';
        param_1[0x41] = '\0';
        param_1[0x42] = '\0';
        param_1[0x43] = '\0';
        goto LAB_080144ce;
      }
      *(char **)(param_1 + 0x38) = param_1 + 0x4f;
      uVar6 = 1;
LAB_080145b0:
      *(undefined4 *)(param_1 + 0x3c) = uVar6;
    }
    *(uint *)(param_1 + 0x40) = uVar8;
  }
LAB_080144ce:
  if ((uint)*(ushort *)(param_1 + 0x4a) < *(uint *)(param_1 + 0x3c)) {
    *(uint *)(param_1 + 0x3c) = (uint)*(ushort *)(param_1 + 0x4a);
  }
  iVar9 = *(int *)(param_1 + 0x3c);
  if (param_1[0x44] < '\0') {
    if (iVar9 == 0) {
      param_1[0x34] = '\x14';
      bVar2 = (bool)isCurrentModePrivileged();
      if (bVar2) {
        setBasePriority(0x30);
      }
      FUN_08014310((int)param_1,0,0,0);
LAB_080146fc:
      bVar2 = (bool)isCurrentModePrivileged();
      if (!bVar2) {
        return;
      }
      setBasePriority(iVar9);
      return;
    }
    param_1[0x34] = '\t';
    bVar2 = (bool)isCurrentModePrivileged();
    if (bVar2) {
      setBasePriority(0x30);
    }
    FUN_08014334((int)param_1,0,*(undefined4 *)(param_1 + 0x38),*(undefined4 *)(param_1 + 0x3c));
  }
  else {
    if (iVar9 == 0) {
      param_1[0x34] = '\v';
      bVar2 = (bool)isCurrentModePrivileged();
      if (bVar2) {
        setBasePriority(0x30);
      }
      FUN_08014334((int)param_1,0,0,0);
      goto LAB_080146fc;
    }
    param_1[0x34] = '\x15';
    bVar2 = (bool)isCurrentModePrivileged();
    if (bVar2) {
      setBasePriority(0x30);
    }
    FUN_08014310((int)param_1,0,*(undefined4 *)(param_1 + 0x38),*(undefined4 *)(param_1 + 0x3c));
  }
  bVar2 = (bool)isCurrentModePrivileged();
  if (bVar2) {
    setBasePriority(0);
  }
  return;
}

