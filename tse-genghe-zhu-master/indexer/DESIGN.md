### Design for TSE Indexer

Genghe Zhu
CS 50 Summer 2020

## Usage
Command line with two arguments: `indexer pageDirectory indexFilename`

## Input/Output
Input: directory from crawler

Output: file with one word per line/one line per word that provides the documentID and count of the word as a pair of positive integers greater than 0

ex: word docID count docId count

## Functions/Modules
Indexer contains a main function which checks the command line arguments and intializes the data structure index

Calls `index_build()` and `index_save()` from index.h in the common.a library. 
* `index_build()` reads in documents from crawler directory
* `index_save()` writes index into a given file

## Data structures used
* hashtable: key word and values are counters
* counter: key docID


