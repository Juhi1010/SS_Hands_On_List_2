============================================================================
Name : 15.c
Author : Juhi Rajani
Description :  15. Write a simple program to send some data from parent to the 
                child process.
Date: 16th Sept, 2024.
============================================================================

#include <pthread.h> 
#include <stdio.h> 
#include <sys/types.h> 
#include <unistd.h>  
#include <stdlib.h>  
#include <sys/wait.h> 
  
int main() 
{ 
  
  int fd[2], i = 0; 
  pipe(fd); 
  pid_t pid = fork(); 
  
  if(pid > 0) { 

    int arr[] = {51,52,53,54,55}; 
  
    close(fd[0]);  
    close(1);     
  
    dup(fd[1]);   
    write(1, arr, sizeof(arr));   
  }  

  else if (pid == 0) { 

      wait(NULL); 
      close(0); 
      close(fd[1]);  
  
      dup(fd[0]);  
      int arr[10]; 
  
      int n = read(fd[0], arr, sizeof(arr)); 

      for ( i = 0;i < n/4; i++) 
            printf("%d ", arr[i]);  
  }  
  
  else { 
      perror("error\n"); 
  } 
}  


juhirajani@Juhis-Laptop Assignment-15 % gcc 15.c
juhirajani@Juhis-Laptop Assignment-15 % ./a.out
51 52 53 54 55 %     