//Task 1.3.1. 1. & 2. --> Basic : Implementation of fork(), wait(), and exec() system calls 
//To compile, type gcc -o fileName fileName.c -Wall  or gcc filename.c -o filename
//To run, type ./fileName
//fork() creates new child process
//wait() parent process waits for child to finish its execution
//exec() is used to replace current process image with new process image 


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
         //When the child process is created, ls will be executed to list contents of current directory
        char *args[] = {"ls", "-l", NULL};
        execvp(args[0], args); //Child process is now replaced, and new command starts executing
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
