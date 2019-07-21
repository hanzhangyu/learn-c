/**
 * @file test for S_ISUID
 * 1. gcc
 * 2. mv to root directory
 * 3. use mod 06755
 * 5. create file
 */

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "expected filename\n");
        return 1;
    }
    char *filename = argv[1];
    int fd = open(filename, O_CREAT, 0777);
    printf("%d:%d\n", getuid(), getgid());
    printf("%d:%d\n", geteuid(), getegid());
    if (fd < 0) {
        perror("created failed");
        return 0;
    }
    printf("created file %s\n", filename);
    close(fd);
    return 0;
}