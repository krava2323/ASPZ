#include <stdio.h>

void recurse(int depth) {
    char buffer[1024];  
    buffer[0] = 1;      
    printf("Recursion depth: %d\n", depth);
    if (depth < 10000) {
        recurse(depth + 1);  
    }
}

int main() {
    recurse(1);
    return 0;
}

