#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

void get_time(struct timespec *ts) {
    if (clock_gettime(CLOCK_MONOTONIC, ts) == -1) {
        perror("clock_gettime");
        exit(EXIT_FAILURE);
    }
}

uint64_t calculate_time_taken(struct timespec *start, struct timespec *end) {
    uint64_t start_ns = (uint64_t)start->tv_sec * 1e9 + start->tv_nsec;
    uint64_t end_ns = (uint64_t)end->tv_sec * 1e9 + end->tv_nsec;
    return end_ns - start_ns;
}

int main() {

    struct timespec start, end;
    pid_t pid;

    get_time(&start);

     for (int i = 0; i < 100; i++) {
        getppid();
    }

    get_time(&end);

    uint64_t time_taken = calculate_time_taken(&start, &end);
    uint64_t time_taken_us = time_taken / 1000;  

    printf("Process ID: %d\n", pid);
    printf("Time taken for getpid() 100 calls - %llu\n", (unsigned long long)time_taken_us);

    return 0;
}