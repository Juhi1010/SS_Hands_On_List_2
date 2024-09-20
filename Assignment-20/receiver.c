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

int main() {
    FILE *my_fifo;
    char msg[100];

    my_fifo = fopen("my_fifo", "r");
    if (my_fifo == NULL) {
        perror("Failed to open FIFO for receiving");
        exit(EXIT_FAILURE);
    }

    while (fgets(msg, sizeof(msg), my_fifo) != NULL) {
        printf("Data received - %s", msg);
    }

    fclose(my_fifo);
    return 0;
}
