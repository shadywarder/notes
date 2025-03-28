**2025-03-17 15:50**
**Tags:** [os](../2%20-%20tags/os.md)

## Concurrency Is Not What You Think
### Running a Program Back Then

Computer was not able to just tack the source code of the program and execute it. Before, the compiler needed to be loaded onto the computer (from magnetic tapes). It was programmer's responsibility to mount this tape and wait for the compiler to be loaded in main memory.

Now can input the source code to be translated to assembly language. It still couldn't be executed by the computer because it needed to compiled again down to machine code by an assembler. It was necessary to store the assembly output whether on tapes, punched cards, or other storage methods of the time.

The procedure required mounting another tape with the assembler requiring the programmer to wait once again. Once loaded the assembler would take the compiler output and translate it into the machine code. Only then the program can be executed.

![](../attachments/Pasted%20image%2020250317155957.png)

### Essence of Concurrency

Researchers eventually conceive (постигли) the notion of enabling multiple users to connect to a single computer simultaneously but with the operating system arbitrating access to the hardware.

Under this approach each user accessed the computer through some type of I/O device such as a teletype writer or dumb terminal.

![](../attachments/Pasted%20image%2020250317160141.png)

This arrangement enabled the computer to execute one user's programs while others were either loading theirs or awaiting user input. But what if multiple users were ready to run their programs simultaneously? Well, in that situation things get more complicated. As the computer disposes (распологает) of one processing users would have to share it somehow.

A program is just a sequence of instructions for the computer's CPU to execute one by one. If multiple programs are available for execution the straightforward approach would be to execute them sequentially. However, even though the CPU would always be utilized here, users would have to wait a long time to start seeing results from their programs. 

To address this problem, programs can be broken down into smaller segments and interleaved so that the CPU can execute them in an alternate order.

Thus, since the CPU is fast enough, we will under illusion, that all programs are being executed at the same time.

Such operating system called **time-sharing operating system**. Multics was one of the first **time-sharing operating system** of all time. 

### Personal Computers

It didn't take too much time until PC manufactures started shipping personal computers capable of multitasking. Instead of using concurrency to allow multiple users to use the same computer at the same time, it was used to allow a single user running multiple programs at the same time.

### How Computer Run Instructions

Inside the CPU there are special registers like the instruction register and the address register. The address register holds the memory location of the next instruction the CPU will execute. When the CPU is ready for the next instruction, it fetches this value and copy it to the instruction register. The CPU then decodes this to know what to do next: an addition, a subtraction, a copy operation, whatever. After the instruction is executed, the address register value increases pointing to the next instruction.

`repeat (fetch -> decode -> execute)`

There are also jump instructions. They change the address register value, making the CPU jump to a specific instruction instead of the next one in line. This is key to dealing with conditions and loops in programs.

Because of this, programs don't have to be literally split and mixed instead they're loaded normally and the operating system makes the CPU switch between them by changing the address register value.

![](../attachments/Pasted%20image%2020250317162754.png)

### Interruptions 

Programs depends on the operating system to perform essential tasks. When we use functions to open a file, read and write to it or things like requesting memory, we interacting with the operating system. These interactions occur through interruptions at the hardware level. Interruptions act as signals to the CPU. When the interruptions occurs, the CPU pauses its current task, saves its state by taking a snapshot, saving it in memory and immediately jumps to a predefined location in memory, where the interrupt service routine associated with that specific interruption resides. This routine is somewhere in the memory region allocated to the operating system itself. Programs use interruptions extensively, especially for I/O operations. 

As only the operating system kernel can handle interactions with hardware, this is how the operating system regains control of the CPU. Now that the address register is pointing to the operating system code, the operating system can use the CPU not only to handle the interruptions but to attend other tasks including scheduling processes.

Since I/O operations take time, the process that initiated the interruption is temporarily placed back in the queue while waiting for the hardware response. But before, the process's captured state is stored withing the process information. Then the dispatcher selects another process from the queue and sets the CPU to execute it. Now this process can utilized the CPU until it needs some sort of I/O operation, requiring giving control to the operating system.

However, for example in case of infinite loop with no interruptions within, operating system may never regain control. This poses (представляет) a serious security risk as malicious programs can exploit this vulnerability to monopolize CPU resources, preventing other programs from accessing them. This scheduling method, reliant on process cooperation is known as **cooperative scheduling** or **non-preemptive scheduling** (невытесняющее).

We can fix this by introducing a hardware timer. Once the time expires, the timer triggers an interruption. The timer is typically implemented within the CPU itself, so, before allocating the CPU to any process, the operating system dispatcher uses a privileged to set and start the timer. This mechanism, known as **preemptive scheduling**, offers increased security. However, an operating system can only implement if the hardware supports. 

The Multics was using this type of scheduling right from the beginning.
## References
[CONCURRENCY IS NOT WHAT YOU THINK](https://www.youtube.com/watch?v=3X93PnKRNUo) 