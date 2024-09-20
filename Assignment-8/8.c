============================================================================
Name : 8.c
Author : Juhi Rajani
Description :  8. Write a separate program using signal system call to 
                catch the following signals.
                a. SIGSEGV
                b. SIGINT
                c. SIGFPE
                d. SIGALRM (use alarm system call)
                e. SIGALRM (use setitimer system call)
                f. SIGVTALRM (use setitimer system call)
                g. SIGPROF (use setitimer system call)
Date: 20th Sept, 2024.
============================================================================


#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <sys/time.h>
#include <string.h>
#include <setjmp.h>

volatile sig_atomic_t signal_caught = 0;
sigjmp_buf jump_buffer;

void signal_handler(int signum) {
    signal_caught = signum;
    printf("Caught signal %d (%s)\n", signum, strsignal(signum));
    siglongjmp(jump_buffer, 1);
}

void test_signal(int signum, const char* signal_name, void (*trigger_func)()) {
    printf("\nTesting %s (%d)\n", signal_name, signum);
    signal_caught = 0;
    signal(signum, signal_handler);
    
    if (sigsetjmp(jump_buffer, 1) == 0) {
        trigger_func();
        printf("Failed to catch %s\n", signal_name);
    } else {
        if (signal_caught == signum) {
            printf("%s was successfully caught\n", signal_name);
        } else {
            printf("Unexpected signal caught: %d\n", signal_caught);
        }
    }
    
    signal(signum, SIG_DFL);  
}

void trigger_sigsegv() {
    int *ptr = NULL;
    *ptr = 10; 
}

void trigger_sigfpe() {
    raise(SIGFPE);  
}

void trigger_sigalrm() {
    alarm(1);
    sleep(2);  
}

void trigger_sigvtalrm() {
    struct itimerval it_val;
    it_val.it_value.tv_sec = 1;
    it_val.it_value.tv_usec = 0;
    it_val.it_interval.tv_sec = 0;
    it_val.it_interval.tv_usec = 0;
    setitimer(ITIMER_VIRTUAL, &it_val, NULL);
    while(1) {
    }
}

void trigger_sigprof() {
    struct itimerval it_val;
    it_val.it_value.tv_sec = 1;
    it_val.it_value.tv_usec = 0;
    it_val.it_interval.tv_sec = 0;
    it_val.it_interval.tv_usec = 0;
    setitimer(ITIMER_PROF, &it_val, NULL);
    while(1) {
    }
}

void trigger_sigint() {
    pause();
}

int main() {
    test_signal(SIGSEGV, "SIGSEGV", trigger_sigsegv);
    test_signal(SIGFPE, "SIGFPE", trigger_sigfpe);
    test_signal(SIGALRM, "SIGALRM (alarm)", trigger_sigalrm);
    test_signal(SIGVTALRM, "SIGVTALRM", trigger_sigvtalrm);
    test_signal(SIGPROF, "SIGPROF", trigger_sigprof);

    printf("\nTo test SIGINT press Ctrl+C\n");
    test_signal(SIGINT, "SIGINT", trigger_sigint);

    printf("\nAll signals tested.\n");
    return 0;
}