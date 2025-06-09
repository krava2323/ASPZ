#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h> 

#define SIGSTKSZ_CUSTOM (SIGSTKSZ * 2) // Розмір альтернативного стеку

volatile sig_atomic_t keep_running = 1;

void signal_handler(int signum) {
    if (signum == SIGINT) {
        printf("\nОтримано SIGINT (Ctrl+C). Завершення роботи...\n");
    } else if (signum == SIGTERM) {
        printf("\nОтримано SIGTERM. Завершення роботи...\n");
    }
    keep_running = 0; 
}

int main() {
    stack_t ss, oss; 
    struct sigaction sa; 

   
    ss.ss_sp = malloc(SIGSTKSZ_CUSTOM);
    if (ss.ss_sp == NULL) {
        perror("Не вдалося виділити пам'ять для альтернативного стеку");
        return 1;
    }
    ss.ss_size = SIGSTKSZ_CUSTOM;
    ss.ss_flags = 0; 

    if (sigaltstack(&ss, &oss) == -1) {
        perror("Не вдалося встановити альтернативний стек");
        free(ss.ss_sp);
        return 1;
    }
    printf("Альтернативний стек встановлено за адресою %p, розмір %zu байт.\n", ss.ss_sp, ss.ss_size);


    sa.sa_handler = signal_handler; 
    sigemptyset(&sa.sa_mask);      
    sa.sa_flags = SA_ONSTACK;     

    if (sigaction(SIGINT, &sa, NULL) == -1) {
        perror("Не вдалося зареєструвати обробник SIGINT");
        sigaltstack(&oss, NULL); 
        free(ss.ss_sp);
        return 1;
    }
    printf("Обробник SIGINT зареєстровано.\n");

    if (sigaction(SIGTERM, &sa, NULL) == -1) {
        perror("Не вдалося зареєструвати обробник SIGTERM");
        sigaltstack(&oss, NULL); 
        free(ss.ss_sp);
        return 1;
    }
    printf("Обробник SIGTERM зареєстровано.\n");

    printf("Програма працює. Натисніть Ctrl+C або SIGTERM ( за допомогою `kill %d`).\n", getpid());

    // Головний цикл програми
    while (keep_running) {
        printf("Основний цикл виконується...\n");
        sleep(2); 
    }

    printf("Програма завершує роботу.\n");

    if (sigaltstack(&oss, NULL) == -1) {
        perror("Не вдалося відновити старий стек");
    } else {
        printf("Старий стек відновлено.\n");
    }
    free(ss.ss_sp); 
    printf("Пам'ять альтернативного стеку звільнено.\n");

    return 0;
}
