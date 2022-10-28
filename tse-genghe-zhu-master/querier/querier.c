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
#include "../common/word.h"
#include "../libcs50/hashtable.h"
#include "../libcs50/counters.h"
#include "../libcs50/memory.h"
#include <unistd.h>
#include <sys/stat.h>
#include <ctype.h>


/**************** file-local global variables ****************/
/* none */

/**************** local types ****************/
struct twocts {
	counters_t *result;
	counters_t *another;
};

struct docScore {
        int docID;
        int score;
};

struct docScoreArray {
	struct docScore* doc_score;
	int arraySize;
};

/**************** global types ****************/

/**************** global functions ****************/
/* that is, visible outside this file */

/**************** local functions ****************/
/* not visible outside this file */
int fileno(FILE *stream);
static void prompt(void);
void process_query(hashtable_t *index, char *pageDirectory);
void run_query(hashtable_t *index, int numWords, char ** words, char *pageDirectory);
void generate_array(counters_t *query, char *pageDirectory);
void print_array(int arraySize, struct docScore *rankedResults, char *pageDirectory);
void counters_intersect(counters_t* ct1, counters_t* ct2);
void intersect_helper(void *arg, const int key, const int count);
void counters_union(counters_t* ct1, counters_t* ct2);
void union_helper1(void *arg, const int key, const int count);
void union_helper2(void *arg, const int key, const int count);
static void itemcount(void *arg, const int key, const int count);
static void insertion_sort(void *arg, const int key, const int count);
int extract_words(char *line, char ** words);
bool valid_query(int numWords, char ** words);
counters_t* run_andSequence(hashtable_t *index, int lenAndSequence, char **andSequence);

static inline int min(const int a, const int b) {
  return (a < b ? a : b);
}

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
	char* indexFile = argv[2];
	FILE *fp = fopen(indexFile, "r");
        if (fp == NULL) {
		fprintf(stderr,"indexFile %s is not readable.\n", indexFile);
                return 3;
        }
	int lines = lines_in_file(fp);
	fclose(fp);

	hashtable_t *index = hashtable_new(lines);
	assertp(index, "failed to create hashtable index\n");

        index_load(indexFile, index);

	process_query(index, pageDirectory);

	// clean up
	index_delete(index);
	return 0;
}


/**************** prompt() ****************/
// from hints
static void prompt(void)
{
  // print a prompt iff stdin is a tty (terminal)
  if (isatty(fileno(stdin))) {
    printf("Query? ");
  }
}

/**************** process_query() ****************/
void process_query(hashtable_t *index, char *pageDirectory)
{
	while (!feof(stdin)) {
		prompt();
		char *line = readlinep();
		// when exiting ctrl-d
		if (line == NULL) {
			return;
		}
		char ** words = malloc((strlen(line)+1)/2 * sizeof(char*));
		int numWords = extract_words(line, words);
		if (numWords > 0) {
			printf("Query: "); 
			for (int i = 0; i < numWords; i++) {
				printf("%s ", words[i]);
			}
			printf("\n");
			if (valid_query(numWords, words)) {
				run_query(index, numWords, words, pageDirectory);
			}
		}


		free(words);
		free(line);
	}
}

/**************** extract_words() ****************/
int extract_words(char *line, char ** words)
{
	normalizeWord(line);
	//bool inWord = false;
	int totalNumWords = 0;
	//int length = (int) strlen(line);
	for (char *p = line; *p != '\0'; p++) {
		if (isalpha(*p) == 0 && isspace(*p) == 0) {
			printf("Error: bad character '%c' in query.\n", *p);
			return 0;
		} 
		if (isalpha(*p) != 0) {
			words[totalNumWords] = p;
			totalNumWords++;
			while (isalpha(*(p + 1))) {
				p++;
			}
			if (isspace(*(p + 1)) != 0) {
				*(p + 1) = '\0';
				p++;				
			}
		}
	}
	return totalNumWords;
}

/**************** valid_query() ****************/
bool valid_query(int numWords, char ** words)
{
	// check first and last words are not "and" or "or"
	if (strcmp(words[0], "and") == 0 || strcmp(words[0], "or") == 0) {
		printf("Error: '%s' cannot be first\n", words[0]);		
		return false;
	}

	if (strcmp(words[numWords-1], "and") == 0 || strcmp(words[numWords-1], "or") == 0) {
		printf("Error: '%s' cannot be last\n", words[numWords-1]);
                return false;
	}

	for (int i = 1; i < numWords-1; i++) {
		if ((strcmp(words[i], "and") == 0 || strcmp(words[i], "or") == 0) && 
				(strcmp(words[i+1], "and") == 0 || strcmp(words[i+1], "or") == 0)) {
			printf("Error: 'and' and 'or' cannot be adjacent\n");
			return false;
		}
	}
	return true;
}

/**************** run_query() ****************/
void run_query(hashtable_t *index, int numWords, char ** words, char *pageDirectory)
{
	char **andSequence = words;
	counters_t *query = counters_new();
        assertp(query, "failed to create counters_t query");
	int lenAndSequence = 1;
	bool inAndSequence = true;
	

	for (int i = 1; i < numWords; i++) {
		if (inAndSequence && strcmp(words[i], "or") != 0) {
			lenAndSequence++;
		} else if (inAndSequence && strcmp(words[i], "or") == 0) {
			inAndSequence = false;
			counters_t * andSequenceCounter = 
				run_andSequence(index, lenAndSequence, andSequence);
			counters_union(query, andSequenceCounter);
			counters_delete(andSequenceCounter);
			lenAndSequence = 0;
		} else if (!inAndSequence && strcmp(words[i], "or") != 0) {
			andSequence = &words[i];
			inAndSequence = true;
			lenAndSequence++;
		} 
	}

	counters_t * andSequenceCounter = 
		run_andSequence(index, lenAndSequence, andSequence);
	counters_union(query, andSequenceCounter);
	counters_delete(andSequenceCounter);


	// generate a sorted list (ranking results in lab6 hints)
	generate_array(query, pageDirectory);
	counters_delete(query);
}

