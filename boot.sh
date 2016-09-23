#!/bin/bash

source compile.sh
echo "Compiled"
python generate.py $1 $2 $3 $4 > 'test.graphs'
echo "Running"
source run1.sh 'test'
echo "Done"
minisat 'test.satinput' 'test.satoutput' 
source run2.sh 'test'
python check.py 'test.graphs' 'test.mapping'

