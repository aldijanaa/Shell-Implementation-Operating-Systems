# Shell-Implementation-Operating-Systems
# GROUP MEMBERS

Aldijana Čulezović <br />
Ajla Korman

# Files
shell.c

# Task 1.1
aldi@ubuntu  <br />
ajla korman...

# Task 1.2
# Answers from Task 1.5
### Question 1: If we have a single-core, uniprocessor system that supports multiprogramming, how many processes can be in a running state in such a system, at any given  time?
# 
In a single-core, uniprocessor system that supports multiprogramming, the CPU time is divided among various tasks, enabling them to operate simultaneously. Every process is given a time window, or quantum, in which to carry out its operations. There can only be one process running at a time on a single-core, uniprocessor system that supports multiprogramming. However, several processes may be in a "running" or "ready" state while they wait for the CPU to execute them. The individual operating system and the available system resources, such as CPU speed, memory, and I/O bandwidth, determine the maximum number of processes that can be active at any given time

#
### Question 2: Explain why system calls are needed for a shared memory method of inter-process communication (IPC). If there are multiple threads in one process, are the system calls needed for sharing memory between those threads?
#
System calls are needed because each process has it's own unique address space, and the kernel must be involved when dealing with the address space of other processes.
When two or more processes need to communicate with each other using shared memory, they need to ask the operating system to provide a shared memory region that they can access. This is done using system calls. Threads share their address space by definition, so they don't need to make a system call to share memory.

