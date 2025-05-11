#include <stdio.h>
#include <stdlib.h>
#include <time.h>

double generate_random_0_1() {
    return (double)rand() / (double)RAND_MAX;
}

double generate_random_0_n(double n) {
    return generate_random_0_1() * n;
}
int main() {

    srand(time(NULL));  


    printf("Random numbers between 0.0 and 1.0:\n");
    for (int i = 0; i < 5; i++) {
        printf("%f\n", generate_random_0_1());
    }


    double n;
    printf("Enter a value for n: ");
    scanf("%lf", &n);  
    printf("Random numbers between 0.0 and %f:\n", n);
    for (int i = 0; i < 5; i++) {
        printf("%f\n", generate_random_0_n(n));
    }

    return 0;
}
