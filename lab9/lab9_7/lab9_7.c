#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>

#define FLAGFILE "/tmp/.group_ready"

int main() {
    uid_t uid = getuid();
    const char *filename = "/tmp/groupdir/shared.txt";

    if (access(FLAGFILE, F_OK) != 0) {
        FILE *f = fopen(FLAGFILE, "w");
        if (f) {
            fprintf(f, "%d", uid);
            fclose(f);
            printf("Waiting for second user...\n");
            sleep(10); 
        } else {
            perror("fopen");
        }
        remove(FLAGFILE);
        printf("Timeout. No cooperation.\n");
    } else {
        FILE *out = fopen(filename, "w");
        if (out) {
            fprintf(out, "Shared file created by two users!\n");
            fclose(out);
            printf("Success! File written.\n");
        } else {
            perror("fopen");
        }
        remove(FLAGFILE);
    }

    return 0;
}

