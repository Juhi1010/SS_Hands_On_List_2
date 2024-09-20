============================================================================
Name : 19e.c
Author : Juhi Rajani
Description :  19. Create a FIFO file by
                a. mknod command
                b. mkfifo command
                c. use strace command to find out, which command (mknod or mkfifo) is better.
                c. mknod system call
                d. mkfifo library function
Date: 20th Sept, 2024.
============================================================================

#include <stdio.h>
#include <sys/stat.h>

int main() {
    if (mkfifo("fifo4", 0666) == -1) {
        perror("mkfifo");
        return 1;
    }
    return 0;
}
