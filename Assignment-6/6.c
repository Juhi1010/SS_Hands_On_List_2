#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define NUM_THREADS 5

struct thread_data {
    int thread_id;
    char *message;
};

void *PrintMsg(void *threadarg) {
    struct thread_data *data;
    data = (struct thread_data *) threadarg;
    printf("Thread ID - %d\n", data->thread_id);
    printf("Message - %s\n", data->message);
    pthread_exit(NULL);
}

int main() {
    pthread_t threads[NUM_THREADS];
    struct thread_data td[NUM_THREADS];
    int rc, i;

    for (i = 0; i < NUM_THREADS; i++) {
        printf("creating thread %d\n", i);
        td[i].thread_id = i;
        td[i].message = "I am thread";
        rc = pthread_create(&threads[i], NULL, PrintMsg, &td[i]);
        if (rc) {
            printf("Error: unable to create thread\n");
            exit(-1);
        }
    }

    pthread_exit(NULL);
}