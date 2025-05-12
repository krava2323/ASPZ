#include <stdio.h>
#include <stdlib.h>


int data_var = 10;

int bss_var;

void dummy_function() {}

int main() {
    int stack_var;
    printf("Stack top is near        : %p\n", &stack_var);

    int *heap_var = (int *)malloc(sizeof(int));
    printf("Heap is near             : %p\n", heap_var);

    printf("Initialized data is near : %p\n", &data_var);

    printf("BSS is near              : %p\n", &bss_var);

    printf("Text  is near      : %p\n", &dummy_function);

    char big_array1[10000];
    char big_array2[10000];
    printf("New stack top is near    : %p\n", &big_array2);

    free(heap_var);
    return 0;
}




