#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <limits.h>
#include <unistd.h>
#include <sys/stat.h>

#define BUF_SIZE 4096

int main(int argc, char *argv[]) {
    FILE *src, *dest;
    char buffer[BUF_SIZE];
    size_t bytesRead, bytesWritten;
    struct stat st;

    if (argc != 3) {
        fprintf(stderr, "Program need two arguments\n");
        return 1;
    }

    src = fopen(argv[1], "rb");
    if (!src) {
        fprintf(stderr, "Cannot open file %s for reading: %s\n", argv[1], strerror(errno));
        return 2;
    }

    dest = fopen(argv[2], "wb");
    if (!dest) {
        fprintf(stderr, "Cannot open file %s for writing: %s\n", argv[2], strerror(errno));
        fclose(src);
        return 3;
    }

    if (fstat(fileno(src), &st) == 0 && st.st_size > (1L << 30)) {
        fprintf(stderr, "File size exceeds 1GB limit\n");
        fclose(src);
        fclose(dest);
        return 4;
    }

    while ((bytesRead = fread(buffer, 1, BUF_SIZE, src)) > 0) {
        bytesWritten = fwrite(buffer, 1, bytesRead, dest);
        if (bytesWritten != bytesRead) {
            fprintf(stderr, "Error writing to %s\n", argv[2]);
            fclose(src);
            fclose(dest);
            return 5;
        }
    }

    fclose(src);
    fclose(dest);
    return 0;
}

