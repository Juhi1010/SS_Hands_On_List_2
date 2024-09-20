============================================================================
Name : 29.c
Author : Juhi Rajani
Description :  29. Write a program to remove the message queue.
Date: 18th Sept, 2024.
============================================================================

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

int main() {

    key_t key;
    int msgId;

    key = ftok("/tmp", 'a');
    if (key == -1) {
        perror("ftok");
        exit(EXIT_FAILURE);
    }

    msgId = msgget(key, 0666);
    if (msgId == -1) {
        perror("msgget");
        exit(EXIT_FAILURE);
    }

    if (msgctl(msgId, IPC_RMID, NULL) == -1) {
        perror("msgctl IPC_RMID");
        exit(EXIT_FAILURE);
    }

    printf("Message queue with id %d removed successfully.\n", msgId);

    return 0;
}
