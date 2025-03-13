**Author: Sergey Razmakhov**
**Group: CBS-02**
**Lab 2: The filesystem, command line, and file manipulation**

### Part 1: Filesystem
- View filesystem of block devices
	
	![](../attachments/Pasted%20image%2020250201160824.png)
- View all `/dev` filesystems
	
	![](../attachments/Pasted%20image%2020250201161507.png)
	A lot more actually...
	
	![](../attachments/Pasted%20image%2020250201161300.png)
- View memory info from the `/proc` filesystem
	
	![](../attachments/Pasted%20image%2020250201161545.png)
	![](../attachments/Pasted%20image%2020250201161615.png)

### Part 2: echo, pipes, redirects and quotes
- On your machine login with password. Open terminal. Check your location.
	
	![](../attachments/Pasted%20image%2020250201161738.png)
- Create a directory, change directory, create a file, check directory.
	
	![](../attachments/Pasted%20image%2020250201162004.png)
- Copy the files from the `/home/$USER/mydocs/textproc` directory into your home directory.
- Type the following in a shell and use append to the file using `>>`.
	
	![](../attachments/Pasted%20image%2020250201162705.png)
- Notice how the following copies a file. Same as using `cp simple_echo new_echo`
	
	![](../attachments/Pasted%20image%2020250201162829.png)
- If we cat a file that doesn't exist
	
	![](../attachments/Pasted%20image%2020250201162920.png)
- We  get an error message. This is stderr. Let's handle that using the `2>`
	
	![](../attachments/Pasted%20image%2020250201163322.png)
- We can send errors to the same place as stdout by using the `2>&1`
	
	![](../attachments/Pasted%20image%2020250201163347.png)
- Now let's sett what the '<<' does. Type in the following
	
	![](../attachments/Pasted%20image%2020250201164100.png)
	`<<` terminates input when foobar meets.
- Create a file `fragemented.txt` with 5 lines of any text
	
	![](../attachments/Pasted%20image%2020250201164841.png)
- Notice how it only adds line number to lines with entries. Also re-run the command without the `<`. It should work.
	
	![](../attachments/Pasted%20image%2020250201165122.png)
- Now let us read stdin from the keyboard until a specific marker. We will make the specific marker the word "end"
	
	![](../attachments/Pasted%20image%2020250201165322.png)
- If you wanted to store this information
	
	![](../attachments/Pasted%20image%2020250201165410.png)
- If you wanted to add line numbers this output regardless of blank lines
	
	![](../attachments/Pasted%20image%2020250201165544.png)
- You can turn on the backslash escaped character like tab, backspace, form feed, newline, etc, by specifying `-e` with echo
	
	![](../attachments/Pasted%20image%2020250201165712.png)
- Use combination of pipe `|` and `grep` to filter data in output
	
	![](../attachments/Pasted%20image%2020250201165811.png)
- Write a compound command to write input to a file, and then sort the content of the file
	
	![](../attachments/Pasted%20image%2020250201165943.png)

### Part 3: Heads and tails, cat and tac
- Create a file and following data inside. Read the last 5 numbers and look at the first 3 lines
	
	![](../attachments/Pasted%20image%2020250201170230.png)
- Reverse the contents of the file using `tac`
	
	![](../attachments/Pasted%20image%2020250201170312.png)

### Part 4: Cutting comments
- To cut out the specific information from a file you can use the `cut` command. You can specify delimiters and fields within the `cut` command. Following will put out field 1, 4 and 5 in the passwd file
	
	![](../attachments/Pasted%20image%2020250201170624.png)
- To output the mounted filesystems. Space as the field delimiter
	
	![](../attachments/Pasted%20image%2020250201170757.png)
- Extracting fields 1, 3, 11 and 12 frome a uname kernel output
	
	![](../attachments/Pasted%20image%2020250201170918.png)

### Part 5: Unique lines extraction, sorting and filtering
- Create the following file called unique with following content
	
	![](../attachments/Pasted%20image%2020250201171036.png)
- Using the `uniq` command we can count and extract unique lines
	
	![](../attachments/Pasted%20image%2020250201171159.png)
- We can sort files using the `sort` command.
	
	![](../attachments/Pasted%20image%2020250201171315.png)
