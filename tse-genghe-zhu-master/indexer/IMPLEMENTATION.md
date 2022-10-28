### Implementation for TSE Indexer

Genghe Zhu
CS 50 Summer 2020
Dartmouth College

##Pseudocode

# `indexer`

* Process and validate command-line parameters
 	* Check number of arguments
 	* Check directory is crawled directory
  	* Check output index file
* Initialize data structure index
	* Call hashtable new
* `index_build(directory, index)`
	* Read every number file in the directory 
        * For each file, read every word
		* For each word, if it is in hashtable, call counter add
		* If not, add new counter to hashtable, then call counter add                
* `index_save(file, index)`
	* Read the hashtable 
                * For each key, read the counter
                * Print the key and counter pair to a line
* clean up data structures
	* Free the hashtable
 
* # `indextest`

* Process and validate command-line parameters
	* Check number of arguments
        * Check input index file
        * Check output index file
* Initialize data structure index
	* Call hashtable new
* `index_load(file1, index)`
	* Read the index file line by line
	* For each line, read the key and counter pair
		* Save the data to counter
		* Save key and counter pointer to hashtable
* `index_save(file2, index)`
	* Read the hashtable 
		* For each key, read the counter
		* Print the key and counter pair to a line
* clean up data structures
	*  Free the hashtable
