## IPC
It provides a mechanism to exchange data across multiple processes. We have different ways to implement IPC.
- Pipes
	- a half-duplex method (or one-way communication). It has a read end (`pipefd[0]`) and a write end (`pipefdp[1]`). Data written to the write end of a pipe can be read from the read end of the pipe. (`man 7 pipe`)
	- lasts only as long as the process created it.
	- `int pipe(int pipefd[2])` system call. (`man 2 pipe`)
- Named pipes (FIFO files)
	- An extension to the traditional pipe and it can last as long as the system it up (beyond the life of the process).
	- Similar to regular files but it follows FIFO.
	- `mkfifo()` library function.
- Message Queues
- Shared Memory

Example:
- What are file decriptors?
	- *File descriptors* provide a primitive, low-level interface to input and output operations and are represented as objects of type `int`. They can represent a connection to a device (such as terminal), or a pipe for communicating with another process.

## POSIX Threads
A *language-independent* thread model (although its API is provided in C) developed by IEEE.
In C language, it provides functions and macros for:
- Thread management (creating, deletion, cancellation, etc.).
- Mutexes
- Condition variables
- Advanced thread synchronization mechanism.
Semaphores are not part of the standard, but they are provided as an appendix.

## Thread Creation and Deletion

```c
#include <pthread.h>

pthread_t pthread_self(void
					  
void ∗start routine(void ∗arg);
int pthread create(pthread_t* thread, const pthread_attr_t∗ attr,
void* (∗start routine)(void ∗), void∗ arg);
					   
void pthread exit(void* retval);
```

## Thread Synchronization
The race condition is an undesirable situation in OS, and we need to find a way to prevent the threads/processes from entering the critical region/section. We can achieve this desire by synchronizing the threads/processes.

We will learn about 3 thread synchronization mechanisms:
- Joins 
- Mutexes
- Condition variables (Optional)

Semaphores are also widely used thread synchronization mechanism.

## Joins

```c
#include <pthread.h>

int pthread_join(pthread_t thread, void** value_ptr);
```

`pthread_join` blocks the calling thread until the specified thread has finished executing, storing its return value.

