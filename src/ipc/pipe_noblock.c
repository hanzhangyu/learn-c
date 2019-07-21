#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <wait.h>
#include <fcntl.h>
#include <errno.h>

int main(void) {
    int fds[2];
    char str[] = "hello world";
    char buf[1024];
    pid_t pid;

    if (pipe(fds) < 0) {
        perror("pipe");
        exit(1);
    }

    pid = fork();
    // 父写子读
    if (pid > 0) {
        close(fds[0]); // 关闭父读
        sleep(5);
        write(fds[1], str, strlen(str));
        close(fds[1]); // 写完关闭写端
        wait(NULL);
    } else if (pid == 0) {
        int len, flags;
        close(fds[1]); // 关闭子写
        flags = fcntl(fds[0], F_GETFL);
        flags |= O_NONBLOCK;
        fcntl(fds[0], F_SETFL, flags);
        reread:
        len = read(fds[0], buf, sizeof(buf)); // 无数据，阻塞读，等待sleep结束写数据
        if (len == -1) {
            if (errno == EAGAIN) {
                write(STDOUT_FILENO, "try again\n", 10);
                sleep(1);
                goto reread;
            } else {
                perror("read");
                exit(1);
            }
        }
        write(STDOUT_FILENO, str, len);
        close(fds[0]);
    } else {
        perror("fork");
        exit(1);
    }
    return 0;
}