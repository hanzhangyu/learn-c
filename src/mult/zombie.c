#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main(void) {
    pid_t pid;
    pid = fork();
    if (pid < 0) {
        perror("fork failed");
        exit(1);
    }
    if (pid == 0) {
        printf("This is the child\n");
        printf("My pid = %d\n", getpid());
        printf("My parent pid = %d\n", getppid());
        sleep(10);
    } else {
        while (1) {
            printf("This is the parent\n");
            printf("My pid = %d\n", getpid());
            printf("My parent pid = %d\n", getppid());
            sleep(1);
        }
    }
    return 0;
}