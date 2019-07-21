/**
 * @file use wait
 */
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(void) {
    pid_t pid, pid_c;
    pid = fork();
    if (pid < 0) {
        perror("fork failed");
        exit(1);
    }
    if (pid == 0) {
        printf("This is the child %d\n", getpid());
        sleep(10);
    } else {
        while (1) {
            printf("This is the parent %d\n", getpid());
            // pid_c = wait(NULL); // 传入NULL，不关心子进程时如何死亡的
            int status;
            pid_c = wait(&status);
            printf("wait for child %d\n", pid_c);
            sleep(1);
        }
    }
    return 0;
}