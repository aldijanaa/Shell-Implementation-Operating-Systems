//SHELL IMPLEMENTATION BY ALDIJANA AND AJLA
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>  //for system calls
#include <limits.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <linux/kernel.h>
#include <sys/sysinfo.h>
#include <libgen.h>
#include <signal.h>
#include <sys/wait.h>
#include "internal.h"
#include <sys/statvfs.h> //df
#include <errno.h>  //df
#include <time.h>

//max length a command can have (constant value)
#define MAX_LINE 100

//intializating variable for infinite Loop later on
int infiniteLoop = 1;

//initialization of the variable count
int count = 0;



//Task 1.1 --> Basic: prompt
/*int takeInput(char* str){
    char* buf;
    buf = readline("\nprompt$ ");  //prompt$
    if(strlen(buf) !=0){
        //add_history(buf);
        strcpy(str, buf);
        return 0;
    }else{
        return 1;
    }
} */


//Task 1.1 Advanced: Displays user prompt
void takePrompt(){
    char * username;
    char machinename[MACHINE_NAME + 1];// Sets the limit (usually to 255)

    //gets current username (built-in function)
    username = getlogin();

    //gets current hostname (built-in function)
    gethostname(machinename, MACHINE_NAME + 1);

    //current working directory is stored in variable cwd
    char cwd[PATH_MAX];

    //Calling functions to set color to the shell
    setColorBlue();
    printf("%s", machinename);

    setColorBlueBold();
    printf("@");

    setColorGreen();
    printf("%s", username);

    setColorGreenBold();
    printf(":~$ ");

    //resetColor();
}


//Task 1.4 Adding color to the shell and name.
//For changing the text color/style of text we used ANSI escape sequence.

void setColorYellow() {
    printf("\033[0;33m");
}
void setColorYellowBold() {
    printf("\033[1;33m");
}

void setColorRed() {
    printf("\033[0;31m");
}
void setColorRedBold() {
    printf("\033[1;31m");
}

void setColorBlue() {
    printf("\033[0;34m");
}
void setColorBlueBold() {
    printf("\033[1;34m");
}

void setColorGreen() {
    printf("\033[0;32m");
}
void setColorGreenBold() {
    printf("\033[1;32m");
}

//Resets to the default color
void resetColor() {
    printf("\033[0m");
}

//Task 1.4 Setting the foreground and background color
void setForegroundAndBackground(){
    printf("\033[38;5;36m\033[48;5;45m");
}

void setForegroundAndBackground1(){
    printf("\033[38;5;220m\033[48;5;17m");
}



//What is displayed on the shell
void init_shell()
{
    system("clear");
    printf("\n\n\n\n******************"
           "************************");
    printf("\n\n\n\t****SHELL IMPLEMENTATION BY ALDIJANA AND AJLA****");
    //printf("\n\n\n\n*******************"
          // "***********************");
    //char* username = getenv("USER");
    //printf("\n\n\nUSER is: @%s", username);
    //printf("\n");
    sleep(3);
    system("clear");
}

//Function used for reading user input. Deals with system calls and functions   -- ovdje treba ta tokens funkcija
void routerFunction(char input[1024]) {  //input variable is used for when user enters some command to be executed

    //extracting given command from input variable into function variable
    char function [10] = "";
    int fun_counter = 0;

    //identifying the command
    for (int i = 0; i < strlen(input); i++) {
        if (input[i] != ' ' || (int) input[i] == 0) {
            function [fun_counter] = input[i];
            fun_counter++;
        } else {
            break;
        }
    }


    //Which command user wants to execute
    function [strcspn(function, "\n")] = 0; //removing newline characters

    //if statements which calls the function to its input
    if (strcmp(function, "wc") == 0) {  //wc
        wc();
    } else if (strcmp(function, "grep") == 0) {  //grep
        grep();
    } else if (strcmp(function, "df") == 0) {   //df
        dfCall();
    } else if (strcmp(function, "cmatrix") == 0) {   //cmatrix
        dfCall();

        //Owl command
    } else if(strcmp(function, "owl") == 0){
        for (int i = 0; i < 120; i++){
            // movement of the owl
            system("sleep 0.01");

            // clears the screen before each instance of owl appears
            system("clear");
            owl(i); // the owl moves 120 spaces
        }
        system("clear"); //clearing the console screen
    } else if ((int)function [0] != 0) {
        printf("%s: command is not found\n", function);
    }

}



