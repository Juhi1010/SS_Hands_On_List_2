============================================================================
Name : first.c
Author : Juhi Rajani
Description :  13. Write two programs: first program is waiting to catch SIGSTOP signal, 
                the second program will send the signal (using kill system call). 
                Find out whether the first program is able to catch the signal or not.
Date: 16th Sept, 2024.
============================================================================

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Error passing arguments");
        exit(1);
    }

    pid_t pid = atoi(argv[1]);
    
    printf("Sending SIGSTOP to process %d\n", pid);
    
    if (kill(pid, SIGSTOP) == -1) {
        perror("Failed to send SIGSTOP");
        exit(1);
    }
    
    printf("SIGSTOP sent successfully\n");
    
    return 0;
}
