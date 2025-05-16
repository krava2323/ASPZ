#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/stat.h>

int main(void) {
    const char *tmpFile = "/tmp/myfile.txt";
    const char *destDir = "/home/krava/Public/lab9";
    const char *destFile = "/home/krava/Public/lab9/myfile.txt";


    FILE *fp = fopen(tmpFile, "w");
    if (!fp) {
        perror("fopen(tmpFile)");
        return 1;
    }
    fprintf(fp, "This file created normal user.\n");
    fclose(fp);
    printf("File '%s' created  normal user.\n", tmpFile);


    struct stat st = {0};
    if (stat(destDir, &st) == -1) {
        if (mkdir(destDir, 0755) != 0) {
            perror("mkdir(destDir)");
            return 1;
        }
        printf("Created directory: %s\n", destDir);
    }


    char command[512];
    snprintf(command, sizeof(command),
             "sudo cp %s %s && sudo chown root:root %s",
             tmpFile, destFile, destFile);
    int ret = system(command);
    if (ret != 0) {
        fprintf(stderr, "Failed to copy file as root. Return code: %d\n", ret);
        return 1;
    }
    printf("File copied to '%s' as root.\n", destFile);


    fp = fopen(destFile, "a");
    if (fp) {
        fprintf(fp, "Attempting to modify the file...\n");
        fclose(fp);
        printf("Modification succeeded. (Unexpected!)\n");
    } else {
        printf("Modification failed as expected: %s\n", strerror(errno));
    }


    ret = remove(destFile);
    if (ret != 0) {
        printf("File deletion failed: %s\n", strerror(errno));
    } else {
        printf("File successfully deleted.\n");
    }

    return 0;
}

