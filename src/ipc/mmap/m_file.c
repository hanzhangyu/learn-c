/**
 * @file mmap 修改通过指针文件
 * @usage
 * $ echo helloworld > temp.tmp
 * $ gcc m_file.c
 * $ ./a.out
 * $ od -tx1 -tc temp.tmp # 越界的len会被忽略
 * 0000000  30  31  32  33  30  31  32  33  30  31  32
 *          0   1   2   3   0   1   2   3   0   1   2
 * 0000013
 */
#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>

int main(void) {
  int fd;
  int len;
  int *mmp;
  if ((fd = open("temp.tmp", O_RDWR)) < 0) {
    perror("open");
    exit(1);
  }
  len = lseek(fd, 0, SEEK_END); // 假设我们获取这个文件大小的内存
  mmp = mmap(NULL, len, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
  if (mmp == MAP_FAILED) {
    perror("mmap");
    exit(1);
  }
  setbuf(stdout, NULL);
  printf("len: %d\nsizeof mmp %ld\n", len, sizeof(mmp)); // TODO 为什么返回了8个指针长度？
  // 越界修改
  for (int i = 0; i < sizeof(mmp); ++i) {
    printf("origin mmp[%d] is %x\n", i, mmp[i]);
    mmp[i] = 0x33323130; // 后面的被丢齐了（x86为小端）
    printf("now mmp[%d] is %x\n", i, mmp[i]);
  }
  close(fd);
  munmap(mmp, len);
}