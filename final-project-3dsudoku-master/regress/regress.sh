#!/bin/bash
#
# regress.sh - peform regression testing
#
# usage: regress.sh dirname testfilename...
# where dirname is the name of a directory containing test results, and
# where each testfilename is the name of a file containing bash command(s) for one test case. Note that test files can be in other directories.
#
# input: dir name, test files
# output: 
#
# there must be at least two arguments;
# if something by the name dirname exists, it must be a directory;
# each testfilename must be a regular file and be readable.
#
# exit 1 : num args less than 2
# exit 2: dirname is not a directory
# exit 4: file is not readable
# exit 5: error making date directory
# exit 6: error in renaming date directory
# exit 7: test case is not a file
# exit 10: differences when comparing
#
# Author: William Scott

# checks if num of args is less than 2
if [ $# -lt 2 ]; then
	echo 1>&2 Incorrect number of arguments. Usage: ./regress.sh dirname testfilename...
	exit 1
fi

# checks if dirname exists, and if it does, then must be a directory
if [ -e "$1" ]; then 
	if [ ! -d "$1" ]; then
		echo 1>&2 Error: first argument "('$1')" is not a directory
		exit 2
	fi
fi

DIRNAME="$1"

# check if files exists and are readable
for file in "${@:2}"
do
	if [ ! -r "$file" ]; then
		echo "Error: "$file" is not a file (or not readable)"
		exit 4
	fi
	if [ -d "$file" ]; then
		echo "Error: test case '$file' is a directory. It must be a file"
		exit 7
	fi
done

date="$(date +"%Y-%m-%d %T" | sed -e "s/-//g" -e "s/ /./g" -e "s/://g")"
mkdir ./$date 2> /dev/null 
if [ $? -ne 0 ]; then
	echo Error in creating directory...
	exit 5
fi

for file in "$@"
do
	if [ "$file" != "$1" ]; then
		strippedfile=$(basename "$file") 
		cp "$file" $date/"$strippedfile".test
		bash "$file" 2>$date/"$strippedfile".output >>$date/"$strippedfile".output
		echo $? > $date/"$strippedfile".status
	fi
done

if [ ! -d "$DIRNAME" ]; then
	mv $date/ $DIRNAME/ 2> /dev/null
	if [ $? -ne 0 ]; then
		echo "failed to save test results in $DIRNAME; they remain in $date"
		exit 6
	fi
	echo saved test results in $DIRNAME 
else 
	# compare with date/ with dirname/
	echo saved test results in $date 
	echo comparing $date with $DIRNAME...
	diff -q $DIRNAME/ $date/
	if [ $? -eq 0 ]; then
		echo no differences comparing $date with $DIRNAME
	else
		exit 10
	fi 
fi

