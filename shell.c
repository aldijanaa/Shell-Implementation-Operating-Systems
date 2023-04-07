
//Linux shell implementation by Aldijana Culezovic and Ajla Korman
//Necessary libraries
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/statvfs.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <fcntl.h>
#include <time.h>
#include <errno.h>

//function declarations
void setColorYellow();
void setColorRed();
void setColorBlue();
void setColorGreen();
void setColorCyan();
void setColorBrightCyan();
void setColorBrightMagenta();
void resetColor();

//custom functions declarations
void quote();
void kitty();
void content();
void initShell();

//constants declarations
#define MAX_COMMAND_LENGTH 256
#define MAX_NUM_ARGUMENTS 32
#define HOST_NAME_MAX 256
#define PATH_MAX 256



int main() {

 // char *command[MAX_COMMAND_LENGTH]; seems to be unused command
  char *arguments[MAX_NUM_ARGUMENTS];
  char input[MAX_COMMAND_LENGTH];
  int status; //for tracking status of the process

  char hostName[100];                           //Here, host name is stored
  char *login = getlogin();                     //Here, login name is stored and called
  gethostname(hostName, 100);                   //Here, the host name of the machine is received

  //changing name of the terminal where 033] means start and \007 means end
  printf("\033]0;Aldijana and Ajla's Shell\007");

 //Displaying the introduction to the shell
   initShell();


    while (1) {

/*Task 1.1 Basic prompt:
    setColorRed();
    printf("prompt~$: ");
    resetColor();
    Since we can't use two different prompts at the same time, we chose to use advanced prompt
    but if you would like to choose the basic prompt, just comment the advanced prompt.*/

//Task 1.1 Advanced: Prompt that contains machinename and username of device
    setColorBrightMagenta();
    printf("%s", hostName);
    setColorRed();
    printf("@");
    setColorBrightCyan();
    printf("%s", login);
    setColorGreen();
    printf("~$: ");
 
    fgets(input, sizeof(input), stdin);

    input[strlen(input) - 1] = '\0';
        // Remove newline character
       
    if(strcmp(input, "") == 0) {
      continue;
    }

    // Tokenize the command string by spaces
    char *token = strtok(input, " ");
    int i = 0;
    char *out_file = NULL;

    /*int pipefd[2] = {0, 0};
    int pipe_exists = 0;  -> part which was used for piping*/


//Task 1.2 Advanced: Implementation of redirection using > symbol
    while (token != NULL && i < MAX_NUM_ARGUMENTS) {
      if (strcmp(token, ">") == 0) {
        token = strtok(NULL, " ");
        if (token != NULL) {
          out_file = token;
          token = strtok(NULL, " ");
          continue;
        }
        else {
          printf("Output file name missing.\n");
          break;
        }
      }


//Task 1.2 Advanced: Implementation of piping using | symbol
    /*else if (strcmp(token, "|") == 0) {
        pipe_exists = 1;
        token = strtok(NULL, " ");
        command[i] = NULL;
        pid_t pid = fork();
        if (pid == 0) { // Child process
          close(pipefd[0]); // close unused read end
          dup2(pipefd[1], STDOUT_FILENO); // redirect stdout to the write end of the pipe
          close(pipefd[1]); // close the write end of the pipe
          execvp(command[0], command);
          perror("execvp"); // This line only executes if execvp fails
          exit(1);
        } else if (pid > 0) { // Parent process
          close(pipefd[1]); // close the write end of the pipe
          dup2(pipefd[0], STDIN_FILENO); // redirect stdin to the read end of the pipe
          close(pipefd[0]); // close the read end of the pipe
          command[0] = token;
          i = 0; // reset the argument count for the next command
          continue;
        } else { // Error forking
          perror("fork");
          exit(1);
        }
      }*/

//We tried to implement piping, however for some reason whenever we would run, we would be left with an infinitive loop of user prompts

      arguments[i] = token;
      token = strtok(NULL, " ");
      i++;
    }
    arguments[i] = NULL;  // Set the last argument to NULL for execvp

    // Check for the "exit" command --> display goodbye figure
    if (strcmp(arguments[0], "exit") == 0) {
    setColorRed();
    printf("\n");
    printf("\t\t You exited the shell! Goodbye. \n");
    printf("\n");
            setColorCyan();
            printf("\t                   ()   \n");
            printf("\t                 __/\\__             \n");
            printf("\t        |\\   .-\"`      `\"-. /|  \n");
            printf("\t        | \\.'( ') (' ) (. )`./ |     \n");
            printf("\t         \\_                  _/     \n");
            printf("\t           \\  `~\"'=::='\"~`/     \n");
            printf("\t    ,       `-.__      __.-'       ,   \n");
          printf("\t.---'\\________( `\"\"~~\"\"` )________/'---.    \n");
            printf("\t >   )       / `\"\"~~~~\"\"` \\       (   <   \n");
            printf("\t'----`--..__/        -(-)- \\__..--`----'   \n");
            printf("\t            |_____ __ _____|    \n");
            printf("\t            [_____[##]_____]   I HAVE BEEN CHOSEN...\n");
            printf("\t            |              |    FAREWELL MY FRIENDS...\n");
            printf("\t            \\      ||     /     I GO ONTO A BETTER PLACE!\n");
            printf("\t             \\     ||    /    \n");
            printf("\t          .-\"~`--._||_.--'~\"-.  \n");
            printf("\t         (_____,.--\"\"--.,_____)");
            printf("\n");
            resetColor();
      break;
    }

   //If user enters exit or presses CTRL + C, will immediately be taken out of our shell

    // Check for the "man" command
    if (strcmp(arguments[0], "man") == 0) {
      // Open the manual page for the specified command
      char manual_page[100];
      sprintf(manual_page, "man %s", arguments[1]);
      system(manual_page);
      continue;  // Prompt the user for input again
    }

    // Check for supported commands and execute them
    if (strcmp(arguments[0], "kitty") == 0) {
      kitty();
    } else if (strcmp(arguments[0], "content") == 0) {
      content();
    }  else if (strcmp(arguments[0], "quote") == 0) {
      quote();
} else {       //this is for all other commands
      pid_t pid = fork();
      if (pid == 0) {  // Child process
        if (out_file != NULL) {
          int fd = open(out_file, O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
          if (fd == -1) {
            perror("open");
            exit(1);
          }
          if (dup2(fd, STDOUT_FILENO) == -1) {
            perror("dup2");
            exit(1);
          }
          if (close(fd) == -1) {
            perror("close");
            exit(1);
          }
        }
        execvp(arguments[0], arguments);
        perror("execvp");  // This line only executes if execvp fails
        exit(1);
      } else if (pid > 0) {  // Parent process
        waitpid(pid, &status, 0);
      } else {  // Error forking
        perror("fork");
        exit(1);
      }
    }
  }

  return 0;
}

//Task 1.2 Intermediate: Implement something that doesn't exist i the shell
void initShell()
{
    system("clear"); //clean the terminal/console window

 
    setColorCyan();
    printf("\t\t\tWELCOME to the Aldijana and Ajla's shell \n");
    printf("\n");

    setColorBlue();
    printf("\t\t\t .--.            .--. \n");
    setColorBlue();
    printf("\t\t\t( (`\\.\"--``--\".//`) )\n");
    setColorBlue();
    printf("\t\t\t '-.   __   __    .-'  \n");
    setColorBlue();
    printf("\t\t\t  /   /__\\ /__\\   \\  \n");
    printf("\t\t\t |    \\ 0/ \\ 0/    | \n");
    setColorGreen();
    printf("\t\t\t \\     `/   \\`     /  \n");
    setColorGreen();
    printf("\t\t\t  `-.  /-\"\"\"-\\  .-'  \n");
    setColorCyan();
    printf("\t\t\t    /  '.___.'  \\  \n");
    setColorCyan();
    printf("\t\t\t    \\     I     /  \n");
    setColorCyan();
    printf("\t\t\t     `;--'`'--;`   \n");
    setColorCyan();
    printf("\t\t\t        .___..'            \n");
    

    //pause the execution of the program for 5 seconds before resuming
    sleep(5);
    system("clear");
}

//Task 1.2 Intermediate: Implement something that doesn't exist in the shell
//Colorful kitty that moves across the screen and increases its size
void kitty() {
  for (int i = 0; i < 120; i++) {
        usleep(50000); // wait for 50 milliseconds
        system("clear"); // clear the screen
        for (int j = 0; j < i; j++) {
            printf(" "); // print spaces before the cat
        }
        setColorBlue();
        printf("         /\\/\\    \n");
        for (int j = 0; j < i; j++) {
            printf(" "); // print spaces before the cat
        }
        setColorYellow();
        printf("        ( o  o )  \n");
        for (int j = 0; j < i; j++) {
            printf(" "); // print spaces before the cat
        }
        setColorGreen();
        printf("       /  =^=  \\ \n");
        for (int j = 0; j < i; j++) {
            printf(" "); // print spaces before the cat
        }
        setColorBrightMagenta();
        printf("      /   ---   \\\n");
        for (int j = 0; j < i; j++) {
            printf(" "); // print spaces before the cat
        }
        setColorBrightCyan();
        printf("     (    \\/    ) \n");
        for (int j = 0; j < i; j++) {
            printf(" "); // print spaces before the cat
        }
        setColorGreen();
        printf("      \\______/  \n");
        for (int j = 0; j < i; j++) {
            printf(" "); // print spaces before the cat
        }
        setColorBlue();
        printf("       ||    || \n");
        for (int j = 0; j < i; j++) {
            printf(" "); // print spaces before the cat
        }
        setColorRed();
        printf("  MEET OUR CAT CICKO\n");  
}
}

//Task 1.2 Intermediate: Implement something that doesn't exist in the shell
//This functions shows you the functions whose implementation we will shown on Demo Day
void content() {
  setColorYellow();
  printf("Table of contents:\n");
  setColorCyan();
  printf("1. WC- Word count\n");
  setColorRed();
  printf("2. DF- Free disk space\n");
  setColorCyan();
  printf("3. Cmatrix- Digital Rain\n");
  setColorYellow();
  printf("4. Grep - Pattern finder\n");
  resetColor();

}

//Task 1.2 Intermediate: Implement something that doesn't exist in the shell
//This function displays you a random quote in a random color
void quote() {
    // List of quotes
    char *quotes[] = {
        "The greatest glory in living lies not in never falling, but in rising every time we fall. -Nelson Mandela",
        "The way to get started is to quit talking and begin doing. -Walt Disney",
        "Your time is limited, don't waste it living someone else's life. -Steve Jobs",
        "If life were predictable it would cease to be life, and be without flavor. -Eleanor Roosevelt",
        "If you look at what you have in life, you'll always have more. If you look at what you don't have in life, you'll never have enough. -Oprah Winfrey",
        "If you set your goals ridiculously high and it's a failure, you will fail above everyone else's success. -James Cameron",
        "Life is what happens when you're busy making other plans. -John Lennon",
        "Spread love everywhere you go. Let no one ever come to you without leaving happier. -Mother Teresa"
        "If you can see it in your head, you can hold it in your hand. -Walt Disney"
    };

    // List of colors
    char *colors[] = {
        "\033[1;31m",  // Red
        "\033[1;32m",  // Green
        "\033[1;33m",  // Yellow
        "\033[1;34m",  // Blue
        "\033[1;35m",  // Magenta
        "\033[1;36m"   // Cyan
    };

    // Get the number of quotes and colors
    int num_quotes = sizeof(quotes) / sizeof(quotes[0]);
    int num_colors = sizeof(colors) / sizeof(colors[0]);

    // Generate a random index for the quote and color
    srand(time(NULL));
    int quote_index = rand() % num_quotes;
    int color_index = rand() % num_colors;

    // Print the quote in the chosen color
    printf("%s%s\033[0m\n", colors[color_index], quotes[quote_index]);
}


//Task 1.4 Adding color to the shell and text.
//For changing the text color/style of text we used ANSI escape sequence.
void setColorYellow() {
    printf("\033[0;33m");
}
void setColorRed() {
    printf("\033[0;31m");
}
void setColorBlue() {
    printf("\033[0;34m");
}
void setColorGreen() {
    printf("\033[0;32m");
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
//Reset to the default colors of the shell
void resetColor() {
    printf("\033[0m");
}

	
