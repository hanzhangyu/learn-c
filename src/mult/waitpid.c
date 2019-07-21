#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>

int main(void) {
    pid_t pid;
    int n = 3;
    while (n--) {
        pid = fork();
        if (pid == 0) {
            break;
        }
    }
    if (pid == 0) {
        {
            printf("I am child %d, gpid is %d\n", getpid(), getpgid(getpid())); // 默认所有子进程在同一进程组下
            sleep(3);
        }
    } else if (pid > 0) {
        pid_t pid_c;
        n = 0;
        while (1) {
            printf("I am parent \n");
            pid_c = waitpid(0, NULL, WNOHANG); // 不阻塞
            if (pid_c == -1)
                continue;
            else {
                printf("wait for child %d\n", pid_c);
                if(pid_c > 0) {
                    if (++n == 3 ) break;
                }
            }
            sleep(1);
        }
    }

    return 0;
}