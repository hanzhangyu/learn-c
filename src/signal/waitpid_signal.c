/**
 * @file 使用信号回收子进程
 * @usage
 * $ ./a.out
 * $ 使用kill向子进程发送信号，去修改子进程状态
 */
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

#define CHILD_NUM 10

void sigChildHandler(int sig) {
  int status;
  pid_t pid;
  // 因为前32位信号时不会 sequence 的，所以可能一个信号抵达的时刻里面有多个子进程待回收
  while ((pid = waitpid(0, &status, WNOHANG)) > 0) {
    if (WIFEXITED(status)) {
      printf("child %d exit on %d\n ", pid, WEXITSTATUS(status));
    } else if(WIFSIGNALED(status)) {
      printf("child %d terminated by signal %d\n", pid, WTERMSIG(status));
    }
  }
}

int main(void) {
  pid_t pid;
  // TODO 阻塞 SIGCHILD 信号，防止 SIGCHILD 在注册 handler 之前触发，之后再恢复原mask
  int i;
  for (i = 0; i < CHILD_NUM; ++i) {
    if ((pid = fork()) == 0) {
      break;
    } else if (pid < 0) {
      perror("fork");
      exit(1);
    }
  }

  if (pid == 0) {
    for (int j = 0; j < 10; ++j) {
      printf("child id %d\n", getpid());
      sleep(1);
    }

    return i;
  }

  struct sigaction action;
  // 注册捕获handler
  action.sa_handler = sigChildHandler;
  sigemptyset(&action.sa_mask);
  action.sa_flags = 0;
  sigaction(SIGCHLD, &action, NULL);
  while (1) {
    printf("parent id %d\n", getpid());
    sleep(1);
  }
}