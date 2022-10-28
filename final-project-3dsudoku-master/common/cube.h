/* 
 * headerfile for cube.c - structs and functions for cube suduko that common to both creator and solver modules
 * 
 * Authors: William Scott, Isabella Zenkl, Genghe Zhu, Rachael Williams
 * 
 * CS50 Summer 2020
 */

#ifndef __CUBE_H
#define __CUBE_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

/**************** local types ****************/
struct position {
        int axis;
        int row;
        int col;
};

/**************** initialize_empty () ****************/
/* 
 * helper function to create grid of 0s
 */
void initialize_empty_cube(int grid[6][4][4]);

/**************** print_grid () ****************/
/* 
 * helper function to print grid
 */
void print_grid_cube(int grid[6][4][4]);

/**************** can_in_col () ****************/
/*
 * checks to see if num can be inserted in col
 * by sudoku rules 
 */ 
bool can_in_col_cube(int num, int axis, int col, int grid[3][16][4]);

/**************** can_in_box () ****************/
/*
 * checks to see if num can be inserted in 4x4 box  
 * by sudoku rules
 */ 
bool can_in_box_cube(int num, int row, int col, int box, int grid[6][4][4]);

/**************** rotate_box_clockwise_and_copy () ****************/
/*
 * rotate the box clockwise and copy it to columns
 */ 
bool rotate_box_clockwise_and_copy(int box, int axis, int level, int grid[6][4][4], int columns[3][16][4], struct position pos[6][4][4]);

/**************** rotate_box_counter_clockwise_and_copy () ****************/
/*
 * rotate the box counter clockwise twice and copy it to columns
 */ 
bool rotate_box_counter_clockwise_and_copy(int box, int axis, int level, int grid[6][4][4], int columns[3][16][4], struct position pos[6][4][4]);

/**************** rotate_box_counter_clockwise_twice_and_copy () ****************/
/*
 * rotate the box counter clockwise and copy it to columns
 */ 
bool rotate_box_counter_clockwise_twice_and_copy(int box, int axis, int level, int grid[6][4][4], int columns[3][16][4], struct position pos[6][4][4]);

/**************** can_in_box () ****************/
/*
 * copy the box to columns
 */ 
bool copy_box(int box, int axis, int level, int grid[6][4][4], int columns[3][16][4], struct position pos[6][4][4]);

#endif // __CUBE_H
