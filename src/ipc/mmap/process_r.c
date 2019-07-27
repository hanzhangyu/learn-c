/**
 * @file 从映射的内存中读取结构体
 * @usage
 * $ gcc process_r -o process_r.out
 * $ ./process_r.out mmap.tmp
 */
#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>

#define LEN 0x1000 // 4K

struct STU {
    int id;
    char name[100];
    char sex;
};

int main(int argc, char *argv[]) {
  struct STU *mmp;
  int fd;
  int i = 0;
  if (argc < 2) {
    printf("need filename");
    exit(1);
  }
  fd = open(argv[1], O_RDONLY, 0777);
  if (fd < 0) {
    perror("open");
    exit(1);
  }

  mmp = mmap(NULL, LEN, PROT_READ, MAP_SHARED, fd, 0);
  if (mmp == MAP_FAILED) {
    perror("mmap");
    exit(1);
  }

  close(fd); // 与我们修改内存没有关系，所以可以关闭，外部修改文件，shared模式下内存同步

  while(i++ < 100) {
    puts("======================================");
    printf("id: %d | name: %s | sex: %c\n", mmp->id, mmp->name, mmp->sex);
    sleep(1);
  }
}