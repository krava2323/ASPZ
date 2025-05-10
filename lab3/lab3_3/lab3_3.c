#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define FILENAME "dice_rolls.txt"
#define MAX_FILE_SIZE 100  

long get_file_size(FILE *file) {
    long current_pos = ftell(file);
    fseek(file, 0L, SEEK_END);
    long size = ftell(file);
    fseek(file, current_pos, SEEK_SET);
    return size;
}

int roll_dice() {
    return (rand() % 6) + 1;
}

int main() {
    FILE *file;
    srand(time(NULL)); 

    file = fopen(FILENAME, "a");
    if (file == NULL) {
        perror("Не вдалося відкрити файл");
        return 1;
    }

    printf("Починаємо кидати кубик і записувати результати у файл '%s'...\n", FILENAME);

    while (1) {
        if (get_file_size(file) >= MAX_FILE_SIZE) {
            printf("Досягнуто максимального розміру файлу. Завершення програми.\n");
            break;
        }

        int roll = roll_dice();
        fprintf(file, "Кидок: %d\n", roll);
        fflush(file); 
    }

    fclose(file);
    return 0;
}

