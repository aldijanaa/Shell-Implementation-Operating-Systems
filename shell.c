///opet novi shell estagfirulahh  -- 300 ajlin original


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

#define MAX_COMMAND_LENGTH 100
#define MAX_NUM_ARGUMENTS 10

//declaration of functions
void takePrompt();
void setColorYellow();
void setColorRed();
void setColorBlue();
void setColorGreen();
void setColorCyan();
void setColorBrightCyan();
void setColorBrightMagenta();
void resetColor();
//void newColor();

void print_random_quote();
void my_cat();
void table_of_content();


void my_cat() {
  for (int i = 0; i < 120; i++) {
        usleep(50000); // wait for 50 milliseconds
        system("clear"); // clear the screen
        for (int j = 0; j < i; j++) {
            printf(" "); // print spaces before the cat
        }
        setColorBlue();
        printf("         /\\_/\\    \n");
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
        printf("      \\_______/  \n");
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
  
  printf("Meow! Here's your custom cat function.\n");
}


void table_of_content() {
  printf("Table of contents:\n");
  printf("1. WC - \n");
  printf("2. DF- Describe free disk space\n");
  printf("3. Cmatrix- Digital Rain\n");
  printf("4. Grep - \n");

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

//Another way to set color of text
/*void newColor() {
    printf("\x1B[44m"); // Set background color of the text to blue
    printf("Hello, from Aldijana and Ajla!\n");
    printf("\x1B[0m"); // Reset to default color

}*/

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
    setColorBlue();
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



int main() {
  char *command[MAX_COMMAND_LENGTH];
  char *arguments[MAX_NUM_ARGUMENTS];
  char input[MAX_COMMAND_LENGTH];
  int status;

  //Changing name of the terminal window, where  033]0 --> start  and \007 --> end
  printf("\033]0;Aldijana and Ajla's shell\007");

  while (1) {
    takePrompt();
    fgets(input, MAX_COMMAND_LENGTH, stdin);
    input[strlen(input) - 1] = '\0';  // Remove newline character

    // Tokenize the command string by spaces
    char *token = strtok(input, " ");
    int i = 0;
    char *out_file = NULL;
    int pipefd[2];

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
else if (strcmp(token, "|") == 0) {
    token = strtok(NULL, " ");
    pipe(pipefd);
    pid_t pid = fork();
    if (pid == 0) {  // Child process
      dup2(pipefd[1], STDOUT_FILENO);
      close(pipefd[0]);
      close(pipefd[1]);
      execvp(command[0], command);
      perror("execvp");  // This line only executes if execvp fails
      exit(1);
    } else if (pid > 0) {  // Parent process
      dup2(pipefd[0], STDIN_FILENO);
      close(pipefd[0]);
      close(pipefd[1]);
      command[0] = token;
      continue;
    } else {  // Error forking
      perror("fork");
      exit(1);
    }
  }

      arguments[i] = token;
      token = strtok(NULL, " ");
      i++;
    }
    arguments[i] = NULL;  // Set the last argument to NULL for execvp

    // Check for the "exit" command
    if (strcmp(arguments[0], "exit") == 0) {
printf("You exited the shell! Goodbye.");
      break;
    }

    // Check for the "man" command
    if (strcmp(arguments[0], "man") == 0) {
      // Open the manual page for the specified command
      char manual_page[100];
      sprintf(manual_page, "man %s", arguments[1]);
      system(manual_page);
      continue;  // Prompt the user for input again
    }

    // Check for supported commands and execute them
    if (strcmp(arguments[0], "cat") == 0) {
      my_cat();
    } else if (strcmp(arguments[0], "content") == 0) {
      table_of_content();
    }  else if (strcmp(arguments[0], "quote") == 0) {
      print_random_quote();
} else {
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

void print_random_quote() {
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
