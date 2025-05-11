#include <stdio.h>
#include <stdlib.h>

int main() {

    void *ptr1 = realloc(NULL, 100);
    if (ptr1) {
        printf("realloc(NULL, 100) succeeded: %p\n", ptr1);
        free(ptr1);
    } else {
        printf("realloc(NULL, 100) failed\n");
    }


    void *ptr2 = malloc(50);
    if (!ptr2) {
        perror("malloc failed");
        return 1;
    }

    void *ptr3 = realloc(ptr2, 0); 
    printf("realloc(ptr, 0) returned: %p\n", ptr3);
  

    return 0;
}

