### System Practicum Assignment 2

##### Course Instructor: 
######  Dr Aditya Nigam

#### Group Members:
* b18084 Saatvik Chugh

* b18175 Manav Mehta



# Question 1

### Build custom linux kernel



### Requirements and executing

Modules are present in the q1 folder along with the make file
[module] + [1,2,3]

To install the modules 

* `make all`
* `sudo insmod module-[number].ko`
   number can be [1,2,3]
* `sudo rmmod module-[number]`



### Language and Modules used
C

# Question 2

### Round-Robin Scheduling


### Requirements and executing

* `make roundrobin`
* `./a.out [args_as_specified_in_questions]`


### Language and Modules used
C++ 11


# Question 3


### Merge-sort using threads

To run the standard mergesort which doesn't use threads

* `make old_mergesort`
* `./a.out [size of array]`



To run mergesort using threads


* `make new_mergesort`
* `./a.out [number of threads] [size of array]` 




### Language and Modules used
C++ 11
