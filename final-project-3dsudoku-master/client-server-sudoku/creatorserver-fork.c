/* 
 * creatorserver-fork.c
 *
 * This program accepts connections forever in an infinite loop, sending 
 * sudoku puzzles to clients.
 *
 *
 * 
 * usage: ./creatorserver-fork and ctrl-C to exit. 
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>	  // bool type
#include <string.h>	  // memcpy, memset
#include <unistd.h>	  // read, write, close, fork
#include <arpa/inet.h> // socket-related calls
#include <signal.h>	  // wait() and waitpid(), signal()
#include "../common/common.h"
#include "../creator/creator.h"
#include "../solver/solver.h"
#include "../solver/solvecube.h"
#include "../common/cube.h"
#include "../common/file.h"

/**************** file-local constants ****************/
#define SERV_PORT 3000	 // creator_server port number
#define LISTEN_BACKLOG 5 // number of connections to keep waiting
#define BUFSIZE 250		 // read buffer size

/**************** function prototypes ****************/
static void connect_to(struct sockaddr_in creator_server, int *listener_sock);
static void send_sudoku(int solver_sock, int numRow, int numCol);
static void send_cube(int solver_sock);

/**************** main() ****************/
int main(const int argc, char *argv[])
{
	int listener_sock, solver_sock;
	struct sockaddr_in creator_server; // server address

	signal(SIGCHLD, SIG_IGN); // reap zombie processes automatically

	// check arguments
	char *program = argv[0];
	if (argc > 1)
	{
		fprintf(stderr, "usage: %s and ctrl-C to exit.\n", program);
		exit(100);
	}

	connect_to(creator_server, &listener_sock);

	// start accepting connections, and allow one connection at a time
	listen(listener_sock, LISTEN_BACKLOG);
	while (true)
	{
		// accept connection and receive communication socket (file descriptor = 0 since stdin)
		if ((solver_sock = accept(listener_sock, 0, 0)) == -1)
			perror("accept");
		else
		{
			// start a new process to handle the new client
			if (fork())
			{
				// parent process
				close(solver_sock);
			}
			else
			{
				// child process
				close(listener_sock);

				printf("Connection started\n\n");

				int size;

				// get size from client
				char buf[BUFSIZE];		 // a buffer for reading data from stdin
				int bytes_read;			 // #bytes read from socket
				memset(buf, 0, BUFSIZE); // clear up the buffer
				if ((bytes_read = read(solver_sock, buf, BUFSIZE - 1)) < 0)
				{
					fprintf(stderr, "Error: reading size from client\n");
					close(solver_sock);
					printf("Connection ended\n\n");
					exit(5);
				}
				else
				{
					if (sscanf(buf, "%d", &size) < 1)
					{
						fprintf(stderr, "Error: scanning size from client\n");
						close(solver_sock);
						printf("Connection ended\n\n");
						exit(10);
					}
				}
				
				if (size != 3)
				{
					printf("Requested 2D puzzle of size %d\n\n", size);
					send_sudoku(solver_sock, size, size);
				}	else {
					printf("Requested cube\n\n");
					send_cube(solver_sock);
				}

				close(solver_sock);

				printf("Connection ended\n\n");
				exit(0);
			}
		}
	}
	close(listener_sock);
}

/**************** connect_to() ****************/
static void connect_to(struct sockaddr_in creator_server, int *listener_sock)
{
	// create socket on which to write puzzle
	if ((*listener_sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
	{
		fprintf(stderr, "Error: opening socket stream");
		exit(1);
	}

	// initiate the fields of the server address
	creator_server.sin_family = AF_INET;
	creator_server.sin_addr.s_addr = htonl(INADDR_ANY);
	creator_server.sin_port = htons(SERV_PORT);

	// bind the socket to the given server address
	if (bind(*listener_sock, (struct sockaddr *)&creator_server, sizeof(creator_server)))
	{
		perror("binding socket name");
		exit(2);
	}
	printf("Listening at port %d\n", ntohs(creator_server.sin_port));
	printf("To find your MacOS IP address, ifconfig | grep 'inet '\n");
}

/**************** send_2Dsudoku() ****************/
static void send_sudoku(int solver_sock, int numRow, int numCol)
{
	// get command string for script
	char cmd[BUFSIZE] = ".././sudoku.sh create ";
	char sizestr[5];
	sprintf(sizestr, "%d", numRow);	
	strcat(cmd, sizestr);
	strcat(cmd, " server");

	// run script to generate solvable puzzle
	system(cmd);

	int sudoku[numRow][numCol];
	initialize_empty(numRow, numCol, sudoku);

	FILE *fp;
	if ((fp = fopen("puzzle.txt", "r")) == NULL) {
		fprintf(stderr, "Error: reading puzzle from script");
		exit(47);
	}

	load_puzzle(numRow, numCol, sudoku, fp);
	printf("\n");

	// numRow, numCol, grid
	printf("\nSending puzzle...\n");

	// write sudoku to solver_sock
	int row = 0;
	while (row < numRow)
	{
		char line[BUFSIZE];
		memset(line, 0, BUFSIZE); // clear up the buffer
		for (int col = 0; col < numCol; col++)
		{
			int num = sudoku[row][col];
			if (col == 0)
			{
				// resets line to int in first col
				sprintf(line, "%d", num);
			}
			else
			{
				char snum[5];
				// convert num to string [buf]
				sprintf(snum, " %d", num);
				strcat(line, snum);
			}
		}
		strcat(line, "Z"); // signals end of row
		int res;
		if ((res = write(solver_sock, line, strlen(line))) < 0)
		{
			fprintf(stderr, "writing on stream socket");
			exit(6);
		}

#ifdef DEBUG_FLAG
		printf("\nrow %d : %s sent\n", row + 1, line);
#endif
		row++;
		sleep(.5); // to stop writing extra bytes to buffer
	}
}

/**************** send_3Dsudoku() ****************/
static void send_cube(int solver_sock)
{
	// get command string for script
	char cmd[BUFSIZE] = ".././sudoku.sh create 3 server";
	// run script to generate solvable puzzle
	system(cmd);

	int cube[6][4][4];
	initialize_empty_cube(cube);

	FILE *fp;
	if ((fp = fopen("puzzle.txt", "r")) == NULL) {
		fprintf(stderr, "Error: reading cube from script");
		exit(47);
	}

	load_cube(cube, fp);
	printf("\n");

	printf("\nSending cube...\n");

	// write cube to solver_sock
	int face = 0;
	while (face < 6)
	{
		char line[BUFSIZE];
		memset(line, 0, BUFSIZE); // clear up the buffer
		for (int row = 0; row < 4; row++)
		{
			for (int col = 0; col < 4; col++)
			{
				int num = cube[face][row][col];
				if (col == 0)
				{
					if (num > 9) {
						char c = cube[face][row][col] + 55;
						sprintf(line, "%c", c);
					} else {
						// resets line to int in first col
						sprintf(line, "%d", num);
					}
				}
				else
				{
					char snum[5];
					if (num > 9) {
						char c = cube[face][row][col] + 55;
						sprintf(snum, " %c", c);
					} else {
						// convert num to string [buf]
						sprintf(snum, " %d", num);
					}
					strcat(line, snum);
				}
			}
			int res;
			if ((res = write(solver_sock, line, strlen(line))) < 0)
			{
				fprintf(stderr, "writing on stream socket");
				exit(6);
			}
			#ifdef DEBUG_FLAG
				printf("\nface %d row %d : %s sent\n", face, row, line);
			#endif
			sleep(.5); // to stop writing extra bytes to buffer
		}
		face++;
	}
}