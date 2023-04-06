//Task 1.3.1. 1. & 2. --> Basic : Implementation of fork and wait together
//To compile, type gcc -o fileName fileName.c -Wall
//To run, type ./fileName
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    int child;

    child = fork();
    printf("Fork process returned a value: %d\n", child);

    //Fork failed
    if (child < 0)
    {
        printf("Fork process failed.\n");
        exit(1);
        
    }
    else if (child == 0)  //New child process created
    {
     
        printf("Hello, I am child and this is my id: %d\n", (int)getpid());
    }
    else
    {
        printf("Hello, I am parent and this is my id: %d\n", (int)getpid());
        wait(NULL); //parent waits for child to finish it's execution
        printf("child has terminated\n");
    } 
    return 0;
}