/**
 * @file 
 * @usage 
 */
#include <stdio.h>
#include <bits/types/sig_atomic_t.h>

struct MAN {
    int age;
};

int main(void) {
  struct MAN man1, man2;
  man1.age = 11;
  man2 = man1; // 赋值，将会把man1的内存块直接复制给man2。（废话，C里面除了指针和值，又没有引用）
  man2.age = 12;
  printf("man1.age: %d\nman2.age: %d", man1.age, man2.age);
  printf("sizeof sig_atomic_t: %lu", sizeof(sig_atomic_t));
}
