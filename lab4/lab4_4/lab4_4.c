
#include <stdlib.h>
#include <stdio.h>

int main() {
    void *ptr = NULL;
    for (int i = 0; i < 3; i++) {
        ptr = malloc(100);
        if (!ptr) {
            perror("malloc failed");
            exit(1);
        }

        printf("Iteration %d: ptr = %p\n", i, ptr);

        free(ptr);   
        ptr = NULL;  
    }
    return 0;
}

