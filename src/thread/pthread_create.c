/**
 * @file 创建一个线程
 * @usage
 */
#include <stdio.h>
#include <pthread.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>


void *th_func(void *arg) {
  int *p = (int *) arg;
  printf("thread id %x\n", (unsigned int)pthread_self());
  printf("thread pid %d\n", getpid());
  printf("thread *arg %d\n", *p);
  // 没有发生系统调用，内核不会终止该线程，pthread_cancel无效
  while (1) {
    // pthread_testcancel(); // 让内核去检测是否需要终止该线程
  }
}

int main(void) {
  pthread_t tid;
  int arg = 10;
  int err;

  // 创建完之后继续执行该进程，还是去执行线程，有操作系统决定
  // 所以如果子进程过快结束，此返回的 tid 可能已经失效
  err = pthread_create(&tid, NULL, th_func, (void *) &arg);
  if (err != 0) {
    fprintf(stderr, "create thread: %s\n", strerror(err));
    exit(1);
  }
  // 可以看到线程的 print 与进程的 print 输出顺序是不固定的，可能混在一起
  printf("main thread id %x\n", (unsigned int)pthread_self());
  printf("main thread id return %x\n", (unsigned int)tid);
  printf("main pid %d\n", getpid());
  pthread_cancel(tid);
  while (1)
    sleep(1);


  return 0;
}