============================================================================
Name : 30.c
Author : Juhi Rajani
Description :  30. Write a program to create a shared memory.
                a. write some data to the shared memory
                b. attach with O_RDONLY and check whether you are able to overwrite.
                c. detach the shared memory
                d. remove the shared memory
Date: 20th Sept, 2024.
============================================================================

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>

int main() {

    int shmId;
    char *dt;

    shmId = shmget(123, 512, IPC_CREAT | 0666);
    if (shmId == -1) {
        perror("shmget");
        exit(1);
    }

    dt = shmat(shmId, NULL, 0);
    if (dt == (char *)(-1)) {
        perror("shmat");
        exit(1);
    }

    strcpy(dt, "I am shared memory data");
    printf("Data written to shared memory - %s\n", dt);

    if (shmdt(dt) == -1) {
        perror("shmdt");
        exit(1);
    }

    dt = shmat(shmId, NULL, SHM_RDONLY);
    if (dt == (char *)(-1)) {
        perror("shmat");
        exit(1);
    }

    // the output ss attached has both outputs - this line commented and uncommented
    // strcpy(dt, "Trying to overwrite");

    printf("Read-only mode..cannot overwrite\n");

    if (shmdt(dt) == -1) {
        perror("shmdt");
        exit(1);
    }

    if (shmctl(shmId, IPC_RMID, NULL) == -1) {
        perror("shmctl");
        exit(1);
    }

    return 0;
}
