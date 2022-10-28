/* 
 * solver.c - solver module for Sudoku game
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
#include "../common/common.h"
#include "../common/file.h"
#include "solver.h"

/**************** file-local global variables ****************/
/* none */

/**************** local types ****************/

/**************** global types ****************/

/**************** global functions ****************/
/* that is, visible outside this file */

/**************** local functions ****************/
/* not visible outside this file */
/**************** solve() ****************/
int solve(int numRow, int numCol, int grid[numRow][numCol], FILE *fp)
{
	fprintf(fp, "solve\n");
	/* check if the provided puzzle is valid */
	if (!IsValidPuzzle(numRow, numCol, grid))
	{
		return 1;
	}
	/* starts recursive solution */
	if (check_number(numRow, numCol, grid, fp))
	{
		printf("\nSolved Puzzle:\n\n");
		print_grid(numRow, numCol, grid);
		return 0;
	}
	else
	{
		printf("\nUnsolvable Puzzle.\n");
		return 1;
	}
}

/**************** IsValidPuzzle() ****************/
bool IsValidPuzzle(int numRow, int numCol, int grid[numRow][numCol])
{
	// sudoku grid cannot have number greater than number of rows
	int maxNum = numRow;

	/* count number of empty spaces */
	int emptySpaces = 0;

	/* loop through grid */
	for (int i = 0; i < numRow; i++)
	{
		for (int j = 0; j < numCol; j++)
		{
			if (grid[i][j] == 0)
			{
				emptySpaces++;
			}
			/* check for neg numbers */
			else if (grid[i][j] < 0)
			{
				fprintf(stderr, "Invalid Puzzle: grid cannot have negative num\n");
				return false;
			}
			/* check for numbers in range */
			else if (grid[i][j] > maxNum)
			{
				fprintf(stderr, "Invalid Puzzle: grid num must be in range 1-%d\n", maxNum);
				return false;
			}
			/* check no repeat number in row/col/square */
			else if (repeat_exists(i, j, numRow, numCol, grid))
			{
				fprintf(stderr, "Invalid Puzzle: grid cannot have repeated num in row/col/square\n");
				return false;
			}
		}
	}

	return true;
}

/**************** repeat_exists() ****************/
bool repeat_exists(int row, int col, int numRow, int numCol, int grid[numRow][numCol])
{
	int num = grid[row][col];

	/* check if num is 0 */
	if (num == 0)
	{
		return false;
	}

	/* check no repeats in col */
	for (int i = row + 1; i < numRow; i++)
	{
		if (grid[i][col] == num)
		{
			fprintf(stderr, "in row repeated num %d in row %d, col %d with row %d, col %d\n", num, i, col, row, col);
			return true;
		}
	}

	/* check no repeats in row */
	for (int j = col + 1; j < numCol; j++)
	{
		if (grid[row][j] == num)
		{
			fprintf(stderr, "in col repeated num %d in row %d, col %d with row %d, col %d\n", num, row, j, row, col);
			return true;
		}
	}

	/* check box around num */
	if (!can_in_box(num, row, col, numRow, numCol, grid))
	{
		fprintf(stderr, "in box repeated num %d in row %d, col %d\n", num, row, col);
		return true;
	}

	return false;
}

/**************** find_empty_grid () ****************/
struct singleGrid find_empty_grid(int numRow, int numCol, int grid[numRow][numCol])
{
	struct singleGrid sg = {-1, -1};
	for (int i = 0; i < numRow; i++)
	{
		for (int j = 0; j < numCol; j++)
		{
			if (grid[i][j] == 0)
			{
				struct singleGrid sg1 = {i, j};
				return sg1;
			}
		}
	}
	return sg;
}

/**************** check_number () ****************/
/*
 * checks number recursively using backtracking
 */
bool check_number(int numRow, int numCol, int grid[numRow][numCol], FILE *fp)
{
	/* advances to next empty slot */
	struct singleGrid sg = find_empty_grid(numRow, numCol, grid);
	if (sg.col == -1)
	{
		/* there are no more empty slots; thus, puzzle has been completed */
		return true;
	}

	int col = sg.col;
	int row = sg.row;

	/* try each number 1-9 */
	for (int num = 1; num < numRow + 1; num++)
	{
		if (can_in_row(num, row, numRow, numCol, grid) && can_in_col(num, col, numRow, numCol, grid) && can_in_box(num, row, col, numRow, numCol, grid))
		{
			grid[row][col] = num;

			fprintf(fp, "%2d %2d %2d\n", num, row, col); //FOR GUI. DO NOT DELETE

			/* continue recursive check */
			if (check_number(numRow, numCol, grid, fp))
			{
				return true;
			}

			/* this attempted number failed; set to 0 and try with next number */
			grid[row][col] = 0;
			int zero = 0;
			fprintf(fp, "%2d %2d %2d\n", zero, row, col); //FOR GUI. DO NOT DELETE
		}
	}

	/* unable to solve puzzle */
	return false;
}

/**************** load_puzzle () ****************/
/*
 * read the puzzle from stdin
 */
