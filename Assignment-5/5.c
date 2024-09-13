#include <stdio.h>
#include <unistd.h>
#include <sys/resource.h>
#include <sys/sysctl.h>
#include <sys/types.h>
#include <stdlib.h>

int main() {

    // a. Maximum length of the arguments to the exec family of functions

    int argmax;
    size_t size = sizeof(argmax);
    if (sysctlbyname("kern.argmax", &argmax, &size, NULL, 0) == 0) {
        printf("Maximum length of the arguments to the exec family of functions is %d bytes\n", argmax);
    } else {
        perror("error");
    }

    // b. Maximum number of simultaneous processes per user ID

    int maxprocs;
    size = sizeof(maxprocs);
    if (sysctlbyname("kern.maxproc", &maxprocs, &size, NULL, 0) == 0) {
        printf("Maximum number of simultaneous processes per user ID is %d\n", maxprocs);
    } else {
        perror("error");
    }

    // c. Number of clock ticks (jiffy) per second

    long clktick = sysconf(_SC_CLK_TCK);
    if (clktick != -1) {
        printf("Number of clock ticks (jiffy) per second is  %ld\n", clktick);
    } else {
        perror("error");
    }

    // d. Maximum number of open files

    struct rlimit rl;
    if (getrlimit(RLIMIT_NOFILE, &rl) == 0) {
        printf("Maximum number of open files is  %llu\n", rl.rlim_cur);
    } else {
        perror("error");
    }

    // e. Size of a page

    long pagesize = sysconf(_SC_PAGESIZE);
    if (pagesize != -1) {
        printf("Size of a page is %ld bytes\n", pagesize);
    } else {
        perror("error");
    }

    // f. Total number of pages in the physical memory

    int64_t totalmem;
    size = sizeof(totalmem);
    if (sysctlbyname("hw.memsize", &totalmem, &size, NULL, 0) == 0) {
        printf("Total number of pages in the physical memory are %lld\n", totalmem / pagesize);
    } else {
        perror("error");
    }

    // g. Number of currently available pages in the physical memory

    int64_t freemem;
    size = sizeof(freemem);
    if (sysctlbyname("vm.page_free_count", &freemem, &size, NULL, 0) == 0) {
        printf("Number of currently available pages in the physical memory are %lld\n", freemem / pagesize);
    } else {
        perror("error");
    }

    return 0;
}
