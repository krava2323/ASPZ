#include <stdio.h>
#include <stdlib.h>

#define LINES_PER_PAGE 20
#define MAX_LINE 1024

void display_file(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror(filename);
        return;
    }

    char line[MAX_LINE];
    int line_count = 0;

    while (fgets(line, MAX_LINE, file)) {
        printf("%s", line);
        line_count++;

        if (line_count >= LINES_PER_PAGE) {
            printf("\n-- Press ENTER to continue --");
            while (getchar() != '\n');
            line_count = 0;
        }
    }

    fclose(file);
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <file1> [file2 ]\n", argv[0]);
        return 1;
    }

    for (int i = 1; i < argc; i++) {
        printf("\nDisplaying: %s \n", argv[i]);
        display_file(argv[i]);
    }

    return 0;
}

