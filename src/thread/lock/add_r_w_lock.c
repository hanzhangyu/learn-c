/**
 * @file 读写锁
 * @usage 
 */
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

#define ADD_TIME 10000
#define THREAD_NUM_WRITE 2
#define THREAD_NUM_READ 3

int number = 0;

pthread_rwlock_t rwlock;

void *th_func_w(void *arg) {
  for (int i = 0, temp; i < ADD_TIME; ++i) {
    pthread_rwlock_wrlock(&rwlock);

    temp = number;
    usleep(1);
    number = temp + 1;

    pthread_rwlock_unlock(&rwlock);
  }
  printf("number %d\n", number);

  return NULL;
}

void *th_func_r(void *arg) {
  for (int i = 0; i < ADD_TIME; ++i) {
    pthread_rwlock_rdlock(&rwlock);
    printf("%x read : %d\n", (int)pthread_self(), number);
    pthread_rwlock_unlock(&rwlock);

    usleep(700); // 让写线程写的时间多一点
  }
  printf("number %d\n", number);

  return NULL;
}


int main(void) {
  pthread_t w_tids[THREAD_NUM_WRITE];
  pthread_t r_tids[THREAD_NUM_READ];

  for (int i = 0; i < THREAD_NUM_WRITE; ++i) {
    pthread_create(w_tids + i, NULL, th_func_w, NULL);
  }
  for (int i = 0; i < THREAD_NUM_READ; ++i) {
    pthread_create(r_tids + i, NULL, th_func_r, NULL);
  }

  for (int j = 0; j < THREAD_NUM_WRITE; ++j) {
    pthread_join(w_tids[j], NULL);
  }
  for (int j = 0; j < THREAD_NUM_READ; ++j) {
    pthread_join(r_tids[j], NULL);
  }

  printf("expected %d\n", THREAD_NUM_WRITE * ADD_TIME);
  printf("actual %d\n", number); // 可以看到

  return 0;
}