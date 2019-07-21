/**
 * @file errno 是一个唯一的全局变量
 */
#include <stdio.h>
#include <fcntl.h>
#include <errno.h>

#define MSG_TRY "try again\n"

int main(void) {
    int fd;
    fd = open("not exist", O_RDONLY );
//    if (fd < 0) perror("error is"); // 如果不及时处理就会被覆盖
    // int errnoOfFd = errno; // 缓存errno
    int fd2 = open("/tmp/temp", O_CREAT |  O_EXCL, 0444);
    if (fd < 0) perror("error is"); // 如果文件已存在，两个语句都会报错，错误会被覆盖
    if (fd2 < 0) perror("error is");
    return 0;
}