/**************** generate_array() ****************/
void generate_array(counters_t *query, char *pageDirectory)
{
	int arraySize = 0;
	counters_iterate(query, &arraySize, itemcount);
	struct docScore rankedResults[arraySize];
	// initialize all docScores in array to 0 so we know which ones we initialized
	for (int i = 0; i < arraySize; i++) {
		struct docScore placeHolder = {0,0}; 
		rankedResults[i] = placeHolder;
	}
	struct docScoreArray rankedResults_size = {rankedResults, arraySize};	
	counters_iterate(query, &rankedResults_size, insertion_sort);
	print_array(arraySize, rankedResults, pageDirectory);	
	printf("-----------------------------------------------\n");
	//free(rankedResults);

}

/**************** print_array() ****************/
void print_array(int arraySize, struct docScore *rankedResults, char *pageDirectory) 
{
	if (arraySize == 0) {
		printf("No documents match.\n");
		return;
	}

	if (rankedResults[0].score == 0) {
		printf("No documents match.\n");
                return;
	}

	for (int i = 0; i < arraySize; i++) {
		if (rankedResults[i].score != 0) {
			char *docName = malloc(100*sizeof(char));
			sprintf(docName, "%s/%d", pageDirectory, rankedResults[i].docID);
			FILE *fp = fopen(docName, "r");
			assertp(fp, "failed to open files");
			free(docName);
	
			char *url;
			url = freadlinep(fp);
			printf("score %3d doc %3d: %s\n", rankedResults[i].score, rankedResults[i].docID, 
				url);
			free(url);
			fclose(fp);
		} else {
			return;
		}
	}
}

/**************** run_andSequence() ****************/
counters_t* run_andSequence(hashtable_t *index, int lenAndSequence, char **andSequence)
{
	counters_t *counter = counters_new();
	assertp(counter, "failed to create counters_t counter");
	counters_union(counter, hashtable_find(index, andSequence[0]));
	for (int i = 1; i < lenAndSequence; i++) {
		if (strcmp(andSequence[i], "and") != 0) {
			counters_intersect(counter, hashtable_find(index, andSequence[i]));
		}
	int arraySize = 0;
	counters_iterate(counter, &arraySize, itemcount);
	}
	return counter;
}

/**************** counters_intersect() ****************/
// from activity
void counters_intersect(counters_t* ct1, counters_t* ct2)
{
	if (ct1 == NULL) {
		ct1 = counters_new();
		assertp(ct1, "counters 1 invalid");
	}
	
	if (ct2 == NULL) {
		ct2 = counters_new();
		assertp(ct1, "counters 1 invalid");
	}

	struct twocts args = {ct1, ct2};
	counters_iterate(ct1, &args, intersect_helper);
}

/**************** intersect_helper() ****************/
void intersect_helper(void *arg, const int key, const int count)
{
	struct twocts *two = arg;

	counters_set(two->result, key, min(count, counters_get(two->another, key)));

}

/**************** counters_union() ****************/
void counters_union(counters_t* ct1, counters_t* ct2)
{
	if (ct1 == NULL) {
		ct1 = counters_new();
		assertp(ct1, "counters 1 invalid");
	}
	
	if (ct2 == NULL) {
		ct2 = counters_new();
		assertp(ct2, "counters 2 invalid");
	}
	
	int arraySize = 0;
	counters_iterate(ct1, &arraySize, itemcount);

	arraySize = 0;
	counters_iterate(ct2, &arraySize, itemcount);
        
	struct twocts args = {ct1, ct2};
        counters_iterate(ct1, &args, union_helper1);
	counters_iterate(ct2, &args, union_helper2);
}

/**************** union_helper1() ****************/
void union_helper1(void *arg, const int key, const int count)
{
        struct twocts *two = arg;

        counters_set(two->result, key, count + counters_get(two->another, key));
}

/**************** union_helper2() ****************/
void union_helper2(void *arg, const int key, const int count)
{
        struct twocts *two = arg;
	if (counters_get(two->result, key) == 0 && count != 0) {
	        counters_set(two->result, key, count);
	}
}

/**************** itemcount() ****************/
static void itemcount(void *arg, const int key, const int count)
{
	int *nitems = arg;

	if (nitems != NULL && key >= 0)
		(*nitems)++;
}

/**************** insertion_sort() ****************/
static void insertion_sort(void *arg, const int key, const int count)
{
	struct docScoreArray * rankedResults_size = arg;
	struct docScore *rankedResults = rankedResults_size->doc_score;
	assertp(rankedResults, "failed to initilize rankedResults");
	if (key >= 0) {
		int i = 0;
		while(rankedResults[i].score >= count) {
			i++;
		}
		if (rankedResults[i].score != 0 && rankedResults[i].docID != 0) {
			int arraySize = rankedResults_size->arraySize-1;
			while (arraySize >= i) {
				if (rankedResults[arraySize].score != 0 && 
						rankedResults[arraySize].docID != 0) {
					rankedResults[arraySize + 1].score = rankedResults[arraySize].score;
					rankedResults[arraySize + 1].docID = rankedResults[arraySize].docID;	
				}
				arraySize--;
			}

		}
		rankedResults[i].score = count;
		rankedResults[i].docID = key;
	}
}
