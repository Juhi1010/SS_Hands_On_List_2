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

int main() {

    FILE *fifo1, *fifo2;
    char msg[100];

    fifo1 = fopen("fifo1", "r");
    fifo2 = fopen("fifo2", "w");

    if (fifo1 == NULL || fifo2 == NULL) {
        perror("Failed to open fifo");
        exit(EXIT_FAILURE);
    }

    fgets(msg, sizeof(msg), fifo1);
    printf("Received data - %s", msg);
    
    snprintf(msg, sizeof(msg), "Received data - \n");
    fprintf(fifo2, "%s", msg);
    fflush(fifo2);

    fclose(fifo1);
    fclose(fifo2);

    return 0;
}
