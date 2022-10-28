#!/bin/bash
#
# testing.sh
#
#
#
# Genghe Zhu, Summer 2020


printf "\ntest usage syntax errors\n"

printf "\ntest no args\n"
printf "./querier\n"
./querier 
printf "\n\ntest not crawled directory\n"
printf "./querier data ~cs50/data/tse-output/letters-index-6\n"
./querier data ~cs50/data/tse-output/letters-index-6
printf "\n\ntest not readable indexfile\n"
printf "./querier ~cs50/data/tse-output/letters-depth-6/ ~cs50/data/tse-output/letters-index-7\n"
./querier ~cs50/data/tse-output/letters-depth-6/ ~cs50/data/tse-output/letters-index-7

printf "\n\nrun examples from lecture notes\n"

./querier ~cs50/data/tse-output/letters-depth-6/ ~cs50/data/tse-output/letters-index-6 < example-test.querier

printf "\n\nrun simple test from fuzzquery letters-index-6\n"

./querier ~cs50/data/tse-output/letters-depth-6/ ~cs50/data/tse-output/letters-index-6 <  letters-index-6.querier

printf "\n\nrun test from fuzzquery wilipedia-index-2\n"

./querier ~cs50/data/tse-output/wikipedia-depth-2/ ~cs50/data/tse-output/wikipedia-index-2 <  wikipedia-index-2.querier

printf "\n\nrun test from fuzzquery toscrape-index-2\n"

./querier ~cs50/data/tse-output/toscrape-depth-2  ~cs50/data/tse-output/toscrape-index-2 < toscrape-index-2.querier


