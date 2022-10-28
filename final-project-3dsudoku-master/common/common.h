/* 
 * headerfile for common.c - structs and functions common to both creator and solver modules
 * 
 * Authors: William Scott, Isabella Zenkl, Genghe Zhu, Rachael Williams
 * 
 * CS50 Summer 2020
 */

#ifndef __COMMON_H
#define __COMMON_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

/**************** initialize_empty () ****************/
/* 
 * helper function to create grid of 0s
 */
void initialize_empty(int numRow, int numCol, int grid[numRow][numCol]);

/**************** print_grid () ****************/
/* 
 * helper function to print grid
 */
void print_grid(int numRow, int numCol, int grid[numRow][numCol]);

/**************** can_in_row () ****************/
/*
 * checks to see if num can be inserted in row 
 * by sudoku rules
 */ 
bool can_in_row(int num, int row, int numRow, int numCol, int grid[numRow][numCol]);

/**************** can_in_col () ****************/
/*
 * checks to see if num can be inserted in col
 * by sudoku rules 
 */ 
bool can_in_col(int num, int col, int numRow, int numCol, int grid[numRow][numCol]);

/**************** can_in_box () ****************/
/*
 * checks to see if num can be inserted in 3x3 box  
 * by sudoku rules
 */ 
bool can_in_box(int num, int row, int col, int numRow, int numCol, int grid[numRow][numCol]);

#endif // __COMMON_H
