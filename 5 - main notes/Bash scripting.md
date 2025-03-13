**2025-02-18 19:31**
**Tags:** [bash](../2%20-%20tags/bash.md)

## Bash scripting
### Bash scripting basics
Use the `echo` command to display a line, `echo` has three important options.

`-n` do not output the trailing newline
`-e` enable interpretation of backslash escapes
`-E` disable interpretation of backslash escapes (default)

```bash
# one line comment

: '
This is multuline commen
Nothing happens in this section
'
```

Double brackets are used to do arithmetic tasks. For example, append the following to `script.sh`

```bash
((sum = 12 + 24))
echo $sum
```

Get user input with the `read` command. This is normally used in combination with `echo` to print a prompt to user.

```bash
echo "What is your favourite fruit?"
read fruit
echo "Hey! I like $foo too."
```

### Bash loops and conditions

```bash
#!/bin/bash

counter=1
while [ $counter -le 10 ]
do 
	echo $counter
	((counter++))
done
echo All done
```

`-le` is the same as `<=`.

```bash
#!/bin/bash

counter=1
until [ $counter -gt 10 ]
do 
	echo $counter
	((counter++))
done
echo All done
```

`-gt` is the same as `>`.

```bash
#!/bin/bash

names='Liliya Peter Emili'
for name in $names
do 
	echo $name
done
echo All done
```

```bash
#!/bin/bash

counter=1
while [ $counter -le 10 ]
do 
	if [ $counter -eq 5 ]
	then
		echo Script encountered the value $counter
		break
	fi
	echo $counter
	((counter++))
done
echo All done
```

`-eq` is the same as `==`.

```bash
#!/bin/bash

counter=0
while [ $counter -lt 10 ]
do 
	((counter++))
	if [ $counter -eq 6 ]
	then
		echo Number 6 encountered, skipping to the next iteration
		continue
	fi
	echo $counter
done
echo All done
```

`-lt` is the same as `<`.

### If statements

```bash
#!/bin/bash

echo -n "Enter the number: "
read number
if [ $number -gt 100]
then
	echo That\'s a large number.
elif [ $number -gt 50]
then
	echo Not so much.
else
	echo The number is way too small.
fi
```

### Bash functions
Create a simple function

```bash
fun () { echo "This is a function"; echo; }
```

```bash
#!/bin/bash
 JUST_A_SECOND=3
funky ()
{ # This is about as simple as functions get.
     echo "This is a funky function."
    echo "Now exiting funky function."
} # Function declaration must precede call
 fun ()
{ # A somewhat more complex function. 
    i=0
    REPEATS=30
    echo
    echo "And now the fun really begins."
    echo 
    sleep $JUST_A_SECOND 
    while [ $i -lt $REPEATS ] #use as (<,>,=) or (-lt, -gt, -eq)
        do
        echo   "----------FUNCTIONS---------->"
        echo   "<------------ARE-------------"
        echo   "<------------FUN------------>"
        echo
        let "i+=1"
        done
}

add_fun()
{
# A function just to add numbers
echo $((2+2))
}
#Now, call the functions
funky
fun
echo The return value of add_fun is: $(add_fun)
echo exit $? #check your exit status of the last function/command: if 0-success, otherwise is not
```

### File and directory test operators

There are several options in bash to check the type of file you are interacting with. In many cases the options are also used to check for the existence of a specified file or directory. The example below shows the options that can be used.

```bash
#!/bin/bash

if [[ $# -le 0 ]]
then
  echo "You did not pass any files as arguments to the script."
  echo "Usage:" "$0" "my-file-1 my-file-2"
  exit
fi
 for arg in "$@"
do
  # Does it actually exist?
  if [[ ! -e "$arg" ]]
  then
      echo "* Skipping ${arg}"
      continue
  fi
   # Is it a regular file?
  if [ -f "$arg" ]
  then
      echo "* $arg is a regular file!"
  else
      echo "* $arg is not a regular file!"
  fi
  [ -b "$arg" ] && echo "* $arg is a block device."
  [ -d "$arg" ] && echo "* $arg is a directory."
  [ ! -d "$arg" ] && echo "* $arg is not a directory."
  [ -x "$arg" ] && echo "* $arg is executable."
  [ ! -x "$arg" ] && echo "* $arg is not executable."
  [[ -h "$arg" ]] && echo "* $arg is a symbolic link."
  [ ! -h "$arg" ] && echo "* $arg is not a symbolic link."
  [[ -s "$arg" ]] && echo "* $arg has nonzero size."
  [ ! -s "$arg" ] && echo "* $arg has zero size."

  [[ -r "$arg" && -d "$arg" ]] && echo "* $arg is a readable directory."
  [[ -r "$arg" && -f "$arg" ]] && echo "* $arg is a readable regular file."
done
```

### Directory and file manipulation

You can create a new directory in bash with the `mkdir` command.

```bash
#!/bin/bash
echo "Enter directory name"
read newdir
mkdir newdir
```

You can check for the existence of a directory before proceeding to create it.

```bash
echo "Enter directory name"
read newdir
if [ -d "$newdir" ]
then 
	echo Directory exists
else 
	mkdir newdir
	echo Directory created
fi
```

Bash script to read every line of a specified file. The file name is passed as a command line argument.

```bash
#!/bin/bash

file=$1

if [[ "$file" = "" || (! -f "$file") ]]
then
	echo Using standard input!
	file="/dev/stdin"
fi

while read -r line
do
	echo "$line"
done
```

The Internal Field Separator (IFS) is used to recognize word boundaries. The default value for IFS consists of whitespace characters. Whitespace characters are space, tab and newline.

```bash
#!/bin/bash

mystring="foo:bar baz rab"
for word in $mystring do
	echo "Word: $word"
done
```

We can modify for the IFS.

```bash
#!/bin/bash

IFS=:
mystring="foo:bar baz rab"
for word in $mystring do
	echo "Word: $word"
done
```

Let's do this on a larger scale. Read `/etc/passwd` word by word while using `:` as the IFS.

```bash
#!/bin/bash
if [[ $# == 0 ]]
then
	echo "you did not pass any files as arguments to the script."
	echo "usage:" "$0" "my-file"
	exit
fi

IFS=:
file=$1

if [ ! -f "$file" ] 
then
	echo "file does not exist"
fi

for word in $(cat "$file") 
do
	echo $word
done
```

### Jump directories

Sometimes it is difficult to navigate directories with the possibly infinite number of parent directories we need to provide. For example `cd ../../../../../`. Let's create a script that will help us jump to a specified directory without executing `cd ../`.


## References