/**
 * @file 循环导致死锁
 * @usage 
 */
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

#define ADD_TIME 10000

int number = 0;

pthread_mutex_t counter_mutexA = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t counter_mutexB = PTHREAD_MUTEX_INITIALIZER;

void *th_funcA(void *arg) {
  for (int i = 0, temp; i < ADD_TIME; ++i) {
    pthread_mutex_lock(&counter_mutexA);

    temp = number;
    printf("%x: %d\n", (unsigned int)pthread_self(), temp + 1);
    number = temp + 1;

    pthread_mutex_lock(&counter_mutexB);
    pthread_mutex_unlock(&counter_mutexB);

    pthread_mutex_unlock(&counter_mutexA);
  }
  printf("number %d\n", number);

  return NULL;
}
void *th_funcB(void *arg) {
  for (int i = 0, temp; i < ADD_TIME; ++i) {
    pthread_mutex_lock(&counter_mutexB);

    temp = number;
    printf("%x: %d\n", (unsigned int)pthread_self(), temp + 1);
    number = temp + 1;

    pthread_mutex_lock(&counter_mutexA);
    pthread_mutex_unlock(&counter_mutexA);

    pthread_mutex_unlock(&counter_mutexB);
  }
  printf("number %d\n", number);

  return NULL;
}

int main(void) {
  pthread_t tidA;
  pthread_t tidB;

  pthread_create(&tidA, NULL, th_funcA, NULL);
  pthread_create(&tidB, NULL, th_funcB, NULL);

  pthread_join(tidA, NULL);
  pthread_join(tidB, NULL);

  printf("expected %d\n", 2 * ADD_TIME);
  printf("actual %d\n", number); // 可以看到

  return 0;
}