int main() {

    //system("clear");
    init_shell();

    //calling function for background change
    setBlueAndWhiteColors();

    //calling functions for system calls
    wc();
    execFunction();
    forkAndWaitFunction();
    redirectOutputToFile();

    //basic functionalities function calling
    wc();
    grep();
    dfCall();


    char input[1024];

    //infinite loop for taking user input
    while (infiniteLoop) {

        takePrompt();
        fgets(input, 1024, stdin);

        routerFunction(input);
    }


    //calling cmatrix
    const int SCREEN_WIDTH = 80; // adjust as needed for your terminal
    const int SCREEN_HEIGHT = 25; // adjust as needed for your terminal
    const int NUM_LETTERS = 50; // adjust as needed for desired density of letters
    const int DURATION = 30; // duration of matrix effect in seconds

    cmatrix(SCREEN_WIDTH, SCREEN_HEIGHT, NUM_LETTERS, DURATION);

}


void tokens(){   //????????

}







//Task 1.2 Intermediate b) - Create something that does not exist in the bash
void owl(){

    setColorBlue();
    printf(" '___'\n");
    setColorRed();
    printf(" (O,O)\n");
    setColorYellow();
    printf("  /)_)\n");
    setColorGreen();
    printf("   ""  \n");

    //to reset the colors after command execution
   resetColor();
}


//Task 1.2 --> Basic: wc()   -WORKS!
//wc() - counts word, lines and characters in the given string

void  wc(){

    //i - loop counter, count, count2, count3 - used to count nummber of words, characters and lines
    int i, count = 0, count2 = 0, count3 = 0;
    char l[200];

    //text that will be used for performing operations
    //printf("Function wc(word count) can perform options such as number of words (-W), lines (-l), and characters (-m).\n");
    printf("The text on which these operations will be performed is:\n");
    printf("\n");
    printf("Introduction to Operating Systems is a graduate-level introductory course in operating systems.\nThis course teaches the basic operating system abstractions, mechanisms, and their implementations.\nThe core of the course contains concurrent programming (threads and synchronization), inter process communication, and an introduction to distributed operating systems.\nThe course is split into four sections: (1) Introduction, (2) Process and Thread Management, (3) Resource Management and Communication, and (4) Distributed Systems.\n");

    char s[12256] = "Introduction to Operating Systems is a graduate-level introductory course in operating systems.\nThis course teaches the basic operating system abstractions, mechanisms, and their implementations.\nThe core of the course contains concurrent programming (threads and synchronization), inter process communication, and an introduction to distributed operating systems.\nThe course is split into four sections: (1) Introduction, (2) Process and Thread Management, (3) Resource Management and Communication, and (4) Distributed Systems.";
    printf("\n");


    printf("The first option is to count the number of words in the given text.\n");

    //counting number of words in text
    for (i = 0; s[i] != '\0'; i++) {
        if (s[i] == ' ' && s[i+1] != ' ')
            count++;
    }
    printf("Number of words in the given string is: %d\n", count + 1);

    printf("The second option is to count the number of lines in the given text.\n");

    //counting number of lines in text
    for(i = 0; s[i] != '\0'; i++) {
        if(s[i] == '\n') {
            count3++;
        }
    }
    printf("The number of lines in the given string is: %d\n", count3 + 1);

    printf("The third option is to count the number of characters in the given text.\n");

    //counting number of characters in text
    for (i = 0; s[i] != '\0'; i++) {
        if(s[i] >= 'a' && s[i] <= 'z') {
            count2++;
        }
    }
    printf("The number of characters in the given string is: %d\n", count2);
}



