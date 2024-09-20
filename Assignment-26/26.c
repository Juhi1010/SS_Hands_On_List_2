============================================================================
Name : 26.c
Author : Juhi Rajani
Description :  26. Write a program to send messages to the message queue. 
                Check $ipcs -q
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
    long msg_type; 
    char msg_text[120]; 
};

int main() {

    key_t key;
    int msgid;
    struct msg_buffer message;

    key = ftok("26.c", 30);
    if (key == -1) {
        perror("error");
        exit(EXIT_FAILURE);
    }

    msgid = msgget(key, 0666 | IPC_CREAT);

    if (msgid == -1) {
        perror("error");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < 3; i++) {

        message.msg_type = 1; 
        snprintf(message.msg_text, sizeof(message.msg_text), "Data %d", i + 1);

        if (msgsnd(msgid, &message, sizeof(message.msg_text),0) == -1) {
            perror("msgsnd");
            exit(EXIT_FAILURE);
        }

        printf("Sent - %s\n", message.msg_text);
    }

    return 0;
}
