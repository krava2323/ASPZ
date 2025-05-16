#include <stdio.h>
#include <unistd.h>

int main() {
    int pid;
    pid = fork();

    if (pid == -1) {

        perror("fork");
        return 1;
    }

    printf("pid = %d (from process %d)\n", pid, getpid());
    return 0;
}

