/**
 * @file 锁
 * @usage 
 */
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

#define ADD_TIME 10000
#define THREAD_NUM 2

int number = 0;

pthread_mutex_t counter_mutex = PTHREAD_MUTEX_INITIALIZER;

void *th_func(void *arg) {
  for (int i = 0, temp; i < ADD_TIME; ++i) {
    pthread_mutex_lock(&counter_mutex); // 只有一个能获得锁，其他阻塞

    temp = number;
    usleep(1);
    number = temp + 1;

    pthread_mutex_unlock(&counter_mutex);
  }
  printf("number %d\n", number);

  return NULL;
}

int main(void) {
  pthread_t tids[THREAD_NUM];

  int err;
  for (int i = 0; i < THREAD_NUM; ++i) {
    err = pthread_create(tids + i, NULL, th_func, NULL);
    if (err) {
      printf("%s\n", strerror(err));
      exit(1);
    }
  }

  for (int j = 0; j < THREAD_NUM; ++j) {
    pthread_join(tids[j], NULL);
  }

  printf("expected %d\n", THREAD_NUM * ADD_TIME);
  printf("actual %d\n", number); // 可以看到

  return 0;
}