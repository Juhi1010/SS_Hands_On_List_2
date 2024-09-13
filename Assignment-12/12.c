#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <signal.h>

int main() {

    pid_t pid = fork();

    if (pid < 0) {
        perror("Fork failed");
        exit(1);
    } 

    else if (pid == 0) {
        printf("Child process PID - %d created\n", getpid());
        printf("Parent PID - %d\n", getppid());
        
        sleep(1);
        
        printf("Child sending SIGKILL to parent PID - %d\n", getppid());
        
        if (kill(getppid(), SIGKILL) == -1) {
            perror("Failed to send SIGKILL to parent");
            exit(1);
        }
        
        sleep(1);
        
        printf("Parent PID - %d\n", getppid());
        printf("Child process is now an orphan\n");
        
        sleep(15);
    } 

    else {
        printf("Parent process PID - %d created child with PID - %d\n", getpid(), pid);
        while(1) {
            sleep(1);
        }
    }

    return 0;
}