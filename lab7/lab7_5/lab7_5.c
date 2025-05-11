#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

void list_files(const char *path) {
    struct dirent *entry;
    DIR *dir = opendir(path);

    if (!dir) {
        perror("opendir");
        return;
    }

    printf("Directory: %s\n", path);

    while ((entry = readdir(dir)) != NULL) {
        char full_path[1024];
        struct stat entry_stat;


        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
            continue;

        snprintf(full_path, sizeof(full_path), "%s/%s", path, entry->d_name);
        if (stat(full_path, &entry_stat) == -1) {
            perror("stat");
            continue;
        }

        if (S_ISDIR(entry_stat.st_mode)) {

            list_files(full_path);
        } else {

            printf("  %s\n", full_path);
        }
    }

    closedir(dir);
}

int main() {
    list_files(".");
    return 0;
}

