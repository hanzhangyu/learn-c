/**
 * @file
 * @failed
 *      1. 原本是想测试一下 栈空间 对线程数上限的影响，结果一直都是 9180 附近徘徊（怀疑有其他设置上限，第二点就是）
 *      2. 单独 malloc，系统都卡住了，还没出现分配错误
 */
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#define STACK_SIZE 0x100000

void *th_func(void *arg) {
  int i;
  for (i = 0; i < 10; ++i) {
    printf("%x = %d\n", (unsigned int) pthread_self(), i);
    sleep(1);
  }
  int *ret = (int *) malloc(sizeof(int));
  *ret = i;
  return ret;
}


int main(void) {
  pthread_t tid;
  pthread_attr_t attr;
  int err;
  size_t stackSize;
  void *stackAddr;
  // void *ret;

  pthread_attr_init(&attr);
  pthread_attr_getstack(&attr, &stackAddr, &stackSize); // 初始为默认
  printf("stackAddr: %p, stackSize %x\n", stackAddr, (int) stackSize);

  pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED); // 设为detach，测试最大创建线程数

  for (int i = 0; i < 1000000; ++i) {

    stackAddr = malloc(STACK_SIZE);
    if (stackAddr == NULL) {
      perror("malloc");
      exit(1);
    }
    stackSize = STACK_SIZE;
    pthread_attr_setstack(&attr, stackAddr, stackSize);
    pthread_attr_getstack(&attr, &stackAddr, &stackSize);
    printf("stackAddr: %p, stackSize %x\n", stackAddr, (int) stackSize);

    err = pthread_create(&tid, &attr, th_func, NULL);
    if (err) {
      printf("create failed: %s\n", strerror(err));
      exit(1);
    }
    // pthread_join(tid, &ret);
    printf("index %d\n", i);

  }

  pthread_attr_destroy(&attr);

  return 0;
}