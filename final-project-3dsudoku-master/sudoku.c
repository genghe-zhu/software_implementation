/* 
 * sudoku - 9x9 variant of Sudoku game
 * 
 * usage: ./sudoku create [3, 4, 6, 9, 16] or to create a random Sudoku puzzle with size cube, 4x4, 6x6, 9x9, 16x16 respectively
 *        ./sudoku solve [3, 4, 6, 9, 16] to solve a given Sudoku puzzle with size cube, 4x4, 6x6, 9x9, 16x16 respectively 
 * 
 * Authors: William Scott, Isabella Zenkl, Genghe Zhu, Rachael Williams
 * 
 * CS50 Summer 2020
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "common/common.h"
#include "common/cube.h"
#include "solver/solver.h"
#include "creator/creator.h"
#include "solver/solvecube.h"

/*********** global variables ***********/
bool IsFromServer = false; // needed to circumvent opening logfile when coming from server

/*********** function prototypes ***********/
int get_sudoku_size(char *ssize);
void run_creator(int size);
int run_solver(int size);

int main(const int argc, char *argv[])
{
	int returnValue = -1;

	char *program;
	if (argc < 3)
	{
		fprintf(stderr, "Invalid Usage: try ./sudoku create [3, 4, 6, 9, 16] or ./sudoku solve [3, 4, 6, 9, 16] \n");
		exit(1);
	}

	if (argc == 4 && (strcmp(argv[3], "server") == 0)) {
		IsFromServer = true;
	} else if (argc == 4 && (strcmp(argv[3], "server") != 0)) {
		fprintf(stderr, "Invalid Usage: try ./sudoku create [3, 4, 6, 9, 16] or ./sudoku solve [3, 4, 6, 9, 16] \n");
		exit(49);
	}

	program = argv[1];
	int size = get_sudoku_size(argv[2]);

	/* parse second command */
	if (strcmp(program, "create") == 0)
	{
		run_creator(size);
	}
	else if (strcmp(program, "solve") == 0)
	{
		returnValue = run_solver(size);
	}
	else
	{
		fprintf(stderr, "'%s' is invalid! try ./sudoku create or ./sudoku solve\n", program);
		exit(2);
	}

	return returnValue;
}

int get_sudoku_size(char *ssize)
{
	int size;
	sscanf(ssize, "%d", &size);
	if ((size != 3 ) && (size != 4) && (size != 6) && (size != 9) && (size != 16))
	{
		fprintf(stderr, "Error: input size '%d' must be either 3, 4, 6, 9, or 16\n", size);
		exit(5);
	}
	return size;
}

void run_creator(int size)
{
	FILE *fp = stdin;
	// open the logfile
	if (!IsFromServer) {
		fp = fopen("GUI/clogfile.txt", "w");
		if (fp == NULL)
		{
			fprintf(stderr, "could not open clogfile.txt\n");
			exit(10);
		}
	}

	/* 2D puzzle */
	if (size != 3) {
		int sudoku[size][size];
		initialize_empty(size, size, sudoku);

		create_sudoku(size, size, sudoku, fp);
		print_grid(size, size, sudoku);

	} else {
		/* 3D puzzle */
		int cube[6][4][4];
		
		create_cube(cube, fp);
	}
	fclose(fp);
}

int run_solver(int size)
{
	int res = -1;
	// open the logfile
	FILE *fp = stdin;
	if (!IsFromServer) {
		fp = fopen("GUI/slogfile.txt", "w");
		if (fp == NULL)
		{
			fprintf(stderr, "could not open logfile.txt\n");
			exit(10);
		}
	}

	/* 2D puzzle */
	if (size != 3) {
		int sudoku[size][size];
		initialize_empty(size, size, sudoku);

		// loads puzzle from stdin 
		if (!load_puzzle(size, size, sudoku, stdin))
		{
			// bad character in stdin 
			exit(3);
		}

		printf("\nProvided Puzzle: \n\n");
		print_grid(size, size, sudoku);

		res = solve(size, size, sudoku, fp);

	} else {
		/* 3D puzzle */
		int cube[6][4][4];
		initialize_empty_cube(cube);

		// loads puzzle from stdin 
		if (!load_cube(cube, stdin))
		{
			// bad character in stdin 
			exit(4);
		}
		printf("\nProvided Cube: \n\n");
		print_grid_cube(cube);

		res = solve_cube(cube, fp);
		if (res == 0) {
			printf("\nSolved Cube:\n\n");
			print_grid_cube(cube);
		}
	}

	fclose(fp);
	return res;
}
