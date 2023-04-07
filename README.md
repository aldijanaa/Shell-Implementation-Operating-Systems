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
Shared memory is a popular method for inter-process communication (IPC) in modern operating systems. It allows multiple processes to access the same physical memory location simultaneously, which can greatly improve performance and reduce the overhead of message passing or other IPC methods.
However, when multiple processes access the same shared memory region, proper synchronization is crucial to prevent data corruption, race conditions, and other synchronization issues. System calls are essential for shared memory IPC because they provide a way for processes to coordinate and synchronize their access to shared memory regions.
In most modern operating systems, system calls such as shmget(), shmat(), and shmdt() are used to manage shared memory regions. These system calls provide a way for processes to create shared memory regions, attach to them, detach from them, and perform other operations related to shared memory IPC. However, because multiple processes can access the same memory addresses within the shared memory region, proper synchronization mechanisms must be used to prevent synchronization issues. Techniques such as mutexes, semaphores, and atomic operations can be used to coordinate access to shared memory between processes. When multiple threads exist in one process, they all share the same memory space, so system calls are generally not needed for sharing memory between those threads. In other words, threads within a process can share memory simply by accessing the same memory addresses. However, just like with inter-process communication, proper synchronization mechanisms must still be used to prevent race conditions and other synchronization issues. Techniques such as mutexes, semaphores, and atomic operations can be used to coordinate access to shared memory between threads within a process.



# 
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
  
  - Custom commands: quote, kitty
  
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

# Resources
https://www.geeksforgeeks.org/making-linux-shell-c/
https://github.com/TunsAdrian/Linux-Terminal/blob/master/Source%20code/shell.c
https://blog.ehoneahobed.com/building-a-simple-shell-in-c-part-1
https://indradhanush.github.io/blog/writing-a-unix-shell-part-1/
https://linux.die.net/man/  
https://www.geeksforgeeks.org/exec-family-of-functions-in-c/
https://www.tecmint.com/wc-command-examples/#:~:text=The%20followings%20are%20the%20options,of%20bytes%20in%20a%20file.
https://codesteps.com/2014/05/19/c-programming-creating-a-child-process-using-clone/





