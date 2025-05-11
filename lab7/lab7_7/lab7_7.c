#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

int main() {
    DIR *dir;
    struct dirent *entry;
    struct stat fileStat;
    char choice;

    dir = opendir(".");
    if (!dir) {
        perror("opendir");
        return 1;
    }

    while ((entry = readdir(dir)) != NULL) {
        if (strstr(entry->d_name, ".c") != NULL) {
            if (stat(entry->d_name, &fileStat) == -1) {
                perror("stat");
                continue;
            }


            if (S_ISREG(fileStat.st_mode)) {
                printf("File: %s\n", entry->d_name);
                printf("Grant read permission to others? (y/n): ");
                scanf(" %c", &choice);

                if (choice == 'y' || choice == 'Y') {
                    mode_t new_mode = fileStat.st_mode | S_IROTH;
                    if (chmod(entry->d_name, new_mode) == -1) {
                        perror("chmod");
                    } else {
                        printf("Permission granted.\n");
                    }
                }
            }
        }
    }

    closedir(dir);
    return 0;
}
