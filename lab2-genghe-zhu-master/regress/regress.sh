#!/bin/bash
#
# regress.sh - perform regression testing on group of scripts and its running results
#
# Usage: ./regress.sh dirname testfilename...
#
# Input: dirname testfilename ...
# Output: 
#
# Genghe Zhu, Summer 2020

# define directories

# check arguments
if [ $# -lt 2 ] 
then
    echo 1>&2 "incorrect number of arguments. Usage: ./regress.sh dirname testfilename..."
    exit 1
fi

dir=$1

# check if directory is a directory
if [ -e $dir  ]
then
    if [ ! -d $dir ]
    then
        echo 1>&2 "directory $dir is not a directory"
        exit 2
    fi
    
fi
echo $dirExist

# check if files exist
for ((i = 2; i <= $#; i++ ))
do
    #printf '%s\n' "${!i}"
    file=${!i}

    if [ ! -r $file -o ! -f $file ]
    then
        echo 1>&2 "test case '$file' is not a file (or not readable)"
        exit 3
    else
        files[i-2]=$file
    fi        
done    


# main business
date=$(date +"%Y%m%d.%H%M%S")
mkdir $date
echo "saved test results in $date ..."

# run each file get output
for i in ${files[*]}
do
    cp $i "$date/$i.test"
    bash $i > $date/$i.stdout  2> $date/$i.stderr
    status=$?
    echo $status > "$date/$i.status"
    cat $date/$i.stderr >> $date/$i.stdout
    rm $date/$i.stderr
done

# move or compare files
if [ ! -e $dir ]
then
    # move the directory
    mv $date $dir
    status=$?
    if [ $status -eq 0 ]
    then
        echo "saved test results in $dir"
    else
        echo "failed to save test results in $dir; they remain in $date"
    fi    
    exit $status
else 
    # compare the directory
    echo "comparing $date $dir"
    diff --brief $date $dir
    status=$?
    if [ $status -eq 0 ]
    then
        echo "no differences"
    fi    
    exit $status
fi
