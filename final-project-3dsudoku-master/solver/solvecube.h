/* 
 * solvecube.h - solver module for cube Sudoku game
 * 
 * Authors: William Scott, Isabella Zenkl, Genghe Zhu, Rachael Williams
 * 
 * CS50 Summer 2020
 */

#ifndef __SOLVECUBE_H
#define __SOLVECUBE_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include "../common/cube.h"

/**************** file-local global variables ****************/
/* none */

/**************** local types ****************/

/**************** solve_cube() ****************/
/*
 * drives the solver module for 3D puzzle
 */ 
int solve_cube(int cube[6][4][4], FILE *fp);

/**************** IsValidCube() ****************/
/*
 * checks if cube is valid:
 * - no negative numbers
 * - all numbers within range [0,9]
 * - no repeats in col/box
 */ 
bool IsValidCube(int grid[6][4][4], int columns[3][16][4], struct position pos1[6][4][4], struct position pos2[6][4][4]);

/**************** save_columns() ****************/
/*
 * saves columns from grid for future can in col
 */
void save_columns(int grid[6][4][4], int columns[3][16][4], struct position pos1[6][4][4], struct position pos2[6][4][4]);

/**************** find_empty_grid_cube() ****************/
/*
 * finds an empty position in cube
 */
struct position find_empty_grid_cube(int grid[6][4][4]);

/**************** can_in_position() ****************/
/*
 * checks if you can insert in that position
 */
bool can_in_position(int num, int box, int row, int col, int grid[6][4][4], int columns[3][16][4],
                struct position pos1[6][4][4], struct position pos2[6][4][4]);

/**************** assign_num_position() ****************/
/*
 * assigns a number to a position in cube
 */
void assign_num_position(int num, int box, int row, int col, int grid[6][4][4], int columns[3][16][4],
                struct position pos1[6][4][4], struct position pos2[6][4][4]);

/**************** check_number_cube() ****************/
/*
 * checks number recursively using backtracking
 */
bool check_number_cube(int grid[6][4][4], int columns[3][16][4], struct position pos1[6][4][4], struct position pos2[6][4][4], FILE *fp);


/**************** print_columns() ****************/
/*
 * debug function for printing the columns
 */
void print_columns(int columns[3][16][4]);


/**************** print_pos() ****************/
/*
 * debug function for printing the position structs
 */
void print_pos(struct position pos1[6][4][4], struct position pos2[6][4][4]);

/**************** load_cube () ****************/
/*
 * read the cube from stdin and loads into sudoku parameter
 */
bool load_cube(int cube[6][4][4], FILE *fp);

/**************** load_cube_demo() ****************/
/*
 * loads in numbers to demo solve
 */
void load_cube_demo(int grid[6][4][4]);

#endif // __SOLVECUBE_H
