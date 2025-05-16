#include <stdio.h>
#include <stdlib.h>

int main() {
    printf(" read /etc/shadow \n");

    int ret = system("sudo cat /etc/shadow");

    if (ret != 0) {
        fprintf(stderr, "Failed read /etc/shadow. \n");
        return 1;
    }

    return 0;
}

