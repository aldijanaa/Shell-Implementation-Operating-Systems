
//Task 1.3.2.1. --> Intermediate: execle()  
//execle() used to execute 'env' command which will print out the  environment variables in the current shell 

//execle() is one of functions in the exec family used to execute new program within the process
//when exec function is called, current process is replaced with the new program specified by function call
 
//To compile, type gcc -o fileName fileName.c -Wall
//To run, type ./fileName


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>  //for system calls

int main() {
    char *env[] = {"MY_VAR=hello", NULL}; // environment variable 
    char *args[] = {"env", NULL}; // Command and its arguments

    //calling execle() function
    execle("/usr/bin/env", args[0], NULL, env);  //each of these commands is located in "bin" directory

    // if execle() succeeds - this line won't be printed 
    printf("This line won't be printed because execle() replaced the current process.Goodbye\n");

    // If execle() fails
    perror("Execle() failed");
    exit(1);
    
    // Retrieve and print the value of the MY_VAR variable
    char *my_var = getenv("MY_VAR");  
    printf("The value of MY_VAR is: %s\n", my_var);
}


