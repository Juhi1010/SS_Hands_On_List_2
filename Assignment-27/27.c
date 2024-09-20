============================================================================
Name : 27.c
Author : Juhi Rajani
Description :  27. Write a program to receive messages from the message queue.
                a. with 0 as a flag
                b. with IPC_NOWAIT as a flag
Date: 18th Sept, 2024.
============================================================================


#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>

#define MSG_SIZE 256

struct msg_buffer {
    long msg_type;
    char msg_text[MSG_SIZE];
};

int main() {
    key_t key;
    int msgid;
    struct msg_buffer message;

    key = ftok("/tmp", 30);
    if (key == -1) {
        perror("ftok");
        exit(EXIT_FAILURE);
    }

    msgid = msgget(key, 0666);
    if (msgid == -1) {
        perror("msgget");
        exit(EXIT_FAILURE);
    }

    printf("Receiving messages with blocking (flag 0):\n");
    for (int i = 0; i < 5; i++) {
        if (msgrcv(msgid, &message, sizeof(message.msg_text), 1, 0) == -1) {
            perror("msgrcv");
            exit(EXIT_FAILURE);
        }
        printf("Received: %s\n", message.msg_text);
    }

    printf("Receiving messages with IPC_NOWAIT:\n");
    for (int i = 0; i < 5; i++) {
        if (msgrcv(msgid, &message, sizeof(message.msg_text), 1, IPC_NOWAIT) == -1) {
            if (errno == ENOMSG) {
                printf("No messages available (non-blocking mode).\n");
                break;
            } else {
                perror("msgrcv");
                exit(EXIT_FAILURE);
            }
        }
        printf("Received: %s\n", message.msg_text);
    }

    if (msgctl(msgid, IPC_RMID, NULL) == -1) {
        perror("msgctl");
        exit(EXIT_FAILURE);
    }

    return 0;
}
