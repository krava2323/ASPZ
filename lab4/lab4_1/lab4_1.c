#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int main() {
    size_t size = (size_t)1 << 63; 
    void* ptr = malloc(size);

    if (ptr == NULL) {
        perror("malloc failed");
    } else {
        printf("malloc succeeded\n");
        free(ptr);
    }

    return 0;
}

