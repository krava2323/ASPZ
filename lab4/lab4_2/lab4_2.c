#include <stdio.h>
#include <stdlib.h>

int main() {
    int xa = 100000;
    int xb = 30000;
    int num = xa * xb;  

    printf("xa = %d, xb = %d\n", xa, xb);
    printf("num (as int) = %d\n", num);
    printf("num (as size_t) = %zu\n", (size_t)num);

    void* ptr = malloc(num);
    if (ptr == NULL) {
        perror("malloc failed");
    } else {
        printf("malloc succeeded\n");
        free(ptr);
    }

    return 0;
}
