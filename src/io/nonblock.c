/**
 * @file 非阻塞读取终端
 */
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>

#define MSG_TRY "try again\n"

int main(void) {
    char buf[10];
    int fd, n;
    fd = open("/dev/tty", O_RDONLY | O_NONBLOCK); // 打开文件时设置为非阻塞
    if (fd < 0) {
        perror("open /dev/tty");
        exit(1);
    }
    // region 轮询检查数据
    tryagain:
    n = read(fd, buf, 10);
    if (n < 0) {
        if (errno == EAGAIN) { // Try again
            sleep(1);
            write(STDOUT_FILENO, MSG_TRY, strlen(MSG_TRY));
            goto tryagain;
        }
        perror("read /dev/tty");
        exit(1);
    }
    write(STDOUT_FILENO, buf, n);
    close(fd);
    // endregion
    return 0;
}