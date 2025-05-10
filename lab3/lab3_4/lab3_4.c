#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <signal.h>

#define LIMIT_CPU_SECONDS 100 

void cpu_limit_exceeded(int signum) {
    printf("\nЛіміт часу перевищено! Завершення програми.\n");
    exit(1);
}


void shuffle(int *array, int n) {
    for (int i = n - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        int temp = array[i];
        array[i] = array[j];
        array[j] = temp;
    }
}


void pick_numbers(int *source, int source_size, int count) {
    shuffle(source, source_size);
    for (int i = 0; i < count; i++) {
        printf("%d ", source[i]);
    }
    printf("\n");
}

int main() {

    signal(SIGXCPU, cpu_limit_exceeded);


    struct rlimit rl;
    rl.rlim_cur = LIMIT_CPU_SECONDS;
    rl.rlim_max = LIMIT_CPU_SECONDS + 1; 
    if (setrlimit(RLIMIT_CPU, &rl) != 0) {
        perror("Не вдалося встановити ліміт часу ");
        return 1;
    }

    srand(time(NULL));

    int numbers_49[49];
    int numbers_36[36];


    for (int i = 0; i < 49; i++) {
        numbers_49[i] = i + 1;
    }
    for (int i = 0; i < 36; i++) {
        numbers_36[i] = i + 1;
    }

    printf("Лотерея 7 з 49: ");
    pick_numbers(numbers_49, 49, 7);

    printf("Лотерея 6 з 36: ");
    pick_numbers(numbers_36, 36, 6);

    return 0;
}

