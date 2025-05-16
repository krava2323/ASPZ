#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <string.h>
#include <errno.h>

void run_ls(const char *path) {
    char command[256];
    snprintf(command, sizeof(command), "ls -l %s", path);
    printf("\nListing files in %s \n", path);
    system(command);
}

void test_file_access(const char *filepath) {
    printf("\nTesting file: %s\n", filepath);


    int fd = open(filepath, O_RDONLY);
    if (fd < 0) {
        printf("Read: FAIL (%s)\n", strerror(errno));
    } else {
        printf("Read: SUCCESS\n");
        close(fd);
    }


    fd = open(filepath, O_WRONLY);
    if (fd < 0) {
        printf("Write: FAIL (%s)\n", strerror(errno));
    } else {
        printf("Write: SUCCESS\n");
        close(fd);
    }


    if (access(filepath, X_OK) == 0) {
        printf("Execute: POSSIBLE\n");
    } else {
        printf("Execute no possible (%s)\n", strerror(errno));
    }
}

int main() {

    const char *home = getenv("HOME");
    if (!home) {
        fprintf(stderr, "Cannot get HOME environment variable.\n");
        return 1;
    }


    run_ls(home);
    run_ls("/usr/bin");
    run_ls("/etc");


    const char *test_files[] = {
        "/usr/bin/ls",
        "/etc/passwd",
        "/etc/shadow",      
        "/etc/hosts",
        "/bin/bash",
        NULL
    };

    for (int i = 0; test_files[i] != NULL; i++) {
        test_file_access(test_files[i]);
    }

    return 0;
}

