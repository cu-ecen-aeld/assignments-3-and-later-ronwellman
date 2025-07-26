#!/bin/sh

# ensure the requisite number of args
if [ 2 -ne $# ]; then
	echo "Usage: $0 <directory> <search string>"
    exit 1
fi

filesdir=$1
searchstr=$2

files=$(find $filesdir -type f | wc -l)
contains=$(grep -r $searchstr $filesdir | wc -l)

echo "The number of files are $files and the number of matching lines are $contains" 
