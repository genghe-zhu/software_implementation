/* 
 * indexer.c - CS50 'TSE' indexer module
 *
 * see indexer.h for more information.
 *
 * CS50 
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "../common/index.h"
#include "../common/pagedir.h"
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
	
/**************** main ****************/
int main(const int argc, char *argv[])
{
	char* program = argv[0];  // program name

	// check input arguments: # of arguments
	if (argc != 3) {
		fprintf(stderr, "usage: %s pageDirectory indexFilename\n", program);
		return 1; 
	}

	// check if pageDirectory is a pathname for existing diretory
	char* pageDirectory = argv[1];
	if (!isCrawlerDirectory(pageDirectory)) {
		return 2;
	}

	// check input arguments: indexFilename validity
	char* indexFilename = argv[2];
	FILE *fp = fopen(indexFilename, "w");
        if (fp == NULL) {
		fprintf(stderr,"indexFile %s is not writable", indexFilename);
                return 3;
        }
	fclose(fp);

	hashtable_t *index = hashtable_new(900);

	index_build(pageDirectory, index);
	index_save(indexFilename, index);

	// clean up
	index_delete(index);
	return 0;
}
