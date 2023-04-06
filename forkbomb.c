
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
