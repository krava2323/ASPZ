#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {

    struct timespec start, end;

    clock_gettime(CLOCK_MONOTONIC, &start);

    long long sum = 0;
    for (long long i = 0; i < 1000000000; i++) {
        sum += i;
    }

    clock_gettime(CLOCK_MONOTONIC, &end);

    long long diff = (end.tv_sec - start.tv_sec) * 1000 + (end.tv_nsec - start.tv_nsec) / 1000000;

    printf("Execution time: %lld milliseconds\n", diff);

    return 0;
}

