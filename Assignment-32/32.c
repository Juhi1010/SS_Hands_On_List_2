==================================================================================
Name : 32.c
Author : Juhi Rajani
Description :  32. Write a program to implement semaphore to protect any critical section.
                a. rewrite the ticket number creation program using semaphore
                b. protect shared memory from concurrent write access
                c. protect multiple pseudo resources ( may be two) using counting semaphore
                d. remove the created semaphore 
Date: 20th Sept, 2024.
===================================================================================

#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <stdlib.h>

// Shared resources
int ticket_number = 0;
int shared_memory = 0;
int resource_count = 2;

// Semaphores
sem_t ticket_semaphore;
sem_t memory_semaphore;
sem_t resource_semaphore;

void* createTicket(void* arg) {
    sem_wait(&ticket_semaphore);
    
    if (ticket_number < 100) {
        ticket_number++;
        printf("Ticket created - %d\n", ticket_number);
    } else {
        printf("Max tickets reached\n");
    }
    
    sem_post(&ticket_semaphore);
    return NULL;
}

void* writeToMemory(void* arg) {

    sem_wait(&memory_semaphore);
    
    shared_memory++;
    printf("Writing to shared memory resource - %d\n", shared_memory);
    
    sem_post(&memory_semaphore);
    return NULL;
}

void* useResource(void* arg) {

    sem_wait(&resource_semaphore);
    
    printf("Thread %ld is using a resource\n", (long)arg);
    sleep(1);  
    printf("Thread %ld has finished using the resource\n", (long)arg);
    
    sem_post(&resource_semaphore);
    return NULL;
}

int main() {

    sem_init(&ticket_semaphore, 0, 1);
    sem_init(&memory_semaphore, 0, 1);
    sem_init(&resource_semaphore, 0, resource_count);

    pthread_t ticket_threads[4];
    for (int i = 0; i < 4; i++) {
        pthread_create(&ticket_threads[i], NULL, createTicket, NULL);
    }

    pthread_t memory_threads[4];
    for (int i = 0; i < 4; i++) {
        pthread_create(&memory_threads[i], NULL, writeToMemory, NULL);
    }

    pthread_t resource_threads[4];
    for (long i = 0; i < 4; i++) {
        pthread_create(&resource_threads[i], NULL, useResource, (void*)i);
    }

    for (int i = 0; i < 4; i++) {
        pthread_join(ticket_threads[i], NULL);
    }
    for (int i = 0; i < 4; i++) {
        pthread_join(memory_threads[i], NULL);
    }
    for (int i = 0; i < 4; i++) {
        pthread_join(resource_threads[i], NULL);
    }

    sem_destroy(&ticket_semaphore);
    sem_destroy(&memory_semaphore);
    sem_destroy(&resource_semaphore);

    return 0;
}