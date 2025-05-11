#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>

int main() {
    int count = 0;
    int fd;
    char filename[256];

    while (1) {
        snprintf(filename, sizeof(filename), "tmpfile_%d.txt", count);
        fd = open(filename, O_CREAT | O_WRONLY, 0644);
        if (fd == -1) {
            perror("open");
            printf("Total files opened: %d\n", count);
            break;
        }
        count++;
    }

    return 0;
}

