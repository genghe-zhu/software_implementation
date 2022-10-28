# Implementation of sudoku

* [Major Data Structures](#Major-Data-Structures)
* [Functions / Pseudo Code](#Functions-/-Pseudo-Code)
* [Output / Storage](#Output-/-Storage)

## Major data structures
These helper modules provide the primary data structures for sudoku:
* solver.c
* creator.c
* cube.c
* common.c
* sudoku.sh

 Useful definitions:
 * int ***size*** which denotes the size of the grid either 4x4, 6x6, 9x9, or 16x16
   -  if size = 3, then that signals creator to generate a cube instead of the standard 2D puzzle

**sudoku.sh**

For 2D sudoku puzzles of sizes 4, 6, 9, and 16 the create and solve run together in order to find a valid puzzle. Since our creator operates by adding a quantiy of numbers between the lower and upper bounds, it uses the two conditions available to us to ensure the greatest probability of getting a valid puzzle:
	
	1. a well-formed sudoku puzzle of rank n must have at least *n^2 - 1* unqiue numbers (this is equivalent to 4, 6, 9, or 16 all - 1)
	2. a well-formed sudoku puzzle must have at least 17 given numbers for a rank 3, 9x9, sudoku puzzle. This lower bound is not known for sudoku puzzles of other ranks, so we used an approximate of 25% of the numbers. This gives 9x9 sudoku puzzle a lower bound of 20 given numbers in our implementation and provides a more generizable scenario for sudoku puzzles of other ranks.

All well-formed sudoku puzzles have these qualities, but it is not sufficient for any sudoku puzzle to be well-formed. Meeting these conditions gives us the highest probability of generating a well-formed sudoku puzzle, and from there we just keep running create and solve together. In academic papers on the subject of sudoku, this creator method is called the Las Vegas method due to its reliance on probability and keep rerunning create and solve until it finds a well-formed puzzle. 

At its most basic function, the `sudoku.sh` file runs create and solve together in a while loop until it finds a solvable sudoku puzzle.

## Functions / Pseudo Code

### sudoku.c

`main`
* check arguments: must be 3 args, then check if called by server
* gets the size of puzzle from arguments
* call either run_creator(size) or run_solver(size) passing the size from argument

`get_sudoku_size`
* parses a string `char *ssize*
* only returns an integer if the size given was 3, 4, 6, 9, or 16

`run_creator`
* opens logfile for GUI
* if it is a 2D puzzle, initializes an empty sudoku puzzle with dimensions size by size and calls `create_sudoku`
* if it is a 3D puzzle, initializes an empty cube and calls `create_cube`

`run solver`
* opens logfile for GUI
* if it is a 2D puzzle, initializes an empty sudoku puzzle with dimensions size by size
	- loads in the provided puzzle with `load_puzzle`
	* calls `solve`
* if it is a 3D puzzle, initializes an empty cube sudoku puzzle with dimensions 6x4x4
	* loads provided puzzle with `load_cube`
	* calls `solve_cube`

### common library
includes:
* common.c for functions unviversal across the modules
* cube.c for functions related to the cube puzzle
* file.c for reading from stdin
* memory.c for memory related functions

#### common.c

`initialize_empty`
* initializes an empty grid by looping through `numRow` and `numCol`, setting every value of grid to 0

`print_grid`
* loops through `numRow` and `numCol`
* checks if the number is greater than or equal to 10
  * if greater than 10, convert number to hexidecimal by converting into to char + 55
  * print the char instead of int
* else just print the int if number less than 10

`can_in_row`
* given a row and a number, loop through that row
* check if the number already exists in that row
* if so return false, otherwise return true

`can_in_col`
* given a colunn and a number, loop through that column
* check if the number already exists in that column
* if so return false, otherwise return true

`can_in_box`
* given a row, column, and a number, first determine the dimensions of the box
* if the box is 4,9,16, then the box is just the square root of the `numRow`
* else, the puzzle must be 6x6, so the box sizes are 2x3
* check if the number already exists in that box by looping though the box
* if so return false, otherwise return true

#### cube.c

High level overview: divide each 4x4 into a box, so there are 6 boxes in total. Since there are three ways we need to satisfy the 1-16 rules, so copy those boxes into 3 columns to represent the x,y,z axes. Each column has 4 boxes. Notice some of the boxes orientation needs to be changed (rotated in some way) when inserting into a column. Also keep two arrays pos1 and pos2. Each of them saves the saved location in the 6x4x4 box into the columns, so when we change a number in the box, we also change the corresponding number in the columns. 

`initialize_empty_cube`
* initializes an empty cube puzzle by looping through all 6 faces, then the 4x4 box and setting every value to 0

`print_grid_cube`
* first print face 0
  * loop through the box, but add 8 spaces before every row for formatting
* next print faces 1,2,3
  * loop through every row, then have a nested loop for the box, then have a nested loop for every column
* next print face 4
  * loop through the box, but add 8 spaces before every row for formatting
* finally print face 5
  * loop through the box, but add 24 spaces before every row for formatting

`can_in_col_cube`
* given an axis, number and col, check if the number is in the col
* loop through the col for that axis
* return false if that number already exists, otherwise return true

`can_in_box_cube`
* basically the same as `can_in_box` for 2d cube, but this time give box number
* since we know the size must be 4x4, loop through the given box to see if the number already exists
* if so return false, else, return true

`rotate_box_clockwise_and_copy`
* loop through the box, and keep the rows in the column the same, but change the columsn to 3-i. So for example, if a value in the box was at 4,0 before, it now becomes 0,0 after the rotate. 
* looping through these new positions, take note of what position it is, and save it into a struct position

`rotate_box_counter_clockwise_and_copy`
* same as the metod above, loop through the box, but this time keep the columns in the column the same, but change the row to 3-j. So for example, if a value was at 0,0 before, now its at 4,0.
* looping through these new positions, take note of what position it is, and save it into a struct position

`rotate_box_counter_clockwise_twice_and_copy`
* same as method above, but now change row to 3-i and column to 3-j. So if a value was at 0,0 before, now it is at 4,4. 
* looping through these new positions, take note of what position it is, and save it into a struct position

`copy_box`
* loops through the box and copies it exactly as it is into the columns array
* looping through these new positions, take note of what position it is, and save it into a struct position

### solver

#### solver.c

`solve`
* checks if it is a valid puzzle with `IsValidPuzzle`
* then uses `check_number` to solve the puzzle
* if it is solvable, return 0, else return 1

`IsValidPuzzle`
* loops through the puzzle row and col
* makes sure there are no negative numbers, all the numbers are in range for the size (ex: for 9x9, max num is 9, for 16x16 max num is 16... etc), makes sure no repeats already exist in row/col/box by calling `repeat_exists`
* returns true if all conditions met, otherwise return false

`repeat_exists`
* given a number, first check if that number is not 0
* then check if there are no repeats in the row
* then check if there are no repeats in the column
* then check if there are no repeats in the box

`find_empty_grid`
* used by `check_number`
* loops through the grid to see if there are any spaces that are still 0
* if so, then return a structure with the row,col position of where it is

`check_number`
* recursive solve method for sudoku
* first finds empty grid 
* then tries each number 1-maxnum to see if it can insert it
* if so, then continues to call itself to find next empty space
* if not, then it goes back and tries a different number

`load_puzzle`
* reads puzzle from stdin by reading every line
* then gets the first number of that line, loops through the other numbers to convert them to int
* if it is 16x16 grid, then accept hexidecimal characters
* adds that number to the sudoku grid
* then continues with next number until all numbers added
* terminates if bad character in the line

#### cubesolve.c

`solve_cube`
* first initializes the columns[3][16][4] array, and the two position structures
* calls `IsValidCube` to make sure grid is valid
* then solves  with `check_number_cube`
* if it is solvable, return 0, otherwise return 1

`IsValidCube`
* first checks if tere are repeats in the boxes
* then saves the boxes into columns with `save_columns`
* check can in col

`print_columns`
* debug function used to see if the columns are saved correctly
* loop through the axes, then the boxes to print the value at every column

`print_pos`
* debug function to see if the positions saved are correct
* loop through the position structs to print out where each value was saved after rotations

`save_columns`
* saved every box into its correct axis column with the correct rotate function if needed

`find_empty_grid_cube`
* loops through the boxes then the rows and columsn to see if that value at the position is 0
* if so it returns that position

`can_in_position`
* checks if the number can be inserted in that position 
* checks if it can be inserted in box
* checks if can be inserted in column
* then checks if there any conflicts with the other columns 

`assign_num_position`
* adds the number to the position structures
* assigns that number in the grid to be the number given

`check_number_cube`
* first tries to find empty slots
* then when it finds one, check numbers 1-16 if it can be put in that position
* if it can, then `assign_num_position`
* continue recursive check, if it doesnt work backtrack 
* return true if it can be solved, false it it cannot

`load_cube`
* reads line from stdin for each face
* then loops through the other numbers in the line
* then moves to to the other faces, and converts the number into int
* adds to sudoku grid and gets next number

### creator

#### creator.c
`create_sudoku`
* takes the following parameters: `create_sudoku(int numRow, int numCol, int sudoku[numRow][numCol], FILE *fp)` 

1. seed the random number generator
	* our implementation uses time(0) from <time.h> module. This allows the random number generator to be seeded at the second that the program was run.
2. figure the upper and lower bounds for how many numbers the sudoku puzzle will start out with.
	* our implementation uses 0.5 times the total number of boxes in the sudoku for the upper bound, and 0.25 times the total number of boxes for the lower bound.
	* these numbers are most important to the classic 9x9 sudoku puzzle. All well-formed 9x9 sudoku puzzles have at least 17 given numbers. 81 * 0.25 = 20, so this is close to 17. 81 * 0.5 = 40, whic 41 is the maximum number of givens per our design spec so that a sudoku puzzle is still fun to solve.
3. uses rand() to get a random number between upper and lower bounds for the total number to be added to the puzzle as givens.
4. call add_nums method

`add_nums`
* takes the following parameters: `add_nums(int numRow, int numCol, int sudoku[numRow][numCol], int totalnum, FILE *fp)`

1. use rand() to pick one random number to not **guarantee** a spot in the sudoku puzzle.
	* a well-formed sudoku puzzle of rank *n* must have *n^2 - 1* unique numbers, so our implementation guarantees this.
2. loop through all numbers to be put in
	3. check that this number is not equal to the number that is not **guaranteed* a spot
		4. use rand() to generate numbers for the column and row
		5. check that the column and row is empty (0)
			* we do not need any further checks here since we are adding unqiue numbers. The unique numbers will never conflict with the sudoku column, row, and box rules at this point.
			6. put that number at that row and column
			7. increment to the next number
			8. lower the total numbers since one less needs to be put in 
	3. increment to the next number to pass over it

9. while we still have numbers to add, (the total is greater than 0)
	10. use rand() to generate a random number to add
	11. use rand() to generate numbers for the column and rows
	12. check that the column and row is empty (0)
		13. check that the number can be validly placed here per the column, row, and box rules of sudoku
			* in our implementation we have these three functions in the `common` module in `common.c`. This allows both creator and solver to share these important helper functions.
			14. put that number at that row and column
			15. increment the total numbers to be added down
	
#### cubecreator.c

`create_cube`
* initializes an empty cube
* picks a random box and generates it, then adds it to the grid
* solve box on that grid
* then remove numbers from the grid
* finally print the created grid and solve again to print the created solution

`generate_random_box`
* first initializes `srand(time(0))` to get random numbers
* gets a random box 0-5 to fill
* then creates an array of possible numbers
* then inserts the possible numbers so the array at indexes 0-15 is filled with numbers 1-16
* then generates random numbers by removing from that array
	* if removed from array, then the last number of the array replaces it, so we never duplicate

`remove_random_nums`
* first initializes `srand(time(0))` to get random numbers
* then loops through every box, row, col
* then picks a random number either 0 or 1
* if it is 0, then replace that box with 0
* if it is 1, then keep the number as is
* should end up with about half of the numbers taken away

### sudoku.sh
This pseudocode is very top-level. 

1. validate the arguments
	* argument 2 is the size of the sudoku, so run if statements and set a number variable equal to this parameter
2. set a found puzzle variable equal to 0, this will act as a boolean.
3. while a puzzle is not found (the variable is still 0)
	4. run `./sudoku create number | ./sudoku solve number` together
		* it is optional (but a good idea) to suppress output from the unsuccessful runs. Our implementation does this by splitting the command-line and sending each output into puzzle.txt and solution.txt files.
	5. if the return value of the last run is equal to 0
		6. a puzzle has been found, so set boolean integer to non-zero
		7. display the completed puzzle

## Output / Storage

### ./sudoku.sh create size
outputs the generated puzzle to stdout
- gaurentees that the puzzle is solvable

The puzzle is almso written to a file named 'puzzle.txt' which is read line-by-line by the creatorserver-fork.

### ./sudoku solver size
outputs the solver puzzle to stdout


