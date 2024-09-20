============================================================================
Name : 28.c
Author : Juhi Rajani
Description :  28. Write a program to change the exiting message queue permission. 
                (use msqid_ds structure)
Date: 18th Sept, 2024.
============================================================================

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>
#include <unistd.h>

struct msg_buffer {
    long msgType;
    char msgText[132];
};

int main() {

    key_t key;
    int msgId;
    struct msg_buffer msg;

    key = ftok(".", 30);
    if (key == -1) {
        perror("ftok");
        exit(EXIT_FAILURE);
    }

    msgId = msgget(key, 0666 | IPC_CREAT);
    if (msgId == -1) {
        perror("msgget");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < 5; i++) {
        msg.msgType = 1;
        snprintf(msg.msgText, sizeof(msg.msgText), "Message %d", i + 1);
        if (msgsnd(msgId, &msg, sizeof(msg.msgText), 0) == -1) {
            perror("msgsnd");
            exit(EXIT_FAILURE);
        }
        printf("Sent - %s\n", msg.msgText);
        sleep(1);
    }

    return 0;
}
