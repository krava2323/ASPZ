
#include <stdio.h>
#include <stdlib.h>

int main() {
    int *ptr = (int *)malloc(sizeof(int));  
    if (ptr == NULL) {
        perror("malloc failed");
        return 1;
    }

    *ptr = 42;  
    printf("Before free: %d\n", *ptr);

    free(ptr);  

    *ptr = 99;  
    printf("After free: %d\n", *ptr); 

    return 0;
}