bool load_puzzle(int numRow, int numCol, int sudoku[numRow][numCol], FILE *fp)
{
	int row = 0;

	char *line;
	while ((line = freadlinep(fp)) != NULL)
	{
		if (row >= numRow)
		{
			free(line);
			break;
		}
		else if (strcmp(line, "") == 0)
		{
			/* exits on newline */
			free(line);
			fprintf(stderr, "Error: provided invalid input '\\n' in puzzle\n");
			return false;
		}

		int col = 0;
		char *numstr;

		/* get the first number */
		numstr = strtok(line, " ");

		/* loop through other numbers in line */
		while (numstr != NULL)
		{
			if (col >= numCol)
			{
				free(line);
				fprintf(stderr, "Error: puzzle from stdin exceeds bounds of puzzle to solve.\n");
				fclose(fp);
				return false;
			}

			/* convert numstr to int */
			int num;
			if (sscanf(numstr, "%d", &num) == 0)
			{
				if (numRow < 16)
				{
					// non 16x16 grids should never have a character
					/* bad input */
					free(line);
					fprintf(stderr, "Error: provided invalid input '%s' in puzzle\n", numstr);
					fclose(fp);
					return false;
				}
				// otherwise must be a 16x16
				// convert hexadecimal char to digit
				if (strcmp(numstr, "A") == 0)
				{
					num = 10;
				}
				else if (strcmp(numstr, "B") == 0)
				{
					num = 11;
				}
				else if (strcmp(numstr, "C") == 0)
				{
					num = 12;
				}
				else if (strcmp(numstr, "D") == 0)
				{
					num = 13;
				}
				else if (strcmp(numstr, "E") == 0)
				{
					num = 14;
				}
				else if (strcmp(numstr, "F") == 0)
				{
					num = 15;
				}
				else if (strcmp(numstr, "G") == 0)
				{
					num = 16;
				}
				else
				{
					/* some other bad input */
					free(line);
					fprintf(stderr, "Error: provided invalid input '%s' in puzzle\n", numstr);
					fclose(fp);
					return false;
				}
			}

			/* add num to sudoku grid */
			sudoku[row][col] = num;

			/* get next number */
			numstr = strtok(NULL, " ");
			/* move to next col */
			col++;
		}
		/* free current line and move to next row */
		free(line);
		row++;
	}
	/* if done reading from stdin */
	if (row < (numRow - 1))
	{
		fprintf(stderr, "Error: puzzle from stdin has smaller grid size than puzzle to solve.\n");
		fclose(fp);
		return false;
	}

	fclose(fp);
	return true;
}

/**************** UNIT TESTING ****************/
#ifdef UNIT_TEST
#include "../common/unittest.h"
int test_IsValidPuzzle(int sudoku[9][9])
{
	START_TEST_CASE("IsValidPuzzle");

	// pass valid puzzle
	EXPECT(IsValidPuzzle(0, 9, 9, sudoku) == true);

	// has negative number at (5, 7)
	int bad1[9][9] = {{3, 1, 6, 5, 7, 8, 4, 9, 2},
							{5, 2, 9, 1, 3, 4, 7, 6, 8},
							{4, 8, 7, 6, 2, 9, 5, 3, 1},
							{2, 6, 3, 0, 1, 5, 9, 8, 7},
							{9, 7, 4, 8, 6, 0, 1, 2, 5},
							{8, 5, 1, 7, 9, 2, 6, -4, 3},
							{1, 3, 8, 0, 4, 7, 2, 0, 6},
							{6, 9, 2, 3, 5, 1, 8, 7, 4},
							{7, 4, 5, 0, 8, 6, 3, 1, 0}};
	EXPECT(IsValidPuzzle(0, 9, 9, bad1) == false);

	// has number > 9 at (8, 4)
	int bad2[9][9] = {{3, 1, 6, 5, 7, 8, 4, 9, 2},
							{5, 2, 9, 1, 3, 4, 7, 6, 8},
							{4, 8, 7, 6, 2, 9, 5, 3, 1},
							{2, 6, 3, 0, 1, 5, 9, 8, 7},
							{9, 7, 4, 8, 6, 0, 1, 2, 5},
							{8, 5, 1, 7, 9, 2, 6, 4, 3},
							{1, 3, 8, 0, 4, 7, 2, 0, 6},
							{6, 9, 2, 3, 5, 1, 8, 7, 4},
							{7, 4, 5, 0, 18, 6, 3, 1, 0}};
	EXPECT(IsValidPuzzle(0, 9, 9, bad2) == false);

	// has repeat in row 8
	int bad3[9][9] = {{3, 1, 6, 5, 7, 8, 4, 9, 2},
							{5, 2, 9, 1, 3, 4, 7, 6, 8},
							{4, 8, 7, 6, 2, 9, 5, 3, 1},
							{2, 6, 3, 0, 1, 5, 9, 8, 7},
							{9, 7, 4, 8, 6, 0, 1, 2, 5},
							{8, 5, 1, 7, 9, 2, 6, 4, 3},
							{1, 3, 8, 0, 4, 7, 2, 0, 6},
							{6, 9, 2, 3, 5, 1, 8, 7, 4},
							{7, 4, 5, 0, 6, 6, 3, 1, 0}};
	EXPECT(IsValidPuzzle(0, 9, 9, bad3) == false);

	END_TEST_CASE;
	return TEST_RESULT;
}
int main(const int argc, char *argv[])
{
	int sudoku[9][9] = {{0, 0, 0, 0, 0, 0, 0, 0, 0},
							  {0, 0, 0, 0, 0, 0, 0, 0, 0},
							  {0, 0, 0, 0, 0, 0, 0, 0, 0},
							  {0, 0, 0, 0, 0, 0, 0, 0, 0},
							  {0, 0, 0, 0, 0, 0, 0, 0, 0},
							  {0, 0, 0, 0, 0, 0, 0, 0, 0},
							  {0, 0, 0, 0, 0, 0, 0, 0, 0},
							  {0, 0, 0, 0, 0, 0, 0, 0, 0},
							  {0, 0, 0, 0, 0, 0, 0, 0, 0}};

	// either stdin or pipe a valid puzzle from ../testpuzzles
	load_puzzle(9, 9, sudoku);
	print_grid(9, 9, sudoku);

	int failed = 0;

	failed += test_IsValidPuzzle(sudoku);

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
#endif // UNIT_TEST
