/**
 * @file 获取终端名称
 * @usage 
 */
#include <stdio.h>
#include <unistd.h>
int main()
{
  // 在GUI下就是pts/n
  printf("fd 0: %s\n", ttyname(0));
  printf("fd 1: %s\n", ttyname(1));
  printf("fd 2: %s\n", ttyname(2));
  return 0;
}