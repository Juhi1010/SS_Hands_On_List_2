============================================================================
Name : second.c
Author : Juhi Rajani
Description :  13. Write two programs: first program is waiting to catch SIGSTOP signal, 
                the second program will send the signal (using kill system call). 
                Find out whether the first program is able to catch the signal or not.
Date: 16th Sept, 2024.
============================================================================

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

void signalHandler(int signum) {
    printf("Caught signal %d\n", signum);
}

int main() {

    printf("Process ID: %d\n", getpid());
    
    // Attempt to set up signal handler for SIGSTOP
    if (signal(SIGSTOP, signalHandler) == SIG_ERR) {
        perror("Unable to catch SIGSTOP");
    } else {
        printf("Signal handler set successfully\n");
    }
        
    while(1) {
        sleep(2);
    }
    
    return 0;
}
