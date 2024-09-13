#include <stdio.h>
#include <signal.h>
#include <unistd.h>

void sigintIgnore(int signum) {
    printf(" SIGINT signal is being ignored\n");
}

int main() {

    if (signal(SIGINT, sigintIgnore)==SIG_ERR) {
        perror("Unable to call ignore function properly");
        return 1;
    }
    printf("SIGINT is in ignore mode, pressing a key won't interrupt\n");
    sleep(15); 

    if (signal(SIGINT, SIG_DFL)==SIG_ERR) {
        perror("Unable to reset sigint to default\n");
        return 1;
    }
    printf("SIGINT signal handling in default mode\n");
    sleep(15); 

    return 0;
}
