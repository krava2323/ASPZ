#include <stdio.h>
#include <stdlib.h>

void recurse(int depth) {
    char buffer[1024]; 
    printf("Recursion depth: %d\n", depth);
    buffer[0] = depth % 256; 
    recurse(depth + 1);    
}

int main() {
    recurse(1);
    return 0;
}

