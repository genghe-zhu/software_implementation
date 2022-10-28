/* 
 * solver.h - solver module for Sudoku game
 * 
 * Authors: William Scott, Isabella Zenkl, Genghe Zhu, Rachael Williams
 * 
 * CS50 Summer 2020
 */

#ifndef __SOLVER_H
#define __SOLVER_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

/**************** file-local global variables ****************/
/* none */

/**************** local types ****************/
struct singleGrid {
        int row;
        int col;
};

/**************** solve() ****************/
/*
 * drives the solver module for 2D puzzle
 */ 
int solve(int numRow, int numCol, int grid[numRow][numCol], FILE *fp);

/**************** solve_cube() ****************/
/*
 * drives the solver module for 3D puzzle
 */ 
int solve_cube(int cube[6][4][4], FILE *fp);

/**************** IsValidPuzzle() ****************/
/*
 * checks if puzzle is valid:
 * - no negative numbers
 * - all numbers within range [0,9]
 * - no repeats in row/col/square
 */ 
bool IsValidPuzzle(int numRow, int numCol, int grid[numRow][numCol]);

/**************** repeat_exists() ****************/
/*
 * checks to see if there are multiple num in row, col, and square
 */ 
bool repeat_exists(int row, int col, int numRow, int numCol, int grid[numRow][numCol]);

/**************** find_empty_grid () ****************/
/*
 * finds the next empty space in the grid
 * designated by a 0
 */ 
struct singleGrid find_empty_grid(int numRow, int numCol, int grid[numRow][numCol]);

/**************** check_number () ****************/
/*
 * recursively solves the puzzle
 * - backtracking algorithm
 */ 
bool check_number(int numRow, int numCol, int grid[numRow][numCol], FILE *fp);

/**************** load_puzzle () ****************/
/*
 * read the puzzle from stdin and loads into sudoku parameter
 */
bool load_puzzle(int numRow, int numCol, int sudoku[numRow][numCol], FILE *fp);

#endif // __SOLVER_H
