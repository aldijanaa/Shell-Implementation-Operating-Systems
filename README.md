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
In a single-core, uniprocessor system that supports multiprogramming, the CPU time is divided among various tasks, enabling them to operate simultaneously. Every process is given a time window, or quantum, in which to carry out its operations. There can only be one process running at a time on a single-core, uniprocessor system that supports multiprogramming. However, several processes may be in a "running" or "ready" state while they wait for the CPU to execute them. The individual operating system and the available system resources, such as CPU speed, memory, and I/O bandwidth, determine the maximum number of processes that can be active at any given time

#
### Question 2: Explain why system calls are needed for a shared memory method of inter-process communication (IPC). If there are multiple threads in one process, are the system calls needed for sharing memory between those threads?
#
System calls are needed because each process has it's own unique address space, and the kernel must be involved when dealing with the address space of other processes.
When two or more processes need to communicate with each other using shared memory, they need to ask the operating system to provide a shared memory region that they can access. This is done using system calls. Threads share their address space by definition, so they don't need to make a system call to share memory.
# Outline Of The Assignment
A simple implementation of a shell with the use of tokens, where user can execute commands such as wc, grep, cmatrix.<br />
There is also redirecting output to a file (ex. wc ajla.txt > output.txt),  as well as piping implemented. We used basic system calls such as fork(), wait(), execvp() to execute commands and create new processes.
For additional visual creativity, we added colors to the user's name, as well as a custom figure kitten.
# 
Shell.c has implementation of following commands: <br />
-wc --> run like this: wc fileName -option(l,w,c...) <br />
-grep --> run like this: grep -option(c,i,f...) pattern fileName.txt <br />
-cmatrix --> run like this: cmatrix -options(a,b - bold, o; to exit from cmatrix press q) <br />
-df --> run like this: df (tells about disk storage) <br />
-kitten --> run like this: kitty <br />
-quote --> run like this: quote (will display random quote in random color) <br />
-exit <br />



# Shell.c has implementation of following system calls:
fork(), wait(), execle(), execvp(), forkbomb(), execvp(),
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

# Resources
https://www.geeksforgeeks.org/making-linux-shell-c/
https://github.com/TunsAdrian/Linux-Terminal/blob/master/Source%20code/shell.c
https://blog.ehoneahobed.com/building-a-simple-shell-in-c-part-1
https://indradhanush.github.io/blog/writing-a-unix-shell-part-1/
https://linux.die.net/man/  
https://www.geeksforgeeks.org/exec-family-of-functions-in-c/
https://www.tecmint.com/wc-command-examples/#:~:text=The%20followings%20are%20the%20options,of%20bytes%20in%20a%20file.
https://codesteps.com/2014/05/19/c-programming-creating-a-child-process-using-clone/





