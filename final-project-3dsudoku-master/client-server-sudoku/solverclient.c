/* 
 * solverclient.c
 *
 * Makes a connection to the given host/port and requests a sudoku 
 * puzzle from that server.
 * 
 * usage: solverclient hostname port
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> // read, write, close
#include <string.h> // memcpy, memset
#include <netdb.h>  // socket-related structures
#include "../common/common.h"
#include "../solver/solver.h"
#include "../common/cube.h"

/**************** file-local constants ****************/
#define BUFSIZE 250 // read buffer size

/**************** function prototypes ****************/
static void parse_args(const int argc, char *argv[], char **program, char **hostname, int *port);
static int connect_to(const char *program, const char *hostname, const int port);
bool load_puzzle_fromserver(int size, int sudoku[size][size], int *row, char line[BUFSIZE]);
bool load_cube_fromserver(int cube[6][4][4], int *face, int *row, char line[BUFSIZE]);

/**************** main() ****************/
int main(const int argc, char *argv[])
{
	char *program;	 // this program's name
	char *hostname; // server hostname
	int port;		 // server port

	// parse arguments - exit on error
	parse_args(argc, argv, &program, &hostname, &port);

	// open connection - exit on error
	int comm_sock = connect_to(program, hostname, port);

	int size = -1;
	printf("Enter the size of puzzle: ");
	if (scanf("%d", &size) != 1)
	{
		fprintf(stderr, "Error: reading in size of puzzle\n");
		exit(16);
	}
	if ((size != 3 ) && (size != 4) && (size != 6) && (size != 9) && (size != 16))
	{
		fprintf(stderr, "Error, input size '%d' must be either 3, 4, 6, 9, or 16\n", size);
		exit(5);
	}

#ifdef DEBUG_FLAG
	fprintf(stdout, "size: %d\n", size);
#endif

	// write type and size to server
	char buf[BUFSIZE];		 // a buffer for reading data from stdin
	int bytes_read;			 // #bytes read from socket
	memset(buf, 0, BUFSIZE); // clear up the buffer
	sprintf(buf, "%d", size);
	if (size != 3) {
		printf("Requesting puzzle of size %d from server...\n", size);
	} else {
		printf("Requesting cube from server...\n");
		size = 22;	// cube specific
	}
	
	int res;
	if ((res = write(comm_sock, buf, strlen(buf))) < 0) {
		fprintf(stderr, "Error: writing on stream socket\n");
		exit(6);
	}

	memset(buf, 0, BUFSIZE); // clear up the buffer

	/* initialize blank puzzle */
	int sudoku[size][size];
	initialize_empty(size, size, sudoku);

	int cube[6][4][4];
	initialize_empty_cube(cube);

	int row = 0;
	int face = 0;
	do
	{
		// read content from socket
		if ((bytes_read = read(comm_sock, buf, BUFSIZE - 1)) < 0)
		{
			fprintf(stderr, "Error: reading from server\n");
			exit(5);
		}
		else
		{
#ifdef DEBUG_FLAG
			printf("received row %d: %s\n\n", row, buf);
#endif
			if (size != 22) {
				if (!load_puzzle_fromserver(size, sudoku, &row, buf) && row < size)
				{
					/* bad character provided by server */
					exit(21);
				}
			} 
			else {
				if (!load_cube_fromserver(cube, &face, &row, buf))
				{
					/* bad character provided by server */
					exit(21);
				}
			}
		}
		memset(buf, 0, BUFSIZE); // clear up the buffer
	} while (bytes_read > 0 && row < size);

	if (size != 22) {
		printf("\nReceived Puzzle: \n\n");
		print_grid(size, size, sudoku);
		solve(size, size, sudoku, stdin);
	} else {
		printf("\nReceived Cube: \n\n");
		print_grid_cube(cube);
		res = solve_cube(cube, stdin);
		if (res == 0) {
			printf("\nSolved Cube:\n\n");
			print_grid_cube(cube);
		}
	}

	close(comm_sock);

	return 0;
}

static void parse_args(const int argc, char *argv[], char **program, char **hostname, int *port)
{
	// check arguments
	*program = argv[0];
	if (argc != 3)
	{
		fprintf(stderr, "usage:ech %s hostname port\n", *program);
		exit(1);
	}
	else
	{
		// TODO: more robust param checker
		*hostname = argv[1];
		*port = atoi(argv[2]);
	}
}

static int connect_to(const char *program, const char *hostname, const int port)
{
	// create socket
	int comm_sock = socket(AF_INET, SOCK_STREAM, 0);
	if (comm_sock < 0)
	{
		fprintf(stderr, "Error: opening socket\n");
		exit(2);
	}

	// initialize the fields of the server address
	struct sockaddr_in creator_server; // address of the server
	creator_server.sin_family = AF_INET;
	creator_server.sin_port = htons(port);

	// look up the hostname specified on command line
	struct hostent *hostp = gethostbyname(hostname); // server hostname
	if (hostp == NULL)
	{
		fprintf(stderr, "%s: unknown host '%s'\n", program, hostname);
		exit(3);
	}
	memcpy(&creator_server.sin_addr, hostp->h_addr_list[0], hostp->h_length);

	// connect the socket to that server
	if (connect(comm_sock, (struct sockaddr *)&creator_server, sizeof(creator_server)) < 0)
	{
		fprintf(stderr, "Error: connecting stream socket\n");
		exit(4);
	}

	printf("Connected!\n");

	return comm_sock;
}

bool load_puzzle_fromserver(int size, int sudoku[size][size], int *row, char line[BUFSIZE])
{
	if ((*row) >= size)
		return false;

	int col = 0;
	char *numstr;

	/* get the first number */
	numstr = strtok(line, " ");

	/* loop through other numbers in line */
	while (numstr != NULL)
	{
		if (col >= size)
		{
			break;
		}

		/* convert numstr to int */
		int num;
		if (sscanf(numstr, "%d", &num) == 0)
		{
			/* input E to signal end of row */
			break;
		}

		/* add to sudoku grid */
		sudoku[*row][col] = num;

		/* get next number */
		numstr = strtok(NULL, " ");
		col++;
	}

	// increment row
	(*row)++;
	return true;
}

bool load_cube_fromserver(int cube[6][4][4], int *face, int *row, char line[BUFSIZE])
{
	int col = 0;
	char *numstr;

	/* get the first number */
	numstr = strtok(line, " ");

	/* loop through other numbers in line */
	while (numstr != NULL)
	{
		if (col >= 4)
		{
			break;
		}

		/* convert numstr to int */
		int num;
		if (sscanf(numstr, "%d", &num) == 0)
		{
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
			} 
		}

		/* add to sudoku grid */
		cube[*face][*row][col] = num;

		/* get next number */
		numstr = strtok(NULL, " ");
		col++;
	}

	// increment row
	(*row)++;
	if ((*row) == 4) {
		/* go to next face */
		(*face)++;
		/* set row to top of new face */
		(*row) = 0;
	}
	return true;
}
