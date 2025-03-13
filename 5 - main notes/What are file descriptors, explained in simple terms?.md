**2025-02-24 11:31**
**Tags:** [os](../2%20-%20tags/os.md)

## What are file descriptors, explained in simple terms?

This notes consist of answers from corresponding StackOverflow discussion.

### Answer I
In simple words, when you open a file, the operating system creates an entry to represent that file and store the information about the opened file. So if there are 100 files opened in your OS then there will be 100 entries in OS (somewhere in kernel). These entries are represented by integers like (...100, 101, 102...). This entry number is the file descriptor. So it is just an integer number that uniquely represents an opened file for the process. If you process opens 10 files then your process table will have 10 enemies for file descriptors.

Similarly, when you open a network socket, it is also represented by an integer and it is called Socket Descriptor.

### Answer II
A file descriptor is an opaque handle that is used in the interface between user and kernel space to identify file/socket resources. Therefore, when you use `open()` or `socket()` (system calls to interface to the kernel), you are given a file descriptor, which is an integer (it is actually an index into the processes u structure - but that is not important). Therefore, if you want to interface directly with the kernel, using system calls to `read()`, `write()`, `close()` etc. the handle you use is a file descriptor.

There is a layer of abstraction overlaid on the system calls, which is the `stdio` interface. This provides more functionality/features that the basic system calls do. For this interface, the opaque handle you get is a `FILE*`, which is returned by the `fopen()` call. There are many many functions that use the `stdio` interface `fprintf()`, `fscanf()`, `fclose()`, which are there to make your life easier. In C, `stdin`, `stdout`, and `stderr` are `FILE*`, which in UNIX respectively map to file descriptors `0`, `1` and `2`.

### Answer III
To the kernel, all open files are referred to by File Descriptors. A file descriptor is a non-negative number.

**When we open an existing file or create a new file, the kernel returns a file descriptor to the process**. The kernel maintains a table of all open file descriptors, which are in use. The allotment of file descriptors is generally sequential and they are allotted to the file as the next free file descriptor from the pool of free file descriptors. When we closes the file, the file descriptor gets freed and is available for further allotment.

![](../attachments/Pasted%20image%2020250224114415.png)

When we want to read or write a file, we identify the file with the file descriptor that was returned by `open()` or `create()` function call, and use it as an argument to either `read()` or `write()`. It is by convention that, UNIX System shells associates the file descriptor 0 with `stdin` of a process, file descriptor 1 with `stdout`, and file descriptor 2 with `stderr`. File descriptor ranges from 0 to `OPEN_MAX`. File descriptor max value can be obtained with `ulimit -n`. 

### Answer IV
According to Wikipedia we know for sure: a file descriptor is a non-negative integer. The most important thing I think is missing, would be to say:

**File descriptors are bound to a process ID.**

We know most famous file descriptors are 0, 1 and 2. 0 corresponds to `stdin`, 1 to `stdout`, and 2 to `stderr`.

> Say, take shell processes as an example and how does it apply for it?

Check out this code

```bash
sleep 1000 &
[12] 14726
```

We created a process with the id 14726 (PID). Using the `lsof -p 14726` we can get the things like this:

```bash
COMMAND   PID USER   FD   TYPE DEVICE SIZE/OFF    NODE NAME
sleep   14726 root  cwd    DIR    8,1     4096 1201140 /home/x
sleep   14726 root  rtd    DIR    8,1     4096       2 /
sleep   14726 root  txt    REG    8,1    35000  786587 /bin/sleep
sleep   14726 root  mem    REG    8,1 11864720 1186503 /usr/lib/locale/locale-archive
sleep   14726 root  mem    REG    8,1  2030544  137184 /lib/x86_64-linux-gnu/libc-2.27.so
sleep   14726 root  mem    REG    8,1   170960  137156 /lib/x86_64-linux-gnu/ld-2.27.so
sleep   14726 root    0u   CHR  136,6      0t0       9 /dev/pts/6
sleep   14726 root    1u   CHR  136,6      0t0       9 /dev/pts/6
sleep   14726 root    2u   CHR  136,6      0t0       9 /dev/pts/6
```

The 4-th column FD and the very next column TYPE correspond to the File Descriptor and the File Descriptor type.

Some of the values for the FD can be:

```
cwd - Current Working Directory
txt - Text file
mem - Memory mapped file
mmap - Memory mapped device
```

But the real file descriptor is under:

```
NUMBER - Represent the actual file descriptor.
```

The character after the number i.e. `1u`, represents the mode in which file is opened. `r` for read, `w` for write, `u` for read and write.

TYPE specifies the type of the file. Some of the values of TYPEs are:

```
REG - Regular File
DIR - Directory
FIFO - First In First Out
```

But all file descriptors are CHR - Character special file (or character device file).

Now, we can identify the File Descriptors for `stdin`, `stdout` and `stderr` easy with `lsof -p PID`, or we seen the same if we `ls /proc/PID/fd`.

Note also that file descriptor table that kernel track of is not the same as files table or inodes table. These are separate, as some other answers explained.

![](../attachments/Pasted%20image%2020250224120123.png)

You may ask yourself where are these file descriptors physically and what si stored in `/dev/pts/6` for instance.

```bash
sleep   14726 root    0u   CHR  136,6      0t0       9 /dev/pts/6
sleep   14726 root    1u   CHR  136,6      0t0       9 /dev/pts/6
sleep   14726 root    2u   CHR  136,6      0t0       9 /dev/pts/6
```

Well, `/dev/pts/6` lives purely in memory. These are not regular files, but so called  **character device files**. You can check this with : `ls -l /dev/pts/6` and they will start with `c`.

Just to recall most Linux like OS define seven types of files:
- Regular files
- Directories
- Character device files
- Block device files
- Local domain names
- Named pipes (FIFOs)
- Symbolic links

## References
[What are file descriptors, explained in simple terms?](https://stackoverflow.com/questions/5256599/what-are-file-descriptors-explained-in-simple-terms)