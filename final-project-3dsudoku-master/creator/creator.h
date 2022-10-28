/* 
 * creator.h - header file for creator.c
 * 
 * Authors: William Scott, Isabella Zenkl, Genghe Zhu, Rachael Williams
 * 
 * CS50 Summer 2020
 */

#ifndef __CREATOR_H
#define __CREATOR_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include "../common/common.h"

/**************** create_sudoku****************/
/* 
* seeds random number, randomly chooses a number between 17-41. 
* This number is going to be the amount of numbers that the puzzle is going to fill in (totalnum)
* The more numbers, the easier the puzzle is to solve.
* Then, it prints a "create" message to the logfile (for GUI).
* Then, it calls add_nums (specified below)
*/
void create_sudoku(int numRow, int numCol, int sudoku[numRow][numCol], FILE *fp); 

/**************** create_cube ****************/
void create_cube(int cube[6][4][4], FILE *fp);

/**************** add_nums****************/
/* 
* generates a random number to not have in the initial 9 distinct numbers. Fills in all numbers besides that one (to guarantee that we at
* least have 8 distinct numbers in the initial sudoku so that the puzzle has one unique solution)
* then, once we have at least 8 distinct numbers, it fills in all other numbers until it reaches totalnum (specified above).
* additionally, it prints a message for every number that is added into the sudoku in the logfile (for GUI)
*/
void add_nums(int numRow, int numCol, int sudoku[numRow][numCol], int totalnum, FILE *fp);

#endif // __CREATOR_H
