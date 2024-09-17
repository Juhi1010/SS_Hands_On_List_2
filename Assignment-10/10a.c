============================================================================
Name : 10a.c
Author : Juhi Rajani
Description :  10. Write a separate program using sigaction system call to
                   catch the following signals.
                    a. SIGSEGV
                    b. SIGINT
                    c. SIGFPE
Date: 16th Sept, 2024.
============================================================================

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

void sigsegv_handler(int signum, siginfo_t *info, void *context) {
    printf("Caught signal %d - SIGSEGV (Segmentation fault)\n", signum);    
    exit(EXIT_FAILURE);
}

int main() {
    struct sigaction s;

    s.sa_flags = SA_SIGINFO;   
    s.sa_sigaction = sigsegv_handler;
    sigemptyset(&s.sa_mask);  

    if (sigaction(SIGSEGV, &s, NULL) == -1) {
        perror("sigaction(SIGSEGV) failed");
        return 1;
    }

    printf("Generating segmentation fault\n");
    int *p = NULL;
    *p = 10; 
    pause();

    return 0;
}
