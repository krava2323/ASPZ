#include <stdio.h>
#include <stdlib.h>

void secret_function() {
    printf("You have successfully exploited the buffer overflow!\n");
}

void vulnerable_function() {
    char buffer[64];  
    printf("Enter some text: ");
    gets(buffer);  
    printf("You entered: %s\n", buffer);
}

int main() {
    vulnerable_function();
    return 0;
}
