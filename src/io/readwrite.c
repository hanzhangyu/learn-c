#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

int main(void) {
    char buf[1024];
    char *breakLine = "\nnext read\n";
    int len;
//    len = read(STDIN_FILENO, buf, sizeof(buf));
    // 1. read只读走10个字符，剩下的字符仍然保存在内核的终端设备输入缓冲区中
    // 1. read只读走10个字符，剩下的字符仍然保存在内核的终端设备输入缓冲区中
    // 2. 再次read的时候继续上次读取
    // 3. a.out退出时，这时Shell进程恢复运行，Shell继续从终端读取用户输入的命令
    // 4. 于是读走了终端设备输入缓冲区中剩下的字符d和换行符，把它当成一条命令解释执行
    len = read(STDIN_FILENO, buf, 10);
    write(STDOUT_FILENO, buf, len);
    write(STDOUT_FILENO, breakLine, strlen(breakLine));
    len = read(STDIN_FILENO, buf, 10);
    write(STDOUT_FILENO, buf, len);
    return 0;
}