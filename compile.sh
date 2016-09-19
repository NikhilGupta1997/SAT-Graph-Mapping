#!/bin/bash

## Compile our two program files
g++ -std=c++11 -Ofast -march=native -o create main1.cpp
g++ -std=c++11 -Ofast -march=native -o map  main2.cpp
