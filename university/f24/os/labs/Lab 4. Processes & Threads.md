## Execution flow of C program

![[Pasted image 20240929223718.png]]

## Program vs. Process
**Program:** is a sequence or set of instructions in a programming language for a computer to execute.
**Process:** is a program in execution.
**Multiprogramming:** is the ability of the OS to load multiple process into the memory which are available to run simultaneously on a **single** CPU.
**Multiprocessing:** is the ability of the OS to load multiple processes into the memory and to allow them to be executed on **multiple** CPUs.
**System call:** The way in which the program enters the OS kernel to perform some task. The manual pages of all system calls can be accessed as (**man 2 *system_call_name***).

## Process States
The three main states of the process.
- Running (actually using the CPU at that instant).
- Ready (runnable; temporarily stopped to let another process run).
- Blocked (unable to run until some external event happens).

![[Pasted image 20240929224301.png]]


## Process Creating and Termination
**Process Creation** 
- Running a program.
- **fork:** creates a new process by duplicating the calling process. The new process is referred to as the *child* process. The calling process is referred to as the *parent* process. It is declared as: (Use `man 2 fork`)

```c
#include <unistd.h>
pid_t fork(void);
```

**Process termination** 
- The process is terminated, usually due to one of the following conditions:
	- Normal exit (voluntary). (Successful termination by exit system call)
	- Error exit (voluntary). (Unsuccessful termination by exit system call)
	- Fatal error (involuntary). (Errors or bugs)
	- Killed by another process (involuntary). (kill system call)
- **exit:** causes process termination. The C standard library specifies two constants. `EXIT_SUCCESS` and `EXIT_FAILURE`, that may be passed to indicate successful of unsuccessful termination. respectively. (Use `man 2 exit`)

## Some Process Management Utilities
Some useful utilities for sleeping, waiting and pausing processes.
- **sleep:** a "system call" used to stop the calling thread (process) for a specific number of seconds passed as an argument.
- **wait:** a system call used to wait for state changes in one of the children of the calling process, and obtain information about the child whose state has changed. A state change is considered to be: the child terminated; the child was stopped by a signal; of the child was resumed by a signal. For instance, to let the parent wait for its $n$ children, you need to call wait function $n$ times and pass `NULL` to this function if you interested in the stage change information.
- **pause:** a system call which causes the calling process (or thread) to sleep until a signal is delivered. 
