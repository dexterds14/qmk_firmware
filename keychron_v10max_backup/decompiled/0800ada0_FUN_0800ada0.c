// FUN_0800ada0 @ 0x0800ada0  size=78  body=[[0800ada0, 0800aded]]

void FUN_0800ada0(uint param_1,char param_2)

{
  byte local_50 [3];
  undefined1 local_4d;
  
  FUN_08008798(local_50,0,0x40);
  local_50[0] = 0x84;
  local_50[1] = 0x7f;
  local_4d = 0x80;
  FUN_08014120(&DAT_20004b50,&DAT_08016714);
  FUN_0801415e(0x20004b50);
  FUN_080141bc(&DAT_20004b50,(uint)(byte)(param_2 + 4),(uint)local_50,param_1);
  FUN_0801417a(0x20004b50);
  FUN_08014142(&DAT_20004b50);
  return;
}

