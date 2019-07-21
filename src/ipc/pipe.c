#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <wait.h>

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
        sleep(2);
        write(fds[1], str, strlen(str));
        wait(NULL);
    } else if (pid == 0) {
        int len;
        close(fds[1]); // 关闭子写
        len = read(fds[0], buf, sizeof(buf)); // 无数据，阻塞读，等待sleep结束写数据
        // sprintf(str, "child %s", buf);
        write(STDOUT_FILENO, str, len);
    } else {
        perror("fork");
        exit(1);
    }
    return 0;
}