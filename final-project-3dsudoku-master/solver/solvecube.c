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
#include "solvecube.h"

/**************** file-local global variables ****************/
/* none */

/**************** local types ****************/

/**************** global types ****************/

/**************** global functions ****************/
/* that is, visible outside this file */

/**************** local functions ****************/
/* not visible outside this file */


/**************** solve() ****************/
int solve_cube(int grid[6][4][4], FILE *fp)
{
	fprintf(fp, "solve cube\n");

	int columns[3][16][4];
	struct position pos1[6][4][4];
	struct position pos2[6][4][4];

	/* check if the provided puzzle is valid */
	if (!IsValidCube(grid, columns, pos1, pos2))
	{
		return 1;
	}

	if (check_number_cube(grid, columns, pos1, pos2, fp))
	{
		return 0;
	}
	else
	{
		printf("\nUnsolvable Puzzle.\n");
		return 1;
	}
}

/**************** IsValidCube() ****************/
bool IsValidCube(int grid[6][4][4], int columns[3][16][4], struct position pos1[6][4][4], struct position pos2[6][4][4]) 
{

	// check can in box
	for (int b = 0; b < 6; b++)
	{
		for (int i = 0; i < 4; i++) 
		{
			for (int j = 0; j < 4; j++)
			{
				if (grid[b][i][j] == 0)
                        	{
					// do nothing
                        	}
                        	/* check for neg numbers */
                        	else if (grid[b][i][j] < 0)
                        	{
                                	fprintf(stderr, "Invalid Puzzle: cube cannot have negative num\n");
                                	return false;
                        	}
                        	/* check for numbers in range */
                        	else if (grid[b][i][j] > 16)
                        	{
                                	fprintf(stderr, "Invalid Puzzle: grid num must be in range 1-16\n");
                                	return false;
                        	}
                        	/* check no repeat number in row/col/square */
				else if (!can_in_box_cube(grid[b][i][j], i, j, b, grid))
				{
					fprintf(stderr, "Invalid Puzzle: grid cannot have repeated num in row/col/square\n");
					return false;
				}
			}
		
		}
	
	}

	save_columns(grid, columns, pos1, pos2);
	//print_columns(columns);
	//print_pos(pos1, pos2);
	return true;

	// check can in col
	for (int b = 0; b < 3; b++)
	{
		for (int j = 0; j < 4; j++) 
		{
			for (int i = 0; i < 16; i++)
			{
				for (int i1 = i + 1; i1 < 16; i1++)
				{
					if (columns[b][i][j] != 0 && columns[b][i][j] == columns[b][i1][j]) 
					{
						fprintf(stderr, "in axis %d col %d repeated num %d in row %d, with row %d\n", 
								b, j, columns[b][i][j], i, i1);
						return false;
					}
				}
			}
		
		}
	}

	return true;
}

/**************** print_columns() ****************/
void print_columns(int columns[3][16][4])
{
	for (int b = 0; b < 3; b++)
	{
		printf("axis %d\n", b);
		for (int i = 0; i < 16; i++)
		{
			for (int j = 0; j < 4; j++) 
			{
				printf("%2d ", columns[b][i][j]);
			}
			printf("\n");
		}
	}
}

/**************** print_pos() ****************/
void print_pos(struct position pos1[6][4][4], struct position pos2[6][4][4]) 
{
	for (int b = 0; b < 6; b++)
	{
		for (int i = 0; i < 4; i++) 
		{
			for (int j = 0; j < 4; j++)
			{
				printf("%d,%d,%d->%d,%d,%d, %d,%d,%d\n",b,i,j,pos1[b][i][j].axis,
					       pos1[b][i][j].row, pos1[b][i][j].col, pos2[b][i][j].axis,
					       pos2[b][i][j].row, pos2[b][i][j].col);
			}
		}
	}
}

