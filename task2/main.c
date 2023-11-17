#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

struct ThreadArgs {
    char *name;
    char *str;
    int num;
};

void *thread_function(void *arg) {
    struct ThreadArgs *args = (struct ThreadArgs *)arg;
    for (int i = 1; i <= args->num; i++) {
        printf("Thread %s. %s %d\n", args->name, args->str, i);
    }
    pthread_exit(NULL);
}

int main() {
    pthread_t threads[4];
    struct ThreadArgs args[] = {
            {"A", "Str1", 3},
            {"B", "Str2", 2},
            {"C", "Str3", 4},
            {"D", "Str4", 5}
    };
    for (int i = 0; i < 4; i++) {
        if (pthread_create(&threads[i], NULL, thread_function, &args[i]) != 0) {
            perror("pthread_create");
            exit(1);
        }
    }
    for (int i = 0; i < 4; i++) {
        if (pthread_join(threads[i], NULL) != 0) {
            perror("pthread_join");
            exit(1);
        }
    }
    return 0;
}