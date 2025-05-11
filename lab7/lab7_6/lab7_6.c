#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include <sys/stat.h>


typedef struct {
    char **names;
    int count;
    int capacity;
} DirList;


void add_to_list(DirList *list, const char *name) {
    if (list->count == list->capacity) {
        list->capacity = (list->capacity == 0) ? 10 : list->capacity * 2;
        list->names = realloc(list->names, list->capacity * sizeof(char *));
    }
    list->names[list->count++] = strdup(name);
}


int compare(const void *a, const void *b) {
    return strcmp(*(char **)a, *(char **)b);
}

int main() {
    DIR *dir = opendir(".");
    struct dirent *entry;
    struct stat statbuf;
    DirList list = {NULL, 0, 0};

    if (!dir) {
        perror("opendir");
        return 1;
    }


    while ((entry = readdir(dir)) != NULL) {
        if (entry->d_type == DT_DIR) {

            if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
                continue;
            add_to_list(&list, entry->d_name);
        }
    }
    closedir(dir);


    qsort(list.names, list.count, sizeof(char *), compare);


    printf("Subdirectories in alphabetical order:\n");
    for (int i = 0; i < list.count; ++i) {
        printf("%s\n", list.names[i]);
        free(list.names[i]);
    }
    free(list.names);

    return 0;
}
