# CS50 TSE common library

Modules support the TSE project, can be used by crawler, indexer, and querier.

## Usage

To build `common.a`, run `make`

To clean up, run `make clean`

## Overview

* `pagedir` - determine whether the pathname provided as pageDirectory is indeed a directory, and is writable
* `index` - function used to load and save index files
* `word` - normalize the words 
