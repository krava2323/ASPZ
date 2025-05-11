#include <stdlib.h>
#include <stdio.h>

int main() {
    size_t alignment = 64;      
    size_t size = 1024;         

    void *ptr = aligned_alloc(alignment, size);
    if (!ptr) {
        perror("aligned_alloc failed");
        return 1;
    }

    printf("Memory allocated at address: %p\n", ptr);


    if ((uintptr_t)ptr % alignment == 0) {
        printf("Pointer is properly aligned to %zu bytes\n", alignment);
    } else {
        printf("Pointer is NOT properly aligned!\n");
    }

    free(ptr);
    return 0;
}

