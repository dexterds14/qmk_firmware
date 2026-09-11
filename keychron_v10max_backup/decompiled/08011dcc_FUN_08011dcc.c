// FUN_08011dcc @ 0x08011dcc  size=34  body=[[08011dcc, 08011ded]]

bool FUN_08011dcc(int param_1)

{
  if (((*(char *)(param_1 + 2) == '\0') && (*(char *)(param_1 + 3) == '\0')) &&
     (*(char *)(param_1 + 4) == '\0')) {
    return *(char *)(param_1 + 5) != '\0';
  }
  return true;
}

