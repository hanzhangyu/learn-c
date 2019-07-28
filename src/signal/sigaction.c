/**
 * @file POSIX捕捉信号
 * @usage 
 */
#include <stdio.h>
#include <signal.h>
#include <unistd.h>

void sigHandler(int num) {
  printf("receive signal %d\n", num);
  sleep(5); // 信号吹了过程中，默认会阻塞当前信号
  puts("handler resolved"); // 前32位最多存两份，block与pend各一份
}

int main(void) {
  struct sigaction action;
  action.sa_handler = sigHandler; // 还可以设置为 SIG_IGN SIG_DFL
  sigemptyset(&action.sa_mask); // 移除默认的sigset_t值
  sigaddset(&action.sa_mask, SIGTERM); // 处理handler时生效，后续从stdin中读取出来被消费
  action.sa_flags = 0;

  sigaction(SIGINT, &action, NULL);

  for (int i = 0; i < 100; ++i) {
    puts("======================");
    sleep(1);
  }
  return 0;
}