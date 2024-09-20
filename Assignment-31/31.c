#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <pthread.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>

int main() {

    sem_t *binarySemap = sem_open("/binary_semaphore", O_CREAT | O_EXCL, 0644, 1);

    if (binarySemap == SEM_FAILED) {
        perror("Error creating binary semaphore");
        exit(EXIT_FAILURE);
    }
    printf("Binary semaphore created and initialised to 1\n");

    sem_t *countingSemap = sem_open("/counting_semaphore", O_CREAT | O_EXCL, 0644, 10);
    if (countingSemap == SEM_FAILED) {
        perror("Error creating counting semaphore");
        sem_close(binarySemap);
        sem_unlink("/binary_semaphore");
        exit(EXIT_FAILURE);
    }
    printf("Counting semaphore initialised to 10\n");

    sem_close(binarySemap);
    sem_close(countingSemap);
    sem_unlink("/binary_semaphore");
    sem_unlink("/counting_semaphore");

    return 0;
}
