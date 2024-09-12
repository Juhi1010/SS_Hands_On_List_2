============================================================================
Name : 1b.c
Author : Juhi Rajani
Description :  1. Write a separate program (for each time domain) to set a interval 
               timer in 10sec and 10micro second
                a. ITIMER_REAL
                b. ITIMER_VIRTUAL
                c. ITIMER_PROF
Date: 11th Sept, 2024.
============================================================================

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/time.h>

sig_atomic_t flagg = 0;

void set_flag(int signum) {
    flagg = 1;
}

int main() {
    struct itimerval timer;
    struct sigaction s;

    s.sa_handler = &set_flag;
    sigaction(SIGVTALRM, &s, NULL);

    timer.it_value.tv_sec = 10;     // 10 seconds
    timer.it_value.tv_usec = 10;    // 10 microseconds
    timer.it_interval = timer.it_value;

    if (setitimer(ITIMER_VIRTUAL, &timer, NULL) == -1) {
        perror("Error setting timer");
        exit(1);
    }

    printf("ITIMER_VIRTUAL timer set for 10 seconds and 10 microseconds\n");

    while (1) {
        if (flagg) {
            printf("Timer expired\n");
            flagg = 0;
        }
    }
    return 0;
}