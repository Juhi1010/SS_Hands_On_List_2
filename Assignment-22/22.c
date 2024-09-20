============================================================================
Name : 22.c
Author : Juhi Rajani
Description :  22. Write a program to wait for data to be written into FIFO 
                within 10 seconds, use select system call with FIFO.
Date: 18th Sept, 2024.
============================================================================

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/select.h>
#include <string.h>

int main() {

    int fifo;
    fd_set readd;
    struct timeval timeout;
    char msg[120];

    fifo = open("my_fifo", O_RDONLY | O_NONBLOCK);
    if (fifo == -1) {
        perror("Failed to open fifo");
        exit(EXIT_FAILURE);
    }

    FD_ZERO(&readd);
    FD_SET(fifo, &readd);

    timeout.tv_sec = 10;
    timeout.tv_usec = 0;

    printf("Waiting for data 10 secs to get the data\n");

    int isSuccess = select(fifo + 1, &readd, NULL, NULL, &timeout);

    if (isSuccess == -1) {
        perror("Error");
        close(fifo);
        exit(EXIT_FAILURE);
    } 
    else if (isSuccess == 0) {
        printf("Data not received in 10 secs\n");
    } 
    else {
        if (FD_ISSET(fifo, &readd)) {
            ssize_t bytesRead = read(fifo, msg, sizeof(msg) - 1);
            if (bytesRead > 0) {
                msg[bytesRead] = '\0'; 
                printf("Received - %s", msg);
            }
        }
    }

    close(fifo);
    return 0;
}
