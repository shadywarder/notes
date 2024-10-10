### What is the UNIX shell?
**Shell** is a text user interface (TUI) for access to an operating system's services. Has many implementations: bash shell, original Unix shell, Bourne shell, ksh, csh. etc.

![](/attachments/Pasted%20image%2020241008213709.png)

The job of the **shell** is to translate the user's command lines into operating system instructions.
For example, consider this command line:

![](/attachments/Pasted%20image%2020241008213838.png)

This means, "Sort lines in the file *namelist* in numerical and reverse order, and put the result in the file *namelist.sorted*."

## Shell - Streams
**Standard streams** are preconnected communication channels of programs. They are:
- **stdin** - standard input that going into program,
- **stdout** - standard out where program writes output,
- **stderr** - to display error messages
It is possible to redirect streams to or from files with `>` and `<`.
It is possible to redirect output of one program to input of another by `|` (pipe symbol).

## Foreground and Background
**Foreground** processes block shell during execution whereas **background** processes do not. Appending `&` will run process in background.
- `gedit &`

Foreground process can be suspend by ctrl+z and run in background with **bg** or foreground with **fg**.
- `jobs` - display list of jobs.

A job can be chosen by its number in the list with %, %+ for the current job and %- for the previous one:
- `fg %1` - run job 1 in foreground

![](/attachments/Pasted%20image%2020241008222311.png)

