#!/bin/bash
#
# sudoku.sh uses the las vegas method to generate a valid sudoku puzzle
#
# Usage: ./sudoku.sh create size [server]
# where the second argument is an optional number for the size of the sudoku puzzle
#
# CS50, Dartmouth College, Summer 2020
# Sudoku final project
#
# Authors: Rachael Williams, Isabella Zenkl, Genghe Zhu, Garrett Scott
# Last Update: 8/26/2020

# validate arguments
if [ $# -lt 2 ]; then
	echo 1>&2 "usage: ./sudoku.sh create size [server]"
	exit 35
fi

if [[ $1 != "create" ]]; then
	echo 1>&2 "usage: ./sudoku.sh create size [server]"
	exit 36
fi

if [[ $# -eq 3 && $3 != "server" ]]; then
	echo 1>&2 "usage: ./sudoku.sh create size [server]"
	exit 38
else 
	str="../"
fi

# set the number for sudoku size
if [ $2 -eq 3 ]; then
	num=3
elif [ $2 -eq 4 ]; then
	num=4
elif [ $2 -eq 6 ]; then
	num=6
elif [ $2 -eq 9 ]; then
	num=9
elif [ $2 -eq 16 ]; then
	num=16
else 
	echo "$2 is invalid size. must be 3, 4, 6, 9, or 16"
	exit 37
fi

found_puzzle=0 # int value that acts as boolean if a puzzle was found
i=0 # variable to store the number of puzzles tried

# keep running create and solve together until puzzle found
while [ $found_puzzle -eq 0 ]
do
	let "i+=1" # count the number of times it runs
	
	if [[ $# -eq 3 && $3 == "server" ]]; then
		# sudoku is in a different location when running script from server
		# run create and output to file
		.././sudoku create $num server > puzzle.txt

		# redirect input from created puzzle.txt
		cat puzzle.txt | .././sudoku solve $num server > solution.txt
	else
		# run create and output to file
		./sudoku create $num > puzzle.txt

		# redirect input from created puzzle.txt
		cat puzzle.txt | ./sudoku solve $num > solution.txt
	fi
	
	# if solve returns a value of 0
	if [ $? -eq 0 ] ;
	then
		cat puzzle.txt
		found_puzzle=1; # puzzle is found
	fi

	sleep 1 # sleep for one second in between runs to get new random seed
done

rm -f solution.txt

exit 0

