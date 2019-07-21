/**
 * @file exec example
 */

#include <stdio.h>
#include <unistd.h> // 提供对POSIX 操作系统API 的访问功能

/**
#include <unistd.h>
int execl(const char *path, const char *arg, ...);
int execlp(const char *file, const char *arg, ...);
int execle(const char *path, const char *arg, ..., char *const envp[]);
int execv(const char *path, char *const argv[]);
int execvp(const char *file, char *const argv[]);
int execve(const char *path, char *const argv[], char *const envp[]);
 */
int main(void) {
    printf("hello\n");
    /**
     * /bin/ls 程序所在的路径
     * ls 第一个命令行参数为，执行该程序时的调用方式 argv[0]
     * NULL 哨兵，标记argv结束
     */
    execl("/bin/ls", "ls", "-l", NULL);
    printf("word\n");
    return 0;
}
