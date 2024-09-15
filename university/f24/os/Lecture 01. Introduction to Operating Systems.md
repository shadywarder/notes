## What is Operating System?
The OS is a layer of software that:
- Provides user programs with a better, simpler, cleaner model of the computer
- Handles managing all the resources

## Kernel mode & User mode
Most computers have two modes of operation: kernel mode and user mode

![[Pasted image 20240908161531.png]]

### Kernel mode
The operating system runs in kernel mode (also called supervisor mode):
- Has complete access to all the hardware
- Can execute any instruction the machine is capable of

### User mode
The rest of the software runs in user mode:
- Only a subset of the machine instructions is available
- The instructions that affect control of the machine or do I/O are forbidden to user-mode program
- To obtain services form the OS, a user program must make a system call (TRAP), which traps into the kernel and invokes the OS

## The OS as an Extended Machine
Top-down view
- Problem:
	- hardware is very complicated and presents difficult and inconsistent interfaces to the software developers
- Solution:
	- use abstractions, for instance, a disk driver, that deals with the hardware and provides an interface to read and write disk blocks


## The OS as a Resource Manager
Bottom-up view
- Manage all the pieces of a complex system
- The job of the operating system is to provide for an orderly and controlled allocation of the processors, memories, and I/O devices among the various programs wanting them


Multiplexing(sharing) resources can be done in two ways:
- Time multiplexing
	- different programs or users take turns using it (example: CPU, printers)
- Space multiplexing
	- instead of the customers taking turns, each one gets part of the resource (example: memory, disks)


## Computer Hardware
An OS is tied to the hardware of the computer it runs on. It extends the computer's instruction set and manages its resources
- Processors
- Main memory
- Disks
- I/O devices
- Buses

![[Pasted image 20240908162905.png]]

### Processors
The basic cycle of every CPU:
- **Fetch Instruction** - read next expected instruction into buffer
- **Decode Instruction** - determine opcode operand specifiers
- **Calculate Operands** - calculate the effective address of each source operand
- **Fetch Operands** - fetch each operand from memory. Operands in registers need not be fetched
- **Execute Instruction** - perform the indicated operation and store the result
- **Write Operand** - store the result in memory


CPU contains some registers inside to hold key variables and temporary results:
- **General registers** - hold variables and temporary results
- **Program counter** - contains the address of next instruction to be fetched
- **Stack pointer** - points to the current stack in memory
- **PSW (Program Status Word)** - bits of results of comparison instructions, the CPU priority, the mode (kernel or user) and various other control bits


Multithreading or hyper-threading
- It allows CPU to hold the state of two different threads and then switch between then in nanoseconds
- If one of the processes needs to read a word from memory (long operation), a multithreaded CPU can just switch to another thread thus saving time
- Multithreading does not offer true parallelism



| Feature               | Multithreading                                        | Hyperthreading                                                   |
| --------------------- | ----------------------------------------------------- | ---------------------------------------------------------------- |
| Definition            | Multiple threads within a single process concurrently | Single physical processor operates as two virtualized processors |
| Resource Sharing      | Each thread has its own set of execution resources    | Threads share the execution resources of a single physical core  |
| Implementation        | Software or hardware level                            | Hardware level                                                   |
| Hardware Requirements | Multiple physical cores required                      | Single physical core capable of running multiple threads         |

| Multitreading                                                       | Hyperthreading                                                                    |
| ------------------------------------------------------------------- | --------------------------------------------------------------------------------- |
| More processing power                                               | Handles multiple threads efficiently                                              |
| Leads to significant performance for tasks that can be parallelized | Leads to improved performance for tasks that require a high degree of parallelism |
| Requires a processor with multiple physical cores                   | Doesn't provide as much processing power as multithreading                        |
| More expensive and may not be available on all systems              | May cause contention and cache thrashing                                          |

Hyperthreading breaks a single physical processor into two logical/virtual processors, whereas multithreading simultaneously runs numerous threads in a single process.

![[Pasted image 20240908165918.png]]


Many CPU chips now have some complete processors or cores. Making use of such a multicore chip will require a multiprocessor OS
- A modern GPU (Graphics Processing Unit) is a processor with thousands of tiny cores which are very good for many small computations done in parallel, like rendering polygons in graphics applications
- Multicore chips do true parallelism

### Memory
The memory system is constructed as a hierarchy of layers. The top layers have higher speed, smaller capacity, and greater cost per bit than lower ones

