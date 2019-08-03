/**
 * @file 设置进程 detach 属性
 * @tip 不要在 WSL 中试
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
  return (void *) i;
}


int main(void) {
  pthread_t tid;
  pthread_attr_t attr;
  int err, detachState;

  pthread_attr_init(&attr);

  pthread_attr_getdetachstate(&attr, &detachState);
  if (detachState == PTHREAD_CREATE_DETACHED)
    puts("is detached");
  else if (detachState == PTHREAD_CREATE_JOINABLE) // 可以看到，系统默认为 joined
    puts("is joined");
  else
    puts("unknown");

  pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);

  err = pthread_create(&tid, &attr, th_func, NULL);

  if (err) {
    printf("create failed: %s\n", strerror(err));
    exit(1);
  }

  err = pthread_join(tid, NULL); // 属性设置了 detached ，无法join
  if (err) {
    printf("get retval failed: %s\n", strerror(err)); // Invalid argument
    sleep(5);
    // exit(1)。注意这里不能使用 exit 退出，不然进程就退出了
    pthread_exit((void *) 1); // 退出主线程，未回收显示 defunct，类似僵尸线程
    puts("can`t reach");
  }

  return 0;
}