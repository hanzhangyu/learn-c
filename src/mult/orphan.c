#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main(void) {
    pid_t pid;
    pid = fork();
    if (pid > 0) {
        printf("I am parent \n");
        exit(0);
    } else if (pid == 0) {
        int n = 10;
        while (n--) {
            printf("I am %d, my parent is %d \n", getpid(), getppid());
            sleep(1);
        }
    } else {
        perror("fork");
        exit(-1);
    }
}
