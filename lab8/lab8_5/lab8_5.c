#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>


void test_lseek(const char *path) {
    printf("\ Test: %s \n", path);

    int fd = open(path, O_RDONLY);
    if (fd == -1) {
        perror("open");
        return;
    }


    off_t pos = lseek(fd, 1000, SEEK_SET);
    if (pos == -1) {
        printf("lseek(fd, 1000, SEEK_SET) FAILED: %s\n", strerror(errno));
    } else {
        printf("lseek(fd, 1000, SEEK_SET) = %ld\n", (long)pos);
    }


    pos = lseek(fd, 0, SEEK_CUR);
    if (pos == -1) {
        printf("lseek(fd, 0, SEEK_CUR) FAILED: %s\n", strerror(errno));
    } else {
        printf("lseek(fd, 0, SEEK_CUR) = %ld\n", (long)pos);
    }


    pos = lseek(fd, 0, SEEK_END);
    if (pos == -1) {
        printf("lseek(fd, 0, SEEK_END) FAILED: %s\n", strerror(errno));
    } else {
        printf("lseek(fd, 0, SEEK_END) = %ld\n", (long)pos);
    }

    close(fd);
}

int main() {
    test_lseek("/dev/null");
    test_lseek("/dev/zero");
    return 0;
}

