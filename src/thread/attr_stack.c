/**
 * @file 设置进程 stack 属性
 * @usage
 * $ ./a.out
 * $ ps -eLF
 * after 5 seconds
 * $ ps -eLF
 *  ... ./a.out <defunct>
 *  ... ./a.out
 */
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

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
  void *ret;

  pthread_attr_init(&attr);
  pthread_attr_getstack(&attr, &stackAddr, &stackSize); // 初始为默认
  printf("stackAddr: %p, stackSize %x\n", stackAddr, (int) stackSize);


  stackAddr = malloc(0x100000);
  if (stackAddr == NULL) {
    perror("malloc");
    exit(1);
  }
  stackSize = 0x100000;
  pthread_attr_setstack(&attr, stackAddr, stackSize);
  pthread_attr_getstack(&attr, &stackAddr, &stackSize);
  printf("stackAddr: %p, stackSize %x\n", stackAddr, (int) stackSize);

  err = pthread_create(&tid, &attr, th_func, NULL);
  if (err) {
    printf("create failed: %s\n", strerror(err));
    exit(1);
  }
  pthread_join(tid, &ret);
  printf("return %d\n", *(int *) ret);

  pthread_attr_destroy(&attr);

  return 0;
}