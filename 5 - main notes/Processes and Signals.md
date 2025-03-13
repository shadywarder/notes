**2025-02-24 14:58**
**Tags:** [os](../2%20-%20tags/os.md)

## Processes and Signals
### Process id and jobs
The fundamental way of controlling processes in Linux is by sending signals to them. There are multiple signals that you can send to a process. To view all the signals, run:

```bash
kill -l
```

To kill process with a `SIGTERM` (-15):

```bash
kill -15 [id]
```

If that failed, you can use a `SIGKILL` (-9):

```bash
kill -9 [id]
```

To list all process running on the system, issue the following command:

```bash
ps -ef
```

To find the process ID of a specific named `bash`:

```bash
ps -ef | grep bash
```

Another useful command is the pstree command which shows a tree structure of the cascading process IDs (-p).

When you press the `CTRL+C` or Break key at your terminal during execution of a shell program, normally that program is immediately terminated, and your command prompt returns. This may not always be desirable. For instance, you may end up leaving a bunch of temporary files that won't get cleaned up.

Trapping these signals is quite easy, and `trap` command has the following syntax:

```bash
trap "commands" signals
```

Here command can be any valid Unix command, or even a user-defined function, and signal can be a list of any number signals you want to trap.
There are two common uses for trap in shell scripts:
- Clean up temporary files
- Ignore signals

Let's create a script with a trap `SIGINT`. 

You can also use trap to ensure the user cannot interrupt the script execution. This feature is important when executing sensitive commands whose interruption may permanently damage the system. The syntax for disabling a signal is:

```bash
trap "command" [signal]
```

Double quotation marks that no command will be executed when the signal is received. For example, to trap the `SIGINT` and `SIGABRT` signals, type:

```bash
trap "" SIGINT SIGABRT
```

### The proc file system
The `/proc/` directory - also called the proc file system - contains a hierarchy of special files which represent the current state of the kernel - allowing applications add users to peer into the kernel's view of the system.

Within the `/proc/` directory, one can find a wealth of information detailing the system hardware and any processes currently running. In addition, some of the files withing the `/proc/` directory tree can be manipulated by users and applications configuration changes to the kernel.

You can view the `/proc/` virtual files with the command line file readers. For example, view `/proc/cpuinfo`

```bash
cat /proc/cpuinfo
```

When viewing different virtual files in the `/proc/` file system, some of the information are easily understandable while some are not human-readable. This is in part why utilities exist to pull data from virtual files and display it in a useful way. Examples of these utilities include `lspci`, `apm`, `free` and `top`.

Most virtual files within the `/proc/` directory are read-only. However, some can be used to adjust settings in the kernel. This is especially true for files in the `/proc/sys/` subdirectory. 

To change the value of a virtual file, use the `echo` command and redirect (>) the new value to the file. For example, to change the hostname on the fly, run:

```bash
echo SNALabPC > /proc/sys/kernel/hostname
```

Other files act as binary or boolean switches. Typing `cat /proc/sys/net/ipv4/ip_forward` returns either a 0 or a 1. A `0` indicates that kernel is not forwarding network packets. Using the `echo` command to change the value of the `ip_forward` file to `1` immediately turns packet forwarding on.

On multi-user systems, it is often useful to secure the process directories stored in `/proc/` so that they can viewed only by the `root` user. You can restrict the access to these directories with the use of the `hidepid` option.

To change the file system parameters, you can use the `mount` command with the `-o` remount option.

```bash
sudo mount -o remount,hidepid=value /proc
```

Here, value passed to `hidepid` is one of:
- `0` (default) - every user can read all world-readable files stored in a process directory
- `1` - users can access only their own process directories. This protects the sensitive files like `cmdline`, `sched`, or `status` by non-root users. This setting does not affect the actual file permissions.
- `2` - process files are invisible to non-root users. The existance of a process can be learned by other means, but its effective UID and GID are hidden. Hiding these IDs complicates an intruder's task of gathering information about running processes.

To make process files accessible only to the root user, type:

```bash
sudo mount -o remount,hidepid=1 /proc
```

With `hidepid=1`, a non-root user cannot access the contents of process directories. An attempt to do so fails with the following message:

```bash
ls /proc/1/
​​ls: /proc/1/: Operation not permitted
```

With `hidepid=2` enabled, process directories are made invisible to non-root users:

```bash
ls /proc/1/       
​​ls: /proc/1/: No such file or directory
```

Also, you can specify a user group that will have access to process even when `hidepid` is set to 1 or 2. To do this, use the `gid` option.

```bash
sudo mount -o remount,hidepid=value,gid=gid /proc
```

> You can find system groups and their respective group IDs in `/etc/group`. Replace `gid` with the specific group id. For members of selected group, the process files will act as if `hidepid` was set to `0`. However, users which are not supposed to monitor the tasks in the whole system should not be added to the group.

### `top`

Open a command shell and run the `top` command.
This opens up a tool that shows the top processes running on your system. This tool can be used to kill processes, renice processes, sort and various other process management. Press the `h` command to get a list of help.

By default, `top` sorts the process list using the `%CPU` column. To sort processes using a different column, press one of the following keys.

- `M` - sort by by the `%MEM` column.
- `N` - sort by `PID` column.
- `T` - sort by the `TIME+` column.
- `P` - sort by the `%CPU` column.

To show the process command line instead of just the process name, press `c`.

The filter feature allows using a filter expression to limit which processes to see in the list. We can activate it by pressing `o`. The program will ask you to enter filter expression. For example, to filter processes using more that 1% CPU.

```bash
%CPU>1.0
```

To clear the filter just press `=`.

We can filter processes by user as well (`-u` option). 

```bash
top -u root
```

The first five line of the output demonstrates some useful metrics.

![](../attachments/Pasted%20image%2020250224160151.png)

- `https://whimsical.com/operating-system-cheatsheet-by-love-babbar-S9tuWBCSQfzoBRF5EDNinQtop` - displays uptime information.
- `Tasks` - information about processes status.
- `%CPU(s)` - different processor values.
- `MiB Mem` - utilization of the physical memory.
- `MiB Swap` - utilization of the virtual memory.


## References