- If you wish to sort with a different delimiter then you must specify a delimiter with the `-t` option
	
	![](../attachments/Pasted%20image%2020250201172045.png)

### Part 6: Bash helpers
- The bash history helps you view commands you have run in the past, and you can repeat them if you want. View your bash command history
	
	![](../attachments/Pasted%20image%2020250201172216.png)
- Run any command in your history by typing `!N`.
	
	![](../attachments/Pasted%20image%2020250201172312.png)
- Ping localhost on your machine
	
	![](../attachments/Pasted%20image%2020250201172407.png)
- Run the last command in your bash history
	
	![](../attachments/Pasted%20image%2020250201172441.png)

### Questions to answers:
--- 
#### 1. Filesystem
1. How many inodes are in use in your system?
	
	![](../attachments/Pasted%20image%2020250201223842.png)
2. What is the filesystem type of the EFI partition?
	The EFI system partition (ESP) is a FAT formatted partition containing the primary EFI boot loader(s) for installed operating system.
3. What device is mounted at your root `/` directory?
	
	![](../attachments/Pasted%20image%2020250201224153.png)
4. What is your partition UUID?
	
	![](../attachments/Pasted%20image%2020250201224409.png)
5. What is the function of `/dev/zero`?
	`/dev/zero` is a special file in Unix-like operating system that provides as many null characters (ASCII NUL, 0x00) as are read from it. One of the typical uses is to provide a character stream for initializing data storage.

#### 2. Command line and file manipulation
1. Explain the role of the pipe `|` in this command `cat /etc/apt/sources.list | less`.
	Pipe `|` redirects the stdout from the `cat /etc/apt/sources.list` to stdin for `less`.
2. What does section 5 in man mean? And how can you find it?
	This is where formats of lots of different files are find, including both system and user files, `a.out` format, and lots of others. We can find it in `/usr/share/man/man5`/
3. What is the full file path of `ls` on your machine? How did you find it?
	
	![](../attachments/Pasted%20image%2020250201230517.png)
4. Show two ways of renaming a file `test_file.tot` to `test_file.txt`.
	1. `mv test_file.tot test_file.txt`
	2. `cp test_file.tot test_file.txt && rm test_file.tot`
5. Create a compound command that does the following to a given string:
	- sort a given string
	- find only the unique lines without duplication
	- save the sorted unique lines to a file
	- append the username of the currently logged in user to the end of the file.
	
	`echo -e "The location of hundreds of crab pots\nLittle Red Riding Hood\nThe location of hundreds of crab pots\nThe location of hundreds of crab pots\nThe sound of thunder\nEight hours in a row\nAll aboard\nEight hours in a row" | sort | uniq -u > uniq.txt && echo "$USER" >> uniq.txt`
6. What can you do to discard the output from the command `ping 127.0.0.1`? You should also discard standard error. Show how you achieve this.
	From the previous lab exercise we know that we can discard stderr by using `&>`. There is also `-q` flag which stands for quiet output.
	
	`ping -q 127.0.0.1 &> /dev/null`
7. Show how you can sort input, append line numbers, and save the sorted result to a file. Add line numbers to empty lines too.
	
	![](../attachments/Pasted%20image%2020250201233616.png)
8. Create the directory `home/$USER/testdir`. Write out as much as possible ways to go from `/usr/share` folder to `/home/$USER/testdir`
	`cd ~/testdir`
	`cd ../../home/$USER/testdir`
	`cd /home/$USER/testdir`
	`cd ... && cd /home/$USER/testdir`
	`cd && cd testdir`
9. Write a pipe that will result with a unique list of commands/shell from `/etc/passwd` file (last column of it)
	`cut -d: -f7 /etc/passwd | uniq -u > uniqcmd`
10. Find all man pages that contain word `malloc`. The result should be just a list of files. 
	`zgrep -l "malloc" /usr/share/man/*/*.gz 2> /dev/null`
11. Write a one-liner that will result with a message "Was found!" if grep found an occurence of a patter, and "Wasn't found..." if grep does not find the pattern. Add the desired pattern as the last line on any file.
	![](../attachments/Pasted%20image%2020250202005611.png)
