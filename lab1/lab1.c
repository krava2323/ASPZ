#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#define ROWS 5
#define COLS 5
#define EPSILON 0.0001 

void fillArray(float arr[ROWS][COLS]) {
    for (int i = 0; i < ROWS; ++i)
        for (int j = 0; j < COLS; ++j)
            arr[i][j] = ((float)rand() / RAND_MAX) * 100.0; 
}

void printArray(float arr[ROWS][COLS]) {
    for (int i = 0; i < ROWS; ++i) {
        for (int j = 0; j < COLS; ++j)
            printf("%6.2f ", arr[i][j]);
        printf("\n");
    }
}

void findIndices(float arr[ROWS][COLS], float value) {
    int found = 0;
    for (int i = 0; i < ROWS; ++i) {
        for (int j = 0; j < COLS; ++j) {
            if (fabs(arr[i][j] - value) < EPSILON) {
                printf("Знайдено: [%d][%d]\n", i, j);
                found = 1;
            }
        }
    }
    if (!found)
        printf("Значення %.2f не знайдено в масиві.\n", value);
}

int main() {
    srand((unsigned int)time(NULL));
    float array[ROWS][COLS];

    fillArray(array);
    printf("Масив:\n");
    printArray(array);

    float target;
    printf("\nВведіть число для пошуку: ");
    scanf("%f", &target);

    findIndices(array, target);

    return 0;
}

