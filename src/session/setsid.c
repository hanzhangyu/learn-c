/**
 * @file 父进程直接退出，子进程 setsid 脱离当前会话，tty变为？符号
 * @usage
 * $ ps ajx
 *     1  6931  6930   601 pts/0        0 S     1000   0:00 ./a.out
 * $ ps ajx # 10秒后
 *     1  6931  6931  6931(新的sid==pid) ?(变为没有终端)            0 Ss    1000   0:00 ./a.out
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(void) {
  pid_t pid;

  if ((pid = fork()) < 0) {
    perror("fork");
    exit(1);
  } else if (pid > 0) {
    return 0; // 父进程直接退出
  }
  printf(
    "child pid: %d, pgid: %d, sid: %d\n",
    getpid(), getpgid(0), getsid(0)
  );
  sleep(10);
  setsid(); // 子进程脱离当前会话
  printf(
    "changed child pid: %d, pgid: %d, sid: %d\n",
    getpid(), getpgid(0), getsid(0)
  );
  sleep(20);
  return 0;
}