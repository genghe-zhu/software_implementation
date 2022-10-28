/* 
 * common.c - structs and functions common to both creator and solver modules
 * included in common library
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

/**************** initilize_empty () ****************/
// function to create an empty sudoku puzzle
void initialize_empty(int numRow, int numCol, int grid[numRow][numCol])
{
	// loop through every row
	for (int row = 0; row < numRow; row++)
	{
		// loop through every column
		for (int col = 0; col < numCol; col++)
		{
			grid[row][col] = 0; // insert a zero for an empty grid
		}
	}
}

/**************** print_grid () ****************/
// function to print a sudoku puzzle grid
void print_grid(int numRow, int numCol, int grid[numRow][numCol])
{
	// loop through every row
	for (int row = 0; row < numRow; row++)
	{
		// loop through every column
		for (int col = 0; col < numCol; col++)
		{
			if (numRow > 10)
				if (grid[row][col] > 9) {
					char c = grid[row][col] + 55;
					printf("%c ", c);
				} else {
					printf("%d ", grid[row][col]);
				}
			else
				printf("%d ", grid[row][col]);
		}
		printf("\n");
	}
}

/**************** can_in_row () ****************/
// function to check if a number can be placed in that row
bool can_in_row(int num, int row, int numRow, int numCol, int grid[numRow][numCol])
{
	// check if the num is in row
	for (int i = 0; i < numRow; i++)
	{
		// if the number is equal to anything already present in the row
		if (grid[row][i] == num)
		{
			return false; // can't put the number there
		}
	}
	return true; // otherwise we can put the number there
}

/**************** can_in_col () ****************/
// function to check if a number can be placed in that column
bool can_in_col(int num, int col, int numRow, int numCol, int grid[numRow][numCol])
{
	// check if the num is in col
	for (int i = 0; i < numCol; i++)
	{
		// if the number is equal to anything already present in the row
		if (grid[i][col] == num)
		{
			return false; // can't put the number there
		}
	}
	return true; // otherwise we can put the number there
}

/**************** can_in_box () ****************/
// function to check if a number can be placed in that box
bool can_in_box(int num, int row, int col, int numRow, int numCol, int grid[numRow][numCol])
{

        /* check box around num */
        int box_x_size = 0;
        int box_y_size = 0;
	
        if (numRow != 6) { // checks if it's a square sudoku puzzle
                box_x_size = (int)sqrt((double)numRow); // calculates size
                box_y_size = box_x_size; // 
        } else if (numRow == 6) { // not square
                box_x_size = 2; // x and y sizes assigned differently
                box_y_size = 3;
        }

	// uses floor division to orientate around each box and determine how large each box is
	// loop through that box's rows
        for (int i = floor(row / box_x_size) * box_x_size; i < floor(row / box_x_size) * box_x_size + box_x_size; i++)
        {
		// loop through that box's columns
                for (int j = floor(col / box_y_size) * box_y_size; j < floor(col / box_y_size) * box_y_size + box_y_size; j++)
                {
			// check if the number is already inside the box
                        if (grid[i][j] == num)
                        {
                                if (i != row && j != col)
                                {
                                        return false; // can't put the number here
                                }
                        }
                }
        }

	return true; // otherwise, can put the number here
}

/**************** UNIT TESTING ****************/
#ifdef UNIT_TEST
#include "unittest.h"
int test_print_grid(int grid[9][9])
{
	START_TEST_CASE("print_grid");
	print_grid(grid);

	END_TEST_CASE;
	return TEST_RESULT;
}
int test_can_in_row(int grid[9][9])
{
	START_TEST_CASE("can_in_row");

	int row = 3;
	EXPECT(can_in_row(4, row, grid) == true);
	EXPECT(can_in_row(2, row, grid) == false);

	END_TEST_CASE;
	return TEST_RESULT;
}
int test_can_in_col(int grid[9][9])
{
	START_TEST_CASE("can_in_col");

	int col = 3;
	EXPECT(can_in_col(4, col, grid) == true);
	EXPECT(can_in_col(5, col, grid) == false);

	END_TEST_CASE;
	return TEST_RESULT;
}
int test_can_in_box(int grid[9][9])
{
	START_TEST_CASE("can_in_box");

	int row = 3;
	int col = 3;
	EXPECT(can_in_box(4, row, col, grid) == true);
	EXPECT(can_in_box(2, row, col, grid) == false);

	END_TEST_CASE;
	return TEST_RESULT;
}
int main(int argc, char *argv[])
{
	int failed = 0;
	int grid[9][9] = {{3, 1, 6, 5, 7, 8, 4, 9, 2},
					  {5, 2, 9, 1, 3, 4, 7, 6, 8},
					  {4, 8, 7, 6, 2, 9, 5, 3, 1},
					  {2, 6, 3, 0, 1, 5, 9, 8, 7},
					  {9, 7, 4, 8, 6, 0, 1, 2, 5},
					  {8, 5, 1, 7, 9, 2, 6, 4, 3},
					  {1, 3, 8, 0, 4, 7, 2, 0, 6},
					  {6, 9, 2, 3, 5, 1, 8, 7, 4},
					  {7, 4, 5, 0, 8, 6, 3, 1, 0}};

	failed += test_print_grid(grid);
	failed += test_can_in_row(grid);
	failed += test_can_in_col(grid);
	failed += test_can_in_box(grid);

	if (failed)
	{
		printf("FAIL %d test cases\n", failed);
		return failed;
	}
	else
	{
		printf("PASS all test cases\n");
		return 0;
	}
}
#endif //UNIT_TEST
