/**
 * @file 函数指针 与 指针函数 与 通过指针函数实现回调
 * @usage
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 函数指针
int *add(int a, int b) {
  int *p = (int *) malloc(sizeof(int));
  memset(p, 0, sizeof(int)); // 初始化，可以不必
  *p = a + b;
  printf("*p = %d \n", *p);
  return p;
}

int max(int a, int b) {
  return a > b ? a : b;
}

int min(int a, int b) {
  return a < b ? a : b;
}

/**
 * C 的回调函数
 * @param func 接受一个函数指针
 * @param other 可以传入任意类型，单都会被转为int
 * @return 返回一个指针
 */
int *wrapper(int (*func)(int, int), void *other) {
  // do something
  int *ret = (int *) malloc(sizeof(int));
  *ret = func(0, *(int *)other);
  return ret;
}

int main(void) {
  // region 函数指针
  int *p = NULL;
  p = add(1, 2);
  printf("main *p = %d \n", *p);
  // endregion


  // region 指针函数
  int (*p_func)(int, int); // 声明函数指针（c# 的委托也是怎么实现的？）
  p_func = max;
  printf("max(1,2) = %d \n", p_func(1, 2));
  p_func = min;
  printf("min(1,2) = %d \n", p_func(1, 2));
  // endregion


  // region 回调
  int *num = (int *) malloc(sizeof(int));
  *num = -1;
  int *retNum = NULL;
  retNum = wrapper(max, (void *)num);
  printf("wrapper max curry 0 compare -1 = %d \n", *retNum);
  retNum = wrapper(min, (void *)num);
  printf("wrapper min curry 0 compare -1 = %d \n", *retNum);
  // endregion

  return 0;
}