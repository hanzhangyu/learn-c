#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(void) {
    if(close(STDOUT_FILENO) < 0) {
        perror("close stdout");
        exit(1);
    }
    int fd;
    if ((fd = open("output.txt", O_WRONLY | O_CREAT, 0777)) < 0) { // 填充关闭的 fd 1
        perror("open failed");
        exit(1);
    }
    write(STDOUT_FILENO, "helloworld\n", 11); // 写入了 output.txt
    // region disabled cache to print immediately
    setbuf(stdout, NULL);
    printf("printf to %d\n", fd);
    close(fd); // 立即关闭，如果有缓存 printf 将会打印失败
    // endregion
    return 0 ;
}