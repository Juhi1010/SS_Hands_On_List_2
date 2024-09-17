============================================================================
Name : 16.c
Author : Juhi Rajani
Description :  16. Write a program to send and receive data from parent to child 
                vice versa. Use two waycommunication.
Date: 16th Sept, 2024.
============================================================================

#include<stdio.h>
#include<unistd.h>

int main() {
   int fds1[2], fds2[2];
   int pid;
   char msg1[20] = "abc";
   char msg2[20] = "xyz";
   char readmsg[20];
   
   if (pipe(fds1) == -1) {
      printf("Unable to create pipe 1 \n");
      return 1;
   }
   
   if (pipe(fds2) == -1) {
      printf("Unable to create pipe 2 \n");
      return 1;
   }

   pid = fork();
   
   if (pid != 0) {
      close(fds1[0]); 
      close(fds2[1]); 
      printf("parent writing to pipe1 – %s\n", msg1);
      write(fds1[1], msg1, sizeof(msg1));
      read(fds2[0], readmsg, sizeof(readmsg));
      printf("parent reading from pipe 2 – %s\n", readmsg);
   } else { 
      close(fds1[1]); 
      close(fds2[0]); 
      read(fds1[0], readmsg, sizeof(readmsg));
      printf("child reading from pipe 1 – %s\n", readmsg);
      printf("child writing to pipe 2 – %s\n", msg2);
      write(fds2[1], msg2, sizeof(msg2));
   }
   return 0;
}


juhirajani@Juhis-Laptop Assignment-16 % gcc 16.c
juhirajani@Juhis-Laptop Assignment-16 % ./a.out 
parent writing to pipe1 – abc
child reading from pipe 1 – abc
child writing to pipe 2 – xyz
parent reading from pipe 2 – xyz