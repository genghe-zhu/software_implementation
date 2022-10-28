# project-50-stars
Our sudoku creator runs through the shell script ./sudoku.sh. Here we check if the generated puzzle is solvable.
# sudoku 
* [Usage](#usage)
* [Assumptions](#assumptions)
* [Compilation](#compilation)
* [Files](#files)
* [Output](#output)
* [Testing](#testing)
* [Exit Codes](#exit-codes)
* [Testing](#testing)
* [Memory](#myvalgrind-output)
* [GUI](#gui)

## Usage
### creator 
```c
./sudoku.sh create size
```
Note for creating a puzzle we use a sudoku.sh instead of sudoku.c
### solver 
```c
./sudoku solve size
```
When reading from stdin, you must either enter a row at a time pressing return after the last col or you must pipe in a puzzle. 

For example, `cat goodpuzzlesize9 | ./sudoku solve 9`

### important definitions 
* size is the size of the grid [ 3, 4, 6, 9, 16 ]
   * size 4, 9, 16 are standard 2D puzzles
   * size 6 is a 2D puzzle but with rectangle boxes 2x3 boxes instead of square boxes
   * size 3 is a cube puzzle

## Compilation

To compile, simply `make` inside project-50-stars directory. The common library must exist prior.

## Assumptions

No assumptions beyond those that are clear from a typical client-server model.

## Files

* `Makefile` - compilation procedure
* `sudoku.c` - the implementation of the sudoku game
* `testing.sh` - integration testing driver
* `testing.out` - testing results from testing.sh
* `solver.h` - headerfile for solver module
* `creator.h` - headerfile for creator module
* `common.h` - headerfile for common.c file that contains functions common across the modules
* `file.h` - headerfile for functions needed to read from stdin
* `cube.h` - headerfile for cube module
* `sudoku.sh` - script for verifying the generated sudoku is solvable
* `regress.sh` - script for regression testing

## Output
### ./sudoku.sh create size
outputs the puzzle generated from the creator module to stdin. 
-  the generated puzzle is a solvable puzzle 

### ./sudoku solve size
outputs the puzzle and the puzzle's solution to stdin.

## Exit Codes
```c
exit(1): invalid number of arguments for sudoku.c
exit(2): invalid command; must be create or solve
exit(3): bad character in stdin when loading in puzzle
exit(4): bad character in stdin when loading in cube
exit(5): invalid input size; must be either 3, 4, 6, 9, or 16
exit(10): could not open logfile.txt needed for GUI
exit(35): invalid number of arguments for sudoku.sh
exit(36): invalid command; must be create or solve for sudoku.sh 
exit(37): invalid size; must be 3, 4, 6, 9, 16
exit(38): invalid 4th supplemental argument; must be "server" 
```
Errors are printed to stderr.

## Testing
*Unit testing*.  A small test program to test each module to make sure it does what it's supposed to do.

*Integration testing*.  Assemble the sudoku and test it as a whole.

*Testing.sh*
* tests with incorrect number of arguments
* tests with invalid arguments
* tests sudoku.sh with sizes 4, 6, 9
* tests ./sudoku.c solve with sizes 4, 6, 9
* tests bad input into ./sudoku.c solve
* tests puzzle boundaries in ./sudoku.c solve

*Regression testing*
- create a 9x9, 4x4, 6x6, and cube puzzle in the regress directory
- run the shell script piping in the puzzles to ./sudoku solve
- comparing output to verify consistency

We ran `$ regress/regress.sh regress/base ./testing.sh` three times, providing the same three puzzles a 9x9, 4x4, and 6x6 to the testing script.
```c
$ regress/regress.sh regress/base ./testing.sh
saved test results in regress/base

$ regress/regress.sh regress/base ./testing.sh
saved test results in 20200827.165235
comparing 20200827.165235 with regress/base...
no differences comparing 20200827.165235 with regress/base

$ regress/regress.sh regress/base ./testing.sh
saved test results in 20200827.165308
comparing 20200827.165308 with regress/base...
no differences comparing 20200827.165308 with regress/base
```
The output was consistent across multiple runs. 

## myvalgrind output
### ./sudoku.sh create 
```c
$ myvalgrind ./sudoku create 9
==2287470== Memcheck, a memory error detector
==2287470== Copyright (C) 2002-2017, and GNU GPL'd, by Julian Seward et al.
==2287470== Using Valgrind-3.16.0 and LibVEX; rerun with -h for copyright info
==2287470== Command: ./sudoku create 9
==2287470== 
9 1 0 0 0 0 0 0 0 
8 0 0 4 6 0 0 0 0 
0 0 5 0 0 0 0 7 0 
0 0 0 0 0 0 4 0 0 
0 0 0 0 0 0 0 5 0 
1 0 0 2 0 0 9 0 0 
0 0 0 3 0 0 8 2 0 
0 0 0 9 0 0 0 0 0 
0 0 0 0 0 0 3 0 0 
==2287470== 
==2287470== HEAP SUMMARY:
==2287470==     in use at exit: 0 bytes in 0 blocks
==2287470==   total heap usage: 3 allocs, 3 frees, 9,688 bytes allocated
==2287470== 
==2287470== All heap blocks were freed -- no leaks are possible
==2287470== 
==2287470== For lists of detected and suppressed errors, rerun with: -s
==2287470== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)
```

### ./sudoku solve
reading from stdin provided by user
```c
$ myvalgrind ./sudoku solve 9
==2322025== Memcheck, a memory error detector
==2322025== Copyright (C) 2002-2017, and GNU GPL'd, by Julian Seward et al.
==2322025== Using Valgrind-3.16.0 and LibVEX; rerun with -h for copyright info
==2322025== Command: ./sudoku solve 9
==2322025== 
4 0 0 9 0 0 0 8 0
0 0 0 1 0 0 0 0 0
0 0 1 0 0 0 0 0 0
0 1 3 0 8 0 0 0 0
0 0 6 0 0 0 0 0 0 
0 0 5 0 0 6 4 0 0
0 0 0 0 0 0 7 0 3
0 0 0 0 0 0 0 0 9
0 6 0 0 0 0 0 4 0 


Provided Puzzle: 

4 0 0 9 0 0 0 8 0 
0 0 0 1 0 0 0 0 0 
0 0 1 0 0 0 0 0 0 
0 1 3 0 8 0 0 0 0 
0 0 6 0 0 0 0 0 0 
0 0 5 0 0 6 4 0 0 
0 0 0 0 0 0 7 0 3 
0 0 0 0 0 0 0 0 9 
0 6 0 0 0 0 0 4 0 

Solved Puzzle:

4 2 7 9 3 5 1 8 6 
3 5 8 1 6 2 9 7 4 
6 9 1 4 7 8 2 3 5 
2 1 3 5 8 4 6 9 7 
8 4 6 2 9 7 3 5 1 
9 7 5 3 1 6 4 2 8 
5 8 2 6 4 9 7 1 3 
7 3 4 8 2 1 5 6 9 
1 6 9 7 5 3 8 4 2 
==2322025== 
==2322025== HEAP SUMMARY:
==2322025==     in use at exit: 0 bytes in 0 blocks
==2322025==   total heap usage: 14 allocs, 14 frees, 11,522 bytes allocated
==2322025== 
==2322025== All heap blocks were freed -- no leaks are possible
==2322025== 
==2322025== For lists of detected and suppressed errors, rerun with: -s
==2322025== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)
```

### ./sudoku create | ./sudoku solve
reading from stdin provided by creator module
```c
$ myvalgrind ./sudoku create 9 | ./sudoku solve 9
==2295912== Memcheck, a memory error detector
==2295912== Copyright (C) 2002-2017, and GNU GPL'd, by Julian Seward et al.
==2295912== Using Valgrind-3.16.0 and LibVEX; rerun with -h for copyright info
==2295912== Command: ./sudoku create 9
==2295912== 
==2295912== 
==2295912== HEAP SUMMARY:
==2295912==     in use at exit: 0 bytes in 0 blocks
==2295912==   total heap usage: 3 allocs, 3 frees, 12,760 bytes allocated
==2295912== 
==2295912== All heap blocks were freed -- no leaks are possible
==2295912== 
==2295912== For lists of detected and suppressed errors, rerun with: -s
==2295912== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)

Provided Puzzle: 

0 0 0 0 0 0 0 0 0 
3 0 2 0 0 0 6 7 5 
0 0 0 0 0 0 0 8 9 
0 2 0 0 0 9 0 0 7 
0 0 3 0 2 7 0 0 0 
5 0 0 0 0 8 0 0 0 
4 0 0 0 0 0 0 0 0 
0 0 0 0 0 0 0 0 0 
1 0 0 0 9 0 4 0 0 

Solved Puzzle:

6 1 8 9 7 5 2 3 4 
3 9 2 1 8 4 6 7 5 
7 4 5 2 3 6 1 8 9 
8 2 1 3 4 9 5 6 7 
9 6 3 5 2 7 8 4 1 
5 7 4 6 1 8 3 9 2 
4 3 6 7 5 2 9 1 8 
2 8 9 4 6 1 7 5 3 
1 5 7 8 9 3 4 2 6 
```
Note: you are not supposed to run valgrind on bash scripts.

## GUI
The GUI is implemented on python3, to run it the user must have python3 installed. Additionally, the user must have cs1lib (provided in the GUI directory). The GUI mostly uses cs1lib functions for its functionality. Once the user has those components, they should run GUI.py on a software that is able to run python (like pycharm). When the user clicks run, the GUI screen appears and a sudoku grid begins filling itself in. Then, it stops. When it's stops it's because it's finished CREATING the puzzle. If the user wants the puzzle to be solved, the user must click "s" on their keyboard. The puzzle should then begin solving itself once the user does so. When the puzzle is completely done, the user can exit the window. 

To get the GUI to represent different sudoku puzzles (and even sudoku puzzles of different sizes), fill in a logfile from first running ./sudoku.sh create x | ./sudoku solve x (where x is the size of the puzzle). This should create TWO files in the GUI directory: clogfile.txt and slogfile.txt. This is because create and solve are called various times and we want the final time they're called (so we can't "append" solve to the end of the create file because we want solve to overwrite itself). Then, in the terminal do "cat clogfile.txt slogfile.txt > logfilex.txt to append the two files together. Then, download the logfile you created and put it into the directory where your python program is (in a python running software) and change the name of the file opened at the beginning of the GUI.py file to the downloaded file. 

GUI DOESN'T WORK FOR CUBE. DO NOT CALL the logfile product of ./sudoku.sh create 3 | ./sudoku solve 3 on GUI.


## Cube sudoku
Cube sudoku takes 6 4x4 puzzles (for the 6 faces of the cube). Face must have no repeats, each row and col extending around the cube must have no repeats as well. Below is an example of a unsolved cube and a solved cube: 
```c
        0 0 0 0 
        0 3 6 D 
        0 0 A 0 
        0 8 1 E 
0 0 0 0 A 9 0 0 0 0 0 0 
F 4 B 7 0 0 E 0 0 0 0 0 
2 0 E 5 0 0 7 0 D 0 0 8 
0 G 0 0 0 0 0 0 F 0 C 0 
        G 0 2 0 
        0 0 5 0 
        B 0 0 0 
        0 C 0 0 
                        0 4 0 0 
                        9 0 3 0 
                        B 0 G 5 
                        0 0 0 8 

Solved Puzzle:

        9 7 B G
        5 3 6 D
        F 2 A C
        4 8 1 E
D 1 3 C A 9 G 6 B 4 7 E 
F 4 B 7 C 1 E 8 9 6 2 5 
2 9 E 5 3 F 7 B D G A 8 
A G 8 6 2 4 D 5 F 1 C 3 
        G A 2 3 
        7 D 5 9 
        B E 8 F 
        6 C 4 1 
                        7 4 A 2 
                        9 C 3 F 
                        B 6 G 5 
                        E 1 D 8 
```

In this version of the output, let the cube faces be enumerated 0-5 such that:
```c
         face 0

face 1   face 2   face 3

         face 4

                         face 5
```
there exists a column containing faces 0,2,4,5
there exists a column containing faces 1,2,3,5
there exists a column containing faces 3,0,1,4 

To run 3d sudoku: call `./sudoku solve/create 3`.
All the solve functions are in the `/solver/solvecube.c`.
All the create functions are in `/creator/cubecreator.c`.
And the helper functions to both in `/common/cube.c`.

