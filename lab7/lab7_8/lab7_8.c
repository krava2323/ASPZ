#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include <unistd.h>

int main() {
    DIR *dir;
    struct dirent *entry;
    char filename[256];
    char choice;
    

    dir = opendir(".");
    if (dir == NULL) {
        perror("Unable to open directory");
        return 1;
    }


    while ((entry = readdir(dir)) != NULL) {

        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
            continue;


        printf("File: %s\n", entry->d_name);


        printf("Do you want to delete this file? (y/n): ");
        scanf(" %c", &choice);  

        if (choice == 'y' || choice == 'Y') {

            if (remove(entry->d_name) == 0) {
                printf("File %s deleted successfully.\n", entry->d_name);
            } else {
                perror("Failed to delete file");
            }
        }
    }

    closedir(dir);


    printf("Do you want to delete all files in the directory? (y/n): ");
    scanf(" %c", &choice);

    if (choice == 'y' || choice == 'Y') {

        dir = opendir(".");
        if (dir == NULL) {
            perror("Unable to open directory");
            return 1;
        }

        while ((entry = readdir(dir)) != NULL) {
            if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
                continue;


            if (remove(entry->d_name) == 0) {
                printf("File %s deleted success.\n", entry->d_name);
            } else {
                perror("Failed delete file");
            }
        }

        closedir(dir);
    }

    return 0;
}

