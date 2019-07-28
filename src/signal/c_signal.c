/**
 * @file 使用c标准库处理信号
 * @usage 
 */
#include <stdio.h>
#include <signal.h>
#include <unistd.h>

void sigHandler(int num) {
  printf("receive signal %d\n", num);
  sleep(5);
  puts("handler resolved");
}

int main(void) {
  signal(SIGINT, sigHandler);

  for (int i = 0; i < 100; ++i) {
    puts("======================");
    sleep(1);
  }
  return 0;
}