# sudoku client-server

Sudoku across machines: application of socket programming to create a client-server model for our Sudoku program. The Sudoku creator runs at one *server* and Sudoku solver runs at another *client*. The solver client connects to the creator server, receives a puzzle, and then solves it.

* [Usage](#usage)
* [Assumptions](#assumptions)
* [Compilation](#compilation)
* [Files](#files)
* [Output](#output)
* [Testing](#testing)
* [Exit Codes](#exit-codes)
* [Testing](#testing)
* [Memory](#myvalgrind-output)

## Usage
### server side
```c
./creatorserver-fork
```
### client side
```c
./solverclient hostname port
```

### important definitions 
* size is the size of the grid [ 3, 4, 6, 9, 16 ]
   * size 4, 6, 9, 16 are standard 2D puzzles
   * size 3 is a cube puzzle

## Compilation

To compile, simply `make` inside client-server-sudoku directory. The common library must exist prior.

## Assumptions

No assumptions beyond those that are clear from a typical client-server model.

## Files

* `Makefile` - compilation procedure
* `creatorserver-fork.c` - the implementation of the *server*
* `solverclient.c` - the implementation of the *client*
* `testing.sh` - integration testing driver
* `testing.out` - testing results from testing.sh
* `solver.h` - headerfile for solver module
* `creator.h` - headerfile for creator module
* `common.h` - headerfile for common.c file that contains functions common across the modules
* `cube.h` - headerfile for cube module

## Output
**server side** outputs the puzzle generated from the client's request to stdin. 

**client side** outputs the puzzle received from the server and its solution to stdin.

## Exit Codes
**server side**
```c
exit(100): incorrect usage
exit(1): error opening socket stream
exit(2): error binding socket name
exit(5): error reading from stdin when trying to load type and size from client
exit(6): error writing on stream socket
exit(10): error scanning type and data from client
exit(0): exiting forked loop once connection terminates
```
**client side**
```c
exit(2): error opening socket
exit(3): error unknown host
exit(4): error connecting to stream socket
exit(5): error reading from server
exit(6): error writing on stream socket
exit(14): error reading in type of grid
exit(15): inavlid type must be 0 or 1
exit(16): error reading in size of grid
exit(17): invalid size for type 0 grid; must be 4, 9, 16 or 25
exit(21): server provided bad character in server
```
Errors are printed to stderr.

## Testing
*Unit testing*.  A small test program to test each module to make sure it does what it's supposed to do.

*Integration testing*.  Assemble the client-server and test it as a whole.

Testing.sh 
* tests with incorrect number of arguments
* tests with invalid type and size input on client side

## myvalgrind output
**server side**
```c
$ myvalgrind ./creatorserver-fork
==2331364== Memcheck, a memory error detector
==2331364== Copyright (C) 2002-2017, and GNU GPL'd, by Julian Seward et al.
==2331364== Using Valgrind-3.16.0 and LibVEX; rerun with -h for copyright info
==2331364== Command: ./creatorserver-fork
==2331364== 
Listening at port 3000
To find your MacOS IP address, ifconfig | grep 'inet '
Connection started

Requested 2D puzzle of size 9

0 8 7 0 4 0 2 0 0 
3 5 0 0 7 1 0 4 0 
0 0 1 0 0 6 5 0 9 
0 0 0 0 3 0 7 0 1 
0 6 3 0 0 0 9 8 0 
0 0 9 0 8 0 0 3 0 
1 0 0 8 0 0 0 0 3 
0 2 0 0 6 4 0 0 7 
8 4 5 3 0 0 1 0 0 

Sending puzzle...
Connection ended

==2331366== 
==2331366== HEAP SUMMARY:
==2331366==     in use at exit: 0 bytes in 0 blocks
==2331366==   total heap usage: 1 allocs, 1 frees, 1,024 bytes allocated
==2331366== 
==2331366== All heap blocks were freed -- no leaks are possible
==2331366== 
==2331366== For lists of detected and suppressed errors, rerun with: -s
==2331366== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)
^C==2331364== 
==2331364== Process terminating with default action of signal 2 (SIGINT)
==2331364==    at 0x4AD8987: accept (in /usr/lib64/libc-2.31.so)
==2331364==    by 0x401384: main (creatorserver-fork.c:56)
==2331364== 
==2331364== HEAP SUMMARY:
==2331364==     in use at exit: 0 bytes in 0 blocks
==2331364==   total heap usage: 1 allocs, 1 frees, 1,024 bytes allocated
==2331364== 
==2331364== All heap blocks were freed -- no leaks are possible
==2331364== 
==2331364== For lists of detected and suppressed errors, rerun with: -s
==2331364== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)
```
**client side**
```c
$ myvalgrind ./solverclient 129.170.213.207 3000
==600778== Memcheck, a memory error detector
==600778== Copyright (C) 2002-2017, and GNU GPL'd, by Julian Seward et al.
==600778== Using Valgrind-3.16.0 and LibVEX; rerun with -h for copyright info
==600778== Command: ./solverclient 129.170.213.207 3000
==600778== 
Connected! Requesting puzzle from server...

Received Puzzle: 

5 3 0 6 0 7 1 0 0 
8 0 7 0 0 0 5 0 0 
0 0 0 0 0 0 0 0 0 
0 0 0 0 0 0 0 0 0 
0 0 0 0 0 0 0 0 0 
0 0 0 0 0 0 0 0 0 
0 0 0 0 0 0 0 0 0 
0 0 0 0 0 0 0 0 0 
0 0 0 0 0 0 0 0 0 

Solved Puzzle:

5 3 2 6 4 7 1 8 9 
8 1 7 2 3 9 5 4 6 
4 6 9 1 5 8 2 3 7 
1 2 3 4 6 5 7 9 8 
6 4 8 7 9 1 3 2 5 
7 9 5 3 8 2 4 6 1 
2 5 4 8 1 6 9 7 3 
3 8 1 9 7 4 6 5 2 
9 7 6 5 2 3 8 1 4 
==600778== 
==600778== HEAP SUMMARY:
==600778==     in use at exit: 0 bytes in 0 blocks
==600778==   total heap usage: 14 allocs, 14 frees, 11,694 bytes allocated
==600778== 
==600778== All heap blocks were freed -- no leaks are possible
==600778== 
==600778== For lists of detected and suppressed errors, rerun with: -s
==600778== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)
```
