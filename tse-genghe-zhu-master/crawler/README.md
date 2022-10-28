# CS50 TSE crawler module

## Usage

To build `crawler.c`, run `make`
This program assumes that there exists libraries libcs50.a in ../libcs50/libcs50.a and common.a in ../common/common.a

To run, call in command line with 3 arguments: `./crawler seedURL pageDirectory maxDepth`

## Inputs and outputs

input: command line parameters

output: save each explored webpage to file, one per page with unique document ID as file name 1,2,3 ... etc

in each file, there exists:
* the page URL on the first line
* the depth of the page on the second line
* the page contents (HTML) on the third line

## Overview
* `main` parses parameters and passes them to the crawler
* `crawler` uses a bag to track pages to explore, and hashtable to track pages seen; when it explores a page it gives the page URL to the pagefetcher, then the result to pagesaver, then to the pagescanner
* `process_website` calls pagefetcher, pagesaver, pagescanner, urldelete
* `pagefetcher` fetches the contents (HTML) for a page from a URL and returns
* `pagesaver` outputs a page to the appropriate file 
* `pagescanenr` extracts URLs from a page and returns one at a time
* `urldelete` delete a url

## Error Messages
1. incorrect num arguments
2. url cannot be normalized
3. directory does not exist
4. maxdepth out of range 
5. initalize new bag failed
6. initialize new hashtable failed
7. failed to fetch website
8. url is not internal


