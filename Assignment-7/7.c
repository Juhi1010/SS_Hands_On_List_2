#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define NUM_THREADS 5

struct thread_data {
    int thread_id;
    char *message;
};

void *PrintMsg(void *threadarg) {
    pthread_t thread_id = pthread_self();
    printf("Thread ID - %lu\n", (unsigned long)thread_id);
    return NULL;
}

int main() {
    pthread_t threads[NUM_THREADS];
    struct thread_data td[NUM_THREADS];
    int rc, i;

    for (i = 0; i < NUM_THREADS; i++) {
        printf("creating thread %d\n", i);
        td[i].thread_id = i;
        rc = pthread_create(&threads[i], NULL, PrintMsg, &td[i]);
        if (rc) {
            printf("Error: unable to create thread\n");
            exit(-1);
        }
    }

    pthread_exit(NULL);
}