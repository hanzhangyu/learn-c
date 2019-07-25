/**
 * @file fifo通过文件实现write
 * @usage
 * $ mkfifo myfifo
 * $ gcc fifo_write
 * $ gcc fifo_read
 * $ ./fifo_write myfifo
 * $ ./fifo_read myfifo
 */
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>

void sys_err(char *str, int exitno) {
    perror(str);
    exit(exitno);
}

int main(int argc, char *argv[]) {
    int fd;
    char buf[] = "hello world\n";
    if (argc < 2) {
        printf("./a,out expect fifoname\n");
        exit(1);
    }
    fd = open(argv[1], O_WRONLY);
    if (fd < 0) sys_err("open", 1);
    write(fd, buf, strlen(buf)); // 阻塞直至有读取端打开
    close(fd);

    return 0;
}