============================================================================
Name : server.c
Author : Juhi Rajani
Description :  33. Write a program to communicate between two machines using socket.
Date: 20th Sept, 2024.
============================================================================

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

int main() {
    int server, new_sock;
    struct sockaddr_in address;
    char buffer[512];

    server = socket(AF_INET, SOCK_STREAM, 0);
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(8080);

    bind(server, (struct sockaddr *)&address, sizeof(address));
    listen(server, 3);
    
    new_sock = accept(server, NULL, NULL);
    read(new_sock, buffer, 512);

    printf("Message received from client - %s\n", buffer);

    send(new_sock, buffer, strlen(buffer), 0);

    close(new_sock);
    close(server);
    return 0;
}
