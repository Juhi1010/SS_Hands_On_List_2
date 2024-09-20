============================================================================
Name : 20.c
Author : Juhi Rajani
Description :  20. Write two programs so that both can communicate by FIFO 
                -Use one way communication
Date: 18th Sept, 2024.
============================================================================

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main() {
    FILE *my_fifo;
    char msg[100];

    my_fifo = fopen("my_fifo", "w");
    if (my_fifo == NULL) {
        perror("Failed to open FIFO for sending");
        exit(EXIT_FAILURE);
    }

    snprintf(msg, sizeof(msg), "Hello\n");
    fprintf(my_fifo, "%s", msg);
    fflush(my_fifo);  
    printf("Successfuly sent below message to receiver program\n %s", msg);
    sleep(1);  
    
    fclose(my_fifo);
    return 0;
}
