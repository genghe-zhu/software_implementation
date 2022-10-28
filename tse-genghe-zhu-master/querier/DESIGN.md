# DESIGN.md

## Genghe Zhu, Summer 2020

### Input
1. crawled directory
2. indexfile

user input from stdin: query line

### Output
Ranked document score, name, and url from query

### Data structures
`hashtable` loaded from indexer
`counters` with key as the docID

### Pseudo code
1. check arguments
2. load index from index file
3. process query from keyboard
	3.1 extract words from line
	3.2 check if query is valid
	3.3 run query 
		3.3.1 split the query into andSequence
		3.3.2 run query for each andSequence
		3.3.3 union andSequence
	3.4 sort output
		3.4.1 loop through counters to get size
		3.4.2 save counters to sorted array (insertion sort)
	3.5 print the output of query
4. clean up
