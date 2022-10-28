/* 
 * crawler.c - CS50 'TSE' crawler module
 *
 * see crawler.h for more information.
 *
 * CS50 
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "../common/pagedir.h"
#include "../libcs50/webpage.h"
#include "../libcs50/bag.h"
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
static void process_website(void *item, bag_t *bag, hashtable_t *hashtable, int count, char *dir, int maxDepth);
int crawl(char *url, char *dir, int maxDepth); 
bool pagefetcher(webpage_t *page, char *url);
void pagesaver(webpage_t* page, char *dir, int count, int depth);
void pagescanner(webpage_t *page, bag_t *bag, hashtable_t *hashtable, int depth); 
void urldelete(void *item);

	
/**************** main ****************/
int main(const int argc, char *argv[])
{
	char* program = argv[0];  // program name

	// check input arguments: # of arguments
	if (argc != 4) {
		fprintf(stderr, "usage: %s seedURL pageDirectory maxDepth\n", program);
		return 1; 
	}
	// check input arguments: URL validity
	char* url = argv[1];
	if (!NormalizeURL(url)) {
		fprintf(stderr, "%s cannot be normalized\n", url);
		return 2;
	}
	// check if pageDirectory is a pathname for existing diretory
	char* dir = argv[2];
	if (!dirExists(dir)) {
		fprintf(stderr, "%s directory does not exist or not writable\n", dir);
		return 3;
	}

        int maxDepth = atoi(argv[3]);
	if (maxDepth < 0 || maxDepth > 10) {
		fprintf(stderr, "maxDepth %d must be an integer in the range 0 to 10\n", maxDepth);
		return 4;
	}

	return crawl(url, dir, maxDepth);
}

int crawl(char *url, char *dir, int maxDepth) 
{
	bag_t *bag;
	bag = bag_new();
	// check if make bag success 
	if (bag == NULL) {
   		fprintf(stderr, "bag_new failed\n");
    		return 5;
  	}

	hashtable_t *hashtable;
	hashtable = hashtable_new(100);
	// check if make bag success 
	if (hashtable == NULL) {
   		fprintf(stderr, "hashtable_new failed\n");
    		return 6;
  	}


	// fetch the page
	// first make a copy of the url in heap memory
	char* urlcopy = assertp(malloc(strlen(url)+1), "url copy");
	strcpy(urlcopy, url);
	webpage_t *web = webpage_new(urlcopy, 0, NULL); 
	if (webpage_fetch(web)) { 
		if (!IsInternalURL(url)) {	
			fprintf(stderr, "%s url not internal\n", url);
			return 8;
		}

		bag_insert(bag, web);
		hashtable_insert(hashtable, webpage_getURL(web), webpage_getURL(web));
	}
	else { // failed to fetch the page
		fprintf(stderr, "failed to fetch %s\n", url);
		webpage_delete(web);
		return 7;
	}

	int count = 1;

	webpage_t *page;
	while ((page = bag_extract(bag)) != NULL) {
      		process_website(page, bag, hashtable, count, dir, maxDepth);
		count++;
    	}

	//webpage_delete(web);
	hashtable_delete(hashtable, urldelete);
	bag_delete(bag, webpage_delete);
	return 0;
}

/**************** process_website() **************/
static void process_website(void *item, bag_t *bag, hashtable_t *hashtable, int count, char *dir, int maxDepth)
{
	webpage_t *web = item;

	assertp(web, "NULL website \n");

	char *url = webpage_getURL(web);
	int depth = webpage_getDepth(web);
	printf("processing url: %s at depth %d\n", url, depth);
	if (!webpage_getHTML(web)) {
		if (!pagefetcher(web, url)) {
			return;
		}
	}
	pagesaver(web, dir, count, depth);
	if (depth < maxDepth) {
		pagescanner(web, bag, hashtable, depth);	
	}
	//webpage_delete(web);
}

/**************** pagefetcher()  ****************/
bool pagefetcher(webpage_t *page, char *url)
{
	//sleep(1); 		// pause for 1 second
	if (!webpage_fetch(page)) {	
		fprintf(stderr, "Can't fetch the website for url %s\n", url);
		return false;
	}
	return true;
}


/**************** pagesaver() ****************/
void pagesaver(webpage_t* page, char *dir, int count, int depth)
{
	char *file_name = malloc(100*sizeof(char));
	sprintf(file_name, "%s/%d", dir, count);	
	FILE *fp = fopen(file_name, "w");
        char *message = malloc(200*sizeof(char));
	sprintf(message, "cannot open file %s for writing\n", file_name);	
	assertp(fp, message);

	fprintf(fp, "%s\ndepth: %d\n%s", webpage_getURL(page), depth, webpage_getHTML(page));
	free(message);	
	fclose(fp);	
	free(file_name);
}


/**************** pagescanner() ****************/
void pagescanner(webpage_t *page, bag_t *bag, hashtable_t *hashtable, int depth) 
{
	int pos = 0;
	char *result;

	while ((result = webpage_getNextURL(page, &pos)) != NULL) {
		if (NormalizeURL(result)) {
			if (IsInternalURL(result)) {
				if (hashtable_insert(hashtable, result, result)) {	
					printf("\tinsert_page %s at depth %d\n", result, depth+1);
					webpage_t *web = webpage_new(result, depth+1, NULL); 
					if (webpage_fetch(web)) { 
						bag_insert(bag, web);
				
					}
				}	
			}
		}
	}
	free(result);
}

/**************** urldelete() ****************/
// delete a url
void urldelete(void *item)
{
  if (item != NULL) {
    free(item);
  }
}
