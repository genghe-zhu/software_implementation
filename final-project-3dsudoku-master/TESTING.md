# Sudoku Testing

### unit tests - solver.c

We used premade sudoku puzzles to test our solver.c. We know that these puzzles for sure have a solution, so this gave us a way to test the sudoku solver independently from the creator. By also running these puzzles in a sudoku solver online, we were able to manually compare solutions to ensure that the sudoku solver was indeed generating the proper solution to a sudoku puzzle.

### regress testing

Regress testing gave us a way to ensure that the solver output was consistent. From the puzzles of sizes 4, 6, and 9 named "#puzzle.txt" in the regress folder, we ran regress tests. This way, we got to compare the output across multiple runs on the same puzzle to ensure that the solver worked consistently.

We ran `$ regress/regress.sh regress/base ./testing.sh` three times, providing the same three puzzles a 9x9, 4x4, and 6x6 to the testing script.

```
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
The output was consistent across multiple runs.
```

### unit tests - creator.c

Once we knew that the sudoku solver worked properly, our solver became the easiest way to test the creator. We could simply pipe the output of creator to solver and view the results. If solver would generate a solution from the provided puzzle without causing any invalid or unsolvable puzzle errors, then we knew that creator worked.

Given our method our method of implementating creator, we used the shell script `sudoku.sh` to generate this valid puzzle. The solver does indeed toss out all unsolvable puzzles and properly solves a valid puzzle, so the `sudoku.sh` works with our creator method. Here is a sample output from a successfully created and solved puzzle.

`bash$ ./sudoku.sh create 9 | ./sudoku solve 9`

```
Provided Puzzle: 

0 0 0 0 0 0 0 1 0 
6 0 1 0 0 7 0 0 3 
0 0 0 0 0 6 0 4 0 
0 0 5 0 0 1 2 0 0 
0 0 0 3 6 0 0 9 4 
0 0 4 0 0 0 0 5 0 
0 0 0 0 8 0 7 0 0 
0 0 0 0 0 2 0 6 0 
9 0 0 0 0 0 8 0 5 

Solved Puzzle:

2 3 9 4 5 8 6 1 7 
6 4 1 2 9 7 5 8 3 
5 7 8 1 3 6 9 4 2 
3 9 5 8 4 1 2 7 6 
7 8 2 3 6 5 1 9 4 
1 6 4 7 2 9 3 5 8 
4 1 6 5 8 3 7 2 9 
8 5 3 9 7 2 4 6 1 
9 2 7 6 1 4 8 3 5 
```

This works similarly for sudoku's of different sizes. For instance, here is a sudoku of size 4 with another successful output.

`bash$ ./sudoku.sh create 4 | ./sudoku solve 4`

Output:

```
Provided Puzzle: 

0 4 1 0 
0 0 4 3 
0 3 0 0 
0 2 0 0 

Solved Puzzle:

3 4 1 2 
2 1 4 3 
1 3 2 4 
4 2 3 1 
```

We also did this for sudoku puzzles of size 6 and 16, as well as the cube sudoku. Outputs are not shown here for the sake of saving space in the TESTING.md file.

### Error Checking

All of our code was developed defensively so we have many parameters and error checks throughout the different files of our program. For instance, sudoku.c validates arguments before running either create or solve methods. For our sudoku.sh which handles creating, this also validates its arguments. So if create is called, there are multiple levels of checks throughout the programs for the sake of having defensive code.

We purposely passed in invalid numbers of arguments and bad arguments, as well as bad sudoku puzzles, to test our error checking.

Our testing script `testing.sh` runs many error checks (as well as valid runs of the program). The testing script shows the output and then checks the result of the run and tells the user if the test had passed or not. Either run `./testing.sh` or check the `testing.out` file to see how testing.sh handles errors as well as valid tests to the sudoku program.
