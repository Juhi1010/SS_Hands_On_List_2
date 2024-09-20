============================================================================
Name : 34a.c
Author : Juhi Rajani
Description :  34. Write a program to create a concurrent server.
                a. use fork
                b. use pthread_create
Date: 20th Sept, 2024.
============================================================================


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/wait.h>

#define PORT 8080
#define BUFFER_SIZE 512

void handle_client(int new_socket) {
    char buffer[BUFFER_SIZE];
    read(new_socket, buffer, BUFFER_SIZE);
    printf("Message from client: %s\n", buffer);
    send(new_socket, buffer, strlen(buffer), 0);
    close(new_socket);
}

int main() {
    int server_fd, new_socket;
    struct sockaddr_in address;
    int opt = 1;
    socklen_t addrlen = sizeof(address);

    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));
    
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    bind(server_fd, (struct sockaddr *)&address, sizeof(address));
    listen(server_fd, 3);

    printf("Server listening on port %d \n", PORT);
    while ((new_socket = accept(server_fd, (struct sockaddr *)&address, &addrlen)) >= 0) {
        if (fork() == 0) {
            close(server_fd); 
            handle_client(new_socket);
            exit(0);
        }
        close(new_socket); 
        waitpid(-1, NULL, WNOHANG); 
    }
    
    close(server_fd);
    return 0;
}
