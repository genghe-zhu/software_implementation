/*
 * index.c - saves and lodes index files 
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include "word.h"
#include "../libcs50/hashtable.h"
#include "../libcs50/counters.h"
#include "../libcs50/memory.h"
#include "../libcs50/file.h"
#include "index.h"

/**************** local function prototypes ****************/
void save_item (void *arg, const char *key, void *item);
void save_counts (void *arg, const int key, int count); 
void load_item (hashtable_t *ht, FILE *fp);
void page_build(FILE *fp, int filename, hashtable_t *index);
static void ct_delete(void *item);


/**************** index_save ****************/
void index_save(char *file, hashtable_t *index)
{
	// check input arguments: # of arguments
	if (file == NULL) {
		fprintf(stderr, "null file name\n");
		return; 
	}

	// create and initialize hashtable content
	if (index == NULL) {
		fprintf(stderr, "null hashtable pointer\n");
		return;
	}

	// save hashtable content to an external file 
	FILE *fp = fopen(file, "w");
	if (fp == NULL) {
		fprintf(stderr, "failed to open file: %s\n", file);
		return;
	}
	hashtable_iterate(index, fp, save_item);
	fclose(fp); 

	return;
}

/**************** index_load ****************/
void index_load(char *file, hashtable_t *index)
{
        // check input arguments: # of arguments
        if (file == NULL) {
                fprintf(stderr, "null file name\n");
                return;
        }

        // create and initialize hashtable content
        if (index == NULL) {
                fprintf(stderr, "null hashtable pointer\n");
                return;
        }

        // read words save to hashtable 
        FILE *fp = fopen(file, "r");
        if (fp == NULL) {
                fprintf(stderr, "failed to open file: %s\n", file);
                return;
        }
        load_item(index, fp);
        fclose(fp);

        return;
}


/******** helper to save item in hashtable ********/
void save_item (void *arg, const char *key, void *item)
{
	FILE *fp = arg; 
	counters_t *c = item;
	assertp(c, "counter pointer is null\n");

	fprintf(fp, "%s ", key);
	counters_iterate(c, fp, save_counts);
	fprintf(fp, "\n");
}

/******** helper to load item in hashtable ********/
void load_item (hashtable_t *ht, FILE *fp)
{
	char *line; 

	while ((line = freadlinep(fp)) != NULL) {
		char * linecopy = line;
		char *hashKey = malloc(100*sizeof(char));
		int offset; 
		sscanf(line, "%s %n", hashKey, &offset);
		line += offset;
		int counterKey;
		int counterValue;
		counters_t *counter = counters_new();
		while (sscanf(line, "%d %d %n", &counterKey, &counterValue, &offset) == 2) {
			line += offset;
			//printf("counterKey: %d counterValue: %d\n", counterKey, counterValue); 
			counters_set(counter, counterKey, counterValue);
		}
		free(linecopy);
		hashtable_insert(ht, hashKey, counter);		
		free(hashKey);
	}
}

/******** helper to save items in counters ********/
void save_counts (void *arg, const int key, int count)
{
	FILE *fp = arg; 
	fprintf(fp, " %d %d", key, count);
}

/******** delete counters item ********/
void index_delete(hashtable_t *index)
{
	hashtable_delete(index, ct_delete);
}

/******** delete counters item ********/
static void ct_delete(void *item)
{
        counters_t* ct = item;

        if (ct != NULL) {
                counters_delete(ct);
	}
}

//to fix later
//
//
//
/******** index_build()  ********/
void index_build(char *pageDirectory, hashtable_t *index)
{
        int i = 1;
        assertp(pageDirectory, "pageDirectory pointer is NULL\n");
        assertp(index, "hashtable index pointer is NULL\n");
        char *file_name = malloc(100*sizeof(char));
        assertp(file_name, "file_name pointer is NULL\n");

        sprintf(file_name, "%s/%d", pageDirectory, i);

        FILE *fp = fopen(file_name, "r");
        while (fp != NULL) {
                //index_load(file_name, index);
		page_build(fp, i, index);
                fclose(fp);
                i++;
                sprintf(file_name, "%s/%d", pageDirectory, i);
                fp = fopen(file_name, "r");
        }
        free(file_name);
}

/******** page_build()  ********/
void page_build(FILE *fp, int filename, hashtable_t *index)
{
	char *word;
	word = freadlinep(fp);
	free(word);
	word = freadlinep(fp);
	free(word);

	while ((word = freadwordp(fp)) != NULL) {
		normalizeWord(word);
		
		counters_t *ctrs = hashtable_find(index,word);
		if (ctrs == NULL) {
			ctrs = counters_new();
			assertp(ctrs, "failed to allocate memory for counters\n");
			hashtable_insert(index, word, ctrs);
		}
		free(word);
		counters_add(ctrs, filename);
	}
	//free(word);
}

