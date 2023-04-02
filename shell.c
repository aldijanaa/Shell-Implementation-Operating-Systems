//SHELL IMPLEMENTATION BY ALDIJANA AND AJLA (original)
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>  //-> for system calls
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
#include <sys/statvfs.h> 
#include <errno.h>  
#include <time.h>

//Defining length of command and number of arguments
#define MAX_COMMAND_LENGTH 100
#define MAX_NUM_ARGUMENTS 10
#define true 1

//constants needed for cmatrix (digital rain)
#define MAX_COLS 80
#define MAX_ROWS 25
#define MAX_LENGTH 10
#define MIN_SPEED 50000 // in microseconds
#define MAX_SPEED 150000 // in microseconds

//declaration of the functions
void takePrompt();
void initShell();
void tokensFunction();
int wc();
int grep();
int df();
int cmatrix();
int owl();
void redirectOutputToFile();

//declaration of color functions
void setColorYellow();
void setColorYellowBold();
void setColorBrightYellowBold();
void setColorRed();
void setColorRedBold();
void setColorBlue();
void setColorBlueBold();
void setColorGreen();
void setColorGreenBold();
void setColorBrightGreen();
void setColorCyan();
void setColorBrightCyan();
void setColorBrightMagenta();

void setCyanAndBrightGreen();
void setBlackAndBrightWhite();
void setWhiteAndRed();
void setMagentaAndBrightCyan();
void setWhiteAndBlack();
void resetColor();



//Task 1.1 Advanced: Displays user prompt
void takePrompt(){
    char * username;
    char hostname[HOST_NAME_MAX + 1];// Sets the limit (usually to 255)

    //gets current username (built-in function)
    username = getlogin();

    //gets current hostname (built-in function)
    gethostname(hostname, HOST_NAME_MAX + 1);

    //current working directory is stored in variable cwd
    char cwd[PATH_MAX];

    //Calling functions to set color to the shell
    setColorBlueBold();
    printf("%s", hostname);

    setColorRed();
    printf("@");

    setColorBrightCyan();
    printf("%s", username);

    setColorBrightMagenta();
    printf(":~$ ");

    //resetColor();

    //Task 1.1 Basic user prompt
    //printf("prompt:~$ ");
    //This part is commented, because you can't at the same time use two prompts. 
    //We have decided to use the advanced prompt through out the shell.
    //If you want to use the basic prompt, then you should uncomment this part, and comment advanced prompt part
}



//Display of the shell
void initShell()
{
    system("clear"); //clean the terminal/console window 

    setColorBlue();
    
    printf("\n\n\n\t****Welcome to BO$shell!****");
    printf("\n\n\n\t****It is a Linux based shell created and implemented by****");
    printf("\n\n\n\t****two young female students Aldijana and Ajla.****");
    printf("\n\n\n\t****They aspire one day to have their own companies****");
    printf("\n\n\n\t****And be their own bosses.****\n");
   
    //char* username = getenv("USER");
    //printf("\n\n\nUSER is: @%s", username);
    printf("\n");

    //pause the execution of the program for 5 seconds before resuming
    sleep(5); 
    system("clear");
}



//Tokens function: handles user input and commands and functions related to it
void tokensFunction(){
    char *command[MAX_COMMAND_LENGTH]; //command length (not used)
    char *arguments[MAX_NUM_ARGUMENTS];  //max number of  arguments command can have (each token is stored in arguments)
    char input[MAX_COMMAND_LENGTH]; //input from user
    //int status;  //not used tho

  //infinite loop to take user prompt
    while (1) {
        takePrompt();
        fgets(input, MAX_COMMAND_LENGTH, stdin);  
        input[strlen(input) - 1] = '\0';  // Remove newline character

        //user can exit command
        if (strcmp(input, "exit") == 0) {
            printf("Goodbye!\n");
            break;
        }

    //first call to strok() --> returns pointer to first token in "input"

    //Tokenize (split) the "input" string by spaces with strtok() 
    char *token = strtok(input, " ");   //strtok() -> extracting tokens from "input", limit is " " (space)
    int i = 0;  
    
    //while token is not null and is less than max number of arguments
    while (token != NULL && i < MAX_NUM_ARGUMENTS) {
      arguments[i] = token;  //store each token in arguments variable/array
      token = strtok(NULL, " ");  //next calls  with null as first argument, will continue to return pointer to next token in input string, until no more tokens found
      i++;
    }

    //Handling possible errors 
    //if command extends the limited amout of arguments
    if (i == MAX_NUM_ARGUMENTS) {
      printf("Too many arguments. Maximum number of arguments is %d.\n", MAX_NUM_ARGUMENTS);
      printf("Please enter a new command: \n"); //asks user for input again 
      continue; // Skip the rest of the loop and start over
    }

    // Handle empty input, if user entered 0 
    if (i == 0) {
      printf("Command is empty, please enter again: \n");
      continue; // Skip the rest of the loop and start over
    }

    // Check for built-in commands and execute them, handling errors as well
    if (strcmp(arguments[0], "wc") == 0) {
      if (wc() != 0) {
        printf("Error executing wc.\n");  //wc
      }

    } else if (strcmp(arguments[0], "grep") == 0) {  //grep
      if (grep() != 0) {
        printf("Error executing grep.\n");
      }

    } else if (strcmp(arguments[0], "df") == 0) {  //df
      if (df() != 0) {
        printf("Error executing df.\n");
      }

    } else if (strcmp(arguments[0], "cmatrix") == 0) { //cmatrix
      if (cmatrix() != 0) {
        printf("Error executing cmatrix.\n");
      }

    } else if (strcmp(arguments[0], "owl") == 0) {
        if(owl() != 0){
            printf("Error executing owl. \n");
        }
      system("clear"); //clearing the console screen
    }else {   //if command entered is not part of shell
      printf("%s: Command not found.\n", arguments[0]);
    }
  }
}

