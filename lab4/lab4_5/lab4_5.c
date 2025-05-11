#include <stdlib.h>
#include <stdio.h>

int main() {
    size_t big_size = (size_t)1024 * 1024 * 1024 * 8; 
    void *ptr = malloc(1024);
    if (!ptr) {
        perror("initial malloc failed");
        return 1;
    }

    printf("Initial malloc succeeded: %p\n", ptr);

    void *tmp = realloc(ptr, big_size);  
    if (!tmp) {
        perror("realloc failed");

        free(ptr);
    } else {
        printf("Realloc succeeded: %p\n", tmp);
        free(tmp);
    }

    return 0;
}

