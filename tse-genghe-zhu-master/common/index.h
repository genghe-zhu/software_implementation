/* 
 * index.h - CS50 'TSE' common module
 *
 * normalize the word given
 *
 * CS50 
 */
#ifndef __INDEX_H
#define __INDEX_H

#include <stdio.h>
#include <stdlib.h>
#include "../libcs50/hashtable.h"
#include "../libcs50/counters.h"
#include "../libcs50/memory.h"
#include "../libcs50/file.h"
#include "index.h"

/**************** global types ****************/

/**************** functions ****************/

/**************** index_save() **************/
/* save index hashtable to a file
 *
 * Caller provides: 
 * 	file and hashtable 
 * We return:
 * 	nothing, we are writing to a file
 */
void index_save(char *file, hashtable_t *index);

/**************** index_load() **************/
/* loads the words from the file into the hashtable
 *
 * Caller provides: 
 *      file and hashtable
 * We return:
 *      nothing, we are loading the index from file to hashtable
 */
void index_load(char *file, hashtable_t *index);

/**************** index_delete() **************/
/* deletes hashtable_t module, used when deleting index hashtable
 *
 * Caller provides: 
 *      void *item for the pointer to the hashtbale index
 * We return:
 *      nothing, deletes the hashtable by calling counter delete
 */
void index_delete(hashtable_t *index);

/**************** index_build() **************/
/* build a hashtable from reading the website directory
 *
 * Caller provides: 
 *      directory and hashtable
 * We return:
 *      nothing, we are building the index from files to hashtable
 */
void index_build(char *pageDirectory, hashtable_t *index);


#endif // __INDEX_H

