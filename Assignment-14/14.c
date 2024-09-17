============================================================================
Name : 14.c
Author : Juhi Rajani
Description :  14. Write a simple program to create a pipe, write to the pipe, 
                read from pipe and display on the monitor.
Date: 16th Sept, 2024.
============================================================================

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main() {

    int fd[2];
    char buffer[100];
    pid_t pid;

    if (pipe(fd) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    pid = fork();

    if (pid == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (pid == 0) {  
        close(fd[1]);  

        ssize_t numOfBytes = read(fd[0], buffer, 100);
        if (numOfBytes == -1) {
            perror("read");
            exit(EXIT_FAILURE);
        }

        printf("Child process received message - %s", buffer);

        close(fd[0]);
        exit(EXIT_SUCCESS);
    } 

    else {  
        close(fd[0]);  

        const char *msg = "Hello I am parent\n";
        ssize_t numOfBytes = write(fd[1], msg, strlen(msg));
        if (numOfBytes == -1) {
            perror("write");
            exit(EXIT_FAILURE);
        }

        printf("Parent process message - %s", msg);

        close(fd[1]);
        wait(NULL); 
        exit(EXIT_SUCCESS);
    }

    return 0;
}
