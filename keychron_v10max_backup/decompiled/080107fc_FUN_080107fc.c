// FUN_080107fc @ 0x080107fc  size=166  body=[[080107fc, 080108a1]]

bool FUN_080107fc(char *param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  byte bVar1;
  uint uVar2;
  int iVar3;
  uint uVar4;
  uint uVar5;
  undefined4 local_20;
  undefined4 local_1c;
  
  local_20 = param_3;
  local_1c = param_4;
  uVar2 = FUN_0801017e(*param_1);
  uVar5 = uVar2 & 0xff;
  uVar4 = (uVar2 & 0xffff) >> 8;
  memcpy(&local_20,(undefined4 *)&DAT_20004809,3);
  bVar1 = DAT_2000480b;
  uVar2 = FUN_0800f81c(((uint)(DAT_2000480c >> 3) * (uint)(ushort)DAT_20004810 & 0xffff) >> 8);
  iVar3 = (int)(char)((char)uVar2 + -0x80);
  if (iVar3 < 0) {
    iVar3 = (int)(char)(-0x80 - (char)uVar2);
  }
  local_20._0_3_ =
       CONCAT12((char)((uint)((int)(short)((ushort)(iVar3 << 1) & 0xff) * (int)(short)(ushort)bVar1)
                      >> 8),(undefined2)local_20);
  uVar2 = FUN_0800fd30(local_20);
  local_1c._0_3_ = (undefined3)uVar2;
  for (; (uVar5 & 0xff) < uVar4; uVar5 = uVar5 + 1) {
    if (((&DAT_20000e23)[uVar5] & param_1[1]) != 0) {
      FUN_0800fe78(uVar5,local_1c._1_1_,(undefined1)local_1c,local_1c._2_1_);
    }
  }
  return uVar4 < 0x58;
}

