/**
 * @file 获取文件配置信息
 */
#include <stdio.h>
#include <unistd.h>

int main(void) {
    // region 文件名大小
    printf("%ld\n", fpathconf(STDOUT_FILENO, _PC_NAME_MAX));
    printf("%ld\n", pathconf("/tmp/temp", _PC_NAME_MAX));
    // endregion

    // region pipe buf 大小
    int fd[2];
    pipe(fd);
    printf("pipe buf %ld\n", fpathconf(fd[0], _PC_PIPE_BUF));
    // endregion

    return 0;
}
