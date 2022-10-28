/* 
 * word.c - CS50 'TSE' common---- module
 *
 * see word.h for more information.
 *
 * CS50 
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "word.h"

/**************** file-local global variables ****************/
/* none */

/**************** local types ****************/

/**************** global types ****************/

/**************** global functions ****************/
/* that is, visible outside this file */

/**************** local functions ****************/
/* not visible outside this file */

/**************** normalizeWord() **************/
// normalize word by turning all letters to lower case
void normalizeWord(char *word) 
{
	if (word == NULL) {
		return;
	}
	int i = 0;
	while ( word[i] ) {
		word[i] = tolower(word[i]);
		i++;
	}
}


