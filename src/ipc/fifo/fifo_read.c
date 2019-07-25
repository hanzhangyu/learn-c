/**
 * @file fifo通过文件实现read
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
    int fd, len;
    char buf[1024];
    if (argc < 2) {
        printf("./a,out expect fifoname\n");
        exit(1);
    }
    fd = open(argv[1], O_RDONLY);
    if (fd < 0) sys_err("open", 1);
    len = read(fd, buf, sizeof(buf)); // 阻塞直至有写入端打开
    write(STDOUT_FILENO, buf, len);
    close(fd);

    return 0;
}