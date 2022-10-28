# CS50 Lab 6: TSE Querier

## Genghe Zhu, Summer 2020

### querier overview and usage
Querier reads index files produced by indexer and page files produced by crawler to create search queries inputted by users from stdin

To run querier, input two args into the commandline: 

1. pathname of a directory produced by crawler

2. pathname of the file produced by indexer

### assumptions
No assumptions were made

### compilation
To compile run `make`

To test querier, run `make test` to run one testing example from stdin
`make test` runs `./querier pathname of the file produced by indexer`

To test for memory leaks, run `make valgrind`

Run `./testing.sh` to test invalid options, output from letters, toscrape, wikipedia
Notice, when we pipe in the input from a file, the input querier won't show up in the `testing.out`. 
`testing.out` has output from `testing.sh`

I generated a couple of testing files needed for `testing.sh`
the files include: 
* `example-test.querier`
* `letters-index-6.querier`
* `toscrape-index-2.querier`
* `wikipedia-index-2.querier`
