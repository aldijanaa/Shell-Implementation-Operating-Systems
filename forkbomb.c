
//Task 1.3.3. --> Advanced: forkbomb
//forkbomb() harms the system, it's a form of DoS attack

//WE DO NOT RECOMMEND COMPILING AND RUNNING THIS PROGRAM AT ALL, BUT DO EVERYTHING ON YOUR CAUTION!
//ONCE AGAIN, FORKBOMB WILL OVERLOAD YOUR SYSTEM AND POTENTIALLY EVEN CRASH IT!
//To compile, type gcc -o fileName fileName.c -Wall or gcc fileName.c -o fileName
//To run, type ./fileName

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{
    //declaring a variable to track the process execution based on user input (yes/no)
    char bomb; 
    
    //Ask user for input: y or Y for yes, n or N for no
    printf("Are you sure you want to do this? (yes/no): ");   
    scanf("%c", &bomb);

    //If yes -> execute bomb
    if(bomb=='y' || bomb =='Y'){
        printf("A forkbomb's code is quite simple, It multiplies itself like a ripple.\n Each child process makes more, Till the system can take no more.\n Use it wisely, use it well OR you'll be in a forkbomb's shell.\n");
        while(1){
            fork();
        }
    }

     //If no -> bomb will not the be executed
    else if(bomb=='n' || bomb=='N'){
        printf("Sometimes not knowing is more helpful than knowing. Forkbomb will NOT be executed!\n ");

    }
    else{
        printf("Not valid input.\n");
    }
}



/*Forkbomb can also be presented through this symbol :(){ :|: & };:

: -> This defines a function named : (colon). The function does not take any arguments.
(){ ... } -> This is the body of the function. It contains a command to call the function recursively, creating an infinite loop. Curly braces create a code block in which the function is performed.
:-> This calls the function, starting the infinite loop.
|-> This is the symbol for piping, which connects the output of one command to the input of another.
:-> This is the name of the function being piped to. The : function is called with its output as input.
& -> This puts the command in the background, allowing other commands to be executed in the foreground.
; -> This separates the two commands, allowing them to be executed sequentially.
: -> This is the final call to the : function, which starts another iteration of the infinite loop.

The combination of these commands creates a chain reaction of process creation, as each call to the function creates two new processes 
(one to execute the function and one to pipe its output), which in turn create more processes, 
quickly consuming all available system resources and causing the system to crash or become unresponsive.*/


