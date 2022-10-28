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
#include <time.h>
#include "../common/file.h"
#include "../common/cube.h"
#include "cubecreator.h"
#include "../solver/solvecube.h"

/**************** file-local global variables ****************/
/* none */

/**************** local types ****************/

/**************** global types ****************/

/**************** global functions ****************/
/* that is, visible outside this file */

/**************** local functions ****************/
/* not visible outside this file */


/**************** solve() ****************/
int create_cube(int grid[6][4][4], FILE *fp)
{
	fprintf(fp, "create cube\n");
	initialize_empty_cube(grid);
	generate_random_box(grid);
	int i = solve_cube(grid, fp);
	remove_random_nums(grid);
	print_grid_cube(grid);
	return i;
}


/**************** generate_random_box() ****************/
void generate_random_box(int grid[6][4][4])
{
	srand(time(0));
	int box = rand() % (6);

	int possibleNum[16];
	for (int i = 1; i < 17; i++) 
	{
		possibleNum[i-1] = i;
	}

	int size = 16;
	for (int i = 0; i < 4; i ++) 
	{
		for (int j = 0; j < 4; j++) 
		{
			// generate random number
			srand(time(0));
			int arrayPosition = rand() % (size);
			
			grid[box][i][j] = possibleNum[arrayPosition];
			possibleNum[arrayPosition] = possibleNum[size - 1];
			size--;

		}
	}

	return;

}



/**************** remove_random_num() ****************/
void remove_random_nums(int grid[6][4][4])
{
	
	srand(time(0));
	for (int b = 0; b < 6; b++)
	{
		for (int i = 0; i < 4; i++) 
		{
			for (int j = 0; j < 4; j++)
			{
				int removeOrNot = (rand() % (2));
				//printf("%d\n", removeOrNot);
				if (removeOrNot == 0) {
					grid[b][i][j] = 0;
				} 
			}
			
		}
	
	}

}
