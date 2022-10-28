#!/bin/bash
#
# query.sh - give case number and death number for input state and/or date
#
# Usage: ./first 
#
# Input: state, date
# Output: case number, death number
#
# Genghe Zhu, Summer 2020

file="covid.csv"
# define directories
 
# check arguments
if [ $# -eq 0 -o $# -gt 2 ]; then
        echo 1>&2 "incorrect number of arguments. Usage: ./query.sh state [date]"
        exit 1
fi

# check if file exist
if [ ! -e $file  ]
        then
                echo 1>&2 "file $file does not exist"
                exit 2
        fi
 
 
# main business
state=$1
cases=0
deaths=0

# check if state exists in file
flag=$(grep "$state" "$file")
if [ "$flag" == "" ]
then
	echo 1>&2 "$state state does not exist"
	exit 3
fi	

# state only argument case
if [ $# -eq 1 ]; then

	# get case and death for the latest date of that state for every county
	for i in $(grep "$state" "$file" | cut -d , -f 1,2,3,5,6 | sort -t ',' -k2,2 -k1,1r |  sort -um -t ',' -k 2.1,2.0 | cut -d , -f 4,5)
	do
		case="$(echo $i | cut -d',' -f1)" 
		death="$(echo $i | cut -d',' -f2)" 
		let cases=$cases+$case
		let deaths=$deaths+$death
		flag=1
	done
	# print the output
        echo $state ": Case:" $cases "Death:" $deaths
fi

# state and date argument case
if [ $# -eq 2 ]; then
        date=$2

	# check if the date exists
	flag=$(grep "$date" "$file")
	if [ "$flag" == "" ]
	then
		echo 1>&2 "date $date does not exist"
		exit 4
	fi	

	# get case and death for that specific date
	for i in $(grep "$state" "$file" | grep "$date" | cut -d , -f 5,6)
	do
		case="$(echo $i | cut -d',' -f1)" 
		death="$(echo $i | cut -d',' -f2)" 
		let cases=$cases+$case
		let deaths=$deaths+$death
	done

	#print the output
        echo $state ": Case:" $cases "Death:" $deaths
	
fi 
 
# exit
exit 0
