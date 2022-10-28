/* 
 * indextest.c - CS50 'TSE' indextest module
 *
 * see indextest.h for more information.
 *
 * CS50 
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "../common/index.h"
#include "../libcs50/file.h"
#include "../libcs50/hashtable.h"
#include "../libcs50/memory.h"
#include <unistd.h>
#include <sys/stat.h>

/**************** file-local global variables ****************/
/* none */

/**************** local types ****************/

/**************** global types ****************/

/**************** global functions ****************/
/* that is, visible outside this file */

/**************** local functions ****************/
/* not visible outside this file */
void index_build(char *pageDirectory, hashtable_t *index);
	
/**************** main ****************/
int main(const int argc, char *argv[])
{
	char* program = argv[0];  // program name

	// check input arguments: # of arguments
	if (argc != 3) {
		fprintf(stderr, "usage: %s oldIndexFIlename newIndexFilename\n", program);
		return 1; 
	}

	// check input arguments: indexFilename validity
	char* oldIndexFilename = argv[1];
	FILE *fp = fopen(oldIndexFilename, "r");
        if (fp == NULL) {
		fprintf(stderr,"oldIndexFile %s is not readable", oldIndexFilename);
                return 3;
        }
	int lines = lines_in_file(fp);
	fclose(fp);


	// check input arguments: indexFilename validity
	char* newIndexFilename = argv[2];
	fp = fopen(newIndexFilename, "w");
        if (fp == NULL) {
		fprintf(stderr,"newIndexFile %s is not writable", newIndexFilename);
                return 3;
        }
	fclose(fp);

	hashtable_t *index = hashtable_new(lines);

	index_load(oldIndexFilename, index);
	index_save(newIndexFilename, index);

	// clean up
	index_delete(index);
	return 0;
}
