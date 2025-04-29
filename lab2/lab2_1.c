#include <stdio.h>
#include <time.h>
#include <limits.h>

int main() {
    printf("Розмір time_t: %zu байт\n", sizeof(time_t));

    time_t max = (time_t)(~(1ULL << (sizeof(time_t)*8 - 1)));  // Макс. значення для signed time_t
    printf("Максимальне значення time_t: %lld\n", (long long)max);

    struct tm *t = gmtime(&max);
    if (t)
        printf("Дата та час при максимальному time_t: %s", asctime(t));
    else
        printf("Дата неможлива для перетворення (можливо переповнення).\n");

    return 0;
}
