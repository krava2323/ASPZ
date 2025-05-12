#include <stdio.h>
#include <unistd.h>

void bar() {
    printf("Inside bar()\n");
}

void foo() {
    printf("Inside foo()\n");
    bar();  
}

int main() {
    printf("Start main()\n");
    foo();  
    printf("Back in main()\n");
    pause(); 
    return 0;
}
