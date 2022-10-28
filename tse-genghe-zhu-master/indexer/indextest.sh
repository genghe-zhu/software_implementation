#!/bin/bash
#
# indextest.sh - test indexer.c and indextest.c 
#
#
#
# Genghe Zhu, Summer 2020


printf "\ntest usage syntax errors"

printf "\ntest no args"
./indexer 
printf "\ntest no file name"
./indexer ../data
printf "\ntest not writbale directory"
./indexer ../wrong index.txt

printf "\n\nrun test\n"
make test

printf "\n\ndiff input and output index file\n"
diff index.txt index.new
