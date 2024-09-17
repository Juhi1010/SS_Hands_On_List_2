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
#include <string.h>
#include <errno.h>

volatile sig_atomic_t sig_caught = 0;

void sigfpe_handler(int signum, siginfo_t *info, void *context) {
    sig_caught = 1;
    printf("Caught SIGFPE (Signal %d)\n", signum);
    
    switch (info->si_code) {
        case FPE_INTDIV:
            printf("Integer divide by zero\n");
            break;
        case FPE_INTOVF:
            printf("Integer overflow\n");
            break;
        case FPE_FLTDIV:
            printf("Floating-point divide by zero\n");
            break;
        case FPE_FLTOVF:
            printf("Floating-point overflow\n");
            break;
        case FPE_FLTUND:
            printf("Floating-point underflow\n");
            break;
        case FPE_FLTRES:
            printf("Floating-point inexact result\n");
            break;
        case FPE_FLTINV:
            printf("Invalid floating-point operation\n");
            break;
        case FPE_FLTSUB:
            printf("Subscript out of range\n");
            break;
        default:
            printf("Unknown floating-point exception\n");
    }
}

int trigger_fpe() {
    volatile int a = 1;
    volatile int b = 0;
    return a / b;
}

int main() {

    struct sigaction s;
    memset(&s, 0, sizeof(struct sigaction));
    
    s.sa_sigaction = sigfpe_handler;
    s.sa_flags = SA_SIGINFO;
    
    if (sigaction(SIGFPE, &s, NULL) == -1) {
        perror("Error setting up signal handler");
        return 1;
    }
    
    printf("Raising SIGFPE\n");
    
    
    if (raise(SIGFPE) != 0) {
        perror("Error raising SIGFPE");
        return 1;
    }
    
    return 0;
}