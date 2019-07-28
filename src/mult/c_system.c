/**
 * @file 查看system子进程
 * @usage
 * $ ./a.out
 * $ ps ajx
 */
#include <stdlib.h>

int main(void) {
  system("sleep 10");
  return 0;
}