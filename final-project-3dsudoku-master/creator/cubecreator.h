/* 
 * solvecube.c - solver module for Sudoku cube
 * 
 * Authors: William Scott, Isabella Zenkl, Genghe Zhu, Rachael Williams
 * 
 * CS50 Summer 2020
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>
#include "../common/file.h"
#include "../common/cube.h"

/**************** file-local global variables ****************/
/* none */

/**************** local types ****************/

/**************** global types ****************/

/**************** global functions ****************/
/* that is, visible outside this file */

/**************** local functions ****************/
/* not visible outside this file */


/**************** create_cube() ****************/
/*
 * function for creating cube
 */
int create_cube(int grid[6][4][4], FILE *fp);

/**************** generate_random_box() ****************/
/*
 * generates a random seed box for the solver to solve
 */
void generate_random_box(int grid[6][4][4]);

/**************** remove_random_num() ****************/
/*
 * removes a number after creater calls solver to create a puzzle
 */
void remove_random_nums(int grid[6][4][4]);
