#!/bin/bash

# ensure the requisite number of args
if [ 2 -ne $# ]; then
	echo "Usage: $0 <filename> <writestr>"
    exit 1
fi

writefile=$1
writestr=$2  
basepath=$(dirname $writefile)

# create parent directories if needed
mkdir -p $basepath

# create/overwrite file
echo $2 > $1