
//Task 1.3.2.1. --> Intermediate: execle()  
//Executing a binary file "ls" located in /bin directory
//New process is created using execle(), the env variables passed to the function is used to initialize the 'environ' array in the new process.
// If the env argument is NULL, the new process inherits the environment variables from the parent process.
//this code will print out if execle succeds(), all current working directory (command ls)
//To compile, type gcc -o fileName fileName.c -Wall
//To run, type ./fileName

 
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    char *env[] = {"MY_VAR=hello", NULL}; // environment variable to pass
    char *args[] = {"env", NULL}; // program and its arguments

    execle("/usr/bin/env", args[0], NULL, env); // calling execle function

    // This line won't be printed if execle() succeeds
    printf("This line won't be printed because execle() replaced the current process.\n");

    // If execle() fails
    perror("execle() failed");
    exit(1);
}

