
//Task 1.3.2.2. --> Intermediate: clone()
//creates a new ("child") process, in a manner similar to fork. However, the difference is clone() function is used to run a particular function in a separate thread other than the calling //process. 
//Unlike fork() function where rest of the code after fork() function call will execute both parent and child processes. 
//But with clone() , a particular function will be executed in //separate thread.

//When CLONE_VM is set, the calling process and the child process run in the same memory space.
//When CLONE_FS is set, the caller and the child process share the same filesystem information.
//When CLONE_FILES is set, the calling process and the child process share the same file descriptor table.
//When CLONE_SIGHAND is set, the calling process and the child process share the same table of signal handlers.
//If CLONE_THREAD is set, the child is placed in the same thread group as the calling process. 

//To compile, type gcc -o fileName fileName.c -Wall
//To run, type ./fileName


#define _GNU_SOURCE  //non-standard flag for additional functions and macros that are not part of standard C libary
#include <stdio.h>
#include <stdlib.h>
#include <sched.h>
#include <unistd.h>

int child_func(void *arg) {
    printf("Child thread\n");
    return 0;
}

int main() {
    char *stack = malloc(4096);
    
    //Flags specifying child thread should share virtual memory space, file system info, open file descriptors, signal handlers and thread group ID of parent
    int flags = CLONE_VM | CLONE_FS | CLONE_FILES | CLONE_SIGHAND | CLONE_THREAD; 
    int ret = clone(child_func, stack + 4096, flags, NULL);
    if (ret == -1) {
        perror("Clone failed");
        exit(1);
    }

    printf("Parent thread\n");
    sleep(1); // wait for the child thread to complete
    return 0;
}
