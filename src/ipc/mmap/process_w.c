/**
 * @file 将结构体写入映射的内存
 * @usage
 * $ gcc process_w -o process_w.out
 * $ ./process_w.out mmap.tmp
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
  fd = open(argv[1], O_CREAT | O_RDWR, 0777);
  if (fd < 0) {
    perror("open");
    exit(1);
  }
  // region 修正文件大小
  if (lseek(fd, LEN - 1, SEEK_SET) < 0) {
    perror("lseek");
    exit(1);
  }
  if (write(fd, "\0", 1) < 0) {
    perror("write");
    exit(1);
  }
  // endregion

  mmp = mmap(NULL, LEN, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
  if (mmp == MAP_FAILED) {
    perror("mmap");
    exit(1);
  }

  close(fd); // 与我们修改内存没有关系，所以可以关闭


  while (i < 100) {
    mmp->id = i;
    sprintf(mmp->name, "student%d", i);
    mmp->sex = i % 2 == 0 ? 'm' : 'w';
    puts("write success");
    sleep(1);
    i++;
  }
}