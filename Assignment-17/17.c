============================================================================
Name : 17.c
Author : Juhi Rajani
Description :  17. Write a program to execute ls -l | wc.
                a. use dup
                b. use dup2
                c. use fcntl
Date: 17th Sept, 2024.
============================================================================

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <string.h>

void child_proc_ls(int fd[2], const char* method) {

    close(fd[0]);  

    if (strcmp(method, "dup") == 0) {
        dup(fd[1]);
        close(fd[1]);
    } else if (strcmp(method, "dup2") == 0) {
        dup2(fd[1], STDOUT_FILENO);
        close(fd[1]);
    } else if (strcmp(method, "fcntl") == 0) {
        fcntl(fd[1], F_SETFD, FD_CLOEXEC);
        fcntl(fd[1], F_DUPFD, STDOUT_FILENO);
        close(fd[1]);
    }

    execlp("ls", "ls", "-l", NULL);
    perror("execlp ls");
    exit(1);
}

void child_proc_wc(int fd[2], const char* method) {

    close(fd[1]);  

    if (strcmp(method, "dup") == 0) {
        dup(fd[0]);
        close(fd[0]);
    } else if (strcmp(method, "dup2") == 0) {
        dup2(fd[0], STDIN_FILENO);
        close(fd[0]);
    } else if (strcmp(method, "fcntl") == 0) {
        fcntl(fd[0], F_SETFD, FD_CLOEXEC);
        fcntl(fd[0], F_DUPFD, STDIN_FILENO);
        close(fd[0]);
    }

    execlp("wc", "wc", NULL);
    perror("execlp wc");
    exit(1);
}


void executePipe(const char* method) {
    int fd[2];
    pid_t pid1, pid2;

    if (pipe(fd) == -1) {
        perror("pipe");
        exit(1);
    }

    pid1 = fork();
    if (pid1 == -1) {
        perror("fork");
        exit(1);
    }

    if (pid1 == 0) {
        child_proc_ls(fd, method);
    }

    pid2 = fork();
    if (pid2 == -1) {
        perror("fork");
        exit(1);
    }

    if (pid2 == 0) {
        child_proc_wc(fd, method);
    }

    close(fd[0]);
    close(fd[1]);
    waitpid(pid1, NULL, 0);
    waitpid(pid2, NULL, 0);
}

int main(int argc, char *argv[]) {
    if (argc != 2 || (strcmp(argv[1], "dup") != 0 && 
                      strcmp(argv[1], "dup2") != 0 && 
                      strcmp(argv[1], "fcntl") != 0)) {
        printf("Method can be: dup, dup2, or fcntl\n");
        exit(1);
    }

    executePipe(argv[1]);
    return 0;
}
