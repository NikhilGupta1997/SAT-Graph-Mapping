#!/bin/bash

source compile.sh
python generate.py $1 $2 $3 $4 > 'test.graphs'
source run1.sh 'test'
source minisat 'test.satinput' 'test.satoutput' 
source run2.sh 'test'
python check.py 'test.graphs' 'test.mapping'

