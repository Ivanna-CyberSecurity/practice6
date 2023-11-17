#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>

int iterations;
int min_num;
int max_num;
int target_num;
int exit_signal = 0;

struct ThreadData {
    char *identifier;
    char *msg;
};

void *thread_func(void *arg) {
    struct ThreadData *data = (struct ThreadData *)arg;
    for (int i = 1; i <= iterations; i++) {
        if (exit_signal) {
            printf("Thread %s. Exiting due to signal.\n", data->identifier);
            pthread_exit(NULL);
        }
        printf("Thread %s. %s %d\n", data->identifier, data->msg, i);
        int random = min_num + rand() % (max_num - min_num + 1);
        printf("Thread %s. Random Number: %d\n", data->identifier, random);
        if (random == target_num) {
            printf("Thread %s. Received %d, setting exit signal.\n", data->identifier, target_num);
            exit_signal = 1;
        }
        sleep(1);
    }
    pthread_exit(NULL);
}

int main() {
    pthread_t threads[2];
    struct ThreadData thread_data[] = {
            {"One", "Msg1"},
            {"Two", "Msg2"}
    };
    printf("Enter the number of iterations: ");
    scanf("%d", &iterations);
    printf("Enter the minimum number: ");
    scanf("%d", &min_num);
    printf("Enter the maximum number: ");
    scanf("%d", &max_num);
    printf("Enter the target number: ");
    scanf("%d", &target_num);
    srand(time(NULL));
    for (int i = 0; i < 2; i++) {
        if (pthread_create(&threads[i], NULL, thread_func, &thread_data[i]) != 0) {
            perror("pthread_create");
            exit(1);
        }
    }
    for (int i = 0; i < 2; i++) {
        if (pthread_join(threads[i], NULL) != 0) {
            perror("pthread_join");
            exit(1);
        }
    }
    printf("Main Thread. All threads have completed.\n");
    return 0;
}