/**************** save_columns() ****************/
void save_columns(int grid[6][4][4], int columns[3][16][4], struct position pos1[6][4][4], struct position pos2[6][4][4]) 
{
	// create column 0
	copy_box(0, 0, 0, grid, columns, pos1);
	copy_box(2, 0, 1, grid, columns, pos1);
	copy_box(4, 0, 2, grid, columns, pos1);
	rotate_box_clockwise_and_copy(5, 0, 3, grid, columns, pos1);

	// create column 1
	rotate_box_clockwise_and_copy(1, 1, 0, grid, columns, pos1);
	rotate_box_clockwise_and_copy(2, 1, 1, grid, columns, pos2);
	rotate_box_clockwise_and_copy(3, 1, 2, grid, columns, pos1);
	copy_box(5, 1, 3, grid, columns, pos2);

	// create column 2
	rotate_box_counter_clockwise_twice_and_copy(3, 2, 0, grid, columns, pos2);
	rotate_box_counter_clockwise_and_copy(0, 2, 1, grid, columns, pos2);
	copy_box(1, 2, 2, grid, columns, pos2);
	rotate_box_clockwise_and_copy(4, 2, 3, grid, columns, pos2);
}


/**************** find_empty_grid_cube() ****************/
struct position find_empty_grid_cube(int grid[6][4][4])
{
	struct position sg = {-1, -1, -1};
	for (int b = 0; b < 6; b++)
	{
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				if (grid[b][i][j] == 0) {
					struct position sg1 = {b,i,j};
					return sg1;
				}
			
			}
		}
	}
	return sg;
}

/**************** can_in_position() ****************/
bool can_in_position(int num, int box, int row, int col, int grid[6][4][4], int columns[3][16][4], 
		struct position pos1[6][4][4], struct position pos2[6][4][4])
{
	if (!can_in_box_cube(num, row, col, box, grid)) 
	{ 
		return false;
	}

	struct position p1 = pos1[box][row][col];
	if (!can_in_col_cube(num, p1.axis, p1.col, columns)) 
	{ 
		return false;
	}

	struct position p2 = pos2[box][row][col];
	if (!can_in_col_cube(num, p2.axis, p2.col, columns)) 
	{ 
		return false;
	}
	
	return true;
}

/**************** assign_num_position() ****************/
void assign_num_position(int num, int box, int row, int col, int grid[6][4][4], int columns[3][16][4], 
                struct position pos1[6][4][4], struct position pos2[6][4][4])
{       
        struct position p1 = pos1[box][row][col];
        struct position p2 = pos2[box][row][col];

	grid[box][row][col] = num;
	columns[p1.axis][p1.row][p1.col] = num;
	columns[p2.axis][p2.row][p2.col] = num;
	//printf("assign %d %d %d, %d\n", box, row, col, num);
        
}

/**************** check_number_cube() ****************/
bool check_number_cube(int grid[6][4][4], int columns[3][16][4], struct position pos1[6][4][4], struct position pos2[6][4][4], FILE *fp)
{
	/* advances to next empty slot */
	struct position sg = find_empty_grid_cube(grid);
	if (sg.col == -1)
	{
		/* there are no more empty slots; thus, puzzle has been completed */
		return true;
	}

	int box = sg.axis;
	int col = sg.col;
	int row = sg.row;

	/* try each number 1-16 */
	for (int num = 1; num < 17; num++)
	{
		if (can_in_position(num, box, row, col, grid, columns, pos1, pos2))
		{
			assign_num_position(num, box, row, col, grid, columns, pos1, pos2);

			//fprintf(fp, "%2d %2d %2d %2d\n", num, box, row, col); //FOR GUI. DO NOT DELETE

			/* continue recursive check */
			if (check_number_cube(grid, columns, pos1, pos2, fp))
			{
				return true;
			}

			/* this attempted number failed; set to 0 and try with next number */
			assign_num_position(0, box, row, col, grid, columns, pos1, pos2);
			//fprintf(fp, "%2d %2d %2d %2d\n", 0, box, row, col); //FOR GUI. DO NOT DELETE
		}
	}

	/* unable to solve puzzle */
	return false;
}

/**************** load_cubepuzzle () ****************/
/*
 * read the cube puzzle from stdin
 */
