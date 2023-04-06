
//Task 1.3.1.3. --> Basic: exec
//To compile, type gcc -o fileName fileName.c -Wall
//To run, type ./fileName

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    char *args[] = {"ls", "-l", NULL}; // program and its arguments

    execv("/bin/ls", args); // calling execv function

    // This line won't be printed if execv succeeds
    printf("This line won't be printed because execv replaced the current process.\n");

    // If execv fails
    perror("execv failed");
    exit(1);
}
