#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

void *child(void *arg) {
    int count;
    for (count = 1; count <= 10; count++) {
        printf("Child Thread. Iteration: %d\n\n", count);
        sleep(2);
    }
    pthread_exit(NULL);
}

int main() {
    pthread_t child_thread;
    int count;
    if (pthread_create(&child_thread, NULL, child, NULL) != 0) {
        perror("pthread_create");
        exit(1);
    }
    for (count = 1; count <= 10; count++) {
        printf("Main Thread. Iteration: %d\n\n", count);
        sleep(2);
    }
    if (pthread_join(child_thread, NULL) != 0) {
        perror("pthread_join");
        exit(1);
    }
    return 0;
}