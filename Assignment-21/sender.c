============================================================================
Name : 21.c
Author : Juhi Rajani
Description :  21. Write two programs so that both can communicate by FIFO 
                -Use two way communications.
Date: 18th Sept, 2024.
============================================================================

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main() {

    FILE *fifo1, *fifo2;
    char msg[100];

    fifo1 = fopen("fifo1", "w");
    fifo2 = fopen("fifo2", "r");

    if (fifo1 == NULL || fifo2 == NULL) {
        perror("Failed to open fifo");
        exit(EXIT_FAILURE);
    }

    snprintf(msg, sizeof(msg), "Hi Receiver\n");
    fprintf(fifo1, "%s", msg);
    fflush(fifo1);
    printf("Sent data %s", msg);
    
    fgets(msg, sizeof(msg), fifo2);
    
    fclose(fifo1);
    fclose(fifo2);

    return 0;
}
