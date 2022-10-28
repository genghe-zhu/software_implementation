# IMPLEMENTATION.md

## Genghe Zhu, Summer 2020

### Detailed pseudocode
1. check arguments
	1.1 use `isCrawlerDirectory()` to validate `pageDirectory`
	1.2 check if file is readable 
2. load index from index file
	2.1 use `indexLoad()`
3. process query from keyboard with `process_query()`
        3.1 extract words from line `extract_words()`
        3.2 check if query is valid `valid_query()`
        3.3 run query `run_query()`
                3.3.1 split the query into andSequence 
                3.3.2 run query for each andSequence `run_andSequence()`
			3.3.2.1 use `counters_intersect()` for `run_andSequence()`
                3.3.3 union andSequence `counters_union()`
        3.4 sort output `generate_array()`
                3.4.1 loop through counters to get size
                3.4.2 save counters to sorted array `insertion_sort()`
        3.5 print the output of query `print_array()`
4. clean up `index_delete()`

### Data structures needed 

`struct twocts` 
needed for union and intersect counters iterate

`struct docScore` 
save document id and score

`struct docScoreArray`
used for saving docScore into the sorted array 

### Functions used
`static void prompt(void);`
print the query

`void process_query(hashtable_t *index, char *pageDirectory);`
main function to process query, calls valid query and run query

`void run_query(hashtable_t *index, int numWords, char ** words, char *pageDirectory);`
run the query from query line

`void generate_array(counters_t *query, char *pageDirectory);`
create the sorted array

`void print_array(int arraySize, struct docScore *rankedResults, char *pageDirectory);`
prints the sorted array

`void counters_intersect(counters_t* ct1, counters_t* ct2);`
intersects two counters

`void intersect_helper(void *arg, const int key, const int count);`
function used for `counters_iterate` during `counters_intersect`

`void counters_union(counters_t* ct1, counters_t* ct2);`
union two counters

`void union_helper1(void *arg, const int key, const int count);`
function used for `counters_iterate` during `counters_union` 
iterate through first counters key

`void union_helper2(void *arg, const int key, const int count);`
function used for `counters_iterate` during `counters_union` 
iterate through second counters key

`static void itemcount(void *arg, const int key, const int count);`
get the number of counters used by `counters_iterator` to get arraySize

`static void insertion_sort(void *arg, const int key, const int count);`
insert the counters by count from greatest to least

`int extract_words(char *line, char ** words);`
get the words from the query

`bool valid_query(int numWords, char ** words);`
check if the query line is valid

`counters_t* run_andSequence(hashtable_t *index, int lenAndSequence, char **andSequence);`
run query for andSequence

`static inline int min(const int a, const int b)` 
get the minimum of two integers

