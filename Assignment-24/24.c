============================================================================
Name : 24.c
Author : Juhi Rajani
Description :  24. Write a program to create a message queue and print the 
                key and message queue id.
Date: 18th Sept, 2024.
============================================================================

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <errno.h>

int main() {

    key_t key;
    int qId;

    key = ftok(".", 30);
    if (key == -1) {
        perror("error");
        exit(1);
    }

    qId = msgget(key, IPC_CREAT | 0666);
    if (qId == -1) {
        perror("msgget");
        exit(1);
    }

    printf("Message Queue created\n");
    printf("Key - 0x%x\n", (unsigned int)key);
    printf("Message Queue id - %d\n", qId);

    return 0;
}