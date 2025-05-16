#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <sys/stat.h>

int can_read_write(const char *filepath) {
    if (access(filepath, R_OK) == 0)
        printf("User CAN read the file.\n");
    else
        printf("User CANNOT read the file. (%s)\n", strerror(errno));

    if (access(filepath, W_OK) == 0)
        printf("User CAN write to the file.\n");
    else
        printf("User CANNOT write to the file. (%s)\n", strerror(errno));
}

int main() {
    const char *tmpFile = "/tmp/mytempfile.txt";


    FILE *fp = fopen(tmpFile, "w");
    if (!fp) {
        perror("fopen");
        return 1;
    }
    fprintf(fp, "Temporary data.\n");
    fclose(fp);
    printf("Temporary file '%s' created by normal user.\n", tmpFile);



    const char *user_name = getenv("USER");
    if (!user_name) user_name = "yourusername"; 

    char command[512];


    snprintf(command, sizeof(command), "sudo chown root:root %s", tmpFile);
    if (system(command) != 0) {
        fprintf(stderr, "Failed to chown to root.\n");
        return 1;
    }
    printf("Changed owner to root.\n");


    snprintf(command, sizeof(command), "sudo chmod 0644 %s", tmpFile);
    if (system(command) != 0) {
        fprintf(stderr, "Failed to chmod 0644.\n");
        return 1;
    }
    printf("Changed permissions to 0644.\n");

    printf("Testing access after chown root and chmod 0644:\n");
    can_read_write(tmpFile);


    snprintf(command, sizeof(command), "sudo chown %s:%s %s", user_name, user_name, tmpFile);
    if (system(command) != 0) {
        fprintf(stderr, "Failed to chown back to user.\n");
        return 1;
    }
    snprintf(command, sizeof(command), "sudo chmod 0600 %s", tmpFile);
    if (system(command) != 0) {
        fprintf(stderr, "Failed to chmod \n");
        return 1;
    }
    printf("Changed owner back to %s \n", user_name);

    printf("Testing access \n");
    can_read_write(tmpFile);


    if (remove(tmpFile) != 0) {
        perror("Failed  remove file");
    } else {
        printf(" file removed.\n");
    }

    return 0;
}

