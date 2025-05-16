#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <errno.h>

int main() {
    int pipefd[2];
    char buffer[4096]; 
    memset(buffer, 'X', sizeof(buffer));


    if (pipe(pipefd) == -1) {
        perror("pipe");
        return 1;
    }


    int flags = fcntl(pipefd[1], F_GETFL);
    fcntl(pipefd[1], F_SETFL, flags | O_NONBLOCK);


    ssize_t count = write(pipefd[1], buffer, sizeof(buffer));

    if (count == -1) {
        perror("write");
    } else if (count < sizeof(buffer)) {
        printf( erite  %zd bytes with %zu\n", count, sizeof(buffer));
    } else {
        printf(" write %zd bytes\n", count);
    }

    close(pipefd[0]);
    close(pipefd[1]);

    return 0;
}

