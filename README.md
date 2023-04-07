# Shell-Implementation-Operating-Systems
# GROUP MEMBERS
Aldijana Čulezović <br />
Ajla Korman

# Files
shell.c <br />
clone.c <br />
forkwait.c <br />
forkbomb.c <br />
execle.c <br />


# Answers from Task 1.5
### Question 1: If we have a single-core, uniprocessor system that supports multiprogramming, how many processes can be in a running state in such a system, at any given  time?
# 
There can only be one process running at a time on a single-core, uniprocessor system that supports multiprogramming. However, several processes may be in a "running" or "ready" state while they wait for the CPU to execute them. The individual operating system and the available system resources, such as CPU speed, memory, and I/O bandwidth, determine the maximum number of processes that can be active at any given time.
In a single-core, uniprocessor system that supports multiprogramming, only one process can be in the running state at any given time becuase we only have enough components(registers, CU and ALU) to  execute one instruction at a time, so it can only be actively running one process at any given moment. However,  multiple processes can be supported by using a technique called time-sharing, where the CPU rapidly switches between processes, giving the illusion of concurrent execution. So while only one process can be running at any given moment, the system can still support multiple processes in a time-shared manner. The number of processes that can be supported in such a system depends on factors such as the amount of available memory and the scheduling algorithm used by the operating system.
#
### Question 2: Explain why system calls are needed for a shared memory method of inter-process communication (IPC). If there are multiple threads in one process, are the system calls needed for sharing memory between those threads?
#
Shared memory is a popular method for inter-process communication (IPC) in modern operating systems. It allows multiple processes to access the same physical memory location simultaneously, which can greatly improve performance and reduce the overhead of message passing or other IPC methods.
However, when multiple processes access the same shared memory region, proper synchronization is crucial to prevent data corruption, race conditions, and other synchronization issues. System calls are essential for shared memory IPC because they provide a way for processes to coordinate and synchronize their access to shared memory regions.
In most modern operating systems, system calls such as shmget(), shmat(), and shmdt() are used to manage shared memory regions. These system calls provide a way for processes to create shared memory regions, attach to them, detach from them, and perform other operations related to shared memory IPC. However, because multiple processes can access the same memory addresses within the shared memory region, proper synchronization mechanisms must be used to prevent synchronization issues. Techniques such as mutexes, semaphores, and atomic operations can be used to coordinate access to shared memory between processes. When multiple threads exist in one process, they all share the same memory space, so system calls are generally not needed for sharing memory between those threads. In other words, threads within a process can share memory simply by accessing the same memory addresses. However, just like with inter-process communication, proper synchronization mechanisms must still be used to prevent race conditions and other synchronization issues. Techniques such as mutexes, semaphores, and atomic operations can be used to coordinate access to shared memory between threads within a process.



# Outline of the Project
For the first part of our project from the course "Operating System" we implemented a Linux Shell using tokens (especially execvp()). Now, users can enter the command name, flags, file names and even more in a single line and execute that command. User can choose between the two types of the user prompt (advanced or basic), which come with appropriate colors. We have also implemented redirection, so everytime symbol " > " is used between a command and another file (ex. wc ajla.txt > output.txt),  the output of the first command will be saved in the given file. Besides redirecting, we put great effort into implementing piping. If the user isn't sure, what does the certain command stnad for, can't think of the proper flag they're looking for, they can always type in terminal "man <commandName>", and this will take them to manual page where user can read everything regrading that command. We added couple of our own unique functions such as initShell(introduction to our shell), quote(displays random quote in a random color), kitty (a colorful kitty animation that moves across the screen and increases its size) and content(displays some of the commands and their colorful definitions). We have also written system calls such as fork(), wait(), exec(), execle(), clone() and forkbomb() which can be executed and new processes can be created. But be careful, when it comes to execution of forkbomb - it is a type of Ddos attack.

Shell.c has implementation of following commands: <br />
  - wc with options(flags)
  * l - count lines
  * w - count words
  * c - count characters
  * b - count byte
  
  - cmatrix with flags
  * r - rainbow mode
  * s - space mode
  * B - bold letters mode
  
  - grep
  - df
  - exit
  - man
  - Redirecting output to a file
  
  - Custom commands: quote, kitty, content
  
Shell.c has implementation of following system calls: fork(), wait(), execle(), execvp(), forkbomb(), execvp(),

#
# Project was built with
- Visual Studio Code and nano editor in Ubuntu
- Written in C Language
- Tested through Ubuntu, in terminal window

# Instructions to clone the repository
git clone https://github.com/aldijanaa/Shell-Implementation-Operating-Systems.git
# Instructions for compiling
Save the file with extension c and then run the file like this in the terminal window: <br />
``` gcc -o shell shell.c - Wall (contains more flags) OR gcc shell.c-o shell``` <br/>

```./shell ``` <br/>

# Challenges
Hard to grasp and understand advanced aspects of C Programming Language. <br/>
Lack of understanding what was asked from us to implement exactly, so the first time we implemented the whole shell from scratch by writing our own code for wc, grep, cmatrix, df and others. <br/>
Difficulty to understand and implement concept of piping, we put a great effort into trying to resolve a problem. We tried several of different approaches, however none of those gave us the needed, correct solution. <br/>

# Explanation for the code that doesn't work
We experienced problems with the implementation of piping using " | ". Piping represents using output of one process as an input of the second process. So the logic, which we were following is that we wanted to create two or more child processes and then connect them through pipes. So the code that we wrote piping can be described as following:
- First we used a flag pipe_exists to indicate that a pipe exists in the command
- Then, the strtok function was supposed to extract the next token in the command line, which was the next command to be piped to.
- Using fork, a child process would be created. If the fork returns 0, that would be the child process and the output code would be redirected  to the write end of pipe using the dup2 function, and then executed using the execvp function. If execvp fails, an error message is printed using the perror function, and the child process exits with an error code. If fork return a positive value, then this is a parent process and its input would be redirected as read end of pipe using the dup2 function. Then a "current" command will be set to be the next token which is extracted from the input command line. If the fork function returns a negative value, it means that an error occurred while forking, and an error message is printed and the process exits with an error code.
- The problem we then had, was when we entered two processes which we wanted to be piped with one another, and infinitive amount of user prompts would appear, and we couldn't figure out why.

If we had more time, we would pay more attention to the part with tokens and input, because we think that was the problem that was causing the issue. We used strtok to tokenize the input here, however we don't think that it handled spaces correctly. So, we would definitely put some kind of a delimiter there. Also, we would check, if we wrote the code for wait() correctly, because wait() should wait for all child processes to finish, and not only one. Also, since execvp() is used to handling executions, we would double check, if we used proper arguments there.



# Resources
https://www.geeksforgeeks.org/making-linux-shell-c/
https://github.com/TunsAdrian/Linux-Terminal/blob/master/Source%20code/shell.c
https://blog.ehoneahobed.com/building-a-simple-shell-in-c-part-1
https://indradhanush.github.io/blog/writing-a-unix-shell-part-1/
https://linux.die.net/man/  
https://www.geeksforgeeks.org/exec-family-of-functions-in-c/
https://www.tecmint.com/wc-command-examples/#:~:text=The%20followings%20are%20the%20options,of%20bytes%20in%20a%20file.
https://codesteps.com/2014/05/19/c-programming-creating-a-child-process-using-clone/





