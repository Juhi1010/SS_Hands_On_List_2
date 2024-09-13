#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

void sigintIgnore(int signum) {
    printf(" SIGINT is being ignored\n");
}

int main() {

    struct sigaction s;
    s.sa_handler = sigintIgnore;
    s.sa_flags = 0;            
    sigemptyset(&s.sa_mask);  

    if (sigaction(SIGINT, &s, NULL)==-1) {
        perror("sigaction failed to call ignore function properly");
        return 1;
    }
    printf("SIGINT is in ignore mode, pressing a key won't interrupt\n");
    sleep(10); 

    s.sa_handler = SIG_DFL;   
    if (sigaction(SIGINT, &s, NULL)==-1) {
        perror("Unable to reset sigint to default\n");
        return 1;
    }

    printf("SIGINT signal handling in default mode\n");
    sleep(10); 

    return 0;
}
