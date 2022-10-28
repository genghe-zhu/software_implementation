# Sudoku Design Spec

The **sudoku** is a program that mimics the popular 'sudoku' game. The user can call `./sudoku create` to create a new sudoku puzzle and `./sudoku solve` for the computer to solve a given puzzle.

* [User interface](#user-interface)
* [Inputs and Outputs](#inputs-and-outputs)
* [Functional decomposition into modules](#Functional-decomposition-into-modules)
* [Pseudo code for logic/algorithmic flow](#Pseudo-code-for-logic/algorithmic-flow)
* [Dataflow through modules](#Dataflow-through-modules)
* [Major data structures](#Major-data-structures)
* [Testing plan](#Testing-plan)

## User interface

The user interface uses the command-line interface. 

`./sudoku create` makes a new sudoku board that is printed out to the stdout. The numbers appear in a 9x9 grid of numbers seperated by whitespaces. Unfilled spaces are represented by a 0 since this number is not used in sudoku otherwise. 

Similarly, `./sudoku solve` will print the solution to stdout with all numbers 1-9 printed into the grid to display the unique solution to that sudoku puzzle.

## Inputs and outputs
**We will be using the suggested textual representation for our Sudoku grid between the modules.**

### create
Input: command-line parameters (see the User Interface above).

Output: prints the puzzle to stdout with all numbers 1-9 printed into the grid.

### solve
Input: command-line parameters (see the User Interface above).
- the inputted puzzle **must** comply with the format listed below

Output: prints the solution to stdout with all numbers 1-9 printed into the grid to display the unique solution to that sudoku puzzle.

### Puzzle Format
- 9x9 grid
- each row, column, and box contains 9 integers that range from 0 to 9, separated by a whitespace 
- 0 represents a missing number in the grid
- there will need to be at least 17 numbers generated (since that is the minimum number of clues that a well-formed sudoku can have with a unique solution) and at most 41 numbers (since our code requirement is to have at least 40 missing numbers). This means that a generated puzzle will have 41-64 missing numbers.
- of the numbers generated, at least 8 will be distinct numbers to ensure that the puzzle is well-formed with one unique solution.


## Functional decomposition into modules

`main` in sudoku.c: checks arguments and calls either solve or create

### Decomposition of Creator.c
`create` creates a grid by calling the methods specified below.
`create_sudoku` which seeds the random generator, randomly selects the amount of numbers that are going to be filled in in the grid, and calls add_nums and print_grid.
`add_nums` which randomly selects which number, if any, is not going to be added to the sudoku (a well-formed sudoku puzzle has to have at least 8 distinct numbers, so we allowed for either 8 or 9 distinct numbers in our puzzle). Then, it adds the rest of the numbers randomly until it reaches the amount of numbers that should be added according to the random number generator called in `create_sudoku`.

### Decomposition of Solver.c
`solve` solves the grid by calling the methods below  
`load_puzzle` loads puzzle from stdin
- checks for invalid characters 

`IsValidPuzzle` validates the input grid such that it can be solved
- all numbers in range [0,9]
- no repeats in row/col/box (calls `repeat_exists`)  

`find_empty_grid` finds empty cell to insert  
`check_number` recursively tries inserting numbers  
`repeat_exists` finds if there are repeats in row/col/box  

### Common.c
`can_in_row` finds if you can insert a number in row  
`can_in_col` finds if you can insert in a col  
`can_in_box` finds if you can insert in a box  
`print_grid` prints out the grid

## Pseudo code for logic/algorithmic flow

### create
`create_sudoku()`
1. seed random number
2. randomly choose a number between 17-41. This number is going to be the amount of numbers that the puzzle is going to fill in. The more numbers, the easier the puzzle is to solve.
3. then it calls add_nums (specified below)
4. then it calls print_grid (a method in the common.a library)

`add_nums()`
1. generate a random number to not have in the initial 9 distinct numbers
1. loop through numbers 1-9
    1. if the number is not equal to the random number we're not putting in
    2. generate random rows and columns
    3. check if the sudoku at the row and column has already been filled
        3. put the number in the sudoku
        4. repeat the loop with the next number by incrementing up
        4. increment the total numbers to add down 
    1. else repeat the loop with the next number by incrementing up

5. while total numbers to add is greater than 0
    5. generate a random number
    5. generate random rows and columns
    6. check if the sudoku at the row and column has already been filled
        6. check if the number can be validly placed into sudoku puzzle per row, column, and box rules
            6. put the number in the sudoku
            7. increment the total numbers to add down


### solve

1. load grid from stdin
2. call `IsValidPuzzle` to validate grid 
3. call `check_number` to start recursive solution   
    4. advance to next empty cell in grid  
    5. if no empty cells, then we have solved the puzzle  
    6. else try numbers [1,9] in cell calling `can_in_row`, `can_in_col` and `can_in_box`  
        7.  recursively call the function `check_number` for all safe cases from 1 to 9 returning true if number is 'safe'  
        8.  once there are no more empty cells, return true  
        9.  otherwise false--that is, hte puzzle is unsolvable

## Major data structures

* `int[9][9]` 2D array to store the sudoku puzzle 

## Testing plan

*Unit testing*. A small test program to test both the creator and solver modules.

*Integration testing*. Assemble the Sudoku and test it as a whole. 

*Regression testing*. 
- create a 9x9, 4x4, and 6x6 puzzle in the regress directory
- run the shell script piping in the puzzles to ./sudoku solve
- comparing output to verify consistency
