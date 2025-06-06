#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>


void create_process_level(int current_level, int max_level) {

    printf("Рівень %d: Процес PID=%d, Батьківський PID=%d\n",
           current_level, getpid(), getppid());
    
   
    fflush(stdout);


    if (current_level >= max_level) {
        return;
    }


    for (int i = 0; i < 2; i++) {
        pid_t pid = fork();

        if (pid < 0) {

            perror("fork failed");
            exit(1);
        }

        if (pid == 0) {
          
            create_process_level(current_level + 1, max_level);
            

            
            exit(0);
        }
    }

   
    for (int i = 0; i < 2; i++) {
        wait(NULL);
    }
}

int main() {
   
    create_process_level(1, 3);
    return 0;
}
