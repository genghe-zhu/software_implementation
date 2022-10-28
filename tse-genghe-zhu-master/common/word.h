/* 
 * word.h - CS50 'TSE' common module
 *
 * normalize the word given
 *
 * CS50 
 */
#ifndef __WORD_H
#define __WORD_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/**************** global types ****************/

/**************** functions ****************/

/**************** normalizeWord() **************/
/* changes a string to lower case
 *
 * Caller provides: 
 *	string word
 * We return:
 * 	nothing, we are changing the pointer to the string
 */
void normalizeWord(char *word);

#endif // __WORD_H
