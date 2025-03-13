**Author: Sergey Razmakhov**
**Group: CBS-2**
**Lab 1: Introduction to Linux and OS main components**

## Exercise 1: Finding you way around Linux
1. Check the distribution of Linux you have just installed

	![](../attachments/Pasted%20image%2020250121233549.png)

> [!NOTE] 
> `-a` flag responsible for printing all the possible information

2. Check the username of the user who is currently logged on to the local system

	![](../attachments/Pasted%20image%2020250121233821.png)

3. View all currently logged in users

	![](../attachments/Pasted%20image%2020250121233847.png)

4. View the content of your current working directory

	![](../attachments/Pasted%20image%2020250121233931.png)

5. List the content of your current directory

	![](../attachments/Pasted%20image%2020250121234056.png)

(actually, there are much more files/directories/etc.)

> [!NOTE]
> `-a` do not ignore entries starting with .
> `-l` use a long listing format

6. Navigate to another directory

	![](../attachments/Pasted%20image%2020250121234500.png)

7. View all shells installed on the machine

	![](../attachments/Pasted%20image%2020250121234559.png)

8. View the shell you are currently using

	![](../attachments/Pasted%20image%2020250121234700.png)

9. Learn to read manuals with the `man` command. Read the manual of the bash shell.

	![](../attachments/Pasted%20image%2020250121234943.png)

## Exercise 2: SWAP
#### 1. Working with a Swap memory
- First, check if the system has any swap configured.

	![](../attachments/Pasted%20image%2020250121235158.png)

- Let's remove a swap file.
	1. Deactivate the swap file

	![](../attachments/Pasted%20image%2020250121235415.png)
	
	2.  Open the file `/etc/fstab` and delete the swap information line from it or comment it out
	
	![](../attachments/Pasted%20image%2020250122000331.png)
	
	3. Delete the file from the systems
	
	![](../attachments/Pasted%20image%2020250122000508.png)

#### 2. Create the SWAP file
- To create the swap file, run the following command
	![](../attachments/Pasted%20image%2020250122001849.png)
- Now check if the file was created
	![](../attachments/Pasted%20image%2020250122001934.png)

#### 3. Configure the SWAP file
- Make the swap file only accessible for the root (if it is not)
- Mark the file as a swap file

	![](../attachments/Pasted%20image%2020250122002346.png)

- Finally, we will tell the system to start using our new swap files
- To verify that the swap is now available type

	![](../attachments/Pasted%20image%2020250122002531.png)

- We can also run the following to see our new file alongside physical memory

	![](../attachments/Pasted%20image%2020250122002725.png)

#### 4. Make it Persistent
- This swap will only last until next reboot. In order to make it permanent, we will add it to the `etc/fstab` file

	![](../attachments/Pasted%20image%2020250122002950.png)

## Exercise 3: GPT partition
- Check the currently connected store devices

	![](../attachments/Pasted%20image%2020250122134139.png)

#### MBR Dump and Analysis
- MBR starts at logical block address (LBA) of the GPT layout. Use `dd` to dump the first 512 bytes from LBA 0.

	![](../attachments/Pasted%20image%2020250122142953.png)

#### GPT Header Dump and Analysis
- GPT header starts from LBA 1. Use `dd` to dump the 512 bytes in sector 1:
	![](../attachments/Pasted%20image%2020250122143328.png)

- View the GPT dump with hexedit
	![](../attachments/Pasted%20image%2020250122143356.png)

## Exercise 3: UEFI Booting
- To view the boot entry on a UEFI enabled system, run `efitbootmgr -v` (`-v` prints additional information).

	![](../attachments/Pasted%20image%2020250122143720.png)

- The firmware validates and loads the shim binary.

	![](../attachments/Pasted%20image%2020250122143920.png)

- Shim then loads GRUB bootloader

	 ![](../attachments/Pasted%20image%2020250122144047.png)

## Questions to answer
### 1. Introduction to Linux
1. What is your machine hostname? How did you check it?
	A hostname is a name given to a computer and attached to the network. It allows to uniquely it over a network. We can obtain by running `hostname` command without any flags.
	
	![](../attachments/Pasted%20image%2020250122144541.png)

2. What is the difference between `/bin/bash` and `/bin/sh`?
	 `/bin/sh` is a symbolic link to the currently configured *system shell*. 
	 `/bin/bash` is the most common shell used as default shell for users of Linux systems.

3. Explain all the details of the output from the command `uname -a`.
	
	![](../attachments/Pasted%20image%2020250122145744.png)
	
	`Linux` - kernel name
	`machine` - hostname
	`6.8.0-51-generic` - kernel release
	`#52-Ubuntu SMP PREEMPT_DYNAMIC Thu Dec  5 13:09:44 UTC 2024` - kernel version
	`x86_64` - machine hardware name
	`x86_64` - processor type
	`x86_64` - hardware platform
	`GNU/Linux` - operating system

4. What command typically shows you the manual for POSIX compliant tools on the Linux operating system?
	The command is `man <command>`.

### 2. GPT
1. What is fdisk utility used for?
	It is a dialog-driven program for creation and manipulation of partition tables. It understands GPT, MBR, Sun, SGI and BSD partition tables.

2. Show the bootable device(s) on your machine, and identify which partition(s) are bootable.
	Bootable devices on my machine:
	
	![](../attachments/Pasted%20image%2020250122151604.png)
	 Bootable partitions:
	 ![](../attachments/Pasted%20image%2020250122153048.png)

3. What is logical block address?
	LBA is common scheme used to specifying the location of blocks of data stored on computer storage devices, generally secondary system such as hard disk drives. If follows simple linear addressing scheme; blocks are located by an integer index, with the first block being LBA 0, the second LBA 1, and so on.

4. Why did the specify the `count`, the `bs`, and the `skip` options when using dd?
	 `count=N` - copy only N input blocks
	`bs=BYTES` - read and write up to BYTES bytes at a time
	`skip=N` - skip N ibs-sized (`bs` parameter overrides `ibs`) input blocks
	In order to achieve the desired partition table we need to manipulate these parameters.

5. Why does a GPT formatted disk have the MBR?
	 Legacy tools will simply "see" a partition in legacy partition table (MBD) occupying the entire disk and as such the partition (hopefully) "protects" the drive from new and overlapping partitions being created.

6. Name two differences between primary and logical partitions in an MBR partitioning scheme
	1. You can have only 4 primary partitions (3 if you decide to have an extended partition), whereas you can have an arbitrary number of logical partitions.
	2. Legacy MBR bootloader can only boot from a primary partition.

### UEFI Booting
1. Why is Shim used to load the GRUB bootloader?
	Shim provides a sort of parallel Secure Boot verification feature. Shim registers itself with the EFI in a way that enables follow-on programs to call Shim to verify that binaries are signed. It ensures the integrity and authenticity of the bootloader (GRUB) and other binaries in a Secure Boot environment.

2. Can you located your grub configuration file? Show the path.
	GRUB is configured using `grub.cfg`.
	![](../attachments/Pasted%20image%2020250122155222.png)

3. According to the boot order, what is third boot device on your computer? How did you check this?
	
	![](../attachments/Pasted%20image%2020250122155737.png)
	I don't know why, but there is only two devices on my machine... So, the third one is undefined :(