![[Pasted image 20240908174046.png]]

Main memory is divided up into cache lines, typically 64 bytes. The most heavily used cache lines are kept in high-speed cache located inside the CPU.

When the program needs to read a memory word, the cache hardware checks to see if the line needed is in the cache. If it is (a cache hit), no memory request is sent over the bus to the main memory. It normally takes about 2 clock cycles.

Caching system issues:
- When to put a new item into the cache
- Which cache line to put the new item in
- Which item to remove from the cache when a slot is needed
- Where to put a newly evicted item in the larger memory


### I/O Devices
Generally consist of two parts:
- a controller that accepts commands from the operating system and carries them out
- a device itself that has fairly simple interfaces, both because they cannot do much and to make them standard

Device driver is a software that talks to a controller, giving it commands and accepting responses. It has to be put into the OS so it can run in kernel mode

Every controller has a small number of registers that are used to communicate with it. The collection of all the device registers forms the **I/O port space**

Interrupt:
- The driver starts the device and asks it to give an interrupt when it is finished. The operating system then blocks the caller if need be and looks for other works to do
- When the controller detects the end of the transfer, it generates an interrupt to signal completion. The device number may be used as an index into part of memory to find the address of the interrupt handler for this device. This part of memory is called **the interrupt vector**

![[Pasted image 20240908231449.png]]

Direct Memory Access (DMA):
- DMA is a chip that can control the flow of bits between memory and some controller without constant CPU intervention
- The CPU programs the DMA chip, telling it what and where to transfer and lets it go. When the DMA chip is done, it causes an interrupt

![[Pasted image 20240908231509.png]]

### Buses
The system has many buses, each with a different transfer rate and function. The OS must be aware of all of them for configuration and management.
A shared bus architecture means that multiple devices use the sane wires to transfer data which needs an arbiter to determine who can use the bus.

A parallel bus architecture means that you send each word of data over multiple wires. For instance, in regular PCI buses, a single 32-bit number is sent over 32 parallel wires.

![[Pasted image 20240908233154.png]]

A serial bus architecture sends all bits in a message through a single collection, known as a lane. Parallelism is still used, because you can have multiple lanes in parallel (sen 32 messages via 32 lanes).

![[Pasted image 20240908233323.png]]

Double Data Rate (DDR3, DDR4) connects CPU and RAM
Peripheral Component Interconnect (PCIe) is a bus to an external graphical device 
Direct Media Interface (DMI) is a link between north bridge and south bridge - a hub for all the other devices
SCSI, SATA - connects hard disks
Universal Serial Bus (USB is a centralized bus in which a root device polls at the I/O devices to see if they have any traffic.

Before plug and play, each I/O card had a fixed interrupt request level and fixed address for its I/O registers. And two different pieces of hardware might use the same interrupt, so they will conflict
Plug and play makes the system automatically collect information about the I/O devices, centrally assign interrupt level and I/O addresses, and then tell each card what its numbers are

### Booting the Computer
**Basic Input Output System (BIOS)** is a program on the parent board that contains low-level I/O software.
After the BIOS is started it performs **Power-On Self-Test (POST)** to test integrity and see how much RAM is installed and other basic devices are installed and responding correctly.

Is starts out by scanning the buses to detect all the devices attached to them. Then it determines the boot device by trying a list of devices stored in the **CMOS** memory
**CMOS (Complementary metal-oxide-semiconductor)** is a technology for constructing integrated circuits

The boot sector (first sector from the boot device) is read into memory and executed. This sector contains a program that normally examines the partition table at the end of the boot sector to determine which partition is active.

A secondary boot loader is read in from that partition. This loader reads in the OS from the active partition and starts it. The OS then queries the BIOS to get the configuration information. For each device, it checks to see if it has  the device driver.

Once it has all the device drivers, the OS loads them into the kernel. Then it initializes its tables, creates whatever background processes are needed, and starts up a login program or GUI.

### Mainframe Operating Systems
Mainframes are room-sized computers in data centers. The operating systems for mainframes are heavily oriented toward processing many jobs at once, most of which need prodigious amount of I/O.

Typically kinds of service:
- A **batch** system processes routine jobs without any interactive user present
- **Transaction-processing** systems handle large numbers of small requests
- **Timesharing** systems allow multiple remote users to run jobs on the computes at once, such as querying a big database