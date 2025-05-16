#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pwd.h>

#define UID_THRESHOLD 1000  

int main() {
    FILE *fp;
    char line[512];
    int found_other_users = 0;

    uid_t my_uid = getuid(); 
    struct passwd *pw = getpwuid(my_uid);
    const char *my_username = pw ? pw->pw_name : "unknown";

    fp = popen("getent passwd", "r");
    if (fp == NULL) {
        perror("popen");
        return 1;
    }

    printf("Your UID: %d, Username: %s\n", my_uid, my_username);
    printf("Search other users (UID >= %d)...\n\n", UID_THRESHOLD);

    while (fgets(line, sizeof(line), fp)) {
        char *username = strtok(line, ":");
        strtok(NULL, ":"); 
        char *uid_str = strtok(NULL, ":");
        if (!username || !uid_str) continue;

        int uid = atoi(uid_str);

        if (uid >= UID_THRESHOLD && strcmp(username, my_username) != 0) {
            found_other_users = 1;
            printf("Found user: %s (UID: %d)\n", username, uid);
        }
    }

    pclose(fp);

    if (!found_other_users) {
        printf("\n no otherusers found.\n");
    }

    return 0;
}