bool load_cube(int cube[6][4][4], FILE *fp)
{
	int face = 0;
	int row = 0;
	char *line;
	while ((line = freadlinep(fp)) != NULL) {
		if (row >= 16) {
			// out of bounds
			free(line);
			break;
		} else if (row > 3 && row < 8) {
			// start in left most face
			face = 1;
		} else if (row >= 8 && row < 12) {
			// bottom face
			face = 4;
		} else if (row >= 12 && row <= 15){
			// outside face
			face = 5;
		}

		if (strcmp(line, "") == 0) {
			/* exits on newline */
			free(line);
			fprintf(stderr, "Error: provided invalid input '\\n' in cube\n");
			return false;
		}

		int col = 0;
		char *numstr;

		/* get the first number */
		numstr = strtok(line, " ");

		/* loop through other numbers in line */
		while (numstr != NULL)
		{
			if ((face == 0 || face == 4 || face == 5) && col >= 4) {
				free(line);
				fprintf(stderr, "Error: puzzle from stdin exceeds bounds of puzzle to solve.\n");
				fclose(fp);
				return false;
			} 
			// move to next face
			if (col > 3 && col < 8) {
				face = 2;
			} else if (col >= 8 && col < 12) {
				face = 3;
			} else if (col > 12) {
				free(line);
				fprintf(stderr, "Error: puzzle from stdin exceeds bounds of puzzle to solve.\n");
				fclose(fp);
				return false;
			} 

			/* convert numstr to int */
			int num;
			if (sscanf(numstr, "%d", &num) == 0) {
				// must be a 16x16
				// convert hexadecimal char to digit
				if (strcmp(numstr, "A") == 0) {
					num = 10;
				} else if (strcmp(numstr, "B") == 0) {
					num = 11;
				} else if (strcmp(numstr, "C") == 0) {
					num = 12;
				} else if (strcmp(numstr, "D") == 0) {
					num = 13;
				} else if (strcmp(numstr, "E") == 0) {
					num = 14;
				} else if (strcmp(numstr, "F") == 0) {
					num = 15;
				} else if (strcmp(numstr, "G") == 0) {
					num = 16;
				} else {
					/* some other bad input */
					free(line);
					fprintf(stderr, "Error: provided invalid input '%s' in puzzle\n", numstr);
					fclose(fp);
					return false;
				}
			}

			/* add to sudoku grid */
			cube[face][(row % 4)][(col % 4)] = num;

			/* get next number */
			numstr = strtok(NULL, " ");
			col++;
		}
		free(line);
		row++;
	}
	return true;
}

/**************** load_cube_demo() ****************/
void load_cube_demo(int grid[6][4][4])
{
	grid[0][1][1] = 3;
        grid[0][1][2] = 6;
        grid[0][1][3] = 13;
        grid[0][2][2] = 10;
        grid[0][3][1] = 8;
        grid[0][3][2] = 1;
        grid[0][3][3] = 14;

        grid[1][1][0] = 15;
        grid[1][1][1] = 4;
        grid[1][1][2] = 11;
        grid[1][1][3] = 7;
        grid[1][2][0] = 2;
        grid[1][2][2] = 14;
        grid[1][2][3] = 5;
        grid[1][3][1] = 16;

        grid[2][0][0] = 10;
        grid[2][0][1] = 9;
        grid[2][1][2] = 14;
        grid[2][2][2] = 7;

        grid[3][2][0] = 13;
        grid[3][3][0] = 15;
        grid[3][3][2] = 12;
        grid[3][2][3] = 8;

        grid[4][0][0] = 16;
        grid[4][2][0] = 11;
        grid[4][0][2] = 2;
        grid[4][1][2] = 5;
        grid[4][3][1] = 12;

        grid[5][0][1] = 4;
        grid[5][1][0] = 9;
        grid[5][2][0] = 11;
        grid[5][1][2] = 3;
        grid[5][2][2] = 16;
        grid[5][2][3] = 5;
        grid[5][3][3] = 8;
}
