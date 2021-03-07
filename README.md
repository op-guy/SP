### System Practicum Assignment 1

##### Course Instructor: 
######  Dr Aditya Nigam

#### Group Members:
`b18084 Saatvik Chugh`

`b18175 Manav Mehta`



# Question 1

### oz
The unix shell

### Requirements and executing
The readline devel-package is required as the header 'readline'.
We are not including the steps in makefile as the evaluator would've installed it most probably.

If there is a need to install, use these commands:
* `sudo apt-get update -y`
* `sudo apt-get install -y libreadline-dev`

Now to compile, just use `make` and use the execuable `oz` to run the shell in prompt.

If the user wants the shell to read commands from external file, use `./a.out <filename>`

For convenience, put the commands in the file `commands` and run `./a.out commands`

### Language and Modules used
C++ 11

Headers:

* fstream - for file r/w
* stdlib.h, unistd.h - for some standard macros and functions
* sys/wait.h - for if need arises to use fork, parent needs to wait for child to finishs
* string.h - for string datatype
* signal.h - for handling some signals
* dirent.h - for directory entry struct needed for the dir command implementation
* errno.h - for standar error codes
* readline/readline.h - for getting input from realtime shell on prompt


# Question 2

### p2
The Students Dining Problem

### Requirements and executing

`make all`
`./a.out`


### Language and Modules used
C++ 11


# Question 3

### p3

To run the sequential program to multiply square matrices:
Compile it using

`make sequential` 

and run the executable `without_thread` ie ./without_thread n where n is the size of the row/column of the matrix


To run the program which uses threads to multiply the square matrices:
Compile it using

`make parallel`

and run the executable `with_thread` ie ./with_thread n where n is the size of the row/column of the matrix


### Language and Modules used
C++ 11
