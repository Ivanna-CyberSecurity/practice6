#include <stdio.h>
#include <pthread.h>

unsigned long long computeCatalan(int n) {
    if (n <= 1) {
        return 1;
    }
    unsigned long long result = 0;
    for (int i = 0; i < n; i++) {
        result += computeCatalan(i) * computeCatalan(n - i - 1);
    }
    return result;
}

int isPrime(int number) {
    if (number <= 1) {
        return 0;
    }
    for (int i = 2; i * i <= number; i++) {
        if (number % i == 0) {
            return 0;
        }
    }
    return 1;
}

struct ThreadArgs {
    int inputN;
    unsigned long long catalanRes;
    int primeCount;
};

void *threadFunc(void *arg) {
    struct ThreadArgs *args = (struct ThreadArgs *)arg;
    for (int i = 0; i <= args->inputN; i++) {
        args->catalanRes = computeCatalan(i);
        printf("Thread: Calculated Catalan Number for N = %d: %llu\n", i, args->catalanRes);
        args->primeCount = 0;  
        for (int j = 2; j <= args->catalanRes; j++) {
            if (isPrime(j)) {
                args->primeCount++;
            }
        }
        printf("Thread: Count of Prime Numbers for N = %d: %d\n", i, args->primeCount);
    }
    pthread_exit(NULL);
}

int main() {
    pthread_t thread;
    struct ThreadArgs arguments;
    printf("Enter the number 'N' of Catalan Numbers to calculate: ");
    scanf("%d", &arguments.inputN);
    pthread_create(&thread, NULL, threadFunc, &arguments);
    pthread_join(thread, NULL);
    printf("Last calculated Catalan Number: %llu\n", arguments.catalanRes);
    printf("Count of Prime Numbers up to last calculated Catalan Number: %d\n", arguments.primeCount);
    return 0;
}