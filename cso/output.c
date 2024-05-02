#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/stat.h>

int main() {
    printf("This is before open\n"); fflush(stdout);
    int fd = open("output.txt", O_WRONLY | O_CREAT | O_TRUNC);
    if (fd < 0) { printf("Error in open\n"); return 1; }
    printf("This is after open\n"); fflush(stdout);
    dup2(fd, 1);
    printf("This is after dup2\n"); fflush(stdout);
    close(fd);
    printf("This is after close\n"); fflush(stdout);
    return 0;
}
