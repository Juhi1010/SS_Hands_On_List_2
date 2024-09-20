============================================================================
Name : 23.c
Author : Juhi Rajani
Description :  23. Write a program to print the maximum number of files can 
                be opened within a process and size of a pipe (circular buffer).
Date: 18th Sept, 2024.
============================================================================

#include <stdio.h>
#include <unistd.h>
#include <sys/resource.h>
#include <fcntl.h>

int main() {
    struct rlimit rlim;
    long pipe_buf_size;
    
    if (getrlimit(RLIMIT_NOFILE, &rlim) == 0) {
        printf("Maximum number of open files:\n");
        printf("  Soft limit - %ld\n", (long)rlim.rlim_cur);
        printf("  Hard limit - %ld\n", (long)rlim.rlim_max);
    } else {
        perror("getrlimit");
    }

    pipe_buf_size = fpathconf(STDOUT_FILENO, _PC_PIPE_BUF);
    if (pipe_buf_size != -1) {
        printf("Pipe buffer size: %ld bytes\n", pipe_buf_size);
    } else {
        perror("fpathconf");
    }

    return 0;
}