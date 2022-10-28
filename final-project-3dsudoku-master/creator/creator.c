/* 
 * creator.c - creator module for Sudoku game
 * 
 * Authors: William Scott, Isabella Zenkl, Genghe Zhu, Rachael Williams
 * 
 * CS50 Summer 2020
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include "creator.h"
#include "../common/common.h"
#include "../solver/solver.h"

/*****function_prototypes*****/

#ifdef UNIT_TEST
#include "unittest.h"
//int main() {
    
    //create_sudoku();
//}
#endif // UNIT_TEST

/*********create_sudoku*********/
/****see creator.h for more****/
void create_sudoku(int numRow, int numCol, int sudoku[numRow][numCol], FILE *fp) {

    srand(time(0)); //seed initial random number according to time (to guarantee a different random number each time)
   
    int total = numRow * numCol; // total number of boxes in sudoku
    int upper = 0.5 * total; // upper is 50% of numbers
    int lower = 0.25 * total; // lower bound is 25% of numbers
   
    // rand() % (upper - lower + 1) + lower
    int totalnum = rand() % (upper - lower + 1) + lower; //chooses a random number between upper and lower for how many numbers to fill in
    
    // send info to log file
    fprintf(fp, "create\n");
    fprintf(fp, "%d\n", numRow);

    // call method to add the numbers
    add_nums(numRow, numCol, sudoku, totalnum, fp); 
}

/*************add_nums************/
/****see creator.h for more****/
void add_nums(int numRow, int numCol, int sudoku[numRow][numCol], int totalnum, FILE *fp) {

    // ensure we have at least numRow - 1 distinct values
    int numtakeout = rand() % numRow + 1; //selects a number from 1-numRow to pass over in for loop
    
    //for each number between 1-numRow
    for (int k = 1; k <= numRow;) {

        //if the number is not equal to numtakeout
        if (k != numtakeout) {

            //then choose a random column and row to add to
            int col = rand() % numCol; // generates numbers 0-numRow
            int row = rand() % numRow;

            // if that spot wasn't already filled in
            if (sudoku[row][col] == 0) {
                sudoku[row][col] = k; //fill in that spot with the current number

		// send info to logfile
                fprintf(fp, "%2d %2d %2d\n", k, row, col);
                
		k++; //increase k to next num since added succesfully
		totalnum--; //decrease totalnum (which has the total amount of nums that we should add)

            }
        }

        else {
            k++; //otherwise, if k is the number that we don't want, then skip over it
        }
    }
    
    /*****add the rest of numbers randomly*****/
    while (totalnum > 0) { //while we still have nums to add

        int numtoadd = rand() % (numRow - 1 + 1) + 1; //randomly select a number between 1-9 to add

        //randomly select a col and row to add to
        int col = rand() % numCol;
        int row = rand() % numRow;

        //if that row hasn't already been filled
        if (sudoku[row][col] == 0) {
            //check if the sudoku puzzle would still be valid if a number was added in that spot
            if (can_in_row(numtoadd, row, numRow, numCol, sudoku) 
			    && can_in_col(numtoadd, col, numRow, numCol, sudoku) 
			    && can_in_box(numtoadd, row, col, numRow, numCol, sudoku)) {
                
		sudoku[row][col] = numtoadd; //if so, then add the number
                totalnum--; //decrease totalnum

		// send info to logfile
                fprintf(fp, "%2d %2d %2d\n", numtoadd, row, col);
            }
        }
    }
}

