/**
 * @file POSIX注册信号集
 * @usage 
 */
#include <stdio.h>
#include <signal.h>
#include <unistd.h>

#define NORMAL_SIGNAL_LEN 32 // 只考虑前32位

void printSigset(const char *msg, const sigset_t *set) {
  printf("%s", msg);
  for (int i = 0; i < NORMAL_SIGNAL_LEN; ++i) {
    if (sigismember(set, i) == 1) {
      putchar('1');
    } else {
      putchar('0');
    }
  }
  putchar('\n');
}

void printSigsetInfo(const sigset_t *set) {
  printf("信号集初始结构\n    sizeof sigset_t %lu\n    ", sizeof(set)); // (1024 / (8 * sizeof (unsigned long int))) -> 128B
  for (int i = 0; i < 128; ++i) {
    printf("%lu", set->__val[i]);
  }
  putchar('\n');
}

int main(void) {
  sigset_t s, p;
  printSigsetInfo(&s);
  printSigset("初始sigset_t为 ", &s); // 可以看到室友默认设置的
  sigemptyset(&s); // 清空默认设置
  sigaddset(&s, SIGINT);
  sigprocmask(SIG_BLOCK, &s, NULL);
  for (int i = 0; i < 100; ++i) {
    sigpending(&p);
    if (i == 10) {
      sigprocmask(SIG_UNBLOCK, &s, NULL); // 100 &= ~100 移除设置的 2 信号
    }
    printSigset("该时刻Pending信号集为 ", &p);
    sleep(1);
  }
  return 0;
}
