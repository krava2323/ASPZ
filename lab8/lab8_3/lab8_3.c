#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>


int compare_ints(const void *a, const void *b) {
    int x = *(const int*)a;
    int y = *(const int*)b;
    return (x > y) - (x < y);  
}


void generate_array(int *arr, int size, const char *type) {
    if (strcmp(type, "random") == 0) {
        for (int i = 0; i < size; i++)
            arr[i] = rand() % 10000;
    } else if (strcmp(type, "sorted") == 0) {
        for (int i = 0; i < size; i++)
            arr[i] = i;
    } else if (strcmp(type, "reversed") == 0) {
        for (int i = 0; i < size; i++)
            arr[i] = size - i;
    } else if (strcmp(type, "same") == 0) {
        for (int i = 0; i < size; i++)
            arr[i] = 42;
    } else if (strcmp(type, "alternating") == 0) {
        for (int i = 0; i < size; i++)
            arr[i] = (i % 2 == 0) ? 1 : 10000;
    }
}


int is_sorted(const int *arr, int size) {
    for (int i = 1; i < size; i++) {
        if (arr[i-1] > arr[i]) return 0;
    }
    return 1;
}


double time_qsort(int *arr, int size) {
    clock_t start = clock();
    qsort(arr, size, sizeof(int), compare_ints);
    clock_t end = clock();
    return (double)(end - start) / CLOCKS_PER_SEC;
}


void test_case(const char *label, int size) {
    int *arr = malloc(size * sizeof(int));
    if (!arr) {
        printf("Memory allocation failed.\n");
        return;
    }

    generate_array(arr, size, label);

    double elapsed = time_qsort(arr, size);

    int correct = is_sorted(arr, size);
    printf("Test: %-12s | Size: %6d | Time: %.6f s | Sorted: %s\n",
           label, size, elapsed, correct ? "Yes" : "No");

    free(arr);
}

int main() {
    srand(time(NULL));

    const char *types[] = {
        "random", "sorted", "reversed", "same", "alternating"
    };

    int sizes[] = {1000, 10000, 50000};

    for (int i = 0; i < sizeof(sizes)/sizeof(int); i++) {
        for (int j = 0; j < sizeof(types)/sizeof(types[0]); j++) {
            test_case(types[j], sizes[i]);
        }
        printf("-----------------------------------------------------\n");
    }

    return 0;
}

