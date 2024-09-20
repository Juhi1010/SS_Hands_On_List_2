============================================================================
Name : permission_chg.c
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
#include <sys/stat.h>

int main() {

    key_t key;
    int msgId;
    struct msqid_ds msgDets;

    key = ftok(".", 30);
    if (key == -1) {
        perror("ftok");
        exit(EXIT_FAILURE);
    }

    msgId = msgget(key, 0666);
    if (msgId == -1) {
        perror("msgget");
        exit(EXIT_FAILURE);
    }

    if (msgctl(msgId, IPC_STAT, &msgDets) == -1) {
        perror("msgctl IPC_STAT");
        exit(EXIT_FAILURE);
    }

    printf("Current permissions - %o\n", msgDets.msg_perm.mode);

    msgDets.msg_perm.mode = 0644; 

    if (msgctl(msgId, IPC_SET, &msgDets) == -1) {
        perror("msgctl IPC_SET");
        exit(EXIT_FAILURE);
    }

    printf("Changed permissions - %o\n", msgDets.msg_perm.mode);

    return 0;
}
