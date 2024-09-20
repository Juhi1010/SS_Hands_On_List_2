#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <time.h>
#include <errno.h>

int main() {

    key_t key;
    int msgq_id;
    struct msqid_ds queue_info;

    key = ftok(".", 30);
    if (key == -1) {
        perror("ftok");
        exit(1);
    }

    msgq_id = msgget(key, IPC_CREAT | 0666);
    if (msgq_id == -1) {
        perror("msgget");
        exit(1);
    }

    if (msgctl(msgq_id, IPC_STAT, &queue_info) == -1) {
        perror("msgctl");
        exit(1);
    }

    printf("Message Queue Details :- \n");
    printf("a. Access Permissions - %#o\n", queue_info.msg_perm.mode);
    printf("b. UID - %d, GID - %d\n", queue_info.msg_perm.uid, queue_info.msg_perm.gid);
    printf("c. Time of last msgsnd - %s", ctime(&queue_info.msg_stime));
    printf("   Time of last msgrcv - %s", ctime(&queue_info.msg_rtime));
    printf("d. Time of last change - %s", ctime(&queue_info.msg_ctime));
    printf("e. Size of the queue - %lu bytes\n", (unsigned long)queue_info.msg_cbytes);
    printf("f. Number of messages in the queue - %lu\n", (unsigned long)queue_info.msg_qnum);
    printf("g. Maximum number of bytes allowed - %lu\n", (unsigned long)queue_info.msg_qbytes);
    printf("h. PID of last msgsnd - %d\n", queue_info.msg_lspid);
    printf("   PID of last msgrcv - %d\n", queue_info.msg_lrpid);

    return 0;

}