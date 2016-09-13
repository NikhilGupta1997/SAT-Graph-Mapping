#!/bin/bash

## This is to run the second program main2.cpp

if [ ! -e "$1.satoutput" ]; then
    echo "Inputfile doesn't exist. Exitting..."
    exit 1
fi

if [ -e "map" ]; then
    ./map "$1.satoutput" "$1.graphs" "$1.mapping"
else
    echo "First run compile.sh to compile the code"
fi 
