#include <stdio.h>
#include <stdlib.h>

int main() {
    printf("User \n");
    int ret1 = system("whoami");

    if (ret1 == -1) {
        perror("Error");
        return 1;
    }

    printf("\n Info \n");
    int ret2 = system("id");

    if (ret2 == -1) {
        perror("Error id");
        return 1;
    }

    return 0;
}