//Task 1.2 --> Basic: wc()
//Task 1.2. --> Also intermediate: because we implemented three functionalities of wc command -> number of lines, characters and words. 
//wc() - counts word, lines and characters in the given string
//This is example with wc() where it operates based on the user's input

int wc() {
    char inputTaken[1000];   //this array will hold input text
    int i, count = 0, count2 = 0, count3 = 0;
    
    //Asking user for input
    printf("Please enter some text: ");
    fgets(inputTaken, sizeof(inputTaken), stdin);
     
     //Handiling errors, if input is null and if input is too long
     if (fgets(inputTaken, sizeof(inputTaken), stdin) == NULL) {
        printf("Error reading input\n");
        return 1;
    }
    if (strlen(inputTaken) == sizeof(inputTaken)-1 && inputTaken[sizeof(inputTaken)-2] != '\n') {
        printf("Input too long\n");
        return 1;
    }
     
    //First case: number of words
    printf("The text on which these operations will be performed is:\n%s\n", inputTaken);

    printf("The first option is to count the number of words in the given text.\n");
    for (i = 0; inputTaken[i] != '\0'; i++) {
        if (inputTaken[i] == ' ' && inputTaken[i+1] != ' ')
            count++;
    }
    printf("Number of words in the given text is: %d\n", count + 1);
    
    //Second case: number of lines
    printf("The second option is to count the number of lines in the given text.\n");
    for (i = 0; inputTaken[i] != '\0'; i++) {
        if (inputTaken[i] == '\n')
            count3++;
    }
    printf("The number of lines in the given text is: %d\n", count3 + 1);
    

    //Third case: number of characters
    printf("The third option is to count the number of characters in the given text.\n");
    for (i = 0; inputTaken[i] != '\0'; i++) {
        if (inputTaken[i] >= 'a' && inputTaken[i] <= 'z')
            count2++;
    }
    printf("The number of characters in the given text is: %d\n", count2);

    return 0;
}


/*ANOTHER EXAMPLE OF wc(), where wc operates on the text we passed to it*/
/*int  wc(){

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
    return 0;
} */



//Task 1.2 --> Basic: grep
//grep --> searches for a file containing particular pattern, and displays lines containing that pattern
//grep doesn't return any value, therefore it's type is void
int grep()  //works!
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
        fgets(temp,100,fp);

        //does the pattern appear in line, if yes print it
        if(strstr(temp, pattern)) //temp - max number of characters
            printf("%s",temp);
    }
    fclose(fp);  //Closing the file
}

//Task 1.2 --> Basic: df 
//df -  display information about the file system disk space usage

int df() {
    struct statvfs vfs;
    if (statvfs("/", &vfs) == -1) {
        perror("Error getting file system status");
        exit(EXIT_FAILURE);
    }

    unsigned long total_space = vfs.f_frsize * vfs.f_blocks;
    unsigned long free_space = vfs.f_frsize * vfs.f_bfree;
    unsigned long used_space = total_space - free_space;
    double used_percent = (double) used_space / total_space * 100;

    printf("File system disk space usage:\n");
    printf("Total space: %lu bytes\n", total_space);
    printf("Used space: %lu bytes\n", used_space);
    printf("Free space: %lu bytes\n", free_space);
    printf("Used space percentage: %.2f%%\n", used_percent);

    return 0;
} 

