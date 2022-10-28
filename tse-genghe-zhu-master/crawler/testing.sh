#!/bin/bash
#
# testing.sh - test crawler.c  
#
#
#
# Genghe Zhu, Summer 2020

crawler="./crawler"
letter="http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters/index.html"
toscrape="http://old-www.cs.dartmouth.edu/~cs50/data/tse/toscrape/index.html"
wikipedia="http://old-www.cs.dartmouth.edu/~cs50/data/tse/wikipedia/index.html"
dir="../data"

rm -f $dir/*

printf "\n0. test usage syntax errors"

t0="$crawler $letter $dir"
echo $t0
$t0


t0="$crawler $letter $dir-wrong 0"
echo $t0
$t0

t0="$crawler $letter $dir -1"
echo $t0
$t0

t0="$crawler $letter $dir 11"
echo $t0
$t0

printf "\ntest not writbale directory"
t0="$crawler $letter /tmp/not_writable_dir 1"
echo $t0
$t0

printf "\n1. testing nonexisting server"
t0="$crawler http://old-www.cs.ddd $dir 1"
echo $t0
$t0

printf "\n2. testing noninternal server"
t0="$crawler http://www.google.com/ $dir 1"
echo $t0
$t0

printf "\n3. testing valid server but nonexisting page"
t0="$crawler http://old-www.cs.dartmouth.edu/~cs50/data/tse/asdf/index.html $dir 1"
echo $t0
$t0

printf "\n4. Crawl a simple, closed set of cross-linked web pages"
rm -f $dir/*
t0="$crawler $letter $dir 2"
echo $t0
$t0
printf "\n####expected 3 files in data\n"
ls $dir
cat $dir/*

printf "\n5. point crawler at letter site, explore at depths 1,2,3,4,5\n"
for i in 1 2 3 4 5
do
	rm -f $dir/*
	t0="$crawler $letter $dir $i"
	echo $t0
	$t0
	j=$i*2 
	if [ $i == 2 ]
	then
		j=3
	fi	
	if [ $i == 5 ]
	then
		j=9
	fi	
	printf "\n####expected $j files in data, get "
	ls $dir | wc -l
	printf "\n"
done

printf "\n6. Repeat with a different seed page in that same site\n"
rm -f $dir/*
t0="$crawler http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters/A.html $dir 1"
echo $t0
$t0
printf "\nexpected 3 files in data\n"
ls $dir

printf "\n7. point crawler at wikipedia site, explore at depths 0,1,2\n"
for i in 0 1 2 
do
	rm -f $dir/*
	t0="$crawler $wikipedia $dir $i"
	echo $t0
	$t0
	j=1
	if [ $i == 1 ]
	then
		j=7
	fi	
	if [ $i == 2 ]
	then
		j=1675
	fi	
	printf "\n####expected $j files in data, get "
	ls $dir | wc -l
	printf "\n"
done

printf "\n8. point crawler at toscrape site, explore at depths 0,1,2\n"
for i in 0 1 2
do
	rm -f $dir/*
	t0="$crawler $toscrape $dir $i"
	echo $t0
	$t0
	j=1
	if [ $i == 1 ]
	then
		j=73
	fi	
	if [ $i == 2 ]
	then
		j=585
	fi	
	printf "\n####expected $j files in data, get "
	ls $dir | wc -l
	printf "\n"
done
