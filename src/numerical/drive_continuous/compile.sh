#!/usr/bin/env bash

./regexp.py expressions_resident.txt
./regexp.py expressions_fmatrix_x1m.txt
./regexp.py expressions_fmatrix_x2m.txt
./regexp.py expressions_eigenvecs_x1m.txt
./regexp.py expressions_eigenvecs_x2m.txt
./regexp.py selgrad_x1m.txt
./regexp.py selgrad_x2m.txt

./generate_cpp.py

un=`uname`

lrtflag=''

if [ "${un}"=='Linux' ];
then lrtflag='-lrt'
fi

g++ -Wall -o xdrive_continuous drive_continuous2.cpp -lm "${lrtflag}" -lgsl -lgslcblas