//Task 1.2.1. --> Basic: cmatrix 
//Task 1.2.2. --> Also intermediate: We added foreground and background color, and used different random characters, and not only letters
int cmatrix() {
    int i, j, k, col, length, speed;
    char matrix[MAX_ROWS][MAX_COLS];
    char letter;
   
    srand(time(NULL));
   
    for (i = 0; i < MAX_ROWS; i++) {
        for (j = 0; j < MAX_COLS; j++) {
            matrix[i][j] = ' ';
        }
    }
   
    while (1) {
        // Randomly select a column, letter, length, and speed for the falling character
        col = rand() % MAX_COLS;
        length = rand() % MAX_LENGTH + 1;
        speed = rand() % (MAX_SPEED - MIN_SPEED) + MIN_SPEED;
       
        // "Drop" the characters by setting the appropriate matrix elements
        for (k = 0; k < length; k++) {
            if (k + i < MAX_ROWS) {
                letter = (char)((rand() % 26) + 'a');
                matrix[k + i][col] = letter;
            }
        }
       
        // Print the matrix to the screen, with green text on black background
        system("clear");           
        printf("\033[40m\033[32m");  // set background to black and foreground to green
        for (i = 0; i < MAX_ROWS; i++) {
            for (j = 0; j < MAX_COLS; j++) {
                letter = matrix[i][j];
                if (letter != ' ') {
                    printf("\033[32m%c", letter); // set foreground to green before printing each character
                } else {
                    printf("\033[30m%c", letter); // set foreground to black for empty spaces
                }
            }
            printf("\n");
        }

        printf("\033[0m"); // reset color
       
        // Shift the matrix down by a random number of rows
        int shift = rand() % 3 + 1;
        for (i = MAX_ROWS - 1; i > shift; i--) {
            for (j = 0; j < MAX_COLS; j++) {
                matrix[i][j] = matrix[i - shift][j];
            }
        }
        for (j = 0; j < MAX_COLS; j++) {
            matrix[shift][j] = ' ';
        }
       
        // Pause shortly before starting the next iteration
        usleep(speed);
    }
   //dodati opciju da izadje
    return 0;
}

//Task 1.2.2. Intermediate b) - Create something that does not exist in the bash
//We created a custom owl figure in different colors that moves
int owl(){

    setColorBrightCyan();
    printf(" '___'\n");
    setColorRedBold();
    printf(" (O,O)\n");
    setColorYellowBold();
    printf("  /)_)\n");
    setColorGreen();
    printf("   ""  \n");
    
    for (int i = 0; i < 200; i++){
        system("sleep 0.01"); // movement of the owl
        system("clear");
        owl(i); // the owl moves 120 spaces
        }

    //to reset the colors after command execution
    resetColor();
    return 0;
} 

//owl druga verzija
/*int owl(){
    setColorBrightCyan();
    printf(" '___'\n");
    setColorRedBold();
    printf(" (O,O)\n");
    setColorYellowBold();
    printf("  /)_)\n");
    setColorGreen();
    printf("   ""  \n");


    //to reset the colors after command execution
    resetColor();
    return 0;
} */



//Task 1.2 Advanced - Redirect output to a text file
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

//Task 1.4 Adding color to the shell and text.
//For changing the text color/style of text we used ANSI escape sequence.
//We created functions for different combinations of colors, created of normal density or higher and normal shade or lighter.

void setColorYellow() {
    printf("\033[0;33m");
}
void setColorYellowBold() {
    printf("\033[1;33m");
}
void setColorBrightYellowBold() {
    printf("\033[1;93m");
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
void setColorBrightGreen(){
    printf("\033[0;92m");
}

void setColorCyan(){
    printf("\033[0;36m");
}
void setColorBrightCyan(){
    printf("\033[0;96m");
}
void setColorBrightMagenta(){
    printf("\033[0;95m");
}

//Now, we have functions to set the background and foreground color at the same time
void setCyanAndBrightGreen(){
    printf("\033[46m\033[92m");
}
void setBlackAndBrightWhite(){
    printf("\033[40m\033[97m");
}
void setWhiteAndRed(){
    printf("\033[47m\033[91m");
}
void setMagentaAndBrightCyan(){
    printf("\033[35m\033[96m");
}
void setWhiteAndBlack(){
    printf("\033[47m\033[30m");
}

//Reset to the default colors of the shell
void resetColor() {
    printf("\033[0m");
}



int main() {

    initShell();

    //calling function to change background and foreground color
    setBlackAndBrightWhite(); //?

    
    system("clear");
    printf("Aldijana and Ajla"); 


    tokensFunction();

    return 0;


}