//Task 1.2 --> Basic: grep - WORKS!!
//grep --> searches for a file containing particular pattern, and displays lines containing that pattern
//grep doesn't return any value, therefore it's type is void
void grep()
{
    //file name, pattern and number of characters that can be read
    char fileName[10],pattern[10],temp[200];

    //pointer for file that is opened for reading
    FILE *fp;

    //User prompt
    printf("Enter file name\n");
    scanf("%s", fileName);
    printf("Enter pattern to be searched\n");
    scanf("%s", pattern);

    //opens the file specified by user
    fp=fopen(fileName, "r");  // "r" - file should be opened in reading mode

    //loop to read each line of file
    while(!feof(fp))
    {
        //stores line in temp, max numb of characters is 1000, and file pointer to open the file
        fgets(temp,1000,fp);

        //does the pattern appear in line, if yes print it
        if(strstr(temp, pattern)) //temp - max number of characters
            printf("%s",temp);
    }
    fclose(fp);  //Closing the file
}

//Task 1.2 --> Basic: df - provjeriti zasto ne radi!
//df - reports file system disk space usage

//argc - number of command line arguments passed to program, argv - array of strings containing those arguments
void dfCall(int argc, char *argv[]) {
    struct statvfs buf; //buf - instance of structure in memory, stores info about file system

    //if number of arguments not equal to 2 - print error and return 1
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <directory>\n", argv[0]);
        return 1;
    }

    //argv[1] - directory to check, retrieves info about file system that the directory resides on
    //and stores it in struct "buf"
    if (statvfs(argv[1], &buf) == -1) {
        perror("statvfs");  //if it fails, return 1
        return 1;
    }else{  //if it didn't fail, print these informations retrieved from buff
        printf("File system block size: %ld bytes\n", buf.f_frsize);
        printf("Total number of blocks: %ld\n", buf.f_blocks);
        printf("Free blocks: %ld\n", buf.f_bfree);
        printf("Available blocks: %ld\n", buf.f_bavail);
        printf("Total file nodes: %ld\n", buf.f_files);
        printf("Free file nodes: %ld\n", buf.f_ffree);
        printf("File system ID: %ld\n", buf.f_fsid);
        printf("Maximum filename length: %ld\n", buf.f_namemax);

    }
    return 0;
}
//Task 1.2 --> Basic: cmatrix

void cmatrix(const int SCREEN_WIDTH, const int SCREEN_HEIGHT, const int NUM_LETTERS, const int DURATION) {
    srand(time(NULL)); // seed the random number generator with current time
    time_t start_time = time(NULL); // record the start time of the program

    // loop until the duration has elapsed
    while (time(NULL) - start_time < DURATION)
    {
        // create random letters at random positions
        for (int i = 0; i < NUM_LETTERS; i++)
        {
            int x = rand() % SCREEN_WIDTH; // random x-coordinate
            int y = rand() % SCREEN_HEIGHT; // random y-coordinate
            char c = (rand() % 26) + 'A'; // random letter from A to Z

            // set text color to green
            printf("\033[32m");

            // move cursor to position and print letter
            printf("\033[%d;%dH%c", y+1, x+1, c); // ANSI escape code to move cursor

            // set text color back to default
            printf("\033[0m");

            // update y-coordinate for next iteration
            y = (y + 1) % SCREEN_HEIGHT;
        }

        fflush(stdout); // flush output buffer
        //there is a possibiltiy that usleep won't work on some  POSIX systems,
        // so another option is:
        // struct timespec delay = {0, 50000L);
        // nanosleep(delay,run);
        usleep(50000); // wait for a short time to create animation effect
    }
}



//Task 1.3 --> Basic: fork() and wait() implemented together  -WORKS!
//fork --> creates new child process
//wait --> parent process waits for child to finish
void forkAndWaitCall(){
    int child = fork();
    printf("Fork returned: %d\n", child);

    //Fork failed
    if (child < 0)
    {
        setColorGreen();
        printf("Fork process failed \n");
        exit(1);
        resetColor();
    }
    else if (child == 0)  //New child process created
    {
        setColorRed();
        printf("Hello I am child and this is my id: %d\n", (int)getpid());
        resetColor();
    }
    else
    {
        printf("Hello I am parent and this is my id: %d\n", (int)getpid());
        wait(NULL); //parent waits for child to finish it's execution
        printf("child has terminated\n");
    }
}


