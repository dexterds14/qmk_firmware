// FUN_080123bc @ 0x080123bc  size=72  body=[[080123bc, 08012403]]

bool FUN_080123bc(int param_1,int param_2)

{
  bool bVar1;
  
  if ((((*(char *)(param_1 + 1) == *(char *)(param_2 + 1)) &&
       ((*(char *)(param_1 + 2) == '\0' || (*(char *)(param_2 + 2) == *(char *)(param_1 + 2))))) &&
      ((*(char *)(param_1 + 3) == '\0' || (*(char *)(param_2 + 3) == *(char *)(param_1 + 3))))) &&
     ((*(char *)(param_1 + 5) == '\0' || (*(char *)(param_2 + 5) == *(char *)(param_1 + 5))))) {
    bVar1 = false;
    if (*(char *)(param_1 + 4) != '\0') {
      return *(char *)(param_2 + 4) != *(char *)(param_1 + 4);
    }
  }
  else {
    bVar1 = true;
  }
  return bVar1;
}

