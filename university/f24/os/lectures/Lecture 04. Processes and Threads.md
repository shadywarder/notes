d### Processes
A process is an **abstraction of running program**
Processes support the ability to have (pseudo) concurrent operation even when there is only one CPU available
Example:
- Web server serves many requests from different users simultaneously
- OS on User PC is able to run several processes: email client, antivirus, word processor and so on

In any multiprogramming system, the CPU switches from process to process quickly
At any one instant the CPU is running only one process
In the short period of time, it may work in several of the processes
Such an illusion of parallelism is called **pseudo parallelism**

### The Process Model
All the runnable software on the computer, sometimes including the OS, is organized into a number of **(sequential) processes**
A process is an instance of an **executing program** including the current values of the program counter, registers, and variables
**Conceptually**, each process has its own CPU
It reality, the real CPU switches between different processes. Such a switching is called **multiprogramming**

There is only one physical program counter, so when each process runs, its logical program counter is loaded into the real program counter. When it is finished (for the time being), the physical program counter is saved in the process' stored logical program counter in memory

An example of a computer multiprogramming four programs in memory

![[Pasted image 20240909220346.png]]

Each of the processes has its own flow of control (i.e., its own logical program counter) and runs independently of the other ones 

![[Pasted image 20240909220527.png]]

All the processes have made progress, but at any given instant only one process is actually running 

![[Pasted image 20240909221308.png]]

The difference between a program and a process:
- A program is a set of instructions. It is not doing anything (like a recipe from recipe book)
- A process is an activity of some kind. It has a program, input, output, and a state (like a cook following a recipe from a book)
If a program is running twice, it counts as two distinct processes

### Process Creating
Four principal events that cause processes to be created:
- System initialization
- Execution of a process creation system call by a running process
- A user request to create a new process
- Initiation of a batch job

In UNIX, there is only system call to create a new process: **fork**, which creates **an exact clone** of the calling process
After the fork, the parent and the child processes, have the same memory image, environment strings and open files
Usually, the child process then executes **execve** or a similar system call to change its memory image and run a new program
The child can manipulate its file descriptors after the **fork** but before the **execve** in order to accomplish redirection of standard input, standard output, and standard error

### Process Termination
Typical conditions which terminate a process:
- Normal exit (voluntary)
- Error exit (voluntary)
- Fatal error (involuntary)
- Killed by another process (involuntary)

### Process Hierarchies 
In some systems the parent process and child process continue to be associated in certain ways. The child process can itself create more processes, forming a **process hierarchy**
In UNIX, a process and all of its children and further descendants together form a **process group**
For example, when a user sends a signal from the keyboard, the signal is delivered to all members of the process group currently associated with the keyboard. Each process can catch the signal, ignore the signal, or to be killed by the signal (default action)

### Process States
Three states a process may be in
- Running (actually using the CPU at that instant)
- Ready (runnable; temporarily stopped to let another program run)
- Blocked (unable to run until some external event happens)
When a process blocks, it does so because logically it cannot continue (waiting for input that is not yet available)
Different situation is when OS decides to allocate the CPU to another process for a while

![[Pasted image 20240909224444.png]]

Transition 1 (Running -> Blocked):
- occurs when the OS discovers that a process cannot continue right now
- in some systems the process executes a system call, such as **pause**
- in UNIX and some other systems the process is blocked automatically
Transition 2 (Running -> Ready):
- occurs when the scheduler decides that it is time to let another process have some CPU time
Transition 3 (Ready -> Running):
- occurs when it is time for the first process to the CPU to run again since all the other processes have run long enough
Transition 4 (Blocked -> Ready):
- occurs when the external event for which a process was waiting (such as the arrival of some input) happens
- **if no other process is running at the moment, transition 3 will be triggered and the process will start running**

![[Pasted image 20240909231230.png]]

The complete list of process states is:
- The process is executing in user mode
- The process is executing in kernel mode
- The process is not executing but is ready to run as soon as the kernel schedules it
- The process is sleeping and resides in main memory
- The process is ready to run, but the swapper (process 0) must swap the process into main memory before the kernel can schedule it to execute