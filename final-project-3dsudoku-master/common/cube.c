/* 
 * cube.c - structs and functions cube to both creator and solver modules
 * included in cube lib
 * 
 * Authors: William Scott, Isabella Zenkl, Genghe Zhu, Rachael Williams
 * 
 * CS50 Summer 2020
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "memory.h"
#include <math.h>
#include "cube.h"

/**************** local types ****************/

/**************** initilize_empty () ****************/
void initialize_empty_cube(int grid[6][4][4])
{
	for (int i = 0;  i < 6; i++) 
	{
		for (int row = 0; row < 4; row++)
		{
			for (int col = 0; col < 4; col++)
			{
				grid[i][row][col] = 0;
				//grid[i][row][col] = row*4+col;
			}
		}
	}
}

/**************** print_grid () ****************/
void print_grid_cube(int grid[6][4][4])
{
	for (int i = 0; i < 4; i++) 
	{
		printf("%8c", ' ');

		for (int j = 0; j < 4; j++) 
		{
			if (grid[0][i][j] > 9) {
                                char c = grid[0][i][j] + 55;
                                printf("%c ", c);
                        } else {
				printf("%d ", grid[0][i][j]);
                        }

		}
		printf("\n");
	}

	for (int i = 0; i < 4; i++) 
	{
		for (int b = 1; b < 4; b++) 
		{
			for (int j = 0; j < 4; j++)
			{
				if (grid[b][i][j] > 9) {
                                	char c = grid[b][i][j] + 55;
                                	printf("%c ", c);
                        	} else {
					printf("%d ", grid[b][i][j]);
                        	}
			}
		
		}

		printf("\n");
	
	}
	
	for (int i = 0; i < 4; i++) 
        {
                printf("%8c", ' ');

                for (int j = 0; j < 4; j++) 
                {
                        if (grid[4][i][j] > 9) {
                                char c = grid[4][i][j] + 55;
                                printf("%c ", c);
                        } else {
                                printf("%d ", grid[4][i][j]);
                        }

                }
                printf("\n");
        }	


	for (int i = 0; i < 4; i++)
        {
                printf("%24c", ' ');

                for (int j = 0; j < 4; j++)
                {
                        if (grid[5][i][j] > 9) {
                                char c = grid[5][i][j] + 55;
                                printf("%c ", c);
                        } else {
                                printf("%d ", grid[5][i][j]);
                        }
        
                }
                printf("\n");
        }	
}


/**************** can_in_col () ****************/
bool can_in_col_cube(int num, int axis, int col, int columns[3][16][4])
{
	// check if the num is in col
	for (int i = 0; i < 16; i++)
	{
		if (columns[axis][i][col] == num)
		{
			return false;
		}
	}
	return true;
}

/**************** can_in_box () ****************/
bool can_in_box_cube(int num, int row, int col, int box, int grid[6][4][4])
{

	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
                        if (grid[box][i][j] == num)
                        {
                                if (i != row && j != col)
                                {
                                        return false;
                                }
                        }
                }
        }

	return true;
}


/**************** rotate_box_clockwise_and_copy () ****************/
bool rotate_box_clockwise_and_copy(int box, int axis, int level, int grid[6][4][4], int columns[3][16][4], struct position pos[6][4][4])
{

	int plus = 4 * level;
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			int x = j;
			int y = 3 - i; 
			columns[axis][x+plus][y] = grid[box][i][j];
			struct position p = {axis, x+plus, y};
			pos[box][i][j] = p;
		}
	}
}

/**************** rotate_box_counter_clockwise_and_copy () ****************/
bool rotate_box_counter_clockwise_and_copy(int box, int axis, int level, int grid[6][4][4], int columns[3][16][4], struct position pos[6][4][4])
{

	int plus = 4 * level;
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			int x = 3 - j;
			int y = i; 
			columns[axis][x+plus][y] = grid[box][i][j];
			struct position p = {axis, x+plus, y};
			pos[box][i][j] = p;
		}
	}
}



/**************** rotate_box_counter_clockwise_twice_and_copy () ****************/
bool rotate_box_counter_clockwise_twice_and_copy(int box, int axis, int level, int grid[6][4][4], int columns[3][16][4], struct position pos[6][4][4])
{

	int plus = 4 * level;
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			int x = 3 - i;
			int y = 3 - j; 
			columns[axis][x+plus][y] = grid[box][i][j];
			struct position p = {axis, x+plus, y};
			pos[box][i][j] = p;
		}
	}
}


/**************** copy_box () ****************/
bool copy_box(int box, int axis, int level, int grid[6][4][4], int columns[3][16][4], struct position pos[6][4][4])
{
	int plus = 4 * level;
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			columns[axis][i+plus][j] = grid[box][i][j];
			struct position p = {axis, i+plus, j};
			pos[box][i][j] = p;
		}
	}
}

