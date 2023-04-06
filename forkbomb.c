
//Task 1.3.3. --> Advanced: forkbomb
//forkbomb() harms the system, it's a form of DoS attack
//WE DO NOT RECOMMEND COMPILING AND RUNNING THIS PROGRAM AT ALL, BUT DO EVERYTHING ON YOUR CAUTION!
//ONCE AGAIN, FORKBOMB WILL OVERLOAD YOUR SYSTEM AND POTENTIALLY EVEN CRASH IT!
//To compile, type gcc -o fileName fileName.c -Wall
//To run, type ./fileName
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{
    
    char bomb; //declaring a char variable to track the process execution based on user input (yes/no)
    printf("Are you sure you want to do this? (yes/no): ");   //Ask user for input
    scanf("%c", &bomb);

    //If yes -> execute bomb
    if(bomb=='yes' || bomb=='Yes'){
        printf("Your wish is my command. Forkbomb will know be executes.\n");
        while(1){
            fork();
        }
    }

     //If no -> bomb will not the be executed
    else if(bomb=='no' || bomb=='No'){
        printf("Sometimes not knowing is more helpful than knowing. Forkbomb will NOT be executed!\n ");

    }
    else{
        printf("Inappropriate input.\n");
    }
}
