#!/bin/bash

## This is to run the first program main1.cpp

if [ ! -e "$1.graphs" ]; then
    echo "Inputfile doesn't exist. Exitting..."
    exit 1
fi

if [ -e "create" ]; then
    ./create "$1.graphs" "$1.satinput"
else
    echo "First run compile.sh to compile the code"
fi
