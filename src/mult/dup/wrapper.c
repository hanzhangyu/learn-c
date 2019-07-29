/**
 * @file 将文件转发至exec的输入
 * @usage
 * $ gcc wrapper.c -o wrapper.out
 * $ gcc upper.c -o upper.out
 * $ echo helloworld > temp.tmp
 * $ ./wrapper temp.tmp
 * HELLOWORLD
 */
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
int main(int argc, char *argv[])
{
    int fd;
    if (argc != 2) {
        fputs("usage: wrapper file\n", stderr);
        exit(1);
    }
    fd = open(argv[1], O_RDONLY);
    if(fd<0) {
        perror("open");
        exit(1);
    }
    // 复制文件 fd 至 stdin 位置，然后关闭fd
    dup2(fd, STDIN_FILENO);
    close(fd);
    execl("./upper.out", "upper", NULL);
    perror("exec ./upper.out");
    exit(1);
}