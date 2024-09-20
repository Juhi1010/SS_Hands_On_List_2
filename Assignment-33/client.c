============================================================================
Name : client.c
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
    int sock;
    struct sockaddr_in serv_addr;
    char *msg = "Hello i am client";
    char buffer[512];

    sock = socket(AF_INET, SOCK_STREAM, 0);
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(8080);
    inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr);

    connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr));
    send(sock, msg, strlen(msg), 0);
    read(sock, buffer, 512);

    printf("Message from server - %s\n", buffer);
    close(sock);
    return 0;
}