//Task 1.3 --> Basic: exec() system call
// exec () - executes command from the bash itself, ongoing process is replaced with the command
//TREBA OVAJ KOD!!!!




//Task 1.3 --> Intermediate: execle()  - WORKS!
//Executing a binary file "ls" located in /bin directory
//New process is created using execle(), the env variables passed to the function is used to initialize the 'environ' array in the new process.
// If the env argument is NULL, the new process inherits the environment variables from the parent process.

//this code will print out if execle succeds(), all current working directory (command ls)
int execleCall(){
    char *args[] = {"ls", "-la", NULL};  //defining commands and
    char *env[] = {NULL}; //environment variable

    execle("/bin/ls", "ls", "-la", NULL, env); //calling execle function

    // This line won't be printed if execle() succeeds
    printf("This line won't be printed because execle() comamnd replaced this current process.\n");

    //If execle() fails
    perror("execle() failed");
    return -1;
}




//Task 1.3 --> Intermediate: clone() --provjeriti ovaj??????????
#define _GNU_SOURCE
#define STACK_SIZE (1024 * 1024)  // 1 MB stack size for child process

int child_func(void *arg) {
    printf("This is a child process: pid=%d\n", (int) getpid());
    return 0;
}

int cloneFun(){  // ((int but no return type??))

    void *stack = malloc(STACK_SIZE);

    if (stack == NULL) {
        perror("malloc");
        exit(EXIT_FAILURE);
    }

    int flags = CLONE_NEWPID | CLONE_NEWUTS| SIGCHLD;  // create a new PID namespace
//CLONE_NEWPID means if it is set, then create a process in the new PID namespace,
// If this flag is not set, then  the process is created in the same PID namespace as the calling process

//CLONE_NEWUTS means if it is set, then create the process in a new UTS namespace, whose identifiers are initialized by duplicating
// the identifiers from the UTS namespace of the calling process.
// If this flag is not set, then the process is created in the same UTS namespace as the calling process

//SIGCHILD is used as the child termination signal, if it wasn't this signal then the parent would not know when the child terminated,
// and if it was specified by anything else, then parent would have to specify certain wait function

    int pid = clone(child_func, (char *)stack + STACK_SIZE, flags, NULL);
    //int clone(int (*fn)(void *), void *stack, int flags, void *arg, --> this is the structure for the calling that we used
    if (pid < 0) {
        perror("This clone process failed.");
        exit(1);
    }

    printf("This is a parent process: pid=%d, child pid=%d\n", (int) getpid(), pid);
    free(stack); //after execution, freeing the memory
    return 0;
}





//Task 1.3 --> Additionally: forkbomb()  - PROABLY WORKS I AINT TRYING OK
//forkbomb() harms the system, it's a form of DoS attack
void forkbomb(); //declaration
void forkbomb() //implementation
{
    //declaring a char variable to track the process execution based on user input (yes/no)
    char bomb;
    printf("You sure you really really wanna do this? (yes/no): ");//Ask user for input
    scanf("%c", &bomb);

    //If yes -> execute bomb
    if(bomb=='yes' || bomb=='Yes'){
        printf("That was fast :(\n");
        while(1){
            fork();
        }
    }

     //If no -> thank the user
    else if(bomb=='no' || bomb=='No'){
        printf("You saved yourself some trouble!\n ");

    }
    else{
        printf("This is out of order :/\n");
    }
}


//Task 1.2 --> Advanced: Redirecting output to another file  - WORKS
//To compile use: gcc output.c -o output  and then ./output
void redirectOutputToFile(); //declaration
void redirectOutputToFile() { //implementation
    FILE *fp; //file pointer - used for accessing the file

    //opens file output.txt for writing
    fp = fopen("output.txt", "w");  // "w" - write mode

    //if file can't be open
    if (fp == NULL) {
        printf("Error opening the file.\n");
        return;
    }else{  //file opens, function writes this string to the file
        fprintf(fp, "This is the output to a file.\n Goodbye wishes you Aldijana and Ajla");
        fclose(fp);  //closing the file
    }

}

