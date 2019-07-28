/**
 * @file 时序竞态
 * @usage 
 */
#include <stdio.h>
#include <signal.h>
#include <unistd.h>

void sigHandler(int num) {
}

unsigned int mySleep(unsigned int second) {
  struct sigaction newact, oldact;
  sigset_t newmask, oldmask, suspmask;
  unsigned int unslept;

  // region 将action设为空函数，并报存原本的action
  newact.sa_handler = sigHandler;
  sigemptyset(&newact.sa_mask);
  newact.sa_flags = 0;
  sigaction(SIGALRM, &newact, &oldact);
  // endregion

  // region 阻塞 sigalrm，并报存当前的阻塞信号集
  sigemptyset(&newmask);
  sigaddset(&newmask, SIGALRM);
  sigprocmask(SIG_BLOCK, &newmask, &oldmask);
  // endregion

  alarm(second);

  suspmask = oldmask;
  sigdelset(&suspmask, SIGALRM); // 解除 sigalrm 阻塞
  sigsuspend(&suspmask); // 等待信号

  unslept = alarm(0); // 加入被其他信号强制唤醒，获取未休眠的时间

  sigaction(SIGALRM, &oldact, NULL); // 恢复旧的action
  sigprocmask(SIG_SETMASK, &oldmask, NULL); // 恢复阻塞信号集

  return unslept;
}

int main(void) {
  mySleep(5);
  printf("sleep success");
  return 0;
}