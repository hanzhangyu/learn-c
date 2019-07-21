#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int main(void) {
    int fd = open("abc.txt", O_RDWR | O_CREAT);
    if (fd < 0) {
        perror("open abc.txt");
        exit(-1);
    }

    lseek(fd, 0x1000, SEEK_SET); // 修改读写位置，向后移动 4096 位置
    char buf[1024];
    // region 读不会触发文件大小改变
    int len = read(fd, buf, sizeof(buf));
    write(STDOUT_FILENO, buf, len);
    // endregion
    // region 写会
    write(fd, "a", 1); // ls -l abc.txt 得到 4097
    // endregion
    close(fd);
    return 0;
}